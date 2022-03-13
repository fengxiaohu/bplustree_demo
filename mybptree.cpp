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
    Node **ptr;
    friend class BPtree;
public:
    Node();
    ~Node();
};

Node::Node()
{
    key = 
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

