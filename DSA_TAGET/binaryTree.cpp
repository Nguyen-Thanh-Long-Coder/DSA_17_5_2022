#include <bits/stdc++.h>
#include <iostream>
#include <stack>
#include <string>
#include <queue>
using namespace std;

struct node
{
	int data;
	struct node* left;
	struct node* right;

	node(int data)
	{
		this->data = data;
		left = right = nullptr; 
	}
};
typedef struct node* Node;

void checkLeftPushRightStack(Node root, stack<Node> &st)
{
	while(root != nullptr)
	{
		cout << root->data << " ";
		if(root->right != nullptr)
			st.push(root->right);
		root = root->left;
	}
}

void traverTreeNotRecurDLR(Node root)
{
	if(root == nullptr)
		return;
	stack<Node> storeRight;
	checkLeftPushRightStack(root, storeRight);

	while(!storeRight.empty())
	{
		Node check = storeRight.top();
		storeRight.pop();
		checkLeftPushRightStack(check, storeRight);
	}
}

void traverTreeNotRecurLDR(Node root)
{
	stack<Node> storeNode;	
	while(1)
	{
		while(root != nullptr)
		{
			Node leftRoot = root->left;
			storeNode.push(root);
			root = leftRoot;
		}

		if(storeNode.size())
		{
			cout << storeNode.top()->data << " ";
			root = storeNode.top()->right;
			storeNode.pop();
		}
		else
			break;
	}
}

void traverTreeNotRecurLRD(Node root)
{
	stack<Node> st;
	stack<int> reverseData;

	while(1)
	{
		while(root != nullptr)
		{
			reverseData.push(root->data);
			if(root->left != nullptr)
				st.push(root->left);
			root = root->right;
		}

		if(!st.empty())
		{
			root = st.top();
			st.pop();
		}
		else
			break;
	}

	while(!reverseData.empty())
	{
		cout << reverseData.top() << " ";
		reverseData.pop(); 
	}
}

void insertNodeIntoTree(Node &root, int data)
{
	if(root != nullptr)
	{
		if(root->data <= data)
			insertNodeIntoTree(root->right, data);
		else
			insertNodeIntoTree(root->left, data);
	}
	else
		root = new node(data);
}

void traverTreeOrderLever(Node root)
{
	queue<Node> q;
	if(root != nullptr)
		q.push(root);

	while(!q.empty())
	{
		int size = q.size();
		for(int i=0; i<size; i++)
		{
			Node tmp = q.front();
			cout << tmp->data << " ";
			q.pop();
			q.push(tmp);
		}

		for(int i=0; i<size; i++)
		{
			Node tmp = q.front();
			if(tmp->left != nullptr)
				q.push(tmp->left);
			if(tmp->right != nullptr)
				q.push(tmp->right);
			q.pop();
		}
	}
}

int maximumInBinarySearhTree(Node root)
{
	if(root == nullptr)
		return 0;
	while(root->right != nullptr)
		root = root->right;
	return root->data;
}

int maximumInBinaryTreeRecur(Node root)
{
	if(root == nullptr)
		return 0;
	else if(root->left == nullptr && root->right == nullptr)
		return root->data;
	else if (root->left != nullptr && root->right != nullptr)
	{
		int maxLeft = maximumInBinaryTreeRecur(root->left);
		int maxRight = maximumInBinaryTreeRecur(root->right);
		return max({maxLeft, maxRight, root->data});
	}
	else if(root->left != nullptr)
	{
		int maxLeft = maximumInBinaryTreeRecur(root->left);
		return (root->data > maxLeft) ? root->data : maxLeft;
	}
	else if(root->right != nullptr)
	{
		int maxRight = maximumInBinaryTreeRecur(root->right);
		return (root->data > maxRight) ? root->data : maxRight;
	}
}

void insertNodeIntoCompleteTree(Node &root, int data)
{
	if(root == nullptr)
		root = new node(data);
	else
	{
		queue<Node> q;
		q.push(root);

		while(1)
		{
			Node tmp = q.front();
			q.pop();
			if(tmp->left == nullptr)
			{
				tmp->left = new node(data);
				return;
			}
			else if(tmp->right == nullptr)
			{
				tmp->right = new node(data);
				return;
			}
			
			q.push(tmp->left);
			q.push(tmp->right);
		}
	}
}

int sizeBinaryTree(Node root)
{
	if(root == nullptr)
		return 0;
	return 1 + sizeBinaryTree(root->left) + sizeBinaryTree(root->right);
}

