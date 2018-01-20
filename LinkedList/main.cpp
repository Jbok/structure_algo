#include <stdio.h>
#include <string.h>
#include "string_tools.h"
#include "musiclibrary.h"
#define BUFFER_LENGTH 200

void process_command();
void handle_add();
void handle_load();

int main() {
	initialize();
	handle_load();
	process_command();
}

void handle_load() {
	char buf1[BUFFER_LENGTH];
	char command[BUFFER_LENGTH];
	printf("Data file name ? ");
	
	if (read_line(stdin, buf1, BUFFER_LENGTH) <= 0) {
		return;
	}

	FILE *fp = fopen(buf1, "r");
	if (fp == NULL) {
		printf("No such file exists.\n");
		return;
	}

	load(fp);
	fclose(fp);
}

void process_command() {
	char command_line[BUFFER_LENGTH];
	char *command;

	while (1) {
		printf("$ ");

		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");
		if (strcmp(command, "add") == 0)
			handle_add();
//		else if (strcmp(command, "search") == 0)
//			handle_sarch();
//		else if (strcmp(command, "remove") == 0)
//			handle_remove();
		else if (strcmp(command, "status") == 0)
			status();
//		else if (strcmp(command, "play") == 0)
//			handle_play();
//		else if (strcmp(command, "save") == 0)
//			handle_save();
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

void handle_add() {
	char buffer[BUFFER_LENGTH];
	char *artist = NULL, *title = NULL, *path = NULL;

	printf("\tArtist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		artist = strdup(buffer);
	}
	
	printf("\tTitle: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		title = strdup(buffer);
	}

	printf("\tPath: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		path= strdup(buffer);
	}

	printf("%s %s %s \n", artist, title, path);
	//add to the music library
	add_song(artist, title, path);
}