#include <iostream>
#include <string>
#include <vector>

#include "../external/clipp/include/clipp.h"
#include "archiver.hpp"

int main(int argc, char* argv[])
{
  // The current version of application.
  const std::string ApplicationVersion = "0.0.0-alpha.0.7.2";

  // The application running mode.
  enum class Mode {COMPRESSION, DECOMPRESSION, INFO, HELP};
  Mode selected = Mode::HELP;

  // The selected archive type.
  archiver::ArchiveType fileFormat = archiver::ArchiveType::ZIP;

  // The selected compression algorithm.
  archiver::CompressionAlgorithm algorithm = archiver::CompressionAlgorithm::DEFLATE;

  // The program input files.
  std::vector<std::string> input;

  // The program output file/directory.
  std::string output;

  // The compression mode options.
  auto compressionMode = (
    // TODO: Archive selection need better documentation.
    clipp::command("pack").set(selected, Mode::COMPRESSION).doc("data compression mode"),
    clipp::values("input file(s)", input),
    clipp::with_prefix("-", clipp::option("zip") >> [&]{ fileFormat = archiver::ArchiveType::ZIP; } |
      clipp::option("gz") >> [&]{ fileFormat = archiver::ArchiveType::GNUGZIP; } ).doc("determines used archive format"),
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

  // The command line parser.
  if(clipp::parse(argc, argv, cli))
  {
    switch(selected)
    {
      case Mode::COMPRESSION:
      {
        // TODO: Create zip file from input files.
        archiver::ArchiveFactory archiver(fileFormat, algorithm);
        archiver.Create(input);
        std::cout << "Zip: " << (fileFormat == archiver::ArchiveType::ZIP ? "true" : "false") << '\n';
        std::cout << "Output file: " << output << '\n';
        break;
      }
      case Mode::DECOMPRESSION:
      {
        // TODO: Decompress archive files from input.
        std::cout << "Input files: ";
        for (auto file : input)
        {
          std::cout << file << ' ';
        }
        std::cout << std::endl;
        std::cout << "Output dir: " << output << '\n';
        break;
      }
      case Mode::INFO:
      {
        // TODO: Print info about files from input.
        for (auto file : input)
        {
          archiver::FileInfo(file);
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

  return 0;
}
