class String
{
private:
    int length = 0;
    struct DATA
    {
        int length = 0;
        char* word = nullptr;
        DATA* next = nullptr;
        DATA* prev = nullptr;
    };
    DATA* head = nullptr;
public:
    String ()
    {
        head = new DATA();
    }
    String (char* data)
    {
        head = new DATA();
        add(data);
    }
    void add(char* data)
    {
        if (head == nullptr) return;
        DATA* D = head;
        while (D->next != nullptr)
            D = D->next;
        int i = 0;
        int counter = 0;
        while (i <= strlen(data))
        {
            if (data[i] == ' ' || data[i] == '\0')
            {
                D->word = new char[counter+1];
                for (int i = 0; i < counter; i++)
                    D->word[i] = ' ';
                D->word[counter] = '\0';
                int j = 0;
                for (int k = i - counter; k < i; k++)
                {
                    D->word[j] = data[k]; j++;
                }
                D->length = counter;
		length = length + D->length + 1;
                D->next = new DATA();
                D->next->prev = D;
                D = D->next;
                counter = -1;
            }
            counter++; i++;
        }
	length--;
    }
    void show()
    {
        DATA* D = head;
        while (D && D->word != nullptr)
        {
        std::cout << D->word;
            std::cout << " ";
            D = D->next;
        }
        delete D;
    }
    void user_defined()
    {
        char CH;
        char* bufer = new char[100];
        int i = 0;
        do
        {
            CH = std::cin.get();
            bufer[i] = CH;
            if (CH == ' ' || CH == '\n')
            {
                char* result = new char[i+1];
                for (int k = 0; k < i; k++)
                    result[k] = bufer[k];
                result[i] = '\0';
                add(result);
                i = -1;
                for (int k = 0; k < i; k++)
                    bufer[k] = ' ';
            }
            i++;
        } while (CH != '\n');
        delete[] bufer;
    }

    void del(DATA* D)
    {
        if (D->next != nullptr)
        {
            D->prev->next = D->next;
            D->next->prev = D->prev;
        }
        else
        {
            D->prev->next = nullptr;
        }
        delete[] D->word;
        delete D;
    }

    void del_per_num(int num)
    {
        num--;
        DATA* D = head;
        if (!head) return;
        for (int i = 0; i < num; i++)
        {
            D = D->next;
            if (!D) {std::cout << "No valid element\n"; return;}
        }
        del(D);
    }
    void del_per_word(char* search_word)
    {
        DATA* D = head;
        if (!D) return;
        while (D->next != nullptr)
        {
            if (strcmp(D->word,search_word) == 0) {del(D); return;}
            D = D->next;
        }
        std::cout << "No valid element\n";
        delete D;
    }

};
