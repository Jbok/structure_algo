#include "polynomial.h"
Polynomial *polys[MAXPOLYS];
int num = 0; //number of polynomials

Term *create_term_instance(int c, int e) {
	Term *temp = (Term*)malloc(sizeof(Term));
	temp->coef = c;
	temp->expo = e;
	return temp;
}

Polynomial *create_polynomial_instance(char name) {
	Polynomial *temp = (Polynomial*)malloc(sizeof(Polynomial));
	temp->name = name;
	temp->first = NULL;
	temp->size = 0;
	return temp;
}

Polynomial *create_by_add_two_polynomials(char x, char former, char later) {
	
	Polynomial *result = create_polynomial_instance(x);
	Polynomial *ptr_former = find_poly(former);
	Polynomial *ptr_later = find_poly(later);

	if (ptr_former != NULL && ptr_later != NULL) {
		Term *temp = ptr_former->first;
		while (temp != NULL) {
			add_term(temp->coef, temp->expo, result);
			temp = temp->next;
		}

		temp = ptr_later->first;
		while (temp != NULL) {
			add_term(temp->coef, temp->expo, result);
			temp = temp->next;
		}

		return result;
	}
	else {
		return NULL;
	}
}

Polynomial *create_by_parse_polynomials(char name, char *body) {
	Polynomial *ptr_poly = create_polynomial_instance(name);
	int i = 0, begin_term = 0;
	while (i < strlen(body)) {
		if (body[i] == '+' || body[i] == '-')
			i++;
		while (i < strlen(body) && body[i] != '+' && body[i] != '-')
			i++;
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);
		if (result == 0) {
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}

int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly) {
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;
	if (expr[i] == '+')
		i++;
	else if (expr[i] == '-') {
		sign_coef = -1;
		i++;
	}
	while (i < end && expr[i] >= '0' && expr[i] <= '9') {
		coef = coef * 10 + (int)(expr[i] - '0');
		i++;
	}

	if (coef == 0)
		coef = sign_coef;
	else
		coef *= sign_coef;

	if (i >= end) {
		add_term(coef, 0, p_poly);
		return 1;
	}

	if (expr[i] != 'x')
		return 0;
	i++;

	if (i >= end) {
		add_term(coef, 1, p_poly);
		return 1;
	}

	if (expr[i] != '^')
		return 0;
	i++;

	expo = 0;
	while (i < end && expr[i] >= '0' && expr[i] <= '9') {
		expo = expo * 10 + (int)(expr[i] - '0');
		i++;
	}

	add_term(coef, expo, p_poly);
	return 1;
}

void add_term(int c, int e, Polynomial *poly) {
	if (c == 0) {
		return;
	}
	Term *p= poly->first;
	Term *q = NULL;
	while (p!= NULL && (p->expo) > e) {
		q = p;
		p= p->next;
	}

	if (p!=NULL && (p->expo) == e) {
		p->coef += c;
		if (p->coef == 0) {
			if (q == NULL) {
				poly->first = p->next;
			}
			else {
				q->next = p->next;
			}
			poly->size--;
			free(p);
		}
		return;
	}
	else {
		Term *temp = create_term_instance(c, e);
		
		if (q == NULL) {
			temp->next = p;
			poly->first = temp;
		}
		else {
			temp->next = p;
			q->next = temp;
		}
		poly->size++;
		return;
	}
}

int eval(Term *term, int x) {
	int result = (term->coef);
	for (int i = 0; i < (term->expo); i++) {
		result *= x;
	}
	return result;
}

int eval(Polynomial *poly, int x) {
	int result = 0;
	Term *t = poly->first;
	while (t != NULL) {
		result += eval(t, x);
		t = t->next;
	}
	return result;
}

void print_poly(Polynomial *p) {
	Term *temp = p->first;
	printf("%c= ", p->name);
	while(temp != NULL) {
		print_term(temp);
		temp = temp->next;
		if (temp != NULL && (temp->coef)>0) {
			printf("+");
		}
	}
	printf("\n");
}

