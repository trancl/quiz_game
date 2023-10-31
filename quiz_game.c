#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define constant
#define ANSNUM 4        // number of answer per question
#define MAXQULEN 200    // max length of question
#define MAXANLEN 100    // max length of answer
#define MAXNMLEN 30     // max length of name
#define QSTNUM 10       // number of question per player

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
    char correct_answer;
} quiz;

// declare function prototype
// main function
void print_menu();
void play();
void show_player_list();
void update_question_bank();

// loading function
int load_question_bank(quiz **quiz_list);
int load_player_record(player **player_list);

// sorting and shuffle
void sort_player(player *player_list, int player_count);
void shuffle_question(quiz *quiz_list, int quiz_count);

// question manipulation
void print_question(quiz qust, char option);
quiz get_question();
int add_question(quiz **quiz_list, int quiz_count);
int change_question(quiz **quiz_list, int quiz_count);


// start of the main function
int main ()
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
                break;
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

//-----------------------------main function------------------------------------

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
    quiz *q_list = NULL;
    int q_count;

    if (q_list == NULL)
    {
        q_count = load_question_bank(&q_list);

        if (q_list == NULL)
            return;
    }

    // create new player
    player p;
    p.score = 0;

    printf("Please enter your name: ");
    scanf("%[^\n]", p.name);
    while(getchar() != '\n');

    // shuffle and print question
    shuffle_question(q_list, q_count);

    // print question and get answer
    for (int i = 0; i < QSTNUM && i < q_count; i++)
    {
        system("clear");
        char p_choice;

        printf("%d. ", i + 1);
        print_question(q_list[i], 'n');

        printf("Enter your choice: ");
        scanf("%c", &p_choice);
        while(getchar() != '\n');

        while (p_choice < 'a' || p_choice > 'd')
        {
            printf("Please enter only a, b, c, or d!\n");
            printf("Enter your choice again: ");
            scanf("%c", &p_choice);
            while(getchar() != '\n');
        }

        if (p_choice == q_list[i].correct_answer)
        {
            p.score++;
        }
    }

    // open player record and move pointer to end of file
    FILE *player_record = fopen("player.txt", "a");

    // append the player information
    fprintf(player_record, "%s,", p.name);
    fprintf(player_record, "%d\n", p.score);

    // close the file
    fclose(player_record);

    // free the pointer
    free(q_list);
}

void show_player_list()
{
    system("clear");

    player *p_list = NULL;
    int p_count;

    if (p_list == NULL)
    {
        p_count = load_player_record(&p_list);
        if (p_list == NULL)
            return;
    }

    sort_player(p_list, p_count);

    printf("-------------------------------------\n");
    printf("|Name                         |Score|\n");
    printf("-------------------------------------\n");

    for (int i = 0; i < p_count; i++)
    {
        printf("|%-29s|%5d|\n", p_list[i].name, p_list[i].score);

    }

    printf("-------------------------------------\n");

    free(p_list);
}

void update_question_bank()
{
    system("clear");

    quiz *q_list = NULL;
    int q_count;

    if (q_list == NULL)
    {
        q_count = load_question_bank(&q_list);
    }

    int choice;

    do
    {   
        printf(" ================================== \n");
        printf("|          UPDATE QUESTION         |\n");
        printf("|             ---------            |\n");
        printf("| 1. Add question                  |\n");
        printf("| 2. Show the question bank        |\n");
        printf("| 0. Exit                          |\n");
        printf(" ================================== \n\n");

        printf("Enter your choice: ");
        scanf("%d%*c", &choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            q_count = add_question(&q_list, q_count);
            break;
        case 2:
            q_count = change_question(&q_list, q_count);
            break;
        default:
            printf("Your choice is not available. Please enter only 1, 2, or 0.");
            break;
        }

        if (choice != 0)
        {
            printf("\nPress any key to return to the previous menu.\n");
            scanf("%*c");
        }
    } while (choice);

    FILE *q_bank = fopen("quiz.txt", "w");

    for (int i = 0; i < q_count; i++)
    {
        fprintf(q_bank, "%s\n", q_list[i].question);

        for (int j = 0; j < ANSNUM; j++)
        {
            fprintf(q_bank, "%s\n", q_list[i].answer[j]);
        }

        fprintf(q_bank, "%c\n", q_list[i].correct_answer);
    }

    fclose(q_bank);

    free(q_list);
}

//------------------------------------------------------------------------------

