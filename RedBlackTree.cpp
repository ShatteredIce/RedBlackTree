//C++ Project 12 - RedBlackTree - 4/12/17
//Creates an red black tree

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <limits>
#include "RedBlackNode.h"

using namespace std;

//prototypes
void addRedBlackNode(RedBlackNode* & head, RedBlackNode* newNode);
void addRedBlackNodeRecursion(RedBlackNode* current, RedBlackNode* newNode);
void insertCase1(RedBlackNode* current);
void insertCase2(RedBlackNode* current);
void insertCase3(RedBlackNode* current);
void insertCase4(RedBlackNode* current);
void insertCase5(RedBlackNode* current);
void displayTree(RedBlackNode* current, int numSpaces);
void deleteTree(RedBlackNode* treeNode);
RedBlackNode* getGrandparent(RedBlackNode* current);
RedBlackNode* getUncle(RedBlackNode* current);
void getInput(char* input);
void trimWhitespace(char* text);

const int INPUT_SIZE = 201;

int main(){
  RedBlackNode* head = NULL;
  RedBlackNode* current = NULL;
  char input[INPUT_SIZE];
  char number[11];
  int copyIndex;

  cout << "\n-----RedBlack Tree v1.0-----\n";
  cout << "Creates a red black tree in the console\n";
  cout << "Enter 'file' to use a file as input or 'quit' to exit the program.\n";
  cout << "C++ Project 12 - Nathan Purwosumarto\n\n";

  //loop until user enters 'quit'
  while(true){
    cout << "Input Numbers: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "\nProgram Terminated." << endl;
      break;
    }
    //if the user inputs 'file', prompt for filename
    else if(strcmp(input, "file") == 0){
      cout << "Enter filename: ";
      getInput(input);
      fstream myfile(input);
      if (myfile.is_open()){
        //if file is found, copy contents into input
        myfile.getline(input, 501);
        trimWhitespace(input);
        cout << input << endl;
        myfile.close();
      }
      //tell the user if filename is invalid
      else{
        cout << "Unable to open file.\n\n";
        continue;
      }
    }
    //extracts numbers from the input char array one by one
    copyIndex = 0;
    fill(number, number + 11, ' ');
    for(int i = 0; i < strlen(input); i++){
      if(isdigit(input[i])){
        number[copyIndex] = input[i];
        copyIndex++;
      }
      //add the extracted number into the red black tree
      else if(copyIndex != 0){
        addRedBlackNode(head, new RedBlackNode(strtol(number, NULL, 10)));
        fill(number, number + 11, ' ');
        copyIndex = 0;
      }
    }
    //add the extracted number into the red black tree
    if(copyIndex != 0){
      addRedBlackNode(head, new RedBlackNode(strtol(number, NULL, 10)));
      fill(number, number + 11, ' ');
      copyIndex = 0;
    }
    //display the full binary search tree after all numbers have been added
    cout << "\nRed Black Tree (leftmost node is head): \n";
    displayTree(head, 0);

    //prompt the user if they want to modify the existing red black tree
    cout << "\nDo you wish to modify the red black tree? \nCommands: 'add', 'print' or 'next' to continue\n";
    while(!strcmp(input, "next") == 0){
      cout << "\nInput: ";
      getInput(input);
      //adds a number to the red black tree
      if(strcmp(input, "add") == 0){
        cout << "Input Numbers: ";
        getInput(input);
        //if the user inputs 'file', prompt for filename
        if(strcmp(input, "file") == 0){
          cout << "Enter filename: ";
          getInput(input);
          fstream myfile(input);
          if (myfile.is_open()){
            //if file is found, copy contents into input
            myfile.getline(input, 501);
            trimWhitespace(input);
            cout << input << endl;
            myfile.close();
          }
          //tell the user if filename is invalid
          else{
            cout << "Unable to open file.\n\n";
            continue;
          }
        }
        //extracts numbers from the input char array one by one
        copyIndex = 0;
        fill(number, number + 11, ' ');
        for(int i = 0; i < strlen(input); i++){
          if(isdigit(input[i])){
            number[copyIndex] = input[i];
            copyIndex++;
          }
          //add the extracted number into the red black tree
          else if(copyIndex != 0){
            addRedBlackNode(head, new RedBlackNode(strtol(number, NULL, 10)));
            fill(number, number + 11, ' ');
            copyIndex = 0;
          }
        }
        //add the extracted number into the red black tree
        if(copyIndex != 0){
          addRedBlackNode(head, new RedBlackNode(strtol(number, NULL, 10)));
          fill(number, number + 11, ' ');
          copyIndex = 0;
        }
      }
      //displays the redblack tree
      else if(strcmp(input, "print") == 0){
        cout << "Red Black Tree (leftmost node is head): \n";
        displayTree(head, 0);
      }
      else if(!strcmp(input, "next") == 0){
        cout << "<Invalid Input>\n";
      }
    }
    //delete the tree to avoid memory leak when the head is set to another new RedBlackNode
    if(head != NULL){
      deleteTree(head);
      head = NULL;
    }
    cout << endl;
  }
  return 0;
}

