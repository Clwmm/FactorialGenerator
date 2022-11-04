#include <stdio.h>
#define tab_max_size 7500

void factorial(short num);
void factorial_bad(short num);

int main()
{
	short number;
	printf("\nEnter a number [max 9000]: ");
	scanf("%d", &number);

	factorial(number);

	return 0;
};

void factorial(short num)
{
	if (num == 1 || num == 0)
	{
		printf("Factorial: 1");
		return;
	}

	int tab[tab_max_size];
	tab[0] = 1;
	for (int i = 1; i < tab_max_size; i++)
		tab[i] = 0;
	int tab_size = 1;

	for (int i = 0; i < num; i++)
	{

		for (int j = tab_size - 1; j >= 0; j--)
		{
			tab[j] *= (i + 1);

			if (tab[j] >= 100000)
			{
				int a = ((tab[j] % 1000000000) - (tab[j] % 100000));
				int b = a / 100000;
				tab[j] = tab[j] - a;
				tab[j + 1] += a / 100000;

				if (j == tab_size - 1)
				{
					tab_size++;
					if (tab_size > 6337)
					{
						printf("Out of range");
						return;
					}
				}
			}
		}
		if (tab_size > tab_max_size)
			break;
	}

	printf("\nFactorial of %d:\n", num);
	for (int i = tab_size - 1; i >= 0; i--)
	{
		if (tab[i] == 0)
			printf("00000");
		else
			printf("%d", tab[i]);
	}
	printf("\n\n");
}

// https://coolconversion.com/math/factorial/


/*
	int a = 432573829;

	"Jednosci: " -- a % 10                                             -- 9
	"Dziesiatki: " -- ((a % 100) - (a % 10)) / 10                      -- 2
	"Setki: " -- ((a % 1000) - (a % 100)) / 100                        -- 8
	"Tysiace: " -- ((a % 10000) - (a % 1000)) / 1000                   -- 3
	"10tys: " -- ((a % 100000) - (a % 10000)) / 10000                  -- 7
	"100tys(i więcej): " -- ((a % 1000000000) - (a % 100000)) / 100000 -- 4325

	int b = ((a % 1000000000) - (a % 100000)) / 100000;
	int c = a - ((a % 1000000000) - (a % 100000));
*/

/*
char 1B [−128; 127]

int co najmniej 2B [−32768; 32767]
	często 4B [−2147483648; 2147483647]

short int nie więcej niż int
	często 2B [−32768; 32767]

long int nie mniej niż int
	często 8 B [−9223372036854775808; 9223372036854775807]
*/


void factorial_bad(short num)
{
	if (num == 1 || num == 0)
	{
		printf("Factorial: 1");
		return;
	}

	int tab[tab_max_size];
	int tab_size = 0;

	int temp[tab_max_size];
	int temp_size = 0;
	temp[0] = 1;

	int inc[3];
	int inc_size = 0;

	tab[0] = 1;
	tab_size = 1;

	for (int i = 1; i <= num; i++)
	{
		if (i < 10)
		{
			inc[0] = i;
			inc_size = 1;
		}
		else if (i < 100)
		{
			inc[0] = i % 10;
			inc[1] = (i - (i % 10)) / 10;
			inc_size = 2;
		}
		else if (i < 1000)
		{
			inc[0] = i % 10;
			inc[2] = (i - (i % 100) / 100);
			inc[1] = ((i - (i % 10)) / 10) - (inc[2] * 10);
			inc_size = 3;
		}

		for (int k = 0; k < inc_size; k++)
		{
			for (int j = 0; j < tab_size; j++)
			{
				temp[j + k] = tab[j] * inc[k];
				temp_size++;
			}
		}
	}

	for (int i = 0; i < temp_size; i++)
	{
		if (temp[i] < 100)
		{
			temp[i + 1] += (temp[i] - (temp[i] % 10)) / 10;
			temp[i] = temp[i] % 10;
			if (i == temp_size)
				temp_size++;
		}
		else if (temp[i] < 1000)
		{
			temp[i + 1] += (temp[i] - (temp[i] % 10)) / 10;
			temp[i] = temp[i] % 10;
			if (i == temp_size)
				temp_size++;
		}
	}

	printf("Factorial: ");
	for (int i = 0; i < temp_size; i++)
		printf("%d", temp[i]);

	return;
}