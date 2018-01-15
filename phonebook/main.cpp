#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIRECTORY_CAPACITY 3
#define COMMAND_CAPACITY 3
#define BUFFER_SIZE 100

//global variable
char **names;
char **phonenumbers;

int capacity = DIRECTORY_CAPACITY; //size of arrays.
int num = 0; //number of people in phone directory.

void reallocate();
void read_line(char str[], int limit);
int search(char *name);
void init_directory();
int process_command();
void add(char *name, char *phonenumber);
void find(char *name);
void status();
void del(char *name);
void load(char *filename);
void save(char *filename);
int exit();

int main() {
	int stop = 1;

	init_directory();

	while (stop) {
		printf("$ ");
		stop=process_command();
	}
}

void read_line(char str[], int limit) {
	int ch, i = 0;
	while ((ch = getchar()) == ' ');
	while (ch != '\n') {
		if (i < limit - 1)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
}

int process_command() {
	char str[BUFFER_SIZE];
	char command[COMMAND_CAPACITY][BUFFER_SIZE] = { 0 };
	
	int num_command = 0;
	read_line(str, BUFFER_SIZE);
	char *ptr = strtok(str, " ");
	while (ptr != NULL) {
		if (num_command < COMMAND_CAPACITY) {
			strcpy(command[num_command++], ptr);
			ptr = strtok(NULL, " ");
		}
		else {
			printf("There are too many arguments\n");
			return -1;
		}
	}


	if (strcmp(command[0], "add")==0) {
		if (command[1][0]=='\0') {
			printf("Name is required.\n");
		}else if (command[2][0]=='\0') {
			printf("Phonenumber is required.\n");
		}
		else {
			add(command[1], command[2]);
		}
	}
	else if (strcmp(command[0], "load")==0) {
		if (command[1][0]=='\0') {
			printf("File name is required.\n");
		}
		else {
			load(command[1]);
		}
	}
	else if (strcmp(command[0], "find")==0) {
		if (command[1][0] == '\0') {
			printf("Name is required.\n");
		}
		else {
			find(command[1]);
		}
	}
	else if (strcmp(command[0], "status")==0) {
		status();
	}
	else if (strcmp(command[0], "delete")==0) {
		if (command[1][0] == '\0') {
			printf("Name is required.\n");
		}
		else {
			del(command[1]);
		}
	}
	else if (strcmp(command[0], "save")==0) {
		if (command[1][0] == '\0') {
			printf("File name is required.\n");
		}
		else {
			save(command[1]);
		}
	}
	else if (strcmp(command[0], "exit")==0) {
		return exit();
	}
	else {
		printf("Please input correct command.\n");
	}
	return 1;
}

void reallocate() {
	capacity *= 2;

	char **tempname = (char **)malloc(sizeof(char*)*capacity);
	char **tempphone = (char **)malloc(sizeof(char*)*capacity);
	
	for (int i = 0; i < num; i++) {
		tempname[i] = names[i];
		tempphone[i] = phonenumbers[i];
	}

	free(names);
	free(phonenumbers);

	names = tempname;
	phonenumbers = tempphone;
}

void init_directory() {
	names = (char**)malloc(sizeof(char*)*DIRECTORY_CAPACITY);
	phonenumbers= (char**)malloc(sizeof(char*)*DIRECTORY_CAPACITY);
}

void add(char *name, char *phonenumber) {
	int i = num;
	
	if (num >= capacity) {
		reallocate();
	}

	while (i != 0 && strcmp(name, names[i - 1]) < 0) {
		free(names[i]);
		free(phonenumbers[i]);
		names[i] = (char *)malloc(sizeof(char)*strlen(names[i-1]) + 1);
		phonenumbers[i] = (char *)malloc(sizeof(char)*strlen(phonenumbers[i-1]) + 1);
		strcpy(names[i], names[i - 1]);
		strcpy(phonenumbers[i], phonenumbers[i - 1]);
		i--;
		if (i == 0)
			break;
	}
		
	names[i] = (char *)malloc(sizeof(char)*(strlen(name) + 1));
	phonenumbers[i] = (char *)malloc(sizeof(char)*(strlen(phonenumber) + 1));
	strcpy(names[i], name);
	strcpy(phonenumbers[i], phonenumber);

	num++;
	printf("%s was added successfully. %s\n", name, phonenumber);
	return;
}

int search(char *name) {
	for (int i = 0; i < num; i++) {
		if (strcmp(names[i], name) == 0) {
			return i; //return index
		}
	}
	return -1; //not found
}

void find(char *name) {
	for (int i = 0; i < num; i++) {
		if (strcmp(names[i], name) == 0) {
			printf("%s %s\n",phonenumbers[i], names[i]);
			return;
		}
	}
	printf("No person named '%s' existst\n", name);
}

void status() {
	for (int i = 0; i < num; i++) {
		printf("%s %s \n", names[i], phonenumbers[i]);
	}
	printf("Total %d persions.\n", num);
}

void del(char *name) {
	int index = search(name);
	if (index == -1) { //not found
		printf("No person named '%s' exists.\n", name);
		return;
	}
	else { //found
		for (int i = index; i < num - 1; i++) {
			free(names[i]);
			free(phonenumbers[i]);
			names[i] = (char *)malloc(sizeof(char)*strlen(names[i+1]) + 1);
			phonenumbers[i] = (char *)malloc(sizeof(char)*strlen(phonenumbers[i + 1]) + 1);
			strcpy(names[i], names[i + 1]);
			strcpy(phonenumbers[i], phonenumbers[i + 1]);
		}
		num--;
		free(names[num]);
		free(phonenumbers[num]);
		printf("'%s' was deleted successfully.\n", name);
	}
}

int exit() {
	for (int i = 0; i < num; i++) {
		free(names[i]);
		free(phonenumbers[i]);
	}
	num = 0;
	return 0;
}

void load(char *filename) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Open failed. \n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp);
}

void save(char *filename) {
	int i;

	FILE*fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (i = 0; i < num; i++) {
		fprintf(fp, "%s %s\n", names[i], phonenumbers[i]);
	}

	fclose(fp);
}