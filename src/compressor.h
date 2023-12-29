#pragma once
#include <iostream>
#include <unordered_map>

#include "huffmanNode.h"

namespace file_compressor
{
class Compressor
{
public:
    explicit Compressor(const std::string& inputFilePath);

private:
    void buildFrequencyTable();
    void printFrequencyTable();
    void buildHuffmanTree();

private:
    std::string inputFilePath;
    std::unordered_map<char, int> frequencyTable;
    HuffmanNode* huffmanTreeRoot;
};

} // namespace file_compressor
