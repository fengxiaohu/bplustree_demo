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
  Node *frinedParent(Node *,Node *);

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
//    else go to its right child x[i+1]
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
                    if(cursor->key[i] == x)
                    {
                        count << "Found \n";
                    }
                }
            }
        }
    }
}

