/*
 * =====================================================================================
 *
 *       Filename:  Chip8.h
 *
 *    Description: The CPU will be responsible for executing
 *                  opcodes given from the main emulator. 
 *
 *        Version:  1.0
 *        Created:  07/11/2017 06:00:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Medina, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <array>

class CPU{
    private:
        std::array<unsigned short, 16> register_;
        unsigned short opcode_;

    public:
        CPU();
        void init();
};
