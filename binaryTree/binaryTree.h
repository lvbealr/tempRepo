#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#define FREE_(field) { \
  free(field);         \
  field = NULL;        \
}

#include <cstdlib>
#include <cinttypes>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>

#include "customWarning/customWarning.h"

static size_t MAX_FILE_NAME_SIZE = 50;

template<typename DT>
struct node {
  DT data      = {};
  node *left   = NULL;
  node *right  = NULL;
  node *parent = NULL;
};

template<typename DT>
struct binaryTree : node<DT> {
  node<DT> *root     = NULL;
  uint64_t errorCode = {};
};

template<typename DT>
struct binaryTreeInfo {
  char *bornFileName         = {};
  char *bornFunctionName     = {};
  int bornLine               = {};
  char *dumpFolderName       = {};
  char *dumpFileName         = {};
  char *lastUserFileName     = {};
  char *lastUsedFunctionName = {};
  int lastUsedLine           = {};
  char *htmlDumpFileName     = {};
};

enum binaryTreeError {
  NO_ERRORS             = 0,
  TREE_BAD_POINTER      = 1,
  NODE_BAD_POINTER      = 2,
  NODE_VALUE_EXIST      = 3,
  BAD_FILE_NAME_POINTER = 4,
  BAD_FUNC_NAME_POINTER = 5,
  BAD_BORN_LINE_VALUE   = 6
};

// TREE FUNCTION PROTOTYPES //
template<typename DT> binaryTreeError binaryTreeInitialize    (binaryTree<DT> *tree,        DT rootData   );
template<typename DT> binaryTreeError binaryTreeDestruct      (node<DT>       *currentNode                );
template<typename DT> binaryTreeError binaryTreeNodeCreate    (binaryTree<DT> *tree,        DT data       );
template<typename DT> binaryTreeError binaryTreeNodeLink      (node<DT>       *parentNode,  node<DT> *node);
template<typename DT> binaryTreeError printBinaryTree         (node<DT>       *root                       );
template<typename DT> binaryTreeError binaryTreeInfoInitialize(binaryTree<DT>, const char *bornFileName,
                                                                               const char *bornFuncName,
                                                                                     int   line           );
// TREE FUNCTION PROTOTYPES //

// OTHER FUNCTION PROTOTYPES //
char           *setDumpFileName         (const char *dumpFolder);
// OTHER FUNCTION PROTOTYPES //

template<typename DT> binaryTreeError binaryTreeInitialize(binaryTree<DT> *tree,        DT rootData   ) {
  customWarning(tree != NULL, TREE_BAD_POINTER);

  node<DT> *treeRoot = (node<DT> *)calloc(1, sizeof(node<DT>));
  customWarning(treeRoot != NULL, NODE_BAD_POINTER);

  tree->root         = treeRoot;
  tree->root->data   = rootData;
  tree->root->left   = NULL;
  tree->root->right  = NULL;
  tree->root->parent = NULL;

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeDestruct  (node<DT>       *currentNode                ) {
  customWarning(currentNode != NULL, NODE_BAD_POINTER);

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeNodeCreate(binaryTree<DT> *tree,        DT data       ) {
  customWarning(tree != NULL, TREE_BAD_POINTER);

  node<DT> *treeNode = (node<DT> *)calloc(1, sizeof(node<DT>));
  customWarning(treeNode != NULL, NODE_BAD_POINTER);

  treeNode->data   = data;
  treeNode->left   = NULL;
  treeNode->right  = NULL;
  treeNode->parent = NULL;

  if (binaryTreeNodeLink(tree->root, treeNode) == NODE_VALUE_EXIST) {
    FREE_(treeNode);
  }

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeNodeLink  (node<DT>       *parentNode,  node<DT> *node) {
  customWarning(parentNode != NULL, NODE_BAD_POINTER);
  customWarning(node       != NULL, NODE_BAD_POINTER);

  DT parentValue = parentNode->data;
  DT nodeValue   = node->data;

  if (nodeValue == parentValue) {
    return NODE_VALUE_EXIST;
  }

  if (nodeValue > parentValue) {
    if (parentNode->right == NULL) {
      parentNode->right = node;
      node->parent      = parentNode;
    }

    else {
      parentNode = parentNode->right;
      binaryTreeNodeLink(parentNode, node);
    }
  }

  if (nodeValue < parentValue) {
    if (parentNode->left == NULL) {
      parentNode->left = node;
      node->parent     = parentNode;
    }

    else {
      parentNode = parentNode->left;
      binaryTreeNodeLink(parentNode, node);
    }
  }

  return NO_ERRORS;
}

template<typename DT> binaryTreeError printBinaryTree     (node<DT>       *node                       ) {
  customWarning(node != NULL, NODE_BAD_POINTER);

  printf("(");

  if (node->left) {
    printBinaryTree(node->left);
  }

  printf(" %d ", node->data); // !

  if (node->right) {
    printBinaryTree(node->right);
  }

  printf(")");

  return NO_ERRORS;
}

char *setDumpFileName(const char *dumpFolder) {
  const time_t currentTime = time(NULL);
  tm localTime = *localtime(&currentTime);

  char *fileName = (char *)calloc(MAX_FILE_NAME_SIZE, sizeof(char));

  customWarning(fileName != NULL, NULL);

  snprintf(fileName, FILENAME_MAX, "%s/%.2d.%.2d.%.4d-%.2d:%.2d:%.2d",
                                    dumpFolder, localTime.tm_mday, localTime.tm_mon,
                                    localTime.tm_year + 1900, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

  return fileName;
}

template<typename DT> binaryTreeError binaryTreeInfoInitialize(binaryTree<DT> *tree, const char *bornFileName,
                                                                                     const char *bornFuncName,
                                                                                           int   line) {
  customWarning(bornFileName != NULL, BAD_FILE_NAME_POINTER);
  customWarning(bornFuncName != NULL, BAD_FUNC_NAME_POINTER);
  customWarning(line         >     0, BAD_BORN_LINE_VALUE  );

  
}

#endif // BINARY_TREE_H_