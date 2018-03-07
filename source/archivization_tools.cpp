#include "archivization_tools.hpp"

namespace archive_management_tools
{
  bool IsArchive(int t_file_descriptor)
  {
    struct stat file_stat;
    if (fstat(t_file_descriptor, &file_stat))
    {
      throw std::runtime_error("Reading file stat failed!");
    }

    if (S_ISREG (file_stat.st_mode))
    {
      // TODO: Check file size:
      // min 22 bytes, max  4,294,967,295 bytes (4 GiB minus 1 byte) for standard ZIP, and 18,446,744,073,709,551,615 bytes (16 EiB minus 1 byte) for ZIP64
      if (file_stat.st_size < 22)
      {
        return false;
      }

      int first_four_bytes;
      read(t_file_descriptor, &first_four_bytes, 4);
      return first_four_bytes == 0x04034b50;
    }

    return false;
  }

  ArchiveType GetArchiveType(const std::string& t_file_path)
  {

  }

  void* SearchForCentralDirectory(void* t_pointer, size_t t_data_size)
  {
    char* ptr = (char*)t_pointer;
    for (size_t i = 0; i < t_data_size; i++)
    {
      int* value = (int*) ptr;
      if (*value == 0x02014b50)
      {
        return value;
      }

      ptr++;
    }

    return nullptr;
  }

  void* SearchForEndOfCentralDirectory(void* t_pointer, size_t t_data_size)
  {
    char* ptr = (char*)t_pointer;
    for (size_t i = 0; i < t_data_size; i++)
    {
      int* value = (int*) ptr;
      if (*value == 0x06054b50)
      {
        return value;
      }

      ptr++;
    }

    return nullptr;
  }

  void MapZipIntoMemory(int fd)
  {
    struct stat file_stat;
    if (fstat(fd, &file_stat))
    {
      throw std::runtime_error("Reading file stat failed!");
    }

    char *p = (char*) mmap(0, file_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
      throw std::runtime_error("mmap file failed!");
    }

    zip::LocalFileHeader* first_header = (zip::LocalFileHeader*)p;
    first_header->print();

    /*for ( auto len = 0; len < file_stat.st_size; len++)
    {
      putchar(p[len]);
    }*/
    zip::CentralDirectory* central_directory = (zip::CentralDirectory*) SearchForCentralDirectory(p, file_stat.st_size);

    central_directory->print_data();
    std::cout << '\n';

    zip::EndOfCentralDirectory* end_central_directory = (zip::EndOfCentralDirectory*) SearchForEndOfCentralDirectory(p, file_stat.st_size);
    end_central_directory->print_data();

    if (munmap(p, file_stat.st_size) == -1)
    {
      throw std::runtime_error("munmap file failed!");
    }
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

    std::cout << "--------------------------------------------------------------" << '\n';
    std::cout << "FILE: " << t_file_path << '\n';
    std::cout << "SIZE: " << sb.st_size << " bytes, TYPE: ";
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

    if (IsArchive(fd))
    {
      MapZipIntoMemory(fd);
    }

    if (close(fd) == -1)
    {
      throw std::runtime_error("close failed!");
    }

  }

  Archive ArchiveFactory::Create(const std::string& t_archive_path)
  {
    /*for(auto filePath : t_paths)
    {
      FileInfo(filePath);
    }*/
    return Archive();
  }

  Archive ArchiveFactory::Read(const std::string& t_archive_path)
  {

  }
} // namespace archive_management_tools
