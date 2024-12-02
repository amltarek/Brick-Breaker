#include "timer.h"

void timer::set_time()
{
	intial_time = time(0);
	started = true;
}

void timer::update_time()
{
	current_time = time(0);
}
int timer::get_time() {
	return (current_time - intial_time);
}

bool timer::get_started()
{
	return started;
}
