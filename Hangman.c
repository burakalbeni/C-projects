#include <time.h> 
#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
void printer(int x);  // this is a function to print the hangman
void infogiver(int random_num); // this is a function to give information about the word to the player
#define SIZE 100 // max num of words in txt file
#define lenght 20 // max lenght of the answer 
int main()
{
	printf("HANGMAN GAME BY BURAK ALBENI\n");
	printf("   -----------------|         \n ");						
	printf("        )          | \n  ");
	printf("       *          |\n");
	printf("        /|\\         |\n");
	printf("         |          |\n");
	printf("         |          |\n");
	printf("        / \\         |\n");
	printf("                    |\n");
	printf("                    |\n");
	printf("                   -|-\n");
	printf("RULES:\n");
	printf("1)You can guess the word letter by letter each time you enter a wrong letter your life diminishes by 1 \n");
	printf("2)You can guess the entire word all at once but if your guess is wrong you get hanged immediately \n");
	printf("3)If you enter a used letter you get a penalty \n");
	printf("4)Answers are lowercase everyday words \n");
	printf("Please enter your name for the scoreboard\n");
	char player_name[30]; // name of the player 
	char guess[20];  // the word or the letter player is guessing
	char *pguess; // this is a pointer  we will use 
	pguess=guess; // lets set it as the guessed letter or word
	char *psecret_answer;	// pointer to the secret_answer character array
	fgets(player_name, sizeof(player_name),stdin);  // read string
	printf("Welcome! %s\n",player_name);	
	int round; // the round player is in 
	char used_letters[3000];// this will be the array where we will store the inputted letters
	int lifes;//the amount of lifes player has
	int score;//the score of the player
	top: //if player decides to play again label for top of the program 
			switch(lifes){
				case 8:
						score=score+500;
						printf("You are the legend of this game! You won 500 points this round!\n");		
						break;
				case 7:		
						score=score+400;
						printf("You must be a dictionary! You won 400 points this round!\n");		
						break;
				case 6:
						score=score+300;
						printf("That was superb! You won 300 points this round!\n");		
						break;
				case 5:	
						score=score+200;
						printf("You are doing great!You won 200 points this round!\n");		
						break;
				case 4:
						score=score+100;
						printf("Excellent!You won 100 points this round!\n");		
						break;
				case 3:	
						score=score+50;
						printf("You could do better!You won 50 points this round!\n");		
						break;
				case 2:
						score=score+25;		
						printf("You should focus!You won points 25 this round!\n");		
						break;
				case 1:		
						score=score+10;		
						printf("Where is your mind!You won only 10 points this round!\n");		
						break;
				case 0:
						printf("Look on the bright side you cant get any worse than this!\nYou won 0 points this round!\n");		
			}
		printf("----SCOREBOARD------\n");	
		printf("Score of %s%d\n",player_name,score);
	lifes=8; //lets set life to 8 
	if(!round==0){
		
		for (int i=0;i<3000;i++) { // for clearing the used_letters array if we dont do this, every time player decides to play again letters from the previous game will be encountered
			used_letters[i]=' ';	
		}
	}
	round = 0; // the round player is in 
	int pressed_button=0; // the value for player to decide to quit game or continue
	int penalty_counter=0; // this is a penalty counter if the player guesses an already guessed letter it is incremented by 1
	char answer[lenght]; //the answer player is trying to find
	char wordlist[SIZE][lenght];//our 2d array of strings which contains SIZE many words with lenght 'lenght'
	srand((unsigned int)time(NULL)); //random seed generator
	// this part is for importing words from a .txt file 
		FILE* fPointer; // this is a pointer to the first line in the txt file
	fPointer = fopen("words.txt", "r"); //this function opens the txt file and reads 
	int wordsreadin=0; // this is reading the words
	char input[20]; // temporary input for words
	if (fPointer == NULL) { // if we are unable to open the txt file or the txt file is corrupted we print error
		printf("Can't open or find the text file\n"); 
	}
	while (!feof(fPointer)) // while the end of the file is not there we take the lines in the txt file
	{
			fgets(input, 19, fPointer); // we insert the lines in the txt file to the wordlist array
			sscanf(input,"%s",wordlist[wordsreadin]);
	//		printf("Scanned: input:%s wordlist[%d]:%s\n",input,wordsreadin,wordlist[wordsreadin]); // this is for testing purposes
			wordsreadin++;
	}
	fclose(fPointer); // we close file 
		// now we can get a random word from the array of wordlist[]
	int random_num = rand() % 99; // this is a random number in the range of [0,99]
//	printf("The answer you are looking for is %s\n",wordlist[random_num]); // now we have the answer player is trying to find this is for cheating purposes
	strcpy(answer,wordlist[random_num]); // now we have the answer as we have previously defined
	// this part will give some information about the word to the player 
	infogiver(random_num);
		//now lets classify the answer only showing its lenght
	int answer_lenght=strlen(wordlist[random_num]); // this integer will be the lenght of the answer
	printf("The lenght of the word is %d \n",answer_lenght);
	char secret_answer[answer_lenght];// our secret answer will be the same lenght as our answer and will be made out of '?' characters
	for(int p=0;p<answer_lenght;p++)	{
		secret_answer[p]='?';  // we have classified our answer with question marks
	}
		// now we can start implementing the actual guessing and gameplay part
	psecret_answer=secret_answer;	// lets set our secret_answer array pointer as the secret_answer
	int occurence=0; // this is the occurence number of the inputted letter in the answer 

			printf("You have 8 lifes until you lose the game and get hanged\n");
			printf("Please enter a letter or a word to guess the answer : ");
				for(int p=0;p<answer_lenght;p++)	
					{
						printf("%c",psecret_answer[p]); // we print the secret answer where all of its characters are '?'
						printf(" ");
					}
						printf("\n");	
					wrong_letter: // label for wrong letter
					scanf("%s",&guess);
						if (!(guess[0]>='a' && guess[0]<='z')) {
									printf("Please enter a lowercase letter or a word!\n");
									goto wrong_letter;
							}
				iteration: // the label for the iteration to take place
				used_letters[round]=guess[0]; // since iteration starts from this line we feed the used letters at the end of every round here
				//now lets write a code to compare if the entered letter is in the answer or not
			for (int i = 0; i < answer_lenght; i++)	// this for loop will run until the lenght of the answer is covered
			{	
				if (answer[i]==pguess[0])  // this is for checking if the ith index of the answer equals to the guessed letter we use pguess here because we can't compare a pointer with a character 
				{ 									
						occurence++;				// This is the most crucial part of the code where the inputted letter is checked for 
					psecret_answer[i]=answer[i];	//whether it is included in the answer or not and then the ith index or indexes of the psecret_answer is altered as the guessed letter							}
				}									//  and we increase the counter of how many correct letters guessed at once									
			}
					
		if (strlen(guess) > 1)  //this is  for the case where if the player decides to guess the whole word at once 
		{
				if (strcmp(guess,answer)==0) // if he finds the answer the game ends immediately
				{
					printf("You have guessed correctly\n");
					printf ("Letters used:");
						for(int i=0;i<=round;i++)
						{	
							printf("%c,",used_letters[i]); // we show the used letters to the player
						}
					printf("\n");
					printf("answer:%s\n",answer);
					printf("Lifes remaining: %d \n",lifes);
					printer(lifes);
					printf("Thats the right word!\n");
					printf("You have beaten the game congratulations no one gets hanged today!\n");
				 	printf("Press 2 to see your score and to play again\n");
				 	printf("Press 1 to quit game\n");
					 scanf("%d", &pressed_button);
					if (pressed_button == 2)
					{
						int main();
						goto top;
					}
						else{
							
							printf("----SCOREBOARD------\n");	
							printf("Score of %s%d\n",player_name,score);
							return 0;
			  			}
				}
				else // if he guesses wrong the game also ends immediately
				{
					lifes = 0;
					printer(lifes);
					printf("You have guessed the wrong word and have been hanged by the neck until you die\n");
					printf("Unfortunately %s was not the correct answer :( \nThe correct answer was %s\n",guess,answer);
					printf("Press 2 to see your score and to play again\n");
					printf("Press 1 to quit game\n");
					scanf("%d", &pressed_button);
						if (pressed_button == 2)
					{
	
						
						goto top;
					}
						else{
							printf("----SCOREBOARD------\n");	
							printf("Score of %s%d\n",player_name,score);

							return 0;
			  			}
				}		
		}
			// now if player decides to guess letter we check for whether it is correct or not
				if (occurence > 0) // if the occurence of the inputted letter is bigger than zero that means player guessed correctly 
				{
					if(occurence>=2)
						printf("Congratulations you have guessed %d letters correctly at once!\n",occurence); // for cheering the player when he guesses multiple letters
					else
						printf("You have guessed correctly\n");
					printf ("Letters used:");
						for(int i=0;i<=round;i++)
						{	
							printf("%c,",used_letters[i]); // we show the used letters to the player
						}
					printf("\n");
					printf("Answer: ");
						for(int p=0;p<answer_lenght;p++)	
						{
							printf("%c",psecret_answer[p]); // we reveal the correct letters to the player
							printf(" ");
						}
						printf("\n");
						printf("Lifes remaining: %d \n",lifes);
						printer(lifes);
						occurence=0; // we set the occurence to zero here because if we dont do that the cheering message will be distorted
				}
				
			else	// this is the case where the guessed letter is not in the answer
			{
				printf("You have guessed wrong \n");
					if(lifes==0) // In the endgame if the player guesses wrong and he guesses a used_letter his life decrements twice so in order to prevent that we increase it
						lifes=lifes +1;	
				lifes--;
				printf ("Letters used:");
					for(int i=0;i<=round;i++)
					{
						printf("%c,",used_letters[i]); // we show the used letters to the player
					}
					printf("\n");
					printf("Answer: ");
					for(int p=0;p<answer_lenght;p++)	
					{
						printf("%c",psecret_answer[p]); // we reveal the correct letters to the player
						printf(" ");
						
					}
						printf("\n");
						printf("Lifes remaining: %d \n",lifes); // printing the remaining lifes
						printer(lifes);
			}
		// The core of our program is now finished now we just have to iterate the program until either player runs out of lifes or he finds the answer
			
					if (lifes > 0) // if player is not hanged we check if the answer is found or not
				{
						// now lets check if the player found the answer by guessing letters one by one
					int counter=0;  // this will count the same letters between the answer and psecret_answer
					for (int i=0;i<answer_lenght;i++)
					{
							if (psecret_answer[i]==answer[i])
								counter++; // counter is incremented every time there is a similar letter
					}
								if(counter==answer_lenght) // if counter is incremented as many times as the lenght of the answer that means the player found the answer by guessing letters
							{

								printf("Thats the right word!\n");
								printf("You have beaten the game congratulations no one gets hanged today!\n"); 
							}
							else 
							{
								round++;
								infogiver(random_num);
								printf("Please enter another letter or a word to guess the answer: ");
								wrong_letter2: // label for wrong letter
								scanf("%s",&guess);
								if (!(guess[0]>='a' && guess[0]<='z')) {
									printf("Please enter a lowercase letter or a word!\n");
									goto wrong_letter2;
										
								}	
									
								if (strlen(guess)==1){ // if the player enters a used letter we give him a penalty and we only check for characters
									for (int i=0;i<=round;i++){ // this for loop runs as many times as lenght of the  used_letters which equals to round number
										if (guess[0]==used_letters[i]){ // if the loop encounters an already enterd letter 
											penalty_counter++; // it increases the penalty counter
											if(penalty_counter>=1){ // and if the penalty counter is greater than 1 we give penalty
												printf("PENALTY! You have entered '%c' that is a used letter your life is decremented from %d to ",guess[0],lifes); 
												lifes--;
												printf("%d now \n",lifes);
												break; // If we dont use break lets say used letters are 'abcdaaaf' when player enters 'a' his life decrements 4 times 
											}
										}
									}	
								}		
							
							
								goto iteration;
							}
					printf("Press 2 to see your score and to play again\n");
					printf("Press 1 to quit game\n");	
					scanf("%d",&pressed_button);
					if (pressed_button == 2){
							goto top;
					}
						else{
							printf("----SCOREBOARD------\n");	
							printf("Score of %s%d\n",player_name,score);
							return 0;
			  			}
			  }
		else
		{
			printf("You have lost all of your lifes and have been hanged by the neck until you die.\nThe correct answer was %s \n",answer);
			printf("Press 2 to see your score and to play again\n");
			printf("Press 1 to quit game\n");
			scanf("%d",&pressed_button);
			if (pressed_button == 2) 
			{
				goto top;
			}
				else{
					printf("----SCOREBOARD------\n");	
					printf("Score of %s%d\n",player_name,score);
					return 0;
			  	}
		}
		
	return 0;
	
}

