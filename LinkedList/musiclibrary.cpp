#include "musiclibrary.h"
#include "string_tools.h"

#define NUM_CHARS 256
#define SIZE_INDEX_TABLE 100
#define BUFFER_LENGTH 200

Artist *artist_directory[NUM_CHARS]; //2^8 = 256
SNode *index_directory[SIZE_INDEX_TABLE]; //for one way linked list

int num_index = 0;

void initialize() {
	for (int i = 0; i < NUM_CHARS; i++) {
		artist_directory[i] = NULL;
	}

	for (int i = 0; i < SIZE_INDEX_TABLE; i++) {
		index_directory[i] = NULL;
	}
}

void load(FILE *fp) {
	char buffer[BUFFER_LENGTH];
	char *name, *title, *path;

	while (read_line(fp, buffer, BUFFER_LENGTH) > 0) {
		name = strtok(buffer, "#");
		if (strcmp(name, " ") == 0) {
			name = NULL;
		}
		else {
			name = strdup(name);
		}

		title = strtok(NULL, "#");
		if (strcmp(title, " ") == 0) {
			title = NULL;
		}
		else {
			title = strdup(title);
		}

		path = strtok(NULL, "#");
		if (strcmp(path, " ") == 0) {
			path = NULL;
		}
		else {
			path = strdup(path);
		}
		add_song(name, title, path);
	}
}

Artist *find_artist(char *name) {
	Artist *p = artist_directory[(unsigned char)name[0]]; //first artist with initial name[0]
														  //why use unsigned char? if first bit of name[0] is 1, It return negative value!
	while (p != NULL && strcmp(p->name, name) < 0) {
		p = p->next;
	}

	if (p != NULL && strcmp(p->name, name) == 0) {
		return p;
	}
	else {
		return NULL;
	}
}

