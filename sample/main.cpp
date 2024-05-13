#include <iostream>
#include <fstream>
#include <string>

int main(int argc, const char * argv[])
{
	if (argc == 1) return 1;

	std::ifstream file(argv[1], std::ios::in);

	if (!file.is_open())
	{
		std::cout << "smth wrong";
		return 1;
	}

	int tableNumber, guestNumber;

	file >> tableNumber;
	std::string time1, time2;
	file >> time1 >> time2;
	file >> guestNumber;

	std::cout << tableNumber << std::endl;
	std::cout << time1 << " " << time2 << std::endl;
	std::cout << guestNumber << std::endl;

	/*while (file >> x)
	{
		std::cout << x << std::endl;
	}*/

	file.close();

	std::cout << "Have arguments: " << argc << std::endl;
	
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;

	return 1;
}