#ifndef SUDOKUAPP_HPP_
#define SUDOKUAPP_HPP_
#include "../Logic/Logic.hpp"
#include "../Gui/Gui.hpp"

class SudokuApp{
    public:
        SudokuApp() = default;
        ~SudokuApp();
        int init(HINSTANCE, LPWSTR, int);
        int start();
    private:
        Logic* ls_;
        Gui* gs_;
};










#endif //!SUDOKUAPP_HPP_