#include "BusinesscardBook.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#pragma warning(disable : 4996) 

#if 0
int main(int argc, char* argv[]) {
	BusinesscardBook businesscardBook;
	Long count;
	Businesscard* index;
	Businesscard* (*indexes);
	Businesscard businesscard;
	Long i;


	//1. 명함철을 만든다.
	BusinesscardBook_Create(&businesscardBook);



	//2. 명함을 준비한다.
	strcpy(businesscard.personal.name, "홍길동");
	strcpy(businesscard.personal.position, "사원");
	strcpy(businesscard.personal.cellphoneNumber, "0101111111");
	strcpy(businesscard.personal.emailAddress, "1@");
	strcpy(businesscard.company.name, "삼성");
	strcpy(businesscard.company.address, "서울시");
	strcpy(businesscard.company.telephoneNumber, "021111111");
	strcpy(businesscard.company.faxNumber, "021111112");
	strcpy(businesscard.company.url, "www.1.com");
	//businesscard.next = NULL;

	//3. 명함을 집어넣는다.
	index = PutIn(&businesscardBook, businesscard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);



	//4. 명함을 준비한다.
	strcpy(businesscard.personal.name, "김길동");
	strcpy(businesscard.personal.position, "사장");
	strcpy(businesscard.personal.cellphoneNumber, "0201111111");
	strcpy(businesscard.personal.emailAddress, "2@");
	strcpy(businesscard.company.name, "현대");
	strcpy(businesscard.company.address, "서울시");
	strcpy(businesscard.company.telephoneNumber, "022111111");
	strcpy(businesscard.company.faxNumber, "022111112");
	strcpy(businesscard.company.url, "www.2.com");
	//businesscard.next = NULL;

	//5. 명함을 집어넣는다.

	index = PutIn(&businesscardBook, businesscard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);


	//6. 명함을 준비한다.
	strcpy(businesscard.personal.name, "박길동");
	strcpy(businesscard.personal.position, "부장");
	strcpy(businesscard.personal.cellphoneNumber, "0301111111");
	strcpy(businesscard.personal.emailAddress, "3@");
	strcpy(businesscard.company.name, "현대");
	strcpy(businesscard.company.address, "서울시");
	strcpy(businesscard.company.telephoneNumber, "032111111");
	strcpy(businesscard.company.faxNumber, "032111112");
	strcpy(businesscard.company.url, "www.3.com");
	//businesscard.next = NULL;

	//7. 명함을 집어넣는다.

	index = PutIn(&businesscardBook, businesscard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//6. 명함을 준비한다.
	strcpy(businesscard.personal.name, "홍길동");
	strcpy(businesscard.personal.position, "부장");
	strcpy(businesscard.personal.cellphoneNumber, "0301111111");
	strcpy(businesscard.personal.emailAddress, "3@");
	strcpy(businesscard.company.name, "현대");
	strcpy(businesscard.company.address, "서울시");
	strcpy(businesscard.company.telephoneNumber, "032111111");
	strcpy(businesscard.company.faxNumber, "032111112");
	strcpy(businesscard.company.url, "www.3.com");
	//businesscard.next = NULL;

	//7. 명함을 집어넣는다.

	index = PutIn(&businesscardBook, businesscard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//6. 명함을 준비한다.
	strcpy(businesscard.personal.name, "차길동");
	strcpy(businesscard.personal.position, "부장");
	strcpy(businesscard.personal.cellphoneNumber, "0301111111");
	strcpy(businesscard.personal.emailAddress, "3@");
	strcpy(businesscard.company.name, "현대");
	strcpy(businesscard.company.address, "서울시");
	strcpy(businesscard.company.telephoneNumber, "032111111");
	strcpy(businesscard.company.faxNumber, "032111112");
	strcpy(businesscard.company.url, "www.3.com");
	//businesscard.next = NULL;

	//7. 명함을 집어넣는다.

	index = PutIn(&businesscardBook, businesscard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//8. 이전 위치를 출력한다.
	index = BusinesscardBook_Previous(&businesscardBook);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//9. 처음 위치를 출력한다.
	index = BusinesscardBook_First(&businesscardBook);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//10. 다음 위치를 출력한다.
	index = BusinesscardBook_Next(&businesscardBook);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//11. 마지막 위치를 출력한다.
	index = BusinesscardBook_Last(&businesscardBook);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("======================================================\n");
	//12. 홍길동을 찾는다.
	Find(&businesscardBook, "홍길동", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
			index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	printf("======================================================\n");
	//13. 마지막 명함을 빼낸다.
	businesscard = PullOut(&businesscardBook, index);
	printf("%s %s %s %s %s %s %s %s %s\n", businesscard.personal.name, businesscard.personal.position, businesscard.personal.cellphoneNumber, businesscard.personal.emailAddress,
		businesscard.company.name, businesscard.company.address, businesscard.company.telephoneNumber, businesscard.company.faxNumber, businesscard.company.url);
	printf("======================================================\n");

	//14. 정렬하다.
	Arrange(&businesscardBook);
	index = First(&businesscardBook);
	while (index != previous) {
		printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.cellphoneNumber, index->personal.emailAddress,
			index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		previous = index;
		index = Next(&businesscardBook);
	}




	//15. 폐기한다.
	BusinesscardBook_Destroy(&businesscardBook);

	return 0;
}
#endif

void BusinesscardBook_Create(BusinesscardBook *businesscardBook) {

	Create(&businesscardBook->businesscards);
	businesscardBook->length = 0;
	businesscardBook->current = NULL;
}

Long Load(BusinesscardBook *businesscardBook) {
	Businesscard businesscard;
	Node* index;
	FILE *fileForPersonals;
	FILE *fileForCompanies;
	size_t flagForPersonals;
	size_t flagForCompanies;
	Long companyNumber;
	Long i;

	fileForPersonals = fopen("Personals.bat", "rb");
	fileForCompanies = fopen("Companies.bat", "rb");

	if (fileForPersonals != NULL && fileForCompanies != NULL) {
		fread(&companyNumber, sizeof(Long), 1, fileForPersonals);
		flagForPersonals = fread(&businesscard.personal, sizeof(Personal), 1, fileForPersonals);
		while (!feof(fileForPersonals) && flagForPersonals != 0) {
			fseek(fileForCompanies, 0L, SEEK_SET);
			flagForCompanies = fread(&businesscard.company, sizeof(Company), 1, fileForCompanies);
			i = 1;
			while (!feof(fileForCompanies) && flagForCompanies != 0 && i != companyNumber) {
				i++;
				flagForCompanies = fread(&businesscard.company, sizeof(Company), 1, fileForCompanies);
			}
			index = AppendFromTail(&businesscardBook->businesscards, &businesscard, sizeof(Businesscard));
			fread(&companyNumber, sizeof(Long), 1, fileForPersonals);
			flagForPersonals = fread(&businesscard.personal, sizeof(Personal), 1, fileForPersonals);

			(businesscardBook->length)++;
			businesscardBook->current = (Businesscard*)(index + 1);
		}
		fclose(fileForPersonals);
		fclose(fileForCompanies);
	}
	return businesscardBook->length;
}




Businesscard* PutIn(BusinesscardBook *businesscardBook, Businesscard businesscard) {
	Node* index;

	index = AppendFromTail(&businesscardBook->businesscards, &businesscard, sizeof(Businesscard));
	(businesscardBook->length)++;
	businesscardBook->current = (Businesscard*)(index + 1);

	return businesscardBook->current;
}


Businesscard* BusinesscardBook_First(BusinesscardBook *businesscardBook) {
	Node* node;
	node = First(&businesscardBook->businesscards);
	businesscardBook->current = (Businesscard*)(node + 1);

	return businesscardBook->current;
}


Businesscard* BusinesscardBook_Previous(BusinesscardBook *businesscardBook) {
	Node* node;
	node = Previous(&businesscardBook->businesscards);
	businesscardBook->current = (Businesscard*)(node + 1);

	return businesscardBook->current;
}


Businesscard* BusinesscardBook_Next(BusinesscardBook *businesscardBook) {
	Node* node;
	node = Next(&businesscardBook->businesscards);
	businesscardBook->current = (Businesscard*)(node + 1);

	return businesscardBook->current;
}

Businesscard* BusinesscardBook_Last(BusinesscardBook *businesscardBook) {
	Node* node;
	node = Last(&businesscardBook->businesscards);
	businesscardBook->current = (Businesscard*)(node + 1);

	return businesscardBook->current;
}

void Find(BusinesscardBook *businesscardBook, char(*name), Businesscard* *(*indexes), Long *count) {
	Node* (*nodes);
	Long i = 0;

	LinearSearchDuplicate(&businesscardBook->businesscards, name, &nodes, count, CompareNames);
	*indexes = (Businesscard*(*))calloc(businesscardBook->length, sizeof(Businesscard*));
	while (i < *count) {
		(*indexes)[i] = (Businesscard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
	}
}

Businesscard PullOut(BusinesscardBook *businesscardBook, Businesscard* index) {
	Node* node;
	Businesscard businesscard;
	node = LinearSearchUnique(&businesscardBook->businesscards, index, CompareBusinesscards);
	GetAt(&businesscardBook->businesscards, node, &businesscard, sizeof(Businesscard));
	node = Delete(&businesscardBook->businesscards, node);
	(businesscardBook->length)--;
	if (businesscardBook->businesscards.current != NULL) {
		businesscardBook->current = (Businesscard*)(businesscardBook->businesscards.current + 1);
	}
	else {
		businesscardBook->current = NULL;
	}

	return businesscard;
}


Long Save(BusinesscardBook *businesscardBook) {
	Businesscard businesscard;
	FILE *fileForPersonals;
	FILE *fileForCompanies;
	Long i = 1;
	Node* index;
	Company company;
	size_t flagForCompanies;
	Long companyNumber;
	Node* previous = NULL;

	fileForPersonals = fopen("Personals.bat", "wb");
	fileForCompanies = fopen("Companies.bat", "wb+");
	if (fileForPersonals != NULL && fileForCompanies != NULL) {
		index = First(&businesscardBook->businesscards);
		while (index != previous) {
			GetAt(&businesscardBook->businesscards, index, &businesscard, sizeof(Businesscard));
			fseek(fileForCompanies, 0L, SEEK_SET);
			flagForCompanies = fread(&company, sizeof(Company), 1, fileForCompanies);
			companyNumber = 1;
			while (!feof(fileForCompanies) && flagForCompanies != 0 && strcmp(company.name, businesscard.company.name) != 0) {
				companyNumber++;
				flagForCompanies = fread(&company, sizeof(Company), 1, fileForCompanies);
			}
			if (flagForCompanies == 0) {
				fwrite(&businesscard.company, sizeof(Company), 1, fileForCompanies);
			}
			fwrite(&companyNumber, sizeof(Long), 1, fileForPersonals);
			fwrite(&businesscard.personal,sizeof(Personal), 1, fileForPersonals);
			previous = index;
			index = Next(&businesscardBook->businesscards);
		}
		fclose(fileForCompanies);
		fclose(fileForPersonals);
	}
	return businesscardBook->length;
}


Businesscard* FindByCompanyName(BusinesscardBook *businesscardBook, char(*name)) {
	Businesscard* index = NULL;
	Node* node;
	node = LinearSearchUnique(&businesscardBook->businesscards, name, CompareCompanyNames);
	if (node != NULL) {
		index = (Businesscard*)(node + 1);
	}
	return index;
}

Businesscard* BusinesscardBook_Move(BusinesscardBook *businesscardBook, Businesscard* index) {
	Node* node;
	node = LinearSearchUnique(&businesscardBook->businesscards, index, CompareBusinesscards);
	node = Move(&businesscardBook->businesscards, node);
	businesscardBook->current = (Businesscard*)(node + 1);

	return businesscardBook->current;
}


void BusinesscardBook_Destroy(BusinesscardBook *businesscardBook) {
	Destroy(&businesscardBook->businesscards);
}

int CompareNames(void* one, void* other) {
	Businesscard* one_ = (Businesscard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->personal.name, other_);
}

int CompareCompanyNames(void* one, void* other) {
	Businesscard* one_ = (Businesscard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->company.name, other_);
}


int CompareBusinesscards(void* one, void* other) {
	int ret;

	if (one > other) {
		ret = 1;
	}
	else if (one == other) {
		ret = 0;
	}
	else if (one < other) {
		ret = -1;
	}

	return ret;
}

