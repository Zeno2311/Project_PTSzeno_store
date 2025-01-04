#include "datatype.h"
// Nguyen ham giao dien sanh
void lobbyMenu(int choice);
void exitMenu(); // quay lai hoac tro ve man hinh chinh
void exitCategory(); // quay lai menu category

// 1.Admin
// Nguyen mau ham giao dien dang nhap tai khoan admin
void loginAd(char userNameAD, char passWordAD);
// Nguyen mau ham giao dien quan ly danh muc
void lobbyMenuCTGR();
void categoryMenu();
void categoryMenu1(); // them danh muc
void categoryMenu2(); // sua danh muc
void categoryMenu3(); // xoa danh muc
void categoryMenu4(); // tim kiem danh muc
void categoryMenu5(); // sap xep danh muc theo ten 
// Nguyen ham giao dien quan ly san pham cua admin
void adminMenu(int choiceAdmin);
void viewProduct(); // menu.01 hien thi cac san pham san co trong cua hang
void addproduct(); // menu.02 them san pham vao trong cua hang
void editproduct(); // menu.03 sua san pham trong cua hang
void deleteProduct(); // menu.04 xoa san pham trong cua hang
void sortProducts(); // menu.05 sap xep san pham trong cua hang
void searchProducts(); // menu.06 tim kiem san pham theo id 
// ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO

// 2.Client
void lobbyMenuCTRGclient();
void clientMenu(int choiceClient);

