#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXPOLYS 100
#define BUFFER_LENGTH 100

struct term {
	int coef;
	int expo;
	struct term *next;
};
typedef struct term Term;

struct polynomial {
	char name;
	Term *first;
	int size;
};
typedef struct polynomial Polynomial;


Term *create_term_instance(int c, int e);
Polynomial *create_polynomial_instance(char name);
Polynomial *create_by_add_two_polynomials(char x, char former, char later);
Polynomial *create_by_parse_polynomials(char name, char *body);
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly);
void add_term(int c, int e, Polynomial *poly);
int eval(Term *term, int x);
int eval(Polynomial *poly, int x);
void print_poly(Polynomial *p);
void print_term(Term *pTerm);
int read_line(FILE *fp, char *str, int max_length);
Polynomial *find_poly(char x);
void handle_print(char x);
void handle_calc(char x, char *arg2);
void erase_blanks(char **expression);
void handle_definition(char *str);
void polynomial_process_command();
void insert_polynomial(Polynomial *ptr_poly);
void destroy_polynomial(Polynomial *ptr_poly);

#endif