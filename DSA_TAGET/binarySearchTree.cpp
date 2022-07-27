#include <queue>
#include <stack>
#include <iostream>
#include <vector>
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

struct ll
{
    int data;
    struct ll* next;

    ll(int data)
    {
        this->data = data;
        next = nullptr;
    }
};
typedef struct ll* LL;

void traversalLNRStack(Node root)
{
    if(root == nullptr)
        return;
    stack<Node> st;
    Node cur = root;

    while(1)
    {
        while(cur != nullptr)
        {
            st.push(cur);
            cur = cur->left;
        }

        cout << st.top()->val << " ";
        if(st.top()->right != nullptr)
            cur = st.top()->right;
        st.pop();

        if(st.empty() && (cur == nullptr))
            break;
    }
}

Node findNode(Node root, int data)
{
    // if(root == nullptr)
    //     return nullptr;
    // else
    // {
    //     if(root->val == data)
    //         return root;
    //     else
    //     {
    //         if(root->val > data)
    //             return findNode(root->left, data);
    //         else if(root->val < data)
    //             return findNode(root->right, data);
    //     }
    // }

    while(root != nullptr && root->val != data)
    {
        if(root->val > data)
            root = root->left;
        else if(root->val < data)
            root = root->right;
    }

    return root;
}

int maxElement(Node root)
{
    // if(root == nullptr)
    //     return 0;
    // else if(root->right == nullptr)
    //     return root->val;
    // return maxElement(root->right);
    // kkk 

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

Node LCATwoNode(Node root, Node a, Node b) // exist two node has lca
{
    while(1)
    {
        if((root->val > a->val && root->val < b->val) || (root->val < a->val && root->val > b->val) || (root->val == a->val) || (root->val == b->val))
            return root;
        if(root->val < a->val)
            root = root->left;
        else    
            root = root->right;
    }
}

Node combine2DLL(Node first, Node second)
{
    if(first == nullptr)
        return second;
    if(second == nullptr)
        return second;
    
    first->left->right = second;
    second->left->right = first;
    Node secondTail = second->left;
    second->left = first->left;
    first->left = secondTail;

    return first;
}

Node BSTCDD(Node root)
{
    if(root == nullptr)
        return nullptr;
    Node leftSub = BSTCDD(root->left);
    Node rightSub = BSTCDD(root->right);

    return (combine2DLL(leftSub, root), rightSub);
}

Node BSTCDD2(Node root, Node &Tail)
{
    Node leftSub, rightSub, lTail, rTail;
    if(root == nullptr)
    {
        Tail = nullptr;
        return nullptr;
    }

    leftSub = BSTCDD2(root->left, lTail);
    rightSub = BSTCDD2(root->right, rTail);
    
    root->left = leftSub;
    root->right = rightSub;

    if(rightSub != nullptr)
    {
        rightSub->left = root;
        Tail = rTail;
    }
    else
        Tail = root;

    if(leftSub != nullptr)
    {
        lTail->right = root;
        return leftSub;
    }
    else
        return root;
}

Node findMiddleDLL(Node head)
{
    if(head == nullptr)
        return head;

    Node fast = head->right;
    Node low = head;

    while((fast != head) && (fast->right != head))
    {
        fast = fast->right->right;
        low = low->right;
    }

    return (fast == head) ? low : low->right;
}

Node converDLLToBST(Node head)
{
    Node middle = findMiddleDLL(head);

    if((head->right == head) && (head->left == head))
    {
        head->left = head->right = nullptr;
    }
    else if(head->right == head->left)
    {
        middle->left->right = middle->left->left = nullptr;
        middle->right = nullptr;
    }
    else
    {
        Node tailLeft = middle->left;
        Node tailRight = head->left;
        head->left = tailLeft;
        tailLeft->right = head;

        middle->right->left = tailRight;
        tailRight->right = middle->right;

        middle->left = converDLLToBST(head);
        middle->right = converDLLToBST(middle->right);
    }

    return middle;
}

void insertNodeInDLL(Node &head, int val)
{
    Node insertNode = new node(val);
    if(head == nullptr)
    {
        head = insertNode;
        insertNode->right = insertNode->left = head;
    }
    else
    {
        head->left->right = insertNode;
        insertNode->left = head->left;
        insertNode->right = head;
        head->left = insertNode;
    }
}

void traversalOrderLever(Node head)
{
    if(head == nullptr)
        return;

    queue<Node> q;
    q.push(head);

    while(!q.empty())
    {
        Node cur = q.front();
        q.pop();

        cout << cur->val << " ";

        if(cur->left != nullptr)
            q.push(cur->left);

        if(cur->right != nullptr)
            q.push(cur->right);
    }
}

void traverDLL(Node head)
{
    if(head == nullptr)
        return;
    Node run = head;
    do
    {
        cout << run->val << " ";
        run = run->right;
    } while (run != head);
}

Node converArrayToBSTSupport(int *a, int l, int r)
{
    if(l > r)   
        return nullptr;
    int mid = (l + r) / 2;
    Node newNode = new node(a[mid]);

    newNode->left = converArrayToBSTSupport(a, l, mid-1);
    newNode->right = converArrayToBSTSupport(a, mid+1, r);
    return newNode;
}

Node converArrayToBST(int *a, int n)
{
    return converArrayToBSTSupport(a, 0, n-1);
}

Node converLLToBSTSPP(LL &head, int start, int end)
{
    if(start > end)
        return nullptr;
    
    int mid = (start + end) / 2;
    Node leftSub = converLLToBSTSPP(head, start, mid-1);

    Node newNode = new node(head->data);
    newNode->left = leftSub;

    head = head->next;
    newNode->right = converLLToBSTSPP(head, mid+1, end);

    return newNode;
}

Node converLLToBST(LL head)
{
    int lengthLL = 0;
    LL tmp = head;
    while(tmp != nullptr)
    {
        lengthLL++;
        tmp = tmp->next;
    }

    return converLLToBSTSPP(head, 0, lengthLL-1);
    // int lengthLL = 0;
    // LL tmp = head;
    // while(tmp != nullptr)
    // {
    //     lengthLL++;
    //     tmp = tmp->next;
    // }

    // int *arr = new int[lengthLL];
    // for(int i=0; i<lengthLL; i++)
    // {
    //     arr[i] = head->data;
    //     head = head->next;
    // }

    // return converArrayToBST(arr, lengthLL);

    // // //test
    // //LL head = new ll(1);
    // // head->next = new ll(2);
    // // head->next->next = new ll(3);
    // // head->next->next->next = new ll(4);
    // // head->next->next->next->next = new ll(5);

    // // Node root = converLLToBST(head);
    // // traversalOrderLever(root);
}

int elementKSmallestSPP(Node root, int &k)
{
    if(root == nullptr)
        return INT_MIN;

    int leftS = elementKSmallestSPP(root->left, k);
    if(leftS != INT_MIN)
        return leftS;

    if(k == 1)
        return root->val;
    k--;

    return elementKSmallestSPP(root->right, k);
}

int elementKSmallest(Node root, int k)
{
    int tmp = k;
    return elementKSmallestSPP(root, tmp);
}

bool ceilAndFloorInBSTSPP(Node root, int value, int &floor, int &ceil)
{
    if(root != nullptr)
    {
        if(!ceilAndFloorInBSTSPP(root->left, value, floor, ceil))
        {
            if(value == root->val)
            {
                floor = ceil = root->val;
                return true;
            }
            else if(value > root->val)
                floor = root->val;
            else
            {
                ceil = root->val;
                return true;
            }
            
            return ceilAndFloorInBSTSPP(root->right, value, floor, ceil);
        }
        else
            return true;
    }
    
    return false;
}

void ceilAndFloorInBST(Node root, int value, int &floor, int &ceil)
{
    floor = ceil = -1;
    ceilAndFloorInBSTSPP(root, value, floor, ceil);
}

// bool findFloorInBSTSPP(Node root, Node &prv, int value)
// {
//     if(root == nullptr)
//         return false;
    
//     if(findFloorInBSTSPP(root->left, prv, value))
//         return true;

//     if(root->val > value)
//         return true;
//     else
//     {
//         prv = root;
//         return findFloorInBSTSPP(root->right, prv, value);
//     }
// }

// Node findFloorInBST(Node root, int value)
// {
//     Node prv = nullptr;
//     findFloorInBSTSPP(root, prv, value);
//     return prv;
// }

Node findFloorInBST(Node root, int value)
{
    if(root == nullptr)
        return nullptr;
    Node rightSub = findFloorInBST(root->right, value);

    if(rightSub != nullptr)
        return rightSub;
    
    if(root->val <= value)
        return root;

    return findFloorInBST(root->left, value);
}

Node findCeilInBST(Node root, int value)
{
    if(root == nullptr)
        return root;
    Node leftSub = findCeilInBST(root->left, value);

    if(leftSub != nullptr)
        return leftSub;
    if(root->val >= value)
        return root;
    return findCeilInBST(root->right, value);
}

vector<int> commonElementsTwoBST(Node root1, Node root2)
{
    stack<Node> st1, st2;
    vector<int> ret;

    while(1)
    {
        if(root1 != nullptr)
        {
            st1.push(root1);         
            root1 = root1->left;
        }
        else if(root2 != nullptr)
        {
            st2.push(root2);
            root2 = root2->left;
        }
        else if(!st1.empty() && !st2.empty())
        {
            root1 = st1.top();
            root2 = st2.top();

            if(root1->val < root2->val)
            {
                root1 = st1.top()->right;
                st1.pop();
                root2 = nullptr;
            }
            else if(root1->val > root2->val)
            {
                root2 = st2.top()->right;
                st2.pop();
                root1 = nullptr;
            }
            else
            {
                ret.push_back(root1->val);
                root1 = st1.top()->right;
                root2 = st2.top()->right;
                st1.pop();
                st2.pop();
            }
        }
        else
            break;
    }

    return ret;
}

void deleteBNT(Node root)
{
    if(root == nullptr)
        return;
    deleteBNT(root->left);
    deleteBNT(root->right);
    delete root;
}

void rangeK1AndK2(Node root, int k1, int k2)
{
    if(root == nullptr)
        return;
    if(root->val < k1)
        rangeK1AndK2(root->right, k1, k2);
    
    if(root->val >= k1 && root->val <= k2)
        cout << root->val << " ";

    if(root->val > k2)
        rangeK1AndK2(root->left, k1, k2);
}

Node trimTreeBSTBetweenAAndB(Node root, int a, int b)
{
    if(root == nullptr)
        return root;

    if(root->val < a)
    {
        return trimTreeBSTBetweenAAndB(root->right, a, b);
        delete root;
        deleteBNT(root->left);
    }
    
    if(root->val > b)
    {
        return trimTreeBSTBetweenAAndB(root->left, a, b);
        delete root;
        deleteBNT(root->right);
    }

    root->left = trimTreeBSTBetweenAAndB(root->left, a, b);
    root->right = trimTreeBSTBetweenAAndB(root->right, a, b);
    return root;
}

bool sameTwoBST(Node root1, Node root2)
{
    if(root1 == nullptr && root2 == nullptr)
        return true;
    if(root1 == nullptr || root2 == nullptr)
        return false;
    
    return (root1->val == root2->val) && sameTwoBST(root1->left, root2->left) && sameTwoBST(root1->right, root2->right);
}

int countBSTCanGreateRange1ToN(int n)
{
    if(n <= 1)
        return 1;

    int sum = 0;
    for(int i=1; i<=n; i++)
    {
        int leftS = countBSTCanGreateRange1ToN(i-1);
        int rightS = countBSTCanGreateRange1ToN(n-i);
        sum += leftS*rightS;
    }

    return sum;
}

int main()
{
    ifstream fileIn;
    fileIn.open("HiDay.txt", ios_base::in);
    if(fileIn.fail())
        return 0;
    
    Node root = nullptr;
    int n;
    cin >> n;
    cout << countBSTCanGreateRange1ToN(n);

        
    fileIn.close();
    return 0;
}