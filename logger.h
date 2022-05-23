#pragma once
#pragma warning(disable : 4996)
void Time(std::ofstream& file);
void Output(std::ofstream& file, std::string msg, int log);

#include <fstream>
#include <chrono> // для подсчета миллисекунд
#include <time.h> 

class Log {
public:
	Log() {

	}

	enum type {
		ERR,
		WARN,
		INFO
	};

	void Trace(std::ofstream& file, std::string msg) {
		Output(file, msg, Log::type::INFO);
	}

	void Warning(std::ofstream& file, std::string msg) {
		Output(file, msg, Log::type::WARN);
	}

	void Error(std::ofstream& file, std::string msg) {
		Output(file, msg, Log::type::ERR);
	}
};

void Output(std::ofstream& file, std::string msg, int log) {
	Time(file);
	switch (log) {
		case Log::type::INFO :
			file << "\t|INFO|\t";
			break;
		case Log::type::WARN :
			file << "\t|WARN|\t";
			break;
		case Log::type::ERR :
			file << "\t|ERR|\t";
			break;
	}
	file << msg << "\n";
}

void Time(std::ofstream& file) { // функция по нахождению времени с точностью до миллисекунд
	auto now_time = std::chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(now_time);
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(now_time.time_since_epoch()) % 1000;

	char buffer[30];

	tm *timeinfo = localtime(&time);
	
	std::strftime(buffer, sizeof(buffer), "%F %T", timeinfo);
	file << buffer << ":" << millisec.count();
}
