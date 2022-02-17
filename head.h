#pragma once

#define COMP_NAME_LENGTH 21
#define EMP_NAME_LENGTH 21
#define SUBJ_NAME_LENGTH 11
#define MENU_LENGTH 21
#define DATE_LENGTH 11
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

typedef struct company {
	int code;
	char name[COMP_NAME_LENGTH];
	struct company* next;
}company;
typedef struct employee {
	int code;
	char name[EMP_NAME_LENGTH];
	struct employee* next;
}employee;
typedef struct subject {
	int code;
	char name[SUBJ_NAME_LENGTH];
}subject;

company* comp_head;
company* comp_tail;
employee* emp_head;
employee* emp_tail;

int comp_count;
int emp_count;

int login();
int main_menu();

void comp_add(int code, char name[COMP_NAME_LENGTH]);
void emp_add(int code, char name[EMP_NAME_LENGTH]);
int Input_string(char* result, int str_size, int kor, int eng, int num, int sign, int space);
int Menu_select(char* pre_input, char menu[][MENU_LENGTH], char* aft_input, int menu_count);
int Input_date(char result[DATE_LENGTH], int mode);
void gotoxy(int x, int y);