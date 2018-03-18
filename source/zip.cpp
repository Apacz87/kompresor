#include "zip.hpp"

namespace archive_management_tools::archives::zip
{
  void ZipArchive::PrintFileStat()
  {
    std::cout << "Still to do!\n";
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
