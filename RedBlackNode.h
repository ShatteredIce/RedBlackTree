//Header file for RedBlackNode.cpp
//Node for an redblack tree, stores int* value, Node* leftchild, Node* rightchild, Node* parent

#include <iostream>

using namespace std;

class RedBlackNode {
 public:
  RedBlackNode(int); //constructor
  int getValue(); //returns the value stored in the node
  void setLeftChild(RedBlackNode*); //sets the left child of the node
  void setRightChild(RedBlackNode*); //sets the right child of the node
  void setParent(RedBlackNode*); //sets the parent of the node
  RedBlackNode* getLeftChild(); //gets the leftchild of the node, may be null
  RedBlackNode* getRightChild(); //gets the rightchild of the node, may be null
  RedBlackNode* getParent();  //gets the parent of the node, may be null
  bool getIsBlack(); //gets the node color, returns true if black and false if red
  void setBlack(bool); //sets the node's color
 protected:
  int value;
  bool isBlack;
  RedBlackNode* leftchild;
  RedBlackNode* rightchild;
  RedBlackNode* parent;
};
