#include "head.h"

company* comp_select();
employee* emp_select();

int login() {
	company* comp_selected;
	employee* emp_selected;
	char PW[11];
	while (1) {
		gotoxy(0, 2);
		printf("                                             \n");
		printf("                                               ");
		gotoxy(0, 0);
		printf("ERP SYSTEM 제목\n\n");
		printf("회사 코드\n");
		printf("회사명\n");
		while (1) {
			if (_getch() == 27) return -1;
			comp_selected = comp_select();
			if (comp_selected != 0) {
				gotoxy(0, 2);
				printf("회사 코드 = %04d\n", comp_selected->code);
				printf("회사명 = %s\n\n", comp_selected->name);
				break;
			}
		}
		while (1) {
			gotoxy(0, 5);
			printf("                                             \n");
			printf("                                               ");
			gotoxy(0, 5);
			printf("사원 코드\n");
			printf("사원명\n");
			if (_getch() == 27) {
				gotoxy(0, 5);
				printf("                                             \n");
				printf("                                               ");
				comp_selected = 0;
				break;
			}
			emp_selected = emp_select();
			if (emp_selected != 0) {
				gotoxy(0, 5);
				printf("사원 코드 = %04d\n", emp_selected->code);
				printf("사원명 = %s\n\n", emp_selected->name);
				while (1) {
					gotoxy(0, 8);
					printf("                                 \n\n");
					printf("                                 ");
					gotoxy(0, 8);
					printf("패스워드 = ");
					if (Input_string(PW, 10, 0, 1, 1, 1, 0) == 0) {
						gotoxy(0, 8);
						printf("                                 ");
						break;
					}
					else {
						if (strcmp(PW, "system") == 0)		//수정필요
							return 1;
						else {
							printf("\n패스워드가 틀립니다.\n");
							_getch();
							continue;
						}
					}
				}
			}
			gotoxy(0, 7);
		}
	}
}

company* comp_select() {
	company* comp_cur=comp_head->next;
	int input_char;
	int select = 1;
	int select_pos_x = 50;
	int select_pos_y = 3;
	CONSOLE_CURSOR_INFO cursorInfo = { 1, };
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	gotoxy(select_pos_x, 0);
	printf("회사 리스트");
	gotoxy(select_pos_x, 2);
	printf("회사코드     회사명");
	while (1) {
		comp_cur = comp_head->next;
		for (int i = 0; i < comp_count; i++) {
			gotoxy(select_pos_x, select_pos_y+i);
			if (select - 1 == i) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%d. %04d  %s", i + 1, comp_cur->code, comp_cur->name);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
				printf("%d. %04d  %s", i + 1, comp_cur->code, comp_cur->name);
			comp_cur = comp_cur->next;
		}
		input_char = _getch();
		switch (input_char) {
		case 13:
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			comp_cur = comp_head->next;
			for (int i = 0; i < select - 1; i++)
				comp_cur = comp_cur->next;
			for (int i = 0; i < comp_count + select_pos_y; i++) {
				gotoxy(select_pos_x, i);
				printf("                                        ");
			}
			return comp_cur;
		case 27:
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			for (int i = 0; i < comp_count + select_pos_y; i++) {
				gotoxy(select_pos_x, i);
				printf("                                        ");
			}
			return 0;
		case 224:
			input_char = _getch();
			switch (input_char) {
			case 72:
				if (select == 1)
					break;
				else
					select--;
				break;
			case 80:
				if (select == comp_count)
					break;
				else
					select++;
				break;
			case 75:
				select = 1;
				break;
			case 77:
				select = comp_count;
				break;
			}
			break;
		}
	}
}
employee* emp_select() {
	employee* emp_cur = emp_head->next;
	int input_char;
	int select = 1;
	int select_pos_x = 50;
	int select_pos_y = 3;
	CONSOLE_CURSOR_INFO cursorInfo = { 1, };
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	gotoxy(select_pos_x, 0);
	printf("사원 리스트");
	gotoxy(select_pos_x, 2);
	printf("사원코드     사원명");
	while (1) {
		emp_cur = emp_head->next;
		for (int i = 0; i < emp_count; i++) {
			gotoxy(select_pos_x, select_pos_y + i);
			if (select - 1 == i) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%d. %04d  %s", i + 1, emp_cur->code, emp_cur->name);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
				printf("%d. %04d  %s", i + 1, emp_cur->code, emp_cur->name);
			emp_cur = emp_cur->next;
		}
		input_char = _getch();
		switch (input_char) {
		case 13:
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			emp_cur = emp_head->next;
			for (int i = 0; i < select - 1; i++)
				emp_cur = emp_cur->next;
			for (int i = 0; i < emp_count + select_pos_y; i++) {
				gotoxy(select_pos_x, i);
				printf("                                        ");
			}
			return emp_cur;
		case 27:
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			for (int i = 0; i < emp_count + select_pos_y; i++) {
				gotoxy(select_pos_x, i);
				printf("                                        ");
			}
			return 0;
		case 224:
			input_char = _getch();
			switch (input_char) {
			case 72:
				if (select == 1)
					break;
				else
					select--;
				break;
			case 80:
				if (select == emp_count)
					break;
				else
					select++;
				break;
			case 75:
				select = 1;
				break;
			case 77:
				select = emp_count;
				break;
			}
			break;
		}
	}
}
