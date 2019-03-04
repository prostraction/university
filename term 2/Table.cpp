#include <iostream>

class Table
{
	private:
		struct DATA
		{
			int key = 0;
			DATA* next = nullptr;
			DATA* prev = nullptr;
			bool empty = false;
		};
		DATA* head = nullptr;
		DATA* tail = nullptr;
		DATA* D = nullptr;
	public:
		void show()
		{
			if (head == nullptr || head -> empty)
			{
				std::cout << "Empty\n";
				return;
			}
			D = head;
			int i = 0;
			while (D -> next != nullptr)
			{
				std::cout << i << ": " << D->key << "\n";
				i++;
				D = D -> next;
			}
		}
		void createNode(int arg)
		{
			if (head == nullptr) return;
			D = head;
			while (D -> next != nullptr)
			{
				D = D -> next;
			}
			for (int i = 0; i < arg; i++)
			{
				D-> next = new DATA();
				D = D -> next;
			}
			tail = D;
		}
		void fill(int key)
		{
			if (head == nullptr) return;
			D = head;
			while (D)
			{
				D -> key = key;
				D = D -> next;
			}
		}
		Table()
		{
			head = new DATA();
			head -> empty = true;
		}
		Table(int arg)
		{
			head = new DATA(); 
			createNode(arg);
		}
		Table (int arg, int key)
		{
			head = new DATA();
			createNode(arg);
			fill(key);
		}
};

int main()
{
	Table T1;
	Table T2(10);
	Table T3(5, 20);
	T1.show();
	T2.show();
	T3.show();
	
	return 0;
}
