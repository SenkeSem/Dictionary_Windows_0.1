#pragma once

#define OnMenuClicked	1
#define OnMenuClicked1	2
#define OnMenuClicked2	3
#define OnExit	4
#define OnEditClear	5
#define OnReadEdit	6
#define OnSaveFile	7
#define OnLoadFile	8

#define TextBufferSize	40

char Buffer[TextBufferSize];

HWND hStaticControl;
HWND hEditControl;

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
