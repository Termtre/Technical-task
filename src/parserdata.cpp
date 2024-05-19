#include "parserdata.h"
#include <fstream>
#include <iostream>

ParserData::ParserData(std::string _url) : url(_url)
{}

bool ParserData::parserWorkTime(std::string str)
{
	if (str.size() != 11)
	{
		return false;
	}

	std::string substring1 = str.substr(0, 5);
	std::string substring2 = str.substr(6, 5);

	if (!parserTime(substring1))
	{
		return false;
	}

	if (!parserTime(substring2))
	{
		return false;
	}

	if (substring1 > substring2)
	{
		return false;
	}

	return true;
}

bool ParserData::parserData(std::string str)
{
	if (str.size() < 9) return false;

	std::string time = str.substr(0, 5);

	if (!parserTime(time)) return false;
	if (time < prevTime) return false;
	
	prevTime = time;
	
	if (str[5] != ' ') return false;
	if (str[6] < '1' || str[6] > '4') return false;
	if (str[7] != ' ') return false;
	
	uint32_t i = 8;

	for (; i < str.size() && str[i] != ' '; i++)
	{
		if (str[i] != '-' && str[i] < '0' ||
			str[i] > '9' && str[i] != '_' && str[i] < 'a' ||
			str[i] > 'z') return false;
	}

	if (str[6] != '2' && i != str.size()) return false;

	if (str[6] == '2')
	{
		if (str[i] != ' ') return false;

		std::string substring = str.substr(i + 1, str.size() - i - 1);

		if (!parserNumber(substring)) return false;

		uint32_t temp = std::stoul(substring);

		if (temp < 1 || temp > tableNumber) return false;
	}

	return true;
}

bool ParserData::parserNumber(std::string str)
{
	if (str[0] == '0') return false;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it < '0' || *it > '9')
		{
			return false;
		}
	}

	return true;
}

bool ParserData::parserTime(std::string str)
{
	if (str.size() != 5) return false;
	if (str[0] != '0' && str[0] != '1' && str[0] != '2') return false;
	if (str[1] < '0' || str[1] > '9') return false;
	if (str[0] == '2' && str[1] > '3') return false;
	if (str[2] != ':') return false;
	if (str[3] < '0' || str[3] > '5') return false;
	if (str[4] < '0' || str[4] > '9') return false;

	return true;
}

std::string ParserData::sumTime(std::string next, std::string prev)
{
	std::string result = "";
	int32_t min;
	int32_t hour;

	min = next[3] * 10 + next[4] + prev[3] * 10 + prev[4] - 22 * '0';
	hour = next[0] * 10 + next[1] + prev[0] * 10 + prev[1] - 22 * '0';
	hour += min / 60;
	min %= 60;

	result += hour / 10 + '0';
	result += hour % 10 + '0';
	result += ':';
	result += min / 10 + '0';
	result += min % 10 + '0';

	return result;
}

std::string ParserData::subTime(std::string next, std::string prev)
{
	std::string result = "";
	int32_t min;
	int32_t hour;

	min = static_cast<int32_t>(next[3] * 10 + next[4]) - static_cast<int32_t>(prev[3] * 10 + prev[4]);
	hour = static_cast<int32_t>(next[0] * 10 + next[1]) - static_cast<int32_t>(prev[0] * 10 + prev[1]);
	
	if (min < 0)
	{
		hour -= 1;
		min = 60 + min;
	}

	result += hour / 10 + '0';
	result += hour % 10 + '0';
	result += ':';
	result += min / 10 + '0';
	result += min % 10 + '0';

	return result;
}

uint32_t ParserData::countHour(std::string time)
{
	uint32_t min;
	uint32_t hour;

	min = time[3] * 10 + time[4] - 11 * '0';
	hour = time[0] * 10 + time[1] - 11 * '0';

	if (min > 0) hour += 1;

	return hour;
}

bool ParserData::checkFormat()
{
	std::ifstream file(url, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "File didn't open" << std::endl;
		return false;
	}

	std::string buffer;

	getline(file, buffer);
	if (!parserNumber(buffer))
	{
		std::cout << buffer << std::endl;
		return false;
	}

	tableNumber = std::stoul(buffer);

	getline(file, buffer);
	if (!parserWorkTime(buffer))
	{
		std::cout << buffer << std::endl;
		return false;
	}

	getline(file, buffer);
	if (!parserNumber(buffer))
	{
		std::cout << buffer << std::endl;
		return false;
	}

	while (getline(file, buffer))
	{
		if (!parserData(buffer))
		{
			std::cout << buffer << std::endl;
			return false;
		}
	}

	file.close();

	return true;
}
