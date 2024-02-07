#include "arguments.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <optional>

namespace arguments
{
std::optional<boost::program_options::variables_map> handleArguments(int argc, char* argv[])
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
        ("help,h", "produce this help message")
        ("input,i", po::value<std::string>(), "path to input file")
        ("output,o", po::value<std::string>(), "path to output file (default: input file name with .compressed extension)")
        ("compress,c", "compress the input file")
        ("decompress,d", "decompress the input file")
    ;
    // clang-format on

    po::positional_options_description p;
    p.add("input", 1);
    p.add("output", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    if (conflicting_options(vm, "compress", "decompress") == -1)
    {
        std::cout << "Conflicting options 'compress' and 'decompress'.\n";
        return std::nullopt;
    }
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return std::nullopt;
    }

    if (vm.count("input") == 0)
    {
        std::cout << "Input file was not set.\n";
        return std::nullopt;
    }

    if (vm.count("output") == 0)
    {
        std::string inputFilePath = std::string(vm["input"].as<std::string>());

        if (vm.count("compress") > 0)
            inputFilePath += ".compressed";
        else if (vm.count("decompress") > 0)
            inputFilePath = inputFilePath.substr(0, inputFilePath.size() - std::string(".compressed").size());

        vm.insert({"output", po::variable_value(inputFilePath, false)});
    }

    if (vm.count("compress") == 0 && vm.count("decompress") == 0)
    {
        std::cout << "Neither compress nor decompress was set.\n";
        return std::nullopt;
    }

    return vm;
}

int conflicting_options(const boost::program_options::variables_map& vm, const std::string& opt1, const std::string& opt2)
{
    if (vm.count(opt1) && !vm[opt1].defaulted() &&
        vm.count(opt2) && !vm[opt2].defaulted())
        return -1;
    return 0;
}
} // namespace arguments