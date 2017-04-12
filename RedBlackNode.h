//Header file for RedBlackNode.cpp
//Node for an redblack tree, stores int* value, Node* leftchild, Node* rightchild, Node* parent

#include <iostream>

using namespace std;

class RedBlackNode {
 public:
  RedBlackNode(char); //constructor
  char* getValue(); //returns the char array stored in the node
  void addToken(char); //adds a digit to the end of the char array
  void setLeftChild(BinaryNode*); //sets the left child of the node
  void setRightChild(BinaryNode*); //sets the right child of the node
  void setParent(BinaryNode*); //sets the parent of the node
  BinaryNode* getLeftChild(); //gets the leftchild of the node, may be null
  BinaryNode* getRightChild(); //gets the rightchild of the node, may be null
  BinaryNode* getRightChild();  //gets the parent of the node, may be null
 protected:
  char* token;
  BinaryNode* leftchild;
  BinaryNode* rightchild;
  BinaryNode* parent;
};
