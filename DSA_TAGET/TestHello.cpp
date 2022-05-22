#include <bits/stdc++.h>
using namespace std;
int i = 0;

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

Node returnNodeMid(Node head)
{
	if(head == nullptr)
		return head;
	Node oddNode = head;
	int count = 0;

	while(head != nullptr)
	{
		if(count % 2 && head->next != nullptr)
			oddNode = oddNode->next;
		head = head->next;
		count++;
	}
	return oddNode;
}

void returnIndexForEnd(Node head, int n)
{
	Node fast = head, low = head;
	while(n && fast != nullptr)
	{
		fast = fast->next;
		n--;
	}

	if(n != 0)
		cout << "Cant print" << endl;
	else
	{
		while(fast != nullptr)
		{
			fast = fast->next;
			low = low->next;
		}
		printList(low);
	}
}	

bool detectLoopLL(Node head)
{
	Node low, fast;
	low = head;
	fast = head->next;

	while(fast != nullptr && fast->next != nullptr)
	{
		if(low == fast)
			return true;
		fast = fast->next->next;
		low = low->next;
	}
	return false;
}

Node reverLL(Node head)
{
	if(!head || !head->next)
		return head;

	Node prv, cur, next;
	cur = head->next;
	prv = head;
	head->next = nullptr;

	while(cur)
	{
		next = cur->next;
		cur->next = prv;
		prv = cur;
		cur = next;
	}

	head = prv;
	return head;
}

bool isPalindromeLL2(Node head)
{
	if(head == nullptr)
		return true;

	Node fast, mid, prv, rec = nullptr;
	fast = mid = head;
	while(fast != nullptr && fast->next != nullptr)
	{
		fast = fast->next->next;
		prv = mid;
		mid = mid->next;
	}

	if(fast != nullptr)
	{
		rec = mid;
		mid = mid->next;
	}
	
	prv->next = nullptr;
	Node rev = reverLL(mid);
	Node tmp = rev;
	bool check = true;

	while(rev != nullptr)
	{
		if(rev->data != head->data)
		{
			check = false;
			break;
		}
		rev = rev->next;
		head = head->next;
	}

	tmp = reverLL(tmp);
	if(rec)
	{
		prv->next = rec;
		rec->next = tmp;
	}
	else
		prv->next = tmp;

	return check;
}

bool isPalindromeLL(Node &head, Node recur)
{
	if(recur == nullptr)
		return true;
	bool isp = isPalindromeLL(head, recur->next);

	if(isp == false)
		return false;

	isp = (head->data == recur->data);
	head = head->next;
	return isp; 
}

Node removeDuplicates(Node head)
{
	// if(head == nullptr)
	// 	return;

	// while(head->next != nullptr)
	// {
	// 	Node nextH = head->next;
	// 	if(head->data == nextH->data)
	// 	{
	// 		head->next = nextH->next;
	// 		delete nextH;
	// 	}
	// 	else
	// 		head = head->next;
	// }
	if(head == nullptr || head->next == nullptr)
		return head;
	Node tmp = removeDuplicates(head->next);
	if(head->data == tmp->data)
	{
		head->next = tmp->next;
		delete tmp;
	}
	return head;
}

Node removeDuplicatesNotSort(Node head)
{
	Node returNode = head;
	while(head)
	{
		Node prv = head;
		Node run = head->next;
		while(run)
		{
			if(run->data == head->data)
			{
				prv->next = run->next;
				delete run;
				run = prv->next;
			}
			else
			{
				prv = run;
				run = run->next;
			}
		}
		head = head->next;
	}
	return returNode;
}

void patision(int *a, int l, int mid, int r)
{
	vector<int> lm(a+l, a+mid+1); // tai sao phai la a + mid + 1 =))
	vector<int> mr(a+mid+1, a+r+1);
	int i, j;
	i = j = 0;
	while(i < lm.size() && j < mr.size())
	{
		if(lm[i] < mr[j])
		{
			a[l] = lm[i];
			i++;
		}
		else
		{
			a[l] = mr[j];
			j++;
		}
		l++;
	}

	while(i < lm.size())
	{
		a[l] = lm[i];
		i++;
		l++;
	}

	while(j < mr.size())
	{
		a[l] = mr[j];
		j++;
		l++;
	}
}

void mergeSort(int *a, int l, int r)
{
	if(l >= r)
		return;
	int mid = (l+r)/2;
	mergeSort(a, l, mid);
	mergeSort(a, mid+1, r);
	patision(a, l, mid, r);
}

void patisionLL(Node &leftLLHead, Node rigthLL)
{
	Node leftLL = leftLLHead;
	Node run = new node;
	Node returnNode = run; // node giu node truoc node dau

	while(leftLL && rigthLL)
	{
		if(leftLL->data < rigthLL->data)
		{
			run->next = leftLL;
			leftLL = leftLL->next;
		}
		else
		{
			run->next = rigthLL;
			rigthLL = rigthLL->next;
		}
		run = run->next;
	}

	while(leftLL)
	{
		run->next = leftLL;
		leftLL = leftLL->next;
		run = run->next;
	}

	while(rigthLL)
	{
		run->next = rigthLL;
		rigthLL = rigthLL->next;
		run = run->next;
	}
	leftLLHead = returnNode->next;
	delete returnNode;
}

void mergeSortLL(Node &head)
{
	if(head->next == nullptr)
		return;
	Node mid = returnNodeMid(head);
	Node rigthLL = mid->next;
	mid->next = nullptr;

	mergeSortLL(head);
	mergeSortLL(rigthLL);
	patisionLL(head, rigthLL);
}

void swapNodeLLNotData(Node &head, int data1, int data2)
{
	Node prv1, prv2, cur1, cur2;
	prv1 = prv2 = nullptr;
	cur1 = cur2 = head;

	while(cur1 != nullptr && cur1->data != data1)
	{
		prv1 = cur1;
		cur1 = cur1->next;
	}

	while(cur2 != nullptr && cur2->data != data2)
	{
		prv2 = cur2;
		cur2 = cur2->next;
	}

	Node calm = cur2->next;
	prv1->next = cur2;
	prv2->next = cur1;
	cur2->next = cur1->next;
	cur1->next = calm;
}

int main()
{
	srand(time(NULL));
	Node head = nullptr;
	for(int i=0; i<10; i++)
		insertNodePosition(head, i+1, i);
	printList(head);
	cout << endl;

	swapNodeLLNotData(head, 2, 9);
	printList(head);
	return 0;
}