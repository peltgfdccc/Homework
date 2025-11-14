#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void sstf_disk_scheduling(int initial_pos, vector<int> requests) {
    int current = initial_pos;
    int total_seek = 0;
    vector<int> sequence;

    cout << "\n初始磁头位置: " << current << endl;
    cout << "处理顺序：" << endl;

    while (!requests.empty()) {
        int min_dist = INT_MAX;
        int selected = -1;
        int index = -1;

        // 查找距离当前磁头最近的磁道
        for (int i = 0; i < requests.size(); ++i) {
            int dist = abs(current - requests[i]);
            if (dist < min_dist) {
                min_dist = dist;
                selected = requests[i];
                index = i;
            }
        }

        // 更新统计信息
        total_seek += min_dist;
        sequence.push_back(selected);
        current = selected;
        requests.erase(requests.begin() + index);

        // 输出当前移动信息
        cout << "移动到磁道 " << selected << "，寻道长度 " << min_dist << endl;
    }

    // 输出最终结果
    cout << "\n总寻道长度: " << total_seek << endl;
    cout << "平均寻道长度: " << (double)total_seek / sequence.size() << endl;
}

int main() {
    vector<int> requests;
    int initial_position, n;

    // 输入初始磁头位置
    cout << "请输入初始磁头位置: ";
    cin >> initial_position;

    // 输入请求数量
    cout << "请输入磁道请求的数量: ";
    cin >> n;

    // 输入磁道号
    cout << "请依次输入" << n << "个磁道号:" << endl;
    for (int i = 0; i < n; ++i) {
        int track;
        cin >> track;
        requests.push_back(track);
    }

    // 执行调度算法
    sstf_disk_scheduling(initial_position, requests);
    return 0;
}