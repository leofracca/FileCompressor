#include <iostream>

#include "compressor.h"

int main()
{
    std::string inputFilePath = "input.txt";
    file_compressor::Compressor compressor(inputFilePath);

    compressor.compress();
    compressor.decompress();

    return 0;
}
