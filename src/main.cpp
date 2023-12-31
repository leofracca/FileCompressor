#include <iostream>

#include "compressor.h"

int main()
{
    std::string inputFilePath = "input.txt";
    file_compressor::Compressor compressor(inputFilePath);

    compressor.compress();

    return 0;
}
