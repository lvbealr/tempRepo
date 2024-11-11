#include "binaryTree.h"

#include "getopt.h"

#include "simpleConsoleParser/consoleParser.h"

#define INIT_BINARY_TREE(treePtr, rootValue) {                                         \
  binaryTreeInitialize(treePtr, rootValue);                                            \
  binaryTreeInfoInitialize(treePtr, __FILE__, __PRETTY_FUNCTION__, __LINE__);          \
  parseConsole(argc, argv, treePtr);                                                   \
  binaryTreeSetInfo(treePtr);                                                          \
}

int main(int argc, char *argv[]) {
  binaryTree<int> intTree = {};
  INIT_BINARY_TREE(&intTree, 100);

  binaryTreeNodeCreate(&intTree, 200);
  binaryTreeNodeCreate(&intTree, 12);
  binaryTreeNodeCreate(&intTree, 1488);
  binaryTreeNodeCreate(&intTree, 228);

  binaryTreeDump(&intTree);

  printBinaryTree(intTree.root);

  // binaryTree<const char*> charTree = {};
  // binaryTreeInitialize(&charTree, "DED");
  // binaryTreeNodeCreate(&charTree, "LOX");
  // printBinaryTree(charTree.root);
  // binaryTreeDestruct(&charTree);

  binaryTreeDestruct(&intTree);
}