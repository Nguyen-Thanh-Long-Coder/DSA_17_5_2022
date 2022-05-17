#include <bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	struct node* next;
};
typedef struct node* Node;

void insertNodePosition(Node &head, int data, int vt)
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

void deleteNodeByData(Node &head, int data)
{
	if(head == nullptr)
		return;
	if(head->data == data)
	{
		Node x = head;
		head = head->next;
		delete x;
	}
	else
		deleteNodeByData(head->next, data);
}

void deleteNodeByPosition(Node &head, int vt)
{
	if(head == nullptr)
		return;

	if(vt == 0)
	{
		Node x = head;
		head = head->next;
		delete x;
	}
	else
	{
		Node prv = nullptr;
		Node cur = head;
		for(int i=0; i<vt && cur != nullptr; i++)
		{
			prv = cur;
			cur = cur->next;
		}

		if(cur != nullptr)
		{
			prv->next = cur->next;
			delete cur;
		}
	}
}

void deleteLinkedList(Node &head)
{
	Node tmp = nullptr;
	while(head != nullptr)
	{
		tmp = head;
		head = head->next;
		delete tmp;
		tmp = head;
	}
}

void printList(Node head)
{
	while(head != nullptr)
	{
		cout << head->data << " ";
		head = head->next;
	}
}

int countLengthLL(Node head)
{
	if(head == nullptr)
		return 0;
	return countLengthLL(head->next) + 1;
	deleteLinkedList(head);
}

Node searchNode(Node head, int data)
{
	if(head == nullptr)
		return head;

	if(head->data != data)
		return searchNode(head->next, data);

	return head;
	// while(head != nullptr && head->data != data)
	// 	head = head->next;
	// return head;
}

int returnIndexDataLL(Node head, int index)
{
	// for(int i=0; i<index && head != nullptr; i++)
	// 	head = head->next;
	// if(head)
	// 	return head->data;
	// return -1;

	if(head == nullptr)
		return -1;
	if(index == 0)
		return head->data;
	return returnIndexDataLL(head->next, index - 1);
}

int main()
{
	srand(time(NULL));
	Node head = nullptr;

	for(int i=0; i<=10; i++)
		insertNodePosition(head, rand() % (20 - 10 + 1) + 10, i);

	int index; cin >> index;
	cout << returnIndexDataLL(head, index) << endl;

	printList(head);
	deleteLinkedList(head);

	return 0;
}