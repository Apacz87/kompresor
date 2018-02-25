#ifndef ZIP_HPP
#define ZIP_HPP

#include <cstdint>

namespace zip
{
  // Overall zipfile format:
  // Byte order: Little-endian
  // [Local file header + Compressed data [+ Extended local header]?]*
  // [Central directory]*
  // [End of central directory record]

  // compression method: (2 bytes)
  // 0 - The file is stored (no compression)
  // 1 - The file is Shrunk
  // 2 - The file is Reduced with compression factor 1
  // 3 - The file is Reduced with compression factor 2
  // 4 - The file is Reduced with compression factor 3
  // 5 - The file is Reduced with compression factor 4
  // 6 - The file is Imploded
  // 7 - Reserved for Tokenizing compression algorithm
  // 8 - The file is Deflated

  // The local file header
  struct LocalFileHeader
  {
    // Local file header signature (0x04034b50) (Offset: 0, Lenght: 4 bytes)
    uint32_t m_signature;

    // Version needed to extract (Offset: 4, Lenght: 2 bytes)
    uint16_t m_version;

    // General purpose bit flag (Offset: 6, Lenght: 2 bytes)
    uint16_t m_bit_flag;

    // Compression method (Offset: 8, Lenght: 2 bytes)
    uint16_t m_compression_method;

    // Last mod file time (Offset: 10, Lenght: 2 bytes)
    uint16_t m_last_mod_time;

    // Last mod file date (Offset: 12, Lenght: 2 bytes)
    uint16_t m_last_mod_date;

    // CRC-32 (Offset: 14, Lenght: 4 bytes)
    uint32_t m_crc;

    // Compressed size (n) (Offset: 18, Lenght: 4 bytes)
    uint32_t m_compressed_size;

    // Uncompressed size (Offset: 22, Lenght: 4 bytes)
    uint32_t m_uncompressed_size;

    // Filename length (f) (Offset: 26, Lenght: 2 bytes)
    uint16_t m_file_name_lenght;

    // Extra field length (e) (Offset: 28, Lenght: 2 bytes)
    uint16_t m_extra_field_length

    // Filename (Offset: 30, Lenght: (f) bytes)
    // Extra field (Offset: (30 + (f)), Lenght: (e) bytes)
    // Compressed data (Offset: ((30 + (f)) + (e)), Lenght: (n) bytes)
  }

  // The extended local header
  struct ExtendedLocalHeader
  {
    // Extended Local file header signature (0x08074b50) (Offset: 0, Lenght: 4 bytes)
    uint32_t m_signature;

    // CRC-32 (Offset: 4, Lenght: 4 bytes)
    uint32_t m_crc;

    // Compressed size (Offset: 8, Lenght: 4 bytes)
    uint32_t m_compressed_size;

    // Uncompressed size (Offset: 12, Lenght: 4 bytes)
    uint32_t m_uncompressed_size;
  }

  // The central directory
  struct CentralDirectory
  {
    // Central file header signature (0x02014b50) (Offset: 0, Lenght: 4 bytes)
    uint32_t m_signature;

    // Made by version (Offset: 4, Lenght: 2 bytes)
    uint16_t m_version_mady_by;

    // Version needed to extract (Offset: 6, Lenght: 2 bytes)
    uint16_t m_version_to_extract;

    // General purpose bit flag (Offset: 8, Lenght: 2 bytes)
    uint16_t m_bit_flag;

    // Compression method (Offset: 10, Lenght: 2 bytes)
    uint16_t m_compression_method;

    // Last mod file time (Offset: 12, Lenght: 2 bytes)
    uint16_t m_last_mod_time;

    // Last mod file date (Offset: 14, Lenght: 2 bytes)
    uint16_t m_last_mod_date;

    // CRC-32 (Offset: 16, Lenght: 4 bytes)
    uint32_t m_crc;

    // Compressed size (Offset: 20, Lenght: 4 bytes)
    uint32_t m_compressed_size;

    // Uncompressed size (Offset: 24, Lenght: 4 bytes)
    uint32_t m_uncompressed_size;

    // Filename length (f) (Offset: 28, Lenght: 2 bytes)
    uint16_t m_file_name_lenght;

    // Extra field length (e) (Offset: 30, Lenght: 2 bytes)
    uint16_t m_extra_field_length;

    // File comment length (c) (Offset: 32, Lenght: 2 bytes)
    uint16_t m_file_comment_length;

    // Disk number start (Offset: 34, Lenght: 2 bytes)
    uint16_t m_disk_number_start;

    // Internal file attributes (Offset: 36, Lenght: 2 bytes)
    uint16_t m_internal_file_attributes;

    // External file attributes (Offset: 38, Lenght: 4 bytes)
    uint32_t m_external_file_attributes;

    // Relative offset of local header (Offset: 42, Lenght: 4 bytes)
    uint32_t m_relative_offset_of_local_header;

    // Filename (Offset: 46, Lenght (f) bytes)
    // Extra field (Offset: (46 + (f)), Lenght (e) bytes)
    // File comment (Offset: ((46 + (f)) + (e)), Lenght (c) bytes)
  }

  // The end of central directory record
  struct EndOfCentralDirectory
  {
    // End of central dir signature (0x06054b50) (Offset: 0, Lenght: 4 bytes)
    uint32_t m_signature;

    // Number of this disk (Offset: 4, Lenght: 2 bytes)
    uint16_t m_this_disk_number;

    // Number of the disk with the start of the central directory (Offset: 6, Lenght: 2 bytes)
    uint16_t m_no_name_for_now;

    // Total number of entries in the central dir on this disk (Offset: 8, Lenght: 2 bytes)
    uint16_t m_number_of_entries_on_this_disk;

    // Total number of entries in the central dir (Offset: 10, Lenght: 2 bytes)
    uint16_t m_number_of_entries;

    // Size of the central directory (Offset: 12, Lenght: 4 bytes)
    uint32_t m_central_directory_size;

    // Offset of start of central directory with respect to the starting disk number (Offset: 16, Lenght: 4 bytes)
    uint32_t m_start_offset;

    // Zipfile comment length (c) (Offset: 20, Lenght: 2 bytes)
    uint16_t m_comment_length;

    // Zipfile comment (Offset: 22, Lenght: (c) bytes)
  }

}

#endif
