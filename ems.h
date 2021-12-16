#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RD_FILE		\
	((fp = fopen("employeefile", "r")) == NULL)

#define WR_FILE 	\
	((fp = fopen("employeefile", "w")) == NULL)

#define APPEND_FILE \
	((fp = fopen("employeefile", "a")) == NULL)

FILE* fp;

typedef struct employee{
	size_t id;
	char first_name[100];
	char last_name [100];
	size_t salary;	
	struct employee* link;
}Employee;

enum option{
	ID = 1,
	F_NAME,
	L_NAME
};

typedef enum bool{
	false,
	true
}bool;

void create_file();
void load_file(Employee* hd); 
void init_record(Employee* hd);
void add();
void view(Employee* hd);
void search_option(Employee* hd);
void search(Employee* hd, const char option);
void modify(Employee* hd);
void delete(Employee* hd);
void main_menu(const char *msg, Employee* hd);
void print_header(const char* current_page);
