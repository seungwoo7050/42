#include "SedIFL.hpp"

int main(const int ac, const char** av) {
	if (ac != 4) {
		std::cout << "사용법: " << av[0] << " <infile> <origin string> <replace string>" << std::endl;
		return 1;
	}
	SedIFL	sedifl(av[1]);
	if (sedifl.replace(av[2], av[3]))
		return 1;
	return 0;
}