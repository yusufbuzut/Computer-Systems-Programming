#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int iter,row,col;
 int deadCell, bornCell;
// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
char **read_from_file(const char *filename)
{
	char** array = NULL;
	
	char line[99];
	
	
	FILE *file;
	file = fopen(filename, "r+");
	if(file==NULL){
		printf("There is no such a file");
		return(0);
	}
	
	int count,i;
	
	while(fgets(line,sizeof(line),file)!=NULL){
		if(count==0){
			iter=atoi(line);
		}
		if(count==1){
                        row=atoi(line);
			array = malloc(row*(sizeof(char*)));
                }if(count==2){
                        col=atoi(line);
                		
			for(i = 0; i<row; i++){
			array[i] = malloc(col*(sizeof(char*)));
		}}
		if(count>2){
			for(i=0;i<col;i++){
				array[count-3][i]= line[i];
			}
		}
		count++;
	}
	fclose(file);
	return array;
}
// given a game step return the next step applying game rules
int counter(char **state ,int r, int c){
	int i,j,count=0;
	for(i= r-1; i<=r+1;i++){
                for(j=c-1;j<=c+1;j++){
                        if((i==r && j==c)|| (i<0 || j<0) || (i>=row || j>=col)){
                                continue;
                        }
                        if(state[i][j]=='X'){
                               count++;
                        }
                }
        }
        return count;
}
char **next_state(char **state)
{	int i,j;
	char** array; 
	array  = malloc(row * (sizeof(char*)));
	for(i=0; i<row;i++){
		array[i] = malloc(col*(sizeof(char*)));
	}
	for(i=0; i<row;i++){
		for(j=0;j<col;j++){
			int count =0;
			array[i][j] = state[i][j];
				
			count = counter(state, i,j);
			if(count<2 && state[i][j]=='X'){
				array[i][j]='-';
				deadCell++;
			}
			if(count>3 && state[i][j]=='X'){
                                array[i][j]='-';
                                deadCell++;
                        }	
			if(state[i][j]='-' && count == 3){
				array[i][j]= 'X';
				bornCell++;
			}
		}
	}
	return array;

}

// bonus task
// return true if the given pattern is an oscillator
bool is_oscillator(char **pattern, int max_steps)
{

}

// print the game state
// after each step you can call this function, add some delay and then clear screen to create a simple game simulation in terminal
void print_state(char **state, int rows, int cols)
{

    int i, j;
    printf("\nNext State:\n");
    printf("%d\n",deadCell);
    printf("%d\n",bornCell);

    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%c", state[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) 
{	int i,j;
	char** temp;
	char** array = 	read_from_file(argv[1]);
	print_state(array,row,col);
	for(i=0;i<iter;i++){
		temp = array;
		array = next_state(array);
		print_state(array,row,col);
		for(j=0;j<row;j++){
			free(temp[j]);
		}
		free(temp);		
		sleep(10
);
	}
	for(i=0;i<row;i++){
		free(array[i]);
	}
	free(array);			   
    return 0;
}               
