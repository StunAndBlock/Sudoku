#include "Menu.hpp"
#include <iostream>
Menu::Menu() : GuiBase() {

};

LRESULT Menu::SetupWin(RECT wm, HWND hParent = NULL){
    WNDCLASSEXW wc = {};
    const wchar_t CLASS_NAME[]  = L"Sudoku menu";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(192, 192, 192));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hParent, GWLP_HINSTANCE));
    wc.lpszClassName = CLASS_NAME;
    RegisterClassExW(&wc);
    // Main
    hMain_ = CreateWindowExW(      
        0,                          // Optional window styles.
        CLASS_NAME,                     // Window class
        L"",    // Window text
        WS_CHILD,            // Window style

        // Size and position
        wm.left, wm.top, wm.right, wm.bottom,

        hParent,       // Parent window    
        NULL,       // Menu
        wc.hInstance,  // Instance handle
        this        // Additional application data
    );
    // Options
    const wchar_t CLASS_NAME_OPTIONS[]  = L"Sudoku options";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = OptionsWinProc;
    wc.hInstance     = wc.hInstance; 
    wc.lpszClassName = CLASS_NAME_OPTIONS;
    RegisterClassExW(&wc);



    for (uint8_t i = 0; i < 3; i++){
        std::pair<Menu*, uint8_t>* winData = new std::pair<Menu*, uint8_t>(this, i);
        options_[i] = CreateWindowExW(      
            0,                          // Optional window styles.
            CLASS_NAME_OPTIONS,                     // Window class
            L"",    // Window text
            WS_CHILD,            // Window style

            // Size and position
            (10)*(i+1) + (150)*i, 10, 150, 180,

            hMain_,       // Parent window    
            NULL,       
            wc.hInstance,  // Instance handle
            winData        // Additional application data
        );
    }

    //stats
    const wchar_t CLASS_NAME_STATS[]  = L"Sudoku stats";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = StatsWinProc;
    wc.hInstance     = wc.hInstance; 
    wc.lpszClassName = CLASS_NAME_STATS;
    RegisterClassExW(&wc);

    std::pair<Menu*, uint8_t>* statsData = new std::pair<Menu*, uint8_t>(this, 0);
    stats_ = CreateWindowExW(      
        0,                          // Optional window styles.
        CLASS_NAME_STATS,                     // Window class
        L"",    // Window text
        WS_CHILD,            // Window style

        // Size and position
        50, 50, 500, 700,

        hParent,       // Parent window    
        NULL,       
        wc.hInstance,  // Instance handle
        statsData        // Additional application data
    );

    //difficulties
    const wchar_t CLASS_NAME_DIFFICULTIES[]  = L"Sudoku difficulties";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(192, 192, 192));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = DifficultiesWinProc;
    wc.hInstance     = wc.hInstance; 
    wc.lpszClassName = CLASS_NAME_DIFFICULTIES;
    RegisterClassExW(&wc);

    chooseDifficulty_ = CreateWindowExW(      
        0,                          // Optional window styles.
        CLASS_NAME_DIFFICULTIES,                     // Window class
        L"",    // Window text
        WS_CHILD,            // Window style

        // Size and position
        200, 50, 200, 700,

        hParent,       // Parent window    
        NULL,       
        wc.hInstance,  // Instance handle
        NULL        // Additional application data
    );
    const wchar_t CLASS_NAME_DIFFICULTIOPT[]  = L"Sudoku difficulty options";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = DifficultyOptionWinProc;
    wc.hInstance     = wc.hInstance; 
    wc.lpszClassName = CLASS_NAME_DIFFICULTIOPT;

    RegisterClassExW(&wc);
    for (uint8_t i = 0; i < 5; i++){
        std::pair<Menu*, uint8_t>* optionsData = new std::pair<Menu*, uint8_t>(this, i);
        difficulties_[i] = CreateWindowExW(      
            0,                          // Optional window styles.
            CLASS_NAME_DIFFICULTIOPT,                     // Window class
            L"",    // Window text
            WS_CHILD,            // Window style

            // Size and position
            10, (10)*(i+1) + (100)*i, 150, 100,

            chooseDifficulty_,       // Parent window    
            NULL,       
            wc.hInstance,  // Instance handle
            optionsData        // Additional application data
        );
    }
    //back putton
    const wchar_t CLASS_NAME_BACK[]  = L"Sudoku back";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW ;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.lpfnWndProc   = BackWinProc;
    wc.hInstance     = wc.hInstance; 
    wc.lpszClassName = CLASS_NAME_BACK;
    RegisterClassExW(&wc);

    // std::pair<Menu*, uint8_t>* statsData = new std::pair<Menu*, uint8_t>(this, 0);
    back_ = CreateWindowExW(      
        0,                          // Optional window styles.
        CLASS_NAME_BACK,                     // Window class
        L"",    // Window text
        WS_CHILD,            // Window style

        // Size and position
        450, 650, 50, 70,

        stats_,       // Parent window    
        NULL,       
        wc.hInstance,  // Instance handle
        this        // Additional application data
    );

    Show();
    return true;
}


