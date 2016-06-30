#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void rules();
int shuffle(int[]);
int convert(int);
int play();
void pic(int);
void intro();


int main()
{
	char again;

	play();
	printf("\nPlay again? Input 'y' or 'n':\n");
	do{
		again = getchar();
	} while(again!='y' && again!='n');

	if(again=='y')
	{
		printf("\nOK, let's go again!\n\n");
		main();
	}

	return 0;
}

int play(void)
{
	int i;
        int x=0;
	int psum=0;
	int bsum=0;
	int pcards[5]={0};
	int bcards[5]={0};
	int cards[52];
	char go_on;
	char d;
        char choice;

	printf("Welcome to Blackjack!\n");
        intro();
        rules();
	printf("Press Enter to continue\n");
        do{
		go_on=getchar();
	} while (go_on!='\n');
	printf("\n");

	//shuffle cards
	shuffle(cards);

	//deal the cards
	pcards[0]=cards[0];
	pcards[1]=cards[1];
	bcards[0]=cards[2];
	bcards[1]=cards[3];

	//Player's 2 cards
	printf("Visible Computer's card:\n");
	pic(bcards[0]);
	printf("\n");
	printf("Your hand:\n");
	pic(pcards[0]);
	pic(pcards[1]);
	i=0;
	for (i=0;i<2;i++)
	{
		if (pcards[i]%100 == 1)
		{
			printf("Choose a value of the Ace %d, input 'y' for 11 or 'n' for 1 :\n", i+1);
			do{
				d = getchar();
			} while(d!='y' && d!='n');

			if(d=='y')
			{
				printf("The ace's value is: 11.\n");
				psum = psum + 11;
			}
			else if(d=='n')
			{
				printf("The ace's value is: 1.\n");
				psum = psum +1;
			}
		}
		else if(convert(pcards[i]) %100 ==10) psum = psum + 10;
		else psum = psum + pcards[i]%100;

		if(psum>21)
		{
			printf("Your total:%d\n\n",psum);
			printf("Computer win!\n");
			return 1;
		}
		else if(psum==21)
		{
			printf("Your total:%d\n\n",psum);
			printf("Player win!\n");
			return 0;
		}
	}
	printf("Your total:%d\n\n",psum);
	//Determine if player gets another card
	i=0;
	for(i=0;i<3;i++)
	{
		char j = 'n';

		printf("Hit or pass? Hit(h) Pass(p):\n");
		do{
			j = getchar();
		} while (j!='h' && j!='p');
		if (j=='h')
		{
			printf("You've got another card now.\n");
			pcards[i+2]=cards[i+4];
			printf("and your card %d is:\n", i+3);
			pic(pcards[i+2]);
			if (pcards[i+2]%100==1)
			{
				printf("Choose the value of the ace, type 'y' for 11 or 'n' for 1:\n", i+3);
				do{
					d=getchar();
				} while (d!='y' && d!='n');
				if (d=='y')
				{
					printf("You've chosen value 11 for the ace.\n");
					psum=psum+11;
				}
				else if(d=='n')
				{
					printf("You've chosen value 1 for the ace.\n");
					psum=psum+1;
				}
			}
			else if(convert(pcards[i+2])%100==10)psum=psum+10;
			else psum=psum+pcards[i+2]%100;

			if(psum>21)
			{
				printf("Sum of player's cards now:%d\n\n",psum);
				printf("Computer win!\n");
				return 1;
			}
			else if(psum==21)
			{
				printf("Sum of player's cards now:%d\n\n",psum);
				printf("Player win!\n");
				return 0;
			}
			else printf("Sum of player's cards now:%d\n\n",psum);
		}
		else
		{
			printf("Sum of player's cards now:%d\n\n",psum);
			break;
		}
	}
	if(i==3)
	{
		printf("Player win! Because the sum of your 5 cards isn't larger than 21!\n");
		return 0;
	}

	//The 2 cards of the computer
	printf("Computer's cards:\n");
	pic(bcards[0]);
	pic(bcards[1]);

	if(bcards[0]%100+bcards[1]%100==2)
	{
		bsum=12; //two A cards
		printf("Sum of computer's cards now:%d\n\n", bsum);
	}
	else if((convert(bcards[0]))%100+(convert(bcards[1]))%100==1)
	{
		bsum=21;
		printf("Sum of computer's cards now:%d\n\n", bsum);
		printf("Computer win!\n");
		return 1;
	}
	else if(bcards[0]%100==1 || bcards[1]%100==1)
	{
		bsum=(bcards[0]+bcards[1])%100+(rand()%2)*10;
		printf("Sum of computer's cards now:%d\n\n", bsum);
	}
	else
	{
		bsum = (convert(bcards[0]))%100 + (convert(bcards[1]))%100;
		printf("Sum of computer's cards now:%d\n\n", bsum);
	}

	//whether computer gets another cards until bsum>16
	for(i=0;i<3 && bsum<17;i++)
	{
		bcards[i+2]=cards[i+7];
		printf("Computer's card #%d is:\n", i+3);
		pic(bcards[i+2]);
		if (bcards[i+2]%100 == 1)
		{
			if (bsum+11 <= 21)
			{
				printf("Computer has chosen the ace to equal 11\n");
				bsum = bsum+11;
				printf("Sum of computer's cards now:%d\n\n", bsum);
			}
			else
			{
				printf("Computer has chosen the ace to equal 1\n");
				bsum = bsum+1;
				printf("Sum of computer's cards now:%d\n\n", bsum);
			}
		}
		else
		{
			bsum = bsum + convert(bcards[i+2])%100;
			printf("Sum of computer's cards now:%d\n\n", bsum);
		}
	}
	if (i==3)
	{
		printf("Computer win! Because the sum of it's 5 cards isn't larger than 21!\n");
		return 1;
	}

	//the last step
	if (bsum>21||psum>bsum)
	{
		printf("Player win!\n");
		return 0;
	}
	else if(psum==bsum)
	{
		printf("TIE!\n");
		return 3;
	}
	else if(psum<bsum)
	{
		printf("Computer win!\n");
		return 1;
	}
	return 3;
}

