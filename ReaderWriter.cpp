#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <random>
#include <atomic>
#include <conio.h>

// 策略定义
#define READER_FIRST 1
#define WRITER_FIRST 2

class RWProblem {
private:
    int strategy;               // 策略：READER_FIRST 或 WRITER_FIRST
    int active_readers;         // 当前活跃读者数量
    int active_writers;         // 当前活跃写者数量（0或1）
    int waiting_readers;        // 等待的读者数量
    int waiting_writers;        // 等待的写者数量
    std::mutex mtx;             // 互斥锁
    std::condition_variable read_cond;  // 读者条件变量
    std::condition_variable write_cond; // 写者条件变量
    std::atomic<bool> stop_flag; // 停止标志

public:
    RWProblem(int strategy) : strategy(strategy), active_readers(0), active_writers(0),
        waiting_readers(0), waiting_writers(0), stop_flag(false) {
    }

    // 设置停止标志
    void setStopFlag(bool flag) {
        stop_flag = flag;
    }

    // 获取活跃读者数量
    int getActiveReaders() {
        std::lock_guard<std::mutex> lock(mtx);
        return active_readers;
    }

    // 获取等待写者数量
    int getWaitingWriters() {
        std::lock_guard<std::mutex> lock(mtx);
        return waiting_writers;
    }

    // 获取等待读者数量
    int getWaitingReaders() {
        std::lock_guard<std::mutex> lock(mtx);
        return waiting_readers;
    }

    // 开始读操作
    bool startRead() {
        std::unique_lock<std::mutex> lock(mtx);
        waiting_readers++;

        if (strategy == READER_FIRST) {
            // 读者优先：等待活跃写者完成
            while (!stop_flag && active_writers > 0) {
                read_cond.wait(lock);
            }
        }
        else if (strategy == WRITER_FIRST) {
            // 写者优先：等待活跃写者或等待中的写者
            while (!stop_flag && (active_writers > 0 || waiting_writers > 0)) {
                read_cond.wait(lock);
            }
        }

        if (stop_flag) {
            waiting_readers--;
            return false;
        }

        waiting_readers--;
        active_readers++;
        return true;
    }

    // 结束读操作
    void endRead() {
        std::unique_lock<std::mutex> lock(mtx);
        active_readers--;

        // 如果没有活跃读者，尝试唤醒写者
        if (active_readers == 0 && !stop_flag) {
            if (waiting_writers > 0) {
                write_cond.notify_one();
            }
        }
    }

    // 开始写操作
    bool startWrite() {
        std::unique_lock<std::mutex> lock(mtx);
        waiting_writers++;

        // 等待活跃读者和活跃写者完成
        while (!stop_flag && (active_readers > 0 || active_writers > 0)) {
            write_cond.wait(lock);
        }

        if (stop_flag) {
            waiting_writers--;
            return false;
        }

        waiting_writers--;
        active_writers = 1;
        return true;
    }

    // 结束写操作
    void endWrite() {
        std::unique_lock<std::mutex> lock(mtx);
        active_writers = 0;

        if (stop_flag) return;

        if (strategy == READER_FIRST) {
            // 读者优先：优先唤醒等待的读者
            if (waiting_readers > 0) {
                read_cond.notify_all();
            }
            else if (waiting_writers > 0) {
                write_cond.notify_one();
            }
        }
        else if (strategy == WRITER_FIRST) {
            // 写者优先：优先唤醒等待的写者
            if (waiting_writers > 0) {
                write_cond.notify_one();
            }
            else if (waiting_readers > 0) {
                read_cond.notify_all();
            }
        }
    }
};

// 全局输出锁，确保控制台输出不混乱
std::mutex output_mutex;

// 读者线程函数
void reader(RWProblem& rw, int id, int num_ops) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleep_dist(100, 500);

    for (int i = 0; i < num_ops; ++i) {
        // 模拟思考时间
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));

        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Reader " << id << " 尝试读取..." << std::endl;
        }

        if (!rw.startRead()) {
            {
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Reader " << id << " 接收到停止信号，提前退出" << std::endl;
            }
            return;
        }

        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Reader " << id << " 开始读取 [活跃读者: " << rw.getActiveReaders()
                << ", 等待写者: " << rw.getWaitingWriters() << "]" << std::endl;
        }

        // 模拟读取时间
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));

        rw.endRead();
        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Reader " << id << " 结束读取" << std::endl;
        }
    }
}

// 写者线程函数
void writer(RWProblem& rw, int id, int num_ops) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleep_dist(100, 500);

    for (int i = 0; i < num_ops; ++i) {
        // 模拟思考时间
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));

        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Writer " << id << " 尝试写入..." << std::endl;
        }

        if (!rw.startWrite()) {
            {
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Writer " << id << " 接收到停止信号，提前退出" << std::endl;
            }
            return;
        }

        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Writer " << id << " 开始写入 [等待读者: " << rw.getWaitingReaders()
                << ", 等待写者: " << rw.getWaitingWriters() << "]" << std::endl;
        }

        // 模拟写入时间
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));

        rw.endWrite();
        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "Writer " << id << " 结束写入" << std::endl;
        }
    }
}

// 运行测试
void run_test(int strategy) {
    const int num_readers = 3;         // 读者线程数
    const int num_writers = 2;         // 写者线程数
    const int num_operations = 5;      // 每个线程操作次数

    RWProblem rw(strategy);
    std::vector<std::thread> threads;

    // 创建读者线程
    for (int i = 0; i < num_readers; ++i) {
        threads.emplace_back(reader, std::ref(rw), i, num_operations);
    }

    // 创建写者线程
    for (int i = 0; i < num_writers; ++i) {
        threads.emplace_back(writer, std::ref(rw), i, num_operations);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
}

// 显示菜单并获取用户选择
int show_menu() {
    system("cls");
    std::cout << "===== 读者-写者问题模拟程序 =====" << std::endl;
    std::cout << "1. 读者优先策略" << std::endl;
    std::cout << "2. 写者优先策略" << std::endl;
    std::cout << "3. 退出程序" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "请选择操作 (1-3): ";

    int choice;
    std::cin >> choice;
    return choice;
}

int main() {
    while (true) {
        int choice = show_menu();

        switch (choice) {
        case 1:
            std::cout << "\n=== 开始读者优先策略测试 ===" << std::endl;
            run_test(READER_FIRST);
            break;
        case 2:
            std::cout << "\n=== 开始写者优先策略测试 ===" << std::endl;
            run_test(WRITER_FIRST);
            break;
        case 3:
            return 0;
        default:
            std::cout << "无效选择，请重新输入!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        std::cout << "\n测试完成! 按任意键返回菜单..." << std::endl;
        _getch(); // 等待用户按键
    }

    return 0;
}