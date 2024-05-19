#pragma once

#include <string>
#include <cstdint>

// класс для обработки входящего файла
class ParserData
{
private:
	std::string url;// путь к файлу
	std::string prevTime = " ";// предыдущее время для отслеживания последовательности событий
	uint32_t tableNumber = 0;// количество столов для проверки номера стола

	bool parserNumber(std::string);// обработка числа
	bool parserTime(std::string);// обработка времени

	bool parserWorkTime(std::string);// обработка 2 строки входящего файла
	bool parserData(std::string);// обработка последующих строк

public:
	ParserData() = default;
	ParserData(std::string);
	~ParserData() = default;

	std::string sumTime(std::string next, std::string prev);// сложение времени
	std::string subTime(std::string next, std::string prev);// вычитание времени из next prev
	uint32_t countHour(std::string time);// возвращает количество часов, округленное в большую сторону

	bool checkFormat();// проверка входных данных на корректность
};