Artist *create_artist_instance(char *name) {
	Artist *ptr_artist = (Artist *)malloc(sizeof(Artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;

	return ptr_artist;
}

Artist *add_artist(char *name) {
	Artist *ptr_artist = create_artist_instance(name);

	Artist *p = artist_directory[(unsigned char)name[0]];
	Artist *q = NULL;
	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}

	if (p == NULL && q == NULL) { //unique node
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL) { //add at the front
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else {
		ptr_artist->next = p;
		q->next = ptr_artist;
	}
	
	return ptr_artist;
}

Song *create_song_instance(Artist *ptr_artist, char *title, char *path) {
	Song *ptr_song = (Song*)malloc(sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title= title;
	ptr_song->path = path;

	ptr_song->index = num_index++;

	return ptr_song;
}

SNode *create_snode_instance(Song *ptr_song){
	SNode *ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;
	ptr_snode->song = ptr_song;
	
	return ptr_snode;
}

void insert_node(Artist *ptr_artist, SNode *ptr_snode) {
	SNode *p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0) {
		p = p->next;
	}
	//add ptr_snode before p

	if (ptr_artist->head == NULL) {  //empty list
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) { //at the front
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if (p == NULL) { //at the end
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else { //add before p
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}

}

void insert_to_index_directory(Song *ptr_song) {
	SNode *ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->prev = NULL; //unused
	ptr_snode->next = NULL;

	int index = ptr_song->index % SIZE_INDEX_TABLE;
	SNode *p = index_directory[index];
	SNode *q = NULL;
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {
		q = p;
		p = p->next;
	}

	if (q == NULL) { //add first
		ptr_snode->next = p;
		index_directory[index] = ptr_snode;
	}
	else {
		q->next = ptr_snode;
		ptr_snode->next = p;
	}
}

void add_song(char *artist, char *title, char*path) {
	// find if the artist already exists
	Artist *ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist);
	}

	//add the song to the artist pointed by ptr_artist
	Song *ptr_song = create_song_instance(ptr_artist, title, path);
	SNode *ptr_snode = create_snode_instance(ptr_song);

	//insert node 
	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}

void status() {
	for (int i = 0; i < NUM_CHARS; i++) {
		Artist *p = artist_directory[i];
		while (p!=NULL) {
			print_artist(p);
			p= p->next;
		}
	}
}

void print_artist(Artist *p) {
	SNode *ptr_snode = p->head;
	while (ptr_snode != NULL) {
		print_song(ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}
}

void print_song(Song *ptr_song) {
	printf("\t%d: %s, %s, %s\n", ptr_song->index, ptr_song->artist->name, ptr_song->title, ptr_song->path);
}

void search_song(char *name) {
	Artist *target = find_artist(name);
	if (target == NULL) {
		printf("There is no file about Artist %s\n", name);
	}
	else {
		printf("Found:\n");
		print_artist(target);
	}
}

void search_song(char *name, char *title) {
	Artist *target = find_artist(name);
	if (target == NULL) {
		printf("There is no file about Artist %s\n", name);
	}
	SNode *ptr_snode = find_snode(target, title);
	if (ptr_snode == NULL) {
		printf("No such song exists. \n");
	}
	else {
		printf("Found:\n");
		print_song(ptr_snode->song);
	}
}

SNode *find_snode(Artist *ptr_artist, char *title) {
	SNode *ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0) {
		ptr_snode = ptr_snode->next;
	}

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0) {
		return ptr_snode;
	}
	else {
		return NULL;
	}
}

SNode *find_song(int index) {
	SNode *ptr_snode = index_directory[index%SIZE_INDEX_TABLE];
	while (ptr_snode != NULL && ptr_snode->song->index != index)
		ptr_snode = ptr_snode->next;

	return ptr_snode;
}

void play(int index) {
	SNode *ptr_snode = find_song(index);
	if (ptr_snode == NULL) {
		printf("No such song exists.\n");
	}
	else {
		char buf1[5] = "open";
		if (ShellExecuteA(GetDesktopWindow(), buf1, (ptr_snode->song->path), NULL, NULL, SW_SHOW)) {
			printf("%s, %s is now playing.\n", ptr_snode->song->artist->name, ptr_snode->song->title);
		}
	}
}

void save(FILE *fp) {
	for (int i = 0; i < NUM_CHARS; i++) {
		Artist *ptr_artist = artist_directory[i];
		while (ptr_artist != NULL) {
			save_artist(fp, ptr_artist);
			ptr_artist = ptr_artist->next;
		}
	}
}

void save_artist(FILE *fp, Artist *ptr_artist) {
	SNode *ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL) {
		save_song(fp, ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}
}

void save_song(FILE *fp, Song *ptr_song) {
	if (ptr_song->artist->name != NULL) {
		fprintf(fp, "%s#", ptr_song->artist->name);
	}
	else {
		fprintf(fp, " #");
	}
	if (ptr_song->title!= NULL) {
		fprintf(fp, "%s#", ptr_song->title);
	}
	else {
		fprintf(fp, " #");
	}
	if (ptr_song->path != NULL) {
		fprintf(fp, "%s#\n", ptr_song->path);
	}
	else {
		fprintf(fp, " #\n");
	}
}

void remove(int index) {
	//find_song for one way linked list
	SNode *p = index_directory[index%SIZE_INDEX_TABLE];
	SNode *q = NULL;
	while (p != NULL && p->song->index != index) {
		q = p;
		p = p->next;
	}

	Song *ptr_song = p->song;

	if (p == NULL) { //either empty list or not exist
		printf("No such file having index(%d)\n", index);
		return;
	}
	else if (q == NULL) { //remove first
		index_directory[index%SIZE_INDEX_TABLE] = p->next;
	}
	else {//remove after q
		q->next = p->next;
	}
	free(p);

	Artist *ptr_artist = ptr_song->artist;
	//find the snode in the double linked list
	SNode *ptr_snode = find_snode(ptr_artist, ptr_song->title);
	if (ptr_snode == NULL) {
		printf("Not found snode - Error: someting wrong.\n");
		return;
	}
	remove_snode(ptr_artist, ptr_snode);
	remove_song(ptr_song);

	if (ptr_artist->head == NULL) {
		remove_artist(ptr_artist);
	}
}

void remove_artist(Artist *ptr_artist) {
	char *name = ptr_artist->name;
	Artist *p = artist_directory[(unsigned char)name[0]];
	Artist *q = NULL;
	while (p != NULL && strcmp(p->name, ptr_artist->name) <0) {
		q = p;
		p->next = q;
	}
	if (p == NULL) { //either empty list or not exist
		printf("No such Artist:%s --- ERROR. something is wrong\n", ptr_artist->name);
		return;
	}
	else if (q == NULL) { //remove first
		artist_directory[(unsigned char)name[0]] = p->next;
	}
	else {//remove after q
		q->next = p->next;
	}
	free(ptr_artist);
}

void remove_snode(Artist *ptr_artist, SNode *ptr_snode) {
	if (ptr_snode == ptr_artist->head && ptr_snode == ptr_artist->tail) { //remove unique node
		ptr_artist->head = NULL;
		ptr_artist->tail = NULL;
	}
	else if (ptr_snode == ptr_artist->head) { //remove frinst node
		ptr_artist->head = ptr_snode->next;
	}
	else if (ptr_snode == ptr_artist->tail) { //remove last node
		ptr_artist->tail = ptr_snode->prev;
	}
	else { //remove general node
		ptr_snode->prev->next = ptr_snode->next;
		ptr_snode->next->prev = ptr_snode->prev;
	}
	free(ptr_snode);
}

void remove_song(Song *ptr_song) {
	if (ptr_song->title != NULL)
		free(ptr_song->title);
	if (ptr_song->path != NULL)
		free(ptr_song->path);
	free(ptr_song);
}