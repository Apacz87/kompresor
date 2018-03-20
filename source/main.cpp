#include <iostream>
#include <string>
#include <vector>

#include "archivization_tools.hpp"
#include "clipp.h"
#include "zip.hpp"

int main(int argc, char* argv[])
{
  namespace amt = archive_management_tools;
  // The current version of application.
  const std::string ApplicationVersion = "0.0.0-alpha.0.13.0";

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
          // TODO: Create zip file from input files.
          // amt::Archive archive = amt::ArchiveFactory(settings);
          // amt::Archive archive = amt::ArchiveFactory.Create(settings);
          // archive.pack(input);
          // archive.save(output)
          break;
        }
        case Mode::DECOMPRESSION:
        {
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
          // TODO: Print info about files from input.
          for (auto file : input)
          {
            if (amt::IsArchive(file))
            {
              auto archive = amt::ArchiveFactory::Read(file);
              archive->PrintFileStat();
            }
            else
            {
              amt::FileInfo(file);
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

  return 0;
}
