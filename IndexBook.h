//IndexBook.h
#ifndef _INDEXBOOK_H
#define _INDEXBOOK_H
#include "BinaryTree.h"
#include "Index.h"

typedef signed long int Long;
typedef struct _indexBook{
	BinaryTree indexes;
	Long length;
}IndexBook;

void IndexBook_Create(IndexBook *indexBook);
Index* IndexBook_PutIn(IndexBook *indexBook, Businesscard* businesscardLink);
Index* IndexBook_Find(IndexBook *indexBook, char(*companyName));
Index* IndexBook_PullOut(IndexBook *indexBook, Businesscard* businesscardLink, char(*companyName));
void IndexBook_Arrange(IndexBook *indexBook);
void ArrangeAllArrayItems(BinaryTree *binaryTree);
void Node_ArrangeAllArrayItems(BinaryNode *node);
void MakeList(IndexBook *indexBook, Index *(*keys), Long *count);
void IndexBook_Destroy(IndexBook *indexBook);
void DestroyAllArrays(BinaryTree *binaryTree);
void Node_DestroyAllArrays(BinaryNode *node);
int IndexBook_CompareCompanyNames(void *one, void *other);
#endif //_INDEXBOOK_H