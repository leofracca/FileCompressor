#include <iostream>

#include "compressor.h"

int main()
{
    using namespace file_compressor;
    std::string inputFilePath = "input.txt";
    Compressor compressor(inputFilePath);

    return 0;
}
