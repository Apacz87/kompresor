#include "zip.hpp"
namespace archive_management_tools::archives::zip
{
  void* GetEndOfCentralDirectoryOffset(void* t_pointer, size_t t_data_size)
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

  void ZipArchive::Pack(std::string  t_input)
  {
    throw std::runtime_error("The function has not yet been implemented");
  }
  void ZipArchive::Unpack(std::string  t_input)
  {
    throw std::runtime_error("The function has not yet been implemented");
  }
  void ZipArchive::Save(std::string t_input)
  {
    throw std::runtime_error("The function has not yet been implemented");
  }
  ZipArchive::ZipArchive(void* t_data_pointer, size_t t_data_block_size) : m_data_pointer(t_data_pointer), m_data_size(t_data_block_size)
  {
    zip::EndOfCentralDirectory* end_central_directory = (zip::EndOfCentralDirectory*) SearchForEndOfCentralDirectory(p, file_stat.st_size);
    end_central_directory->print_data();
  }
}
