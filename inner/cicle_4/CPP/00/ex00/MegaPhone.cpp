/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MegaPhone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:02:14 by seungwok          #+#    #+#             */
/*   Updated: 2024/04/29 16:46:47 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and some other basic stuf

#include <iostream>
#include <cctype>

class	MegaPhone {
private:
	int					ac;
	const char	**av;

public:
	MegaPhone();
	MegaPhone(const int ac, const char **av);
	~MegaPhone();
	
	void print();
};

MegaPhone::MegaPhone() {}
MegaPhone::MegaPhone(const int ac, const char **av) : ac(ac), av(av) {}
MegaPhone::~MegaPhone() {}

void	MegaPhone::print() {
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else {
		for (int i = 1; av[i]; i++) {
			for (int j = 0; av[i][j]; j++) {
					std::cout << static_cast<char>(std::toupper(av[i][j]));
			}
		}
	}
	std::cout << std::endl;
}

int main(const int ac, const char **av)
{
	MegaPhone megaphone(ac, av);
	megaphone.print();
	return 0;
}