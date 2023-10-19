#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSNUM 4
#define MAXQULEN 200
#define MAXANLEN 100
#define MAXNMLEN 100
#define NUMQST 10

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

void print_menu();
void play();
void show_player_list();
void update_question_bank();

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

void play()
{   
    quiz *quiz_buffer; // buffer pointer for one quiz
    player *user_buffer; // buffer pointer for one user
    int qst_count, score; // variable for question count and score record

    // open quiz file
    FILE *quiz_lst = fopen("quiz.txt", "r");

    // check if opened correctly
    if (quiz_lst == NULL)
    {
        printf("Cannot open quiz file.\n");
    }

    // open result file
    FILE *result_lst = fopen("result.txt", "r");

    // check if opened correctly
    if (result_lst == NULL)
    {
        printf("Cannot open result file.\n");
    }

    // let the user enter their name
    printf("Please enter your name: ");
    scanf("%[^\n]s", user_buffer->name);

    // set random seed
    srand(time(NULL));

    // initialize question count to zero
    qst_count = 0;

    // loop while not reached maximum number or end of file
    while (fread(quiz_buffer, sizeof(quiz), 1, quiz_lst) && qst_count <= NUMQST)
    {   
        // create variable to record choice and randomization
        int choice, r;

        // randomize
        r = rand();
        if (r % 2 == 0)
        {
            // print question
            printf("Question %d. %s\n", qst_count + 1, quiz_buffer->question);

            // print possible answer
            for (int i = 0; i < ANSNUM; i++)
            {
                printf("%d. %s\n", i + 1, quiz_buffer->answer[i]);
            }

            // let user make their choice
            printf("Your choice (1, 2, 3, or 4): ");
            scanf("%d", &choice);

            // check correctness
            if (choice == quiz_buffer->correct_answer)
            {
                score ++;
            }

            // increase question count
            qst_count++;
        }
    }
}

void show_player_list()
{
    printf("Write your code here to implement the show_player_list() function.\n");
}

void update_question_bank()
{

}