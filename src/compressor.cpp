#include "compressor.h"

#include <fstream>
#include <queue>
#include <bitset>

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
    std::string header;
    for (auto& pair : encodingTable)
    {
        header += "(" + std::string(1, pair.first) + pair.second + ")";
    }
    outputFile << header.size() << '\n' << header;

    // Read the input file to build the encoding
    std::string encoding;
    char c;
    while (file.get(c))
    {
        encoding += encodingTable[c];
    }

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

void Compressor::decompress()
{
    std::ifstream file("output.txt", std::ios::binary);
    std::ofstream outputFile("decompressed.txt");

    // Read the header
    // TODO: Move the header reading to a separate function
    // TODO: Try to not insert parentheses in the encoding table string
    int headerSize;
    file >> headerSize;

    std::string encodingTableString;
    char c;
    for (int i = 0; i < headerSize; i++)
    {
        file.get(c);
        if (c == '(')
        {
            encodingTableString += c;
            while (file.get(c))
            {
                i++;
                encodingTableString += c;
                if (c == ')')
                {
                    break;
                }
            }
        }
        encodingTableString += c;
    }

    // Build the encoding table from the encoding table string
    std::unordered_map<std::string, char> decodingTable;
    char character;
    std::string encoding;
    for (int i = 0; i < encodingTableString.size(); i++)
    {
        if (encodingTableString[i] == '(')
        {
            character = encodingTableString[i + 1];
            encoding = "";
            i++;
        }
        else if (encodingTableString[i] == ')')
        {
            decodingTable[encoding] = character;
        }
        else
        {
            encoding += encodingTableString[i];
        }
    }

    // Read the encoded file from the output file
    std::string encodedFile;
    while (file.get(c))
    {
        encodedFile += std::bitset<8>(c).to_string();
    }

    // Decode the encoded file
    std::string decodedFile;
    std::string currentEncoding;
    for (char ch : encodedFile)
    {
        currentEncoding += ch;
        if (decodingTable.find(currentEncoding) != decodingTable.end())
        {
            decodedFile += decodingTable[currentEncoding];
            currentEncoding = "";
        }
    }

    // Write the decoded file to the output file
    outputFile << decodedFile;

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
