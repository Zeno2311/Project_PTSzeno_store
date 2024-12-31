#include <stdio.h>
#include <stdlib.h>
#include "function.h"
/* run this program using the console <Zeno> pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	do{
		lobbyMenu(choice);
		scanf("%d", &choice);
		switch(choice){
			case 1: // Admin Zeno
				//Dang nhap admin
				loginAd(userNameAD,passWordAD);
				fflush(stdin);
				fgets(userNameAD,sizeof(userNameAD),stdin);
				printf("\tPassword: ");
				fflush(stdin); // Zeno
				fgets(passWordAD,sizeof(passWordAD),stdin);
				printf("================================================\n");
				do{
					system("cls");
					lobbyMenuCTGR();
					scanf("%d", &choiceCategory);
					getchar(); // Zeno
					fflush(stdin);
					switch(choiceCategory){
						case 1:
							categoryMenu();
							exitMenu();
							break;
						case 2:
							categoryMenu();
							categoryMenu1();
							exitMenu();
							break;
						case 3:
							categoryMenu();
							categoryMenu2();
							exitMenu();
							break;
						case 4:
							do{
								// Lua chon cua admin
								system("cls");
								adminMenu(choiceAdmin);
								scanf("%d", &choiceAdmin);
								switch(choiceAdmin){
									case 1:
										viewProduct();
										exitMenu();
										break;
									case 2:
										viewProduct();
										addproduct();
										exitMenu();
										break;
									case 3: // Zeno
										viewProduct();
										editproduct();
										exitMenu();
										break;
									case 4: // Zeno
										viewProduct();
										deleteProduct();
										exitMenu();
										break;
									case 5:
										sortProducts();
										exitMenu();
										break;
									case 6:
										viewProduct();
										searchProducts();
										exitMenu();
										break;
									case 7:
										exitMenu();
										break;						
								}
							}while(choiceAdmin != 8);
							break;		
					}
				}while(choiceCategory != 5);
			case 2:
				break;
			case 3:
				break;				
		}
	}while(choice != 3);
	return 0;
}
