/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/2017 01:38:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Medina, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
int main(){
    // for now this file is used to experiment with stuff.
    
    
    unsigned char op = 0x3E;
    unsigned char code = 0xAE;
    unsigned short opcode = (op << 8) | code;
    unsigned char operation = (op & 0xF0) >> 4;
    unsigned char v = op & 0x0F;
    //std::cout << "operation: " << std::bitset<8>(operation) << std::endl;
    std::cout << "v: " << std::bitset<8>(v) << std::endl;
    std::cout << "NN: " << std::bitset<8>(code) << std::endl;
    

    return 0;
}

