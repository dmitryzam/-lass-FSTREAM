#include <iostream>
#include<fstream>
#include<string>

// Урок 61. Класс fstream

// Прототип Функции Задачи 1:
bool file_insert(std::string path, int pos, std::string str);

int main() {
	setlocale(LC_ALL, "RU");
	int n;
	const std::string path = "file.txt";	// константная строка, хранящаяся в файле

	// rkfcc fstream для чтения и записи в файл:
	
	std::fstream fs;
	// Открытие файла в нескольких режимах с помощью перегрузки операции битового ИЛИ:
	fs.open(path, std::ios::in | std::ios::app);	// "|" - это битовое ИЛИ.

	if (fs.is_open()) {
		std::cout << "Файл открыт.\n";

		// Ввод данных в файл:
		std::cout << "Введите строку -> ";
		std::string str;
		std::getline(std::cin, str);
		fs << str << '\n';

		// Перемещение курсора по файлу:
		// seekg - seek get pointer (перевод - переместить курсор считывания)
		// seekp - seek put pointer (перевод - переместить курсор записи)
		// beg - begin, cur - current (текущий), end.
		fs.seekg(0, std::ios::beg);		// перемещение курсора считывания в начало файла

		// Чтение данных из файла
		std::cout << "Содержимое файла:\n";
		char sym;
		while (fs.get(sym))
			std::cout << sym;
		std::cout << std::endl;

		// вывод текущей позиции курсора: 
		// fs.tellg или fs.tellp
	}
	else {
		std::cout << "Ошибка открытия файла!\n";
	}

	fs.close();
	
	// Задание 1. "Вставка с середину файла":
	
	if (file_insert(path, 3, "###"))
		std::cout << "Строка вставлена успешно.\n\n";
	else
		std::cout << "Ошибка выполнения функции!\n\n";
	
	// Задача 2. Парсинг 
	std::cout << "Задача 2.\nДата: ";
	std::ifstream in;
	in.open("date.txt");

	if (in.is_open()) {
		std::string date;
		in >> date;
		std::cout << date << std::endl;

		int day = std::stoi(date);	// получаем (извлекаем) из даты переменную day с помощью ф-ции stoi
		int month = std::stoi(date.substr(date.find('.') + 1));
		int year = std::stoi(date.substr(date.rfind('.') + 1));

		std::cout << "День: " << day << std::endl;
		std::cout << "Месяц: " << month << std::endl;
		std::cout << "Год: " << year << std::endl;
	}

	in.close();

	return 0;
}
// Функция Задачи 1:

bool file_insert(std::string path, int pos, std::string str) {
	// app - append - добавить в конец - не подойдет в данной задаче.
	static std::fstream fs;
	fs.open(path, std::ios::in);

	if (!fs.is_open())
		return false;

	std::string file;		// file - строка для содержимого файла
	std::string line;		// line - строка для построчного считывания

	while (std::getline(fs, line))
		file += line + '\n';

	fs.close();

	file.insert(pos, line);

	// открываем файл для записи:
	fs.open(path, std::ios::out);	// удаляем содержимое файла
	if (!fs.is_open())				// проверяем открыт ли файл
		return false;

	fs << file;						// и потом вставляем в стертый файл значение строки file
	fs.close();
	return true;
}