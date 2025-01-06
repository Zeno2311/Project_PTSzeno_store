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
// Giao dien man hinh danh muc cua client
void lobbyMenuCTRGclient(){
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\t CHOOSE YOUR ROLE\n");
	printf("\t======================================\n");
	printf("\t[1].Print Category.\n");
	printf("\t[2].Search Category.\n");
	printf("\t[3].Sort By Name.\n");
	printf("\t[4].Access detailed store information.\n");
	printf("\t======================================\n");
	printf("\tEnter The Choice: ");
}
//Giao dien man hinh danh muc cua admin
void lobbyMenuCTGR(){
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\t CHOOSE YOUR ROLE\n");
	printf("\t======================================\n");
	printf("\t[1].Print Category.\n");
	printf("\t[2].Add Category.\n");
	printf("\t[3].Repair Category.\n");
	printf("\t[4].Delete Category.\n");
	printf("\t[5].Search Category.\n");
	printf("\t[6].Sort By Name.\n");
	printf("\t[7].Access detailed store information.\n");
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
        return;
    }
    Category view2[50];
    int n;
    printf("Enter the quantity of categories you want to add:\n");
    scanf("%d", &n);
    getchar();
    // Kiem tra thong tin nhap vao
    for(int i = 0; i < n; i++){
        int valid = 0;
        while (!valid){
            printf("*Enter category information*\n");
            // id danh muc
            printf("ID: ");
            scanf("%d", &view2[i].id);
            getchar();
            //Kiem tra xem co bi trung lap id hay khong
            FILE *checkFile = fopen("category.dat", "rb");
            if (checkFile != NULL){
                Category existingCategory;
                int idExists = 0;
                while (fread(&existingCategory, sizeof(Category), 1, checkFile)){
                    if (existingCategory.id == view2[i].id){
                        idExists = 1;
                        break;
                    }
                }
                fclose(checkFile);
                if (idExists){
                    printf("This ID already exists. Please enter a different ID.\n");
                    continue;
                }
            }
            // Ten danh muc moi
            printf("Name Category: ");
            fgets(view2[i].categoryProduct, sizeof(view2[i].categoryProduct), stdin);
            view2[i].categoryProduct[strcspn(view2[i].categoryProduct, "\n")] = '\0';
            // Kiem tra ten danh muc
            if (strlen(view2[i].categoryProduct) == 0) {
                printf("Category name cannot be empty. Please enter a valid category name.\n");
                continue;
            }
            // Kiem tra moi co bi trung voi danh muc cu hay khong
            checkFile = fopen("category.dat", "rb");
            if (checkFile != NULL) {
                Category existingCategory;
                int nameExists = 0;
                while (fread(&existingCategory, sizeof(Category), 1, checkFile)) {
                    if (strcasecmp(existingCategory.categoryProduct, view2[i].categoryProduct) == 0) {
                        nameExists = 1;
                        break;
                    }
                }
                fclose(checkFile);
                if (nameExists) {
                    printf("This category name already exists. Please enter a different name.\n");
                    continue;
                }
            }
            // Neu du lieu hop le thoat vong lap
            valid = 1;
        }
    }
    // Ghi du lieu vua nhap vao file
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
    // Tinh so luong danh muc co trong file
    fseek(ptr, 0, SEEK_END);
    int totalCategory = ftell(ptr) / sizeof(Category);
    fseek(ptr, 0, SEEK_SET);
    // Kiem tra admin muon sua san pham o vi tri nao
    printf("If you want to edit a category, please enter the ID (1 -> %d): ", totalCategory);
    scanf("%d", &addEdit);
    getchar();
    while (addEdit < 1 || addEdit > totalCategory){
        printf("Invalid ID. Please enter a valid ID (1 -> %d): ", totalCategory);
        scanf("%d", &addEdit);
    }
    // Sua danh muc
    printf("\n*In the process of category update*\n");
    // Kiem tra ID danh muc nhap vao co hop le
    printf("New Id category: ");
    scanf("%d", &edit.id);
    getchar(); // To consume the newline left by scanf
    while (edit.id < 1) { // Dam bao ID phai lon hon 0
        printf("Invalid ID. Please enter a valid ID: ");
        scanf("%d", &edit.id);
        getchar();
    }
    // Kiem tra ten danh muc nhap vao khong trong va khong trung voi ten da co
    int isValidName = 0;
    while (!isValidName) {
        printf("New Name category: ");
        fgets(edit.categoryProduct, sizeof(edit.categoryProduct), stdin);
        edit.categoryProduct[strcspn(edit.categoryProduct, "\n")] = '\0'; // Xoa ky tu '\n' sau khi nhap
        // Kiem tra ten danh muc khong trong
        if (strlen(edit.categoryProduct) == 0) {
            printf("Category name cannot be empty. Please enter again.\n");
            continue;
        }
        // Kiem tra ten danh muc co bi trung khong
        fseek(ptr, 0, SEEK_SET);
        isValidName = 1;
        Category temp;
        while (fread(&temp, sizeof(Category), 1, ptr)) {
            if (strcasecmp(temp.categoryProduct, edit.categoryProduct) == 0 && temp.id != edit.id) {
                printf("Category name already exists. Please choose a different name.\n");
                isValidName = 0;
                break;
            }
        }
        // Neu ten hop le, thoat vong lap
        if (isValidName) {
            break;
        }
    }
    // Luu danh muc vao file
    fseek(ptr, (addEdit - 1) * sizeof(Category), SEEK_SET);
    fwrite(&edit, sizeof(Category), 1, ptr);
    // Dong file
    fclose(ptr);
    printf("\nUpdated Successfully !!!\n");
}
void categoryMenu3(){ // menu.3 xoa danh muc
	int dltCategory;
	int yesNo;
    FILE *ptr = fopen("category.dat", "rb");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return;
    }
    // Tinh tong so luong danh muc co trong file luu tru
    fseek(ptr, 0, SEEK_END);
    int totalCategory = ftell(ptr) / sizeof(Category);
    fseek(ptr, 0, SEEK_SET);
    if(totalCategory == 0){
        printf("No products to delete.\n");
        fclose(ptr);
        return;
    }
    // Nhap ID cua danh muc can xoa theo yeu cau cua admin
    printf("If you want to delete a category, please enter the ID (1 to %d): ", totalCategory);
    scanf("%d", &dltCategory);
    while(dltCategory < 1 || dltCategory > totalCategory){
        printf("Invalid ID. Please enter a valid ID (1 to %d): ", totalCategory);
        scanf("%d", &dltCategory);
    }
	printf("\nDo you want to remove this category from the list?\n");
	printf("Yes(1)? or No(2)?: ");
	scanf("%d", &yesNo);
	getchar();
	if(yesNo == 1){
		// Cap phat bo nho de luu tru tat ca cac danh muc hien co
	    Category *categorys = (Category *)malloc(totalCategory * sizeof(Category));
	    if(categorys == NULL){
	        printf("Memory allocation failed.\n");
	        fclose(ptr);
	        return;
	    }
	    // Doc tat ca cac danh muc trong tep
	    fread(categorys, sizeof(Category), totalCategory, ptr);
	    fclose(ptr);
	    // Xoa danh muc duoc chon tu yeu cau cua admin
	    for(int i = dltCategory - 1; i < totalCategory - 1; i++){
	        categorys[i] = categorys[i + 1];
	    }
	    // Hien thi file sau khi da xoa theo yeu cau
	     printf("\n*** Updated Category List ***\n");
	     printf("\t*=======|=======================*\n");
		 printf("\t|  ID 	|       Category        |\n");
		 printf("\t|=======|=======================|\n");
		 for(int i = 0; i < totalCategory - 1; i++){
			printf("\t| %-5d | %-21s |\n",
				categorys[i].id,
				categorys[i].categoryProduct);
			printf("\t|-------|-----------------------|\n");
		}
		printf("\t*=======|=======================*\n");
		// luu lai vao file
		ptr = fopen("category.dat", "wb");
	    if(ptr == NULL){
	        printf("Error opening file for writing.\n");
	        free(categorys);
	        return;
	    }
	    fwrite(categorys, sizeof(Category), totalCategory - 1, ptr);
	    fclose(ptr);
	    printf("\nCategory ID %d deleted successfully!\n", dltCategory);
	    // Giai phong bo nho cap phat da cap nhap
	    free(categorys);
	}
	if(yesNo == 2){
		printf("You have canceled the request.\n");
	}
}
void categoryMenu4(){ // Tim kiem theo ten danh muc
	char nameCheck[50]; 
	    FILE *ptr = fopen("category.dat", "rb");
	    if (ptr == NULL) {
	        printf("Error opening file.\n");
	        return;
	    }
	   // Tinh tong so luong danh muc co trong file
	    fseek(ptr, 0, SEEK_END);
	    int totalCategory = ftell(ptr) / sizeof(Category);
	    fseek(ptr, 0, SEEK_SET);
	    if (totalCategory == 0) {
	        printf("No products to search.\n");
	        fclose(ptr);
	        return;
	    }
	    // Cap phat bo nho dong de luu tru danh muc
	    Category *categories = (Category *)malloc(totalCategory * sizeof(Category));
	    if (categories == NULL) {
	        printf("Memory allocation failed.\n");
	        fclose(ptr);
	        return;
	    }
	    // Doc file vao bo nho luu tru tam thoi
	    fread(categories, sizeof(Category), totalCategory, ptr);
	    fclose(ptr);
	    // Yeu cau nguoi dung nhap ten danh muc can tim
	    do {
	        printf("Enter to search: "); 
	        fgets(nameCheck, sizeof(nameCheck), stdin);
	        nameCheck[strcspn(nameCheck, "\n")] = '\0'; 
	        fflush(stdin);
	    } while (strlen(nameCheck) < 1);
	
	    // Tim kiem danh muc co 2 ki tu dau giong nhau
	    int found = 0;
	    for (int i = 0; i < totalCategory; i++) {
	        if (strncasecmp(categories[i].categoryProduct, nameCheck, 2) == 0) {
	            if (found == 0) {
	                printf("\n *** Categories matching the first three characters '%s' ***\n", nameCheck);
	                printf("\t*=======|=======================*\n");
	                printf("\t|  ID 	|       Category        |\n");
	                printf("\t|=======|=======================|\n");
	            }
	            found++;
	            printf("\t| %-5d | %-21s |\n",
	                   categories[i].id,
	                   categories[i].categoryProduct);
	            printf("\t|-------|-----------------------|\n");
	        }
	    }
	
	    if (found > 0) {
	        printf("\t*=======|=======================*\n");
	    } else {
	        printf("No categories found with the first three characters '%s'.\n", nameCheck);
	    }
	
	    // Gia phong bo nho cap phat dong
	    free(categories);
}
void categoryMenu5(){ // sap xep danh muc theo ten
	FILE *ptr = fopen("category.dat", "rb");
	if(ptr == NULL){
	printf("Error opening file.\n");
	}
	// Tinh tong so luong danh muc co trong file luu tru
    fseek(ptr, 0, SEEK_END);
    int totalCategory = ftell(ptr) / sizeof(Category);
    fseek(ptr, 0, SEEK_SET);
    if(totalCategory == 0){
        printf("No products to search.\n");
        fclose(ptr);
        return;
    }
	// Cap phat bo nho de luu tru thong tin san pham
    Category *categorys = (Category *)malloc(totalCategory * sizeof(Category));
    if (categorys == NULL) {
        printf("Memory allocation failed.\n");
        fclose(ptr);
        return;
    }
    // Doc file vao bo nho luu tru tam thoi
    fread(categorys, sizeof(Category), totalCategory, ptr);
    fclose(ptr);
    // Sap xep theo ten
    int compareCategoryByName(const void *a, const void *b){
    const Category *catA = (const Category *)a;
    const Category *catB = (const Category *)b;
    return strcmp(catA->categoryProduct, catB->categoryProduct);
	}
    qsort(categorys, totalCategory, sizeof(Category), compareCategoryByName);
    printf("\n\t      *** Category Product ***\n");
	printf("\t*=======|=======================*\n");
	printf("\t|  ID 	|       Category        |\n");
	printf("\t|=======|=======================|\n");
	for(int i = 0; i < totalCategory; i++){
    	printf("\t| %-5d | %-21s |\n",
		categorys[i].id,
		categorys[i].categoryProduct);
		printf("\t|-------|-----------------------|\n");
	}
	printf("\t*=======|=======================*\n");
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
// Giao dien nguoi dung
void clientMenu(int choiceClient){
	printf("*** ZenoQ Convenience store management system ***\n");
	printf("\n\t\tProduct Management\n");
	printf("================================================\n");
	printf("[1].View product categories available in store\n"); // hien cac san pham dang co trong cua hang
	printf("[2].Sort products.\n"); // sap xep san pham
	printf("[3].Search for products.\n"); //Tim kiem san pham
	printf("================================================\n");
	printf("Enter The Choice: ");
}
//********************************Zeno***********************************//
void viewFullproduct(){
	FILE *ptr = fopen("product.dat","rb");
	if(ptr == NULL){
	printf("Error opening file.\n");
	}
	Product view;
	//in bang thong bao san pham 
	printf("\t*** ZenoQ Convenience store management system ***\n");
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
//****************************************Zeno***************************//
void viewProduct() { // In san pham theo yeu cau cua nguoi dung
    char category[50];
    printf("Enter the category to view products: ");
    fflush(stdin);
    if (fgets(category, sizeof(category), stdin)) {
        category[strcspn(category, "\n")] = '\0'; // Remove newline character
    }

    FILE *ptr = fopen("product.dat", "rb");
    if (ptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Product view;
    int found = 0;

    printf("\t*** ZenoQ Convenience Store Management System ***\n");
    printf("*=======|===========================|===============|=============*\n");
    printf("|  ID   |       Product Name        |      Price    |   Quantity  |\n");
    printf("|=======|===========================|===============|=============|\n");

    while (fread(&view, sizeof(Product), 1, ptr) != NULL) {
        if (strcasecmp(view.typeProduct, category) == 0) {
            printf("| %5d | %-25s | %-13s | %11d |\n",
                view.id,
                view.nameProduct,
                view.price,
                view.quantity);
            printf("|-------|---------------------------|---------------|-------------|\n");
            found = 1;
        }
    }

    if (!found) {
        printf("| No products found in category: %-25s |\n", category);
        printf("|-------|---------------------------|---------------|-------------|\n");
    }

    printf("*=======|===========================|===============|=============*\n");

    fclose(ptr);
}
//********************************************************Zeno***********//
void addproduct() { // menu.02 them san pham vao trong cua hang
    FILE *ptr = fopen("product.dat", "ab+");
    if (ptr == NULL) {
        printf("Error opening file.\n");
        return;
    }
    Product add[50];
    int n;
    printf("Enter the quantity of products you want to add:\n");
    scanf("%d", &n);
    getchar();
    Product temp; // Khai bao temp o day de dung chung
    for (int i = 0; i < n; i++) {
        printf("*Enter product information*\n");
        // Kiem tra ID khong bi trung lap
        int isValidID = 0;
        while (!isValidID) {
            printf("ID: ");
            scanf("%d", &add[i].id);
            getchar();
            while (add[i].id < 1) { // Kiem tra ID hop le
                printf("Invalid ID. Please enter a valid ID: ");
                scanf("%d", &add[i].id);
                getchar();
            }
            // Kiem tra ID trung lap
            isValidID = 1; // Mac dinh la hop le
            fseek(ptr, 0, SEEK_SET);
            while (fread(&temp, sizeof(Product), 1, ptr)) {
                if (temp.id == add[i].id) {
                    printf("ID already exists. Please enter a different ID.\n");
                    isValidID = 0;
                    break;
                }
            }
        }
        // Ten san pham
        printf("Name Product: ");
        fgets(add[i].nameProduct, sizeof(add[i].nameProduct), stdin);
        add[i].nameProduct[strcspn(add[i].nameProduct, "\n")] = '\0';
        fflush(stdin);
        while (strlen(add[i].nameProduct) == 0) { // Kiem tra ten san pham khong duoc rong
            printf("Product name cannot be empty. Please enter again: ");
            fgets(add[i].nameProduct, sizeof(add[i].nameProduct), stdin);
            add[i].nameProduct[strcspn(add[i].nameProduct, "\n")] = '\0';
        }
        // Kiem tra ten san pham khong bi trung
        fseek(ptr, 0, SEEK_SET);
        int isValidName = 1;
        while (fread(&temp, sizeof(Product), 1, ptr)) {
            if (strcasecmp(temp.nameProduct, add[i].nameProduct) == 0) {
                printf("Product name already exists. Please choose a different name.\n");
                isValidName = 0;
                break;
            }
        }
        if (!isValidName) {
            i--; // De yeu cau nhap lai thong tin san pham hien tai
            continue;
        }
        // Gia san pham
        printf("Product price: ");
        fgets(add[i].price, sizeof(add[i].price), stdin);
        add[i].price[strcspn(add[i].price, "\n")] = '\0';
        fflush(stdin);
        while (strlen(add[i].price) == 0) { // Kiem tra gia san pham khong duoc rong
            printf("Product price cannot be empty. Please enter again: ");
            fgets(add[i].price, sizeof(add[i].price), stdin);
            add[i].price[strcspn(add[i].price, "\n")] = '\0';
        }
        // So luong san pham
        printf("Number of products: ");
        scanf("%d", &add[i].quantity);
        getchar();
        while (add[i].quantity < 1) { // Kiem tra so luong san pham hop le
            printf("Quantity must be greater than 0. Please enter again: ");
            scanf("%d", &add[i].quantity);
            getchar();
        }
        // Loai san pham
        printf("Product Type: ");
        fgets(add[i].typeProduct, sizeof(add[i].typeProduct), stdin);
        add[i].typeProduct[strcspn(add[i].typeProduct, "\n")] = '\0';
        fflush(stdin);
        while (strlen(add[i].typeProduct) == 0) { // Kiem tra loai san pham khong duoc rong
            printf("Product type cannot be empty. Please enter again: ");
            fgets(add[i].typeProduct, sizeof(add[i].typeProduct), stdin);
            add[i].typeProduct[strcspn(add[i].typeProduct, "\n")] = '\0';
        }
    }
    // Luu tat ca vao file
    fwrite(add, sizeof(Product), n, ptr);
    printf("\nProducts have been added successfully.\n");
    // Dong file
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
    // Tinh so luong san pham co trong file
    fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(Product);
    fseek(ptr, 0, SEEK_SET);
    // Kiem tra admin muon sua san pham o vi tri nao
    printf("If you want to edit a product, please enter the ID: ");
    scanf("%d", &addEdit);
    while (addEdit < 1 || addEdit > totalProducts){
        printf("Invalid ID. Please enter a valid ID (1 to %d): ", totalProducts);
        scanf("%d", &addEdit);
    }
    // In ra man hinh san pham do luc chua sua
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
    // Sua san pham
    printf("\n*In the process of product repair*\n");
    getchar();
    // Kiem tra ten san pham khong duoc rong
    printf("New product name: ");
    fgets(edit.nameProduct, sizeof(edit.nameProduct), stdin);
    edit.nameProduct[strcspn(edit.nameProduct, "\n")] = '\0';
    while (strlen(edit.nameProduct) == 0) { // Kiem tra ten san pham khong duoc rong
        printf("Product name cannot be empty. Please enter again: ");
        fgets(edit.nameProduct, sizeof(edit.nameProduct), stdin);
        edit.nameProduct[strcspn(edit.nameProduct, "\n")] = '\0';
    }
    // Kiem tra ten san pham khong bi trung
    fseek(ptr, 0, SEEK_SET);
    int isValidName = 1;
    Product temp;
    while (fread(&temp, sizeof(Product), 1, ptr)) {
        if (strcmp(temp.nameProduct, edit.nameProduct) == 0 && temp.id != edit.id) {
            printf("Product name already exists. Please choose a different name.\n");
            isValidName = 0;
            break;
        }
    }
    if (!isValidName) {
        printf("Edit failed due to duplicate product name.\n");
        fclose(ptr);
        return;
    }
    // Loai san pham
    printf("Product Type: ");
    fgets(edit.typeProduct, sizeof(edit.typeProduct), stdin);
    edit.typeProduct[strcspn(edit.typeProduct, "\n")] = '\0';
    // Kiem tra gia san pham khong duoc rong
    printf("Product Price: ");
    fgets(edit.price, sizeof(edit.price), stdin);
    edit.price[strcspn(edit.price, "\n")] = '\0';
    while (strlen(edit.price) == 0) { // Kiem tra gia san pham khong duoc rong
        printf("Product price cannot be empty. Please enter again: ");
        fgets(edit.price, sizeof(edit.price), stdin);
        edit.price[strcspn(edit.price, "\n")] = '\0';
    }
    // So luong san pham
    printf("Number of products: ");
    scanf("%d", &edit.quantity);
    getchar();
    while (edit.quantity < 1) { // Kiem tra so luong san pham hop le
        printf("Quantity must be greater than 0. Please enter again: ");
        scanf("%d", &edit.quantity);
        getchar();
    }
    // Luu vao san pham vao file
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
    int compareProductByName(const void *a, const void *b){
    const Product *catA = (const Product *)a;
    const Product *catB = (const Product *)b;
    return strcmp(catA->nameProduct, catB->nameProduct);
	}
    qsort(products, totalProducts, sizeof(Product), compareProductByName);
    printf("\nProducts sorted by Name Product (A -> Z).\n");
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
void searchProducts(){ // menu.06 tim kiem san pham theo ten
    char searchName[50]; // khai bao bien de luu ten san pham
    int fake = 0;
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
    // Nhap ten san pham
    printf("What product do you want to find? Please enter product name: ");
    getchar(); 
    fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = 0;

    // nguoi dung phai nhap it nhat 3 ki tu 
    if (strlen(searchName) >= 3) {
        for(int i = 0; i < totalProducts; i++){
            if(strncasecmp(products[i].nameProduct, searchName, 3) == 0){ // So sanh 3 ky tu dau
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
            }
        }
        if(fake == 0){
            printf("No product found with the first three characters you entered.\n");
        }
    } else {
        // Neu nguoi dung nhap day du ten muon tim
        for(int i = 0; i < totalProducts; i++){
            if(strcmp(products[i].nameProduct, searchName) == 0){ // So sanh ten san pham
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
            printf("No product found with the name you entered.\n");
        }
    }
}

//***************************Zeno****************************************//
void exitMenu(){ // quay lai hoac tro ve man hinh chinh
	int choiceMenu;
	printf("Go back(b)? or Exit(0)?: ");
	scanf("%d", &choiceMenu);
	getchar();
	if(choiceMenu == 'b'){
		printf(" ");
	}
	if(choiceMenu == 0){
		choiceCategory = 7;
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
