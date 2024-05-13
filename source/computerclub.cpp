#include "../include//computerclub.h"
#include <fstream>
#include <iostream>

ComputerClub::ComputerClub(std::string url)
{
	std::ifstream file(url, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "File didn't find" << std::endl;
		return;
	}

	file >> tableNumber;
	file >> timeOpen >> timeClose;
	file >> costHour;
}

void ComputerClub::show()
{
	std::cout << timeOpen << std::endl;
	std::cout << timeClose << std::endl;
}