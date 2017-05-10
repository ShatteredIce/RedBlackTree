//C++ Project 12 - RedBlackTree - 4/12/17
//Creates an red black tree in the console

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
void deleteRedBlackNode(RedBlackNode* current);
void deleteCase1(RedBlackNode* current);
void deleteCase2(RedBlackNode* current);
void deleteCase3(RedBlackNode* current);
void deleteCase4(RedBlackNode* current);
void deleteCase5(RedBlackNode* current);
void deleteCase6(RedBlackNode* current);
void displayTree(RedBlackNode* current, int numSpaces);
RedBlackNode* searchTree(RedBlackNode* current, int value);
void deleteTree(RedBlackNode* treeNode);
RedBlackNode* getGrandparent(RedBlackNode* current);
RedBlackNode* getUncle(RedBlackNode* current);
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);

const int INPUT_SIZE = 201;

int main(){
  RedBlackNode* head = NULL;
  RedBlackNode* current = NULL;
  char input[INPUT_SIZE];
  char number[11];
  int copyIndex;
  int searchNumber;

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
    //display the full red black tree after all numbers have been added
    cout << "\nRed Black Tree (leftmost node is head): \n";
    displayTree(head, 0);

    //prompt the user if they want to modify the existing red black tree
    cout << "\nDo you wish to modify the red black tree? \nCommands: 'add', 'search', 'print' or 'next' to continue\n";
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
      //searches the red black tree for a node
      else if(strcmp(input, "search") == 0){
        searchNumber = getInt("Enter number to search for: ");
        cin.ignore();
        if(searchTree(head, searchNumber)){
          cout << "The value '" << searchNumber << "' exists in the tree\n";
        }
        else{
          cout << "The value '" << searchNumber << "' does not exist in the tree\n";
        }
      }
      //deletes a value from the red black tree
      else if(strcmp(input, "delete") == 0){
        searchNumber = getInt("Enter number to delete: ");
        cin.ignore();
        if(searchTree(head, searchNumber)){
          deleteRedBlackNode(searchTree(head, searchNumber));
        }
        else{
          cout << "The value '" << searchNumber << "' does not exist in the tree\n";
        }
      }
      //displays the red black tree
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

//gets the sibling node of a RedBlackNode
RedBlackNode* getSibling(RedBlackNode* current){
  //no parent means no sibling
  if(current == NULL || current->getParent() == NULL){
    return NULL;
  }
  if (current == current->getParent()->getLeftChild()){
    return current->getParent()->getRightChild();
  }
  else{
    return current->getParent()->getLeftChild();
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
  //The current node is a right child, and its parent is a left child
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
  //The current node is a left child, and its parent is a right child
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
  //The current node and its parent are both left children
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
  //The current node and its parent are both right children
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

//deletes a RedBlack node from the tree
void deleteRedBlackNode(RedBlackNode* current){
  RedBlackNode* successor = current;
  //finds successor node
  if(current->getRightChild() != NULL){
    successor = current->getRightChild();
    while(successor->getLeftChild() != NULL){
      successor = successor->getLeftChild();
    }
  }
  //swaps values of successor and original node
  int temp = successor->getValue();
  successor->setValue(current->getValue());
  current->setValue(successor->getValue());
  //if successor is black
  if(successor->getIsBlack()){
    //if child is not black, set it to black
    if (successor->getRightChild() != NULL && successor->getRightChild()->getIsBlack() == false){
      successor->getRightChild()->setBlack(true);
    }
    //if both successor and child are black
    else{
     deleteCase1(successor->getRightChild());
    }
  }
  if(successor == successor->getParent()->getLeftChild()){
    successor->getParent()->setLeftChild(successor->getRightChild());
  }
  else{
    successor->getParent()->setRightChild(successor->getRightChild());
  }
  if(successor->getRightChild()){
      successor->getRightChild()->setParent(successor->getParent());
  }
  delete successor;
}

void deleteCase1(RedBlackNode* current){
  cout << "del case 1\n";
  if (current == NULL || current->getParent() != NULL){
    deleteCase2(current);
  }
}

//if sibling is red
void deleteCase2(RedBlackNode* current){
  cout << "del case 2\n";
  RedBlackNode* s = getSibling(current);
  if (s != NULL && s->getIsBlack() == false) {
    current->getParent()->setBlack(false);
    s->setBlack(true);
    //rotate left
    if (current == current->getParent()->getLeftChild()){
      RedBlackNode* saved_p = current->getParent();
      RedBlackNode* saved_s_left = s->getLeftChild();
      if(saved_p->getParent() != NULL){
        if(saved_p == saved_p->getParent()->getLeftChild()){
          saved_p->getParent()->setLeftChild(s);
        }
        else{
          saved_p->getParent()->setRightChild(s);
        }
      }
      s->setParent(saved_p->getParent());
      s->setLeftChild(saved_p);
      saved_p->setParent(s);
      if(saved_s_left != NULL){
        saved_s_left->setParent(saved_p);
      }
      saved_p->setRightChild(saved_s_left);
    }
    //rotate right
    else{
      RedBlackNode* saved_p = current->getParent();
      RedBlackNode* saved_s_right = s->getRightChild();
      if(saved_p->getParent() != NULL){
        if(saved_p == saved_p->getParent()->getLeftChild()){
          saved_p->getParent()->setLeftChild(s);
        }
        else{
          saved_p->getParent()->setRightChild(s);
        }
      }
      s->setParent(saved_p->getParent());
      s->setRightChild(saved_p);
      saved_p->setParent(s);
      if(saved_s_right != NULL){
        saved_s_right->setParent(saved_p);
      }
      saved_p->setLeftChild(saved_s_right);
    }
 }
  deleteCase3(current);
}

//if parent, sibling, and sibling's children are all black
void deleteCase3(RedBlackNode* current){
  cout << "del case 3\n";
  RedBlackNode* s = getSibling(current);
  if ((current->getParent()->getIsBlack()) && (s->getIsBlack()) && (s->getLeftChild()->getIsBlack()) && (s->getRightChild()->getIsBlack())) {
    s->setBlack(false);
    deleteCase1(current->getParent());
  }
  else
    deleteCase4(current);
}

//if sibling and sibling's children are black but parent is red
void deleteCase4(RedBlackNode* current){
  cout << "del case 4\n";
  RedBlackNode* s = getSibling(current);
  if ((!current->getParent()->getIsBlack()) && (s->getIsBlack()) && (s->getLeftChild()->getIsBlack()) && (s->getRightChild()->getIsBlack())){
    s->setBlack(false);
    current->getParent()->setBlack(true);
  }
  else
    deleteCase5(current);
}

void deleteCase5(RedBlackNode* current){
  cout << "del case 5\n";
  RedBlackNode* s = getSibling(current);

  if (s->getIsBlack()) {
    if ((current == current->getParent()->getLeftChild()) && (s->getRightChild()->getIsBlack()) && (!s->getLeftChild()->getIsBlack())){
      s->setBlack(false);
      s->getLeftChild()->setBlack(true);
      //rotate right
      RedBlackNode* saved_sl_right = s->getLeftChild()->getRightChild();
      current->getParent()->setRightChild(s->getLeftChild());
      s->getLeftChild()->setParent(current->getParent());
      s->getLeftChild()->setRightChild(s);
      s->setParent(s->getLeftChild());
      s->setLeftChild(saved_sl_right);
      saved_sl_right->setParent(s);

    }
    else if ((current == current->getParent()->getRightChild()) && (s->getLeftChild()->getIsBlack()) && (!s->getRightChild()->getIsBlack())){
      s->setBlack(false);
      s->getRightChild()->setBlack(true);
      //rotate left
      RedBlackNode* saved_sl_left = s->getRightChild()->getLeftChild();
      current->getParent()->setLeftChild(s->getRightChild());
      s->getRightChild()->setParent(current->getParent());
      s->getRightChild()->setLeftChild(s);
      s->setParent(s->getRightChild());
      s->setRightChild(saved_sl_left);
      saved_sl_left->setParent(s);
    }
  }
  deleteCase6(current);
}

void deleteCase6(RedBlackNode* current){
  cout << "del case 6\n";
  RedBlackNode* s = getSibling(current);
  s->setBlack(current->getParent()->getIsBlack());
  current->getParent()->setBlack(true);
  if (current == current->getParent()->getLeftChild()) {
    s->getRightChild()->setBlack(true);
    //rotate left
    RedBlackNode* saved_p = current->getParent();
    RedBlackNode* saved_s_left = s->getLeftChild();
    if(saved_p->getParent() != NULL){
      if(saved_p == saved_p->getParent()->getLeftChild()){
        saved_p->getParent()->setLeftChild(s);
      }
      else{
        saved_p->getParent()->setRightChild(s);
      }
    }
    s->setParent(saved_p->getParent());
    s->setLeftChild(saved_p);
    saved_p->setParent(s);
    if(saved_s_left != NULL){
      saved_s_left->setParent(saved_p);
    }
    saved_p->setRightChild(saved_s_left);
  }
  else {
    s->getLeftChild()->setBlack(true);
    //rotate right
    RedBlackNode* saved_p = current->getParent();
    RedBlackNode* saved_s_right = s->getRightChild();
    if(saved_p->getParent() != NULL){
      if(saved_p == saved_p->getParent()->getLeftChild()){
        saved_p->getParent()->setLeftChild(s);
      }
      else{
        saved_p->getParent()->setRightChild(s);
      }
    }
    s->setParent(saved_p->getParent());
    s->setRightChild(saved_p);
    saved_p->setParent(s);
    if(saved_s_right != NULL){
      saved_s_right->setParent(saved_p);
    }
    saved_p->setLeftChild(saved_s_right);
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

RedBlackNode* searchTree(RedBlackNode* current, int value){
  if(current == NULL){
    return NULL;
  }
  else if(current->getValue() == value){
    return current;
  }
  //go down the right branch
  else if(current->getValue() < value){
    return searchTree(current->getRightChild(), value);
  }
  else{
    return searchTree(current->getLeftChild(), value);
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

//prompts the user for an integer
int getInt(char* message){
  int number;
  bool valid = false;
  while (!valid){
    cout << message;
    cin >> number;
    //delete excess whitespace
    while (cin.peek() == ' '){
      cin.ignore(1);
    }
    if(cin.peek() != '\n'){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else{
      valid = true;
    }
  }
  return number;
}
