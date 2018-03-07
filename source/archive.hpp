#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <string>

namespace archive_management_tools::archives
{

  enum class ArchiveType {UNKNOWN, ZIP, GNUGZIP};
  enum class CompressionAlgorithm {BZIP2, LZMA, DEFLATE, DCL, IMPLODE, WAVPACK};

  class Archive
  {
    int m_file_descriptor;

    // TODO: Add archive file class content.
  public:
    virtual void Pack(std::string) = 0;
    virtual void Unpack(std::string) = 0;
    virtual void Save(std::string) = 0;
  };
} // namespace archive_management_tools::archives

#endif
