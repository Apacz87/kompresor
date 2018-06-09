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
    std::list<components::LocalFileHeader*> m_local_file_header_list;
    // TODO: Add ExtendedLocalHeader
    std::list<components::CentralDirectory*> m_central_directory_list;
    components::EndOfCentralDirectory* m_end_central_directory = nullptr;

  public:
    friend class ZipBuilder;
    ZipArchive() = default;
    static ZipBuilder Build();
    void PrintFileStat();
    void Pack(std::string);
    void Unpack(std::string);
    void Save(std::string);
    std::list<std::string> GetFileList();
  };

  class ZipBuilder
  {
  private:
    std::shared_ptr<ZipArchive> m_zip;
  public:
    ZipBuilder() = default;
    ZipBuilder& SetFilePointer(void* t_file_pointer)
    {
      if (this->m_zip == nullptr)
      {
        this->m_zip = std::make_shared<ZipArchive>();
      }
      std::cout << "DEBUG: SetFilePointer()...\n";
      this->m_zip->m_data_pointer = t_file_pointer;
      return *this;
    }

    ZipBuilder& SetFileSize(size_t t_file_size)
    {
      std::cout << "DEBUG: SetFileSize()...\n";
      this->m_zip->m_data_size = t_file_size;
      return *this;
    }

    ZipBuilder& SetEndOfCentralDirectory(components::EndOfCentralDirectory* t_eocd)
    {
      std::cout << "DEBUG: SetEndOfCentralDirectory()...\n";
      this->m_zip->m_end_central_directory = t_eocd;
      return *this;
    }

    ZipBuilder& AddCentralDirectory(components::CentralDirectory* t_cd)
    {
      std::cout << "DEBUG: AddCentralDirectory()...\n";
      this->m_zip->m_central_directory_list.push_back(t_cd);
      return *this;
    }

    ZipBuilder& AddCentralDirectoryList(std::list<components::CentralDirectory*> t_cdl)
    {
      std::cout << "DEBUG: AddCentralDirectoryList()...\n";
      this->m_zip->m_central_directory_list = t_cdl;
      return *this;
    }

    ZipBuilder& AddLocalHeader(components::LocalFileHeader* t_lfh)
    {
      std::cout << "DEBUG: AddLocalHeader()...\n";
      this->m_zip->m_local_file_header_list.push_back(t_lfh);
      return *this;
    }

    ZipBuilder& AddLocalHeaderList(std::list<components::LocalFileHeader*> t_lfhl)
    {
      std::cout << "DEBUG: AddLocalHeaderList()...\n";
      this->m_zip->m_local_file_header_list = t_lfhl;
      return *this;
    }

    //ZipBuilder& AddExtendedLocalHeader();
    operator std::shared_ptr<ZipArchive>&&()
    {
      std::cout << "DEBUG: RETURN POINTER()...\n";
      return std::move(this->m_zip);
    }
  };
} // namespace archive_management_tools::archives::zip
#endif
