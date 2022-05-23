#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <time.h>
#include "logger.h"

const int col = 6; // кол-во столбцов
const int row = 5; // кол-во строчек

int main() {
	std::ofstream file;
	Log logger;
	std::string name_file = "log.txt";
	file.open(name_file, std::ofstream::app); // открытие файла на дозапись
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	try {
		if (!file.is_open()) {
			throw std::exception("Файл не смог открыться"); // исключение, если не удалось открыть файл
		}
		// программа по нахождению минимальной суммы столбца 
		int mass[row][col], min = 300, sum = 0;
		
		std::cout << "Сгенерированная матрица:" << std::endl;

		logger.Trace(file, "Началась инициализация матрицы");

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mass[i][j] = rand() % 100;
				std::cout << mass[i][j] << " ";
			}
			std::cout << std::endl;
		}
		
		logger.Trace(file, "Проинициализирована матрица");

		logger.Trace(file, "Начался подсчет сумм");
		
		std::cout << "Суммы элементов столбцов:" << std::endl;
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				sum += mass[j][i];
			}
			std::cout << sum << " ";
			if (sum < min) { 
				min = sum; 
			}
			sum = 0;
		}

		logger.Trace(file, "Найдены суммы элементов каждого стобца");
		
		if (min == 300) {
			logger.Warning(file, "Размер переменной слишком мал"); // предупреждение, если переменная меньше всех сумм (программа будет работать не корректно)
		}

		std::cout << "\nМинимальная сумма из всех сумм столбцов: " << min << std::endl;
	}
	catch(std::exception& err) {
		std::ofstream file2;
		name_file = "log.txt";
		file2.open(name_file, std::ofstream::app);
		logger.Error(file2, err.what());
		file2.close();
	}
	logger.Trace(file, "Завершение работы программы");
	file.close();
	return 0;
}