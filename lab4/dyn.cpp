#include <iostream>
#include <string>
#include <dlfcn.h>


int main() {
    std::string lib1 = "../build/lib_1.so";
	std::string lib2 = "../build/lib_2.so";
	
	void *curlib = dlopen(lib1.c_str(), RTLD_LAZY);

	float (*Derivative)(float A, float deltaX);
	int (*GCF)(int A, int B);

	Derivative = (float (*)(float, float)) dlsym(curlib, "Derivative");
    GCF = (int (*)(int, int)) dlsym(curlib, "GCF");

    int com;
	int number_lib = 1;
	std::cout << "Enter 1 or 2 to select a function or -1 to exit or 0 switch to library" << std::endl;

	while(std::cin >> com) {

		if (com == 0) {
			dlclose(curlib);
			if (number_lib == 1) {
				std::cout << "You switched to library number 2" << std::endl;
				curlib = dlopen(lib2.c_str(), RTLD_LAZY);
				number_lib = 2;

			} else {
				std::cout << "You switched to library number 1" << std::endl;
				curlib = dlopen(lib1.c_str(), RTLD_LAZY);
				number_lib= 1;
			}
			Derivative = (float (*)(float, float)) dlsym(curlib, "Derivative");
    		GCF = (int (*)(int, int)) dlsym(curlib, "GCF");
		}

		if (com == 1) {
			float A, deltaX, Ans1;
			std::cout << "Enter A and deltaX" << std::endl;
			std::cin >> A >> deltaX;
			Ans1 = Derivative(A, deltaX);
			std::cout<<"Derivative value: " << Ans1 << std::endl;
		}

		if (com == 2) {
			int A, B, Ans2;
			std::cout << "Enter A and B" << std::endl;
			std::cin >> A >> B;
			Ans2 = GCF(A, B);
			std::cout << "GCF value: " << Ans2 << std::endl;
		}

		if (com == -1) {
			std::cout << "Exit" << std::endl;
			return 0;
		}

		std::cout << "Enter 1 or 2 to select a function or -1 to exit or 0 switch to library" << std::endl;
		
	}
	
}