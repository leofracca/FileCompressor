#pragma once
#include <iostream>
#include <unordered_map>

#include "huffmanNode.h"

namespace file_compressor
{
class Compressor
{
public:
    explicit Compressor(const std::string& inputFilePath, const std::string& outputFilePath);
    void compress();
    void decompress();

private:
    void buildFrequencyTable();
    void printFrequencyTable();
    void buildHuffmanTree();
    void buildEncodingTable();
    void buildEncodingTableHelper(HuffmanNode* node, std::string encoding);
    void writeEncodingTableToFile(std::ofstream& outputFile);
    std::string buildEncodingString(std::ifstream &inputFile);
    static void writeEncodingStringToFile(std::ofstream& outputFile, const std::string& encoding);
    static std::string readEncodingTableStringFromFile(std::ifstream& inputFile);

    // TODO: Try std::unordered_map<char, std::string> instead. Then save the result in encodingTable.
    static std::unordered_map<std::string, char> buildEncodingTable(const std::string& encodingTableString);

    static std::string readEncodedFile(std::ifstream& inputFile);
    static std::string decodeFile(const std::string& encoded, const std::unordered_map<std::string, char>& decodingTable);
    static void writeDecodedToFile(std::ofstream& outputFile, const std::string& decoded);

private:
    std::string inputFilePath;
    std::string outputFilePath;
    std::unordered_map<char, int> frequencyTable;
    HuffmanNode* huffmanTreeRoot{};
    std::unordered_map<char, std::string> encodingTable;
};
} // namespace file_compressor