void intro(){
    printf(".----..-.     .--.  .---..-. .-.   .-.  .--.  .---..-. .-.\n");
    printf("| {}  } |    / {} \\/  ___} |/ / .-.| | / {} \\/  ___} |/ / \n");
    printf("| {}  } `--./  /\\  \\     } |\\ \\ | {} |/  /\\  \\     } |\\ \\ \n");
    printf("`----'`----'`-'  `-'`---'`-' `-'`----'`-'  `-'`---'`-' `-'\n");
}
void rules()
{
    printf("\nRules of Blackjack\n");
    printf("--Picture Cards (Jack, Queen and King) each count as 10 points.\n"
            "--An Ace counts as either 1 point or 11 points, "
            "whichever is best for the hand\n"
            "--All other cards have their numerical face value.\n"
            "--If a player reaches five cards without breaking 21, they win\n\n");
}

int shuffle(int cards[])
{
	int i,t;
	int deck[52];
	for (i=0;i<52;i++){
		deck[i]=(i/13+3)*100+i%13+1;
        }
	srand(time(NULL));
	for(i=0;i<52;i++){
		do{
			t=rand()%52;
		}while(deck[t]==0);
		cards[i]=deck[t];
		deck[t]=0;
	}
	return 0;
}

int convert(int a){
	if((a%100==11)||(a%100==12)||(a%100==13))return (a/100)*100+10;
	else return a;
}

void pic(int num){
	char fl;
	int po_num;

	fl=num/100;
	po_num=num%100;
	switch(po_num)
	{
		case 1:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   A *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*  %2d *\n", po_num);
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 11:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   J *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 12:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   Q *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 13:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   K *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}

	}
}
