#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//logic ham
//*******************************************Zeno************************//
// Giao dien man hinh chinh
void lobbyMenu(int choice){
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\t CHOOSE YOUR ROLE\n");
	printf("\t\t==================\n");
	printf("\t\t[1].Admin\n");
	printf("\t\t[2].Client.\n");
	printf("\t\t[3].Exit.\n");
	printf("\t\t==================\n");
	printf("\t\tEnter The Choice: ");
}
//******************************Zeno*************************************//
// Giao dien dang nhap tai khoan admin
void loginAd(char userNameAD, char passWordAD){
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\t LOGIN ADMIN\n");
	printf("================================================\n");
	printf("\tEmail: ");
}
//**********Zeno*********************************************************//
//Giao dien man hinh danh muc
void lobbyMenuCTGR(){
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\t CHOOSE YOUR ROLE\n");
	printf("\t======================================\n");
	printf("\t[1].Print Category.\n");
	printf("\t[2].Add Category.\n");
	printf("\t[3].Repair Category.\n");
	printf("\t[4].Access detailed store information.\n");
	printf("\t======================================\n");
	printf("\tEnter The Choice: ");
}
void categoryMenu(){ //menu.0 in ra danh muc
	FILE *ptr = fopen("category.dat","rb");
	if(ptr == NULL){
	printf("Error opening file.\n");
	}
	Category view1;
	printf("\n\t      *** Category Product ***\n");
	printf("\t*=======|=======================*\n");
	printf("\t|  ID 	|       Category        |\n");
	printf("\t|=======|=======================|\n");
	while( fread(&view1, sizeof(Category), 1, ptr) != NULL ){
		printf("\t| %-5d | %-21s |\n",
		view1.id,
		view1.categoryProduct);
		printf("\t|-------|-----------------------|\n");
	}
	printf("\t*=======|=======================*\n");
	//Dong file
	fclose(ptr);
}
void categoryMenu1(){ // menu.1 them danh muc
	FILE *ptr = fopen("category.dat","ab+");
	if(ptr == NULL){
		printf("Error opening file.\n");
	}
	Category view2[50];
	int n;
	printf("Enter the quantity of category you want to add:\n");
	scanf("%d", &n);
	getchar();
	for (int i=0; i<n; i++){
		printf("*Enter category information*\n");
		// id san pham
		printf("ID: ");
		scanf("%d", &view2[i].id);
		getchar();
		// ten danh muc
		printf("Name Category: ");
		fgets(view2[i].categoryProduct, sizeof(view2[i].categoryProduct), stdin);
		view2[i].categoryProduct[strcspn(view2[i].categoryProduct,"\n")] = '\0';
		fflush(stdin);
	}
	fwrite(view2, sizeof(Category), n, ptr);
	// Dong file
	fclose(ptr);
}
void categoryMenu2(){ // menu.2 sua danh muc
	int addEdit;
	Category edit;
	FILE *ptr = fopen("category.dat", "rb+");
	if(ptr == NULL){
	printf("Error opening file.\n");
	return;
	}
	// tinh so luong danh muc co trong file
	fseek(ptr, 0, SEEK_END);
    int totalCategory = ftell(ptr) / sizeof(Category);
    fseek(ptr, 0, SEEK_SET);
	// kiem tra admin muon sua san pham o vi tri nao
	printf("If you want to edit a category, please enter the ID (1 -> %d): ", totalCategory);
	scanf("%d", &addEdit);
	getchar();
	while (addEdit < 1 || addEdit > totalCategory){
        printf("Invalid ID. Please enter a valid ID (1 -> %d): ", totalCategory);
        scanf("%d", &addEdit);
    }
    // sua danh muc
	printf("\n*In the process of product repair*\n");
//	printf("New Id category: ");
//	scanf("%d", &edit.id);
//	getchar();
    printf("New Name category: ");
    fgets(edit.categoryProduct, sizeof(edit.categoryProduct), stdin);
	edit.categoryProduct[strcspn(edit.categoryProduct, "\n")] = '\0';
	fflush(stdin);
	// luu vao san pham vao file
	fseek(ptr, (addEdit - 1) * sizeof(Category), SEEK_SET);
	fwrite(&edit, sizeof(Category), 1, ptr);
	// Dong file
	fclose(ptr);
	printf("\nUpdated Successfully !!!\n");
}
//
//
// ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO ZENO
//
// Menu con thuc hien thao tac cua admin
//
// Giao dien quan ly san pham cua admin
void adminMenu(int choiceAdmin){ //menu sanh lua chon cua admin
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\tProduct Management\n");
	printf("================================================\n");
	printf("[1].View product categories available in store\n"); // hien cac san pham dang co trong cua hang
	printf("[2].Add product.\n"); // them san pham
	printf("[3].Product repair.\n"); // sua san pham
	printf("[4].Delete product.\n"); // xoa san pham 
	printf("[5].Sort products.\n"); // sap xep san pham
	printf("[6].Search for products.\n"); //Tim kiem san pham
	printf("================================================\n");
	printf("Enter The Choice: ");
}
//****************************************Zeno***************************//
void viewProduct(){ // menu.01 in san pham hien co ra man hinh
	FILE *ptr = fopen("product.dat","rb");
	if(ptr == NULL){
	printf("Error opening file.\n");
	}
	Product view;
	//in bang thong bao san pham 
	printf("*=======|===========================|===============|=============*\n");
	printf("|  ID 	|       Name Product        |     Price     |   Quantity  |\n");
	printf("|=======|===========================|===============|=============|\n");
	while( fread(&view, sizeof(Product), 1, ptr) != NULL ){
		printf("| %5d | %-25s | %13s | %11d |\n",
			view.id,
			view.nameProduct,
			view.price,
			view.quantity);
		printf("|-------|---------------------------|---------------|-------------|\n");	
	}
	printf("*=======|===========================|===============|=============*\n");
	// Dong  file
	fclose(ptr);
}
//********************************************************Zeno***********//
void addproduct(){ // menu.02 them san pham vao trong cua hang
	FILE *ptr = fopen("product.dat","ab+");
	if(ptr == NULL){
	printf("Error opening file.\n");
	return;
	}
	Product add[50];
	int n;
	printf("Enter the quantity of products you want to add:\n");
	scanf("%d", &n);
	getchar();
	for (int i=0; i<n; i++){
		printf("*Enter product information*\n");
		// id san pham
		printf("ID: ");
		scanf("%d", &add[i].id);
		getchar();
		// ten san pham
		printf("Name Product: ");
		fgets(add[i].nameProduct, sizeof(add[i].nameProduct), stdin);
		add[i].nameProduct[strcspn(add[i].nameProduct,"\n")] = '\0';
		fflush(stdin);
//		// loai san pham
//		printf("Product Type: ");
//		fgets(add[i].typeProduct, sizeof(add[i].typeProduct), stdin);
//		add[i].typeProduct[strcspn(add[i].typeProduct,"\n")] = '\0';
//		fflush(stdin);
		// gia san pham
		printf("Product price: ");
		fgets(add[i].price, sizeof(add[i].price), stdin);
		add[i].price[strcspn(add[i].price,"\n")] = '\0';
		fflush(stdin);
		// so luong san pham
		printf("Number of products: ");
		scanf("%d", &add[i].quantity);
		getchar();
	}
	fwrite(add, sizeof(Product), n, ptr);
	printf("\nProducts have been added successfully.\n");
	//Dong file
	fclose(ptr);
	printf("\nUpdated Successfully !!!\n");
}
//*******************************************Zeno************************//
void editproduct(){ // menu.03 sua san pham theo id san pham
	int addEdit;
	Product edit;
	FILE *ptr = fopen("product.dat", "rb+");
	if(ptr == NULL){
	printf("Error opening file.\n");
	return;
	}
	// tinh so luong san pham co trong file
	fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(Product);
    fseek(ptr, 0, SEEK_SET);
	// kiem tra admin muon sua san pham o vi tri nao
	printf("If you want to edit a product, please enter the ID: ");
	scanf("%d", &addEdit);
	while (addEdit < 1 || addEdit > totalProducts){
        printf("Invalid ID. Please enter a valid ID (1 to %d): ", totalProducts);
        scanf("%d", &addEdit);
    }
	// in ra man hinh san pham do luc chua sua
	printf("\nCurrent product details:\n"); 
	fseek(ptr, (addEdit - 1) * sizeof(Product), SEEK_SET);
    fread(&edit, sizeof(Product), 1, ptr);
	printf("*=======|===========================|===============|=============*\n");
	printf("|  ID 	|       Name Product        |     Price     |   Quantity  |\n");
	printf("|=======|===========================|===============|=============|\n");
	printf("| %5d | %-25s | %13s | %11d |\n",
		edit.id,
		edit.nameProduct,
		
		edit.price,
		edit.quantity);
	printf("*=======|===========================|===============|=============*\n");
	// sua san pham
	printf("\n*In the process of product repair*\n");
	getchar();
	printf("New product name: ");
	fgets(edit.nameProduct, sizeof(edit.nameProduct), stdin);
	edit.nameProduct[strcspn(edit.nameProduct, "\n")] = '\0';
	fflush(stdin);
//	printf("Product Type: ");
//	fgets(edit.typeProduct, sizeof(edit.typeProduct), stdin);
//	edit.typeProduct[strcspn(edit.typeProduct, "\n")] = '\0';
//	fflush(stdin);
	printf("Product Price: ");
	fgets(edit.price, sizeof(edit.price), stdin);
	edit.price[strcspn(edit.price, "\n")] = '\0';
	fflush(stdin);
	printf("Number of products: ");
	scanf("%d", &edit.quantity);
	getchar();
	// luu vao san pham vao file
	fseek(ptr, (addEdit - 1) * sizeof(Product), SEEK_SET);
	fwrite(&edit, sizeof(Product), 1, ptr);
	// Dong file
	fclose(ptr);
	printf("\nUpdated Successfully !!!\n");
}
//***********************************************Zeno********************//
void deleteProduct(){ // menu.04 xoa san pham khoi ke hang
	int dltproduct;
    FILE *ptr = fopen("product.dat", "rb");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return;
    }
    // Tinh tong so luong san pham co trong file luu tru
    fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(Product);
    fseek(ptr, 0, SEEK_SET);
    if(totalProducts == 0){
        printf("No products to delete.\n");
        fclose(ptr);
        return;
    }
    // Nhap ID cua san pham can xoa theo yeu cau cua admin
    printf("If you want to delete a product, please enter the ID (1 to %d): ", totalProducts);
    scanf("%d", &dltproduct);
    while(dltproduct < 1 || dltproduct > totalProducts){
        printf("Invalid ID. Please enter a valid ID (1 to %d): ", totalProducts);
        scanf("%d", &dltproduct);
    }
    // Cap phat bo nho de luu tru tat ca cac san pham
    Product *products = (Product *)malloc(totalProducts * sizeof(Product));
    if(products == NULL){
        printf("Memory allocation failed.\n");
        fclose(ptr);
        return;
    }
    // Doc tat ca cac san pham trong tep
    fread(products, sizeof(Product), totalProducts, ptr);
    fclose(ptr);
    // Xoa san pham duoc chon tu yeu cau cua admin
    for(int i = dltproduct - 1; i < totalProducts - 1; i++){
        products[i] = products[i + 1];
    }
    // Hien thi file sau khi da xoa theo yeu cau 
    printf("\n*** Updated Product List ***\n");
	printf("*=======|===========================|===============|=============*\n");
	printf("|  ID 	|       Name Product        |     Price     |   Quantity  |\n");
	printf("|=======|===========================|===============|=============|\n");
    for (int i = 0; i < totalProducts - 1; i++) {
        printf("| %5d | %-25s | %13s | %11d |\n",
               products[i].id,
               products[i].nameProduct,
              
               products[i].price,
               products[i].quantity);
        printf("|-------|---------------------------|---------------|-------------|\n");
    }
    printf("*=======|===========================|===============|=============*\n");
    // Ghi danh sach san pham da cap nhat tro lai tep
    ptr = fopen("product.dat", "wb");
    if(ptr == NULL){
        printf("Error opening file for writing.\n");
        free(products);
        return;
    }
    fwrite(products, sizeof(Product), totalProducts - 1, ptr);
    fclose(ptr);
    printf("\nProduct ID %d deleted successfully!\n", dltproduct);
    // Giai phong bo nho cap phat da cap nhap
    free(products);
}
//******************Zeno*************************************************//
void sortProducts(){ // menu.05 sap xep san pham trong cua hang
	FILE *ptr = fopen("product.dat", "rb");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return;
    }
    // Kiem tra so luong san pham dang co trong file
    fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(Product);
    fseek(ptr, 0, SEEK_SET);
    if (totalProducts == 0) {
        printf("No products to sort.\n");
        fclose(ptr);
        return;
    }
    // Cap phat bo nho de luu tru thong tin san pham
    Product *products = (Product *)malloc(totalProducts * sizeof(Product));
    if (products == NULL) {
        printf("Memory allocation failed.\n");
        fclose(ptr);
        return;
    }
    // Doc file vao bo nho luu tru tam thoi
    fread(products, sizeof(Product), totalProducts, ptr);
    fclose(ptr);
    // Sap xep san pham theo gia tien
    int compareByPrice(const void *a, const void *b){
	    int priceA = atoi(((Product *)a)->price);
	    int priceB = atoi(((Product *)b)->price);
	    return priceA - priceB;
	}
    qsort(products, totalProducts, sizeof(Product), compareByPrice);
    printf("\nProducts sorted by Price (Low to High).\n");
	// Hien thi san pham sau khi thuc hien sap xep theo yeu cau
    printf("\n*** Sorted Product List ***\n");
	printf("*=======|===========================|===============|=============*\n");
	printf("|  ID 	|       Name Product        |     Price     |   Quantity  |\n");
	printf("|=======|===========================|===============|=============|\n");
    for (int i = 0; i < totalProducts; i++) {
        printf("| %5d | %-25s | %13s | %11d |\n",
               products[i].id,
               products[i].nameProduct,
              
               products[i].price,
               products[i].quantity);
        printf("|-------|---------------------------|---------------|-------------|\n");
    }
    printf("*=======|===========================|===============|=============*\n");
    // Luu lai vao tep 
