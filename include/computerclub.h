#pragma once

// Фомичев Дмитрий

#include <string>
#include <unordered_map>
#include <queue>
#include <cstdint>

// Класс компьютерный клуб, обрабатывающий информацию из файла
class ComputerClub
{
	struct table
	{
		uint32_t numberTime = 0;// количество часов оплаты
		std::string totalTime = "00:00";// время, на которое был занят стол
		std::string countTime = "";// начало отсчета
		bool busy = false;// флаг занятости стола

		table() = default;

		void setCountTime(std::string);
		void setEndTime(std::string);
	};

private:
	std::string url;//путь к файлу

	uint32_t tableNumber;// количество столов
	std::string timeOpen;// время открытия компьютерного клуба
	std::string timeClose;// время закрытия компьютерного клуба
	uint32_t costHour;// стоимость часа
	uint32_t freeTable;// свободные столы

	std::queue<std::string> queueForTable;// очередь за стол, принимает имя клиента

	std::unordered_map<std::string, uint32_t> clientBase;// хэш-таблица для хранения информации о клиентах
	// в качестве ключа принимает имя клиента, в качестве значения - номер стола

	std::vector<table> tableBase; // вектор для хранения информации о выручке каждого стола

	std::string errors[5] = { "YouShallNotPass", "NotOpenYet", "PlaceIsBusy", "ClientUnknown", "ICanWaitNoLonger!" };
	enum typeError { YouShallNotPass, NotOpenYet, PlaceIsBusy, ClientUnknown, ICanWaitNoLonger };

	void closedClub();// выгнать клиентов

public:
	ComputerClub(std::string url);// конструктор, принимающий путь к файлу
	~ComputerClub() = default;

	void show();// обработка файла
};