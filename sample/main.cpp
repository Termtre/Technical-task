#include "computerclub.h"

int main(int argc, const char * argv[])
{
	if (argc == 1) return 0;

	ComputerClub qwerty(argv[1]);
	qwerty.show();

	return 0;
}