//BinaryTree.c
#include "BinaryTree.h"
#include<memory.h>
#include<stdlib.h>

void BinaryTree_Create(BinaryTree *binaryTree) {
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)){
BinaryNode* parent = NULL;
	BinaryNode* child;
	
	child = binaryTree->root;
	while (child != NULL) {
		parent = child;
		if (compare(parent + 1, key) > 0) {
			child = child->left;
		}
		else {
			child = child->right;
		}
	}
	child = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(child + 1, key, size);
	child->left = NULL;
	child->right = NULL;
	if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = child;
		}
		else {
			parent->right = child;
		}
		if (compare(binaryTree->root + 1, key) > 0) {
			(binaryTree->balance)--;
		}
		else {
			(binaryTree->balance)++;
		}
	}
	else {
		binaryTree->root = child;
	}
	(binaryTree->length)++;

	return child;
}

BinaryNode* Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)) {
	BinaryNode* index;
	index = binaryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}

BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)){
BinaryNode* index;
	BinaryNode* parent = NULL;
	BinaryNode* child = NULL;
	BinaryNode* it;
	BinaryNode* secondParent = NULL;

	index = binaryTree->root;
	while (compare(index + 1, key) != 0){
		parent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	it = index->right;
	while (it != NULL) {
		secondParent = child;
		child = it;
		it = it->left;
	}
	if (child == NULL) {
		it = index->left;
	}
	while (it != NULL) {
		secondParent = child;
		child = it;
		it = it->right;
	}
	if (index->right != NULL) {
		if (child->right != NULL) {
			if (secondParent != NULL) {
				if (compare(secondParent + 1, child->right + 1) > 0) {
					secondParent->left = child->right;
				}
				else {
					secondParent->right = child->right;
				}
				child->right = index->right;
			}
		}
		else {
			if (secondParent != NULL) {
				child->right = index->right;
				secondParent->left = NULL;
			}
		}
	}



	if (index->left != NULL) {
		if (index->left != child) {
			if (index->right == NULL && secondParent != NULL) {
				secondParent->right = NULL;
			}
			child->left = index->left;
		}
	}

	if (parent != NULL && child != NULL) {
		if (compare(parent + 1, child + 1) < 0) {
			parent->right = child;
		}
		else {
			parent->left = child;
		}
	}
	else {
		if (parent != NULL && child == NULL) {
			if (compare(parent + 1, index + 1) < 0) {
				parent->right = NULL;
			}
			else {
				parent->left = NULL;
			}
		}
		else {
			binaryTree->root = child;
		}
	}

	if (index != NULL) {
		free(index);
		index = NULL;
	}

	if (binaryTree->root == NULL) {
		binaryTree->balance = NULL;
	}
	else if (parent == NULL && child != NULL) {
		if (compare(binaryTree->root + 1, key) < 0) {
			(binaryTree->balance)++;
		}
		else {
			(binaryTree->balance)--;
		}
	}
	else {
		if (compare(binaryTree->root + 1, key) < 0) {
			(binaryTree->balance)--;
		}
		else {
			(binaryTree->balance)++;
		}
	}
	(binaryTree->length)--;

	return index;
}


void MakeKeys(BinaryTree *binaryTree, void *(*keys), Long *count, size_t size) {
	Long i = 0;
	*count = 0;

	*keys = calloc(binaryTree->length, size);
	Node_MakeKeys(binaryTree->root, *keys, count, &i, size);
}

void Node_MakeKeys(BinaryNode *node, void(*keys), Long *count, Long *i, size_t size) {
	if (node != NULL) {
		Node_MakeKeys(node->left, keys, count, i, size);
		memcpy(((char(*))keys) + ((*i)*size), node + 1, size);
		(*count)++;
		(*i)++;
		Node_MakeKeys(node->right, keys, count, i, size);
	}
}

void BinaryTree_DeleteAllItems(BinaryTree *binaryTree) {
	Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void Node_DeleteAllItems(BinaryNode *node) {
	if (node != NULL) {
		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);
		if (node != NULL) {
			free(node);
			node = NULL;
		}
	}
}


void MakeTree(BinaryTree *binaryTree, void(*keys), Long count, size_t size) {
	
	
	

	binaryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	

	/**
	MakeBalance 함수로 이동

	binaryTree->length = count;
	remainder = (binaryTree->length) % 2;
	if (remainder == 0) {
		binaryTree->balance = 0;
	}
	else {
		binaryTree->balance = 1;
	}
	**/
}

BinaryNode* Node_MakeTree(void(*keys), Long first, Long last, size_t size) {
	BinaryNode* node = NULL;
	Long middle;
	if (first <= last) {
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		middle = (first + last) / 2;
		memcpy(node + 1, ((char(*))keys) + (middle*size), size);
		node->left = Node_MakeTree(keys, first, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, last, size);
	}

	return node;
}

void MakeBalance(BinaryTree *binaryTree, size_t size) {
	void(*keys);
	Long count;
	Long remainder;

	MakeKeys(binaryTree, &keys, &count, size);
	BinaryTree_DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, count, size);
	if (keys != NULL) {
		free(keys);
	}


	binaryTree->length = count;
	remainder = (binaryTree->length) % 2;
	if (remainder == 0) {
		binaryTree->balance = 1;
	}
	else {
		binaryTree->balance = 0;
	}
}



void BinaryTree_Destroy(BinaryTree *binaryTree){
Node_Destroy(binaryTree->root);
}

void Node_Destroy(BinaryNode *node) {
	if (node != NULL) {
		Node_Destroy(node->left);
		Node_Destroy(node->right);
		if (node != NULL) {
			free(node);
		}
	}
}

void BinaryTree_GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size) {
	memcpy(key, index + 1, size);
}
