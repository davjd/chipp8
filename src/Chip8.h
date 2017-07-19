/*
 * =====================================================================================
 *
 *       Filename:  
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/07/2017 03:37:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Medina, 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <memory>
#include "CPU.h"
class Chip8{
    private:
        std::array<unsigned char, 4096> memory_;
        std::array<unsigned char, 2048> graphics_;
        std::array<unsigned short, 16> stack_;
        std::array<unsigned char, 16> keys_;
        std::array<unsigned char, 16> register_;
        std::array<unsigned char, 80> fontset_;
        unsigned short opcode_;
        unsigned short index_;
        unsigned short pCtr_;
        unsigned char delayTimer_;
        unsigned char soundTimer_;
        unsigned short stackPtr_;
    public:
        Chip8();
        void execute(const unsigned short& opFirst, const unsigned short& opSecond);
        void init();
        void load(const std::string& path);
        void cycle();
        void undefineOpcode() noexcept;
};

#endif
