#include "arguments.h"

#include <boost/program_options.hpp>
#include <optional>
#include <iostream>

namespace arguments
{
std::optional<boost::program_options::variables_map> handleArguments(int argc, char *argv[])
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce this help message")
        ("input,i", po::value<std::string>(), "path to input file")
        ("output,o", po::value<std::string>(), "path to output file (default: input file name with .compressed extension)")
        ("compress,c", "compress the input file")
        ("decompress,d", "decompress the input file")
    ;

    po::positional_options_description p;
    p.add("input", 1);
    p.add("output", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
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
        vm.insert({"output", po::variable_value(std::string(vm["input"].as<std::string>() + ".compressed"), false)});
    }

    if (vm.count("compress") == 0 && vm.count("decompress") == 0)
    {
        std::cout << "Neither compress nor decompress was set.\n";
        return std::nullopt;
    }

    return vm;
}
} // namespace arguments