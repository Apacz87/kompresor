#include "zip.hpp"

namespace archive_management_tools::archives::zip
{
  class ZipBuilder;
  void* ZipArchive::GetEndOfCentralDirectoryOffset()
  {
    unsigned int signature = 0x06054b50;
    char* ptr = (char*)this->m_data_pointer;
    for (size_t i = this->m_data_size - 176; i >=0; --i)
    {
      int* value = (int*) ptr;
      if (*value == signature)
      {
        return value;
      }

      ptr++;
    }

    return nullptr;
  }

  void ZipArchive::Pack(std::string  t_input)
  {
    t_input.clear(); // Temporary operation, to remove warnings for compilation log ;)
    throw std::runtime_error("The function 'ZipArchive::Pack' has not yet been implemented");
  }

  void ZipArchive::Unpack(std::string  t_input)
  {
    t_input.clear(); // Temporary operation, to remove warnings for compilation log ;)
    throw std::runtime_error("The function 'ZipArchive::Unpack' has not yet been implemented");
  }

  void ZipArchive::Save(std::string t_input)
  {
    t_input.clear(); // Temporary operation, to remove warnings for compilation log ;)
    throw std::runtime_error("The function 'ZipArchive::Save' has not yet been implemented");
  }

  void ZipArchive::Print()
  {
    this->m_end_central_directory->print_data();
    this->m_central_directory_list.front()->print_data();
  }

  ZipBuilder ZipArchive::Build()
  {
    return ZipBuilder();
  }
}
