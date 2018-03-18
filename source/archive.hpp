#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <string>
#include <memory>

namespace archive_management_tools::archives
{

  enum class ArchiveType {UNKNOWN, ZIP, GNUGZIP};
  enum class CompressionAlgorithm {BZIP2, LZMA, DEFLATE, DCL, IMPLODE, WAVPACK};

  class Archive : public std::enable_shared_from_this<Archive>
  {
    int m_file_descriptor;

    // TODO: Add archive file class content.
  public:
    std::shared_ptr<Archive> GetPointer()
    {
        return shared_from_this();
    }
    virtual void PrintFileStat() = 0;
    virtual void Pack(std::string) = 0;
    virtual void Unpack(std::string) = 0;
    virtual void Save(std::string) = 0;
  };
} // namespace archive_management_tools::archives

#endif
