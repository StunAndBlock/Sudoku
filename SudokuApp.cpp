#include "SudokuApp.hpp"

SudokuApp::~SudokuApp(){
    delete ls_;
    delete gs_;
}


int SudokuApp::init(){
    try {
    ls_ = new Logic();
    gs_ = new Gui();
    } catch (const std::bad_alloc& e){
        return -1;
    }

     ls_->init();

    return 0;
}
int SudokuApp::start(){
    ls_->create();
    ls_->meshOut();
    return 0;
}