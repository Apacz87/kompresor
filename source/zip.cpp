#include "zip.hpp"

namespace archive_management_tools::archives::zip
{
  void ZipArchive::PrintFileStat()
  {
    this->m_end_central_directory->print_data();
    for (auto central_directory : this->m_central_directory_list)
    {
      central_directory->print_data();
    }

    for (auto local_file_feader : this->m_local_file_header_list)
    {
      local_file_feader->print_data();
    }
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

  ZipBuilder ZipArchive::Build()
  {
    return ZipBuilder();
  }
}
