#include <stdbool.h>
// Khai bao cau truc du lieu tu dinh nghia
// Lua chon cua adim va nguoi dung
int choice, choiceCategory, choiceAdmin, choiceClient;
//Dang nhap tai khoan admin
char userNameAD[50];
char passWordAD[25];
typedef struct{
	int id;
	char nameProduct[50];
	char price[25];
	int quantity;
	char typeProduct[25];
}Product;
typedef struct{
	int id;
	char categoryProduct[50];
}Category;


