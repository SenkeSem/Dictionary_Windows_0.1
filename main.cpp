#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "Menu.h"

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Windows Desktop");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        700, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindowEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case OnMenuClicked:
            MessageBox(hWnd, L"Menu was clicked", L"Menu worked", MB_OK);
            break;
        case OnEditClear:
            SetWindowTextA(hEditControl, "");
            break;
        case OnExit:
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        break;


    case WM_CREATE:
        MainWndAddMenus(hWnd);
        MainWndAddWidgets(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

void MainWndAddMenus(HWND hWnd)
{
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();

    AppendMenu(SubMenu, MF_STRING, OnMenuClicked, L"menu1");
    AppendMenu(SubMenu, MF_STRING, OnMenuClicked1, L"menu2");
    AppendMenu(SubMenu, MF_STRING, OnMenuClicked2, L"menu3");
    AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(SubMenu, MF_STRING, OnExit, L"exit");

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"file");
    SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
    CreateWindowA("static", "Hello Windows!", WS_VISIBLE | WS_CHILD, 5, 5, 490, 20, hWnd, NULL, NULL, NULL);

    hEditControl = CreateWindowA("edit", "This is edit control!", WS_VISIBLE | WS_CHILD, 5, 25, 490, 20, hWnd, NULL, NULL, NULL);

    CreateWindowA("button", "clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 65, 490, 20, hWnd, (HMENU)OnEditClear, NULL, NULL);
}