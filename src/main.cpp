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
    
    /*
    unsigned char op = 0xA2;
    unsigned char code = 0xF0;
    unsigned short opcode = (op << 8) | code;
    unsigned char operation = op & 0xF0;
    //std::cout << std::bitset<8>(operation) << std::endl;
    */

    std::ifstream rom("../pong.rom", std::ios::binary|std::ios::ate);
    if(rom){

        std::cout << "file was opened."; 
        auto size = rom.tellg();
        auto memblock = new char [size];
        rom.seekg(0, std::ios::beg);
        rom.read(memblock, size);
        rom.close();
        std::cout << "the entire file content is in memory";
        
        std::cout << "first item: " << ( memblock[0]) << std::endl;
        
        delete[] memblock;
    } else{
        std::cout << "couldn't open file.";
    }

    std::cout << std::endl;






    return 0;
}

