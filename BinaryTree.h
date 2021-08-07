//BinaryTree.h
#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include<stddef.h>
typedef signed long int Long;
typedef struct _binaryNode BinaryNode;
typedef struct _binaryNode {
	BinaryNode* left;
	BinaryNode* right;
}BinaryNode;
typedef struct _binaryTree {
	BinaryNode* root;
	Long length;
	Long balance;
}BinaryTree;

void BinaryTree_Create(BinaryTree *binaryTree);
BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*));
BinaryNode* Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*));
BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*));
void Node_MakeKeys(BinaryNode *node, void(*keys), Long *count, Long *i, size_t size);
void MakeKeys(BinaryTree *binaryTree, void *(*keys), Long *count, size_t size);
void Node_DeleteAllItems(BinaryNode *node);
void BinaryTree_DeleteAllItems(BinaryTree *binaryTree);
BinaryNode* Node_MakeTree(void(*keys), Long first, Long last, size_t size);
void MakeTree(BinaryTree *binaryTree, void(*keys), Long count, size_t size);
void MakeBalance(BinaryTree *binaryTree, size_t size);
void BinaryTree_GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size);
void Node_Destroy(BinaryNode *node);
void BinaryTree_Destroy(BinaryTree *binaryTree);
#endif //_BINARYTREE_H

