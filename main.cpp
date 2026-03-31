#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

struct NODE
{
    int data;
    NODE *prev;
    NODE *next;
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre()
{
    // Initialization - head and tail are already nullptr
    len = 0;
}

NODE* move(int i)
{
    // Move to the i-th node (0-indexed)
    if (i < 0 || i >= len) return nullptr;

    NODE *current;
    // Optimize by starting from head or tail depending on position
    if (i < len / 2) {
        current = head;
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
    } else {
        current = tail;
        for (int j = len - 1; j > i; j--) {
            current = current->prev;
        }
    }
    return current;
}

void insert(int i, int x)
{
    // Insert x at position i
    NODE *newNode = new NODE;
    newNode->data = x;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (len == 0) {
        // Empty list
        head = tail = newNode;
    } else if (i == 0) {
        // Insert at beginning
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (i == len) {
        // Insert at end
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else {
        // Insert in middle
        NODE *current = move(i);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    len++;
}

void remove(int i)
{
    // Remove node at position i
    if (i < 0 || i >= len) return;

    NODE *toDelete = move(i);

    if (len == 1) {
        // Only one node
        head = tail = nullptr;
    } else if (i == 0) {
        // Remove head
        head = head->next;
        head->prev = nullptr;
    } else if (i == len - 1) {
        // Remove tail
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        // Remove from middle
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
    }

    delete toDelete;
    len--;
}

int Get_length()
{
    return len;
}

int Query(int i)
{
    if (i < 0 || i >= len) return -1;
    NODE *current = move(i);
    return current->data;
}

void Print()
{
    if (len == 0) {
        cout << -1 << endl;
        return;
    }

    NODE *current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) cout << " ";
        current = current->next;
    }
    cout << endl;
}

void Clear()
{
    // Free all nodes to prevent memory leak
    while (head != nullptr) {
        NODE *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    len = 0;
}

}

int n;
int main()
{
    cin >> n;
    int op, x, p, ans;
    LIST::Pre();
    for (int _=0;_<n;++_)
    {
        cin >> op;
        switch(op)
        {
            case 0:
                ans = LIST::Get_length();
                cout << ans << endl;
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << endl;
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}
