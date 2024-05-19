#include "computerclub.h"
#include <fstream>
#include <iostream>
#include "parserdata.h"

void ComputerClub::closedClub()
{
	if (tableBase.empty()) return;

	for (auto it = clientBase.begin(); it != clientBase.end(); ++it)
	{
		std::cout << timeClose << " 11 " << it->first << std::endl;
		if (it->second != 0) tableBase[it->second - 1].setEndTime(timeClose);
	}

	clientBase.clear();
}

ComputerClub::ComputerClub(std::string _url) : url(_url)
{}

void ComputerClub::show()
{
	ParserData pars(url);

	if (!pars.checkFormat()) return;

	std::ifstream file(url, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "File didn't open" << std::endl;
		return;
	}

	file >> tableNumber;
	file >> timeOpen;
	file >> timeClose;
	file >> costHour;

	tableBase.resize(tableNumber);
	freeTable = tableNumber;

	std::cout << timeOpen << std::endl;

	std::string time, name;
	uint32_t id, nTable;

	while (file >> time >> id >> name)
	{
		std::cout << time << " " << id << " " << name;

		if (id == 2)
		{
			file >> nTable;
			std::cout << " " << nTable;
		}

		std::cout << std::endl;

		if (time == timeClose)
		{
			if (id == 1) std::cout << time << " 13 " << errors[NotOpenYet] << std::endl;
			else std::cout << time << " 13 " << errors[ClientUnknown] << std::endl;

			closedClub();

			continue;
		}

		if (time < timeOpen || time > timeClose)
		{
			closedClub();

			if (id == 1) std::cout << time << " 13 " << errors[NotOpenYet] << std::endl;
			else std::cout << time << " 13 " << errors[ClientUnknown] << std::endl;

			continue;
		}

		auto it = clientBase.find(name);

		if (it == clientBase.end())
		{
			if (id == 1) clientBase.insert({ name, 0 });
			else std::cout << time << " 13 " << errors[ClientUnknown] << std::endl;
		}
		else
		{
			switch (id)
			{
			case 1:
			{
				std::cout << time << " 13 " << errors[YouShallNotPass] << std::endl;

				break;
			}
			case 2:
			{
				if (tableBase[nTable - 1].busy)
				{
					std::cout << time << " 13 " << errors[PlaceIsBusy] << std::endl;
				}
				else
				{
					it->second = nTable;
					tableBase[nTable - 1].setCountTime(time);
					tableBase[nTable - 1].busy = true;
					freeTable--;
				}

				break;
			}
			case 3:
			{
				if (it->second != 0) break;

				if (freeTable)
				{
					std::cout << time << " 13 " << errors[ICanWaitNoLonger] << std::endl;
				}
				else
				{
					if (queueForTable.size() != tableNumber)
					{
						queueForTable.push(name);
					}
					else
					{
						std::cout << time << " 11 " << name << std::endl;
						clientBase.erase(name);
					}
				}

				break;
			}
			case 4:
			{
				nTable = it->second;
				clientBase.erase(name);

				if (nTable != 0)
				{
					if (queueForTable.empty())
					{
						tableBase[nTable - 1].setEndTime(time);
						tableBase[nTable - 1].busy = false;
						freeTable++;
					}
					else
					{
						name = queueForTable.front();
						std::cout << time << " 12 " << name << " " << nTable << std::endl;
						queueForTable.pop();
						clientBase.find(name)->second = nTable;
					}
				}

				break;
			}
			}
		}
	}

	file.close();

	closedClub();

	std::cout << timeClose << std::endl;

	for (uint32_t i = 0; i < tableNumber; i++)
	{
		std::cout << (i + 1) << " " << tableBase[i].numberTime * costHour << " " << tableBase[i].totalTime << std::endl;
	}
}

void ComputerClub::table::setCountTime(std::string _countTime)
{
	countTime = _countTime;
}

void ComputerClub::table::setEndTime(std::string endTime)
{
	ParserData tmp;

	totalTime = tmp.sumTime(tmp.subTime(endTime, countTime), totalTime);

	numberTime = tmp.countHour(totalTime);
}
