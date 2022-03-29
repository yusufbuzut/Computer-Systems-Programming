#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/************  COMP201 ASSIGNMENT 2  ************/

//Yusuf Büzüt


int main(int argc, char *argv[])
{

    if (strcmp(argv[1], "calculate-tf") == 0) //frequencyAnalysis
    {
        //TODO:Task 1
        FILE *file = fopen("SMSSpamCollection.txt","r+");
	if (file == NULL){/* We check whether there is a file.*/
		printf("There is no such file.");
		exit(1);
	}
	char keyWord[strlen(argv[2])+1];
	strcpy(keyWord, argv[2]);
	
	char line[999]; /* array of chars where the string read is copied */
	 
	int lineCount =0;
	int i;
	int isHam = 0;
	int isSpam = 0;
	int hamLine;
	int spamLine;
	int hamCount=0;
	int spamCount;
	while(!feof(file)){
		if(fgets(line, 999, file) != NULL){
			lineCount++;	
			char word[99]; /* we keep every word in this array of chars and check whether it is same with our arg*/
			int j; /* index of every letter in word.*/
			int isHam = 0;
        		int isSpam = 0;
			for(i=0; i<4 ; i++){
				word[i] = line[i];
			}
			word[3] = '\0';
			/* We will check whether the line is spam or ham.*/
			if(strcasecmp(word,"ham")==0){
				hamLine++;
				isHam =1;
			}
			else if(strcasecmp(word,"spa")==0){
				isSpam =1;
			}
			/* After understand that line starts with ham or spam we go over other words in the line.*/
			for(i=4; i < strlen(line); i++){
				if(isalpha(line[i])){/* We try to seperate each word with checking nonalpha characters.*/
					word[j] = line[i];
					j++;
				}
				else{
					word[j] = '\0'; /* we add this char to mark end of the word */
					 j = 0; /* we pass to the next word so we reset the index */
					if (strcasecmp(word,keyWord) == 0){
						if (isSpam == 1){
							spamCount++;
						}

						if(isHam ==1){
							hamCount++; 	
						}
					}
				 
				}
				
		}
		
	}
	}
	fclose(file);
	if(hamCount==0 || spamCount == 0){
		printf("This word doesn’t occur in the text!");
	}
	else{
		printf("Total Ham: %d\n", hamLine);
		printf("Word in Ham: %d\n", hamCount);
		printf("Calculated tf value for this word: %f\n", (double)((double)hamCount/(double)hamLine));
		printf("Total Spam: %d\n", lineCount-hamLine);
		printf("Word in Spam: %d\n", spamCount);
		printf("Calculated tf value for this word: %f\n", (double)((double)spamCount/(double)(lineCount- hamLine)));
		if (hamCount > spamCount){
			printf("This word is mostly used for non spam messages\n");
		}
		else printf("This word is mostly used for spam messages\n");
    	}
    }

    else if (strcmp(argv[1], "predict") == 0) //spamDetection
    {/*We use same structure as calculatetf. But this time we have a for loop that goes over all words seperately.*/
int i;
int totalOccur, totalHam,totalHamLine, totalSpam, totalSpamLine, hamLine, lineCount = 0;
 double tdidfHam , tdidfSpam =0;
for(i=2; i<7; i++)
        {
	int checkerCount =0;
        FILE *file = fopen("SMSSpamCollection.txt","r+");
        if (file == NULL){
                printf("There is no such file.");
                exit(1);
        }
        char keyWord[strlen(argv[i])+1];
        strcpy(keyWord, argv[i]);

        char line[999]; /* array of chars where the string read is copied */

        int lineCount =0;
        int i;
        int isHam, checker = 0;
        int isSpam = 0;
        int hamLine = 0;
        int spamLine =0;
        int hamCount=0;
        int spamCount=0;
        while(!feof(file)){
                 checker =0;

                if(fgets(line, 999, file) != NULL){
                        lineCount++;
                        char word[99]; /* we keep every word in this array of chars and check whether it is same with our arg*/
                        int j; /* index of every letter in word.*/
                        int isHam = 0;
                        int isSpam = 0;
                        for(i=0; i<4 ; i++){
                                word[i] = line[i];
                        }
                        word[3] = '\0';

                        if(strcasecmp(word,"ham")==0){
                                hamLine++;
                                isHam =1;
                        }
                        else if(strcasecmp(word,"spa")==0){
                                isSpam =1;
                        } for(i=4; i < strlen(line); i++){
                                if(isalpha(line[i])){
                                        word[j] = line[i];
                                        j++;
                                }
                                else{
                                        word[j] = '\0'; /* we add this char to mark end of the word */
                                         j = 0; /* we pass to the next word so we reset the index */
                                        if (strcasecmp(word,keyWord) == 0){
						 if(checker == 0){
                                                	checkerCount++; /* number of sentence that at least 1 word occur */
							checker =1;
                                        	}	
                                                
                                                if (isSpam == 1){
                                                        spamCount++;
                                                }

                                                if(isHam ==1){
                                                        hamCount++;
                                                }
                                        }
                                        
                                }
                        }
                }
        }
        fclose(file);

        if (totalOccur=0){
                printf("This word is not in the file");
        }
        else{
                double idf=0;
                if(checkerCount !=0){/* to avoid NaN situation that can cause because of logf*/
                        idf = (logf((double)(lineCount)/(double)(checkerCount)));/* calculating idf */
		}		
		tdidfHam += idf* (double)((double)(hamCount)/(double)(hamLine)); /* then we calculate each tdidf for ham and spam*/
                tdidfSpam += idf* (double)((double)spamCount/(double)(lineCount- hamLine));
        
	}

        }
	
        if ( tdidfSpam + tdidfHam !=0){
                printf("Total tf-idf score from non spam messages for the sentence: %f\n", tdidfHam);
                printf("Total tf-idf score from spam messages for the sentence: %f\n", tdidfSpam);
                if(tdidfHam >tdidfSpam){
                
	        printf("This sentence is not spam.");
		}
		else if(tdidfHam < tdidfSpam){
			printf("This sentence is spam.");
		}
		else printf("Values are same");
	}
	else printf("Idf values are zero.");
}






    else if (strcmp(argv[1], "predict-wo-stopwords") == 0) //stopWords
    {/* We only check whether arguments are stop words or not. So we only add a while loop that check this. If a word is stop word we add 0 to our tdidfham and tdidfspam 0*/
        //TODO:Task Extra

int i;
int totalOccur, totalHam,totalHamLine, totalSpam, totalSpamLine, hamLine, lineCount = 0;
 double tdidfHam , tdidfSpam =0;
for(i=2; i<7; i++)
        {
	int checkerCount =0;

        FILE *file = fopen("SMSSpamCollection.txt","r+");
        if (file == NULL){
                printf("There is no such file.");
                exit(1);
        }
        char keyWord[strlen(argv[i])+1];
        strcpy(keyWord, argv[i]);
	
	FILE *wordChecker =fopen("99webtools.txt","r+");
	int y;
        int continueCheck = 0;
        char line1[999];
        while(!feof(wordChecker)){
                if(fgets(line1, 999, wordChecker) != NULL){
                        char word1[99];
                        for(y=0; y< strlen(line1); y++){
                              if(isalpha(line1[y])){ 
				 word1[y] = line1[y];
					
				}
				word1[y+1]='\0';
                        }
		if (strcasecmp(word1,keyWord)==0){
                        	continueCheck = 1;
				printf("%s is a stop word, it is not used in tf-idf calculations.\n", word1); 
                          	break;   
                        }
                }
        }
	fclose(wordChecker);
	if(continueCheck ==1){
		tdidfHam +=0;
		tdidfSpam +=0;
		continue;

	}
        




        char line[999]; /* array of chars where the string read is copied */

        int lineCount =0;
        int i;
        int isHam, checker = 0;
        int isSpam = 0;
        int hamLine = 0;
        int spamLine =0;
        int hamCount=0;
        int spamCount=0;
        
	while(!feof(file)){
                 checker =0;

                if(fgets(line, 999, file) != NULL){
                        lineCount++;
                        char word[99]; /* we keep every word in this array of chars and check whether it is same with our arg*/
                        int j; /* index of every letter in word.*/
                        int isHam = 0;
                        int isSpam = 0;
                        for(i=0; i<4 ; i++){
                                word[i] = line[i];
                        }
                        word[3] = '\0';

                        if(strcasecmp(word,"ham")==0){
                                hamLine++;
                                isHam =1;
                        }
                        else if(strcasecmp(word,"spa")==0){
                                isSpam =1;
                        } for(i=4; i < strlen(line); i++){
                                if(isalpha(line[i])){
                                        word[j] = line[i];
                                        j++;
                                }
                                else{
                                        word[j] = '\0'; /* we add this char to mark end of the word */
                                         j = 0; /* we pass to the next word so we reset the index */
                                        if (strcasecmp(word,keyWord) == 0){
						 if(checker == 0){
                                                	checkerCount++; /* number of sentence that at least 1 word occur */
							checker =1;
                                        	}	
                                                
                                                if (isSpam == 1){
                                                        spamCount++;
                                                }

                                                if(isHam ==1){
                                                        hamCount++;
                                                }
                                        }
                                        
                                }
                        }
                }
        }
        fclose(file);

        if (totalOccur=0){
                printf("This word is not in the file");
        }
        else{
                double idf=0;
                if(checkerCount !=0){/* to avoid NaN situation that can cause because of logf*/
                        idf = (logf((double)(lineCount)/(double)(checkerCount)));/* calculating idf */
		}		
		tdidfHam += idf* (double)((double)(hamCount)/(double)(hamLine)); /* then we calculate each tdidf for ham and spam*/
                tdidfSpam += idf* (double)((double)spamCount/(double)(lineCount- hamLine));
        
	}

        }
        if ( (tdidfSpam + tdidfHam )!=0){
                printf("Total tf-idf score from non spam messages for the sentence: %f\n", tdidfHam);
                printf("Total tf-idf score from spam messages for the sentence: %f\n", tdidfSpam);
                if(tdidfHam > tdidfSpam){
                
	       		 printf("This sentence is not spam.");
		}
		else if(tdidfHam < tdidfSpam){
			printf("This sentence is spam.");
		}
		else printf("Values are same");
	}
	else printf("Tf-idf scores are found to be 0, spam detection failed!");
	
}
 
    else
    {
        printf("Wrong Function!\n");
    }

    return 0;
}
