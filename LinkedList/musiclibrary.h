#pragma once
#ifndef __MUSICLIBRARY_H__
#define __MUSICLIBRARY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <tchar.h>

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
void insert_to_index_directory(Song *ptr_song);
void add_song(char *artist, char *title, char*path);
void status();
void print_artist(Artist *p);
void print_song(Song *ptr_song);
void search_song(char *name);
void search_song(char *name, char *title);
SNode *find_snode(Artist *ptr_artist, char *title);
void play(int index);
void save(FILE *fp);
void save_artist(FILE *fp, Artist *ptr_artist);
void save_song(FILE *fp, Song *ptr_song);
void remove(int index);
void remove_snode(Artist *ptr_artist, SNode *ptr_snode);
void remove_song(Song *song);
#endif