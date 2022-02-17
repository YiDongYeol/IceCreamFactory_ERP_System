#include "head.h"

void comp_add(int code, char name[COMP_NAME_LENGTH]) {
	company* new_comp;

	new_comp = (company*)malloc(sizeof(company));
	new_comp->code = code;
	strcpy(new_comp->name, name);
	new_comp->next = 0;
	comp_tail->next = new_comp;
	comp_tail = new_comp;

	comp_count++;
}
void emp_add(int code, char name[EMP_NAME_LENGTH]) {
	employee* new_emp;

	new_emp = (employee*)malloc(sizeof(employee));
	new_emp->code = code;
	strcpy(new_emp->name, name);
	new_emp->next = 0;
	emp_tail->next = new_emp;
	emp_tail = new_emp;

	emp_count++;
}
int Input_string(char* result, int str_size, int kor, int eng, int num, int sign, int space) {
	CONSOLE_SCREEN_BUFFER_INFO CUR_INFO;
	COORD Pos;
	int index = 0;
	int last_jump = 0;
	int delete_index = 0;
	int input_char;
	while (1) {
		input_char = _getch();
		switch (input_char) {
		case 13:
			printf("\n");
			return 1;
		case 8:
			if (index == 0)
				break;
			delete_index = 0;
			last_jump = 0;
			while (result[delete_index] != '\0') {
				if (result[delete_index] & 0x80) {
					last_jump = 2;
					delete_index += last_jump;
				}
				else {
					last_jump = 1;
					delete_index += last_jump;
				}
			}
			delete_index -= last_jump;
			result[delete_index] = '\0';
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CUR_INFO);
			if (last_jump == 2) {
				Pos.X = (CUR_INFO.dwCursorPosition.X) - 2; Pos.Y = CUR_INFO.dwCursorPosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				printf("  ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				index -= 2;
			}
			else {
				Pos.X = (CUR_INFO.dwCursorPosition.X) - 1; Pos.Y = CUR_INFO.dwCursorPosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				printf(" ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				index--;
			}
			break;
		case 27:
			result[0] = '\0';
			return 0;
		case 224:
		case 0:
			_getch();
			break;
		default:
			if (index == str_size)
				break;

			if (space && input_char == 32) {
				result[index++] = input_char;
				result[index] = '\0';
				printf("%c", result[index - 1]);
				break;
			}

			if (kor && (input_char & 0x80)) {
				if (index < (str_size - 2)) {
					result[index++] = input_char;
					input_char = _getch();
					result[index++] = input_char;
					result[index] = '\0';
					printf("%c%c", result[index - 2], result[index - 1]);
				}
				else {
					_getch();
				}
				break;
			}

			if (eng && ((input_char > 64 && input_char < 91) || (input_char > 96 && input_char < 123))) {
				result[index++] = input_char;
				result[index] = '\0';
				printf("%c", result[index - 1]);
				break;
			}

			if (num && (input_char > 47 && input_char < 58)) {
				result[index++] = input_char;
				result[index] = '\0';
				printf("%c", result[index - 1]);
				break;
			}

			if (sign && ((input_char > 32 && input_char < 48) || (input_char > 57 && input_char < 65) || (input_char > 90 && input_char < 97) || (input_char > 122 && input_char < 127))) {
				result[index++] = input_char;
				result[index] = '\0';
				printf("%c", result[index - 1]);
				break;
			}

		}
	}
}
int Menu_select(char* pre_input, char menu[][MENU_LENGTH], char* aft_input, int menu_count) {
	int input_char;
	int select = 1;
	CONSOLE_CURSOR_INFO cursorInfo = { 1, };
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	while (1) {
		system("cls");
		if (strcmp(pre_input, "\0"))
			printf("%s", pre_input);
		for (int i = 0; i < menu_count; i++) {
			if (select - 1 == i) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%d. %s\n", i + 1, menu[i]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
				printf("%d. %s\n", i + 1, menu[i]);
		}
		if (strcmp(aft_input, "\0"))
			printf("%s", aft_input);
		input_char = _getch();
		switch (input_char) {
		case 13:
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			return select;
		case 27:
			cursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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
				if (select == menu_count)
					break;
				else
					select++;
				break;
			case 75:
				select = 1;
				break;
			case 77:
				select = menu_count;
				break;
			}
			break;
		}
	}
}
int Input_date(char result[DATE_LENGTH], int mode) {
	CONSOLE_SCREEN_BUFFER_INFO CUR_INFO;
	COORD Pos;
	time_t ctime;
	struct tm* ctime_info;
	char input_char;
	int index = 0;
	switch (mode) {
	case 1:
		strcpy(result, "****/**/**");
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CUR_INFO);
		Pos.X = CUR_INFO.dwCursorPosition.X; Pos.Y = CUR_INFO.dwCursorPosition.Y;
		printf("%s", result);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		while (1) {
			input_char = _getch();
			switch (input_char) {
			case 13:
				if (index != 10)
					break;
				printf("\n");
				return 1;
			case 27:
				strcpy(result, "****/**/**");
				return 0;
			case 8:
				if (index == 0)
					break;
				if (index == 5 || index == 8) {
					index -= 2;
					result[index] = '*';
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CUR_INFO);
					Pos.X = CUR_INFO.dwCursorPosition.X - 2; Pos.Y = CUR_INFO.dwCursorPosition.Y;

				}
				else {
					result[--index] = '*';
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CUR_INFO);
					Pos.X = CUR_INFO.dwCursorPosition.X - 1; Pos.Y = CUR_INFO.dwCursorPosition.Y;
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				printf("*");
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CUR_INFO);
				Pos.X = CUR_INFO.dwCursorPosition.X - 1; Pos.Y = CUR_INFO.dwCursorPosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				break;
			default:
				if (index == 10)
					break;
				if (input_char > 47 && input_char < 58) {
					if (index == 5 && input_char > 49)
						break;
					if (index == 6 && result[5] == 49 && input_char > 50)
						break;
					if (index == 6 && result[5] == 48 && input_char == 48)
						break;
					if (index == 8) {
						char tmp[11];
						int month;
						strcpy(tmp, result);
						strtok(tmp, "/");
						month = atoi(strtok(NULL, "/"));
						if (input_char > 51)
							break;
						if (month == 2) {
							if (input_char > 50)
								break;
						}
					}
					if (index == 9) {
						char tmp[11];
						int year;
						int month;
						strcpy(tmp, result);
						year = atoi(strtok(tmp, "/"));
						month = atoi(strtok(NULL, "/"));
						if (result[8] == 48 && input_char == 48)
							break;
						if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
							if (result[8] == 51 && input_char > 49)
								break;
						}
						else if (month == 4 || month == 6 || month == 9 || month == 11) {
							if (result[8] == 51 && input_char > 48)
								break;
						}
						else if (month == 2) {
							int leap_year = 0;
							if (year % 4 == 0) {
								if (year % 100 == 0) {
									if (year % 400 == 0) {
										leap_year = 1;
									}
								}
								else
									leap_year = 1;
							}
							if (result[8] == 50) {
								if (leap_year == 0) {
									if (input_char > 56)
										break;
								}
							}
						}
					}
					result[index++] = input_char;
					printf("%c", result[index - 1]);
					if (index == 4 || index == 7) {
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CUR_INFO);
						Pos.X = CUR_INFO.dwCursorPosition.X + 1; Pos.Y = CUR_INFO.dwCursorPosition.Y;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
						index++;
					}
					break;
				}
			}
		}

	case 2:
		ctime = time(NULL);
		ctime_info = localtime(&ctime);
		sprintf(result, "%d/%02d/%02d", ctime_info->tm_year + 1900, ctime_info->tm_mon + 1, ctime_info->tm_mday);

		return -1;
	}
}
void gotoxy(int x, int y){
	COORD Pos;
	Pos.X = x; Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}