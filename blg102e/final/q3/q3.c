#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 20

char *concat(char *s1, char *s2)
{
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    int size3 = size1 + size2 + 1 + 1; // one for space, one for \0
    if (size3 > MAX_LEN) {
        return NULL;
    }

    char *s3 = (char *) malloc(size3 * sizeof(char));
    strcpy(s3, s1);
    strcat(s3, " ");
    strcat(s3, s2);
    return s3;
}

int main(int argc, char **argv)
{
    // WRITE THIS FUNCTION
    
    
    
    if (argv[1] == NULL){
    	printf("incorrect usage");
    	return 1;
	}
	
	if (argv[2] == NULL){
    	printf("incorrect usage");
    	return 1;
	}
	
	if (argv[3] != NULL){
    	printf("incorrect usage");
    	return 1;
	}
    
    if (concat(argv[1], argv[2]) == NULL){
    	printf("limit exceeded");
    	return 1;
	}
	
	else {
		char* ptr = concat(argv[1], argv[2]);
		printf("%s", ptr);
		free(ptr);
		ptr = NULL;
		return 0;
	}
    
}
