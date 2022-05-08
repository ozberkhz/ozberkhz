#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char alphabet[20] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'Q'};

int rows, seats_per_row, aisles;
int aisle_locations[5];
int input = 0;
int number_of_reservations = 0;
int numberoftimes = 0;

void airplane_layout(int rows, int seats_per_row, int aisles, int number_of_reservations, char coordinates[][seats_per_row]) {
	
	int x = 0;
	
	// turning '+' to 'X'
	
	for (int i = 0; i < rows ; i++){
		for (int j = 0; j < seats_per_row; j++){
			if (coordinates[i][j] == '+'){
				coordinates[i][j] = 'X';
			}
		}
	}
	
	// assigning risk values
	
	double risk_values[rows][seats_per_row];
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < seats_per_row; j++){
			risk_values[i][j] = 0;
		}
	}
	
	for (int i = 0; i < rows; i++){
		
		for (int j = 0; j < seats_per_row; j++){
			
			if (coordinates[i][j] == 'X' || coordinates[i][j] == '+'){
				
				for (int a = 0; a < rows; a++){
					
					for (int b = 0; b < seats_per_row; b++){
						
						int aisles_in_between = 0;
						
						for (int c = 0; c < aisles; c++){
							if ((j >= aisle_locations[c] && b < aisle_locations[c]) || (j < aisle_locations[c] && b >= aisle_locations[c])){
								aisles_in_between += 1; // evaluating the effect of an aisle in between to the risk values
							}
						}
						
						if ((abs(i - a) + (abs(j - b) + aisles_in_between)/2.0) == 0){
							risk_values[a][b] += -100000;
						}
						
						if((abs(i - a) + (abs(j - b) + aisles_in_between)/2.0 != 0)) {
							risk_values[a][b] += 100 - pow(100, 1 / (abs(i - a) + (abs(j - b) + aisles_in_between)/2.0));
						}
					}
				}
			}
		}
	}
		
	// filling a singular seat
	
		if (input == 1) {
		
		// function to choose the right coordinates
				
		if (coordinates[0][0] != 'X' && coordinates[0][0] != '+'){
			coordinates[0][0] = '+';
		}
		
		double target = -1000000;
				
		for (int a = 0; a < rows; a++){
			for (int b = 0; b < seats_per_row; b++){
				if (risk_values[a][b] > target && coordinates[a][b] != '+' && coordinates[a][b] != 'X'){
					target = risk_values[a][b];
				}
			}
		}
				
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < seats_per_row; j++){
			if (target == risk_values[i][j] && coordinates[i][j] != '+' && coordinates[i][j] != 'X' && coordinates[0][0] != '+'){
				coordinates[i][j] = '+';
				j += seats_per_row;
				i += rows;
			}
		}
	}
}

		//filling multiple seats

		if (input > 1 && input <= seats_per_row) {

			double score[rows][seats_per_row];
			double target = -1000000;
			/*int aisles_in_between[rows][seats_per_row];
			int min_aisles_in_between = 5;*/
			
			//assigning default values to score array
			
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < seats_per_row; j++){
						score[i][j] = 0;
				}
			}
			
			//assigning the score values
			
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < seats_per_row; j++){
					for (int k = 0; k < input; k++){
						if (j + k <= seats_per_row){
							score[i][j] += risk_values[i][j + k];
						}						
					}
				}
			}
			
			//assigning the largest allowed score to target
			
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < seats_per_row; j++){
					
					int allow = 1;
					
					for (int k = 0; k < input; k++){
						if (j + k <= seats_per_row){
							if (coordinates[i][j + k] == '+' || coordinates[i][j + k] == 'X' || j + input > seats_per_row){
							allow = 0;
						}
					}	
				}
						if (score[i][j] > target && allow == 1){
						target = score[i][j];
						}
					}	
				}
			
			//determining the minimum number of aisles in between
				
			/*	for (int i = 0; i < rows; i++){
					for (int j = 0; j < seats_per_row; j++){
						
						aisles_in_between[i][j] = 0;
						
						for (int k = 0; k < aisles; k++){
							if (aisle_locations[k] >= j && aisle_locations[k] < j + input && j + input <= seats_per_row){
								aisles_in_between[i][j] += 1;
							}
						}
						
						if (target == score[i][j] && aisles_in_between[i][j] < min_aisles_in_between){
								min_aisles_in_between = aisles_in_between[i][j];
							//	printf("\nminimum is %d at %c%d\n", min_aisles_in_between, alphabet[j], i + 1);
							}
					}
				} */
				
			//signing the chosen coordinate values
				
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < seats_per_row; j++){
					
					int allow = 1;
					
					for (int k = 0; k < input; k++){					
						if (j + k <= seats_per_row){
							if (coordinates[i][j + k] == '+' || coordinates[i][j + k] == 'X'){
								allow = 0;
							}
						}
					}
				
				//	printf("aisles_in_between at %c%d = %d\n", alphabet[j], i + 1, aisles_in_between[i][j]);	
				//	printf("\nmin_aisles_in_between = %d\n\n", min_aisles_in_between);
					
					if (target == score[i][j] && allow == 1 /*&& aisles_in_between[i][j] == min_aisles_in_between */){
							for (int l = 0; l < input; l++) {
								coordinates[i][j + l] = '+';
							}
						j += seats_per_row;
						i += rows;
						}
				}
			}	
		}
			
			//determining the maximum input
			
			int max_input = 0;
			
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < seats_per_row; j++){
					
					int temporary_max_input = 0;
					
					if (coordinates[i][j] == '-'){
						
						for (int k = 0; j + k < seats_per_row; k++){
							
							if (coordinates[i][j + k] == '-'){
								temporary_max_input += 1;
							}
							
							if (coordinates[i][j + k] != '-'){
								if (temporary_max_input > max_input){
									max_input = temporary_max_input;
								}
								temporary_max_input = 0;
							}
							
							if (temporary_max_input > max_input){
								max_input = temporary_max_input;
							}
							
						}
					}
				}
			}
			
	//function to print reserved seats
	
	if (input > 0 && (number_of_reservations == rows * seats_per_row || input <= max_input)){
		printf("Reserved seats: ");
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < seats_per_row; j++){
					if (coordinates[i][j] == '+'){
						printf("%d%c ", i + 1, alphabet[j]); //function to print the coordinates
					}
				}
			}
		printf("\n");
	}
	
	printf("\n   ");
	
	for (int i = 0; i < seats_per_row; i++){
		
		printf("%c ", alphabet[i]);
		
		if (i + 1 == aisle_locations[x]) {
			
			printf("|  | ");
			x++;
		}
		
	}
	
	printf("\n");
	
	for (int i = 0; i < rows; i++){
		x = 0;
		if (i + 1 < 10){
			printf("%d  ", i + 1);
		}
		else {
			printf("%d ", i + 1);
		}
		for (int j = 0; j < seats_per_row; j++)	{
			printf("%c ", coordinates[i][j]);
			if (j + 1 == aisle_locations[x]) {
				printf("|  | ");
				x++;
			}
		}
		printf("\n");
	}
	
	
		printf("\nThe number of people in the reservation\n");
		printf("  (0: print current reservations, -1: exit): ");
		scanf("%d", &input);
	
	
	
	if ((number_of_reservations + input > rows * seats_per_row) || input > max_input ) {		
		for (int i = 0; i != 1;){
			printf("\nNo available seats for the requested reservation!\n\n");
			printf("The number of people in the reservation\n");
			printf("  (0: print current reservations, -1: exit): ");
			scanf("%d", &input);
			if (number_of_reservations + input <= rows * seats_per_row && input <= max_input ){
				i = 1;
			}
		}
	}
		

	if (input >= 0){
		number_of_reservations += input;
	}
	
	(input != -1) ? airplane_layout(rows, seats_per_row, aisles, number_of_reservations, coordinates) : NULL;
	
}

int main(){
	
	printf("Number of rows: ");
	scanf("%d", &rows);
	printf("Number of seats per row: ");
	scanf("%d", &seats_per_row);
	printf("Number of aisles: ");
	scanf("%d", &aisles);
	
	for (int i = 0; i < aisles; i++){
		printf("Add aisle %d after seat: ", i + 1);
		scanf("%d", &aisle_locations[i]);
	}
	
	char coordinates[rows][seats_per_row];
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < seats_per_row; j++){
			coordinates[i][j] = '-';
		}
	}
	
	airplane_layout(rows, seats_per_row, aisles, 0, coordinates); 
	
	return 0;
}
