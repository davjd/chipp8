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
    
    
    unsigned char op = 0x1E;
    unsigned char code = 0xEE;
    unsigned short opcode = (op << 8) | code;
    unsigned char operation = (op & 0xF0) >> 4;
    unsigned short item = opcode & 0x0FFF;

    //std::cout << "operation: " << std::bitset<8>(operation) << std::endl;
    std::cout << "item: " << std::bitset<16>(item) << std::endl;
    

    return 0;
}

