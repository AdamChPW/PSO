#include "logger.h"
#include <stdio.h>

void LogPosition(int i, int x, int y)
{
	FILE* out = fopen("csv.txt", "a");
	if (out != NULL) {
		fprintf(out, "CZĄSTKA %d: [%lf]	[%lf]\n", i, x, y);
		fclose(out);
	}
}
