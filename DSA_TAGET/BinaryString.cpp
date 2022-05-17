#include <iostream>
using namespace std;

struct node
{
	int data;
	struct node* next;
};
typedef struct node* Node;

void insertNodePoision(Node &head, int data, int vt)
{
	Node tmp = new node;
	tmp->data = data;
	tmp->next = nullptr;

	Node prv = nullptr, cur = head;
	if(!head || vt == 0)
	{
		tmp->next = head;
		head = tmp;
		return;
	}

	for(int i=0; i<vt && cur != nullptr; i++)
	{
		prv = cur;
		cur = cur->next;
	}

	prv->next = tmp;
	tmp->next = cur;
}

void printList(Node head)
{
	while(head != nullptr)
	{
		cout << head->data << " ";
		head = head->next;
	}
}

int main()
{
	Node head = nullptr;

	for(int i=0; i<=10; i++)
		insertNodePoision(head, i, i);
	insertNodePoision(head, 2002, 8);

	printList(head);
	return 0;
}