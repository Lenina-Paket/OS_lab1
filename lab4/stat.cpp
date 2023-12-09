#include <iostream>
#include "include/realization.hpp"

int main() {
    int com;

    std::cout << "Enter 1 or 2 to select a function or -1 to exit" << std::endl;

    while (std::cin >> com) {

        if (com == 1) {
            float A, deltaX;
            std::cout << "Enter A and deltaX" << std::endl;
            std::cin >> A >> deltaX;
            std::cout << "Derivative value: " << Derivative(A, deltaX) << std::endl;
        }

        if (com == 2) {
            int A, B;
            std::cout << "Enter A and B" << std::endl;
            std::cin >> A >> B;
            std::cout << "GCF value: " << GCF(A, B) << std::endl;
        }

        if (com == -1) {
            std::cout << "Exit" << std::endl;
            return 0;
        }
        std::cout << "Enter 1 or 2 to select a function or -1 to exit" << std::endl;
    }
}