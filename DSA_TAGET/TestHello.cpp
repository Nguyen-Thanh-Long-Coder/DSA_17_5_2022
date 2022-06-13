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
	if(data1 == data2)
		return;

	int count1 = 0, count2 = 0;
	Node prv1, prv2, cur1, cur2;
	prv1 = prv2 = nullptr;
	cur1 = cur2 = head;

	while(cur1 != nullptr && cur1->data != data1)
	{
		prv1 = cur1;
		cur1 = cur1->next;
		count1++;
	}

	while(cur2 != nullptr && cur2->data != data2)
	{
		prv2 = cur2;
		cur2 = cur2->next;
		count2++;
	}

	if(cur1 == nullptr || cur2 == nullptr)
		return;

	Node calm = cur2->next;
	if(prv1 != nullptr)
		prv1->next = cur2;
	if(prv2 != nullptr)
		prv2->next = cur1;

	cur2->next = cur1->next;
	cur1->next = calm;

	if(count1 > count2)
		head = cur1;
	else
		head = cur2;
}

Node returnSwapTwoNode(Node one, Node two)
{
	one->next = two->next;
	two->next = one;
	return two;
}

void swapTwoNode(Node &head)
{
	if(head == nullptr || head->next == nullptr)
		return;
	head = returnSwapTwoNode(head, head->next);
	Node run = head->next;
	while(run->next != nullptr && run->next->next != nullptr)
	{
		run->next = returnSwapTwoNode(run->next, run->next->next);
		run = run->next->next;
	}
}

void swapNodeRer(Node &head)
{
	if(head == nullptr || head->next == nullptr)
		return;

	Node nextNode = head->next;
	head->next = nextNode->next;
	nextNode->next = head;
	head = nextNode;

	swapNodeRer(head->next->next);
}

void moveLastToFront(Node &head)
{
	if(head == nullptr)
		return;

	Node prv = nullptr;
	Node run = head;
	while(run->next != nullptr)
	{
		prv = run;
		run = run->next;
	}

	if(prv != nullptr)
	{
		prv->next = nullptr;
		run->next = head;
		head = run;
	}
}

Node intersectionSort(Node head, Node head2)
{
	Node insec = nullptr;
	Node returnInsec = nullptr;
	while(head != nullptr && head2 != nullptr)
	{
		if(head->data > head2->data)
			head2 = head2->next;
		else if(head->data < head2->data)
			head = head->next;
		else
		{
			Node tmp = new node;
			tmp->data = head->data;
			tmp->next = nullptr;

			if(insec == nullptr)
			{
				returnInsec = tmp;
				insec = tmp;
			}
			else
			{
				insec->next = tmp;
				insec = insec->next;
			}
			head = head->next;
			head2 = head2->next;
		}
	}

	return returnInsec;
}

Node intersectionPoinTwoLL(Node head1, Node head2)
{
	int len1 = countLengthLL(head1);
	int len2 = countLengthLL(head2);

	while(len1 > len2)
	{
		head1 = head1->next;
		len1--;
	}
	
	while(len1 < len2)
	{
		head2 = head2->next;
		len2--;
	}

	while(head1->next != head2->next)
	{
		head1 = head1->next;
		head2 = head2->next;
	}

	return head1->next;
}

void quickSortArray(int *a, int l, int r)
{
	if(l >= r)
		return;

	int pivot = a[(l + r) / 2];

	int i = l, j = r;

	l--; r++;
	while(l <= r)
	{
		do
		{
			l++;
		}while(a[l] < pivot);

		do
		{
			r--;
		}while(a[r] > pivot);

		if(l < r)
			swap(a[l], a[r]);
	}

	quickSortArray(a, i, r);
	quickSortArray(a, l, j);
}

Node getTail(Node head)
{
	while(head != nullptr && head->next != nullptr)
		head = head->next;

	return head;
}

