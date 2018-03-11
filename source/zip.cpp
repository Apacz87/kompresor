#include "zip.hpp"

namespace archive_management_tools::archives::zip
{
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
    this->m_end_central_directory = (components::EndOfCentralDirectory*) this->GetEndOfCentralDirectoryOffset();
    std::cout << "Data offset: " << this->m_data_pointer << '\n';
    std::cout << "Offset: " << this->m_end_central_directory->m_start_offset << '\n';
    char* pointer = reinterpret_cast<char*>(this->m_data_pointer);
    pointer += this->m_end_central_directory->m_start_offset;
    this->m_central_directory = (components::CentralDirectory*) pointer;
  }

  void ZipArchive::Print()
  {
    this->m_end_central_directory->print_data();
    this->m_central_directory->print_data();
  }
}
