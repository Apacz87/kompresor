#ifndef ZIP_COMPONENTS_HPP
#define ZIP_COMPONENTS_HPP

#include <string>

namespace archive_management_tools::archives::zip::components
{
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
  #pragma pack(push, 1)
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
    uint16_t m_extra_field_length;

    // Filename (Offset: 30, Lenght: (f) bytes)
    std::string get_file_name()
    {
      char* pointer = reinterpret_cast<char*>(this->m_signature);
      return std::string(&pointer[30], this->m_file_name_lenght);
    }

    // Extra field (Offset: (30 + (f)), Lenght: (e) bytes)
    size_t get_extra_field_offset()
    {
      char* pointer = reinterpret_cast<char*>(this->m_signature);
      return (size_t)&pointer[30 + this->m_file_name_lenght];
    }

    // Compressed data (Offset: ((30 + (f)) + (e)), Lenght: (n) bytes)
    size_t get_data_offset()
    {
      return this->get_extra_field_offset() + this->m_extra_field_length;
    }

    void print_data()
    {
      auto data = (unsigned char*)this->get_data_offset();
      for ( size_t i = 0, j = 0; i < this->m_compressed_size; i++, j++)
      {
        //std::cout << std::showbase << std::hex << (int)data[i];
        //std::cout << "0x" << std::hex << (int)data[i];
        printf("%02X", (int)data[i]);
        if (j > 15)
        {
          //std::cout << '\n';
          printf("\n");
          j = 0;
          continue;
        }
        //std::cout << ' ';
        printf(" ");
      }

      std::cout << std::dec << std::endl;
    }

    // Print conntent from local file header
    void print()
    {
      char* signature_ptr = reinterpret_cast<char*>(this->m_signature);
      std::cout << "Signature: " << signature_ptr[0] << signature_ptr[1] << " "
        << (int)signature_ptr[2] << " " << (int)signature_ptr[3] << '\n';
      std::cout << "Version: " << this->m_version <<  '\n';
      std::cout << "Bit flag: " << std::hex << this->m_bit_flag << '\n';
      std::cout << "Compression method: " << this->m_compression_method << '\n';
      std::cout << "Last mod time:"<< std::hex << this->m_last_mod_time << '\n';
      std::cout << "Last mod date:"<< std::hex << this->m_last_mod_date << '\n';
      std::cout << "CRC-32: " << std::hex << this->m_crc << '\n';
      std::cout << "Compressed size: " << std::dec << this->m_compressed_size << " bytes\n";
      std::cout << "Uncompressed size: " << this->m_uncompressed_size << " bytes\n";
      std::cout << "File_name_lenght: " << this->m_file_name_lenght << '\n';
      std::cout << "Extra_field_length: " << this->m_extra_field_length << '\n';
      std::cout << "File name: " << this->get_file_name() << '\n';
      std::cout << "Struct offset: " << this << '\n';
      std::cout << "Extra field offset: " << std::hex << this->get_extra_field_offset() << std::dec << '\n';
      std::cout << "Data field offset: " << std::hex << this->get_data_offset() << std::dec << '\n';
      std::cout << "Data:\n";
      this->print_data();
    }
  };
  #pragma pack(pop)

  // The extended local header
  #pragma pack(push, 1)
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
  };
  #pragma pack(pop)

  // The central directory
  #pragma pack(push, 1)
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
    std::string get_file_name()
    {
      char* ptr = (char*)&this->m_signature;
      return std::string(&ptr[46], this->m_file_name_lenght);
    }

    // Extra field (Offset: (46 + (f)), Lenght (e) bytes)
    size_t get_extra_field_offset()
    {
      char* signature_ptr = (char*)&this->m_signature;
      return (size_t)((signature_ptr + 46) + this->m_file_name_lenght);
    }

    // File comment (Offset: ((46 + (f)) + (e)), Lenght (c) bytes)
    size_t get_comment_offset()
    {
      return this->get_extra_field_offset() + this->m_extra_field_length;
    }

    void print_data()
    {
      char* signature_ptr = (char*)&this->m_signature;
      std::cout << "Central directory signature: " << signature_ptr[0] << signature_ptr[1] << " "
        << (int)signature_ptr[2] << " " << (int)signature_ptr[3] << '\n';
      //std::cout << "Central directory signature: " << this->m_signature << '\n';
      std::cout << "Made by version: " << this->m_version_mady_by << '\n';
      std::cout << "Version needed to extract: " << this->m_version_to_extract << '\n';
      std::cout << "Bit Flag: " << std::hex << this->m_bit_flag << '\n';
      std::cout << "Compression method: " << this->m_compression_method << '\n';
      std::cout << "Last mod file time: " << this->m_last_mod_time << '\n';
      std::cout << "Last mod file date: " << this->m_last_mod_date << '\n';
      std::cout << "CRC-32: " << this->m_crc << '\n';
      std::cout << "Compressed size: " << std::dec << this->m_compressed_size << " bytes\n";
      std::cout << "Uncompressed size: " << this->m_uncompressed_size << " bytes\n";
      std::cout << "Filename length: " << this->m_file_name_lenght << '\n';
      std::cout << "Extra field length: " << this->m_extra_field_length << '\n';
      std::cout << "File comment length: " << this->m_file_comment_length << '\n';
      std::cout << "Disk number start: " << std::hex << this->m_disk_number_start << '\n';
      std::cout << "Internal file attributes: " << this->m_internal_file_attributes << '\n';
      std::cout << "External file attributes: " << this->m_external_file_attributes << '\n';
      std::cout << "Relative offset of local header: " << this->m_relative_offset_of_local_header << '\n';
      std::cout << "File name: " << this->get_file_name() << std::endl;
      if (this->m_file_comment_length > 0)
      {
        std::cout << "Comment: " << std::string(this->get_comment_offset(), this->m_file_comment_length) << std::endl;
      }
    }
  };
  #pragma pack(pop)

  // The end of central directory record
  #pragma pack(push, 1)
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
    std::string get_comment()
    {
      char* ptr = (char*)&this->m_signature;
      return std::string(&ptr[22], this-> m_comment_length);
    }

    void print_data()
    {
      char* signature_ptr = (char*)&this->m_signature;
      std::cout << "End of central directory signature: " << signature_ptr[0] << signature_ptr[1] << " "
        << (int)signature_ptr[2] << " " << (int)signature_ptr[3] << '\n';
      std::cout << "Number of this disk: " << std::dec << this->m_this_disk_number << '\n';
      std::cout << "Number of the disk with the start of the central directory: " << this->m_no_name_for_now << '\n';
      std::cout << "Total number of entries in the central dir on this disk: " << this->m_number_of_entries_on_this_disk << '\n';
      std::cout << "Total number of entries in the central dir: " << this->m_number_of_entries << '\n';
      std::cout << "Size of the central directory: " << this->m_central_directory_size << " bytes\n";
      std::cout << "Offset of start of central directory: " << this->m_start_offset << '\n';
      std::cout << "Zipfile comment length: " << this->m_comment_length << '\n';
      if (this->m_comment_length > 0)
      {
        std::cout << "Comment: " << this->get_comment() << '\n';
      }
    }
  };
  #pragma pack(pop)
} // namespace archive_management_tools::archives::zip::components
#endif
