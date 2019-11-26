#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} //
};
static int day[2] = { 365, 366 };
static char* days[7] = { "mon", "tue", "wed", "thu", "fri", "sat", "sun" };
int total = 0;
int pmonth, pday, plus_year = 0;

int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void month_day(int year, int month, int yearday, int* pmonth, int* pday)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = month; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int else_day(int year, int month, int day)
{
	int i, leap, sum = 0;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	sum += daytab[leap][month] - day;
	for (i = month + 1; i <= 12; i++)
		sum += daytab[leap][i];
	return sum;
}

int between(int year1, int month1, int day1, int year2, int month2, int day2)
{
	int leap1, leap2;
	int error1, error2;
	int i, sample_leap;
	leap1 = year1 % 4 == 0 && year1 % 100 != 0 || year1 % 400 == 0;
	leap2 = year2 % 4 == 0 && year2 % 100 != 0 || year2 % 400 == 0;

	error1 = year1 < 1 || year1 > 3000 || day1 < 1 || day1 > daytab[leap1][month1] || month1 < 1 || month1 > 12;
	error2 = year2 < 1 || year2 > 3000 || day2 < 1 || day2 > daytab[leap2][month2] || month2 < 1 || month2 > 12;
	if (error1 || error2)
		return -1;
	total += else_day(year1, month1, day1);
	for (i = year1 + 1; i < year2; i++)
	{
		sample_leap = i % 4 == 0 && i % 100 != 0 || i % 400 == 0;
		total += day[sample_leap];
	}
	total += day_of_year(year2, month2, day2);
	return 0;
}

void one_sample(int year, int month, int day)
{
	int num = between(1, 1, 1, year, month, day);
	if (num == -1) {
		printf("error");
		return 0;
	}
	else
		printf("%s", days[total % 7]);
}

void after(int year, int month, int day, int days)
{
	int left = days - else_day(year, month, day);
	if (left > 0) {
		month_day(year + 1, 1, left % 365, &pmonth, &pday);
		printf("%d.%d.%d", year + left / 365 + 1, pmonth, pday);
	}
	else {
		month_day(year, month, days, &pmonth, &pday);
		printf("%d.%d.%d", year, pmonth, pday + day);
	}

}

int main(int arg, char* args[])
{
	int leap1, year1, month1, day1;
	int leap2, year2, month2, day2;
	int error1, error2;
	int i, k1, k2, num;
	k1 = sscanf(args[1], "%d.%d.%d", &year1, &month1, &day1);
	if (k1 < 3)
	{
		printf("error");
		return 0;
	}
	if (arg == 2)
		one_sample(year1, month1, day1);
	else
	{
		k2 = sscanf(args[2], "%d.%d.%d", &year2, &month2, &day2);
		if (k2 == 1)
			after(year1, month1, day1, year2);
		else if (k2 == 3) {
			num = between(year1, month1, day1, year2, month2, day2);
			if (num == -1)
				printf("error");
			else
				printf("%d", total);
		}
		else
			printf("error");
	}
}