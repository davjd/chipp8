/*
 * =====================================================================================
 *
 *       Filename:  CPU.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/11/2017 10:53:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "CPU.h"

CPU::CPU(){
    init();
}

void CPU::init(){
    for(int i = 0; i < register_.size(); ++i){
        register_.at(i) = 0;
    }
    opcode_ = 0;
}
