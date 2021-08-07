
#pragma warning(disable:4996)
#include"IndexBook.h"
#include"BusinesscardBook.h"
#include"BinaryTree.h"
#include<string.h>


void IndexBook_Create(IndexBook *indexBook) {
	BinaryTree_Create(&indexBook->indexes);
	indexBook->length = 0;
}



Index* IndexBook_PutIn(IndexBook *indexBook, Businesscard* businesscardLink) {
	Index index;
	Index* indexLink;
	BinaryNode* node;
	Long subscript;
	strcpy(index.companyName, businesscardLink->company.name);
	node = Search(&indexBook->indexes, &index, IndexBook_CompareCompanyNames);
	if (node == NULL) {
		Index_Create(&index, 32);
		node = BinaryTree_Insert(&indexBook->indexes, &index, sizeof(Index), IndexBook_CompareCompanyNames);
		(indexBook->length)++;
	}
	indexLink = (Index*)(node + 1);
	subscript = Index_PutIn(indexLink, businesscardLink);

	return indexLink;
}

Index* IndexBook_Find(IndexBook *indexBook, char(*companyName)) {
	Index index;
	BinaryNode* node;
	Index* indexLink = NULL;
	strcpy(index.companyName, companyName);
	node = Search(&indexBook->indexes, &index, IndexBook_CompareCompanyNames);
	if (node != NULL) {
		indexLink = (Index*)(node + 1);
	}

	return indexLink;
}

void IndexBook_Arrange(IndexBook *indexBook) {
	ArrangeAllArrayItems(&indexBook->indexes);
	MakeBalance(&indexBook->indexes, sizeof(Index));
}

void ArrangeAllArrayItems(BinaryTree *binaryTree) {
	Node_ArrangeAllArrayItems(binaryTree->root);
}

void Node_ArrangeAllArrayItems(BinaryNode *node) {
	Index* indexLink;
	if (node != NULL) {
		Node_ArrangeAllArrayItems(node->left);
		Node_ArrangeAllArrayItems(node->right);
		indexLink = (Index*)(node + 1);
		Index_Arrange(indexLink);
	}
}



void DestroyAllArrays(BinaryTree *binaryTree) {
	Node_DestroyAllArrays(binaryTree->root);
}
void Node_DestroyAllArrays(BinaryNode *node) {
	Index* indexLink;
	if (node != NULL) {
		Node_DestroyAllArrays(node->left);
		Node_DestroyAllArrays(node->right);
		indexLink = (Index*)(node + 1);
		Index_Destroy(indexLink);
	}
}



void MakeList(IndexBook *indexBook, Index *(*keys), Long *count) {
	MakeKeys(&indexBook->indexes, keys, count, sizeof(Index));
}

//Index_Find 정의, Index_PullOut 정의
Index* IndexBook_PullOut(IndexBook *indexBook, Businesscard* businesscardLink, char(*companyName)) {
	Index* indexLink;
	Index index;
	BinaryNode* node;
	Long subscript;
	strcpy(index.companyName, companyName);
	//1. companyName으로 indexLink를 찾는다.
	node = Search(&indexBook->indexes, &index, IndexBook_CompareCompanyNames);
	indexLink = (Index*)(node + 1);
	//2. businesscardLink로 배열의 위치를 구한다.
	subscript = Index_Find(indexLink, businesscardLink);
	//3. 찾은 배열의 위치로 빼낸다.
	subscript = Index_PullOut(indexLink, subscript);
	//4. 배열에 아무것도 없으면 Index를 빼낸다.
	if (indexLink->length == 0) {
		BinaryTree_Delete(&indexBook->indexes, &index, IndexBook_CompareCompanyNames);
		(indexBook->length)--;
		indexLink = NULL;
	}
	return indexLink;
}


void IndexBook_Destroy(IndexBook *indexBook) {
	DestroyAllArrays(&indexBook->indexes);
	BinaryTree_Destroy(&indexBook->indexes);
}

int IndexBook_CompareCompanyNames(void *one, void *other) {
	Index *one_ = (Index*)one;
	Index *other_ = (Index*)other;

	return strcmp(one_->companyName, other_->companyName);
}
