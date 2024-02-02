#include <iostream>

#include "compressor.h"
#include "arguments.h"

int main(int argc, char *argv[])
{
    auto vm = arguments::handleArguments(argc, argv);
    if (!vm)
        return 0;

    std::string inputFilePath = vm.value()["input"].as<std::string>();
    std::string outputFilePath = vm.value()["output"].as<std::string>();
    bool compress = vm.value().count("compress") > 0;
    bool decompress = vm.value().count("decompress") > 0;

    file_compressor::Compressor compressor(inputFilePath, outputFilePath);

    if (compress)
        compressor.compress();
    else if (decompress)
        compressor.decompress();

    return 0;
}
