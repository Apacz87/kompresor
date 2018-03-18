#include "archivization_tools.hpp"

namespace archive_management_tools
{
  EndOfCentralDirectory* ZipFileParser::GetEndOfCentralDirectory(void* const t_data_pointer, const size_t& t_data_size)
  {
    unsigned int signature = 0x06054b50;
    char* pointer = reinterpret_cast<char*>(t_data_pointer);
    for (size_t i =  t_data_size - 176; i == 0x0; --i)
    {
      unsigned int* value = reinterpret_cast<unsigned int*>(pointer);
      if (*value == signature)
      {
        return (EndOfCentralDirectory*)value;
      }

      pointer++;
    }

    return nullptr;
  }
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

  archive_management_tools::archives::zip::ZipArchive ReadZip(const std::string& t_path)
  {
    int fd = open(t_path.c_str(), O_RDONLY);
    if (fd == -1)
    {
      throw std::runtime_error("open file failed!");
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat))
    {
      throw std::runtime_error("Reading file stat failed!");
    }

    auto p = mmap(0, file_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    return archive_management_tools::archives::zip::ZipArchive(p, file_stat.st_size);
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

    if (close(fd) == -1)
    {
      throw std::runtime_error("close failed!");
    }

  }

  /*Archive ArchiveFactory::Create(const std::string& t_archive_path)
  {
    return Archive();
  }

  Archive ArchiveFactory::Read(const std::string& t_archive_path)
  {

  }*/
} // namespace archive_management_tools
