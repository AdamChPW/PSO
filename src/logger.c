#include <stdio.h>
#include "logger.h"

void LogPosition(FILE *f, int i, int x, int y, double value)
{
	if (f != NULL) {
		fprintf(f, "CZĄSTKA %d: [%d]	[%d] : %.2lf\n", i, x + 1, y + 1, value);
	}
}
