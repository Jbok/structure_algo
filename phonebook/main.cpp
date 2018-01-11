#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 100
#define COMMAND_NUM 3

//global variable
char names[CAPACITY][CAPACITY];
char phonenumbers[CAPACITY][CAPACITY];
int num = 0;

int readline();
void add(char *name, char *phonenumber);
void find(char *name);
void status();
void del(char *name);
int exit();

int main() {
	int stop = 1;
	while (stop) {
		printf("$ ");
		stop=readline();
	}
}

int readline() {
	char ch;
	char command[COMMAND_NUM][CAPACITY];

	int row = 0;
	int col = 0;
	
	while ((ch = getchar()) == ' ');
	while (ch != '\n') {
		if (ch == ' ') {
			command[row][col] = '\0';
			row++;
			col = 0;
		}
		else {
			command[row][col++] = ch;
		}
		ch = getchar();
	}
	command[row][col] = '\0';

	if (strcmp(command[0], "add")==0) {
		add(command[1], command[2]);
	}
	else if (strcmp(command[0], "find")==0) {
		find(command[1]);
	}
	else if (strcmp(command[0], "status")==0) {
		status();
	}
	else if (strcmp(command[0], "delete")==0) {
		del(command[1]);
	}
	else if (strcmp(command[0], "exit")==0) {
		return exit();
	}
	return 1;
}

void add(char *name, char *phonenumber) {

	strcpy(names[num], name);
	strcpy(phonenumbers[num], phonenumber);
	num++;
	printf("%s was added successfully. %s\n", name, phonenumber);

	return;
}

void find(char *name) {
	for (int i = 0; i < num; i++) {
		if (strcmp(names[i], name) == 0) {
			printf("%s\n", phonenumbers[i]);
			return;
		}
	}
	printf("No person named '%s' existst\n", name);
}

void status() {
	for (int i = 0; i < CAPACITY; i++) {
		if (strcmp(names[i], "") != 0) {
			printf("%s %s \n", names[i], phonenumbers[i]);
		}
	}
	printf("Total %d persions.\n", num);
}

void del(char *name) {
	for (int i = 0; i < num; i++) {
		if (strcmp(names[i], name) == 0) {
			strcpy(names[i], "");
			strcpy(phonenumbers[i], "");
			num--;
			printf("%s was deleted successfully.\n", name);
			return;
		}
	}
	printf("No person named '%s' existst\n", name);
}

int exit() {
	return 0;
}