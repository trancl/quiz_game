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
// primary functions
void print_menu();
void play();
void show_player_list();
void update_question_bank();

// counting functions
int number_of_player(FILE *ptr);
int number_of_question(FILE *ptr);

// load file content functions
player *load_player_record(FILE *ptr, int player_count);
quiz *load_question_bank(FILE *ptr, int quiz_count);

// array shuffle
void array_shuffle(quiz *quiz_list);

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
            case 0:
                break;
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

        if (choice != 0)
        {
            printf("\nPress any key to return to the menu.");
            scanf("%*c");
        }
        
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

void play()
{   
    int quiz_count;
    quiz *quiz_list;

    FILE *inptr = fopen("quiz.txt", "r");

    if (inptr == NULL)
    {
        printf("Cannot open the quiz file");
    }

    quiz_count = number_of_question(inptr);
    load_question_bank(inptr, quiz_count);

    free(quiz_list);
    fclose(inptr);
}

void show_player_list()
{
    printf("Write your code here to implement the show_player_list() function.\n");
}

void update_question_bank()
{
    printf("Write your code here to implement the update_question_bank() function.\n");
}

int number_of_question(FILE *ptr)
{
    int quiz_count;

    fseek(ptr, 0, SEEK_END);
    quiz_count = ftell(ptr) / sizeof(quiz);
    fseek(ptr, 0, SEEK_SET);

    return quiz_count;
}

int number_of_player(FILE *ptr)
{
    int player_count;

    fseek(ptr, 0, SEEK_END);
    player_count = ftell(ptr) / sizeof(player);
    fseek(ptr, 0, SEEK_SET);

    return player_count;
}

quiz *load_question_bank(FILE *ptr, int quiz_count)
{
    quiz *quiz_list;

    // allocate memory
    quiz_list = (quiz *) calloc(quiz_count, sizeof(quiz));

    // read quiz from file to array
    fread(quiz_list, sizeof(quiz), quiz_count, ptr);

    return quiz_list;
}

player *load_player_record(FILE *ptr, int player_count)
{
    player *player_list;

    // allocate memory
    player_list = (player *) calloc(player_count, sizeof(player));

    // read quiz from file to array
    fread(player_list, sizeof(player), player_count, ptr);

    return player_list;
}

void array_shuffle(quiz *quiz_list)
{
    
}