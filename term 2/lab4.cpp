#include <iostream>

class Deck
{
    struct element
    {
        int* data;
        element* next;
        element* prev;
        element(int d)
        { data = new int(d); }
        element() {}
    };
    element* head;
    element* tail;
    element* E;
public:
    Deck()
    {
        head = nullptr;
    }
    Deck(int d)
    {
        head = new element(d);
        tail = head;
        head->prev = nullptr;
        tail->next = nullptr;
    }
    void pushBack(int d)
    {
        if (head == nullptr)
        {
           head = new element(d); tail = head;
        }
        else
        {
            E = tail;
            E->next = new element(d);
            E->next->prev = E;
            tail = E->next;
            tail->next = nullptr;
         }
    }
    void pushForw(int d)
    {
        if (head == nullptr)
        {
            head = new element(d); tail = head;
        }
        else
        {
            E = nullptr;
            E = new element(d);
            E->next = head;
            head->prev = E;
            head = E;
        }
    }
    bool isEmpty()
    {
        return (head == nullptr) ? true : false;
    }
    element* getLast()
    {
        return tail;
    }
    element* getFirst()
    {
        return head;
    }
};


int main()
{
    Deck D_empty;
    std::cout << "D is empty? " << D_empty.isEmpty() << std::endl;
    Deck D;
    for (int i = 1; i <= 5; i++) 
        D.pushBack(i);
    D.pushForw(0);
    std::cout << *D.getFirst()->data << " -- " << *D.getLast()->data << std::endl;
    return 0;
}