void printTreeLeverReverse(Node root)
{
	if(root == nullptr)
		return;
	queue<Node> q, store;
	stack<vector<int>> st;
	int cnt = 0, h = 1;
	q.push(root);
	store.push(root);

	while(!q.empty())
	{
		if(q.front()->left != nullptr)
		{
			q.push(q.front()->left);
			store.push(q.front()->left);
		}

		if(q.front()->right != nullptr)
		{
			q.push(q.front()->right);
			store.push(q.front()->right);
		}
		q.pop();
	}

	vector<int> v;
	while(!store.empty())
	{
		v.push_back(store.front()->data);
		cnt++;

		if(cnt == pow(2, h) - 1)
		{
			vector<int> tmp(v.begin(), v.end());
			st.push(tmp);
			v.clear();
			h++;
		}

		store.pop();
	}
	if(cnt != pow(2, h) - 1)
		st.push(v);

	while(!st.empty())
	{
		vector<int> traver = st.top();
		st.pop();
		for(int i=0; i<traver.size(); i++)
			cout << traver[i] << " ";
	}
}

void deleteTreeByRecur(Node &root)
{
	if(root != nullptr)
	{
		deleteTreeByRecur(root->left);
		deleteTreeByRecur(root->right);
		delete root;
		root = nullptr;
	}
}

void processHeight(Node root, int &h, int hCur)
{
	if(root != nullptr)
	{
		hCur++;
		if(hCur > h)
			h = hCur;
		processHeight(root->left, h, hCur);
		processHeight(root->right, h, hCur);
	}
}

int heightTreeByRecur(Node root)
{
	int height = 0;
	processHeight(root, height, height);

	return height;
}

Node findNodeDeepeseTree(Node root)
{
	if(root == nullptr)
		return root;

	queue<Node> q;
	Node result = root;
	q.push(root);
	q.push(nullptr);

	while(!q.empty())
	{
		Node pNode = q.front();
		q.pop();

		if(pNode == nullptr)
		{
			if(!q.empty())
			{
				q.push(nullptr);
				result = q.front();
			}
		}
		else
		{
			if(pNode->left != nullptr)
				q.push(pNode->left);
			if(pNode->right != nullptr)
				q.push(pNode->right);
		}
	}

	return result;
}

Node swapDataAndDeleRightMost(Node dele, Node &rightMost)
{
	if(rightMost->right != nullptr)
		swapDataAndDeleRightMost(dele, rightMost->right);
	else
	{
		Node x = rightMost;
		dele->data = rightMost->data;
		rightMost = rightMost->left;
		return x;
	}
}

void deleteNodeInBinaryTreeRecur(Node &root, int data)
{
	if(root == nullptr)
		return;
	else if(root->data == data)
	{
		Node x = root;
		if(root->left == nullptr && root->right == nullptr)
			root = nullptr;
		else if(root->left != nullptr && root->right != nullptr)
		{
			//x = swapDataAndDeleRightMost(root, root->left);

			Node parentRightMost = root, rightMost = root->left;
			while(rightMost->right != nullptr)
			{
				parentRightMost = rightMost;
				rightMost = rightMost->right;
			}

			root->data = rightMost->data;
			x = rightMost;
			if(parentRightMost != root)
				parentRightMost->right = rightMost->left;
			else
				parentRightMost->left = rightMost->left;
		}
		else
		{
			if(root->left == nullptr)
				root = root->right;
			else
				root = root->left;
		}

		delete x;
	}
	else
	{
		if(root->data > data)
			deleteNodeInBinaryTreeRecur(root->left, data);
		else
			deleteNodeInBinaryTreeRecur(root->right, data);
	}
}
bool hasPathEqualSum(Node tree, int sum)
{
	if(tree == nullptr)
		return false;
	if(sum - tree->data == 0)
		return true;
	return hasPathEqualSum(tree->left, sum - tree->data) || hasPathEqualSum(tree->right, sum - tree->data);
}

void convertionTreeToMirrorTree(Node root)
{
	if(root == nullptr || (root->left == nullptr && root->right == nullptr))
		return;
	Node tmp = root->left;
	root->left = root->right;
	root->right = tmp;

	convertionTreeToMirrorTree(root->left);
	convertionTreeToMirrorTree(root->right);
}

bool sameStructTwoTree(Node root1, Node root2)
{
	if(root1 == nullptr && root2 == nullptr)
		return true;
	if(root1 == nullptr && root2 != nullptr || root1 != nullptr && root2 == nullptr)
		return false;

	return (root1->data == root2->data) && sameStructTwoTree(root1->left, root2->left) && sameStructTwoTree(root1->right, root2->right);
}

bool sameTwoTreeMirror(Node root1, Node root2)
{
	if(root1 == nullptr && root2 == nullptr)
		return true;
	if(root1 == nullptr && root2 != nullptr || root1 != nullptr && root2 == nullptr)
		return false;
	return (root1->data == root2->data) && sameTwoTreeMirror(root1->left, root2->right) && sameTwoTreeMirror(root1->right, root2->left);
}

bool pathToNode(Node root, Node find, stack<Node> &st)
{
	if(root == nullptr)
		return false;

	st.push(root);
	if(root == find)
		return true;

	bool check = pathToNode(root->left, find, st) || pathToNode(root->right, find, st);
	
	if(check == false)
	{
		st.pop();
		return false;
	}
	else
		return true;
}

