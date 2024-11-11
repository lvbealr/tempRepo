#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

// TODO убрать поля структур и тд для акинатора из дерева
// TODO дерево это стандартная структура, лишнее здесь не надо

#include <cstdlib>
#include <cinttypes>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#include "customWarning/customWarning.h"

const size_t MAX_FILE_NAME_SIZE   =  50;
const size_t MAX_BORN_FUNC_NAME   =  50;
const int    MAX_LINE_LENGTH      =   4;
const size_t MAX_DUMP_FOLDER_NAME =  20;
const size_t MAX_DUMP_FILE_NAME   =  50;
const size_t MAX_PATH_TO_FILE     = 100;
const size_t MAX_CMD_BUFFER_SIZE  = 100;

#define FREE_(field) { \
  free(field);         \
  field = NULL;        \
}

#define CHECK_ERROR(treePtr, expression, error) { \
  if (!(expression)) {                            \
    (treePtr)->errorCode |= error;                \
    return error;                                 \
  }                                               \
}

struct binaryTreeInfo {
  char *bornFileName         = {};
  char *bornFunctionName     = {};
  int bornLine               = {};
  char *dumpFolderName       = {};
  char *dumpFileName         = {};
  char *lastUsedFileName     = {};
  char *lastUsedFunctionName = {};
  int lastUsedLine           = {};
  char *htmlDumpPath         = {};

  char *dataBasePath         = {}; // TODO only akinator
};

template<typename DT>
struct node {
  DT data      = {};
  node *left   = NULL;
  node *right  = NULL;
  node *parent = NULL;
};

template<typename DT>
struct binaryTree : node<DT> {
  node<DT> *root           = NULL;
  uint64_t errorCode       = {};
  binaryTreeInfo *infoData = NULL;
};

enum binaryTreeError {
  NO_ERRORS             =  0,
  TREE_BAD_POINTER      =  1,
  NODE_BAD_POINTER      =  2,
  NODE_VALUE_EXIST      =  3,
  BAD_FILE_NAME_POINTER =  4,
  BAD_FUNC_NAME_POINTER =  5,
  BAD_BORN_LINE_VALUE   =  6,
  BAD_INFO_POINTER      =  7,
  INFO_NULL_POINTER     =  8,
  BAD_BUFFER_POINTER    =  9,
  BAD_HTML_NAME_POINTER = 10,
  DUMP_FILE_BAD_POINTER = 11
};

// TREE FUNCTION PROTOTYPES //
template<typename DT> binaryTreeError binaryTreeInitialize    (binaryTree<DT> *tree,        DT rootData          );
template<typename DT> binaryTreeError binaryTreeDestruct      (node<DT>       *currentNode                       );
template<typename DT> binaryTreeError binaryTreeNodeCreate    (binaryTree<DT> *tree,        DT data              );
template<typename DT> binaryTreeError binaryTreeNodeLink      (node<DT>       *parentNode,  node<DT> *node       );
template<typename DT> binaryTreeError printBinaryTree         (node<DT>       *root                              );
template<typename DT> binaryTreeError binaryTreeInfoInitialize(binaryTree<DT> *tree, const char *fileName,
                                                                                     const char *funcName,
                                                                                     int   line                  );
template<typename DT> binaryTreeError binaryTreeSetInfo       (binaryTree<DT> *tree                              );
template<typename DT> binaryTreeError binaryTreeDump          (binaryTree<DT> *tree                              );
template<typename DT> binaryTreeError binaryTreeNodeDumpLink  (FILE *dumpFile,              node<DT> *node       );
// TREE FUNCTION PROTOTYPES //

// OTHER FUNCTION PROTOTYPES //
template<typename DT> char           *setDumpFileName         (binaryTree<DT> *dumpFolder);
// OTHER FUNCTION PROTOTYPES //

