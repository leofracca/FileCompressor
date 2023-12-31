#include "compressor.h"

#include <fstream>
#include <queue>
#include <memory>

namespace file_compressor
{
Compressor::Compressor(const std::string& inputFilePath)
    : inputFilePath(inputFilePath)
{
    buildFrequencyTable();
    // printFrequencyTable();
    buildHuffmanTree();
    buildEncodingTable();
}

void Compressor::compress()
{
    std::ifstream file(inputFilePath);
    std::ofstream outputFile("output.txt", std::ios::binary);

    // Write the encoding table to the output file
    for (auto& pair : encodingTable)
    {
        outputFile << pair.first << pair.second;
    }

    // Read the input file to count the number of characters and build the encoding
    int numberOfCharacters = 0;
    std::string encoding;
    char c;
    while (file.get(c))
    {
        numberOfCharacters++;
        encoding += encodingTable[c];
    }
    // Write the number of characters to the output file
    outputFile << numberOfCharacters;

    // Pad the encoding with 0s until it is a multiple of 8
    while (encoding.size() % 8 != 0)
    {
        encoding += "0";
    }

    // Write the encoded file to the output file as bytes
    for (int i = 0; i < encoding.size(); i += 8)
    {
        std::string byte = encoding.substr(i, 8);
        outputFile << static_cast<char>(std::stoi(byte, nullptr, 2));
    }

    // Close the files
    file.close();
    outputFile.close();
}

void Compressor::buildFrequencyTable()
{
    std::ifstream file(inputFilePath);

    char c;
    while (file.get(c))
    {
        frequencyTable[c]++;
    }

    /*
    for (auto& pair : frequencyTable)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    */
    file.close();
}

void Compressor::printFrequencyTable()
{
    for (auto& pair : frequencyTable)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void Compressor::buildHuffmanTree()
{
    auto compare = [](HuffmanNode* left, HuffmanNode* right) { return left->getFrequency() > right->getFrequency(); };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(compare)> priorityQueue(compare);

    // Build the priority queue
    for (auto& pair : frequencyTable)
    {
        //priorityQueue.push(std::make_unique<HuffmanNode>(pair.first, pair.second, nullptr, nullptr).get());
        priorityQueue.push(new HuffmanNode(pair.first, pair.second, nullptr, nullptr));
    }

    /*
    std::cout << "Huffman Tree:" << std::endl;
    // Print elements in priority queue
    while (!priorityQueue.empty())
    {
        auto node = priorityQueue.top();
        priorityQueue.pop();
        std::cout << node->getCharacter() << ": " << node->getFrequency() << std::endl;
    }
    */

    // Build the Huffman tree
    while (priorityQueue.size() > 1)
    {
        auto left = priorityQueue.top();
        priorityQueue.pop();
        auto right = priorityQueue.top();
        priorityQueue.pop();

        auto parent = new HuffmanNode('\0', left->getFrequency() + right->getFrequency(), left, right);
        priorityQueue.push(parent);
    }

    huffmanTreeRoot = priorityQueue.top();
}

void Compressor::buildEncodingTable()
{
    buildEncodingTableHelper(huffmanTreeRoot, "");
}

void Compressor::buildEncodingTableHelper(HuffmanNode* node, std::string encoding)
{
    // Visit the tree
    // If left, add 0 to encoding
    // If right, add 1 to encoding
    // If leaf, add character and encoding to encoding table
    if (node->isLeaf())
    {
        //std::cout << node->getCharacter() << ": " << encoding << std::endl;
        encodingTable[node->getCharacter()] = encoding;
        return;
    }

    buildEncodingTableHelper(node->getLeft(), encoding + "0");
    buildEncodingTableHelper(node->getRight(), encoding + "1");
}
} // namespace file_compressor
