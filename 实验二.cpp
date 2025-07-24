#include <iostream>
#include <vector>
#include <deque>
#include <iomanip>
#include <sstream>
using namespace std;

// 页表项结构
struct PageTableEntry {
    bool present;   // 是否在内存
    int frame;      // 物理块号
    bool modified;  // 修改标志
    int disk_pos;   // 磁盘位置
};

// 指令结构
struct Instruction {
    string operation;
    int page;
    int offset;
};

// 页表
vector<PageTableEntry> initPageTable() {
    return {
        {true,  5, false, 010},  // 页0
        {true,  8, false, 012},  // 页1
        {true,  9, false, 013},  // 页2
        {true,  1, false, 021},  // 页3
        {false, -1, false, 022}, // 页4
        {false, -1, false, 023},// 页5
        {false, -1, false, 125}  // 页6
    };
}

// 输入指令序列
vector<Instruction> inputInstructions() {
    vector<Instruction> instructions;
    cout << "请输入指令序列（格式：操作 页号 偏移量，输入end结束）\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line == "end") break;

        istringstream iss(line);
        Instruction inst;
        if (iss >> inst.operation >> inst.page >> inst.offset) {
            // 输入有效性验证
            if (inst.page < 0 || inst.page >= 7) {
                cout << "错误：页号必须为0-6，跳过该指令\n";
                continue;
            }
            if (inst.offset < 0 || inst.offset >= 1024) {
                cout << "错误：偏移量必须为0-1023，跳过该指令\n";
                continue;
            }
            instructions.push_back(inst);
        }
        else {
            cout << "格式错误！示例：save 3 256\n";
        }
    }
    return instructions;
}

int main() {
    while (1) {
        // 初始化预定义页表
        auto pageTable = initPageTable();

        // 初始化FIFO队列（初始已加载页0-3）
        deque<int> fifoQueue = { 0, 1, 2, 3 };
        int pageFaults = 0;

        // 输入指令
        auto instructions = inputInstructions();

        // 处理每条指令
        for (const auto& inst : instructions) {
            int p = inst.page;
            int offset = inst.offset;
            bool isWrite = (inst.operation == "save");  // 写操作标记

            cout << "\n处理指令: " << inst.operation
                << " [页" << p << " 偏移" << offset << "]\n";

            // 检查页是否在内存
            if (pageTable[p].present) {
                // 命中处理
                int physAddr = pageTable[p].frame * 1024 + offset;
                if (isWrite) pageTable[p].modified = true;  // 写操作设置修改位
                cout << "  命中 -> 物理地址: " << physAddr
                    << " (帧" << pageTable[p].frame << ")\n";
            }
            else {
                // 缺页处理
                pageFaults++;
                int victim = fifoQueue.front();  // FIFO选择被置换页
                fifoQueue.pop_front();

                // 显示置换信息
                cout << "  缺页中断: 需要页" << p
                    << "，置换页" << victim;
                if (pageTable[victim].modified) {  // 需要写回磁盘
                    cout << " (写回磁盘位置 "
                        << setfill('0') << setw(3) << oct
                        << pageTable[victim].disk_pos << dec << ")";
                    pageTable[victim].modified = false;
                }
                cout << endl;

                // 更新页表
                pageTable[victim].present = false;
                pageTable[p].present = true;
                pageTable[p].frame = pageTable[victim].frame;  // 复用帧号
                pageTable[p].modified = false;  // 新页初始未修改
                fifoQueue.push_back(p);  // 新页加入队列尾部

                // 处理当前访问
                int physAddr = pageTable[p].frame * 1024 + offset;
                if (isWrite) pageTable[p].modified = true;
                cout << "  新物理地址: " << physAddr
                    << " (页" << p << "装入帧"
                    << pageTable[p].frame << ")\n";
            }
        }

        cout << "\n总缺页次数: " << pageFaults << endl;
        cout << "是否继续运行（y/n）:";
        char flag = '1';
        while (true) {
            cin >> flag;
            if (flag == 'y' || flag == 'Y' || flag == 'n' || flag == 'N') {
                break;
            }
            cout << "输入错误，请重新输入" << endl;
        }
        if (flag == 'y' || flag == 'Y') {
            continue;
        }else{
            break;
        }
    }
    return 0;
}