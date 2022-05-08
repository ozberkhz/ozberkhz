#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int number;
	int digit;
	
	printf("Number: ");
	scanf("%d", &number);
	printf("Digit: ");
	scanf("%d", &digit);
	
	int number_copy = number;
	
	for (int i = 0; number_copy > 10; i++){
		if (number_copy % 10 == digit){
			printf("%d contains %d.", number, digit);
			return 0;
		}
		number_copy /= 10;	
	}
	
	if (number_copy % 10 == digit){
		printf("%d contains %d.", number, digit);
		return 0;
	}
	
	printf("%d does not contain %d.", number, digit);
	
	return 0;
}
