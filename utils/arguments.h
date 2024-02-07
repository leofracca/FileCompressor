#pragma once

#include <boost/program_options.hpp>
#include <optional>

namespace arguments
{
std::optional<boost::program_options::variables_map> handleArguments(int argc, char* argv[]);
int conflicting_options(const boost::program_options::variables_map& vm, const std::string& opt1, const std::string& opt2);
} // namespace arguments