#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <time.h>
#include "logger.h"

const int col = 6; // ���-�� ��������
const int row = 5; // ���-�� �������

int main() {
	std::ofstream file;
	Log logger;
	std::string name_file = "log.txt";
	file.open(name_file, std::ofstream::app); // �������� ����� �� ��������
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	try {
		if (!file.is_open()) {
			throw std::exception("���� �� ���� ���������"); // ����������, ���� �� ������� ������� ����
		}
		// ��������� �� ���������� ����������� ����� ������� 
		int mass[row][col], min = 300, sum = 0;
		
		std::cout << "��������������� �������:" << std::endl;

		logger.Trace(file, "�������� ������������� �������");

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mass[i][j] = rand() % 100;
				std::cout << mass[i][j] << " ";
			}
			std::cout << std::endl;
		}
		
		logger.Trace(file, "������������������� �������");

		logger.Trace(file, "������� ������� ����");
		
		std::cout << "����� ��������� ��������:" << std::endl;
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

		logger.Trace(file, "������� ����� ��������� ������� ������");
		
		if (min == 300) {
			logger.Warning(file, "������ ���������� ������� ���"); // ��������������, ���� ���������� ������ ���� ���� (��������� ����� �������� �� ���������)
		}

		std::cout << "\n����������� ����� �� ���� ���� ��������: " << min << std::endl;
	}
	catch(std::exception& err) {
		std::ofstream file2;
		name_file = "log.txt";
		file2.open(name_file, std::ofstream::app);
		logger.Error(file2, err.what());
		file2.close();
	}
	logger.Trace(file, "���������� ������ ���������");
	file.close();
	return 0;
}