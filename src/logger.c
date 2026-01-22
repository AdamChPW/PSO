#include "logger.h"
#include <stdio.h>

void LogPosition(int i, int x, int y, double value)
{
	FILE* out = fopen("csv.txt", "a");
	if (out != NULL) {
		fprintf(out, "CZĄSTKA %d: [%d]	[%d] : %lf\n", i, y, x, value);
		fclose(out);
	}
}
