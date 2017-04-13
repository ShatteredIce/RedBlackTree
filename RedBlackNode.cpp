//RedBlackNode class for creating red-black trees
#include <iostream>
#include <string.h>
#include "RedBlackNode.h"

using namespace std;

//Constructor: stores a char, sets childs and parents to NULL
BinaryNode::BinaryNode(char newToken){
  token = new char[9];
  fill(token, token + 9, NULL);
  token[0] = newToken;
  leftchild = NULL;
  rightchild = NULL;
  parent = NULL;
  isBlack = false;
}

//returns the char array stored in the node
char* BinaryNode::getValue(){
  return token;
}

//adds a token to the end of the char array
void BinaryNode::addToken(char newToken){
  token[strlen(token)] = newToken;
}

 //sets the leftchild of this node
void BinaryNode::setLeftChild(BinaryNode* newNode){
  leftchild = newNode;
}

//sets the rightchild of this node
void BinaryNode::setRightChild(BinaryNode* newNode){
 rightchild = newNode;
}

//sets the parent of this node
void BinaryNode::setParent(BinaryNode* newNode){
 parent = newNode;
}

//gets the leftchild of the node, may be null
BinaryNode* BinaryNode::getLeftChild(){
  return leftchild;
}

//gets the rightchild of the node, may be null
BinaryNode* BinaryNode::getRightChild(){
  return rightchild;
}

//gets the parent of the node, may be null
BinaryNode* BinaryNode::getParent(){
  return parent;
}

//sets the node's color
void setBlack(boolean b){
  isBlack = b;
}
