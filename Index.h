//Index.h
#ifndef _INDEX_H
#define _INDEX_H
#include "Array.h"

typedef signed long int Long;
typedef struct _businesscard Businesscard;
typedef struct _index {
	char companyName[16];
	Array businesscards;
	Long capacity;
	Long length;
}Index;
void Index_Create(Index *index, Long capacity);
Long Index_PutIn(Index *index, Businesscard* businesscardLink);
Long Index_Find(Index *index, Businesscard* businesscardLink);
Long Index_PullOut(Index *index, Long subscript);
void Index_Arrange(Index *index);
Businesscard* Index_GetAt(Index *indexLink, Long subscript);
void Index_Destroy(Index *index);
int CompareBusinesscardLinks(void *one, void *other);
int Index_CompareNames(void *one, void *other);
#endif //_INDEX_H
