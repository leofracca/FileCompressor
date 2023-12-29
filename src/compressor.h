#pragma once
#include <iostream>
#include <unordered_map>

namespace file_compressor
{
class Compressor
{
public:
    explicit Compressor(const std::string& inputFilePath);

private:
    void buildFrequencyTable();
    void printFrequencyTable();

private:
    std::string inputFilePath;
    std::unordered_map<char, int> frequencyTable;
};

} // namespace file_compressor
