#ifndef ZIP_HPP
#define ZIP_HPP

#include <stdexcept>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <list>
#include <string>

#include "archive.hpp"
#include "zip_components.hpp"

namespace archive_management_tools::archives::zip
{
  class ZipBuilder;
  using archive_management_tools::archives::Archive;
  using archive_management_tools::archives::zip::components::LocalFileHeader;
  using archive_management_tools::archives::zip::components::ExtendedLocalHeader;
  using archive_management_tools::archives::zip::components::CentralDirectory;
  using archive_management_tools::archives::zip::components::EndOfCentralDirectory;

  class ZipArchive : public Archive
  {
  private:
    void* m_data_pointer = nullptr;
    size_t m_data_size = 0;
    std::list<components::LocalFileHeader*> m_local_file_feader_list;
    // TODO: Add ExtendedLocalHeader
    std::list<components::CentralDirectory*> m_central_directory_list;
    components::EndOfCentralDirectory* m_end_central_directory;
    ZipArchive() = default;

  public:
    friend class ZipBuilder;
    static ZipBuilder Build();
    void PrintFileStat();
    void Pack(std::string);
    void Unpack(std::string);
    void Save(std::string);
    void Print();
  };

  class ZipBuilder
  {
  private:
    ZipArchive m_zip;
  public:
    ZipBuilder() = default;
    ZipBuilder& SetFilePointer(void* t_file_pointer)
    {
      this->m_zip.m_data_pointer = t_file_pointer;
      return *this;
    }

    ZipBuilder& SetFileSize(size_t t_file_size)
    {
      this->m_zip.m_data_size = t_file_size;
      return *this;
    }

    ZipBuilder& SetEndOfCentralDirectory(components::EndOfCentralDirectory* t_eocd)
    {
      this->m_zip.m_end_central_directory = t_eocd;
      return *this;
    }

    ZipBuilder& AddCentralDirectory(components::CentralDirectory* t_cd)
    {
      this->m_zip.m_central_directory_list.push_back(t_cd);
      return *this;
    }

    ZipBuilder& AddLocalHeader(components::LocalFileHeader* t_lfh)
    {
      this->m_zip.m_local_file_feader_list.push_back(t_lfh);
      return *this;
    }
    //ZipBuilder& AddExtendedLocalHeader();
    operator ZipArchive&&()
    {
      return std::move(this->m_zip);
    }
  };
} // namespace archive_management_tools::archives::zip
#endif
