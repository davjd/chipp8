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
#include <fstream>
#include <iostream>
#include <vector>

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

void Chip8::load(const std::string &path){
    std::ifstream rom(path, std::ios::binary);
    if(rom){
        std::vector<unsigned char> buffer(
                (std::istreambuf_iterator<char>(rom)),
                (std::istreambuf_iterator<char>()));
        if(buffer.size() > (4096 - 512)){
            std::cerr << "The size of the ROM file is too large." << std::endl;
        } else{
            for(int i = 0; i < buffer.size(); ++i){
                memory_.at(i + 512) = buffer.at(i);
            }
            std::cout << "ROM file has been copied successfully." << std::endl;
        }
    } else{
        std::cerr << "ROM file couldn't be opened." << std::endl;
    }
}
