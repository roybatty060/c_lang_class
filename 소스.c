#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int last_index = 0;

int function(int num_list[], char cal_list[], int cal_index)
{
	int value;
	int c_index = 0;
	if (last_index != cal_index + 1)
		return -1;
	last_index--;
	while (c_index < cal_index)
	{
		switch (cal_list[c_index])
		{
		case '+':
			value = num_list[last_index - 1] + num_list[last_index];
			;
			break;
		case '-':
			value = num_list[last_index - 1] - num_list[last_index];
			break;
		case 'x':
			value = num_list[last_index - 1] * num_list[last_index];
			break;
		case '%':
			if (num_list[last_index] == 0)
				return -1;
			value = num_list[last_index - 1] / num_list[last_index];
			break;
		}
		num_list[--last_index] = value;
		c_index++;
	}
	last_index++;
	return 0;
}

int main(int arg, char *args[])
{
	int num_list[100];
	char cal_list[100];
	int i = 1;
	int num, cal_index;

	if (arg - 1 < 10)
	{
		printf("error");
		return 0;
	}
	while (1)
	{
		if (args[i][0] < '0' || args[i][0] == 'x')
		{
			cal_index = 0;
			while (i == arg || args[i][0] < '0' || args[i][0] == 'x')
			{
				if (i == arg)
				{
					num = function(num_list, cal_list, cal_index);
					if (num == -1)
					{
						printf("error");
						return 0;
					}
					printf("%d", num_list[0]);
					return 0;
				}
				cal_list[cal_index++] = args[i++][0];
			}
			num = function(num_list, cal_list, cal_index);
			if (num == -1)
			{
				printf("error");
				return 0;
			}
			continue;
		}
		num_list[last_index++] = args[i++][0] - '0';
	}
}