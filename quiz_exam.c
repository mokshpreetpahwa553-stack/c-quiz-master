#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
	char question[200];  //question can be max 200 characters long
	char options[4][30]; //each question has 4 options, each opton can be 30 characters long
	char correct_ans; //to hold correct answer
}QUIZ;

//function to put each question to stuct from file
void feed_ques(QUIZ exam[],char file[],int *total_ques); 

//function to shuffle quiz questions
void shuffle(QUIZ exam[],int *total_ques);

//function to print quiz
void print_ques(QUIZ exam[],char file[],int *total_ques);


//main function
int main(void)
{
	srand(time(NULL));
	char filename[50];
	QUIZ exam[100]; //max 100 questions
	int t_ques=0;

	printf("Enter filename: ");
	fgets(filename,50,stdin);
	int len=strlen(filename);
	filename[len-1]='\0'; //strip newline

	feed_ques(exam,filename,&t_ques);
	//we can run this function if we want to shuufle the question, if we dont want to shuffle we can just put ia ac comment
	shuffle(exam,&t_ques);
	print_ques(exam,filename,&t_ques);

}

void feed_ques(QUIZ exam[],char file[],int *total_ques)
{
	FILE *fp;
	fp=fopen(file,"r");
	char line[200];
	if(fp==NULL) //if there is error opening file
	{
		printf("Error Opening file!");
		return;
	}

	int q_num=0;
	while(q_num<100 && (fgets(line , 200 , fp) != NULL))
	{
		if(line[0]=='\n')
		{
			continue;
		}
		exam[q_num].question[0]='\0';  //initialising to avoid garbage value
		
		while(strncmp(line,"Q:",2)==0)
		{
			strcat(exam[q_num].question,line+3); //strcat conceates strings, and used line+3 as pointer to fourth character skipping "Q: " in question
			fgets(line , 200 , fp);
		}

		int j=0;

		while(j<4 && (line[0]=='A' || line[0]=='B' || line[0]=='C' || line[0]=='D')  )
		{
			exam[q_num].options[j][0]='\0';  //initialising to avoid garbage value
			strcpy(exam[q_num].options[j],line);
			j++;
			fgets(line , 200 , fp);  //used 200 here instead of 30 bcs line is 200 long and it will only store till '\0' so no problem with 200. Moreover we are coyinh jiust till 30 in options
		}

		if(strncmp(line,"ANSWER:",7)==0)
		{
			int len=strlen(line);
			exam[q_num].correct_ans=line[8];  //to just get character of answer
		}

		++q_num;

	}
	(*total_ques)=q_num;

	fclose(fp);

}


void print_ques(QUIZ exam[],char file[],int *total_ques)
{
	int score=0;

	for(int i=0;i<*total_ques;i++)
	{
		printf("Question %d: ",i+1);
		printf("%s\n",exam[i].question);

		for(int j=0;j<4;j++)
		{
			printf("%s\n",exam[i].options[j]);
		}

		char answer;
		printf("ANSWER: ");
		scanf(" %c",&answer);

		if(exam[i].correct_ans==toupper(answer)) //if entered answer is correct
		{
				score++;
		}
		printf("\n");
	}
	printf("\n");

	printf("Score is %d/%d",score,*total_ques);
}

void shuffle(QUIZ exam[],int *total_ques)
{
	
	for(int i=0;i<*total_ques-2;i++)
	{
		int j = (rand() % (*total_ques - i)) + i;  //random number 

		QUIZ temp=exam[i];
		exam[i]=exam[j];
		exam[j]=temp;
	}
}


