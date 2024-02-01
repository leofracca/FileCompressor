#pragma once

#include <boost/program_options.hpp>
#include <optional>

namespace arguments
{
std::optional<boost::program_options::variables_map> handleArguments(int argc, char *argv[]);
} // namespace arguments