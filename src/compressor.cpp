#include "compressor.h"

#include <fstream>

namespace file_compressor
{
Compressor::Compressor(const std::string& inputFilePath)
    : inputFilePath(inputFilePath)
{
    buildFrequencyTable();
    printFrequencyTable();
}

void Compressor::buildFrequencyTable()
{
    std::ifstream file(inputFilePath);

    for (char c; file >> c;)
    {
        frequencyTable[c]++;
    }
}

void Compressor::printFrequencyTable()
{
    for (auto& pair : frequencyTable)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

} // namespace file_compressor