#if !defined(TIMER_H)
#define TIMER_H

#include <time.h>

using namespace std;

class Tiempo
{
	private:
		timespec start;
		timespec end;
	public:
        void start_clock();
        void end_clock();
        timespec diff(); // return elapsed time in timespec format
        double seconds(); // return elapsed time as fractional seconds
};

#endif // TIMER_H