//------------------------------loading function--------------------------------
int load_question_bank(quiz **quiz_list)
{
    int quiz_count = 0;

    // open file
    FILE *ptr = fopen("quiz.txt", "r");

    if (ptr == NULL)
    {
        printf("Cannot load question bank!\n");
        return 0;
    }

    // allocate the space for quiz_list
    quiz *tmp = (quiz *) calloc(quiz_count, sizeof(quiz));

    quiz buffer;

    // read into quiz_list
    while(fscanf(ptr, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n", buffer.question, buffer.answer[0], buffer.answer[1], buffer.answer[2], buffer.answer[3], &buffer.correct_answer) == 6)
    {
        quiz_count++;
        tmp = realloc(tmp, quiz_count * sizeof(quiz));
        tmp[quiz_count - 1] = buffer;
    }

    *quiz_list = tmp;

    // close file
    fclose(ptr);

    return quiz_count;
}

int load_player_record(player **player_list)
{
    int player_count = 0;

    // open file
    FILE *ptr = fopen("player.txt", "r");

    if (ptr == NULL)
    {
        printf("Cannot load player record!\n");
        return 0;
    }

    // allocate the space for player_list
    player *tmp = (player *) calloc(player_count, sizeof(player));

    player buffer;

    // read into player_list
    while(fscanf(ptr, "%[^,], %d\n", buffer.name, &buffer.score) == 2)
    {
        player_count++;
        tmp = realloc(tmp, player_count * sizeof(player));
        tmp[player_count - 1] = buffer;
    }

    *player_list = tmp;

    // close file
    fclose(ptr);

    return player_count;
}
//------------------------------------------------------------------------------

//-----------------------------sorting and shuffle------------------------------
void sort_player(player *player_list, int player_count)
{
    for (int i = 1; i < player_count; i++)
    {
        for (int j = i - 1; j >= 0 && player_list[j].score < player_list[j + 1].score; j--)
        {
            player tmp = player_list[j + 1];
            player_list[j + 1] = player_list[j];
            player_list[j] = tmp;
        }
    }
}

void shuffle_question(quiz *quiz_list, int quiz_count)
{
    srand(time(NULL));

    for (int i = 0, remain = quiz_count; i < quiz_count; i++)
    {
        int j;
        quiz tmp;

        j = i + rand() % remain;
        tmp = quiz_list[i];
        quiz_list[i] = quiz_list[j];
        quiz_list[j] = tmp;
        remain--;
    }
}
//------------------------------------------------------------------------------

//-------------------------question manipulation--------------------------------

void print_question(quiz qust, char option)
{
    printf("%s\n", qust.question);
    for (int i = 0; i < ANSNUM; i++)
    {
       printf("\t%c. %s\n", i + 'a', qust.answer[i]);
    }

    if (option == 'f')
    {
        printf("Correct answer: %c\n", qust.correct_answer);
    }

    return;
}

quiz get_question()
{
    quiz qust;

    printf("Enter your question: ");
    scanf("%[^\n]", qust.question);
    while(getchar() != '\n');

    for (int i = 0; i < ANSNUM; i++)
    {
        printf("Enter answer %c: ", i + 'a');
        scanf("%[^\n]", qust.answer[i]);
        while(getchar() != '\n');
    }

    printf("Enter correct answer: ");
    scanf("%c", &qust.correct_answer);
    while(getchar() != '\n');

    return qust;
}

int add_question(quiz **quiz_list, int quiz_count)
{
    quiz tmp_q;
    tmp_q = get_question();

    quiz_count++;

    quiz* tmp_address = *quiz_list;
    tmp_address = realloc(tmp_address, sizeof(quiz) * quiz_count);

    tmp_address[quiz_count - 1] = tmp_q;

    *quiz_list = tmp_address;

    return quiz_count;
}

int change_question(quiz **quiz_list, int quiz_count)
{
    quiz *tmp = *quiz_list;
    quiz buffer;

    for (int i = 0; i < quiz_count; i++)
    {
        printf("--------------------------------------------\n");
        printf("%d. ", i + 1);
        print_question(tmp[i], 'f');
        printf("--------------------------------------------\n");
    }

    int choice;

    do
    {
        printf("Please choose the question you want to change: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
    } while (choice > quiz_count || choice < 0);

    int option;



    do
    {
        // print the menu
        system("clear");
        // system("cls");
        printf("What do you want to do?\n");
        printf("1. Change question\n");
        printf("2. Delete the question\n");
        printf("0. Return\n");

        // print the chosen question again
        printf("--------------------------------------------\n");
        print_question(tmp[choice - 1], 'f');
        printf("--------------------------------------------\n");

        // let the user choose what to do
        printf("Enter your choice:");
        scanf("%d%*c", &option);

        switch (option)
        {
            case 0:
                break;
            case 1:
                tmp[choice - 1] = get_question();
            case 2:
                for (int i = choice; i < quiz_count; i++)
                    tmp[i - 1] = tmp[i];
                quiz_count--;
                tmp = realloc(tmp, quiz_count * sizeof(quiz));
                *quiz_list = tmp;
                break;
            default:
                printf("Your choice is not available. Please enter only 1, 2, or 0.");
                break;
        }
    } while (option != 0 && option != 2);

    return quiz_count;
}
