#include "huffmanNode.h"

namespace file_compressor
{
HuffmanNode::HuffmanNode(char character, int frequency, HuffmanNode* left, HuffmanNode* right)
    : character(character), frequency(frequency), left(left), right(right)
{}

char HuffmanNode::getCharacter() const
{
    return character;
}

int HuffmanNode::getFrequency() const
{
    return frequency;
}

HuffmanNode* HuffmanNode::getLeft() const
{
    return left;
}

HuffmanNode* HuffmanNode::getRight() const
{
    return right;
}

bool HuffmanNode::isLeaf() const
{
    return left == nullptr && right == nullptr;
}
} // namespace file_compressor
