#include <fstream>

#include "util.hpp"

namespace HB::Util {

std::vector<char> read_file(std::string const& filename)
{
    // FIXME: Replace this function with C++17 filesystem API?
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("failed to open file!");

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);
    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}

}
