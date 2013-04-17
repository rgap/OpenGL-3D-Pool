
#if !defined(TIMER_CPP)
#define TIMER_CPP

#include "Tiempo.h"

void Tiempo::start_clock(){
    clock_gettime(CLOCK_REALTIME, &start);
}

void Tiempo::end_clock(){
    clock_gettime(CLOCK_REALTIME, &end);
}

timespec Tiempo::diff(){
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

double Tiempo::seconds(){
	return (diff().tv_sec + diff().tv_nsec/1000000000.0);
}

#endif // TIMER_CPP

