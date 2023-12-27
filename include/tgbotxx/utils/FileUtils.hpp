#pragma once
#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <tgbotxx/Exception.hpp>
#include <vector>
namespace fs = std::filesystem;

namespace tgbotxx {
  /// @brief Namespace contains useful File related utility functions.
  namespace FileUtils {
    /// @brief Read entire file into an std::string
    /// @throws Exception on failure
    static std::string read(const fs::path& filename) {
      if (std::ifstream ifs{filename, std::ios::ate | std::ios::binary}) {
        std::string buffer(ifs.tellg(), '\000');
        ifs.seekg(0, std::ios::beg);
        ifs.read(buffer.data(), buffer.size());
        ifs.close();
        return buffer;
      } else {
        throw Exception("No such file " + filename.string());
      }
    }

    /// @brief Read entire file lines into std::vector<std::string>
    /// @throws Exception on failure
    static std::vector<std::string> readLines(const fs::path& filename) {
      if (std::ifstream ifs{filename, std::ios::binary}) {
        std::vector<std::string> lines{};
        std::string line{};
        while (std::getline(ifs, line)) {
          lines.push_back(line);
        }
        ifs.close();
        return lines;
      } else {
        throw Exception("No such file " + filename.string());
      }
    }

    /// @brief Read file chunk by chunk
    /// @throws Exception on failure
    static void readChunks(const fs::path& filename, const std::size_t maxChunkSize, const std::function<void(std::vector<std::uint8_t>&&)>& callback) {
      if (std::ifstream ifs{filename, std::ios::binary}) {
        while (!ifs.eof()) {
          std::vector<std::uint8_t> chunk(maxChunkSize, '\000');
          ifs.read(reinterpret_cast<char *>(chunk.data()), chunk.size());

          // resize chunk if we read bytes less than max_chunk_size
          const auto bytes_read = ifs.gcount();
          if (bytes_read < maxChunkSize)
            chunk.resize(bytes_read);

          // serve chunk
          callback(std::move(chunk));
        }
        ifs.close();
      } else {
        throw Exception("No such file " + filename.string());
      }
    }

    /// @brief Write buffer string to a new file
    /// @throws Exception on failure
    static void write(const fs::path& filename, const std::string& buffer) {
      if (std::ofstream ofs{filename, std::ios::binary}) {
        ofs.write(buffer.data(), buffer.size());
        ofs.close();
      } else {
        throw Exception("Failed to write file " + filename.string());
      }
    }

  }
}