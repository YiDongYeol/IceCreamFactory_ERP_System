#include "head.h"

int main_menu() {
	char menu_list[5][MENU_LENGTH];
	char pre_print[] = "ERP SYSTEM 力格\n\n";
	char after_print[] = "\0";
	strcpy(menu_list[0], "前格包府");
	strcpy(menu_list[1], "积魂拌裙");
	strcpy(menu_list[2], "积魂角利炼雀");
	return Menu_select(pre_print,menu_list,after_print,3);
}