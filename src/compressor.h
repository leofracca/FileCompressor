/**
 * @file compressor.h
 * @brief This file contains the declaration of the Compressor class.
 * @details This class is responsible for compressing and decompressing files.
 */

#pragma once
#include <iostream>
#include <unordered_map>

#include "huffmanNode.h"

namespace file_compressor
{
/**
 * @brief The Compressor class
 */
class Compressor
{
public:
    /**
     * @brief Create a new Compressor object
     * @param inputFilePath The path to the input file
     * @param outputFilePath The path to the output file
     * @details If the output file does not exist, it will be created. If it does exist, it will be overwritten.
     * @see buildFrequencyTable, buildHuffmanTree, buildEncodingTable
     */
    explicit Compressor(const std::string& inputFilePath, const std::string& outputFilePath);

    /**
     * @brief Compress the input file
     * @details The frequency table, the encoding table and the encoded file will be written to the output file.
     * @see writeEncodingTableToFile, buildEncodingString, writeEncodingStringToFile
     */
    void compress();

    /**
     * @brief Decompress the input file
     * @details The encoding table will be read from the input file, then the encoded file will be read and decoded.
     *          The decoded file will be written to the output file.
     * @see readEncodingTableStringFromFile, buildEncodingTable, readEncodedFile, decodeFile, writeDecodedToFile
     */
    void decompress();

private:
    /**
     * @brief Build the frequency table
     * @details The frequency of each character in the input file will be counted and saved in the frequency table.
     */
    void buildFrequencyTable();

    /**
     * @brief Print the frequency table
     * @note This function is for debugging purposes only.
     */
    void printFrequencyTable();

    /**
     * @brief Build the Huffman tree
     * @details The Huffman tree will be built based on the frequency table.
     * @see HuffmanNode
     */
    void buildHuffmanTree();

    /**
     * @brief Build the encoding table
     * @details The encoding table will be built based on the Huffman tree.
     * @see buildEncodingTableHelper
     */
    void buildEncodingTable();

    // TODO: check if it is possible to pass the encoding string as a const reference
    /**
     * @brief Helper function for building the encoding table
     * @param node The current node (initially the root of the Huffman tree)
     * @param encoding The encoding of the current node
     * @note This function is called recursively.
     */
    void buildEncodingTableHelper(HuffmanNode* node, std::string encoding);

    /**
     * @brief Write the encoding table to the output file
     * @details The encoding table will be written to the output file in the following format:
     *         - The number of characters in the encoding table
     *         - The character and its encoding for each character in the encoding table
     * @param outputFile The (compressed) output file
     */
    void writeEncodingTableToFile(std::ofstream& outputFile);

    /**
     * @brief Build the encoding string
     * @details The encoding string will be built based on the encoding table.
     * @param inputFile The input file
     * @return The encoding string
     * @see buildEncodingTable
     */
    std::string buildEncodingString(std::ifstream &inputFile);

    /**
     * @brief Write the encoding string to the output file
     * @param outputFile The (compressed) output file
     * @param encoding The encoding string
     * @see buildEncodingString
     */
    static void writeEncodingStringToFile(std::ofstream& outputFile, const std::string& encoding);

    /**
     * @brief Read the encoding table string from the input file
     * @details The input file must be a compressed file
     * @param inputFile The input file
     * @return The encoding table string
     * @see buildEncodingTable
     */
    static std::string readEncodingTableStringFromFile(std::ifstream& inputFile);

    // TODO: Try std::unordered_map<char, std::string> instead. Then save the result in encodingTable.
    /**
     * @brief Build the encoding table
     * @details The encoding table will be built based on the encoding table string.
     * @param encodingTableString The encoding table string
     * @return The encoding table
     * @see readEncodingTableStringFromFile
     */
    static std::unordered_map<std::string, char> buildEncodingTable(const std::string& encodingTableString);

    /**
     * @brief Read the encoded file from the input file
     * @details The input file must be a compressed file
     * @param inputFile The input file
     * @return The encoded file as a string
     */
    static std::string readEncodedFile(std::ifstream& inputFile);

    /**
     * @brief Decode the encoded file
     * @details The encoded file will be decoded based on the encoding table.
     * @param encoded The encoded file content
     * @param decodingTable The decoding table read from the compressed input file
     * @return The decoded file as a string
     */
    static std::string decodeFile(const std::string& encoded, const std::unordered_map<std::string, char>& decodingTable);

    /**
     * @brief Write the decoded file to the output file
     * @param outputFile The output file
     * @param decoded The decoded file content
     */
    static void writeDecodedToFile(std::ofstream& outputFile, const std::string& decoded);

private:
    std::string inputFilePath; ///< The path to the input file
    std::string outputFilePath; ///< The path to the output file
    std::unordered_map<char, int> frequencyTable; ///< The frequency table
    HuffmanNode* huffmanTreeRoot{}; ///< The root of the Huffman tree
    std::unordered_map<char, std::string> encodingTable; ///< The encoding table
};
} // namespace file_compressor
