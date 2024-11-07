#include <iostream>
using namespace std;

struct Node {
    int data;
    int exp;
    Node* next;
};

struct List {
    Node* firstNode = nullptr;
};

void List_Init(List& list) {
    list.firstNode = nullptr;
}

void List_InsertAfter(List& list, int data, int exp) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->exp = exp;
    newNode->next = nullptr;

    if (list.firstNode == nullptr) {
        list.firstNode = newNode;
        return;
    }

    Node* temp = list.firstNode;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    
    temp->next = newNode;
}

void PrintList(const List& list) {
    Node* temp = list.firstNode;
    while (temp != nullptr) {
        cout << temp->data << ".x^" << temp->exp;
        temp = temp->next;
        if (temp != nullptr) cout << " + ";
    }
    cout << endl;
}

List pluslist(List& list1, List& list2) {
    List result;
    List_Init(result);

    Node** lastPtr = &result.firstNode;
    Node* temp1 = list1.firstNode;
    Node* temp2 = list2.firstNode;

    while (temp1 != nullptr || temp2 != nullptr) {
        if (temp1 != nullptr && (temp2 == nullptr || temp1->exp > temp2->exp)) {
            *lastPtr = temp1;
            temp1 = temp1->next;
        }
        else if (temp2 != nullptr && (temp1 == nullptr || temp2->exp > temp1->exp)) {
            *lastPtr = temp2;
            temp2 = temp2->next;
        }
        else if (temp1 != nullptr && temp2 != nullptr && temp1->exp == temp2->exp) {
            temp1->data += temp2->data;
            if (temp1->data != 0) {
                *lastPtr = temp1;
                lastPtr = &((*lastPtr)->next);
            }
            Node* toDelete = temp2;
            temp1 = temp1->next;
            temp2 = temp2->next;
            delete toDelete;
            continue;
        }
        lastPtr = &((*lastPtr)->next);
    }

    *lastPtr = nullptr;
    list1.firstNode = nullptr;
    list2.firstNode = nullptr;

    return result;
}

int main() {
    List list1, list2;
    List_Init(list1);
    List_Init(list2);

    int n, c, e;

    cout << "So luong phan tu da thuc 1: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "He so phan tu thu " << i + 1 << ": ";
        cin >> c >> e;
        List_InsertAfter(list1, c, e);
    }

    cout << "So luong phan tu da thuc 2: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "He so phan tu thu " << i + 1 << ": ";
        cin >> c >> e;
        List_InsertAfter(list2, c, e);
    }

    List result = pluslist(list1, list2);

    cout << "F(x) = ";
    PrintList(list1);
    cout << "G(x) = ";
    PrintList(list2);
    cout << "H(x) = ";
    PrintList(result);

    return 0;
}
