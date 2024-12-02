#pragma once
#include <chrono>
#include <ctime>
class timer {
private:
	int intial_time;
	int current_time;
	bool started=false;
public:
	void set_time();
	void update_time();
	int get_time();
	bool get_started();
};