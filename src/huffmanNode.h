#pragma once

namespace file_compressor
{
class HuffmanNode
{
public:
    HuffmanNode(char character, int frequency, HuffmanNode* left, HuffmanNode* right);
    char getCharacter() const;
    int getFrequency() const;
    HuffmanNode* getLeft() const;
    HuffmanNode* getRight() const;
    bool isLeaf() const;

private:
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
};
} // namespace file_compressor
