/*
 * Simple console quiz application in C.
 * Displays multiple-choice questions, accepts the user's answers,
 * and calculates the final score.
 *
 * Compile: gcc quiz.c -o quiz
 * Run:     ./quiz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OPTIONS 4

typedef struct {
    const char *question;
    const char *options[NUM_OPTIONS];
    int answer; /* correct option, 1-based */
} Question;

static const Question questions[] = {
    {"Which data structure uses the LIFO (Last In, First Out) principle?",
     {"Queue", "Stack", "Array", "Linked List"}, 2},
    {"Which function in Excel adds up a range of cells?",
     {"COUNT", "AVERAGE", "SUM", "MAX"}, 3},
    {"Which of these is an Operating System?",
     {"Python", "Linux", "MySQL", "Chrome"}, 2},
    {"What does CPU stand for?",
     {"Central Processing Unit", "Computer Personal Unit",
      "Central Program Utility", "Control Processing Unit"}, 1},
    {"Which Python library is widely used for data analysis?",
     {"Pandas", "Flask", "Pygame", "Tkinter"}, 1},
    {"Which OS component manages processes and CPU scheduling?",
     {"Compiler", "Kernel", "Text editor", "Browser"}, 2},
    {"Which Excel feature summarizes large datasets into a compact report?",
     {"Pivot Table", "Word Art", "Spell Check", "Page Break"}, 1},
    {"What does RAM stand for?",
     {"Read Access Memory", "Random Access Memory",
      "Run Active Memory", "Rapid Application Module"}, 2},
    {"Which gas is the main contributor to the greenhouse effect from human activity?",
     {"Oxygen", "Nitrogen", "Carbon dioxide", "Argon"}, 3},
    {"Which Python keyword is used to define a function?",
     {"func", "define", "def", "function"}, 3},
};

#define TOTAL (int)(sizeof(questions) / sizeof(questions[0]))

/* Read a valid option number (1..NUM_OPTIONS). Returns -1 on end of input. */
static int read_choice(void) {
    char buf[64];
    char *end;
    long val;

    for (;;) {
        printf("Your answer (1-%d): ", NUM_OPTIONS);
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            return -1;
        val = strtol(buf, &end, 10);
        if (end != buf && (*end == '\n' || *end == '\0') &&
            val >= 1 && val <= NUM_OPTIONS)
            return (int)val;
        printf("Invalid input. Please enter a number from the list.\n");
    }
}

static void ask_question(int number, const Question *q) {
    int i;
    printf("\nQuestion %d/%d: %s\n", number, TOTAL, q->question);
    for (i = 0; i < NUM_OPTIONS; i++)
        printf("  %d. %s\n", i + 1, q->options[i]);
}

static void show_result(int score, const int *given) {
    double percentage = (double)score / TOTAL * 100.0;
    int i;

    printf("\n========================================\n");
    printf("              RESULT\n");
    printf("========================================\n");
    printf("Score      : %d / %d\n", score, TOTAL);
    printf("Percentage : %.1f%%\n", percentage);

    if (percentage == 100.0)
        printf("Remark     : Excellent!\n");
    else if (percentage >= 60.0)
        printf("Remark     : Good job!\n");
    else
        printf("Remark     : Keep practicing.\n");

    if (score < TOTAL) {
        printf("\nQuestions to review:\n");
        for (i = 0; i < TOTAL; i++) {
            if (given[i] != questions[i].answer) {
                printf("- %s\n", questions[i].question);
                printf("    Your answer : %s\n", questions[i].options[given[i] - 1]);
                printf("    Correct     : %s\n",
                       questions[i].options[questions[i].answer - 1]);
            }
        }
    }
}

int main(void) {
    int given[TOTAL];
    int score = 0;
    int i, choice;

    printf("========================================\n");
    printf("          WELCOME TO THE QUIZ\n");
    printf("========================================\n");

    for (i = 0; i < TOTAL; i++) {
        ask_question(i + 1, &questions[i]);
        choice = read_choice();
        if (choice == -1) {
            printf("\nInput ended. Quiz aborted.\n");
            return 1;
        }
        given[i] = choice;
        if (choice == questions[i].answer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong. The correct answer is: %s\n",
                   questions[i].options[questions[i].answer - 1]);
        }
    }

    show_result(score, given);

    printf("\n========================================\n");
    printf("  Thank you for playing! Have a great day!\n");
    printf("========================================\n");
    return 0;
}