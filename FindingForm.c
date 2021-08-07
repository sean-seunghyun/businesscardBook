#include "FindingForm.h"
#include "BusinesscardBook.h"
#include "resource.h"
#include "Index.h"
#include"IndexBook.h"
#include <CommCtrl.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {

	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;

	case WM_CLOSE: ret=FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FINDING:
		ret = FindingForm_OnFindingButtonClicked(hWnd, wParam, lParam); break;

	case IDC_BUTTON_FIRST:
		ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;

	case IDC_BUTTON_PREVIOUS:
		ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;

	case IDC_BUTTON_NEXT:
		ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;

	case IDC_BUTTON_LAST:
		ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;

	case IDC_BUTTON_SELECTING:
		ret = FindingForm_OnSelectingButtonClicked(hWnd, wParam, lParam); break;

	default: ret = FALSE; break;
	}
	return ret;
}


BOOL FindingForm_OnFindingButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char name[11];
	HWND hWndForBusinesscardBook;
	BusinesscardBook *businesscardBook;
	Long count;
	Businesscard* (*indexes);
	Long i = 0;

	//1. 찾기버튼을 클릭헀을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//1.1 개인컨트롤의 성명을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		//1.2 명함철 윈도우를 찾는다.
		hWndForBusinesscardBook = FindWindow("#32770", "명함철");
		businesscardBook = (BusinesscardBook*)GetWindowLong(hWndForBusinesscardBook, GWL_USERDATA);
		//1.3 명함철 윈도우의 명함철에서 찾는다.
		indexes = (Businesscard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}
		Find(businesscardBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);

		
		SetProp(hWnd, "count", (HANDLE)count);
		SetProp(hWnd, "current", (HANDLE)0);
		//1.4.찾은 명함의 첫번째를 찾기 윈도우의 명함에 출력한다.
		if (count > 0) {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.cellphoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.url);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}



BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Businesscard* (*indexes);
	Long current;
	//3. 이동하기의 이전 명함을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1 이전번째 명함을 명함컨트롤에 출력한다.
		indexes = (Businesscard(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		current--;
		if (current < 0) {
			current = 0;
		}
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}


BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Businesscard* (*indexes);
	Long count;
	Long i = 0;
	//2. 이동하기의 첫번째 명함을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 첫번째 명함을 명함철에 출력한다.
		indexes = (Businesscard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.url);
		SetProp(hWnd, "current", (HANDLE)0);
	}
	return TRUE;
}



BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Businesscard* (*indexes);
	Long current;
	Long count;
	//4. 이동하기의 다음명함을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1 다음번째 명함을 명함컨트롤에 출력한다.
		indexes = (Businesscard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		count = (Long)GetProp(hWnd, "count");
		current++;
		if (current >= count) {
			current = count - 1;
		}
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return TRUE;
}


BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Businesscard* (*indexes);
	Long count;
	Long i;
	//5. 마지막번째 명함을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1 마지막번째 명함을 명함컨트롤에 출력한다.
	
	indexes = (Businesscard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	count = (Long)GetProp(hWnd, "count");
	i = count - 1;
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.cellphoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[i]->company.url);
	SetProp(hWnd, "current", (HANDLE)i);
	}
	return TRUE;
}



BOOL FindingForm_OnSelectingButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinesscardBook *businesscardBook;
	Long current;
	Long subscript;
	TVITEM tvi = { 0, };
	TCHAR companyName[8];
	HWND hWndForBusinesscardBook;
	Businesscard* index;
	Businesscard* (*indexes);
	Businesscard* businesscardLink;
	Long i;
	IndexBook *indexBook;
	Index* indexLink;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	

	//6. 선택하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1 명함철 윈도우를 찾는다.
		hWndForBusinesscardBook = FindWindow("#32770", "명함철");
		businesscardBook = (BusinesscardBook*)GetWindowLong(hWndForBusinesscardBook, GWL_USERDATA);
		//6.2 명함철 윈도우에서 해당명함으로 이동한다.
		current = (Long)GetProp(hWnd, "current");
		indexes = (Businesscard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = indexes[current];
		businesscardLink=BusinesscardBook_Move(businesscardBook, index);
		//6.3 명함철 윈도우의 명함컨트롤에 현재위치의 명함을 출력한다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.name);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.position);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.emailAddress);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.name);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.address);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.faxNumber);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.url);
		//6.4. 명함철 윈도우의 색인철에서 찾는다.
		indexBook = (IndexBook*)GetProp(hWndForBusinesscardBook, "indexBook");
		indexLink = IndexBook_Find(indexBook, businesscardLink->company.name);
		//6.5. 명함철 윈도우의 색인에서 찾는다.
		subscript = Index_Find(indexLink, businesscardLink);
		//6.6. 트리뷰에서 찾는다.
		treeRoot = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		treeParent = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)treeRoot);
		
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.pszText = companyName;
		tvi.cchTextMax = 8;
		tvi.hItem = treeParent;
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);
		while (strcmp(companyName, indexLink->companyName) != 0) {
			treeParent = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)treeParent);
			tvi.hItem = treeParent;
			SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);
		}
		treeChild = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)treeParent);
		i = 0;
		while (i < subscript) {
			treeChild = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)treeChild);
			i++;
		}
		//6.7 명함철 윈도우의 트리뷰에서 선택한다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)treeRoot);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)treeParent);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)treeChild);

		//6.4 찾기 윈도우를 닫는다.
		RemoveProp(hWnd, "current");
		RemoveProp(hWnd, "count");
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long current;
	Long count;
	Businesscard* (*indexes);

	RemoveProp(hWnd, "current");
	RemoveProp(hWnd, "count");
	indexes = (Businesscard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	EndDialog(hWnd, 0);
	return TRUE;
}