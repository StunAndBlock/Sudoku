#include "SudokuApp.hpp"

SudokuApp::~SudokuApp(){
    delete ls_;
    delete gs_;
}


int SudokuApp::init(HINSTANCE hInst, LPWSTR args, int nShowCmd){
    try {
        ls_ = new Logic();
        gs_ = new Gui();
    } catch (const std::bad_alloc& e){
        return -1;
    }

    ls_->init();
    gs_->init(hInst, args, nShowCmd);
    return 0;
}
int SudokuApp::start(){
    // ls_->create();
    gs_->create();
    gs_->dispatch();
    return 0;
}


