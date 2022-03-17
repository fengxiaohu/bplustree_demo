#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int MAX=3;

class Node
{
private:
    bool IS_LEAF;
    int *key;
    int size;
    Node **ptr; // pointer tio the child node 
    friend class BPtree;
public:
    Node();
    ~Node();
};

Node::Node()
{
    key = new int[MAX];
    ptr = new Node *[MAX+1];
    
}



class BPtree
{

  private:  
  Node *root;
  void insertInternal(int,Node *,Node *);
  Node *finedParent(Node *,Node *);

  public:
  BPtree();
  void insert(int);
  void search(int);
  void display(Node *);
  Node *getRoot();
  
  
};
BPtree::BPtree()
{
    root = NULL;
}

// search a node in b+ tree(considering the binary search)
// 1. judge the range of target search value in BPtree.
//    compare with the Node x's value:x_value, if key smaller than x_value,go left child: x[i]
//    else compare with next child node until we reach the end of child list(ptr[MAX]).
void BPtree::search(int key)
{
    if(root == NULL)
    {
        cout <<"b plus tree is empty"<<endl;
    }
    else
    {
        Node *cursor = root;
        while(cursor->IS_LEAF == false)
        {
            for(int i=0;i<cursor->size;i++)
            {
                if(key<cursor->key[i])
                {
                    cursor = cursor->ptr[i];
                    break;
                }
                if(i == cursor->size-1) // reach the end subtree, go to rightest subtree
                {
                    cursor = cursor->ptr[i+1];
                    break;
                }
                
            }
        }
        
        // we reach the realted root child list
        for(int i=0;i<cursor->size;i++)
        {
            if(cursor->key[i] == key)
            {
                cout << "Found\n";
                return;
            }
            
        }
        cout << "Not found\n";



    }
}
// 1.tree is empoty, we need to rebuild the root Node
// 2. find the right place to insert value and check if we need to reblance tree


void BPtree::insert(int value)
{
    if(root == NULL)
    {
        root = new Node;
        root->key[0] = value;
        root->size = 1;
        root->IS_LEAF = true;
    }
    else
    {
        Node *cursor = root;
        Node *parent;
        // find the parent node location
        while(!cursor->IS_LEAF)
        {
            parent = cursor;
            for(int i=0;i<cursor->size;i++)
            {
                if(cursor->key[i]>value)
                {
                    cursor = cursor->ptr[i];
                    break;
                }
                else if (i == (cursor->size-1))
                {
                    cursor = cursor->ptr[i+1];
                    break;
                }
                else {} // we do nothing,just let i increase
    
            }
        }
        // now we need to find right place to insert,cursor is leaf node now
        // 
        if(cursor->size<MAX)
        {
            int i=0;
            // find place to insert
            while(cursor->key[i]<value && i<cursor->size)
            {
                i++;
            }
            for(int j=cursor->size;j>i;j--)
            {
                cursor->key[j] = cursor->key[j-1];
            }
            // insert and remove the elements after i
            cursor->size++;
            cursor->key[i] = value;
            // 
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
            cursor->ptr[cursor->size-1] = NULL;
            
        }
        else
        {
            Node *newleaf = new Node;
            int tempnode[MAX+1]; // temp array to store value
            for(int i=0;i<cursor->sizel;i++)
            {
                tempnode[i] = cursor.key[i];
            }
            int i=0
            int j;
            while(x > tempnode[i] && i < MAX)
            {
                i++;
            }
            for(int j= MAX+1;j>i;j--)
            {
                tempnode[j] = tempnode[j-1];
            }
            tempnode[i] = value;
            newleaf->IS_LEAF = true;
            cursor->size = (MAX+1)/2;
            newleaf->size = MAX+1 - ((MAX+1)/2);
            // connect the newleaf with cursor
            cursor->ptr[cursor->size] = newleaf;
            newleaf->ptr[newleaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = NULL;
            // 
            for(i=0;i<cursor->size;i++)
            {
                cursor->key[i] = tempnode[i];
            }
            for(int j=cursor->size,i=0;i<newleaf->size;i++,j++)
            {
                newleaf->key[i] = tempnode[j];
            }
            if(cursor == root)
            {
                
            }
            else{
                insertInternal(newleaf->key[0],parent,newleaf);
            }
            
            
            
            

        }

    }
    



}

void BPtree::insertInternal(int value,Node *cursor,Node *child)
{
    if(cursor->size < MAX)
    {
        int i=0;
        while(value > cursor->key[i] && i<cursor->size )
        {
            i++;
        }
        // remove the element and ptr at the same time when we deal the nonleaf node
        for (int j = cursor->size; j > i; j--) {
        cursor->key[j] = cursor->key[j - 1];
        }
        for(int j= cursor->size+1;j>i+1;j--)
        {
            cursor->ptr[i] = cursor->ptr[i-1];
        }
        cursor->key[i] = value;
        cursor->size++;
        cursor->ptr[i+1] = child;

        
    }
    /*
    If the leaf is full, insert the key into the leaf node in increasing order and balance the tree in the following way.
    Break the node at m/2th position.
    Add m/2th key to the parent node as well.
    If the parent node is already full, follow steps 2 to 3.
    */
    else
    {
        Node *newInternal = new Node;
        int virtualKey[MAX+1];
        Node *virtualPtr[MAX+2];
        for(int i=0;i<MAX;i++)
        {
            virtualKey[i] = cursor->ptr[i];
        }
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
            }
            for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
            }
        
        int i=0;
        while(value > cursor->key[i] && i<cursor->size )
        {
            i++;
        }
        for(int j=MAX+1;j>i;j--)
        {
            virtualKey[j] = virtualKey[j-1];

        }
        virtualKey[i] = value;
        for(int j = MAX+2.j>i+1;j--)
        {
            virtualPtr[j] = virtualPtr[j-1];
        }
        virtualPtr[i+1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX+1)/2;
        newInternal->size = MAX - (MAX+1)/2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
        newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
        newInternal->ptr[i] = virtualPtr[j];
        }

        if(cursor == root)
        {
            Node *newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
            
        }
        else
        {
            insertInternal(cursor->key[cursor->size],finedParent(root,cursor),newInternal);
        }

        

    }
    
}
Node *BPtree::finedParent(Node *cursor,Node *child)
{
    Node *parent = new Node;
    if(cursor->IS_LEAF || cursor->ptr[0]->IS_LEAF)
    {
        return NULL;
    }
    for(int i=0;i<cursor->size;i++)
    {
        if(cursor->key[i] == child)
        {
            parent = cursor;
            return parent;
        }
        else
        {
            parent = finedParent(cursor->ptr[i],child);
            if(parent !=NULL)
            return parent;
        }
        
    }
    return parent;
}

void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

Node * BPtree::getRoot()
{
    return this->root;
}


int main() {
  BPTree node;
  node.insert(5);
  node.insert(15);
  node.insert(25);
  node.insert(35);
  node.insert(45);
  node.insert(55);
  node.insert(40);
  node.insert(30);
  node.insert(20);
  node.display(node.getRoot());

  node.search(15);
}
