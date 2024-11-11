#include "binaryTree.h"

#include "getopt.h"

#define INIT_BINARY_TREE(treePtr, rootValue) {                                \
  binaryTreeInitialize(treePtr, rootValue);                                   \
  binaryTreeInfoInitialize(treePtr, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
}

// CONSOLE PARSER //

// [0]: path-to-dump-folder
// [1]: path-to-database-file

static const size_t MAX_OPTIONS_COUNT = 2;

#define INIT_OPTION(optionsBuffer, flagName, hasArgValue, shortName, flagValue) { \
  customWarning(optionsCount < MAX_OPTIONS_COUNT, (void) 1);                      \
                                                                                  \
  optionsBuffer[optionsCount].name    = flagName;                                 \
  optionsBuffer[optionsCount].has_arg = hasArgValue;                              \
  optionsBuffer[optionsCount].val     = shortName;                                \
  optionsBuffer[optionsCount].flag    = flagValue;                                \
                                                                                  \
  optionsCount++;                                                                 \
}

void parseConsole(int argc, char *argv[]) {
  size_t optionsCount = 0;
  option options[MAX_OPTIONS_COUNT]   = {};

  INIT_OPTION(options, "dumpFolder", 2, 'd', 0);
  INIT_OPTION(options, "dataBase",   2, 'b', 0);

  int   gotOption    = 0;
  while ((gotOption = getopt_long(argc, argv, "2", options, NULL)) != -1) {
    printf("Option: [-%c]\t %s\n", gotOption, optarg);
  }
}

// CONSOLE PARSER //

int main(int argc, char *argv[]) {
  parseConsole(argc, argv);

  binaryTree<int> intTree = {};

  binaryTreeInitialize(&intTree, 100);
  binaryTreeNodeCreate(&intTree, 200);
  binaryTreeNodeCreate(&intTree, 12);
  binaryTreeNodeCreate(&intTree, 1488);
  binaryTreeNodeCreate(&intTree, 228);

  printBinaryTree(intTree.root);

  // binaryTree<const char*> charTree = {};
  // binaryTreeInitialize(&charTree, "DED");
  // binaryTreeNodeCreate(&charTree, "LOX");
  // printBinaryTree(charTree.root);
  // binaryTreeDestruct(&charTree);

  binaryTreeDestruct(&intTree);
}