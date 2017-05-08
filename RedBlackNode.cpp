//RedBlackNode class for creating red-black trees
#include <iostream>
#include <string.h>
#include "RedBlackNode.h"

using namespace std;

//Constructor: stores a char, sets childs and parents to NULL
RedBlackNode::RedBlackNode(int newValue){
  value = newValue;
  leftchild = NULL;
  rightchild = NULL;
  parent = NULL;
  isBlack = false;
}

//returns the value stored in the node
int RedBlackNode::getValue(){
  return value;
}

void RedBlackNode::setValue(int newValue){
    value = newValue;
}

//sets the leftchild of this node
void RedBlackNode::setLeftChild(RedBlackNode* newNode){
  leftchild = newNode;
}

//sets the rightchild of this node
void RedBlackNode::setRightChild(RedBlackNode* newNode){
 rightchild = newNode;
}

//sets the parent of this node
void RedBlackNode::setParent(RedBlackNode* newNode){
 parent = newNode;
}

//gets the leftchild of the node, may be null
RedBlackNode* RedBlackNode::getLeftChild(){
  return leftchild;
}

//gets the rightchild of the node, may be null
RedBlackNode* RedBlackNode::getRightChild(){
  return rightchild;
}

//gets the parent of the node, may be null
RedBlackNode* RedBlackNode::getParent(){
  return parent;
}

//gets the node color, returns true if black and false if red
bool RedBlackNode::getIsBlack(){
  return isBlack;
}

//sets the node's color
void RedBlackNode::setBlack(bool b){
  isBlack = b;
}
