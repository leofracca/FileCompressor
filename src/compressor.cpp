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

void Compressor::buildHuffmanTree()
{
    auto compare = [](HuffmanNode* left, HuffmanNode* right) { return left->getFrequency() > right->getFrequency(); };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(compare)> priorityQueue(compare);

    // Build the priority queue
    for (auto& pair : frequencyTable)
    {
        priorityQueue.push(std::make_unique<HuffmanNode>(pair.first, pair.second, nullptr, nullptr).get());
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

} // namespace file_compressor