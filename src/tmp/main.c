#include <stdio.h>
#include <time.h>
int main() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(stdout, "%d-%02d-%02dT%02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1,
		tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return 0;
}

//for / f % %i in('ztest') do set VARIABLE = % %i
//echo % VARIABLE %