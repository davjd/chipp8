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
    opcode_ = 0x0;
    pCtr_ = 0x200;
    index_ = 0x0;
    stackPtr_ = 0x0;

    for(int i = 0; i < 16; ++i){
        stack_.at(i) = 0;
        keys_.at(i) = 0;
        register_.at(i) = 0;
    }

    graphics_.fill(0);
    fontset_=
        {{ 
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        }};
    
    for(int i = 0; i < 80; ++i){
        memory_.at(i) = fontset_[i];
    }
    for(size_t i = 80; i < memory_.size(); ++i){
        memory_.at(i) = 0;
    }
    
    delayTimer_ = 0x0;
    soundTimer_ = 0x0;
}

void Chip8::load(const std::string &path){
    std::ifstream rom(path, std::ios::binary|std::ios::ate);
    if(rom){
        auto size = rom.tellg();

        if(size > (4096 - 512)){
            std::cerr << "The size of the ROM file is too large to be loaded." << std::endl;
        } else{
            auto buffer = new char[size];
            rom.seekg(0, std::ios::beg);
            rom.read(buffer, size);
            
            for(int i = 0; i < size; ++i){
                memory_.at(i + 512) = ((unsigned char) buffer[i]);
            }

            std::cout << "The ROM file has been loaded successfully." 
                << std::endl;
        }
        rom.close();
    } else{
        std::cerr << "The ROM file couldn't be opened." << std::endl;
    }
}

void Chip8::cycle(){
    // fetch opcode.
    opcode_ = memory_[pCtr_] << 8 | memory_[pCtr_ + 1];

    // decode opcode by isolating left-most bit.
    switch((opcode_ & 0xF0) >> 4){
        case 0x0:{
                     switch(memory_[pCtr_ + 1]){
                        case 0xE0 :{
                                       graphics_.fill(0);
                                   }
                                   break;
                        case 0xEE :{

                                   }
                                   break;
                        default: 
                                   undefineOpcode(); 
                     }
                 }
                 break;
        case 0x1:{
                     pCtr_ = opcode_ & 0x0FFF;
                 }
                 break;
        case 0x2:{
                    pCtr_ = opcode_ & 0x0FFF;
                    cycle();
                 }
                 break;
        case 0x3:{
                     if(register_[memory_[pCtr_] & 0x0F] 
                             == memory_[pCtr_ + 1]){
                         pCtr_ += 4;
                     }
                 }
                 break;
        case 0x4:{
                     if(register_[memory_[pCtr_] & 0x0F] 
                             != memory_[pCtr_ + 1]){
                         pCtr_ += 4;
                     }
                 }
                 break;
        case 0x5:{
                     if(register_[memory_[pCtr_] & 0x0F] 
                            == register_[memory_[pCtr_ + 1]]){
                         pCtr_ += 4;
                     } 
                 }
                 break;
        case 0x6:{

                 }
                 break;
        case 0x7:{

                 }
                 break;
        case 0x8:{

                 }
                 break;
        case 0x9:{

                 }
                 break;
        case 0xA:{

                 }
                 break;
        case 0xB:{

                 }
                 break;
        case 0xC:{

                 }
                 break;
        case 0xD:{

                 }
                 break;
        case 0xE:{

                 }
                 break;
        case 0xF:{

                 }
                 break;
        default: undefineOpcode();
    }
}

void Chip8::undefineOpcode() noexcept{
    std::cout << "Opcode is undefined." << std::endl;
}
