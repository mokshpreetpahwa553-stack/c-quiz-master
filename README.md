# c-quiz-masterC File I/O Quiz – README
Overview
This project is a console-based multiple‑choice quiz program written in C. It reads questions from a text file, loads them into an array of structs, optionally shuffles their order, and then runs an interactive quiz where the user answers each question and receives a final score.

Features
Supports up to 100 questions.

Each question can be multiple lines long (prefixed with Q: in the file).

Four answer options per question (A, B, C, D).

Reads the correct answer from the file and checks user input case‑insensitively.

Optionally shuffles the questions before displaying them.

Question File Format
The quiz reads from a plain text file with repeating blocks in this format:

One or more question lines, each starting with Q:

Four option lines, each starting with A, B, C, or D (e.g. A) ..., B) ...)

An answer line starting with ANSWER: followed by the correct option letter

A blank line between questions is allowed but ignored

Example:

text
Q: Which function is used to open a file in C?
A) open()
B) fopen()
C) fileopen()
D) create()
ANSWER: B

Q: What does fopen("data.txt", "r") return if the file does not exist?
A) 0
B) NULL
C) -1
D) EOF
ANSWER: B
Data Structures
Questions are stored in an array of QUIZ structs:

c
typedef struct {
    char question[200];     // Question text (can span multiple Q: lines)
    char options[4][30];    // Four options, each up to 30 characters
    char correct_ans;       // Correct answer option (A/B/C/D)
} QUIZ;
The program uses:

QUIZ exam[100]; to hold all questions.

int t_ques; to store the total number of questions loaded from the file.

Program Flow
Startup and file input

The program starts in main, seeds the random number generator with time(NULL), and asks the user to enter a filename.

It reads the filename with fgets, strips the trailing newline, and passes it to feed_ques.

Loading questions – feed_ques

c
void feed_ques(QUIZ exam[], char file[], int *total_ques);
Opens the given file for reading.

Loops until EOF or 100 questions are read.

Skips blank lines.

For each question:

Aggregates all consecutive Q: lines into exam[q_num].question, stripping the Q: prefix.

Reads up to 4 option lines (A, B, C, D) into exam[q_num].options.

Reads the ANSWER: line and stores the correct option letter in exam[q_num].correct_ans.

Updates *total_ques with the number of questions successfully loaded.

Shuffling questions – shuffle

c
void shuffle(QUIZ exam[], int *total_ques);
Implements an in‑place Fisher–Yates style shuffle.

For each index i, picks a random j from [i, *total_ques - 1] and swaps exam[i] with exam[j].

This randomizes the question order each run.

Running the quiz – print_ques

c
void print_ques(QUIZ exam[], char file[], int *total_ques);
Iterates through all loaded questions.

Prints "Question X: " followed by the full question text.

Prints the four options.

Prompts the user for an answer (ANSWER: ) and reads a single character.

Compares the uppercase of the user’s answer with correct_ans.

Increments the score on a correct match.

At the end, prints Score is score/total_ques.

How to Compile
Use gcc (or another C compiler that supports C99 or later):

bash
gcc quiz.c -o quiz
Replace quiz.c with your actual source filename.

How to Run
Ensure your quiz text file (e.g. quiz.txt) follows the format described above.

Run the compiled program:

bash
./quiz
When prompted:

text
Enter filename:
type the name of your quiz file, e.g.:

text
quiz.txt
Answer each question by typing A, B, C, or D and pressing Enter.

After the last question, the program prints your final score.

Design Choices and Notes
File I/O and parsing: The program uses fgets to safely read lines up to 200 characters and relies on simple markers (Q:, A/B/C/D, ANSWER:) to parse questions.

Multiple‑line questions: By allowing multiple Q: lines, the format supports longer questions without complicating the parser.

Shuffling: The shuffle function is separated so you can easily disable randomization for testing by commenting out its call in main.

Input robustness: Answers are compared using toupper so both a and A are accepted.

This project demonstrates file I/O, string handling, arrays of structs, and basic randomization in C, wrapped into a practical and extendable quiz application. 
