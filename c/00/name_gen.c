#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *fn_firstname = "../../data/00_fi.data";
char *fn_familyname = "../../data/00_fa.data";

int count_lines(FILE * f);
void cat_nth_line(FILE * f, char *dest, int num, int max_size);
int rand_lim(int limit);

int main()
{
	FILE *f_fi, *f_fa;
	int nl_fi, nl_fa;
	int length;

	char name[80];

	f_fi = fopen(fn_firstname, "r");
	f_fa = fopen(fn_familyname, "r");

	nl_fi = count_lines(f_fi);
	nl_fa = count_lines(f_fa);

	name[0] = 0;

	srand(time(NULL) - getpid());

	cat_nth_line(f_fi, name, rand_lim(nl_fi - 1), 39);
	strcat(name, " ");
	cat_nth_line(f_fa, name, rand_lim(nl_fa - 1), 39);

	fclose(f_fi);
	fclose(f_fa);

	printf("Generated name is « %s ».\n", name);
}

int count_lines(FILE * f)
{
	int ch, lines = 0;

	fseek(f, 0, SEEK_SET);
	while (EOF != (ch = fgetc(f)))
		if (ch == '\n')
			++lines;

	return lines;
}

void cat_nth_line(FILE * f, char *dest, int num, int max_size)
{
	int ch, line = 0, len = strlen(dest), l = len;

	fseek(f, 0, SEEK_SET);
	if (num > line)
		while (EOF != (ch = fgetc(f)))
			if (ch == '\n' && ++line == num)
				break;

	if (num == line)
		while (l-len < max_size && EOF != (ch = fgetc(f)) && ch != '\n')
			dest[l++] = ch;

	dest[l] = 0;
}

int rand_lim(int limit)
{
	int divisor = RAND_MAX / (limit + 1);
	int retval;

	do {
		retval = rand() / divisor;
	} while (retval > limit);

	return retval;
}
