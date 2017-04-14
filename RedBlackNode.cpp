//RedBlackNode class for creating red-black trees
#include <iostream>
#include <string.h>
#include "RedBlackNode.h"

using namespace std;

//Constructor: stores a char, sets childs and parents to NULL
RedBlackNode::RedBlackNode(char newToken){
  token = new char[9];
  fill(token, token + 9, NULL);
  token[0] = newToken;
  leftchild = NULL;
  rightchild = NULL;
  parent = NULL;
  isBlack = false;
}

//returns the char array stored in the node
char* RedBlackNode::getValue(){
  return token;
}

//adds a token to the end of the char array
void RedBlackNode::addToken(char newToken){
  token[strlen(token)] = newToken;
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

//sets the node's color
void RedBlackNode::setBlack(bool b){
  isBlack = b;
}
