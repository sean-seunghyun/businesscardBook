//Array.c
#include "Array.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

void Array_Create(Array *array, Long capacity, size_t size){
array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}

Long Store(Array *array, Long index, void *object, size_t size) {
	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;
	return index;
}

Long Insert(Array *array, Long index, void *object, size_t size) {
	Long i = 0;
	void(*front);
	front = calloc(array->capacity + 1, size);
	while (i < index) {
		memcpy(((char(*))front) + (i*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	while (i < array->length) {
		memcpy(((char(*))front) + ((i+1)*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = front;
	(array->capacity)++;
	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;
	return index;
}

Long AppendFromFront(Array *array, void *object, size_t size) {
	Long index = 0;
	void (*front);
	Long i = 0;
	front = calloc((array->capacity) + 1, size);
	while (i < array->length) {
		memcpy(((char(*))front) + ((i+1)*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	
	array->front = front;
	(array->capacity)++;
	memcpy(((char(*))array->front) + (index*size), object, size);
	
	(array->length)++;

	return index;
}

Long AppendFromRear(Array *array, void *object, size_t size) {
	Long index;
	Long i = 0;
	void(*front);
	
	front = calloc((array->capacity) + 1, size);
	while (i < array->length) {
		memcpy(((char(*))front) + (i*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = front;
	(array->capacity)++;
	index = array->capacity - 1;

	memcpy(((char(*))array->front) + (index*size), object, size);
	(array->length)++;
	return index;
}

Long Array_LinearSearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)){
Long i = 0;
	Long index = -1;
	while (i < array->length &&
		compare(((char(*))array->front) + (i*size), key) != 0) {
		i++;
	}
	if (i < array->length) {
		index = i;
	}
	return index;
}

void Array_LinearSearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*)){
	Long i = 0;
	Long index = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	while (index < array->length) {
		if (compare(((char(*))array->front) + (index*size),key) == 0) {
			(*indexes)[i] = index;
			(*count)++;
			i++;
		}
		index++;
	}
}
Long BinarySearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long minIndex = 0;
	Long maxIndex;
	Long midIndex;
	maxIndex = array->length - 1;
	midIndex = (minIndex + maxIndex) / 2;
	while (minIndex <= maxIndex &&
		compare(((char(*))array->front) + (midIndex*size),key) != 0) {
		if (compare(((char(*))array->front) + (midIndex*size),key) < 0) {
			minIndex = midIndex + 1;
		}
		else {
			maxIndex = minIndex - 1;
		}
		midIndex = (minIndex + maxIndex) / 2;	
}
	if (minIndex <= maxIndex) {
		index = midIndex;
	}
	return index;
}

void BinarySearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long minIndex = 0;
	Long midIndex;
	Long maxIndex;
	Long index;
	Long i = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	maxIndex = array->length - 1;
	midIndex = (minIndex + maxIndex) / 2;
	while (minIndex <= maxIndex &&
		compare(((char(*))array->front) + (midIndex*size),key) != 0) {
		if (compare(((char(*))array->front) + (midIndex*size),key) > 0) {
			maxIndex = midIndex - 1;
		}
		else {
			minIndex = midIndex + 1;
		}
		midIndex = (minIndex + maxIndex) / 2;
	}
	index = midIndex - 1;
	while (index >= 0 &&
		compare(((char(*))array->front) + (index*size),key) == 0) {
		index--;
	}
	index++;
	while (index < array->length&&
		compare(((char(*))array->front) + (index*size),key) == 0) {
		(*indexes)[i] = index;
		(*count)++;
		i++;
		index++;
	}
}

Long Array_Delete(Array *array, Long index, size_t size){
	void (*front) = NULL;
	Long i = 0;
	if (array->capacity > 1) {
		front = calloc(array->capacity - 1, size);
	}
	while (i < index) {
		memcpy(((char(*))front) + (i*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	i++;
	while (i < array->length) {
		memcpy(((char(*))front) + ((i - 1)*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	if (array->capacity > 1) {
		array->front = front;
	}
	(array->capacity)--;
	(array->length)--;
	index = -1;
	return index;
}

Long DeleteFromFront(Array *array, size_t size) {
	Long index;
	Long i = 0;
	void (*front) = NULL;

	if (array->capacity > 1) {
		front = calloc(array->capacity - 1, size);
	}
	while (i < array->length - 1) {
		memcpy(((char(*))front) + (i*size), ((char(*))array->front) + ((i + 1)*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = front;
	}
	(array->capacity)--;
	(array->length)--;
	index = -1;
	return index;
}

Long DeleteFromRear(Array *array, size_t size) {
	Long index;
	void (*front) = NULL;
	Long i = 0;
	if (array->capacity > 1) {
		front = calloc(array->capacity - 1, size);
	}
	while (i < array->capacity - 1) {
		memcpy(((char(*))front) + (i*size), ((char(*))array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = front;
	}
	(array->capacity)--;
	(array->length)--;
	index = -1;

	return index;
}

void Clear(Array *array) {
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}

Long Modify(Array *array, Long index, void *object, size_t size) {
	memcpy(((char(*))array->front) + (index*size), object, size);

	return index;
}

void BubbleSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	Long k;
	Long length;
	void *temp;
	int flag = 0;
	
	temp = malloc(size);
	while (i < array->length - 1 && flag == 0){
		flag = 1;
		j = 0;
		length = array->length - 1;
		while (j < length){
			k = j + 1;
			if (compare(((char(*))array->front) + (j*size), ((char(*))array->front)+(k*size)) > 0) {
				memcpy(temp, ((char(*))array->front) + (j*size), size);
				memcpy(((char(*))array->front) + (j*size), ((char(*))array->front) + (k*size), size);
				memcpy(((char(*))array->front) + (k*size), temp, size);
				flag = 0;
		}
			j++;
			}
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}
void SelectionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	void *temp;
	Long index;
	
	temp = malloc(size);
	while (i < array->length - 1) {
		index = i;
		j = i + 1;
		while (j < array->length) {
			if (compare(((char(*))array->front) + (index*size), ((char(*))array->front) + (j*size)) > 0) {
				index = j;
			}
			j++;
		}
		memcpy(temp, ((char(*))array->front) + (i*size), size);
		memcpy(((char(*))array->front) + (i*size), ((char(*))array->front) + (index*size), size);
		memcpy(((char(*))array->front) + (index*size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}

void InsertionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	Long i = 1;
	Long j;
	Long k;
	void *temp;
	temp = malloc(size);
	while (i < array->length) {
		memcpy(temp, ((char(*))array->front) + (i*size), size);
		j = 0;
		while (i > j &&
			compare(((char(*))array->front) + (j*size), temp)<0) {
			j++;
		}
		k = i;
		while (k > j) {
			memcpy(((char(*))array->front) + (k*size), ((char(*))array->front) + ((k - 1)*size), size);
			k--;
		}
		memcpy(((char(*))array->front) + (j*size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}


void Merge(Array *array, Array *one, Array *other, size_t size, int(*compare)(void*, void*)) {
	Long length;
	Long i = 0;
	Long j = 0;
	Long k = 0;

	length = one->length + other->length;
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = calloc(length, size);
	array->capacity = length;
	while (i < one->length && j < other->length) {
		if (compare(((char(*))one->front) + (i*size), ((char(*))other->front) + (j*size)) >= 0) {
			memcpy(((char(*))array->front) + (k*size), ((char(*))other->front) + (j*size), size);
			k++;
			j++;
		}
		else {
			memcpy(((char(*))array->front) + (k*size), ((char(*))one->front) + (i*size), size);
			k++;
			i++;
		}
	}
		while (i < one->length) {
			memcpy(((char(*))array->front) + (k*size), ((char(*))one->front) + (i*size), size);
			k++;
			i++;
		}
		while (j < other->length)	{
			memcpy(((char(*))array->front) + (k*size), ((char(*))other->front) + (j*size), size);
			k++;
			j++;
		}
		array->length = length;
	}

void Array_GetAt(Array *array, Long index, void *object, size_t size){
memcpy(object, ((char(*))array->front) + (index*size), size);
}


void Array_Destroy(Array *array){
if (array->front != NULL) {
		free(array->front);
	}
}