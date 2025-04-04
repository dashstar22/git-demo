#include <iostream>
#include <vector>
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

// 将生命周期状态转为字符串
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

// 客户信息结构
struct Customer {
    string id;       // 客户编号
    string name;     // 客户名称
    string contact;  // 联系方式
    string address;  // 地址
    string category; // 分类
    LifeCycleState state; // 客户生命周期状态
};

// 客户关系管理系统类
class CRMSystem {
private:
    vector<Customer> customerList; // 使用顺序表（vector）存储客户信息

public:
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
        customerList.clear();
        cout << "客户表已建立。" << endl;
    }

    // 添加客户
    void addCustomer() {
        Customer customer;
        cout << "输入客户编号: ";
        cin >> customer.id;
        cout << "输入客户名称: ";
        cin >> customer.name;
        cout << "输入联系方式: ";
        cin >> customer.contact;
        cout << "输入地址: ";
        cin >> customer.address;
        cout << "输入分类: ";
        cin >> customer.category;

        customer.state = POTENTIAL; // 默认生命周期状态为潜在客户
        customerList.push_back(customer);
        cout << "客户添加成功！当前状态为: " << lifeCycleStateToString(customer.state) << endl;
    }

    // 删除客户
    void deleteCustomer() {
        string id;
        cout << "输入要删除的客户编号: ";
        cin >> id;
        for (auto it = customerList.begin(); it != customerList.end(); ++it) {
            if (it->id == id) {
                customerList.erase(it);
                cout << "客户删除成功！" << endl;
                return;
            }
        }
        cout << "未找到该编号的客户！" << endl;
    }

    // 按编号查询客户
    void searchById() {
        string id;
        cout << "输入客户编号: ";
        cin >> id;
        for (const auto& customer : customerList) {
            if (customer.id == id) {
                displayCustomer(customer);
                return;
            }
        }
        cout << "未找到该编号的客户！" << endl;
    }

    // 按名称或分类查询客户
    void searchByNameOrCategory() {
        string keyword;
        cout << "输入客户名称或分类: ";
        cin >> keyword;
        bool found = false;
        for (const auto& customer : customerList) {
            if (customer.name == keyword || customer.category == keyword) {
                displayCustomer(customer);
                found = true;
            }
        }
        if (!found) {
            cout << "未找到匹配的客户！" << endl;
        }
    }

    // 更新客户生命周期状态
    void updateCustomerLifeCycleState() {
        string id;
        int newState;
        cout << "输入客户编号: ";
        cin >> id;

        for (auto& customer : customerList) {
            if (customer.id == id) {
                cout << "当前状态为: " << lifeCycleStateToString(customer.state) << endl;
                cout << "请选择新的状态 (0: 潜在客户, 1: 新客户, 2: 活跃客户, 3: 忠诚客户, 4: 流失客户): ";
                cin >> newState;

                if (newState >= 0 && newState <= 4) {
                    customer.state = static_cast<LifeCycleState>(newState);
                    cout << "状态更新成功！当前状态为: " << lifeCycleStateToString(customer.state) << endl;
                } else {
                    cout << "无效的状态编号！" << endl;
                }
                return;
            }
        }
        cout << "未找到该编号的客户！" << endl;
    }

    // 显示所有客户
    void displayAllCustomers() {
        if (customerList.empty()) {
            cout << "客户列表为空！" << endl;
        } else {
            for (const auto& customer : customerList) {
                displayCustomer(customer);
            }
        }
    }

    // 显示单个客户信息
    void displayCustomer(const Customer& customer) {
        cout << "编号: " << customer.id << ", 名称: " << customer.name
             << ", 联系方式: " << customer.contact << ", 地址: " << customer.address
             << ", 分类: " << customer.category
             << ", 生命周期状态: " << lifeCycleStateToString(customer.state) << endl;
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
