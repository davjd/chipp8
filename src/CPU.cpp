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
    register_.fill(0);
    opcode_ = 0;
}
