#include <iostream>
#include <string>
#include <vector>

#include "archivization_tools.hpp"
#include "clipp.h"
#include "zip.hpp"
#include "debug_utils.h"

int main(int argc, char* argv[])
{
  debug_log("Enter main function");
  // Use archive_management_tools namespace as amt
  namespace amt = archive_management_tools;
  // The current version of application.
  const std::string ApplicationVersion = "0.0.0-alpha.0.0.0-prototype-0.2.0";

  // The application running mode.
  enum class Mode {COMPRESSION, DECOMPRESSION, INFO, HELP};
  Mode selected = Mode::HELP;

  // The selected archive type.
  amt::ArchiveType fileFormat = amt::ArchiveType::ZIP;

  // The selected compression algorithm.
  amt::CompressionAlgorithm algorithm = amt::CompressionAlgorithm::DEFLATE;

  // The program input files.
  std::vector<std::string> input;

  // The program output file/directory.
  std::string output;

  // The compression mode options.
  auto compressionMode = (
    // TODO: Archive selection need better documentation.
    clipp::command("pack").set(selected, Mode::COMPRESSION).doc("data compression mode"),
    clipp::values("input file(s)", input),
    clipp::with_prefix("-", clipp::option("zip") >> [&]{ fileFormat = amt::ArchiveType::ZIP; } |
      clipp::option("gz") >> [&]{ fileFormat = amt::ArchiveType::GNUGZIP; } ).doc("determines used archive format"),
    clipp::option("-o", "--output").doc("output file") & clipp::value("output file", output)
  );

  // The decompression mode options.
  auto decompressionMode = (
    clipp::command("unpack").set(selected, Mode::DECOMPRESSION).doc("data decompression mode"),
    clipp::values("input file(s)", input),
    clipp::option("-o", "--output").doc("output directory") & clipp::value("output dir", output)
  );

  // The info mode options.
  auto infoMode = (
    clipp::command("info").set(selected, Mode::INFO).doc("displays file information"),
    clipp::values("input file", input)
  );

  // The command line interface.
  auto cli = (
    (compressionMode | decompressionMode | infoMode | clipp::command("help").set(selected,Mode::HELP).doc("print man page") ),
    clipp::option("-v", "--version").call([&ApplicationVersion]{
      std::cout << "Version: " << ApplicationVersion << "\n";
      std::cout << "Compilation date: " << __DATE__ << ' ' << __TIME__ "\n";
    }).doc("show version")
  );

  try
  {
    // The command line parser.
    if(clipp::parse(argc, argv, cli))
    {
      switch(selected)
      {
        case Mode::COMPRESSION:
        {
          debug_log("COMPRESSION MODE");
          // TODO: Create zip file from input files.
          // amt::Archive archive = amt::ArchiveFactory(settings);
          // amt::Archive archive = amt::ArchiveFactory.Create(settings);
          // archive.pack(input);
          // archive.save(output)
          break;
        }
        case Mode::DECOMPRESSION:
        {
          debug_log("DECOMPRESSION MODE");
          // TODO: Decompress archive files from input.
          for (auto file : input)
          {
            // amt::Archive archive = amt::ArchiveFactory(file);
            // amt::Archive archive = amt::ArchiveFactory.Read(file);
            // archive.unpack();
            // archive.unpack(output);
          }

          break;
        }
        case Mode::INFO:
        {
          debug_log("INFO MODE");
          for (auto file : input)
          {
            // TODO: replace with std::filesystem::exists() when filesystem will
            // be supported by compiler
            if (amt::FileExist(file)) {
              if (amt::IsArchive(file))
              {
                auto archive = amt::ArchiveFactory::Read(file);
                std::cout << "[ARCHIVE] " << file << " " << archive->FileStat() << '\n';
                #ifdef DEBUG
                archive->PrintFileStat();
                #endif
              }
              else
              {
                std::cout << amt::FileInfo(file) << "\n\n";
              }
            }
            else {
              std::cerr << "[ERROR] file \"" << file << "\" does not exist!\n\n";
            }
          }

          break;
        }
        case Mode::HELP: std::cout << clipp::make_man_page(cli, argv[0]); break;
      }
    }
    else
    {
      std::cout << clipp::usage_lines(cli, argv[0]) << '\n';
    }
  }
  catch(const std::exception& excep)
  {
    std::cerr << "An exception occurred, with message: " << excep.what() << '\n';
    return 1;
  }

  debug_log("Proper exit");
  return 0;
}
