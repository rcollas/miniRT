#include "miniRT.h"

double	get_timestamp(double start)
{
	double			timestamp;
	double			interval;

	timestamp = get_time();
	interval = timestamp - start;
	interval /= 1000;
	return (interval);
}

double	get_time(void)
{
	struct timeval	timestamp;
	double			time;

	if (gettimeofday(&timestamp, NULL) == -1)
		perror("gettimeofday:");
	time = timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000;
	return (time);
}

double	elapsed_time(double start, double end)
{
	double	interval;

	interval = end - start;
	return (interval);
}