void Menu::Show(){
    ShowWindow(hMain_, SW_SHOW);
    UpdateWindow(hMain_);
    for (uint8_t i = 0; i < 3; i++){
        ShowWindow(options_[i], SW_SHOW);
        UpdateWindow(options_[i]);
    }
    for (uint8_t i = 0; i < 5; i++){
        ShowWindow(difficulties_[i], SW_SHOW);
        UpdateWindow(difficulties_[i]);
    }
    ShowWindow(back_, SW_SHOW);
    UpdateWindow(back_);
}











/* start of WinApi-related block
-----------------------------*/
LRESULT __stdcall Menu::Handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg)
    {    
    // case WM_LBUTTONDOWN:
    //     PostQuitMessage(0);
    //     break;
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT __stdcall Menu::OptionsHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, uint8_t index){
    switch (msg)
    {    
    case WM_LBUTTONDOWN:
        ShowWindow(hMain_, SW_HIDE);
        switch (index)
        {
        case 0:
            ShowWindow(stats_, SW_SHOW);
            UpdateWindow(stats_);
            break;
        case 1:
            ShowWindow(chooseDifficulty_, SW_SHOW);
            UpdateWindow(chooseDifficulty_);
            break;
        default:
            break;
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            SetTextColor(hdc, RGB(0, 0, 255));
            SetBkMode(hdc, TRANSPARENT);      
            TextOutW(hdc, 10, 10, optionsText_[index], 10);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT __stdcall Menu::OptionsWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    std::pair<Menu*, uint8_t>* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        pThis = reinterpret_cast<std::pair<Menu*, uint8_t>*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<std::pair<Menu*, uint8_t>*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->first->OptionsHandler(hwnd, msg, wParam, lParam, pThis->second);
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}



//stats

LRESULT __stdcall Menu::StatsHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, uint8_t index){
    switch (msg)
    {    
    case WM_LBUTTONDOWN:
        //
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            SetTextColor(hdc, RGB(0, 0, 255));
            SetBkMode(hdc, TRANSPARENT);      
            TextOutW(hdc, 10, 10, optionsText_[index], 10);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT __stdcall Menu::StatsWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    std::pair<Menu*, uint8_t>* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        pThis = reinterpret_cast<std::pair<Menu*, uint8_t>*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<std::pair<Menu*, uint8_t>*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->first->StatsHandler(hwnd, msg, wParam, lParam, pThis->second);
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}


LRESULT __stdcall Menu::BackHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg)
    {    
    case WM_LBUTTONDOWN:
        ShowWindow(stats_, SW_HIDE);
        ShowWindow(hMain_, SW_SHOW);
        UpdateWindow(hMain_);
        break;
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT __stdcall Menu::BackWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Menu* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        pThis = reinterpret_cast<Menu*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<Menu*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->BackHandler(hwnd, msg, wParam, lParam);
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}


LRESULT __stdcall Menu::DifficultiesWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}


LRESULT __stdcall Menu::DifficultyOptionHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, uint8_t index){
    switch (msg)
    {    
    case WM_LBUTTONDOWN:
        std::cout << (int)index;
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            SetTextColor(hdc, RGB(0, 0, 255));
            SetBkMode(hdc, TRANSPARENT);      
            TextOutW(hdc, 10, 10, difficultiesText_[index], 10);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_CREATE:
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT __stdcall Menu::DifficultyOptionWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    std::pair<Menu*, uint8_t>* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        pThis = reinterpret_cast<std::pair<Menu*, uint8_t>*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<std::pair<Menu*, uint8_t>*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->first->DifficultyOptionHandler(hwnd, msg, wParam, lParam, pThis->second);
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
/* End of WinApi-related block, start of logic block
-------------------------------------------------*/