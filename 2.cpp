#include <iostream>
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

// ����������״̬ת��Ϊ�ַ���
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

// �ͻ��ڵ�ṹ
struct Customer {
    string id;             // �ͻ����
    string name;           // �ͻ�����
    string contact;        // ��ϵ��ʽ
    string address;        // ��ַ
    string category;       // ����
    LifeCycleState state;  // �ͻ���������״̬
    Customer* next;        // ָ����һ���ͻ���ָ��
};

// �ͻ���ϵ����ϵͳ��
class CRMSystem {
private:
    Customer* head; // �����ͷ�ڵ�

public:
    CRMSystem() : head(nullptr) {}

    ~CRMSystem() {
        clearCustomerList();
    }

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
        clearCustomerList();
        cout << "�ͻ����ѳɹ�������" << endl;
    }

    // ��տͻ��б�
    void clearCustomerList() {
        while (head) {
            Customer* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    // ��ӿͻ�
    void addCustomer() {
        Customer* newCustomer = new Customer();
        cout << "����ͻ����: ";
        cin >> newCustomer->id;
        cout << "����ͻ�����: ";
        cin >> newCustomer->name;
        cout << "������ϵ��ʽ: ";
        cin >> newCustomer->contact;
        cout << "�����ַ: ";
        cin >> newCustomer->address;
        cout << "�������: ";
        cin >> newCustomer->category;
        newCustomer->state = POTENTIAL; // Ĭ��״̬ΪǱ�ڿͻ�
        newCustomer->next = head;
        head = newCustomer;
        cout << "�ͻ���ӳɹ�����ǰ״̬Ϊ: " << lifeCycleStateToString(newCustomer->state) << endl;
    }

    // ɾ���ͻ�
    void deleteCustomer() {
        string id;
        cout << "����Ҫɾ���Ŀͻ����: ";
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
                cout << "�ͻ�ɾ���ɹ���" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "δ�ҵ��ñ�ŵĿͻ���" << endl;
    }

    // ����Ų�ѯ�ͻ�
    void searchById() {
        string id;
        cout << "����ͻ����: ";
        cin >> id;

        Customer* curr = head;
        while (curr) {
            if (curr->id == id) {
                displayCustomer(curr);
                return;
            }
            curr = curr->next;
        }
        cout << "δ�ҵ��ñ�ŵĿͻ���" << endl;
    }

    // �����ƻ�����ѯ�ͻ�
    void searchByNameOrCategory() {
        string keyword;
        cout << "����ͻ����ƻ����: ";
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
            cout << "δ�ҵ�ƥ��Ŀͻ���" << endl;
        }
    }

    // ���¿ͻ���������״̬
    void updateCustomerLifeCycleState() {
        string id;
        cout << "����ͻ����: ";
        cin >> id;

        Customer* curr = head;
        while (curr) {
            if (curr->id == id) {
                int newState;
                cout << "��ǰ״̬Ϊ: " << lifeCycleStateToString(curr->state) << endl;
                cout << "��ѡ���µ�״̬ (0: Ǳ�ڿͻ�, 1: �¿ͻ�, 2: ��Ծ�ͻ�, 3: �ҳϿͻ�, 4: ��ʧ�ͻ�): ";
                cin >> newState;

                if (newState >= 0 && newState <= 4) {
                    curr->state = static_cast<LifeCycleState>(newState);
                    cout << "״̬���³ɹ�����ǰ״̬Ϊ: " << lifeCycleStateToString(curr->state) << endl;
                } else {
                    cout << "��Ч��״̬��ţ�" << endl;
                }
                return;
            }
            curr = curr->next;
        }
        cout << "δ�ҵ��ñ�ŵĿͻ���" << endl;
    }

    // ��ʾ���пͻ�
    void displayAllCustomers() {
        if (!head) {
            cout << "�ͻ��б�Ϊ�գ�" << endl;
            return;
        }

        Customer* curr = head;
        while (curr) {
            displayCustomer(curr);
            curr = curr->next;
        }
    }

    // ��ʾ�����ͻ���Ϣ
    void displayCustomer(Customer* customer) {
        cout << "���: " << customer->id << ", ����: " << customer->name
             << ", ��ϵ��ʽ: " << customer->contact << ", ��ַ: " << customer->address
             << ", ����: " << customer->category
             << ", ��������״̬: " << lifeCycleStateToString(customer->state) << endl;
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
