#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIRECTORY_CAPACITY 3
#define COMMAND_CAPACITY 2
#define BUFFER_SIZE 100

typedef struct user {
	char *name;
	char *phonenumber;
	char *email;
	char *group;
};

//global variable
user **users; //structure array pointer
int num = 0; //number of people in phone directory.
int capacity = DIRECTORY_CAPACITY; //size of arrays.

void releas_user(user *user);
void compose_name(char *str);
void reallocate();
int read_line(FILE *fp, char str[], int limit);
int search(char *name);
void init_directory();
//void init_directory();
int process_command();
void add(char *name, char *phonenumber, char*email, char *group);
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

void releas_user(user *user) {
	free(user->name);
	if (user->email != NULL)
		free(user->email);
	if (user->phonenumber != NULL)
		free(user->phonenumber);
	if (user->group != NULL)
		free(user->group);
	free(user);
}

void compose_name(char *str) {
	char *ptr = (char*)malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(ptr, str);
	strcpy(str, "");

	int length = 0;
	char *temp = strtok(ptr, " ");
	
	while (temp != NULL) {
		length += strlen(temp);
		strcat(str, temp);
		str[length++] = ' ';
		str[length] = '\0';
		temp = strtok(NULL, " ");
	}
	str[length - 1] = '\0';
}

int read_line(FILE * fp, char str[], int limit) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) == ' ');
	while (ch != '\n'&&ch != EOF) {
		if (i < limit - 1)
			str[i++] = ch;
		ch = fgetc(fp);
	}
	str[i] = '\0';
	return i;
}

int process_command() {
	char str[BUFFER_SIZE];
	char command[COMMAND_CAPACITY][BUFFER_SIZE] = { 0 };
	
	int num_command = 0;
	read_line(stdin, str, BUFFER_SIZE);
	char *ptr = strtok(str, " ");
	while (ptr != NULL) {
		if (num_command == 0) {
			strcpy(command[num_command++], ptr);
			ptr = strtok(NULL, "\0");
		}
		else {
			strcpy(command[num_command], ptr);
			compose_name(command[num_command]);
			break;
		}
	}
	


	if (strcmp(command[0], "add")==0) {
		if (command[1][0]=='\0') {
			printf("Name is required.\n");
		}
		else {
			char empty[] = " ";
			char buf2[BUFFER_SIZE];
			char buf3[BUFFER_SIZE];
			char buf4[BUFFER_SIZE];
			printf("Phone: ");
			read_line(stdin, buf2, BUFFER_SIZE);
			printf("Email: ");
			read_line(stdin, buf3, BUFFER_SIZE);
			printf("Group: ");
			read_line(stdin, buf4, BUFFER_SIZE);
			add(command[1], 
				(strlen(buf2)>0? buf2: empty),
				(strlen(buf3)>0 ? buf3 : empty),
				(strlen(buf4)>0 ? buf4 : empty) );
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
	
	user **tempuser = (user**)malloc(sizeof(user*)*capacity);
	for (int i = 0; i < num; i++) {
		tempuser[i] = users[i];
	}
	free(users);
	users = tempuser;
}

void init_directory() {
	users= (user**)malloc(sizeof(user*)*capacity);
}

void add(char *name, char *phonenumber, char*email, char *group) {
	int i = num;


	if (num >= capacity) {
		reallocate();
	}
	if(i!=0)
	while (i != 0 && strcmp(name, users[i-1]->name) < 0) {
		users[i] = users[i - 1];
		i--;
		if (i == 0)
			break;
	}
	users[i] = (user*)malloc(sizeof(user));

	users[i]->name = strdup(name);  //strdup assign address using malloc so, need to free at last.
	users[i]->phonenumber = strdup(phonenumber);
	users[i]->email = strdup(email);
	users[i]->group = strdup(group);
	
	num++;
	printf("%s was added successfully.\n", name);
	return;
}

int search(char *name) {
	for (int i = 0; i < num; i++) {
		if (strcmp(users[i]->name, name) == 0) {
			return i; //return index
		}
	}
	return -1; //not found
}

void find(char *name) {
	int i = search(name);
	if (i != -1) {
		printf("%s:\n\tPhone: %s\n\tEmail: %s\n\tGroup: %s\n", users[i]->name, users[i]->phonenumber, users[i]->email, users[i]->group);
	}
	else {
		printf("No person named '%s' exist\n", name);
	}
}

void status() {
	for (int i = 0; i < num; i++) {
		printf("%s %s \n", users[i]->name, users[i]->phonenumber);
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
		releas_user(users[index]);
		for (int i = index; i < num - 1; i++) {
			users[i] = users[i + 1];
		}
		num--;
		printf("'%s' was deleted successfully.\n", name);
	}
}

int exit() {
	for (int i = 0; i < num; i++) {
		releas_user(users[i]);
	}
	free(users);
	return 0;
}

void load(char *filename) {
	char buf1[BUFFER_SIZE];
	char *name, *number, *email, *group;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Open failed. \n");
		return;
	}
	while (1) {
		if (!read_line(fp, buf1, BUFFER_SIZE - 1))
			break;
		name = strtok(buf1, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
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
		fprintf(fp, "%s#%s#%s#%s#\n", users[i]->name, users[i]->phonenumber, users[i]->email, users[i]->group);
	}
	printf("save contents to %s sucessfully!\n", filename);
	fclose(fp);
}