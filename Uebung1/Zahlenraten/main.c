#include <stdio.h>
#include <stdlib.h>
#include "guessing.h"

static unsigned int counter = 0;
static unsigned int target;
#define TESTRUNS 100
static unsigned int results[TESTRUNS];
static const unsigned int seed = 42;

int evaluate(unsigned int guess)
{
	counter++;
	if (guess < target)
		return 1;
	if (guess > target)
		return -1;
	return 0;
}

unsigned int create_random_digit(int lower, int upper)
{
	return rand() % upper + lower;
}

unsigned int create_random_code()
{
	unsigned int code = create_random_digit(0, 9) * 10000;
	code += create_random_digit(0, 9) * 1000;
	code += create_random_digit(0, 9) * 100;
	code += create_random_digit(0, 9) * 10;
	code += create_random_digit(0, 9);
	return code;
}

int main(void)
{
	srand(seed);

	for (unsigned int i = 0; i < TESTRUNS; i++)
	{
		counter = 0;
		target = create_random_code();
		const unsigned int result = guess_the_number();
		printf("Counter: %d\n", counter);
		if (result == target)
		{
			results[i] = counter;
		}
		else
		{
			results[i] = 99999;
		}
	}

	int sum = 0;
	for (unsigned int i = 0; i < TESTRUNS; i++)
	{
		sum += results[i];
	}

	printf("Average: %d\n", sum / TESTRUNS);
	return EXIT_SUCCESS;
}
