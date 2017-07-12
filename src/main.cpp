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
#include <functional>

int main(){
    // for now this file is used to experiment with stuff.
    
    /*
    unsigned char op = 0xA2;
    unsigned char code = 0xF0;
    unsigned short opcode = (op << 8) | code;
    unsigned char operation = op & 0xF0;
    //std::cout << std::bitset<8>(operation) << std::endl;
    */

    std::function<void()> lambda = [](){
        std::cout << "hello" << std::endl;
    };

    lambda();





    return 0;
}

