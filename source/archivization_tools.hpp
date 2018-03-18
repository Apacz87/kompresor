#ifndef ARCHIVE_MANAGEMENT_TOOLS_HPP
#define ARCHIVE_MANAGEMENT_TOOLS_HPP

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "archive.hpp"
#include "zip.hpp"

namespace archive_management_tools
{
  using archive_management_tools::archives::Archive;
  using archive_management_tools::archives::ArchiveType;
  using archive_management_tools::archives::CompressionAlgorithm;
  using archive_management_tools::archives::zip::components::LocalFileHeader;
  using archive_management_tools::archives::zip::components::ExtendedLocalHeader;
  using archive_management_tools::archives::zip::components::CentralDirectory;
  using archive_management_tools::archives::zip::components::EndOfCentralDirectory;
  using archive_management_tools::archives::zip::ZipArchive;

  ArchiveType GetArchiveType(const std::string& t_file_path);

  bool IsArchive(int);
  bool IsArchive(std::string);

  void* SearchForCentralDirectory(void*, size_t);

  void* SearchForEndOfCentralDirectory(void*, size_t);

  void MapZipIntoMemory(int);

  void FileInfo(const std::string&);

  archive_management_tools::archives::zip::ZipArchive ReadZip(const std::string& t_path);

  class ZipFileParser
  {
  public:
    static EndOfCentralDirectory* GetEndOfCentralDirectory(void* const t_data_pointer, const size_t& t_data_size);
  };

  class ArchiveFactory
  {
    ArchiveType m_archive_type;
    archive_management_tools::archives::CompressionAlgorithm m_compression_algorithm;
    /*
    void CreateArchive(const std::string& path)
    {
    }

    template<typename ...T>
    void CreateArchive(const std::string& path, const T& paths...)
    {
      CreateArchive(path);
      CreateArchive(paths);
    }
    */
    public:
    ArchiveFactory() : m_archive_type(ArchiveType::ZIP), m_compression_algorithm(CompressionAlgorithm::DEFLATE)
    {
    }

    ArchiveFactory(ArchiveType t_type = ArchiveType::ZIP, CompressionAlgorithm t_algorithm = CompressionAlgorithm::DEFLATE)
      : m_archive_type(t_type), m_compression_algorithm(t_algorithm)
    {
    }

    //Archive Create(const std::string&);
    //Archive Read(const std::string&);
  };
} // namespace archive_management_tools

#endif
