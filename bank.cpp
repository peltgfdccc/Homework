#include <iostream>
#include <vector>
using namespace std;

const int N = 5; // 进程数
const int M = 3; // 资源类型数

class Banker {
private:
    int available[M];         // 可用资源
    int max_demand[N][M];     // 最大需求
    int allocation[N][M];     // 已分配资源
    int need[N][M];           // 需求矩阵
    bool finish[N];           // 完成标记

public:
    Banker() {
        // 最大需求矩阵
        int _max[N][M] = {
            {7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}
        };
        
        // 已分配矩阵
        int _alloc[N][M] = {
            {0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}
        };

        // 计算初始可用资源
        int total[M] = {10,5,7};
        int used[M] = {0};
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                used[j] += _alloc[i][j];
        
        for(int j=0; j<M; j++)
            available[j] = total[j] - used[j];

        // 初始化矩阵
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                max_demand[i][j] = _max[i][j];
                allocation[i][j] = _alloc[i][j];
                need[i][j] = max_demand[i][j] - allocation[i][j];
            }
        }
    }

    bool request_resources(int pid, int request[M]) {
        // 检查请求是否超过需求
        for(int j=0; j<M; j++)
            if(request[j] > need[pid][j]) {
                cout << "请求超过进程需求！" << endl;
                return false;
            }

        // 检查可用资源是否足够
        for(int j=0; j<M; j++)
            if(request[j] > available[j]) {
                cout <<"资源不足"<< endl;
                return false;
            }

        // 尝试分配资源
        for(int j=0; j<M; j++) {
            available[j] -= request[j];
            allocation[pid][j] += request[j];
            need[pid][j] -= request[j];
        }

        // 安全检查
        if(!check_safety()) {
            // 回滚分配
            for(int j=0; j<M; j++) {
                available[j] += request[j];
                allocation[pid][j] -= request[j];
                need[pid][j] += request[j];
            }
            cout << "不安全，拒绝分配" << endl;
            return false;
        }
        return true;
    }

    bool check_safety() {
        vector<int> safe_seq;
        int work[M];
        copy(available, available+M, work);
        fill(finish, finish+N, false);

        bool found;
        for(int k=0; k<N; k++) {
            found = false;
            for(int i=0; i<N; i++) {
                if(!finish[i]) {
                    bool can_alloc = true;
                    for(int j=0; j<M; j++)
                        if(need[i][j] > work[j]) {
                            can_alloc = false;
                            break;
                        }
                    
                    if(can_alloc) {
                        for(int j=0; j<M; j++)
                            work[j] += allocation[i][j];
                        finish[i] = true;
                        safe_seq.push_back(i);
                        found = true;
                        break;
                    }
                }
            }
            if(!found) break;
        }

        if(safe_seq.size() == N) {
            cout <<"安全序列:";
            for(size_t i=0; i<safe_seq.size(); i++) 
				cout << "P" << safe_seq[i] << " ";
            cout << endl;
            return true;
        }
        return false;
    }

    void print_status() {
        cout << "\n当前系统状态：\n";
        cout << "进程\t最大需求\t已分配\t需求\n";
        for(int i=0; i<N; i++) {
            cout << "P" << i << "\t";
            for(int j=0; j<M; j++) cout << max_demand[i][j] << " ";
            cout << "\t\t";
            for(int j=0; j<M; j++) cout << allocation[i][j] << " ";
            cout << "\t";
            for(int j=0; j<M; j++) cout << need[i][j] << " ";
            cout << endl;
        }
        cout << "可用资源:";
        for(int j=0; j<M; j++) cout << available[j] << " ";
        cout << endl;
    }
};

int main() {
    Banker banker;
    banker.print_status();
    
    // 初始安全检查
    cout << "\n初始安全检查：";
    if(banker.check_safety()) cout << "系统安全!" << endl;
    else cout << "系统不安全！" << endl;

    // 示例请求处理
    int req1[M] = {1,0,2};
    cout << "\n处理P1请求(1,0,2):" << endl;
    if(banker.request_resources(1, req1)) {
        cout << "分配成功!" << endl;
        banker.print_status();
    }

    // 多次分配循环
    char choice='y';
    while(choice == 'y' || choice == 'Y'){
        int pid, req[M];
        cout << "\n输入请求(进程号 资源A B C):";
        cin >> pid >> req[0] >> req[1] >> req[2];
        
        if(pid <0 || pid >=N) {
            cout << "无效进程号!" << endl;
			cin.clear();          // 清空
            cin.ignore(1024, '\n'); // 清空缓冲区
            continue;
        }
        
        if(banker.request_resources(pid, req)) {
            cout << "分配成功!" << endl;
            banker.print_status();
        }
        
        cout << "继续分配？(y/n): ";
		cin.clear();          // 清空
        cin.ignore(1024, '\n'); // 清空缓冲区
        cin>>choice;
    }
	cout << "再见！ "<<endl;

    return 0;
}