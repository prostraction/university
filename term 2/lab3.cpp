#include <iostream>

class String
{
private:
    struct Symbol
    {
        char data;
        Symbol* next;
        Symbol(char CH)
        {
            data = CH;
        }
    };
    Symbol* head;
public:
    String()
    {
        head = nullptr;
    }
    String(char* income)
    {
        if (income[0] == '\0') return;
        head = new Symbol(income[0]);
        Symbol* S = head;
        for (int i = 1; income[i] != '\0'; i++)
        {
            S->next = new Symbol(income[i]);
            S = S->next;
            S->next = nullptr;
        }
        S = nullptr; delete S;
    }
    void add(char* income)
    {
        Symbol* S = head; int i = 0;
        if ( !head ) { S = new Symbol(income[0]); i++; }
        while ( S->next )
        {
            S = S->next;
        }
        for (; income[i] != '\0'; i++)
        {
            S->next = new Symbol(income[i]);
            S = S->next;
            S->next = nullptr;
        }
        S = nullptr; delete S;

    }
    void show()
    {
        if ( head )
        {
            Symbol* S = head;
            while ( S )
            {
                std::cout << S->data;
                S = S->next;
            }
            std::cout << std::endl;
            S = nullptr; delete S;
        }
    }
    bool isEmpty()
    {
        return ( head ) ? false : true;
    }
    void plus(String S1, String S2)
    {
        Symbol* S = S1.head;
        while ( S->next )
        {
            S = S->next;
        }
        S->next = S2.head;
        S = nullptr; delete S;
    }
};


int main()
{
    String S("STRING is going on");
    S.show();
    S.add(" and another one");
    S.show();
    String S1(" AMD ANOTHER ONE OH MY GOD TRIBLE KILL");
    S.plus(S, S1);
    S.show();
    return 0;
}