//gets the grandparent node of a RedBlackNode
RedBlackNode* getGrandparent(RedBlackNode* current){
  if ((current != NULL) && (current->getParent() != NULL)){
    return current->getParent()->getParent();
  }
  else{
    return NULL;
  }
}

//gets the uncle node of a RedBlackNode
RedBlackNode* getUncle(RedBlackNode* current){
  RedBlackNode* g = getGrandparent(current);
   if (g == NULL){
    return NULL;
  }
  if(current->getParent() == g->getLeftChild()){
    return g->getRightChild();
  }
  else{
    return g->getLeftChild();
  }
}

//adds a RedBlack node to the tree
void addRedBlackNode(RedBlackNode* & head, RedBlackNode* newNode){
  if(head == NULL){
    head = newNode;
  }
  else{
    addRedBlackNodeRecursion(head, newNode);
  }
  insertCase1(newNode);
  while(head->getParent() != NULL){
    cout << head->getValue() << endl;
    head = head->getParent();
  }
}

//recursively called to add a redblack node to the tree once the head is checked and found to be not null
void addRedBlackNodeRecursion(RedBlackNode* current, RedBlackNode* newNode){
  //if child value is greater or equal to parent value, go down the right branch
  if(newNode->getValue() >= current->getValue()){
    if(current->getRightChild() != NULL){
      addRedBlackNodeRecursion(current->getRightChild(), newNode);
    }
    else{
      newNode->setParent(current);
      current->setRightChild(newNode);
    }
  }
  //if child value is less than parent value, go down the left branch
  else{
    if(current->getLeftChild() != NULL){
      addRedBlackNodeRecursion(current->getLeftChild(), newNode);
    }
    else{
      newNode->setParent(current);
      current->setLeftChild(newNode);
    }
  }
}

//if the node entered is the head, color it black
void insertCase1(RedBlackNode* current){
  if (current->getParent() == NULL){
    current->setBlack(true);
  }
  else{
    insertCase2(current);
  }
}

//if parent is black, then none of the properties are violated
void insertCase2(RedBlackNode* current){
  if(current->getParent()->getIsBlack() == true){
    return;
  }
  else{
    insertCase3(current);
  }
}

//If both the parent and the uncle are red, then both of them are repainted black and the grandparent is painted red
void insertCase3(RedBlackNode* current){
  RedBlackNode* g = getGrandparent(current);
  RedBlackNode* u = getUncle(current);
  if ((u != NULL) && (u->getIsBlack() == false)) {
    current->getParent()->setBlack(true);
    u->setBlack(true);
    g->setBlack(false);
    insertCase1(g);
  }
  else {
    insertCase4(current);
  }
}

