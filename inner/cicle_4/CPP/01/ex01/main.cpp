#include "Zombie.hpp"

#define N	5

int main() {
	Zombie *horde = zombieHorde(N, "zombie");

	for(int i = 0; i < N; i++) {
		horde[i].announce();
	}
	
	delete [] horde;
	return (0);
}