Node LCA(Node root, Node a, Node b)
{
	stack<Node> pathA, pathB;
	if(!pathToNode(root, a, pathA) || !pathToNode(root, b, pathB))
		return nullptr;
	queue<Node> q;
	while(!pathA.empty())
	{
		q.push(pathA.top());
		pathA.pop();
	}

	while(!q.empty())
	{
		pathA.push(q.front());
		q.pop();
	}

	while(!pathB.empty())
	{
		q.push(pathB.top());
		pathB.pop();
	}

	while(!q.empty())
	{
		pathB.push(q.front());
		q.pop();
	}

	while(!pathA.empty() && !pathB.empty())
	{
		Node tmp = pathA.top();
		pathA.pop();
		pathB.pop();
		if((pathA.empty() && !pathB.empty()) || (pathA.empty() && !pathB.empty()) || (pathA.top() != pathB.top()))
			return tmp;
	}

	return nullptr;
}

void mainVerticalSum(Node root, int index, vector<int> &result)
{
	if(root != nullptr)
	{
		result[index] += root->data;
		mainVerticalSum(root->left, index-1, result);
		mainVerticalSum(root->right, index+1, result);
	}
}

vector<int> verticalSum(Node root)
{
	int level = 0;
	Node tmp = root;
	while(tmp != nullptr)
	{
		level++;
		tmp = tmp->left;
	}

	vector<int> result((level-1) * 2 + 1);
	mainVerticalSum(root, ((level-1) * 2 + 1)/2, result);
	return result;
}

Node constructTreeByLAndI(string a, int &index)
{

	Node ret = new node(a[index]);
	if(a[index] == 'I')
	{
		ret->left = constructTreeByLAndI(a, ++index);
		ret->right = constructTreeByLAndI(a, ++index);
	}

	return ret;
}

void traverTreeNLRDataIAndL(Node root)
{
	if(root == nullptr)
		return;

	cout << (char)root->data << " ";
	if(root->data == 'I')
	{
		traverTreeNLRDataIAndL(root->left);
		traverTreeNLRDataIAndL(root->right);
	}
}

void traversalLNR(Node root)
{
	if(root == nullptr)
		return;
	stack<Node> st;

	while(1)
	{
		while(root != nullptr)
		{
			st.push(root);
			root = root->left;
		}

		if(st.empty())
			break;
		else
		{
			cout << st.top() << " ";
			root = st.top()->right;
			st.pop();
		}
	}
}

Node findingInorderSuccessor(Node root, Node find)
{
	stack<Node> st;

	while(1)
	{
		while(root != nullptr)
		{
			st.push(root);
			root = root->left;
		}

		if(st.empty())
			break;
		else
		{
			if(st.top() == find)
			{
				Node tmp = st.top()->right;
				while(tmp != nullptr && tmp->left != nullptr)
					tmp = tmp->left;
				return tmp;
			}
			
			root = st.top()->right;
			st.pop();
		}
	}
} 

Node buildExpressionTree(string postfix)
{
	map<int, int> priority;
	priority['+'] = priority['-'] = 1;
	priority['*'] = priority['/'] = 2;
	priority['('] = priority[')'] = 0;

	stack<Node> stOperand, stOperator;
	for(int i=0; i<postfix.length(); i++)
	{
		if(postfix[i] >= '0' && postfix[i] <= '9')
			stOperand.push(new node(postfix[i]));
		else
		{
			if(stOperator.empty() || (postfix[i] == '(') || (priority[postfix[i]] > priority[stOperator.top()->data]))
				stOperator.push(new node(postfix[i]));
			else if(postfix[i] == ')')
			{
				// a operator b
				while(stOperator.top()->data != '(')
				{
					Node b = stOperand.top();
					stOperand.pop();
					Node a = stOperand.top();
					stOperand.pop();
					Node rootSub = stOperator.top();
					stOperator.pop();
					rootSub->left = a;
					rootSub->right = b;
					stOperand.push(rootSub);
				}
				Node dele = stOperator.top();
				stOperator.pop();
				delete dele;
			}
			else
			{
				while(!stOperator.empty() && priority[stOperator.top()->data] > priority[postfix[i]])
				{
					Node b = stOperand.top();
					stOperand.pop();
					Node a = stOperand.top();
					stOperand.pop();
					Node rootSub = stOperator.top();
					stOperator.pop();
					rootSub->left = a;
					rootSub->right = b;
					stOperand.push(rootSub);
				}
				stOperator.push(new node(postfix[i]));
			}
		}
	}

	while(!stOperator.empty())
	{
		Node b = stOperand.top();
		stOperand.pop();
		Node a = stOperand.top();
		stOperand.pop();
		Node rootSub = stOperator.top();
		stOperator.pop();
		rootSub->left = a;
		rootSub->right = b;
		stOperand.push(rootSub);
	}

	return stOperand.top();
}

int main()
{
	string postfix;
	getline(cin, postfix);
	Node root = buildExpressionTree(postfix);
	traverTreeOrderLever(root);
	return 0;
}