void print_term(Term *pTerm) {
	if (pTerm->expo == 0) {
		printf("%d", pTerm->coef);
	}
	else {
		printf("%dx^%d", pTerm->coef, pTerm->expo);
	}
	
}

Polynomial *find_poly(char x) {
	for (int i = 0; i < num; i++) {
		if ((polys[i]->name) == x) {
			return polys[i];
		}
	}
	return NULL;
}

void handle_print(char x) {
	Polynomial *temp;
	temp = find_poly(x);
	if (temp == NULL) {
		printf("There is no polynomial about %c\n", x);
	}
	else {
		print_poly(temp);
	}
}

void handle_calc(char x, char *arg2) {
	Polynomial *temp;
	temp = find_poly(x);
	if (temp == NULL) {
		printf("There is no polynomial about %c\n", x);
	}
	else {
		int value = atoi(arg2);
		printf("result: %d\n", eval(temp, value));
	}
}

void erase_blanks(char **expression) {
	char *temp = (char*)malloc(sizeof(char)*strlen(*expression));
	int length = 0;
	for (int i = 0; i < strlen(*expression); i++) {
		if ((*expression)[i] != ' ') {
			temp[length++] = (*expression)[i];
		}
	}
	temp[length] = '\0';
	*expression = temp;
}

void handle_definition(char *str) {
	
	erase_blanks(&str);
	char *f_name = strtok(str, "=");
	if (f_name == NULL || strlen(f_name) != 1) {
		printf("Unsupported command.\n");
		return;
	}

	char *exp_body = strtok(NULL, "=");
	if (exp_body == NULL || strlen(exp_body) <= 0) {
		printf("Invalid expression format.\n");
		return;
	}

	if (exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x') {
		char *former = strtok(exp_body, "+");
		if (former == NULL || strlen(former) != 1) {
			printf("Inavalid expression format.\n");
			return;
		}
		char *later = strtok(NULL, "+");
		if (later == NULL || strlen(later) != 1) {
			printf("Invalid expression format.\n");
			return;
		}
		Polynomial *pol = create_by_add_two_polynomials(f_name[0], former[0], later[0]);
		if (pol == NULL) {
			printf("Invalid expression format.\n");
			return;
		}
		insert_polynomial(pol);
	}
	else {
		Polynomial *pol = create_by_parse_polynomials(f_name[0], exp_body);
		if (pol == NULL) {
			printf("Invalid expression format.\n");
			return;
		}
		insert_polynomial(pol);
	}
}

void polynomial_process_command() {
	char commnad_line[BUFFER_LENGTH];
	char *command, *arg1, *arg2;

	while (1) {
		printf("$ ");
		if (read_line(stdin, commnad_line, BUFFER_LENGTH) <= 0) {
			continue;
		}
		char temp[BUFFER_LENGTH];
		strcpy(temp, commnad_line);
		command = strtok(commnad_line, " ");
		if (strcmp(command, "print") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments. \m");
				continue;
			}
			handle_print(arg1[0]);
		}
		else if (strcmp(command, "calc") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_calc(arg1[0], arg2);
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			handle_definition(temp);
		}
	}
}

void insert_polynomial(Polynomial *ptr_poly) {
	for (int i = 0; i < num; i++) {
		if (polys[i]->name == ptr_poly->name) {
			destroy_polynomial(polys[i]);
			polys[i] = ptr_poly;
			return;
		}
	}
	polys[num++] = ptr_poly;
}

void destroy_polynomial(Polynomial *ptr_poly) {
	if (ptr_poly == NULL) {
		return;
	}
	Term *t = ptr_poly->first, *tmp;
	while (t != NULL) {
		tmp = t;
		t = t->next;
		free(tmp);
	}
	free(ptr_poly);
}