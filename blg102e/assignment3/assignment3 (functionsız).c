#include <stdio.h>
#include <stdlib.h>

struct candidate {
	char letter;
	int votes;
	float percent;
};

int districts = 1;
int there_is_winner = 0;
char winner = 'A';
char runner_up;

int main(int argc, char* argv[]){
	
	struct candidate first = {'A', 0, 0};
	struct candidate second = {'B', 0, 0};
	struct candidate third = {'C', 0, 0};
	struct candidate fourth = {'D', 0, 0};
	
	struct candidate candidates[4] = {first, second, third, fourth};
	
	int c;
	
	FILE *filep = fopen(argv[1], "r");
	
	if (filep == NULL){
		printf("No file found\n");
		return 0;
	}
	
	while (!feof(filep)){
		c = fgetc(filep);
		if (c == '\n'){
			districts += 1;
		}
	}
	
	rewind(filep);
	
	c = 0;
	
	int* vote_counter = (int*)malloc(4*districts*sizeof(int));
	
	for (int i = 0; i < 4*districts; i++){
			vote_counter[i] = 0;
			fscanf(filep, "%d ", &vote_counter[i]);
		//	printf("%d\n", vote_counter[i]);
			candidates[i % 4].votes += vote_counter[i];
	}
	
	free(vote_counter);
	
	for (int i = 0; i < 4; i++){
		candidates[i].percent = (double)candidates[i].votes * 100 / (candidates[0].votes + candidates[1].votes + candidates[2].votes + candidates[3].votes);
	//	printf("%c has %%%lf of votes\n", candidates[i].letter, candidates[i].percent);
	//	printf("%c has %d votes btw\n", candidates[i].letter, candidates[i].votes);
	}	
		
	//printf("There are %d districts\n", districts);
	
	for (int i = 0; i < 4; i++){
		if (candidates[i].percent > 50){
			printf("Winner: %c\n", candidates[i].letter);
			there_is_winner = 1;
			break;
		}
	}
	
	if (there_is_winner == 0){
		
		int bubblesort[4] = {candidates[0].votes, candidates[1].votes, candidates[2].votes, candidates[3].votes};
		int temp = 0;
		
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3 - i; j++){
				if (bubblesort[j + 1] > bubblesort[j]){
					temp = bubblesort[j];
					bubblesort[j] = bubblesort[j + 1];
					bubblesort[j + 1] = temp;
				}
			}
		}
		
		for (int i = 0; i < 4; i++){
			if (bubblesort[0] == candidates[i].votes){
				winner = candidates[i].letter;
			}
			if (bubblesort[1] == candidates[i].votes){
				runner_up = candidates[i].letter;
			}
		}
		
		printf("Second round: %c and %c\n", winner, runner_up);
		
	}
	
	fclose(filep);
	
	return 0;
	
}
