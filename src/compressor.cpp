#include "compressor.h"

#include <fstream>
#include <queue>
#include <bitset>

namespace file_compressor
{
Compressor::Compressor(const std::string& inputFilePath, const std::string& outputFilePath)
    : inputFilePath(inputFilePath)
    , outputFilePath(outputFilePath)
{
    buildFrequencyTable();
    buildHuffmanTree();
    buildEncodingTable();
}

void Compressor::compress()
{
    std::ifstream file(inputFilePath);
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    writeEncodingTableToFile(outputFile);
    const std::string encoding = buildEncodingString(file);
    writeEncodingStringToFile(outputFile, encoding);

    file.close();
    outputFile.close();
}

void Compressor::decompress()
{
    std::ifstream file(inputFilePath, std::ios::binary);
    std::ofstream outputFile(outputFilePath);

    const std::string encodingTableString = readEncodingTableStringFromFile(file);
    const auto decodingTable = buildEncodingTableFromString(encodingTableString);
    const std::string encoded = readEncodedFile(file);
    const std::string decoded = decodeFile(encoded, decodingTable);
    writeDecodedToFile(outputFile, decoded);

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

    // printFrequencyTable();

    file.close();
}

void Compressor::printFrequencyTable()
{
    for (const auto& pair : frequencyTable)
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

void Compressor::buildEncodingTableHelper(HuffmanNode* node, const std::string& encoding)
{
    if (node->isLeaf())
    {
        encodingTable[node->getCharacter()] = encoding;
        return;
    }

    buildEncodingTableHelper(node->getLeft(), encoding + "0");
    buildEncodingTableHelper(node->getRight(), encoding + "1");
}

void Compressor::writeEncodingTableToFile(std::ofstream& outputFile)
{
    std::string header;
    for (const auto &[k, v]: encodingTable)
    {
        header += "(" + std::string(1, k) + v + ")";
    }
    outputFile << header.size() << '\n' << header;
}

std::string Compressor::buildEncodingString(std::ifstream &inputFile)
{
    std::string encoding;
    char c;
    while (inputFile.get(c))
    {
        encoding += encodingTable[c];
    }

    // Pad the encoding with 0s until it is a multiple of 8
    while (encoding.size() % 8 != 0)
    {
        encoding += "0";
    }

    return encoding;
}

void Compressor::writeEncodingStringToFile(std::ofstream& outputFile, const std::string& encoding)
{
    for (int i = 0; i < encoding.size(); i += 8)
    {
        std::string byte = encoding.substr(i, 8);
        outputFile << static_cast<char>(std::stoi(byte, nullptr, 2));
    }
}

std::string Compressor::readEncodingTableStringFromFile(std::ifstream& inputFile)
{
    int headerSize;
    inputFile >> headerSize;

    std::string encodingTableString;
    char c;
    for (int i = 0; i < headerSize; i++)
    {
        inputFile.get(c);
        if (c == '(')
        {
            encodingTableString += c;
            while (inputFile.get(c))
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

    return encodingTableString;
}

std::unordered_map<std::string, char> Compressor::buildEncodingTableFromString(const std::string& encodingTableString)
{
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

    return decodingTable;
}

std::string Compressor::readEncodedFile(std::ifstream &inputFile)
{
    std::string encodedFile;
    char c;
    while (inputFile.get(c))
    {
        encodedFile += std::bitset<8>(c).to_string();
    }

    return encodedFile;
}

std::string Compressor::decodeFile(const std::string &encoded, const std::unordered_map<std::string, char> &decodingTable)
{
    std::string decoded;
    std::string currentEncoding;
    for (char c : encoded)
    {
        currentEncoding += c;
        if (decodingTable.contains(currentEncoding))
        {
            decoded += decodingTable.at(currentEncoding);
            currentEncoding = "";
        }
    }

    return decoded;
}

void Compressor::writeDecodedToFile(std::ofstream &outputFile, const std::string &decoded)
{
    outputFile << decoded;
}
} // namespace file_compressor
