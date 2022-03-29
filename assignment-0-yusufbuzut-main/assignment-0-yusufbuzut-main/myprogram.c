#include "mylibrary.h"

int sum(int n)
{
	int result = 0;

	//TODO: 1+2+...+n
	result = (n*(n+1))/2;
	return result;
}

int product_of_even_numbers(int *array, int count)
{
	int product = 1;
	for (int i=0;i<count;++i)
	{
		if(array[i]%2 ==0)
		{	
			//TODO: only multiply even numbers, e.g., 2. Skip odd numbers, e.g., 3
			product *= array[i];
		}
	
	}
	return product;
}

int max_of_numbers(int *array, int count)
{
	//TODO: return the maximum number from the array
	int max = array[0];
	for (int i =0;i<count;i++){
		if (array[i] > max){
			max = array[i];
		}
	}
	return max;
}

int reversed_number(int number)
{
	//TODO: if input is 12345, return 54321
	int reversed = 0;
	while(number > 0){
		reversed = reversed*10 + number%10;
	       	number /= 10;
	}
	return reversed;
}


char alphabet_index(int index)
{
	//TODO: for index 0, return A. index 1, B, etc. until 25 for Z.
	//if index is out of range, return space ' '.
	if(index+65 >90){
		return ' ';
	}
	char c = index+65;
	return c;
}


