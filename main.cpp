// C++ program for implementing B+ Tree
#include <bits/stdc++.h>
using namespace std;
int MAX_LEAF= 4;
int MAX_NODE=3;
int index_node=0;
int data_node=0;
// BP node
class Node {

public:
    Node(int a);
    bool IS_LEAF;
    int *key, size,degree;
    Node** ptr;
    friend class BPTree;
};

// BP tree
class BPTree {
    Node* root;
    void insertInternal(int,
                        Node*,
                        Node*);
    Node* findParent(Node*, Node*);

public:
    BPTree();
    void search(int);
    void insert(int);
    Node* getRoot();
};

// Constructor of Node
Node::Node(int a)
{
    if(a==0){
    key = new int[MAX_LEAF];
    ptr = new Node*[MAX_LEAF+1];
    IS_LEAF=true;
    degree=MAX_LEAF;
        }
    else
    {
        key = new int[MAX_NODE];
        ptr = new Node*[MAX_NODE+1];
        IS_LEAF=false;
        degree=MAX_NODE;
    }
}

// Initialise the BPTree Node
BPTree::BPTree()
{
    root = nullptr;
}

// Function to find any element
// in B+ Tree
void BPTree::search(int x)
{

    // If tree is empty
    if (root == nullptr) {
        cout << "Tree is empty\n";
    }

        // Traverse to find the value
    else {

        Node* cursor = root;

        // Till we reach leaf node
        while (!cursor->IS_LEAF) {

            for (int i = 0;
                 i < cursor->size; i++) {

                // If the element to be
                // found is not present
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }

                // If reaches end of the
                // cursor node
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        // Traverse the cursor and find
        // the node with value x
        for (int i = 0;
             i < cursor->size; i++) {

            // If found then return
            if (cursor->key[i] == x) {
                cout << "Found\n";
                return;
            }
        }

        // Else element is not present
        cout << "Not found\n";
    }
}

// Function to implement the Insert
// Operation in B+ Tree
void BPTree::insert(int x)
{

    // If root is null then return
    // newly created node
    if (root == nullptr) {
        root = new Node(0);data_node++;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    }

        // Traverse the B+ Tree
    else {
        Node* cursor = root;
        Node* parent;

        // Till cursor reaches the
        // leaf node
        while (!cursor->IS_LEAF) {

            parent = cursor;

            for (int i = 0;
                 i < cursor->size;
                 i++) {

                // If found the position
                // where we have to insert
                // node
                if (x < cursor->key[i]) {
                    cursor
                            = cursor->ptr[i];
                    break;
                }

                // If reaches the end
                if (i == cursor->size - 1) {
                    cursor
                            = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        if (cursor->size < cursor->degree) {
            int i = 0;
            while (x > cursor->key[i]
                   && i < cursor->size) {
                i++;
            }

            for (int j = cursor->size;
                 j > i; j--) {
                cursor->key[j]
                        = cursor->key[j - 1];
            }

            cursor->key[i] = x;
            cursor->size++;

            cursor->ptr[cursor->size]
                    = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = nullptr;
        }

        else {

            // Create a newLeaf node
            Node* newLeaf = new Node(0);data_node++;

            int virtualNode[MAX_LEAF];

            // Update cursor to virtual
            // node created
            for (int i = 0; i < MAX_LEAF; i++) {
                virtualNode[i]
                        = cursor->key[i];
            }
            int i = 0, j;

            // Traverse to find where the new
            // node is to be inserted
            while (x > virtualNode[i]
                   && i < MAX_LEAF) {
                i++;
            }

            // Update the current virtual
            // Node to its previous
            for (int k = MAX_LEAF;
                 k > i; k--) {
                virtualNode[k]
                        = virtualNode[k - 1];
            }

            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;

            cursor->size = (MAX_LEAF) / 2;
            newLeaf->size
                    = MAX_LEAF+1 - (MAX_LEAF) / 2;

            cursor->ptr[cursor->size]
                    = newLeaf;

            newLeaf->ptr[newLeaf->size]
                    = cursor->ptr[MAX_LEAF];

            cursor->ptr[MAX_LEAF] = nullptr;

            // Update the current virtual
            // Node's key to its previous
            for (i = 0;
                 i < cursor->size; i++) {
                cursor->key[i]
                        = virtualNode[i];
            }

            // Update the newLeaf key to
            // virtual Node
            for (i = 0, j = cursor->size;
                 i < newLeaf->size;
                 i++, j++) {
                newLeaf->key[i]
                        = virtualNode[j];
            }

            // If cursor is the root node
            if (cursor == root) {

                // Create a new Node
                Node* newRoot = new Node(1);index_node++;

                // Update rest field of
                // B+ Tree Node
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {

                // Recursive Call for
                // insert in internal
                insertInternal(newLeaf->key[0],
                               parent,
                               newLeaf);
            }
        }
    }
}

// Function to implement the Insert
// Internal Operation in B+ Tree
void BPTree::insertInternal(int x,
                            Node* cursor,
                            Node* child)
{

    // If we doesn't have overflow
    if (cursor->size < cursor->degree) {
        int i = 0;

        // Traverse the child node
        // for current cursor node
        while (x > cursor->key[i]
               && i < cursor->size) {
            i++;
        }

        // Traverse the cursor node
        // and update the current key
        // to its previous node key
        for (int j = cursor->size;
             j > i; j--) {

            cursor->key[j]
                    = cursor->key[j - 1];
        }

        // Traverse the cursor node
        // and update the current ptr
        // to its previous node ptr
        for (int j = cursor->size + 1;
             j > i + 1; j--) {
            cursor->ptr[j]
                    = cursor->ptr[j - 1];
        }

        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }

        // For overflow, break the node
    else {

        // For new Interval
        Node* newInternal = new Node(1);index_node++;
        int virtualKey[MAX_NODE+1];
        Node* virtualPtr[MAX_NODE + 2];

        // Insert the current list key
        // of cursor node to virtualKey
        for (int i = 0; i < MAX_NODE; i++) {
            virtualKey[i] = cursor->key[i];
        }

        // Insert the current list ptr
        // of cursor node to virtualPtr
        for (int i = 0; i < MAX_NODE+1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }

        int i = 0, j;

        // Traverse to find where the new
        // node is to be inserted
        while (x > virtualKey[i]
               && i < MAX_NODE) {
            i++;
        }

        // Traverse the virtualKey node
        // and update the current key
        // to its previous node key
        for (int k = MAX_NODE+1;
             k > i; k--) {

            virtualKey[k]
                    = virtualKey[k - 1];
        }

        virtualKey[i] = x;

        // Traverse the virtualKey node
        // and update the current ptr
        // to its previous node ptr
        for (int k = MAX_NODE+2;
             k > i + 1; k--) {
            virtualPtr[k]
                    = virtualPtr[k - 1];
        }

        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;

        cursor->size
                = (MAX_NODE) / 2;

        newInternal->size
                = MAX_NODE - (MAX_NODE) / 2;

        // Insert new node as an
        // internal node
        for (i = 0, j = cursor->size + 1;
             i < newInternal->size;
             i++, j++) {

            newInternal->key[i]
                    = virtualKey[j];
        }

        for (i = 0, j = cursor->size + 1;
             i < newInternal->size + 1;
             i++, j++) {

            newInternal->ptr[i]
                    = virtualPtr[j];
        }

        // If cursor is the root node
        if (cursor == root) {

            // Create a new root node
            Node* newRoot = new Node(1);index_node++;

            // Update key value
            newRoot->key[0]
                    = virtualKey[cursor->size];

            // Update rest field of
            // B+ Tree Node
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }

        else {

            // Recursive Call to insert
            // the data
            insertInternal(cursor->key[cursor->size],
                           findParent(root,
                                      cursor),
                           newInternal);
        }
    }
}

// Function to find the parent node
Node* BPTree::findParent(Node* cursor,
                         Node* child)
{
    Node* parent;

    // If cursor reaches the end of Tree
    if (cursor->IS_LEAF
        || (cursor->ptr[0])->IS_LEAF) {
        return nullptr;
    }

    // Traverse the current node with
    // all its child
    for (int i = 0;
         i < cursor->size + 1; i++) {

        // Update the parent for the
        // child Node
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }

            // Else recursively traverse to
            // find child node
        else {
            parent
                    = findParent(cursor->ptr[i],
                                 child);

            // If parent is found, then
            // return that parent node
            if (parent != nullptr)
                return parent;
        }
    }

    // Return parent node
    return parent;
}

// Function to get the root Node
Node* BPTree::getRoot()
{
    return root;
}
void Display(Node* a)
{
    cout<<index_node<<" "<<data_node<<" ";
    for(int i=0;i<a->size;i++)
    {
        std::cout<<a->key[i]<<" ";
    }
    std::cout<<std::endl;
}
// Driver Code
int main()
{
    int a,b;
    cin>>a>>b;
    MAX_LEAF=2*a;
    MAX_NODE=2*b+1;
    BPTree node;

    // Create B+ Tree
    int flag=1;
    while (flag==1)
    {
        int a;cin>>a;
        switch (a) {
            case 1: int n;cin>>n;node.insert(n);break;
            case 2:Display(node.getRoot()->ptr[1]->ptr[2]);break;
            default: flag=0;break;

        }
    }

    return 0;
}
