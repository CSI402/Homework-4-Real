/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Main worker function
*/

#include <stdio.h>
#include <stdlib.h>
#include "BSTStruct.h"
#include "BSTPrototypes.h"

int main(int argc, char *argv[]){

  //If not 4 command line args, print error message and stop
  if (argc != 4){
    fprintf(stderr, "Error: Invalid number of command line arguments.\n");
    return 0;
  }

  //Convert the instruction set opcode file to a binary search tree
  pnode root = fileToBST(argv[1]);
  //Print an inorder traversal of the BST
  printTree(root);

  return 0;
}

