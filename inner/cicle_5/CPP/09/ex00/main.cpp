#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

#define DATABASE "data.csv"

int main(const int argc, const char* argv[]) {
	if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

	try {
		BitcoinExchange exchange(DATABASE);
		exchange.evaluateInputFile(argv[1]);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}