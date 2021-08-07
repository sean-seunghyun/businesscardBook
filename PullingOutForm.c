//PullingOutForm.c
#include "PullingOutForm.h"
#include "BusinesscardBook.h"
#include "resource.h"
#include "Index.h"
#include"IndexBook.h"
#include <CommCtrl.h>

BOOL CALLBACK PullingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = PullingOutForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = PullingOutForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL PullingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinesscardBook *businesscardBook;
	HWND hWndForBusinesscardBook;
	Businesscard businesscard;
	Businesscard* index;
	Businesscard* businesscardLink;
	Index* indexLink;
	Index(*keys);
	Long count;
	Long subscript;
	Long i;
	TVINSERTSTRUCT tvins = { 0, };
	TVITEM tvi = { 0,};
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	TCHAR companyName[8];
	IndexBook *indexBook;

	//2. 빼내기 윈도우가 생성될 때
	//2.1 명함철 윈도우를 찾는다.
	hWndForBusinesscardBook = FindWindow("#32770", "명함철");
	businesscardBook = (BusinesscardBook*)GetWindowLong(hWndForBusinesscardBook, GWL_USERDATA);

	//2.2 명함철 윈도우의 명함철에서 빼낸다.
	index = businesscardBook->current;
	businesscard = PullOut(businesscardBook, index);

	//2.3. 명함철 윈도우의 색인철에서 빼낸다.
	indexBook = (IndexBook*)GetProp(hWndForBusinesscardBook, "indexBook");
	IndexBook_PullOut(indexBook, index, businesscard.company.name);

	//2.4. 명함철 윈도우의 색인철에서 리스트 만들기를 한다.
	MakeList(indexBook, &keys, &count);
	//2.5. 트리뷰의 항목들을 모두 지운다.
	SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);
	//2.6. 명함철 윈도우의 트리뷰에 항목을 추가한다.
	
	tvi.mask = TVIF_TEXT | TVIF_HANDLE;
	tvi.pszText = "회사들";
	tvins.hParent = NULL;
	tvins.item = tvi;
	
		treeRoot = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
		i = 0;
		while (i < count) {
			tvi.pszText = keys[i].companyName;
			tvi.cchTextMax = 8;
			tvins.item = tvi;
			tvins.hParent = treeRoot;
			treeParent = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);


			subscript = 0;
			while (subscript < keys[i].length) {
				businesscardLink = Index_GetAt(keys + i, subscript);
				tvi.pszText = businesscardLink->personal.name;
				tvi.cchTextMax = 11;
				tvins.hParent = treeParent;
				tvins.item = tvi;
				SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
				subscript++;
			}
			i++;
		}
	
	//keys 할당해제
	if (keys != NULL) {
		free(keys);
	}
	//2.6 빼내기 윈도우의 명함컨트롤에 추가한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.personal.cellphoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscard.company.url);
	//2.7 명함이 남아있으면
	if (businesscardBook->current != NULL) {
		//2.7.1 현재 위치의 명함을 명함철 윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.name);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.position);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->personal.emailAddress);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.name);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.address);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.telephoneNumber);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.faxNumber);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businesscardBook->current->company.url);
		//2.7.2 명함철 윈도우의 색인철에서 찾는다. 
		businesscardLink = businesscardBook->current;
		indexLink = IndexBook_Find(indexBook, businesscardLink->company.name);
		//2.7.3. 명함철 윈도우의 색인에서 찾는다. 
		subscript = Index_Find(indexLink, businesscardLink);
		//2.7.4. 트리뷰에서 찾는다.
		treeRoot = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)NULL);
		treeParent = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)treeRoot);

		tvi.pszText = companyName;
		tvi.cchTextMax = 8;
		tvi.hItem = treeParent;
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);
		while (strcmp(companyName, businesscardLink->company.name) != 0) {
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
		//2.7.5 명함철 윈도우의 트리뷰에서 선택한다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)treeRoot);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)treeParent);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)treeChild);

	}
	else {
		//2.5. 명함이 없으면 //2.5.1 공백을 명함철 윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		//2.6. 트리를 모두 지운다.

		//2.7 루트를 추가한다.
	}
	
	return TRUE;
}

