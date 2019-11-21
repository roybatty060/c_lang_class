#include <stdio.h>

int last_index = 0, i = 1;

int function(int list[], int arg, char *args[])
{
	int value;
	while (i == arg || args[i][0] < '0' || args[i][0] == 'x')
	{
		if (i == arg)
			return 1;
		switch (args[i][0])
		{
		case '+':
			value = list[last_index - 1] + list[last_index];
			break;
		case '-':
			value = list[last_index - 1] - list[last_index];
			break;
		case 'x':
			value = list[last_index - 1] * list[last_index];
			break;
		case '%':
			if (list[last_index] == 0)
				return -1;
			value = list[last_index - 1] / list[last_index];
			break;
		}
		list[--last_index] = value;
		i++;
	}
	last_index++;
	return 0;
}

int main(int arg, char *args[])
{
	int list[100];
	int num;

	if (arg - 1 < 10)
	{
		printf("error");
		return 0;
	}
	while (1)
	{
		if (args[i][0] < '0' || args[i][0] == 'x')
		{
			last_index--;
			num = function(list, arg, args);
			if (num == -1)
			{
				printf("error");
				return 0;
			}
			else if (num == 1)
			{
				printf("%d", list[0]);
				return 0;
			}
			else
				continue;
		}
		list[last_index++] = args[i++][0] - '0';
	}
}