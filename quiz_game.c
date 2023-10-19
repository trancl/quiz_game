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
    system("clear"); // for macos, linux
    // system("cls"); // for windows
    printf(" ================================== \n");
    printf("|             QUIZ GAME            |\n");
    printf("|             ---------            |\n");
    printf("| 1. Play game                     |\n");
    printf("| 2. Show the player lists         |\n");
    printf("| 3. Create / update question bank |\n");
    printf("| 0. Exit                          |\n");
    printf(" ================================== \n\n");
}

void play()
{   
    printf("Write your code here to implement the play() function.\n");
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