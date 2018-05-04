#include "archivization_tools.hpp"

namespace archive_management_tools
{

  EndOfCentralDirectory* ZipFileParser::GetEndOfCentralDirectory(void* const t_data_pointer, const size_t& t_data_size)
  {
    const unsigned int signature = 0x06054b50;
    char* file_beginning = reinterpret_cast<char*>(t_data_pointer);
    char* file_end = file_beginning + t_data_size;
    char* pointer = file_end - sizeof(EndOfCentralDirectory);
    while (pointer != file_beginning)
    {
      unsigned int* value = reinterpret_cast<unsigned int*>(pointer);
      if (*value == signature)
      {
        return (EndOfCentralDirectory*)value;
      }

      pointer--;
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

  bool IsArchive(std::string t_path)
  {
    int file_descriptor = open(t_path.c_str(), O_RDONLY);
    if (file_descriptor == -1)
    {
      throw std::runtime_error(std::strerror(errno));
    }

    auto is_archive = IsArchive(file_descriptor);
    if (close(file_descriptor) == -1)
    {
      throw std::runtime_error(std::strerror(errno));
    }

    return is_archive;
  }

  ArchiveType GetArchiveType(const std::string& t_file_path)
  {
    t_file_path.c_str(); // Temporary operation, to remove warnings for compilation log ;)
    return ArchiveType::UNKNOWN;
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

  std::shared_ptr<Archive> ArchiveFactory::Read(const int& t_file_descriptor)
  {
    struct stat file_stat;
    if (fstat(t_file_descriptor, &file_stat))
    {
      throw std::runtime_error("Reading file stat failed!");
    }

    char *p = (char*) mmap(0, file_stat.st_size, PROT_READ, MAP_SHARED, t_file_descriptor, 0);
    if (p == MAP_FAILED)
    {
      throw std::runtime_error("mmap file failed!");
    }

    ZipArchive archive = ZipArchive::Build().SetEndOfCentralDirectory(ZipFileParser::GetEndOfCentralDirectory(p, file_stat.st_size));
    if (munmap(p, file_stat.st_size) == -1)
    {
      throw std::runtime_error("munmap file failed!");
    }

    return archive.GetPointer();
  }

  std::shared_ptr<Archive> ArchiveFactory::Read(const std::string& t_archive_path)
  {
    int file_descriptor = open(t_archive_path.c_str(), O_RDONLY);
    if (file_descriptor == -1)
    {
      throw std::runtime_error(std::strerror(errno));
    }

    auto archive = ArchiveFactory::Read(file_descriptor);
    if (close(file_descriptor) == -1)
    {
      throw std::runtime_error(std::strerror(errno));
    }

    return archive;
  }

  /*Archive ArchiveFactory::Create(const std::string& t_archive_path)
  {
    return Archive();
  }*/
} // namespace archive_management_tools
