#include <iostream>
#include "Span.hpp"

int main() {
    try {
        Span sp = Span(5);
        sp.addNumber(4);
        sp.addNumber(2);
        sp.addNumber(42);
        sp.addNumber(24);
        sp.addNumber(4242);

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;

        std::vector<int> vec;
        for (int i = 0; i < 10000; i++) {
            vec.push_back(i);
        }
        Span bigSpan = Span(10000);
        bigSpan.addNumbers(vec.begin(), vec.end());
        std::cout << bigSpan.shortestSpan() << std::endl;
        std::cout << bigSpan.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
