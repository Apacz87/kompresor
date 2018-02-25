#ifndef ARCHIVER_HPP
#define ARCHIVER_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <stdio.h>

namespace archiver
{
  enum class ArchiveType {ZIP};
  enum class CompressionAlgorithm {BZIP2, LZMA, DEFLATE, DCL, IMPLODE, WAVPACK};

  bool IsFile(const std::string& t_path)
  {
    struct stat path_stat;
    stat(t_path.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);
  }

  void FileInfo(const std::string& t_file_path)
  {
    struct stat sb;
    int ret, fd;

    ret = stat(t_file_path.c_str(), &sb);
    if (ret)
    {
      //perror("stat");
      throw std::runtime_error("stat error!");
    }

    std::cout << "File: " << t_file_path << '\n';
    std::cout << "Size: " << sb.st_size << " bytes, Type: ";
    switch (sb.st_mode & S_IFMT)
    {
      case S_IFBLK:
        std::cout << "block device\n";// wezel urzadzenia blokowego
        break;
      case S_IFCHR:
        std::cout << "character device\n";// wezel urzadzenia znakowego
        break;
      case S_IFDIR:
        std::cout << "directory\n";
        break;
      case S_IFIFO:
        std::cout << "FIFO/pipe\n";// kolejka FIFO
        break;
      case S_IFLNK:
        std::cout << "symlink\n";// dowiazanie symboliczne
        break;
      case S_IFREG:
        std::cout << "regular file\n";
        break;
      case S_IFSOCK:
        std::cout << "socket\n";// gniazdo
        break;
      default:
        std::cout << "unknown?\n";
        break;
    }

    fd = open(t_file_path.c_str(), O_RDONLY);
    if (fd == -1)
    {
      throw std::runtime_error("open file failed!");
    }

    if (S_ISREG (sb.st_mode))
    {
      char *p = (char*) mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
      if (p == MAP_FAILED)
      {
        throw std::runtime_error("mmap file failed!");
      }

      if (close(fd) == -1)
      {
        throw std::runtime_error("close failed!");
      }

      int zip_signature = 0x04034b50;
      int *first_word = (int*)p;

      if (*first_word == zip_signature)
      {
        std::cout << "This file is a ZIP archive!\n";
      }

      for ( auto len = 0; len < sb.st_size; len++)
      {
        putchar(p[len]);
      }

      if (munmap(p, sb.st_size) == -1)
      {
        throw std::runtime_error("munmap file failed!");
      }

    }
  }

  class ArchiveFile
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

    void Create(const std::vector<std::string>& paths)
    {
      for(auto str : paths)
      {
        FileInfo(str);
      }
    }
  };
}

#endif
