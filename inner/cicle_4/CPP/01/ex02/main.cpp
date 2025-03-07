#include <iostream>

int main() {
	std::string	string			= "HI THIS IS BRAIN";
	std::string	*stringPTR	= &string;
	std::string	&stringREF	= string;

	std::cout << std::endl;
	std::cout << "***** ADDRESS *****" << std::endl;
	std::cout << "stringVAR: " << &string << std::endl;
	std::cout << "stringPTR: " << stringPTR << std::endl;
	std::cout << "stringREF: " << &stringREF << std::endl;
	std::cout << std::endl;

	std::cout << "****** VALUE ******" << std::endl;
	std::cout << "stringVAR: " << string << std::endl;
	std::cout << "stringPTR: " << *stringPTR << std::endl;
	std::cout << "stringREF: " << stringREF << std::endl;

	return 0;
	


	return (0);
}