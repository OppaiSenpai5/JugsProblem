#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "JugsProblem.h"

const char* INVALID_INPUT_MESSAGE = "The input supplied is invalid!";

JugsProblem::liters read_input()
{
	std::string input;
	std::getline(std::cin, input);
	bool valid_input = !input.empty() &&
		std::find_if(input.cbegin(), input.cend(),
			[](char c) { return !std::isdigit(c); }) == input.cend();

	if (!valid_input)
	{
		throw INVALID_INPUT_MESSAGE;
	}
	std::istringstream number(input);
	JugsProblem::liters result;
	number >> result;

	return result;
}

int main()
{

	try
	{
		std::cout << "x=";
		JugsProblem::liters x = read_input();
		std::cout << "y=";
		JugsProblem::liters y = read_input();
		std::cout << "z=";
		JugsProblem::liters z = read_input();
		std::cout << "v=";
		JugsProblem::liters v = read_input();
		std::cout << std::endl;

		JugsProblem jugs_problem(x, y, z, v);
		jugs_problem.solve();
	}
	catch (const char* exception)
	{
		std::cout << std::endl;
		std::cerr << exception << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}