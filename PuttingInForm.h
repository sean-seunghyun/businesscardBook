//PuttingInForm.h
#ifndef _PUTTINGINFORM_H
#define _PUTTINGINFORM_H
#include<Windows.h>
BOOL CALLBACK PuttingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL PuttingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PuttingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PuttingInForm_OnPuttingInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PuttingInForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PuttingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif //_PUTTINGINFORM_H