//    ptr = fopen("product.dat", "wb");
//    if(ptr == NULL){
//        printf("Error opening file for writing.\n");
//        free(products);
//        return;
//    }
//    if(fwrite(products, sizeof(Product), totalProducts, ptr) != totalProducts){
//        printf("Error writing to file.\n");
//    }else{
//        printf("\nProducts have been successfully sorted and saved.\n");
//    }
//    fclose(ptr);
    // Giai phong bo nho cap phat luu tru tam thoi
    free(products);
}
//***************************************Zeno****************************//
void searchProducts(){ // menu.06 tim kiem san pham theo id 
	int numcheck;
	FILE *ptr = fopen("product.dat", "rb");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return;
    }
    // Tinh tong so luong san pham co trong file luu tru
    fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(Product);
    fseek(ptr, 0, SEEK_SET);
    if(totalProducts == 0){
        printf("No products to search.\n");
        fclose(ptr);
        return;
    }
    // Cap phat bo nho de luu tru thong tin san pham
    Product *products = (Product *)malloc(totalProducts * sizeof(Product));
    if (products == NULL) {
        printf("Memory allocation failed.\n");
        fclose(ptr);
        return;
    }
    // Doc file vao bo nho luu tru tam thoi
    fread(products, sizeof(Product), totalProducts, ptr);
    fclose(ptr);
    // Tim kiem san pham theo id
    printf("What product do you want to find? Please enter product id (1 to %d): ", totalProducts);
    scanf("%d", &numcheck);
    int fake = 0;
    for(int i = 0; i < totalProducts; i++){
    	if(products[i].id == numcheck){
    		fake++;
	    	printf("\n*** Product information you are looking for ***\n");
			printf("*=======|===========================|===============|=============*\n");
			printf("|  ID 	|       Name Product        |     Price     |   Quantity  |\n");
			printf("|=======|===========================|===============|=============|\n");
		    printf("| %5d | %-25s | %13s | %11d |\n",
	               products[i].id,
	               products[i].nameProduct,
	               
	               products[i].price,
	               products[i].quantity);
		    printf("*=======|===========================|===============|=============*\n");
		    break;
		}
	}
	if(fake == 0){
        printf("No product found with the ID you entered.\n");
    }
}
//***************************Zeno****************************************//
void exitMenu(){ // quay lai hoac tro ve man hinh chinh
	int choiceMenu;
	printf("Go back(b)? or Exit(0)?: ");
	scanf("%d", &choiceMenu);
	getchar();
	if(choiceMenu == 'b'){
		printf("Go back to menu.\n");
	}
	if(choiceMenu == 0){
		choiceCategory = 5;
		choiceAdmin = 7;
		system("cls");
	}
	if(choiceAdmin == 7){
		exitCategory();
	}
}
void exitCategory(){ //tro lai menu category
	system("cls");
	lobbyMenuCTGR();
	scanf("%d", &choiceCategory);
	getchar(); // Zeno
	fflush(stdin);
}
