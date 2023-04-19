#include "philosophers.h"

/* This is an implementation of a custom usleep() 
function in C, which allows a program to sleep for a 
specified number of milliseconds. It is more precise 
than usleep().__uint64_t represents unsigned long long */
void	ft_usleep(int milisec)
{
	struct timeval	time_v;
	__uint64_t		start;
	__uint64_t		end;

	gettimeofday(&time_v, NULL);
	start = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	end = start + milisec;
	while (start < end)
	{
		gettimeofday(&time_v, NULL);
		start = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
		usleep(100);
	}
}
//1 milisegundo sao 1000 microsegundos