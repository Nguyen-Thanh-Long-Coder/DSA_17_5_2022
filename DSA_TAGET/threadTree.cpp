#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct node
{
    int val;
    int lFlag;
    int rFlag;
    struct node* left;
    struct node* right;
};
typedef struct node* Node;

Node mostLeft(Node root)
{
    while(root != nullptr && root->left != nullptr)
        root = root->left;

    return root;
}

Node findingSuccessorInorder(Node find)
{
    if(find->rFlag == 0)
    {
        if(find->right == find->right->right)
            return nullptr;
        return find->right;
    }
    else
    {
        Node tmp = find->right;
        while(tmp->lFlag == 1)
            tmp = tmp->left;
        return tmp; 
    }
}

void traversalInorder(Node root)
{
    if(root != nullptr)
    {
        if(root->lFlag == 1)
            traversalInorder(root->left);
        cout << root->val << " ";
        if(root->rFlag == 1)
            traversalInorder(root->right);
    }
}

void traversalInorderUsingSuccessor(Node root)
{
    Node cur = mostLeft(root);

    while(1)
    {
        cout << cur->val << " ";
        if(cur->rFlag == 1)
        {
            cur = mostLeft(cur->right);
        }
        else
        {
            cur = cur->right;
            if(cur->right = cur->right->right)
                return;
        }
    }
}

Node preInorderInTreeInorder(Node find)
{
    if(find->lFlag == 1)
        return find->left;
    else if(find->rFlag == 1)
        return find->right;
    while(find->rFlag == 0)
    {
        find = findingSuccessorInorder(find);
    }

    return find->right;
}

void traversalPreInorder(Node root)
{
    Node cur = root, tmp;
    while(1)
    {
        while(cur != nullptr)
        {
            cout << cur->val << " ";
            tmp = cur;
            cur = cur->left;
        }

        cur = (tmp->right != nullptr) ? (tmp) : (findingSuccessorInorder(tmp));
        if(cur->right == cur->right->right)
            break;
    }
}

void traversalPreOrderInOrder2(Node root)
{
    while(root != nullptr && (root->right == root->right->right))
    {
        cout << root->val << " ";
        root = preInorderInTreeInorder(root);
    }
}

void insertNodeQAttacRighthNodeP(Node q, Node p)
{
    q->rFlag = p->rFlag;
    q->lFlag = 0;
    q->right = p->right;
    q->left = p;

    p->right = q;
    p->rFlag = 1;

    if(q->rFlag == 1)
    {
        Node leftMost = q->right;
        while(leftMost->lFlag == 1)
            leftMost = leftMost->left;

        leftMost->left = q;
    }
}

Node preOrderSuccessorNotThreadTree(Node root, Node find)
{
    if(find->left != nullptr)
        return find->left;
    else if(find->right != nullptr)
        return find->right;

    stack<Node> st;
    Node top;
    st.push(root);

    while(1)
    {
        top = st.top();
        while(top != nullptr)
        {
            if(top == find)
                return st.empty() ? nullptr : st.top();

            if(top->right != nullptr)
                st.push(top->right);
            top = top->left;
        }

        if(st.empty())
            break;
        else
            top = st.top();
    }
}

Node findingNodeInorderNotThreadTree(Node root, Node find)
{
    if(find->right != nullptr)
        return mostLeft(find->right);
    
    stack<Node> st;
    while(1)
    {
        while(root != nullptr)
        {
            st.push(root);
            root = root->left;
        }

        if(st.empty())
            return nullptr;
        else
        {
            Node tmp = st.top();
            st.pop();
            if(tmp == find)
                return (st.empty()) ? nullptr : st.top();
            root = tmp->right;
        }
    }
}
int main()
{

    return 0;
}