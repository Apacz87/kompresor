#include <iostream>
#include <string>
#include <vector>

#include "../external/clipp/include/clipp.h"

int main(int argc, char* argv[])
{
  enum class mode {compression, decompression, info, help};
  enum class archive {zip};
  enum class compressionAlgorithm {BZIP2, LZMA, Deflate, DCL, Implode, WavPack};
  mode selected = mode::help;
  archive fileFormat = archive::zip;
  compressionAlgorithm algorithm = compressionAlgorithm::Deflate;
  std::vector<std::string> input;
  std::string output;
  const std::string ApplicationName = "kompresor";
  const std::string ApplicationVersion = "0.0.0-alpka.0.1.0";

  auto compressionMode = (
    clipp::command("pack").set(selected, mode::compression).doc("data compression mode"),
    clipp::values("input file(s)", input),
    clipp::option("-z", "--zip").set(fileFormat, archive::zip).doc("use zip archive file format"),
    clipp::option("-o", "--output").doc("output file") & clipp::value("output file", output)
  );

  auto decompressionMode = (
    clipp::command("unpack").set(selected, mode::decompression).doc("data decompression mode"),
    clipp::values("input file(s)", input),
    clipp::option("-o", "--output").doc("output directory") & clipp::value("output dir", output)
  );

  auto infoMode = (
    clipp::command("info").set(selected, mode::decompression).doc("displays file information"),
    clipp::values("input file", input)
  );

  auto cli = (
    (compressionMode | decompressionMode | infoMode | clipp::command("help").set(selected,mode::help).doc("print man page") ),
    clipp::option("-v", "--version").call([&ApplicationVersion]{
      std::cout << "Version: " << ApplicationVersion << "\n";
      std::cout << "Compilation date: " << __DATE__ << ' ' << __TIME__ "\n";
    }).doc("show version")
  );

  if(clipp::parse(argc, argv, cli))
  {
    switch(selected)
    {
      case mode::compression:
      {
        std::cout << "Input files: ";
        for (auto file : input)
        {
          std::cout << file << ' ';
        }
        std::cout << std::endl;
        std::cout << "Zip: " << (fileFormat == archive::zip ? "true" : "false") << '\n';
        std::cout << "Output file: " << output << '\n';
        break;
      }
      case mode::decompression:
      {
        std::cout << "Input files: ";
        for (auto file : input)
        {
          std::cout << file << ' ';
        }
        std::cout << std::endl;
        std::cout << "Output dir: " << output << '\n';
        break;
      }
      case mode::info:
      {
        std::cout << "Input files: ";
        for (auto file : input)
        {
          std::cout << file << ' ';
        }
        std::cout << std::endl;
        break;
      }
      case mode::help: std::cout << clipp::make_man_page(cli, ApplicationName); break;
    }
  }
  else
  {
    std::cout << clipp::usage_lines(cli, ApplicationName) << '\n';
  }

  return 0;
}
