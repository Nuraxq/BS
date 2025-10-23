#include "guessing.h"

unsigned int guess_the_number(void)
{
	unsigned int upper = 100000;
	unsigned int lower = 10000;

	while(lower <= upper){
		unsigned int mid = (upper+lower) / 2;
		unsigned int guess = evaluate(mid);
		if(guess == 1){
			lower = mid+1;
		}
		else if(guess == -1){
			upper = mid-1;
		}
		else{
			return mid;
		}
	}
	return 1; // Return the correct number
}
