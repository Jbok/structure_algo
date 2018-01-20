#pragma once
#ifndef __MUSICLIBRARY_H__
#define __MUSICLIBRARY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

struct song {
	Artist *artist;
	char *title;
	char *path;
	int index;
};
struct snode {
	SNode *next, *prev;
	Song *song;
};
struct artist {
	char *name;
	Artist *next;
	SNode *head, *tail;
};

void initialize();
void load(FILE *fp);
Artist *find_artist(char *name);
Artist *create_artist_instance(char *name);
Artist *add_artist(char *name);
Song *create_song_instance(Artist *ptr_artist, char *title, char *path);
SNode *create_snode_instance(Song *ptr_song);
void insert_node(Artist *ptr_artist, SNode *ptr_snode);
void add_song(char *artist, char *title, char*path);
void status();
void print_artist(Artist *p);
void print_song(Song *ptr_song);
#endif