#include <iostream>
#include <string>
#include <vector>

#include "clipp.h"
#include "version.h"

int main(int argc, char *argv[]) {
	bool verbose = false;
	std::vector<std::string> input;
	std::string output;

	enum class mode { compress, decompress, listout, help };

	mode selected = mode::help;

	auto compressMode = (clipp::required("-c")
				 .set(selected, mode::compress)
				 .doc("Compresses one or more files"),
			     clipp::values("files", input),
			     (clipp::option("-o") & clipp::value("output file", output)));

	auto decompressMode = (clipp::required("-d")
				   .set(selected, mode::decompress)
				   .doc("Decompresses a zip archive"),
			       clipp::value("file", input),
			       (clipp::option("-o") & clipp::value("output dir", output)));

	auto listoutMode = (clipp::required("-l")
				.set(selected, mode::listout)
				.doc("Lists the contents of a zip archive"),
			    clipp::values("files", input));

	auto cli =
	    ((compressMode | decompressMode | listoutMode |
	      clipp::option("-h", "--help").set(selected, mode::help).doc("Display help message")),
	     clipp::option("-v", "--verbose")
		 .set(verbose)
		 .doc("Enables verbose output with additional details"),
	     clipp::option("--version")
		 .call([] { std::cout << "Version: " << PROJECT_VERSION << "\n\n"; })
		 .doc("Print version information"));

	if (clipp::parse(argc, argv, cli)) {
		switch (selected) {
		case mode::compress: /* ... */
			break;
		case mode::decompress: /* ... */
			break;
		case mode::listout: /* ... */
			break;
		case mode::help:
			std::cout << clipp::make_man_page(cli, argv[0]);
			break;
		}
	} else {
		std::cout << clipp::usage_lines(cli, argv[0]) << '\n';
	}

	return 0;
}
