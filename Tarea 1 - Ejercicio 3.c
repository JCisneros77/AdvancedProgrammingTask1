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

typedef void(*option_t)();

typedef struct{
	int available;
	int id;
}bed;

typedef struct{
	char * name;
	char * surname;
	int age;
	char * phone;
	int currentBed;
}patient;

bed * beds;
patient * patients;
int patients_size;
int beds_size;
int beds_available;

int getLength(char * word);
void addPatient();
void checkPatientInBed();
void dischargePatient();
void showAllPatients();
void getBeds();
void exitHospital();




int main(void) {

	patients = (patient *) malloc(sizeof(patient));
	beds = (bed *) malloc(sizeof(bed));
	patients_size = 0;
	beds_available = 1;
	beds_size = 0;
	int option;

	option_t * menu = (option_t *) malloc(6 * sizeof(option_t));
	*menu = addPatient;
	*(menu + 1) = checkPatientInBed;
	*(menu + 2) = dischargePatient;
	*(menu + 3) = showAllPatients;
	*(menu+4) = getBeds;
	*(menu+5) = exitHospital;

	while(option != 6){
		printf("--- Menu ---\n1)Add patient\n2)Check patient in bed\n3)Discharge Patient\n4)Show All Patients\n5)Show Beds\n6)Exit\n");
		scanf("%d",&option);
		if(option > 0 && option < 7)
		(*(menu+option-1))();
		else
			printf("Invalid option.\n");
	}

	// Free Memory
	if(patients_size != 0){
		patient * pIndex;
		patient * pEnd = patients + (patients_size - 1);
		for(pIndex = patients; pIndex <= pEnd; pIndex++){
			free(pIndex->name);
			free(pIndex->surname);
			free(pIndex->phone);
		}

		free(patients);
	}
	free(beds);
	free(menu);
	return EXIT_SUCCESS;
}

void addPatient(){
	char * temp;
	char * name;
	char * surname;
	char * phone;
	int age;
	bed * bedIndex;
	patient * patientIndex;
	patient p;

	printf("Enter patient's name \n");
	scanf("%ms",&temp);
	name = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(name,temp);
	free(temp);

	printf("Enter patient's last name \n");
	scanf("%ms",&temp);
	surname = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(surname,temp);
	free(temp);

	printf("Enter patient's phone number \n");
	scanf("%ms",&temp);
	phone = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(phone,temp);
	free(temp);

	printf("Enter patient's age \n");
	scanf("%d",&age);

	if(beds_size == 0){
		beds->available = 0;
		beds->id = 1;
		beds_size = 1;
		beds_available = 0;
		p.currentBed = 1;
	}
	else{
	if(beds_available == 0){
		beds = (bed *) realloc(beds,(beds_size + 5) * sizeof(bed));
		bedIndex = beds + beds_size;
		bedIndex->available = 0;
		bedIndex->id = beds_size+1;
		p.currentBed = beds_size+1;
		int i;
		bedIndex++;
		for(i = 1; i < 5; ++i){
			bedIndex->id = beds_size + i + 1;
			bedIndex->available = 1;
			bedIndex++;
		}
		beds_size+=5;
		beds_available=4;
	}
	else{
		bed * bStart;
		bed * bEnd = beds + (beds_size - 1);
		for(bStart = beds; bStart <= bEnd; ++bStart){
			if(bStart->available == 1)
				break;
		}
		bStart->available = 0;
		p.currentBed = bStart->id;
		beds_available-=1;

	}
	}

	p.name = name;
	p.surname = surname;
	p.phone = phone;
	p.age = age;

	if (patients_size == 0){
		*patients = p;
	}
	else{
		patients = (patient *) realloc(patients,(patients_size + 1) * sizeof(patient));
		patientIndex = patients + patients_size;
		*patientIndex = p;
	}
	patients_size++;


}

void checkPatientInBed(){
	int id;
	int found = 0;
	patient * patientIndex;
	patient * patientEnd = patients + (patients_size - 1);
	printf("Enter bed's id \n");
	scanf("%d",&id);

	if(id > beds_size){
		printf("Bed %d does not exist.\n",id);
		return;
	}

	for(patientIndex = patients; patientIndex <= patientEnd; ++patientIndex){
		if(patientIndex->currentBed == id){
			printf("%s %s is in bed %d.\n",patientIndex->name,patientIndex->surname,id);
			found = 1;
			break;
		}
	}

	if(found == 0)
		printf("Bed %d is currently empty.\n",id);
}

void dischargePatient(){
	patient * patientIndex;
	patient * patientEnd = patients + (patients_size - 1);
	bed * bedIndex;
	int id;
	printf("Enter bed's id. \n");
	scanf("%d",&id);
	if(id > beds_size){
		printf("The bed %d does not exist.\n",id);
		return;
	}
	bedIndex = beds + (id-1);
	if(bedIndex->available == 1){
		printf("The bed %d is currently empty. \n",id);
		return;
	}

	for(patientIndex = patients; patientIndex <= patientEnd; patientIndex++){
		if(patientIndex->currentBed == id)
			break;
	}
	bedIndex = beds + (id-1);


	bedIndex->available = 1;
	beds_available++;

	free(patientIndex->name);
	free(patientIndex->phone);
	free(patientIndex->surname);

	if (patientIndex != patientEnd)
	memmove(patientIndex, patientIndex+1, (patientEnd - patientIndex) * sizeof(patient));


	patients = (patient *) realloc(patients,(patients_size - 1) * sizeof(patient));
	patients_size--;



}

void showAllPatients(){
	if(patients_size == 0){
		printf("There are no patients currently in the hospital.\n");
		return;
	}
	patient * patientIndex;
	patient * patientEnd = patients + (patients_size - 1);
	int i = 1;

	for(patientIndex = patients; patientIndex <= patientEnd; patientIndex++){
		printf("%d) %s %s (%d years old) in bed %d.\n",i,patientIndex->name,patientIndex->surname,patientIndex->age,patientIndex->currentBed);
		i++;
	}
}

void getBeds(){

	printf("Total beds: %d\n",beds_size);
	printf("Available beds: %d\n",beds_available);

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

void exitHospital(){
	printf("Goodbye \n");
}
