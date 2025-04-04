#include <iostream>
#include <vector>
#include <string>

using namespace std;

// �ͻ���������״̬
enum LifeCycleState {
    POTENTIAL, // Ǳ�ڿͻ�
    NEW,       // �¿ͻ�
    ACTIVE,    // ��Ծ�ͻ�
    LOYAL,     // �ҳϿͻ�
    LOST       // ��ʧ�ͻ�
};

// ����������״̬תΪ�ַ���
string lifeCycleStateToString(LifeCycleState state) {
    switch (state) {
        case POTENTIAL: return "Ǳ�ڿͻ�";
        case NEW: return "�¿ͻ�";
        case ACTIVE: return "��Ծ�ͻ�";
        case LOYAL: return "�ҳϿͻ�";
        case LOST: return "��ʧ�ͻ�";
        default: return "δ֪״̬";
    }
}

// �ͻ���Ϣ�ṹ
struct Customer {
    string id;       // �ͻ����
    string name;     // �ͻ�����
    string contact;  // ��ϵ��ʽ
    string address;  // ��ַ
    string category; // ����
    LifeCycleState state; // �ͻ���������״̬
};

// �ͻ���ϵ����ϵͳ��
class CRMSystem {
private:
    vector<Customer> customerList; // ʹ��˳���vector���洢�ͻ���Ϣ

public:
    // ������
    void showMenu() {
        cout << "=================== �ͻ���ϵ����ϵͳ ===================" << endl;
        cout << "1. �����ͻ���" << endl;
        cout << "2. ��ӿͻ�" << endl;
        cout << "3. ɾ���ͻ�" << endl;
        cout << "4. ����Ų�ѯ�ͻ�" << endl;
        cout << "5. �����ƻ�����ѯ�ͻ�" << endl;
        cout << "6. ���¿ͻ���������״̬" << endl;
        cout << "7. ��ʾ���пͻ�" << endl;
        cout << "0. �˳�ϵͳ" << endl;
        cout << "======================================================" << endl;
    }

    // �����ͻ���
    void createCustomerList() {
        customerList.clear();
        cout << "�ͻ����ѽ�����" << endl;
    }

    // ��ӿͻ�
    void addCustomer() {
        Customer customer;
        cout << "����ͻ����: ";
        cin >> customer.id;
        cout << "����ͻ�����: ";
        cin >> customer.name;
        cout << "������ϵ��ʽ: ";
        cin >> customer.contact;
        cout << "�����ַ: ";
        cin >> customer.address;
        cout << "�������: ";
        cin >> customer.category;

        customer.state = POTENTIAL; // Ĭ����������״̬ΪǱ�ڿͻ�
        customerList.push_back(customer);
        cout << "�ͻ���ӳɹ�����ǰ״̬Ϊ: " << lifeCycleStateToString(customer.state) << endl;
    }

    // ɾ���ͻ�
    void deleteCustomer() {
        string id;
        cout << "����Ҫɾ���Ŀͻ����: ";
        cin >> id;
        for (auto it = customerList.begin(); it != customerList.end(); ++it) {
            if (it->id == id) {
                customerList.erase(it);
                cout << "�ͻ�ɾ���ɹ���" << endl;
                return;
            }
        }
        cout << "δ�ҵ��ñ�ŵĿͻ���" << endl;
    }

    // ����Ų�ѯ�ͻ�
    void searchById() {
        string id;
        cout << "����ͻ����: ";
        cin >> id;
        for (const auto& customer : customerList) {
            if (customer.id == id) {
                displayCustomer(customer);
                return;
            }
        }
        cout << "δ�ҵ��ñ�ŵĿͻ���" << endl;
    }

    // �����ƻ�����ѯ�ͻ�
    void searchByNameOrCategory() {
        string keyword;
        cout << "����ͻ����ƻ����: ";
        cin >> keyword;
        bool found = false;
        for (const auto& customer : customerList) {
            if (customer.name == keyword || customer.category == keyword) {
                displayCustomer(customer);
                found = true;
            }
        }
        if (!found) {
            cout << "δ�ҵ�ƥ��Ŀͻ���" << endl;
        }
    }

    // ���¿ͻ���������״̬
    void updateCustomerLifeCycleState() {
        string id;
        int newState;
        cout << "����ͻ����: ";
        cin >> id;

        for (auto& customer : customerList) {
            if (customer.id == id) {
                cout << "��ǰ״̬Ϊ: " << lifeCycleStateToString(customer.state) << endl;
                cout << "��ѡ���µ�״̬ (0: Ǳ�ڿͻ�, 1: �¿ͻ�, 2: ��Ծ�ͻ�, 3: �ҳϿͻ�, 4: ��ʧ�ͻ�): ";
                cin >> newState;

                if (newState >= 0 && newState <= 4) {
                    customer.state = static_cast<LifeCycleState>(newState);
                    cout << "״̬���³ɹ�����ǰ״̬Ϊ: " << lifeCycleStateToString(customer.state) << endl;
                } else {
                    cout << "��Ч��״̬��ţ�" << endl;
                }
                return;
            }
        }
        cout << "δ�ҵ��ñ�ŵĿͻ���" << endl;
    }

    // ��ʾ���пͻ�
    void displayAllCustomers() {
        if (customerList.empty()) {
            cout << "�ͻ��б�Ϊ�գ�" << endl;
        } else {
            for (const auto& customer : customerList) {
                displayCustomer(customer);
            }
        }
    }

    // ��ʾ�����ͻ���Ϣ
    void displayCustomer(const Customer& customer) {
        cout << "���: " << customer.id << ", ����: " << customer.name
             << ", ��ϵ��ʽ: " << customer.contact << ", ��ַ: " << customer.address
             << ", ����: " << customer.category
             << ", ��������״̬: " << lifeCycleStateToString(customer.state) << endl;
    }

    // ϵͳ����
    void run() {
        int choice;
        do {
            showMenu();
            cout << "��ѡ����: ";
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
                    cout << "�˳�ϵͳ��" << endl;
                    break;
                default:
                    cout << "��Ч��ѡ�������ѡ��" << endl;
            }
        } while (choice != 0);
    }
};

int main() {
    CRMSystem system;
    system.run();
    return 0;
}
