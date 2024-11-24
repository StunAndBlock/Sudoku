#include "Gui.hpp"

// Gui::Gui(HINSTANCE hInst, LPWSTR args, int nShowCmd) : GuiBase(){
//     if (args){

//         //parser
//         //Log(L"NO ARGS");
//     }
//     hInst_ = hInst;
//     nShowCmd_ = nShowCmd;
// }



int Gui::init(HINSTANCE hInst, LPWSTR args, int nShowCmd){
    if (args){

        //parser
        //Log(L"NO ARGS");
    }
    hInst_ = hInst;
    nShowCmd_ = nShowCmd;
    return 1;
}

int Gui::create(){
    RECT wm = {200, 200, 600, 800};
    SetupWin(wm);
    wm = {50, 300, 500, 200};
    menu_.SetupWin(wm, hMain_);
    return 1;
}



bool Gui::dispatch() {
    HACCEL hAccelTable = LoadAcceleratorsW(hInst_, MAKEINTRESOURCEW(109));
    MSG msg = { };
    while (GetMessageW(&msg, NULL, 0, 0) > 0)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return true;
}




LRESULT __stdcall Gui::Handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg)
    {
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT Gui::SetupWin(RECT wm, HWND hParent){
    WNDCLASSEXW wc = {};
    const wchar_t CLASS_NAME[]  = L"Sudoku root";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInst_;
    wc.lpszClassName = CLASS_NAME;
    RegisterClassExW(&wc);

    hMain_ = CreateWindowExW(      
        0,                          // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Sudoku",    // Window text
        WS_OVERLAPPED,            // Window style

        // Size and position
        wm.left, wm.top, wm.right, wm.bottom,

        hParent,       // Parent window    
        NULL,       // Menu
        wc.hInstance,  // Instance handle
        this        // Additional application data
    );
    Show();
    return true;
}

void Gui::Show(){
    ShowWindow(hMain_, SW_SHOW);
    UpdateWindow(hMain_);
}