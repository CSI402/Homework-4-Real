//Functions for the Binary Search Tree

#include "BSTStruct.h"
#include "BSTPrototypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function to create a BST from a given file name, returns the root of the BST
pnode fileToBST(char *fileName){

  //Declare a FILE pointer variable
  FILE *fp;

  //If given file cannot be opened, print error message and stop
  if((fp = fopen(fileName, "r"))== NULL){
    fprintf(stderr, "Error: File %s cannot be opened.\n", fileName);
    return NULL;
  }

  //Delcare local variables
  char line[100]; //Each line of the file
  char *token; //For strtok function and strtoul function
  char instruction[6]; //Each instruction
  unsigned int opcode; //Each opcode
  unsigned int opFormat; //Each opcode format
  pnode root = NULL;

  //Iterate through file, line by line
  while(fgets(line, sizeof(line), fp) != NULL){

    //Get the first token
    token = strtok(line, " ");
    //Initialize instruction
    strcpy(instruction, token);
    instruction[6] = '\0';

    //Get the next token
    token = strtok(NULL, " ");
    //Initialize opcode
    opcode = strtoul(token, &token, 10);

    //Advance token
    token += sizeof(char);
    //Initialize opFormat
    opFormat = strtoul(token, &token, 10);

    //Insert the node into the BST and set the root
    root = insertNode(root, instruction, opcode, opFormat);
  }

  //Close the file
  fclose(fp);

  //Return the BST's root
  return root;
}

//Function to create a new node, returns the new node
pnode createNode(char instruction[6], unsigned int opcode, unsigned int opFormat){

  //Allocate memory for the new node
  pnode newNode = (pnode)malloc(sizeof(node));

  //If memory allocation fails, print error and stop
  if(newNode == NULL){
    fprintf(stderr, "Error: Memory allocation error. (createNode)\n");
    return NULL;
  }

  //Copy all the respective values to the new node
  memcpy(newNode->instruction, instruction, 6);
  newNode->opcode = opcode;
  newNode->opFormat = opFormat;
  //left and right nodes point to null
  newNode->leftNode = NULL;
  newNode->rightNode = NULL;

  return newNode;
}

//Function to insert a new node into the BST, returns the new BST's root
pnode insertNode(pnode root, char instruction[6], unsigned int opcode, unsigned int opFormat){
  //If the root is null, just add the new node
  if (root == NULL)
    root = createNode(instruction, opcode, opFormat);

  //Otherwise, add the node in the correct place
  else{
    //Declare local variables
    int isLeft; //If the node to insert is left, 0, otherwise, 1
    int result = 0; //Result of the comparison
    pnode cursor = root; //Current node
    pnode prev = NULL; //Previous node

    //Iterate through the nodes of the tree to find the right position for the new node
    while (cursor != NULL){
      result = strcmp(cursor->instruction, instruction);
      prev = cursor;

      //If the node to be inserted > cursor, iterate on the right sub tree
      if (result >= 0){
        isLeft = 1;
        cursor = cursor->leftNode;
      }
       //If the node to be inserted < cursor, iterate on the left sub tree
      else{
        isLeft = 0;
        cursor = cursor->rightNode;
      }
    }

    //Now at a leaf, we can just create a new node and add it at the right spot
    if(isLeft)
      prev->leftNode = createNode(instruction, opcode, opFormat);
    else
      prev->rightNode = createNode(instruction, opcode, opFormat);
  }

  //Return the new BST root
  return root;
}

//Function to search through the BST for an instruction, returns the node pointer
pnode search(pnode root, char instruction[6]){

  //If the root is null, the BST is null, so return null
  if (root == NULL)
    return NULL;

  int result;
  pnode cursor = root;

  //Iterate through the BST, comparing the instructions
  while(cursor != NULL){

    result = strcmp(instruction, root->instruction);

    //If the instruction to search < cursor's, iterate on the left sub tree
    if(result < 0)
      cursor = cursor->leftNode;
    //If the instruction to search > cursor's, iterate on the right sub tree
    else if(result > 0)
      cursor = cursor->rightNode;
    else
      return cursor;
  }

  //If the instruction is never found, this will return null
  return cursor;
}

//Function to print an in order traversal of the BST
void printTree(pnode root){

  //As long as the root isn't null, print it in order
  if(root != NULL){
    printTree(root->leftNode); //First left side
    printf("%s\n", root->instruction);
    printTree(root->rightNode); //Then right side
  }
}

//Function to remove all the nodes from the BST
void freeTree(pnode root){

  //As long as the tree isn't already null, free each node recursively
  if(root != NULL){
    freeTree(root->rightNode);
    freeTree(root->leftNode);
    free(root);
  }
}
