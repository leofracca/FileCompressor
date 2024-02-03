/**
 * @file huffmanNode.h
 * @brief Header file for the HuffmanNode class
 */

#pragma once

namespace file_compressor
{
/**
 * @brief A node in the Huffman tree
 */
class HuffmanNode
{
public:
    /**
     * @brief Create a new node
     * @param character The character
     * @param frequency The frequency of the character
     * @param left The left child
     * @param right The right child
     */
    HuffmanNode(char character, int frequency, HuffmanNode* left, HuffmanNode* right);

    /**
     * @brief Get the character of the node
     * @return The character
     */
    char getCharacter() const;

    /**
     * @brief Get the frequency of the character of the node
     * @return The frequency
     */
    int getFrequency() const;

    /**
     * @brief Get the left child of the node
     * @return The left child
     */
    HuffmanNode* getLeft() const;

    /**
     * @brief Get the right child of the node
     * @return The right child
     */
    HuffmanNode* getRight() const;

    /**
     * @brief Check if the node is a leaf
     * @return True if the node is a leaf, false otherwise
     */
    bool isLeaf() const;

private:
    char character; ///< The character
    int frequency; ///< The frequency of the character
    HuffmanNode* left; ///< The left child
    HuffmanNode* right; ///< The right child
};
} // namespace file_compressor
