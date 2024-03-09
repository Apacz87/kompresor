#include <iostream>

int main(int argc, const char *argv[]) {
	std::cout << "name of program: " << argv[0] << "\n";
	for (int i = 1; i < argc; i++) {
		std::cout << "arg " << i << " " << argv[i] << "\n";
	}

	return 0;
}
