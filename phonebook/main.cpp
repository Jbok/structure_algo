#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_SIZE 100
#define COMMAND_NUM 3

//global variable
char *names[CAPACITY];
char *phonenumbers[CAPACITY];
int num = 0;

int readline();
int search(char *name);
void add(char *name, char *phonenumber);
void find(char *name);
void status();
void del(char *name);
void load(char *filename);
void save(char *filename);
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
	else if (strcmp(command[0], "load")==0) {
		load(command[1]);
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
	else if (strcmp(command[0], "save")==0) {
		save(command[1]);
	}
	else if (strcmp(command[0], "exit")==0) {
		return exit();

	}
	else {
		printf("Please input correct command\n");
	}
	return 1;
}

void add(char *name, char *phonenumber) {
	int i = num;
	
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