void	printer(int x) 
{
	switch (x) {
	case 8:
		printf("    ----------------|         \n ");
		printf("                   | \n  ");
		printf("                  |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 7:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("                  |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 6:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 5:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("         |          |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 4:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("        /|          |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 3:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("        /|\\         |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 2:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("        /|\\         |\n");
		printf("         |          |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 1:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("        /|\\         |\n");
		printf("         |          |\n");
		printf("        /           |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	case 0:
		printf("    ----------------|         \n ");
		printf("        )          | \n  ");
		printf("       *          |\n");
		printf("        /|\\         |\n");
		printf("         |          |\n");
		printf("         |          |\n");
		printf("        / \\         |\n");
		printf("                    |\n");
		printf("                    |\n");
		printf("                   -|-\n");
		break;
	}
	return;
}

void infogiver( int random_num)
{
		
		if (random_num >= 0 && random_num < 10)
		printf("The answer you are looking for is a fruit \n");
	if (random_num > 9 && random_num < 20)
		printf("The answer you are looking for is a vegetable \n");
	if (random_num > 19 && random_num < 40)
		printf("The answer you are looking for is a country \n");
	if (random_num > 39 && random_num < 50)
		printf("The answer you are looking for is a video game \n");
	if (random_num > 49 && random_num < 70)
		printf("The answer you are looking for is an animal \n");
	if (random_num > 69 && random_num < 80)
		printf("The answer you are looking for is a colour \n");
	if (random_num > 79 && random_num < 100)
		printf("The answer you are looking for is an occupation \n");
	
	return;
}



