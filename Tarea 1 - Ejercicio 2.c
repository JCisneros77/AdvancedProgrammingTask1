/*
 ============================================================================
 Name        : Tarea.c
 Author      : Jose Cisneros
 Version     :
 Copyright   : Copyright Jose Cisneros 2014
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define NQ 10 // Number of Questions
#define NA 6 // Number of Answers per Question

typedef struct{
	char * description;
	char ** answers;
}question;

typedef struct{
	char * name;
	int age;
	int * selected;
}person;


question * questions;
person * persons;
int persons_size = 0;

int getLength(char *);
void enterQuestions();
void answerSurvey();
void printHistogram();



int main(void) {
	questions = malloc(NQ * sizeof(question));
	persons = malloc(sizeof(person));

	int option = 0;
	enterQuestions();

	while(option != 3){
		printf("---- Menu ----\n1)Take Survey\n2)Show Histogram\n3)Exit\n");
		scanf("%d",&option);
		switch (option){
		case 1:{
			answerSurvey();
			break;
		}
		case 2:{
			printHistogram();
			break;
		}
		case 3:{
			printf("Goodbye.\n");
			break;
		}
		default: printf("Invalid option. \n");
		break;
		}
	}

	// Free Memory

	question * qIndex;
	question * qEnd = questions + (NQ - 1);
	for(qIndex = questions; qIndex <= qEnd; qIndex++){
		free(qIndex->description);
		char ** a;
		    for (a= qIndex->answers;*a;++a)
		        free(*a);
	    free(qIndex->answers);
	}

	person * pIndex;
	person * pEnd = persons + (persons_size - 1);
	for(pIndex = persons; pIndex <= pEnd; ++pIndex){
		free(pIndex->selected);
		free(pIndex->name);
	}

	free(persons);
	free(questions);

	return EXIT_SUCCESS;
}

void enterQuestions(){
	question * questionIndex = questions;
	int i;
	for (i = 1; i < NQ+1; ++i){
		char * temp;
		char * description;
		question q;
		q.answers = (char **) malloc(NA * sizeof(char*));

		printf("Enter question No. %d\n",i);
		scanf("%ms",&temp);
		description = (char *) malloc (getLength(temp) * sizeof(char));
		strcpy(description,temp);
		free(temp);

		q.description = description;
		int j;
		for(j = 1; j < NA+1; ++j){
			char * temp;
			char * answer;
			printf("Enter choice No. %d\n",j);
			scanf("%ms",&temp);
			answer = (char *) malloc (getLength(temp) * sizeof(char));
			strcpy(answer,temp);
			free(temp);
			*(q.answers) = answer;
			q.answers++;
		}
		q.answers = q.answers - NA;
		*questionIndex = q;
		questionIndex++;
	}
}

void answerSurvey(){
	person * personIndex = persons;
	person p;
	p.selected = (int *) malloc(NQ * sizeof(int));
	// User's details
	char * name;
	char * temp;
	int age;
	printf("Enter your name: \n");
	scanf("%ms",&temp);
	name = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(name,temp);
	free(temp);
	p.name = name;
	printf("Enter your age: \n");
	scanf("%d",&age);
	if(age < 18 || age > 120){
		printf("You have to be between 18 and 120 years old to take this survey. \n");
		return;
	}
	p.age = age;

	// Questions
	int i,j,choice;
	question * questionIndex = questions;
	for (i = 1; i < NQ+1; ++i){
		printf("%s :\n",questionIndex->description);
		for (j = 1; j < NA+1; ++j){
			printf("%d) %s \n",j,*(questionIndex->answers));
			questionIndex->answers++;
		}
		printf("0) No Answer. \n");
		questionIndex->answers = questionIndex->answers - NA;
		scanf("%d",&choice);
		*(p.selected) = choice;
		p.selected++;
		questionIndex++;
	}
	p.selected = p.selected - NQ;
	if(persons_size > 0){
		persons = (person *) realloc(persons,(persons_size+1) * sizeof(person));
		personIndex = persons + persons_size;
	}
	*personIndex = p;
	persons_size++;
}

void printHistogram(){
	question * questionIndex;
	question * questionEnd = questions + (NQ - 1);
	person * personIndex;
	person * personEnd = persons + (persons_size - 1);
	int currentQuestion = 0;

	for(questionIndex = questions; questionIndex <= questionEnd; ++questionIndex){
			int * stats = (int *) malloc(NA * 5 * sizeof(int));
			int * counter;
			for (counter = stats; counter <=(stats+(NA * 5 -1)); ++counter)
				*(counter) = 0;
		for(personIndex = persons; personIndex <= personEnd; ++personIndex){
			int age = personIndex->age;
			if(*(personIndex->selected + currentQuestion) == 0)
				continue;

			int answer = *(personIndex->selected + currentQuestion) - 1;

			if(age >= 18 && age <= 25){
				*(stats + answer)+=1;
			}
			else if(age >= 26 && age <= 35){
				*(stats + answer + (NA*1))+=1;
			}
			else if(age >= 36 && age <= 45){
				*(stats+ answer + (NA*2))+=1;
			}
			else if(age >= 46 && age <= 65){
				*(stats+ answer + (NA*3))+=1;
			}
			else if(age >= 66 && age <= 120){
				*(stats+ answer + (NA*4))+=1;
			}
		}
		printf("Question %d \n",currentQuestion + 1);
		int i;
		for(i = 0; i < NA; ++i){
			printf("Answer No. %d\n",i+1);
			// (18-25)
			printf("(18-25)\t\t");
			int j;
			for(j=0; j < *(stats + i);++j){
				printf("*");
			}
			printf("\n");
			// (26-35)
			printf("(26-35)\t\t");
			for(j=0; j < *(stats + i + NA);++j){
				printf("*");
			}
			printf("\n");
			// (36-45)
			printf("(36-45)\t\t");
			for(j=0; j < *(stats + i + (NA*2));++j){
				printf("*");
			}
			printf("\n");
			// (46-65)
			printf("(46-65)\t\t");
			for(j=0; j < *(stats + i + (NA*3));++j){
				printf("*");
			}
			printf("\n");
			// (66-120)
			printf("(66-120)\t\t");
			for(j=0; j < *(stats + i + (NA*4));++j){
				printf("*");
			}
			printf("\n");
		}
		printf("\n");

		currentQuestion++;
		free(stats);
	}
	printf("\n");


}

int getLength(char * word){

	char * end = word;
	char * start = word;
	int i = 0;

	while (*end != '\0'){
		end = word;
		word++;
	}
	i = end - start;

	return i;
}
