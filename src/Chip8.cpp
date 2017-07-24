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
                                       pCtr_ = stack_[--stackPtr_];
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
                     stack_[stackPtr_] = pCtr_;
                     ++stackPtr_;
                     pCtr_ = opcode_ & 0x0FFF;
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
                     register_[memory_[pCtr_] & 0x0F] = memory_[pCtr_ + 1];
                 }
                 break;
        case 0x7:{
                     register_[memory_[pCtr_] & 0x0F] += memory_[pCtr_ + 1];

                 }
                 break;
        case 0x8:{
                     switch(memory_[pCtr_ + 1] & 0x0F){
                         case 0:{
                                    register_[memory_[pCtr_] & 0x0F] 
                                        = register_[memory_[pCtr_ + 1] & 0xF]; 
                                }
                                break;
                         case 1:{
                                    register_[memory_[pCtr_] & 0x0F] |= register_[(memory_[pCtr_ + 1] & 0xF)];
                                }
                                break;
                         case 2:{
                                    register_[memory_[pCtr_] & 0x0F] &= register_[(memory_[pCtr_ + 1] & 0xF)];

                                }
                                break;
                         case 3:{
                                    register_[memory_[pCtr_] & 0x0F] ^= register_[(memory_[pCtr_ + 1] & 0xF)];
                                }
                                break;
                         case 4:{
                                    register_[memory_[pCtr_] & 0x0F] += register_[memory_[pCtr_ + 1] & 0xF];
                                    if(register_[memory_[pCtr_] & 0x0F] > 0xFF){
                                        register_[0xF] = 1;
                                    }
                                    else register_[0xF] = 0;
                                }
                                break;
                         case 5:{
                                    if(register_[memory_[pCtr_] & 0x0F] < register_[memory_[pCtr_ + 1] & 0xF]){
                                        register_[0xF] = 0;
                                    }
                                    else register_[0xF] = 1;

                                    register_[memory_[pCtr_] & 0x0F] -= register_[memory_[pCtr_ + 1] & 0xF];
                                }
                                break;
                         case 6:{
                                    register_[0xF] = register_[memory_[pCtr_] & 0x0F] & 0x1;
                                    register_[memory_[pCtr_] & 0x0F] >>= 1;
                                }
                                break;
                         case 7:{
                                    if(register_[memory_[pCtr_ + 1] & 0xF] < register_[memory_[pCtr_] & 0x0F]){
                                        register_[0xF] = 0;

                                    }
                                    else register_[0xF] = 1;

                                    register_[memory_[pCtr_] & 0x0F] = register_[memory_[pCtr_ + 1] & 0xF] 
                                        - register_[memory_[pCtr_] & 0x0F];
                                }
                                break;
                         case 0xE:{
                                      register_[0xF] = register_[memory_[pCtr_] & 0x0F] >> 7;
                                      register_[memory_[pCtr_] & 0x0F] <<= 1;
                                  }
                                  break;
                         default:{
                                     undefineOpcode();
                                 }
                     }
                 }
                 break;
        case 0x9:{
                     if(register_[memory_[pCtr_] & 0x0F] != register_[memory_[pCtr_ + 1] & 0xF]){
                         pCtr_ += 4;
                     }
                 }
                 break;
        case 0xA:{
                     index_ = opcode_ & 0x0FFF;
                 }
                 break;
        case 0xB:{
                     pCtr_ = register_[0] + (opcode_ & 0x0FFF);
                 }
                 break;
        case 0xC:{
                     register_[memory_[pCtr_] & 0x0F] = 1 & memory_[pCtr_ + 1];
                     // 1 can be changed to any number between 0 - 255.
                 }
                 break;
        case 0xD:{
                     //draw(register_[memory_[pCtr_] & 0x0F], register_[memory_[pCtr + 1] & 0xF], memory_[pCtr_ + 1] & 0x0F);
                     //TODO: implement draw.
                 }
                 break;
        case 0xE:{
                     switch(memory_[pCtr_ + 1]){
                         case 0x9E:{
                                       if(key() == (register_[memory_[pCtr_] & 0x0F])){
                                           pCtr_ += 4;
                                       }
                                   }
                                   break;
                         case 0xA1:{
                                       if(key() != (register_[memory_[pCtr_] & 0x0F])){
                                           pCtr_ += 4;
                                       }
                                   }
                                   break;
                         default:{
                                     undefineOpcode();
                                 }
                     }
                 }
                 break;
        case 0xF:{
                     switch(memory_[pCtr_ + 1]){
                         case 0x07:{
                                       register_[memory_[pCtr_] & 0x0F]
                                           = delay();
                                   }
                                   break;
                         case 0x0A:{
                                       register_[memory_[pCtr_] & 0x0F]
                                           = key();
                                  }
                                  break;
                         case 0x15:{
                                       setDelay(register_[memory_[pCtr_] 
                                               & 0x0F]);
                                   }
                                   break;
                         case 0x18:{
                                       setSound(register_[memory_[pCtr_]
                                               & 0x0F]);
                                   }
                                   break;
                         case 0x1E:{
                                       index_ += register_[memory_[pCtr_]
                                           & 0x0F];
                                   }
                                   break;
                         case 0x29:{
                                       index_ = spriteAdress_[
                                           register_[memory_[pCtr_] 
                                               & 0x0F]];
                                   }
                                   break;
                         case 0x33:{

                                   }
                                   break;
                         case 0x55:{
                                       // TODO: change register_.size() to Vx.
                                       for(int i = 0; i < register_.size(); ++i){
                                           memory_[index_ + i] = register_[i];
                                       }
                                   }
                                   break;
                         case 0x65:{
                                       for(int i = 0; i < register_.size(); ++i){
                                           register_[i] = memory_[index_ + i];
                                       }
                                   }
                                   break;
                         default: undefineOpcode();
                     }
                 }
                 break;

        default: undefineOpcode();
    }
}
unsigned char Chip8::delay() noexcept{
    return delayTimer_;
}

unsigned short Chip8::key() noexcept{
    return 0xF;
    // TODO: integrate SDL into this method.
}

//TODO: implement setters.
void Chip8::setDelay(unsigned char delay) noexcept{
    delayTimer_ = delay;
}

void Chip8::setSound(unsigned char sound) noexcept{
    soundTimer_ = sound;
}

void Chip8::undefineOpcode() noexcept{
    std::cout << "Opcode is undefined." << std::endl;
}