template<typename DT> binaryTreeError binaryTreeInitialize(binaryTree<DT> *tree, DT rootData) {
  customWarning(tree != NULL, TREE_BAD_POINTER);

  node<DT> *treeRoot = (node<DT> *)calloc(1, sizeof(node<DT>));
  CHECK_ERROR(tree, treeRoot != NULL, NODE_BAD_POINTER);

  tree->root         = treeRoot;
  tree->root->data   = rootData;
  tree->root->left   = NULL;
  tree->root->right  = NULL;
  tree->root->parent = NULL;

  tree->infoData     = (binaryTreeInfo *)calloc(1, sizeof(binaryTreeInfo));
  CHECK_ERROR(tree, tree->infoData != NULL, BAD_INFO_POINTER);

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeDestruct(node<DT> *currentNode) {
  customWarning(currentNode != NULL, NODE_BAD_POINTER);
  // TODO
  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeNodeCreate(binaryTree<DT> *tree, DT data) {
  customWarning(tree != NULL, TREE_BAD_POINTER);

  node<DT> *treeNode = (node<DT> *)calloc(1, sizeof(node<DT>));
  CHECK_ERROR(tree, treeNode != NULL, NODE_BAD_POINTER);

  treeNode->data   = data;
  treeNode->left   = NULL;
  treeNode->right  = NULL;
  treeNode->parent = NULL;

  if (binaryTreeNodeLink(tree->root, treeNode) == NODE_VALUE_EXIST) {
    FREE_(treeNode);
  }

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeNodeLink(node<DT> *parentNode, node<DT> *node) {
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

template<typename DT> binaryTreeError printBinaryTree(node<DT> *node) {
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

template<typename DT> char *setDumpFileName(binaryTree<DT> *tree) {
  const time_t currentTime = time(NULL);
  tm localTime = *localtime(&currentTime);

  char *fileName = (char *)calloc(MAX_FILE_NAME_SIZE, sizeof(char));

  customWarning(fileName != NULL, NULL);

  snprintf(fileName, FILENAME_MAX, "%s/%.2d.%.2d.%.4d-%.2d:%.2d:%.2d.html",
                                    tree->infoData->dumpFolderName, localTime.tm_mday, localTime.tm_mon,
                                    localTime.tm_year + 1900,       localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

  return fileName;
}

template<typename DT> binaryTreeError binaryTreeInfoInitialize(binaryTree<DT> *tree, const char *fileName,
                                                                                     const char *funcName,
                                                                                           int   line) {
  customWarning(tree     != NULL, TREE_BAD_POINTER     );
  customWarning(fileName != NULL, BAD_FILE_NAME_POINTER);
  customWarning(funcName != NULL, BAD_FUNC_NAME_POINTER);
  customWarning(line     >     0, BAD_BORN_LINE_VALUE  );

  tree->infoData->bornFileName         = (char *)calloc(MAX_FILE_NAME_SIZE,   sizeof(char));
  tree->infoData->bornFunctionName     = (char *)calloc(MAX_BORN_FUNC_NAME,   sizeof(char));
  tree->infoData->bornLine             = line;
  tree->infoData->dumpFolderName       = (char *)calloc(MAX_DUMP_FOLDER_NAME, sizeof(char));
  tree->infoData->dumpFileName         = (char *)calloc(MAX_DUMP_FILE_NAME,   sizeof(char));
  tree->infoData->lastUsedFileName     = (char *)calloc(MAX_FILE_NAME_SIZE,   sizeof(char));
  tree->infoData->lastUsedFunctionName = (char *)calloc(MAX_BORN_FUNC_NAME,   sizeof(char));
  tree->infoData->lastUsedLine         = line;
  tree->infoData->htmlDumpPath         = (char *)calloc(MAX_DUMP_FILE_NAME,   sizeof(char));
  tree->infoData->dataBasePath         = (char *)calloc(MAX_FILE_NAME_SIZE,   sizeof(char)); // TODO only akinator

  CHECK_ERROR(tree, tree->infoData->bornFileName         != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->bornFunctionName     != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->dumpFolderName       != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->dumpFileName         != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->lastUsedFileName     != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->lastUsedFunctionName != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->htmlDumpPath         != NULL, INFO_NULL_POINTER);
  CHECK_ERROR(tree, tree->infoData->dataBasePath         != NULL, INFO_NULL_POINTER);        // TODO only akinator

  strncpy(tree->infoData->bornFileName,     fileName, MAX_FILE_NAME_SIZE);
  strncpy(tree->infoData->bornFunctionName, funcName, MAX_BORN_FUNC_NAME);

  // TODO set default path to database (akinator) and ONLY htmldump if user didn't set them by console

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeSetInfo(binaryTree<DT> *tree) {
  customWarning(tree != NULL, TREE_BAD_POINTER);

  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));
  CHECK_ERROR(tree, buffer != NULL, BAD_BUFFER_POINTER);

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "mkdir -p %s", tree->infoData->dumpFolderName);
  system(buffer);

  *buffer = {};

  tree->infoData->htmlDumpPath = setDumpFileName(tree);
  CHECK_ERROR(tree, tree->infoData->htmlDumpPath != NULL, BAD_HTML_NAME_POINTER);

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "touch %s", tree->infoData->htmlDumpPath);
  system(buffer);

  FREE_(buffer);

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeDump(binaryTree<DT> *tree) {
  customWarning(tree != NULL, TREE_BAD_POINTER);

  tree->infoData->dumpFileName = "temp.dot";

  FILE *dumpFile = fopen(tree->infoData->dumpFileName, "w");
  CHECK_ERROR(tree, dumpFile != NULL, DUMP_FILE_BAD_POINTER);

  // .DOT HEADER //
  fprintf(dumpFile, "digraph binaryTree {\nsplines=curved;\nrankdir=HR;\nnodesep=0.4;"
                    "\nnode [shape=record, fontname=\"JetBrains Mono\", fontsize=\"10\", color=\"gray\", style=\"rounded\"];\n"
                    "edge [style=dashed, color=\"green\", weight=\"10\", penwidth=\"2\", "
                    "arrowsize=\"0.4\"];\n");
  // .DOT HEADER //

  // NODE //
  binaryTreeNodeDump    (dumpFile, tree->root);
  binaryTreeNodeDumpLink(dumpFile, tree->root);
  // NODE //

  fprintf(dumpFile, "}\n");

  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));
  CHECK_ERROR(tree, buffer != NULL, BAD_BUFFER_POINTER);

  printf("DUMP FILE: %s\n", tree->infoData->dumpFileName);
  fclose(dumpFile);

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "dot -Tsvg %s >> temp.svg && cat temp.svg > %s",
          tree->infoData->dumpFileName, tree->infoData->htmlDumpPath);
  system(buffer);

  *buffer = {};

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "rm -rf temp.svg");
  system(buffer);

  FREE_(buffer);

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeNodeDump      (FILE *dumpFile, node<DT> *node) {
  customWarning(dumpFile != NULL, DUMP_FILE_BAD_POINTER);
  customWarning(node     != NULL, NODE_BAD_POINTER);

  fprintf(dumpFile, "p%p [label = \"{ <p> [%p] | <d> data = [%d] | { <l> [%p] | <r> [%p] }}\"];\n",
          node, node, node->data, node->left, node->right);

  if (node->left != NULL) {
      binaryTreeNodeDump(dumpFile, node->left);
  }

  if (node->right != NULL) {
      binaryTreeNodeDump(dumpFile, node->right);
  }

  return NO_ERRORS;
}

template<typename DT> binaryTreeError binaryTreeNodeDumpLink(FILE *dumpFile, node<DT> *node) {
  customWarning(dumpFile != NULL, DUMP_FILE_BAD_POINTER);
  customWarning(node     != NULL, NODE_BAD_POINTER);

  if (node->left != NULL) {
    fprintf(dumpFile, "p%p:<l> -> p%p\n", node, node->left);
    binaryTreeNodeDumpLink(dumpFile, node->left);
  }

  if (node->right != NULL) {
    fprintf(dumpFile, "p%p:<r> -> p%p\n", node, node->right);
    binaryTreeNodeDumpLink(dumpFile, node->right);
  }

  return NO_ERRORS;
}

#endif // BINARY_TREE_H_