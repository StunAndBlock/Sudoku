#ifndef SUDOKUAPP_HPP_
#define SUDOKUAPP_HPP_
#include "Logic.hpp"
#include "Gui.hpp"

class SudokuApp{
    public:
        SudokuApp() = default;
        ~SudokuApp();
        int init();
        int start();
    private:
        Logic* ls_;
        Gui* gs_;
};










#endif //!SUDOKUAPP_HPP_