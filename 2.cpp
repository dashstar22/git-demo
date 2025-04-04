#include <iostream>
#include <string>

using namespace std;

// 客户生命周期状态
enum LifeCycleState {
    POTENTIAL, // 潜在客户
    NEW,       // 新客户
    ACTIVE,    // 活跃客户
    LOYAL,     // 忠诚客户
    LOST       // 流失客户
};

// 将生命周期状态转换为字符串
string lifeCycleStateToString(LifeCycleState state) {
    switch (state) {
        case POTENTIAL: return "潜在客户";
        case NEW: return "新客户";
        case ACTIVE: return "活跃客户";
        case LOYAL: return "忠诚客户";
        case LOST: return "流失客户";
        default: return "未知状态";
    }
}

// 客户节点结构
struct Customer {
    string id;             // 客户编号
    string name;           // 客户名称
    string contact;        // 联系方式
    string address;        // 地址
    string category;       // 分类
    LifeCycleState state;  // 客户生命周期状态
    Customer* next;        // 指向下一个客户的指针
};

// 客户关系管理系统类
class CRMSystem {
private:
    Customer* head; // 链表的头节点

public:
    CRMSystem() : head(nullptr) {}

    ~CRMSystem() {
        clearCustomerList();
    }

    // 主界面
    void showMenu() {
        cout << "=================== 客户关系管理系统 ===================" << endl;
        cout << "1. 建立客户表" << endl;
        cout << "2. 添加客户" << endl;
        cout << "3. 删除客户" << endl;
        cout << "4. 按编号查询客户" << endl;
        cout << "5. 按名称或分类查询客户" << endl;
        cout << "6. 更新客户生命周期状态" << endl;
        cout << "7. 显示所有客户" << endl;
        cout << "0. 退出系统" << endl;
        cout << "======================================================" << endl;
    }

    // 建立客户表
    void createCustomerList() {
        clearCustomerList();
        cout << "客户表已成功建立。" << endl;
    }

    // 清空客户列表
    void clearCustomerList() {
        while (head) {
            Customer* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    // 添加客户
    void addCustomer() {
        Customer* newCustomer = new Customer();
        cout << "输入客户编号: ";
        cin >> newCustomer->id;
        cout << "输入客户名称: ";
        cin >> newCustomer->name;
        cout << "输入联系方式: ";
        cin >> newCustomer->contact;
        cout << "输入地址: ";
        cin >> newCustomer->address;
        cout << "输入分类: ";
        cin >> newCustomer->category;
        newCustomer->state = POTENTIAL; // 默认状态为潜在客户
        newCustomer->next = head;
        head = newCustomer;
        cout << "客户添加成功！当前状态为: " << lifeCycleStateToString(newCustomer->state) << endl;
    }

    // 删除客户
    void deleteCustomer() {
        string id;
        cout << "输入要删除的客户编号: ";
        cin >> id;

        Customer* prev = nullptr;
        Customer* curr = head;

        while (curr) {
            if (curr->id == id) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                delete curr;
                cout << "客户删除成功！" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "未找到该编号的客户！" << endl;
    }

    // 按编号查询客户
    void searchById() {
        string id;
        cout << "输入客户编号: ";
        cin >> id;

        Customer* curr = head;
        while (curr) {
            if (curr->id == id) {
                displayCustomer(curr);
                return;
            }
            curr = curr->next;
        }
        cout << "未找到该编号的客户！" << endl;
    }

    // 按名称或分类查询客户
    void searchByNameOrCategory() {
        string keyword;
        cout << "输入客户名称或分类: ";
        cin >> keyword;

        bool found = false;
        Customer* curr = head;
        while (curr) {
            if (curr->name == keyword || curr->category == keyword) {
                displayCustomer(curr);
                found = true;
            }
            curr = curr->next;
        }

        if (!found) {
            cout << "未找到匹配的客户！" << endl;
        }
    }

    // 更新客户生命周期状态
    void updateCustomerLifeCycleState() {
        string id;
        cout << "输入客户编号: ";
        cin >> id;

        Customer* curr = head;
        while (curr) {
            if (curr->id == id) {
                int newState;
                cout << "当前状态为: " << lifeCycleStateToString(curr->state) << endl;
                cout << "请选择新的状态 (0: 潜在客户, 1: 新客户, 2: 活跃客户, 3: 忠诚客户, 4: 流失客户): ";
                cin >> newState;

                if (newState >= 0 && newState <= 4) {
                    curr->state = static_cast<LifeCycleState>(newState);
                    cout << "状态更新成功！当前状态为: " << lifeCycleStateToString(curr->state) << endl;
                } else {
                    cout << "无效的状态编号！" << endl;
                }
                return;
            }
            curr = curr->next;
        }
        cout << "未找到该编号的客户！" << endl;
    }

    // 显示所有客户
    void displayAllCustomers() {
        if (!head) {
            cout << "客户列表为空！" << endl;
            return;
        }

        Customer* curr = head;
        while (curr) {
            displayCustomer(curr);
            curr = curr->next;
        }
    }

    // 显示单个客户信息
    void displayCustomer(Customer* customer) {
        cout << "编号: " << customer->id << ", 名称: " << customer->name
             << ", 联系方式: " << customer->contact << ", 地址: " << customer->address
             << ", 分类: " << customer->category
             << ", 生命周期状态: " << lifeCycleStateToString(customer->state) << endl;
    }

    // 系统运行
    void run() {
        int choice;
        do {
            showMenu();
            cout << "请选择功能: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    createCustomerList();
                    break;
                case 2:
                    addCustomer();
                    break;
                case 3:
                    deleteCustomer();
                    break;
                case 4:
                    searchById();
                    break;
                case 5:
                    searchByNameOrCategory();
                    break;
                case 6:
                    updateCustomerLifeCycleState();
                    break;
                case 7:
                    displayAllCustomers();
                    break;
                case 0:
                    cout << "退出系统。" << endl;
                    break;
                default:
                    cout << "无效的选项，请重新选择！" << endl;
            }
        } while (choice != 0);
    }
};

int main() {
    CRMSystem system;
    system.run();
    return 0;
}
