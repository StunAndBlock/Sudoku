#ifndef SUDOKUAPP_HPP_
#define SUDOKUAPP_HPP_
#include "Logic.hpp"
#include "Gui.hpp"

class SudokuApp{
    Logic* ls_;
    Gui* gs_;

    public:
    SudokuApp() = default;
    ~SudokuApp();
    int init();
    int start();
};










#endif //!SUDOKUAPP_HPP_