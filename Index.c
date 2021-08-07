#include"Index.h"
#include"Array.h"
#include"BusinesscardBook.h"
#include<string.h>

Businesscard* Index_GetAt(Index *indexLink, Long subscript) {
	Businesscard* businesscardLink;
	Array_GetAt(&indexLink->businesscards, subscript, &businesscardLink, sizeof(Businesscard*));

	return businesscardLink;
}

void Index_Create(Index *index, Long capacity) {
	Array_Create(&index->businesscards, capacity, sizeof(Businesscard*));
	index->capacity = capacity;
	index->length = 0;
}
Long Index_PutIn(Index *index, Businesscard* businesscardLink) {
	Long subscript;

	subscript = index->length;

	if (index->length < index->capacity) {
		subscript = Store(&index->businesscards, subscript, &businesscardLink, sizeof(Businesscard*));
	}
	else
	{
		subscript = AppendFromRear(&index->businesscards, &businesscardLink, sizeof(Businesscard*));
		(index->capacity)++;
	}
	(index->length)++;

	return subscript;
}

Long Index_Find(Index *index, Businesscard* businesscardLink) {
	Long subscript;

	subscript = Array_LinearSearchUnique(&index->businesscards, businesscardLink, sizeof(Businesscard*), CompareBusinesscardLinks);
	return subscript;
}


Long Index_PullOut(Index *index, Long subscript) {
	subscript = Array_Delete(&index->businesscards, subscript, sizeof(Businesscard*));
	(index->capacity)--;
	(index->length)--;

	return subscript;
}


void Index_Arrange(Index *index) {
	SelectionSort(&index->businesscards, sizeof(Businesscard*), Index_CompareNames);
}


void Index_Destroy(Index *index) {
	Array_Destroy(&index->businesscards);
}

int Index_CompareNames(void *one, void *other) {
	Businesscard* *one_ = (Businesscard**)one;
	Businesscard* *other_ = (Businesscard**)other;

	return strcmp((*one_)->personal.name, (*other_)->personal.name);
}

int CompareBusinesscardLinks(void *one, void *other) {
	Businesscard* *one_ = (Businesscard**)one;
	Businesscard *other_ = (Businesscard*)other;
	int ret;

	if (*one_ > other_) {
		ret = 1;
	}
	else if (*one_ == other_) {
		ret = 0;
	}
	else if(*one_ < other_) {
		ret = -1;
	}

	return ret;
}
