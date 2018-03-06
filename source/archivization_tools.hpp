#ifndef ARCHIVER_HPP
#define ARCHIVER_HPP

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "zip.hpp"

// Archive management tools.
namespace amt
{

  bool IsArchive(int);

  void* SearchForCentralDirectory(void*, size_t);

  void* SearchForEndOfCentralDirectory(void*, size_t);

  void MapZipIntoMemory(int);

  void FileInfo(const std::string&);

  class Archive
  {
    int m_fileDescriptor;
    // TODO: Add archive file class content.
  };

  class ArchiveFactory
  {
    ArchiveType m_archive_type;
    CompressionAlgorithm m_compression_algorithm;
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

    Archive Create(const std::string);
    Archive Read(const std::string);
  };
}

#endif
