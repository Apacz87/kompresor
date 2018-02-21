#include <iostream>
#include <string>
#include <vector>

#include "../external/clipp/include/clipp.h"

int main(int argc, char* argv[])
{
  const std::string ApplicationName = "kompresor";
  const std::string ApplicationVersion = "0.0.0-alpka.0.2.0";
  enum class Mode {COMPRESSION, DECOMPRESSION, INFO, HELP};
  enum class Archive {ZIP};
  enum class CompressionAlgorithm {BZIP2, LZMA, DEFLATE, DCL, IMPLODE, WAVPACK};
  Mode selected = Mode::HELP;
  Archive fileFormat = Archive::ZIP;
  CompressionAlgorithm algorithm = CompressionAlgorithm::DEFLATE;
  std::vector<std::string> input;
  std::string output;

  auto compressionMode = (
    clipp::command("pack").set(selected, Mode::COMPRESSION).doc("data compression mode"),
    clipp::values("input file(s)", input),
    clipp::option("-z", "--zip").set(fileFormat, Archive::ZIP).doc("use zip archive file format"),
    clipp::option("-o", "--output").doc("output file") & clipp::value("output file", output)
  );

  auto decompressionMode = (
    clipp::command("unpack").set(selected, Mode::DECOMPRESSION).doc("data decompression mode"),
    clipp::values("input file(s)", input),
    clipp::option("-o", "--output").doc("output directory") & clipp::value("output dir", output)
  );

  auto infoMode = (
    clipp::command("info").set(selected, Mode::INFO).doc("displays file information"),
    clipp::values("input file", input)
  );

  auto cli = (
    (compressionMode | decompressionMode | infoMode | clipp::command("help").set(selected,Mode::HELP).doc("print man page") ),
    clipp::option("-v", "--version").call([&ApplicationVersion]{
      std::cout << "Version: " << ApplicationVersion << "\n";
      std::cout << "Compilation date: " << __DATE__ << ' ' << __TIME__ "\n";
    }).doc("show version")
  );

  if(clipp::parse(argc, argv, cli))
  {
    switch(selected)
    {
      case Mode::COMPRESSION:
      {
        std::cout << "Input files: ";
        for (auto file : input)
        {
          std::cout << file << ' ';
        }
        std::cout << std::endl;
        std::cout << "Zip: " << (fileFormat == Archive::ZIP ? "true" : "false") << '\n';
        std::cout << "Output file: " << output << '\n';
        break;
      }
      case Mode::DECOMPRESSION:
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
      case Mode::INFO:
      {
        std::cout << "Input files: ";
        for (auto file : input)
        {
          std::cout << file << ' ';
        }
        std::cout << std::endl;
        break;
      }
      case Mode::HELP: std::cout << clipp::make_man_page(cli, ApplicationName); break;
    }
  }
  else
  {
    std::cout << clipp::usage_lines(cli, ApplicationName) << '\n';
  }

  return 0;
}
