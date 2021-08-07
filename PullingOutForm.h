//PullingOutForm.h
#ifndef _PULLINGOUTFORM_H
#define _PULLINGOUTFORM_H
#include<Windows.h>
BOOL CALLBACK PullingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL PullingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PullingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif//_PULLINGOUTFORM_H