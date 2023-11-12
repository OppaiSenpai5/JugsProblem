#include <iostream>
#include "JugsProblem.h"

int main()
{
	size_t x, y, z, v;

	std::cout << "x=";
	std::cin >> x;
	std::cout << "y=";
	std::cin >> y;
	std::cout << "z=";
	std::cin >> z;
	std::cout << "v=";
	std::cin >> v;

	JugsProblem jugs_problem(x, y, z, v);
	jugs_problem.solve();

	return EXIT_SUCCESS;
}