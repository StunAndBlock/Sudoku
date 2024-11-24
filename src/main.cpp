#include "App/SudokuApp.hpp"




int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                        LPWSTR lpCmdLine, int nShowCmd){
    SudokuApp app;
    app.init(hInstance, lpCmdLine, nShowCmd);
    app.start();




    return 0;
}


