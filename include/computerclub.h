#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <queue>

struct client
{
	uint32_t status;
	std::string name;
	std::string timeEntry;
	std::string timeLeave;

};

class ComputerClub
{
private:
	uint32_t tableNumber;
	std::string timeOpen;
	std::string timeClose;
	uint32_t costHour;

	std::queue<client> clientBase;
 
private:


public:
	ComputerClub(std::string url);
	~ComputerClub() = default;

	void show();

};