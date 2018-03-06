#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <string>

namespace amt::base
{
  enum class ArchiveType {ZIP, GNUGZIP};
  enum class CompressionAlgorithm {BZIP2, LZMA, DEFLATE, DCL, IMPLODE, WAVPACK};
  
  class Archive
  {
    // TODO: Add archive file class content.
  public:
    virtual void Pack(std::string) = 0;
    virtual void Unpack(std::string) = 0;
    virtual void Save(std::string) = 0;
  };
} // namespace amt::base

#endif
