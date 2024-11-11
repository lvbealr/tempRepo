#include <ctime>
#include <fcntl.h>
#include <unistd.h>

#include "binaryTree.h"
#include "customWarning/customWarning.h"

#define FREE_(field) { \
  free(field);         \
  field = NULL;        \
}

static size_t MAX_FILE_NAME_SIZE = 50;

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

  if (binaryTreeNodeLink(tree->root, treeNode) == NODE_VALUE_EXITS) {
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

  printf(" %d ", node->data);

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