Node partition(Node head, Node end, Node &newHead, Node &newTail)
{
	Node pivot = end;
	Node prv = nullptr, cur = head, tail = end;

	while(cur != pivot)
	{
		if(cur->data < pivot->data)
		{
			if(newHead == nullptr)
				newHead = cur;

			prv = cur;
			cur = cur->next;
		}
		else
		{
			if(prv != nullptr)
				prv->next = cur->next;

			Node tmp = cur->next;
			cur->next = nullptr;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}

	if(newHead == nullptr)
		newHead = pivot;

	newTail = tail;
	
	return pivot;
}

Node quickSortRecur(Node head, Node tail)
{
	if(!head || head == tail)
		return head;

	Node newHead = nullptr, newTail = nullptr;
	Node pivot = partition(head, tail, newHead, newTail);

	if(pivot->data != newHead->data)
	{
		Node tmp = newHead;
		while(tmp->next != pivot)
		{
			tmp = tmp->next;
		}

		tmp->next = nullptr;
		newHead = quickSortRecur(newHead, tmp);
		Node tailTmp = getTail(newHead);
		tailTmp->next = pivot;
	}

	pivot->next = quickSortRecur(pivot->next, newTail);

	return newHead;

}

void segregateOddEven(Node &head)
{
	Node flag = nullptr;
	Node run = head, prv = nullptr;
	Node tail = getTail(head);
	head = nullptr;

	while(run != flag)
	{
		if(run->data & 1)
		{
			if(flag == nullptr)
				flag = run;

			tail->next = run;
			tail = run;

			Node tmp = run->next;
			if(prv != nullptr)
				prv->next = tmp;
			run->next = nullptr;
			run = tmp;
		}
		else
		{
			if(head == nullptr)
				head = run;
			prv = run;
			run = run->next;
		}
	}
}

Node reverseLLTwoP1(Node head)
{
	if(head == nullptr || head->next == nullptr)
		return head;

	Node cur = head, prv = nullptr;

	while(cur != nullptr)
	{
		cur = (Node) ((int)cur^(int)prv^(int)cur->next^(int)(cur->next = prv)^(int)(prv = cur));
	} 

	return prv;
}

Node reverseLLTwoP2(Node head)
{
	if(head == nullptr || head->next == nullptr)
		return head;
	Node next = nullptr, cur = head;

	while(cur->next != nullptr)
	{
		next = cur->next;
		cur->next = next->next;
		next->next = head;
		head = next;
	}

	return head;
}

Node mergeSortReverseOrder(Node head1, Node head2)
{
	Node dummy = new node;
	dummy->next = nullptr;
	dummy->data = -1;

	while(head1 != nullptr && head2 != nullptr)
	{
		if(head1->data < head2->data)
		{
			Node tmp = head1->next;
			head1->next = dummy->next;
			dummy->next = head1;
			head1 = tmp;
		}
		else
		{
			Node tmp = head2->next;
			head2->next = dummy->next;
			dummy->next = head2;
			head2 = tmp;
		}
	}

	while(head1)
	{
		Node tmp = head1->next;
		head1->next = dummy->next;
		dummy->next = head1;
		head1 = tmp;
	}

	while(head2)
	{
		Node tmp = head2->next;
		head2->next = dummy->next;
		dummy->next = head2;
		head2 = tmp;
	}

	Node ret = dummy->next;
	delete dummy;
	return ret;
}

Node reverseGroup(Node head, const int k)
{
	Node prv = nullptr, cur = head;
	int count = 0;

	while(cur != nullptr && count < k)
	{
		cur = (Node)((int)cur ^ (int)prv ^ (int)(cur->next) ^ (int)(cur->next = prv) ^ (int)(prv = cur));
		count++;
	}

	if(cur != nullptr)
		head->next = reverseGroup(cur ,k);

	return prv;
}

Node reverseGroupByStack(Node head, int k)
{
	int flag = 1;
	Node newHead = nullptr, track = nullptr, cur = head;
	while(cur != nullptr)
	{
		int count = 0;
		if(flag)
		{
			stack<Node> st;

			while(cur != nullptr && count < k)
			{
				st.push(cur);
				cur = cur->next;
				st.top()->next = nullptr;
				count++;
			}

			while(!st.empty())
			{
				if(newHead == nullptr)
				{
					newHead = st.top();
					track = st.top();
					st.pop();
				}
				else
				{
					track->next = st.top();
					st.pop();
					track = track->next;
				}
			}
			flag = 0;
		}
		else
		{
			while(cur != nullptr && count < k)
			{
				track->next = cur;
				track = track->next;
				cur = cur->next;
				count++;
			}
			flag = 1;
		}
	}

	return newHead;
}

Node alternateOddEven(Node head)
{
	// if(head == nullptr || head->next == nullptr)
	// 	return head;

	// int flag = !(head->data & 1);
	// Node updateLink = head, cur = head->next, prv = head;

	// while(cur)
	// {
	// 	if(flag)
	// 	{
	// 		while(cur != nullptr && !(cur->data & 1))
	// 		{
	// 			prv = cur;
	// 			cur = cur->next;
	// 		}

	// 		if(cur != nullptr)
	// 		{
	// 			prv->next = cur->next;
	// 			cur->next = updateLink->next;
	// 			updateLink->next = cur;
	// 			updateLink = updateLink->next;
	// 			cur = updateLink->next;
	// 			prv = updateLink;
	// 		}

	// 		flag = 0;
	// 	}
	// 	else
	// 	{
	// 		while(cur != nullptr && (cur->data & 1))
	// 		{
	// 			prv = cur;
	// 			cur = cur->next;
	// 		}

	// 		if(cur != nullptr)
	// 		{
	// 			prv->next = cur->next;
	// 			cur->next = updateLink->next;
	// 			updateLink->next = cur;
	// 			updateLink = updateLink->next;
	// 			cur = updateLink->next;
	// 			prv = updateLink;
	// 		}
			
	// 		flag = 1;
	// 	}
	// }

	// return head;

	int flag = !(head->data & 1);
	Node odd, even, headOdd, headEven, track;
	even = odd = headOdd = headEven = nullptr;
	track = head;

	for(Node k = head->next; k != nullptr; k = k->next)
	{
		if(k->data & 1)
		{
			if(odd == nullptr)
				headOdd = odd = k;
			else
			{
				odd->next = k;
				odd = odd->next;
			}
		}
		else
		{
			if(even == nullptr)
				headEven = even = k;
			else
			{
				even->next = k;
				even = even->next;
			}
		}
	}

	if(headOdd != nullptr)
		odd->next = nullptr;
	else if(headEven != nullptr)
		even->next = nullptr;

	if(flag)
	{
		while(headOdd && headEven)
		{
			track->next = headOdd;
			headOdd = headOdd->next;
			track->next->next = headEven;
			track = headEven;
			headEven = headEven->next;
		}
	}
	else
	{
		while(headOdd && headEven)
		{
			track->next = headEven;
			headEven = headEven->next;
			track->next->next = headOdd;
			track = headOdd;
			headOdd = headOdd->next;
		}
	}

	if(headOdd)
		track->next = headOdd;
	else if(headEven)
		track->next = headEven;

	return head;
}

Node alternateOddEvenByStack(Node head)
{
	int flag = !(head->data & 1);
	stack<Node> odd, even;
	Node track = nullptr;

	for(Node k = head->next; k != nullptr; k = k->next)
	{
		if(k->data & 1)
			odd.push(k);
		else
			even.push(k);
	}

	if(odd.size() > even.size())
	{
		while(odd.size() > even.size())
		{
			odd.top()->next = track;
			track = odd.top();
			odd.pop();
		}
	}
	else if(odd.size() < even.size())
	{
		while(odd.size() < even.size())
		{
			even.top()->next = track;
			track = even.top();
			even.pop();
		}
	}

	if(flag)
	{
		while(odd.size())
		{
			even.top()->next = track;
			odd.top()->next = even.top();
			track = odd.top();
			odd.pop();
			even.pop();
		}
	}
	else
	{
		while(even.size())
		{
			odd.top()->next = track;
			even.top()->next = odd.top();
			track = even.top();
			even.pop();
			odd.pop();
		}
	}

	head->next = track;

	return head;
}

Node alternateOddEvenDiffPos(Node head)
{
	// int i = 1;
	// stack<Node> odd, even;

	// for(Node k = head; k != nullptr; k = k->next)
	// {
	// 	if((i & 1) && !(k->data & 1))
	// 		odd.push(k);
	// 	else if(!(i & 1) && (k->data & 1))
	// 		even.push(k);
	// 	i++;
	// }

	// while(odd.size() && even.size())
	// {
	// 	swap(odd.top()->data, even.top()->data);
	// 	odd.pop();
	// 	even.pop();
	// }

	// return head;

	Node dummyOdd, dummyEven, odd, even;
	dummyOdd = new node;
	dummyEven = new node;
	odd = dummyOdd;
	even = dummyEven;

	for(Node k = head; k != nullptr; k = k->next)
	{
		if(k->data & 1)
		{
			odd->next = k;
			odd = odd->next; 
		}
		else
		{
			even->next = k;
			even = even->next;
		}
	}

	odd->next = even->next = nullptr;
	odd = dummyOdd->next;
	even = dummyEven->next;
	delete dummyOdd;
	delete dummyEven;

	if(odd)
	{
		head = odd;
		Node track = head;
		odd = odd->next;

		while(odd != nullptr && even != nullptr)
		{
			track->next = even;
			even = even->next;
			track->next->next = odd;
			track = odd;
			odd = odd->next;
		}

		if(odd)
			track->next = odd;
		else if(even)
			track->next = even;
	}
	else
		return even;

	return head;
}

Node deleteNodeAlternate(Node head)
{
	// Node cur = head;
	// while(cur != nullptr && cur->next != nullptr)
	// {
	// 	Node dele = cur->next;
	// 	cur->next = cur->next->next;
	// 	cur = cur->next;
	// 	delete dele;
	// }

	// return head;

	if(head == nullptr || head->next == nullptr)
		return head;

	Node dele = head->next;
	head->next = dele->next;
	delete dele;
	deleteNodeAlternate(head->next);
	
	return head;
}

bool identicalLL(Node head1, Node head2)
{
	while(head1 != nullptr && head2 != nullptr)
	{
		if(head1->data != head2->data)
			return false;
		head1 = head1->next;
		head2 = head2->next;
	}

	if(head1 != nullptr || head2 != nullptr)
		return false;
	return true;
}

bool identicalLLRecur(Node head1, Node head2)
{
	if(head1 == nullptr && head2 == nullptr)
		return true;
	if(head1 == nullptr || head2 == nullptr || (head1->data != head2->data))
		return false;
	return identicalLLRecur(head1->next, head2->next);
}

Node deleteNodesValGreaterRight(Node head)
{
	if(head == nullptr || head->next == nullptr)
		return head;

	Node reverNode = reverLL(head);
	Node cur = reverNode->next, prv = reverNode;
	int maxN = reverNode->data;

	while(cur != nullptr)
	{
		if(cur->data <= maxN)
		{
			Node x = cur->next;
			prv->next = x;
			delete cur;
			cur = x;
		}
		else
		{
			prv = cur;
			maxN = cur->data;
			cur = cur->next;
		}
	}

	return reverLL(reverNode);
}

Node addTwoNumLL(Node head1, Node head2)
{
	int check = 0;
	Node add = new node;
	Node result = add;

	head1 = reverLL(head1);
	head2 = reverLL(head2);

	Node rec1 = head1, rec2 = head2;

	while(head1 != nullptr && head2 != nullptr)
	{
		Node element = new node;
		element->data = (head1->data + head2->data + check) % 10;

		check = (head1->data + head2->data + check) / 10;

		add->next = element;
		add = add->next;
		head1 = head1->next;
		head2 = head2->next;
	}

	while(head1 != nullptr)
	{
		Node element = new node;
		element->data = (head1->data + check) % 10;

		check = (head1->data + check) / 10;

		add->next = element;
		add = add->next;
		head1 = head1->next;
	}

	while(head2 != nullptr)
	{
		Node element = new node;
		element->data = (head2->data) % 10;

		check = (head2->data + check) / 10;

		add->next = element;
		add = add->next;
		head2 = head2->next;
	}

	if(check)
	{
		Node element = new node;
		element->data = 1;
		add->next = element;
		add = add->next;
	}
	add->next = nullptr;

	add = result;
	result = reverLL(result->next);
	delete add;

	reverLL(rec1);
	reverLL(rec2);

	return result;
}

void deleteLLConstrait(Node head, Node dele)
{
	if(dele == head)
	{
		if(head->next == nullptr)
		{
			cout << "No dele" << endl;
			return;
		}
		else
		{
			head->data = head->next->data;
			dele = head->next;
			head->next = head->next->next;
		}
	}
	else
		while(head->next != nullptr && head->next != dele)
			head = head->next;

	if(head->next == nullptr)
	{
		cout << "No dele" << endl;
		return;
	}
	else
	{
		head->next = dele->next;
		delete dele;
	}
}

Node rotateLLByK(Node head, int k)
{
	Node newHead = head, run = head;

	k = k % countLengthLL(head);

	if(k != 0)
	{
		for(int i=1; i<k; i++)
			run = run->next;

		newHead = run->next;
		run->next = nullptr;
		run = newHead;

		while(run->next != nullptr)
			run = run->next;

		run->next = head;
	}

	return newHead;
}

int main()
{
	Node head1 = nullptr, head2 = nullptr;
	int n, m, x;
	cin >> n >> m;

	for(int i=0; i<n; i++)
	{
		cin >> x;
		insertNodePosition(head1, x, i);
	}

	printList(head1);
	cout << endl;
	head1 = rotateLLByK(head1, m);
	printList(head1);

	return 0;
}

