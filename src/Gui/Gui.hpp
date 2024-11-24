#ifndef GUI_HPP_
#define GUI_HPP_
#include "Menu.hpp"
class Gui : private GuiBase {
    public:
        Gui() = default;
        int init(HINSTANCE, LPWSTR, int );
        int create();
        bool dispatch();
    private:
        HINSTANCE hInst_;
        int nShowCmd_;
        Menu menu_;
        
        LRESULT __stdcall Handler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
        LRESULT SetupWin(RECT, HWND = NULL) override;
        void Show() override;

    
};











#endif //!GUI_HPP_
