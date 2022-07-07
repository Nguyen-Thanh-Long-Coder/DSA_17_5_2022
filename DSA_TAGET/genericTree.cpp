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

int main()
{
	int n, x, parent; cin >> n >> x;
	Node root = new node(1);
	n--;

	for(int i=0; i<n; i++)
	{
		cin >> parent >> x;
		if(insertNodeByParent(root, parent, x))
			cout << "Done insert " << parent << " " << x << endl;
		else
			cout << "Fail insert " << parent << " " << x << endl;
	}

	traverTreeNodeChildSibling(root);
	cout << "sum: " << sumOfGenericTree(root) << endl;
	return 0;
}