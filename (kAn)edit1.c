#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define constant
#define ANSNUM 4        // number of answer per question
#define MAXQULEN 200    // max length of question
#define MAXANLEN 100    // max length of answer
#define MAXNMLEN 100    // max length of name
#define NUMQST 10       // number of question per player

// define data type for player and quiz
typedef struct player
{
    char name[MAXNMLEN];
    int score;
} player;

typedef struct quiz
{
    char question[MAXQULEN];
    char answer[ANSNUM][MAXANLEN];
    int correct_answer;
} quiz;

// declare function prototype
void print_menu();
void play();
void show_player_list();
void update_question_bank();
void load_question_bank();
void shuffle_question();

// start of the main function
int main(void)
{
    int choice;

    do
    {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d%*c", &choice);

        switch(choice)
        {
            case 1:
                play();
                break;
            case 2:
                show_player_list();
                break;
            case 3:
                update_question_bank();
                break;
            default:
                printf("Your choice is not available. Please choose 0, 1, 2, or 3.\n");
        }

        printf("\nPress any key to return to the menu.");
        scanf("%*c");
    }
    while(choice);

    return 0;
}

void print_menu()
{
    // system("clear"); // for macos, linux
    system("cls"); // for windows
    printf(" ================================== \n");
    printf("|             QUIZ GAME            |\n");
    printf("|             ---------            |\n");
    printf("| 1. Play game                     |\n");
    printf("| 2. Show the player lists         |\n");
    printf("| 3. Create / update question bank |\n");
    printf("| 0. Exit                          |\n");
    printf(" ================================== \n\n");
}

void shuffle_question(quiz *qNo, int n)
{
    srand(time(NULL));

    int i, numQLeft, j;
    quiz temp;

    numQLeft = n;                         // Set number of quizzes left to n

    for(i=0; i<n; i++)
    {
        j = i + rand()%numQLeft;
        temp = qNo[i];
        qNo[i] = qNo[j];
        qNo[j] = temp;
        numQLeft--;
    }
}

void play()
{
    player *pNo;                          //Pointer to 1 player(name and score)

    FILE *fp = fopen("result.txt","r");   //Open result file
    if(fp == NULL){                       //Validate file's existence
        printf("File not found");
        return 0;
    }

    printf("Please enter your name: ");  //Players enter their name
    scanf("%[^\n]", pNo->name);
    pNo->score = 0;                      //Set initial value for player's score

/*-----------------------------------------------*/

    quiz *qNo;                               //Pointer to quiz list
    int i, n;                                //n is total number of quizzes in the list

    qNo = (quiz*)malloc(n*sizeof(quiz));     //Pointer to array of quiz list

    shuffle_question(qNo, n);                //Call the shuffle function to change the order of quizzes

    i = 0;                                   //Current quiz = i + 1

    while(i<NUMQST)                          //Read 10 shuffled quizzes from the file (NUMQST = 10)
    {
        printf("%s", qNo[i]);                //Display one quiz at a time

        int pAns;
        printf("Enter your answer: ");       //Players enter their answer
        scanf("%d",&pAns);

        if(pAns == qNo->correct_answer)      //Validate player's answer
            pNo->score++;                    //+ 1 point if their answer is correct

        i++;                                 //Jump to next quiz
    }

    return 0;

}

void show_player_list()
{
    printf("Write your code here to implement the show_player_list() function.\n");
}

void update_question_bank()
{
    printf("Write your code here to implement the update_question_bank() function.\n");
}

void load_question_bank()
{
    printf("Write your code here to implement the load_question_bank() function.\n");
}
