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

  std::list<CentralDirectory*> ZipFileParser::GetCentralDirectoryList(void* const t_data_pointer, const EndOfCentralDirectory* t_eocd_pointer)
  {
    CentralDirectory* c_dir = (CentralDirectory*)(t_data_pointer + t_eocd_pointer->m_start_offset);
    std::list<CentralDirectory*> cdir_list;
    for (int entries = 1; entries <= t_eocd_pointer->m_number_of_entries_on_this_disk; entries++)
    {
      cdir_list.push_back(c_dir);
      c_dir = (CentralDirectory*)(((char*)c_dir)+c_dir->get_struct_full_size());
    }

    return cdir_list;
  }

  std::list<LocalFileHeader*> ZipFileParser::GetLocalFileHeaderList(void* const t_data_pointer, const std::list<CentralDirectory*>& t_cdir_list)
  {
    std::list<LocalFileHeader*> lfh_list;
    for (auto central_directory : t_cdir_list)
    {
      lfh_list.push_back((LocalFileHeader*)(t_data_pointer + central_directory->m_relative_offset_of_local_header));
    }

    return lfh_list;
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

  std::string FileInfo(const std::string& t_file_path)
  {
    struct stat sb;
    std::basic_stringstream<char> output;

    if (stat(t_file_path.c_str(), &sb))
    {
      throw std::runtime_error("stat error!");
    }

    switch (sb.st_mode & S_IFMT)
    {
      case S_IFBLK:
        output << "[BLOCK DEVICE]";
        break;
      case S_IFCHR:
        output << "[CHARACTER DEVICE]";
        break;
      case S_IFDIR:
        output << "[DIRECTORY]";
        break;
      case S_IFIFO:
        output << "[FIFO/PIPE]";
        break;
      case S_IFLNK:
        output << "[SYMLINK]";
        break;
      case S_IFREG:
        output << "[REGULAR FILE]";
        break;
      case S_IFSOCK:
        output << "[SOCKET]";
        break;
      default:
        output << "[UNKNOWN]";
        break;
    }

    output << " \"" << t_file_path << "\" " << sb.st_size << " bytes\n";
    return output.str();
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

    auto eocd = ZipFileParser::GetEndOfCentralDirectory(p, file_stat.st_size);
    auto cdl =  ZipFileParser::GetCentralDirectoryList(p, eocd);
    auto lfhl = ZipFileParser::GetLocalFileHeaderList(p, cdl);

    std::shared_ptr<ZipArchive> archive = ZipArchive::Build().SetFilePointer(p)
      .SetFileSize(file_stat.st_size)
      .SetEndOfCentralDirectory(eocd)
      .AddCentralDirectoryList(cdl)
      .AddLocalHeaderList(lfhl);
      //.AddCentralDirectory((CentralDirectory*)(p + eocd->m_start_offset));
    //archive->PrintFileStat();
    /*if (munmap(p, file_stat.st_size) == -1)
    {
      throw std::runtime_error("munmap file failed!");
    }*/

    //auto test_ptr = archive->GetPointer();
    //test_ptr->PrintFileStat();
    //return test_ptr;

    return archive;
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
