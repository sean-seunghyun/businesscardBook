//BusinesscardBook.h
#ifndef _BUSINESSCARDBOOK_H
#define _BUSINESSCARDBOOK_H

#include "LinkedList.h"

typedef signed long int Long;
typedef unsigned long int ULong;
typedef struct _personal {
	char name[11];
	char position[5];
	char cellphoneNumber[12];
	char emailAddress[32];
}Personal;
typedef struct _company {
	char name[11];
	char address[64];
	char telephoneNumber[12];
	char faxNumber[12];
	char url[64];
}Company;
typedef struct _businesscard {
	Personal personal;
	Company company;
}Businesscard;
typedef struct _businesscardBook {
	LinkedList businesscards;
	Long length;
	Businesscard* current;
}BusinesscardBook;

void BusinesscardBook_Create(BusinesscardBook *businesscardBook);
Long Load(BusinesscardBook *businesscardBook);
Businesscard* PutIn(BusinesscardBook *businesscardBook, Businesscard businesscard);
void Find(BusinesscardBook *businesscardBook, char(*name), Businesscard* *(*indexes), Long *count);
Businesscard PullOut(BusinesscardBook *businesscardBook, Businesscard* index);
Businesscard* FindByCompanyName(BusinesscardBook *businesscardBook, char(*name));
Businesscard* BusinesscardBook_Move(BusinesscardBook *businesscardBook, Businesscard* index);
Businesscard* BusinesscardBook_First(BusinesscardBook *businesscardBook);
Businesscard* BusinesscardBook_Previous(BusinesscardBook *businesscardBook);
Businesscard* BusinesscardBook_Next(BusinesscardBook *businesscardBook);
Businesscard* BusinesscardBook_Last(BusinesscardBook *businesscardBook);
Long Save(BusinesscardBook *businesscardBook);
void BusinesscardBook_Destroy(BusinesscardBook *businesscardBook);
int CompareCompanyNames(void* one, void* other);
int CompareNames(void* one, void* other);
int CompareBusinesscards(void* one, void* other);
#endif //BUSINESSCARDBOOK_H