void insertCase4(RedBlackNode* current){
  RedBlackNode* g = getGrandparent(current);
  if ((current == current->getParent()->getRightChild()) && (current->getParent() == g->getLeftChild())) {
    RedBlackNode* saved_p = g->getLeftChild();
    RedBlackNode* saved_current_left = current->getLeftChild();
    g->setLeftChild(current);
    current->setParent(g);
    current->setLeftChild(saved_p);
    saved_p->setParent(current);
    saved_p->setRightChild(saved_current_left);
    if(saved_current_left != NULL){
      saved_current_left->setParent(saved_p);
    }
    current = current->getLeftChild();

  }
  else if ((current == current->getParent()->getLeftChild()) && (current->getParent() == g->getRightChild())) {
    RedBlackNode* saved_p = g->getRightChild();
    RedBlackNode* saved_current_right = current->getRightChild();
    g->setRightChild(current);
    current->setParent(g);
    current->setRightChild(saved_p);
    saved_p->setParent(current);
    saved_p->setLeftChild(saved_current_right);
    if(saved_current_right != NULL){
      saved_current_right->setParent(saved_p);
    }
    current = current->getRightChild();
  }
  insertCase5(current);
}

void insertCase5(RedBlackNode* current){
  RedBlackNode* g = getGrandparent(current);
  current->getParent()->setBlack(true);
  g->setBlack(false);
  if (current == current->getParent()->getLeftChild()){
    RedBlackNode* saved_parent_right = current->getParent()->getRightChild();
    current->getParent()->setRightChild(g);
    current->getParent()->setParent(g->getParent());

    if(g->getParent() != NULL){
      if(g->getParent()->getLeftChild() == g){
        g->getParent()->setLeftChild(current->getParent());
      }
      else{
        g->getParent()->setRightChild(current->getParent());
      }
    }

    g->setParent(current->getParent());
    g->setLeftChild(saved_parent_right);
    if(saved_parent_right != NULL){
      saved_parent_right->setParent(g);
    }
  }
  else{
    RedBlackNode* saved_parent_left = current->getParent()->getLeftChild();
    current->getParent()->setLeftChild(g);
    current->getParent()->setParent(g->getParent());

    if(g->getParent() != NULL){
      if(g->getParent()->getLeftChild() == g){
        g->getParent()->setLeftChild(current->getParent());
      }
      else{
        g->getParent()->setRightChild(current->getParent());
      }
    }

    g->setParent(current->getParent());
    g->setRightChild(saved_parent_left);
    if(saved_parent_left != NULL){
      saved_parent_left->setParent(g);
    }
  }
}

//prints out the redblack tree to the console
void displayTree(RedBlackNode* head, int numSpaces){
  if(head == NULL){
    return;
  }
  if(head->getRightChild() != NULL){
    displayTree(head->getRightChild(), numSpaces+1);
  }
  for(int i = 0; i < numSpaces; i++){
    cout << "     ";
  }
  cout << head->getValue();
  if(head->getIsBlack()){
    cout << "(B)" << endl;
  }
  else{
    cout << "(R)" << endl;
  }
  if(head->getLeftChild() != NULL){
    displayTree(head->getLeftChild(), numSpaces+1);
  }
}

//deletes all nodes in a red black tree
void deleteTree(RedBlackNode* treeNode){
  if(treeNode->getRightChild() != NULL){
    deleteTree(treeNode->getRightChild());
    treeNode->setRightChild(NULL);
  }
  if(treeNode->getLeftChild() != NULL){
    deleteTree(treeNode->getLeftChild());
    treeNode->setLeftChild(NULL);
  }
  delete treeNode;
  //treeNode = NULL;
}

//stores user input into a char*
void getInput(char* input){
  fill(input, input + INPUT_SIZE, ' ');
  cin.getline(input, INPUT_SIZE);
  trimWhitespace(input);
}

//remove extra whitespaces to make sure input is compared as intended
void trimWhitespace(char* text){
  char* newText = text;
  char lastChar = ' ';
  while(*text != '\0'){
    if(!(*text == ' ' && lastChar == ' ')){
      *newText = *text;
      lastChar = *text;
      newText++;
    }
    text++;
  }
  if(*(newText-1) != ' '){
    *newText = '\0';
  }
  else{
    *(newText-1) = '\0';
  }
}