BOOL PullingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinesscardBook *businesscardBook;
	HWND hWndForBusinesscardBook;
	Businesscard businesscard;
	Businesscard* index;
	IndexBook *indexBook;
	Index* indexLink;
	Businesscard* businesscardLink;
	Long subscript;
	Index(*keys);
	Long count;
	TVINSERTSTRUCT tvins = { 0, };
	TVITEM tvi = { 0, };
	TCHAR companyName[8];
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	Long i;
	//2. 닫기버튼을 클릭했을 때
	//2.1 메세지박스를 띄운다.

	int response = MessageBox(
		hWnd,
		(LPCTSTR)"명함을 다시 집어넣으시겠습니까?",
		(LPCTSTR)"알림",
		MB_YESNOCANCEL);
	//2.2 예버튼을 클릭했을 때
	if (response == IDYES) {
		//2.2.1 빼내기 윈도우의 명함컨트롤을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME),	WM_GETTEXT, (WPARAM)11, (LPARAM)businesscard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businesscard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businesscard.personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)32, (LPARAM)businesscard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_GETTEXT, (WPARAM)16, (LPARAM)businesscard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)16, (LPARAM)businesscard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)16, (LPARAM)businesscard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)16, (LPARAM)businesscard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_GETTEXT, (WPARAM)16, (LPARAM)businesscard.company.url);
		//businesscard.next = NULL;
		//2.2.2. 명함철 윈도우를 찾는다
		hWndForBusinesscardBook = FindWindow("#32770", "명함철");
		businesscardBook = (BusinesscardBook*)GetWindowLong(hWndForBusinesscardBook, GWL_USERDATA);
		//2.2.3. 명함철 윈도우의 명함에 끼워넣는다.
		index = PutIn(businesscardBook, businesscard);
		//2.2.4. 명함철 윈도우의 색인철에 끼워넣는다.
		indexBook = (IndexBook*)GetProp(hWndForBusinesscardBook, "indexBook");
		indexLink = IndexBook_PutIn(indexBook, index);
		//2.2.5. 리스트 만들기를 한다.
		MakeList(indexBook, &keys, &count);
		//2.2.6. 명함철 윈도우의 트리뷰 항목을 모두 지운다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)NULL);
		//2.2.7. 명함철 윈도우의 트리뷰에 항목을 추가한다.
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.pszText = "회사들";
		tvins.hParent = NULL;
		tvins.item = tvi;
		treeRoot = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
		i = 0;
		while (i < count) {
			tvi.pszText = keys[i].companyName;
			tvi.cchTextMax = 8;
			tvins.hParent = treeRoot;
			tvins.item = tvi;
			treeParent = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);

			subscript = 0;
			while (subscript < keys[i].length) {
				businesscardLink = Index_GetAt(keys + i, subscript);
				tvi.pszText = businesscardLink->personal.name;
				tvi.cchTextMax = 11;
				tvins.hParent = treeParent;
				tvins.item = tvi;
				SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
				subscript++;
			}
			i++;
		}

		if (keys != NULL) {
			free(keys);
		}
		//2.2.8. 명함철 윈도우의 명함컨트롤에 현대위치는 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_CELLPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.cellphoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);

		//2.2.9. 명함철 윈도우의 색인철에서 찾는다.
		indexLink = IndexBook_Find(indexBook, index->company.name);
		//2.2.10. 명함철 윈도우의 색인에서 찾는다.
		subscript = Index_Find(indexLink, index);
		//2.2.11. 트리뷰에서 찾는다.
		treeParent = SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)treeRoot);
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
		//2.2.12. 명함철 윈도우의 트리뷰에서 선택한다.
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)treeRoot);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)treeParent);
		SendMessage(GetDlgItem(hWndForBusinesscardBook, IDC_TREE_INDEXES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)treeChild);
		//2.13 끼워넣기 윈도우를 닫는다.
		
		//2.2.6. 빼내기 윈도우를 닫는다.
		//2.2.6. 빼내기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		
	}
	//2.3. 아니오 버튼을 클릭했을 때
	else if (response == IDNO) {
		//2.3.1 빼내기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		
	}
	
	return TRUE;
}
