#include "zip.hpp"

namespace archive_management_tools::archives::zip
{
  std::string ZipArchive::FileStat()
  {
    std::basic_stringstream<char> output;
    output << "[ARCHIVE] ZIP: entries = " <<
     this->m_end_central_directory->m_number_of_entries << "\n";

    if (this->m_end_central_directory->m_number_of_entries > 0) {
      for (auto local_file_feader : this->m_local_file_header_list) {
        output << "\t" << local_file_feader->get_file_name() << " (" <<
        local_file_feader->m_compressed_size << "/" <<
        local_file_feader->m_uncompressed_size << ") bytes\n";
      }
    }

    return output.str();
  }

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

  std::list<std::string> ZipArchive::GetFileList()
  {
    std::list<std::string> result;
    for (auto local_file_feader : this->m_local_file_header_list)
    {
      result.push_back(local_file_feader->get_file_name());
    }

    return result;
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
