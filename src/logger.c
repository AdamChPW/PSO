#include <stdio.h>
#include "logger.h"

void LogPosition(FILE *f, int i, int x, int y, double value)
{
	if (f != NULL) {
		fprintf(f, "CZĄSTKA %d: [%d]	[%d] : %lf\n", i, x, y, value);
	}
}
