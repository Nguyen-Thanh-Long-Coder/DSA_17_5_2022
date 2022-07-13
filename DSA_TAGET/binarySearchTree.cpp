#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node
{
    int val;
    struct node* left;
    struct node* right;

    node(int val)
    {
        this->val = val;
        left = right = nullptr;
    }
};
typedef struct node* Node;

Node findNode(Node root, int data)
{
    if(root == nullptr)
        return nullptr;
    else
    {
        if(root->val == data)
            return root;
        else
        {
            if(root->val > data)
                return findNode(root->left, data);
            else if(root->val < data)
                return findNode(root->right, data);
        }
    }
}

int maxElement(Node root)
{
    // if(root == nullptr)
    //     return 0;
    // else if(root->right == nullptr)
    //     return root->val;
    // return maxElement(root->right);

    if(root == nullptr)
        return 0;
    while(root->right != nullptr)
        root = root->right;
    return root->val;
}

int minElement(Node root)
{
    // if(root == nullptr)
    //     return 0;
    // else if(root->left == nullptr)
    //     return root->val;
    // return maxElement(root->left);

    if(root == nullptr)
        return 0;
    while(root->left != nullptr)
        root = root->left;
    return root->val;
}

void insert(Node &root, int val)
{
    if(root == nullptr)
        root = new node(val);
    else
    {
        if(root->val > val)
            insert(root->left, val);
        else if(root->val < val)
            insert(root->right, val);
    }
}

void deleteNode(Node &root, int valDele)
{
    Node prev = nullptr, find = root;
    while(find != nullptr && (find->val != valDele))
    {
        prev = find;
        find = (find->val > valDele) ? find->left : find->right;
    }

    if(find == nullptr)
        return;

    if(find->left != nullptr && find->right != nullptr)
    {
        Node rightMost = find->left;
        prev = find;
        while(rightMost->right != nullptr)
        {
            prev = rightMost;
            rightMost = rightMost->right;
        }
        find->val = rightMost->val;
        find = rightMost;
    }
    
    if(find->left == nullptr || find->right == nullptr)
    {
        if(prev == nullptr)
            root = (find->left != nullptr) ? find->left : find->right;
        else if(prev->left == find)
            prev->left = find->left != nullptr ? find->left : find->right;
        else    
            prev->right = find->left != nullptr ? find->left : find->right;
    }

    delete find;
}

void traversalLNR(Node root)
{
    if(root != nullptr)
    {
        traversalLNR(root->left);
        cout << root->val << " ";
        traversalLNR(root->right);
    }
}

bool isBST(Node root)
{
    if(root == nullptr)
        return true;

    bool checkCur = true;
    if((root->left != nullptr && (root->val < root->left->val)) || (root->right != nullptr && (root->val > root->right->val)))
        checkCur = false;
    return checkCur && isBST(root->left) && isBST(root->right);
}

Node smallestKthSupport(Node root, int &curTh, int kTh)
{
    if(root == nullptr)
        return nullptr;

    Node leftSub = smallestKthSupport(root->left, curTh, kTh);
    
    if(curTh == (kTh-1))
    {   curTh++;
        return root;
    }
    curTh++;

    Node rightSub = smallestKthSupport(root->right, curTh, kTh);
    return (leftSub != nullptr) ? leftSub : rightSub;
}

Node smallestKth(Node root, int k)
{
    int curTh = 0;
    return smallestKthSupport(root, curTh, k);
}

int main()
{
    ifstream fileIn;
    fileIn.open("HiDay.txt", ios_base::in);
    if(fileIn.fail())
        return 0;
        
    int n, x; fileIn >> n;
    Node root = nullptr;
    for(int i=0; i<n; i++)
    {
        fileIn >> x;
        insert(root, x);
    }

    traversalLNR(root);
    if(isBST(root))
        cout << "is bst" << endl;
    else    
        cout << "not bst" << endl;

    cin >> x;
    cout << smallestKth(root, x)->val << endl;

    fileIn.close();
    return 0;
}