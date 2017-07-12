/*
 * =====================================================================================
 *
 *       Filename:  Chip8.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/2017 01:27:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Medina, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Chip8.h"

Chip8::Chip8(){
    init();
}

void Chip8::init(){
    cpu_ = std::make_unique<CPU>();
    opcode_ = 0x0;
    pCtr_ = 0x200;
    index_ = 0x0;
    stackPtr_ = 0x0;

    stack_.fill(0);
    graphics_.fill(0);
    keys_.fill(0);
    
    for(int i = 0; i < 80; ++i){
        memory_.at(i) = fontset_[i];
    }
    for(int i = 80; i < memory_.size(); ++i){
        memory_.at(i) = 0;
    }
    
    delayTimer_ = 0x0;
    soundTimer_ = 0x0;
}

void Chip8::load(){
    // load the game.
}
