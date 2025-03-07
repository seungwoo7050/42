#include "Zombie.hpp"

int main() {
	std::string name;
	
	std::cout << "Creating zombie on the stack." << std::endl;
	std::cout << "Zombie name: ";
	std::cin >> name;

	Zombie zombie_stack(name);
	zombie_stack.announce();

	std::cout << "Creating zombie on th heap." << std::endl;
	std::cout << "Zombie name: ";
	std::cin >> name;

	Zombie *zombie_heap = newZombie(name);
	zombie_heap->announce();
	delete zombie_heap;

	std::cout << "Call a function called randomChump()." << std::endl;
	randomChump("MOOYAHO");
	
	return (0);
}