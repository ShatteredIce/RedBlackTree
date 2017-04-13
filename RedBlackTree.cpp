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
void displayTree(RedBlackNode* current, int numSpaces);

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
      addRedBlackNode(head, new RedBlackTree(strtol(number, NULL, 10)));
      fill(number, number + 11, ' ');
      copyIndex = 0;
    }
    //display the full binary search tree after all numbers have been added
    cout << "\Red Black Tree (leftmost node is head): \n";
    displayTree(head, 0);
  }
  return 0;
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
