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

typedef struct{
	char * name;
	char * surname;
	char * role;
	int age;
	int available;
}crewMember;

typedef struct{
	char * owner;
	char * name;
	int width;
	int length;
	int maxPeople;
	int currentPeople;
	crewMember * crew;
}ship;

int ships_size = 0;
int crewMembers_size = 0;
ship * shipsG;
crewMember * crewMembersG;

int getLength(char *);
void addShip(ship*);
void addCrewMember(crewMember*);
void addCrewMemberToShip(ship*,crewMember*);
void getCrewMembers(ship*);
void getShips(ship*);

int main(void) {

	shipsG = (ship *) malloc(sizeof(ship));
	crewMembersG = (crewMember *) malloc(sizeof(crewMember));

	int option = 0;

	while (option != 6){
	printf("--- Menu --- \n1-Add Ship\n2-Add Crew Member\n3-Add Crew Member to Ship\n4-Show Crew Members\n5-Show all ships\n6-Exit\n");
	scanf("%d",&option);

	switch(option){
		case 1:{
			addShip(shipsG);
			break;
		}
		case 2:{
			addCrewMember(crewMembersG);
			break;
		}
		case 3:{
			addCrewMemberToShip(shipsG,crewMembersG);
			break;
		}
		case 4:{
			getCrewMembers(shipsG);
			break;
		}
		case 5:{
			getShips(shipsG);
			break;
		}
		case 6:{
			printf("Goodbye. \n");
			break;
		}

		default:{
			printf("Invalid option. \n");
			break;
		}

	}

	}
	//free(shipsG);
	//free(crewMembersG);

	ship * index;
	ship * end = shipsG + (ships_size - 1);
	for(index=shipsG; index <= end;++index){
		free(index->name);
		free(index->owner);
		free(index->crew);
	}
	crewMember * crewIndex;
	crewMember * crewEnd = crewMembersG + (crewMembers_size - 1);
	for(crewIndex = crewMembersG; crewIndex <= crewEnd; ++crewIndex){
		free(crewIndex->name);
		free(crewIndex->role);
		free(crewIndex->surname);
	}
	free(shipsG);
	free(crewMembersG);
	return EXIT_SUCCESS;
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

void addShip(ship * ships){
	char * owner;
	char * name;
	char * temp;
	int width;
	int length;
	int maxPeople;
	ship * shipIndex = ships;

	//Owner's name

	printf("Enter owner's name: \n");
	scanf("%ms",&temp);
	owner = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(owner,temp);
	free(temp);

	// Ship's name

	printf("Enter ship's name: \n");
	scanf("%ms",&temp);
	name = (char *) malloc(getLength(temp) * sizeof(char));
	strcpy(name,temp);
	free(temp);

	//Ship's dimensions

	printf("Enter ship's width: \n");
	scanf("%d",&width);
	printf("Enter ship's length: \n");
	scanf("%d",&length);

	// Ship's max people

	printf("Enter ship's maximum capacity: \n");
	scanf("%d",&maxPeople);

	ship newShip;
	newShip.owner = owner;
	newShip.name = name;
	newShip.width = width;
	newShip.length = length;
	newShip.maxPeople = maxPeople;
	newShip.currentPeople = 0;
	newShip.crew = (crewMember *) malloc(maxPeople * sizeof(crewMember));


	if (ships_size == 0){
		*shipIndex = newShip;
	}
	else{
		shipsG = (ship *) realloc(shipsG,(ships_size + 1) * sizeof(ship));
		shipIndex = shipsG + ships_size;
		*shipIndex = newShip;
	}
	ships_size++;

}

void addCrewMember(crewMember * crewMembers){
	char * name;
	char * surname;
	char * role;
	char * temp;
	int age;
	crewMember * memberIndex = crewMembers;

	// Crew member's name

		printf("Enter crew member's name: \n");
		scanf("%ms",&temp);
		name = (char *) malloc(getLength(temp) * sizeof(char));
		strcpy(name,temp);
		free(temp);


	// Crew member's surname

		printf("Enter crew member's surname: \n");
		scanf("%ms",&temp);
		surname = (char *) malloc(getLength(temp) * sizeof(char));
		strcpy(surname,temp);
		free(temp);

	// Crew member's role

		printf("Enter crew member's role: \n");
		scanf("%ms",&temp);
		role = (char *) malloc(getLength(temp) * sizeof(char));
		strcpy(role,temp);
		free(temp);
	// Crew member's age

		printf("Enter crew member's age: \n");
		scanf("%d",&age);

		crewMember newMember;
		newMember.name = name;
		newMember.surname = surname;
		newMember.role = role;
		newMember.age = age;
		newMember.available = 1;

		if (crewMembers_size == 0){
			//crewMembers = (crewMember *) malloc(sizeof(crewMember));
			*memberIndex = newMember;
		}
		else{
			crewMembersG = (crewMember *) realloc(crewMembersG,(crewMembers_size + 1) * sizeof(crewMember));
			memberIndex = crewMembersG + crewMembers_size;
			*memberIndex = newMember;
		}

		crewMembers_size++;

}

void addCrewMemberToShip(ship * ships,crewMember * crewMembers){
	ship * shipIndex = ships;
	crewMember * memberIndex = crewMembers;
	int i;
	int moved = 0;

	if(ships_size == 0 || crewMembers_size == 0){
		printf("Make sure you have at least 1 ship and 1 crew member.\n");
		return;
	}

	printf("Choose a ship: \n");
	for(i = 0; i < ships_size; ++i){
		printf("%d - %s\n",i,shipIndex->name);
		shipIndex++;
	}
	scanf("%d",&moved);
	shipIndex = ships + moved;
	//shipsG = shipsG + moved;

	if(shipIndex->maxPeople - shipIndex->currentPeople == 0){
		printf("This ship's crew is at full capacity.\n");
		//shipsG = shipsG - moved;
		return;
	}
		printf("Choose a crew member: \n");
		for(i = 0; i < crewMembers_size; ++i){
			printf("%d - %s %s (%s)\n",i,memberIndex->name,memberIndex->surname,memberIndex->role);
			memberIndex++;
		}
		scanf("%d",&i);
		memberIndex = crewMembers + i;

		if(memberIndex->available == 0){
			printf("This crew member is already assigned to a ship. \n");
			return;
		}

			shipIndex->crew = shipIndex->crew + shipIndex->currentPeople;
			*(shipIndex->crew) = *memberIndex;

		shipIndex->currentPeople++;
		memberIndex->available = 0;
		shipIndex->crew->available = 0;
		shipIndex->crew = shipIndex->crew - (shipIndex->currentPeople - 1);

}


void getCrewMembers(ship * ships){
	ship * shipIndex = ships;
	crewMember * memberIndex;
	int i;

	if(ships_size == 0 || crewMembers_size == 0){
		printf("Make sure you have at least 1 ship and 1 crew member.\n");
		return;
	}
	printf("Choose a ship: \n");
		shipIndex = ships;
		for(i = 0; i < ships_size; ++i){
			printf("%d - %s\n",i,shipIndex->name);
			shipIndex++;
		}
		scanf("%d",&i);
		shipIndex = ships + i;
		memberIndex = shipIndex->crew;
		printf("Owner: %s \nCrew: \n",shipIndex->owner);
		for(i = 0; i < shipIndex->currentPeople; ++i){
					printf("%s %s (%s)\n",memberIndex->name,memberIndex->surname,memberIndex->role);
					memberIndex++;
				}

}

void getShips(ship * ships){
	ship * shipIndex = ships;
	crewMember * memberIndex;
	int i;
	int j;

	if(ships_size == 0 || crewMembers_size == 0){
		printf("Make sure you have at least 1 ship and 1 crew member.\n");
		return;
	}


	for(i = 0; i < ships_size; ++i){
		printf("%d - %s\n",i,shipIndex->name);
		memberIndex = shipIndex->crew;
		printf("Owner: %s \nCrew: \n",shipIndex->owner);
		int j;
				for(j = 0; j < shipIndex->currentPeople; ++j){
							printf("%s %s (%s)\n",memberIndex->name,memberIndex->surname,memberIndex->role);
							memberIndex++;
						}
		shipIndex++;
	}

}

