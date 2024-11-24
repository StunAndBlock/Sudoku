#ifndef MENU_HPP_
#define MENU_HPP_
#include "StunAndBlock/san_winapi_gui.hpp"
#include "../Global.hpp"

class Menu : private GuiBase {
    public:
        Menu();
        LRESULT SetupWin(RECT, HWND) override;
        static LRESULT __stdcall OptionsWinProc(HWND , UINT , WPARAM , LPARAM );
        static LRESULT __stdcall StatsWinProc(HWND , UINT , WPARAM , LPARAM );
        static LRESULT __stdcall BackWinProc(HWND , UINT , WPARAM , LPARAM );
        static LRESULT __stdcall DifficultiesWinProc(HWND , UINT , WPARAM , LPARAM );
        static LRESULT __stdcall DifficultyOptionWinProc(HWND , UINT , WPARAM , LPARAM );
    private:
        wchar_t optionsText_[3][10] = {{L"stats"},{L"new game"},{L"???"}};
        wchar_t difficultiesText_[5][10] = {{L"Easy"},{L"Medium"}, {L"Hard"}, {L"Extreame"}, {L"Nightmare"}};
        HWND options_[3];
        HWND stats_;
        HWND chooseDifficulty_;
        HWND difficulties_[5];
        HWND whaaat_;
        HWND back_;
        LRESULT __stdcall Handler(HWND, UINT , WPARAM , LPARAM) override;
        LRESULT __stdcall OptionsHandler(HWND, UINT , WPARAM , LPARAM, uint8_t);
        LRESULT __stdcall StatsHandler(HWND, UINT , WPARAM , LPARAM, uint8_t);
        LRESULT __stdcall BackHandler(HWND, UINT , WPARAM , LPARAM);
        LRESULT __stdcall DifficultyOptionHandler(HWND, UINT , WPARAM , LPARAM, uint8_t);
        void Show() override;
};














#endif //!MENU_HPP_