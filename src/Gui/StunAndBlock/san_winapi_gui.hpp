#ifndef SAN_WINAPI_GUI_HPP_
#define SAN_WINAPI_GUI_HPP_
#include <Windows.h>


#ifdef SAN_WINAPI_GUI_EXPORTS
#define SAN_WINAPI_GUI_LIB __declspec(dllexport)
#else
#define SAN_WINAPI_GUI_LIB __declspec(dllimport)
#endif


class SAN_WINAPI_GUI_LIB GuiBase{
    protected:
        HWND hMain_;
        virtual LRESULT __stdcall Handler(HWND , UINT , WPARAM , LPARAM );
    public:
        static LRESULT __stdcall WindowProc(HWND , UINT , WPARAM , LPARAM );
        GuiBase();
        virtual ~GuiBase() = default;
        virtual void Show();
        virtual LRESULT SetupWin(RECT, HWND) = 0;
};


















#endif //!SAN_WINAPI_GUI_HPP_
