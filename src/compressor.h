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
    void compress();

private:
    void buildFrequencyTable();
    void printFrequencyTable();
    void buildHuffmanTree();
    void buildEncodingTable();
    void buildEncodingTableHelper(HuffmanNode* node, std::string encoding);

private:
    std::string inputFilePath;
    std::unordered_map<char, int> frequencyTable;
    HuffmanNode* huffmanTreeRoot;
    std::unordered_map<char, std::string> encodingTable;
};
} // namespace file_compressor
