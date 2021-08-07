//BusinesscardBookForm.h
#ifndef _BUSINESSCARDBOOKFORM_H
#define _BUSINESSCARDBOOKFORM_H
#include <Windows.h>
#include <stdlib.h>

BOOL CALLBACK BusinesscardBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnPuttingInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnFindingButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnPullingOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnArrangingButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnTreeView(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinesscardBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif //_BUSINESSCARDBOOKFORM_H