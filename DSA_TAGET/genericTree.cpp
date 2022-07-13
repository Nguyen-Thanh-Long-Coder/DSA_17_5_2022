#include <bits/stdc++.h>
using namespace std;

struct node
{
	int val;
	struct node* sibling;
	struct node* child;

	node(){}

	node(int val)
	{
		this->val = val;
		sibling = child = nullptr;
	}

};
typedef struct node* Node;

bool insertNodeByParent(Node &root, int parent, int val)
{
	if(root != nullptr)
	{
		if(root->val == parent)
		{
			if(root->child == nullptr)
				root->child = new node(val);
			else
			{
				Node childRoot = root->child;
				while(childRoot->sibling != nullptr)
					childRoot = childRoot->sibling;
				childRoot->sibling = new node(val);
			}

			return true;
		}

		if(insertNodeByParent(root->child, parent, val) || insertNodeByParent(root->sibling, parent, val))
			return true;
		return false;
	}
	else
		return false;
}

void traverTreeNodeChildSibling(Node root)
{
	if(root != nullptr)
	{
		cout << root->val << " ";
		traverTreeNodeChildSibling(root->child);
		traverTreeNodeChildSibling(root->sibling);
	}
}

int sumOfGenericTree(Node root)
{
	if(root == nullptr)
		return 0;
	return root->val + sumOfGenericTree(root->child) + sumOfGenericTree(root->sibling); 
}

int countNodeSiblingSupport(Node root, Node x, int prevCnt)
{
	if(root == nullptr)
		return 0;
	if(root == x)
		return prevCnt;
	
	int siblingNode = countNodeSiblingSupport(root->sibling, x, prevCnt+1);
	int childNode = countNodeSiblingSupport(root->child, x, 0);

	if(siblingNode)
		return siblingNode;
	return childNode;
}

int countNodeSibling(Node root, Node x)
{	
	int ret = 0;
	Node tmp = x;
	while(tmp != nullptr)
	{
		ret++;
		tmp = tmp->sibling;
	}

	return countNodeSiblingSupport(root, x, 0) + ret;
}

int countChildOfNodeIntoNodeChild(Node cur)
{
	if(cur->child == nullptr)
		return 0;

	int count = 0;
	queue<Node> q;
	q.push(cur->child);

	while(!q.empty())
	{
		Node tmp = q.front();
		q.pop();
		
		while(tmp != nullptr)
		{
			count++;
			if(tmp->child != nullptr)
				q.push(tmp->child);
			tmp = tmp->sibling;
		}
	}

	return count;
}

int countChildOfNode(Node cur)
{
	int count = 0;
	Node tmp = cur->child;
	while(tmp != nullptr)
	{
		count++;
		tmp = tmp->sibling;
	}

	return count;
}

Node constructGenericTreeRecur(vector<Node> nsc, int n, int k, int height, int &elementsDeepHeight, int &index)
{

	if(height <= 1 && elementsDeepHeight == 0)
		return nullptr;

	Node newNode = new node(nsc[index]->val);
	Node link = nullptr;

	for(int i=0; i<k; i++)
	{
		if(height > 1 && index < n - 1 )
		{
			index++;
			if(link == nullptr)
			{
				link = newNode->child = constructGenericTreeRecur(nsc, n, k, height-1, elementsDeepHeight, index);
			}
			else
			{
				link->sibling = constructGenericTreeRecur(nsc, n, k, height-1, elementsDeepHeight, index);
				link = link->sibling;
			}
		}
		else if(height == 1 && elementsDeepHeight != 0)
		{
			elementsDeepHeight--;
			return newNode;
		}
	}

	return newNode;
}

Node constructGenericTreeByArrayNCS(vector<Node> ncs, int k)
{
	int height = ceil(log(ncs.size()*(k-1) + 1) / log(k));
	int index = 0, elementDeep = ncs.size() - ((float)(1-pow(k, height-1)) / (1-k));
	return constructGenericTreeRecur(ncs, ncs.size(), k, height, elementDeep, index);
}

int main()
{
	ifstream fileIn;
	fileIn.open("inputGenericTree.txt", ios_base::in);
	int n, x, parent; fileIn >> n >> x;
	Node root = new node(1);
	n--;

	for(int i=0; i<n; i++)
	{
		fileIn >> parent >> x;
		if(insertNodeByParent(root, parent, x))
			cout << "Done insert " << parent << " " << x << endl;
		else
			cout << "Fail insert " << parent << " " << x << endl;
	}

	cout << endl << countChildOfNode(root->child->sibling->sibling->sibling) << endl;
	fileIn.close();

	return 0;
}