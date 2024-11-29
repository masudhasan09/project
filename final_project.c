
#include <stdio.h>                                      
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_USERS 10
#define MAX_PRODUCT_TYPES 10

#define FILENAME_PRODUCTS "products.txt"
#define FILENAME_USERS "users.txt"
#define FILENAME_PRODUCT_TYPES "product-types.txt"
// Structures
struct ProductType {
    char typeName[50];
};
struct Product {
    char name[50];
    float quantity;
    float price;
    struct ProductType type;
};
struct User {
    char username[50];
    char password[50];
};

// Function prototypes
void displayMenu();
void displayMainMenu();
void registerUser(struct User users[], int *userCount);
int  loginUser(struct User users[], int userCount);

void addProduct(struct Product products[],int *count, struct ProductType productTypes[], int typeCount);
void displayProducts(struct Product products[],int count);
void updateProduct(struct Product products[],int count, struct ProductType productTypes[], int typeCount);
void deleteProduct(struct Product products[],int *count);
void searchProduct(struct Product products[], int count);


void uploadProducts(struct Product products[], int count);
void downloadProducts(struct Product products[], int *count);

void addProductType(struct ProductType productTypes[], int *typeCount);
void displayProductTypes(struct ProductType productTypes[], int typeCount);

void readProducts(struct Product products[], int *count);
void writeProducts(struct Product products[], int count);

void readUsers(struct User users[], int *userCount);
void writeUsers(struct User users[], int userCount);

void readProductTypes(struct ProductType productTypes[], int *typeCount);
void writeProductTypes(struct ProductType productTypes[], int typeCount);

int main() {
    struct Product products[MAX_PRODUCTS];
    struct User users[MAX_USERS];
    struct ProductType productTypes[MAX_PRODUCT_TYPES];
    int productCount = 0;
    int userCount = 0;
    int typeCount = 0;
    int loggedIn = 0;

    // Read data from files
    readProducts(products, &productCount);
    readUsers(users, &userCount);
    readProductTypes(productTypes, &typeCount);

    char choice;
    //login menu for admin
    do {
        if (!loggedIn) {
            displayMainMenu();
            printf("Enter your choice: ");
            scanf(" %c", &choice);
            printf("\n");

            switch (choice) {
                case '1':
                    registerUser(users, &userCount);
                    break;
                case '2':
                    loggedIn = loginUser(users, userCount);
                    break;
                case '0':
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            //display menu for admin
            displayMenu();
            printf("Enter your choice: ");
            scanf(" %c", &choice);
            printf("\n");

            switch (choice) {
                case '1':
                    addProductType(productTypes, &typeCount);
                    
                    break;
                case '2':
                    addProduct(products, &productCount, productTypes, typeCount);
                    
                    break;
                case '3':
                    displayProducts(products, productCount);
                    
                    break;
                case '4':
                    displayProductTypes(productTypes, typeCount);

                    break;
                case '5':
                    
                    updateProduct(products, productCount, productTypes, typeCount);
                    break;
                case '6':
                    deleteProduct(products, &productCount);

                    break;
                case '7':
                   
                    searchProduct(products, productCount);
                    break;
                case '8':
                   uploadProducts(products, productCount);

                    break;
                case '9':
                    downloadProducts(products, &productCount);

                    break;
              
                case 'A':
                    loggedIn = 0;
                    printf("Logged out successfully.\n");
                    break;
                case '0':
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } while (choice != '0');

    // Write data to files before exiting
    writeProducts(products, productCount);
    writeUsers(users, userCount);
    writeProductTypes(productTypes, typeCount);

    return 0;
}

void displayMainMenu() {
    printf("============= Welcome to Super Shop Management System ============= \n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("0. Exit\n");
    printf("-------------------------------------------------------------------\n");
    
}

void displayMenu() {
    printf("================ Super Shop Management System ================\n");
    printf("1. Add Product Type\n");
    printf("2. Add Product\n");
    printf("3. Display Products\n");
    printf("4. Display Product Types\n");
    printf("5. Update Product\n");
    printf("6. Delete Product\n");
    printf("7. Search Product\n");
    printf("8. Upload Data to File\n");
    printf("9. Download Data from File\n");
    printf("A. Logout\n");
    printf("0. Exit\n");
    printf("------------------------------------------------------------\n");
}
//admin registertion function
void registerUser(struct User users[], int *userCount) {
    if (*userCount >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("============== Register ==============\n");
    printf("Enter username: ");
    scanf("%s", users[*userCount].username);
    printf("Enter password: ");
    scanf("%s", users[*userCount].password);

    (*userCount)++;
    writeUsers(users, *userCount);
    printf("Registration successful. Please log in.\n");
}

int loginUser(struct User users[], int userCount) {
    char username[50];
    char password[50];
    int loggedIn = 0;

    printf("============== Login ==============\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            loggedIn = 1;
            printf("Login successful. Welcome, %s!\n", username);
            break;
        }
    }

    if (!loggedIn) {
        printf("Invalid username or password. Please try again.\n");
    }

    return loggedIn;
}

void addProduct(struct Product products[], int *count, struct ProductType productTypes[], int typeCount) {
    printf("============== Add Product ==============\n");
    if (*count == MAX_PRODUCTS) {
        printf("Maximum product limit reached. Cannot add more products.\n");
        return;

    }

    printf("Enter product name: ");
    scanf("%s", products[*count].name);
    printf("Enter product quantity: ");
    scanf("%f", &products[*count].quantity);
    printf("Enter product price: ");
    scanf("%f", &products[*count].price);
    
    if (typeCount > 0) {
        printf("Available Product Types:\n");
        for (int i = 0; i < typeCount; i++) {
            printf("%d. %s\n", i + 1, productTypes[i].typeName);
        }
        int typeChoice;
        printf("Choose product type (1-%d): ", typeCount);
        scanf("%d", &typeChoice);
        if (typeChoice >= 1 && typeChoice <= typeCount) {
            products[*count].type = productTypes[typeChoice - 1];
        } else {
            printf("Invalid choice. Setting type to 'Unknown'.\n");
            strcpy(products[*count].type.typeName, "Unknown");
        }
    } else {
        printf("No product types available. Setting type to 'Unknown'.\n");
        strcpy(products[*count].type.typeName, "Unknown");
    }

    printf("Product added successfully.\n");
    (*count)++;
}

void displayProducts(struct Product products[], int count) {
    printf("============== Product List ==============\n");
    printf("%-13s%-10.2f%-10.2f%-10.2s\n","Name","Quantity","Price","Type");
    for (int i = 0; i < count; i++) {
        printf("%-13s%-10.2f%-10.2f%-10.2s\n", products[i].name, products[i].quantity, products[i].price, products[i].type.typeName);
    }
}

void updateProduct(struct Product products[], int count, struct ProductType productTypes[], int typeCount) {
    printf("============== Update Product ==============\n");
    char name[50];
    int found = 0;

    printf("Enter the name of the product to update: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(name, products[i].name) == 0) {
            printf("Enter new quantity: ");
            scanf("%f", &products[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &products[i].price);
            found = 1;

            if (typeCount > 0) {
                printf("Available Product Types:\n");
                for (int j = 0; j < typeCount; j++) {
                    printf("%d. %s\n", j + 1, productTypes[j].typeName);
                }
                int typeChoice;
                printf("Choose product type (1-%d): ", typeCount);
                scanf("%d", &typeChoice);
                if (typeChoice >= 1 && typeChoice <= typeCount) {
                    products[i].type = productTypes[typeChoice - 1];
                } else {
                    printf("Invalid choice. Setting type to 'Unknown'.\n");
                    strcpy(products[i].type.typeName, "Unknown");
                }
            } else {
                printf("No product types available. Setting type to 'Unknown'.\n");
                strcpy(products[i].type.typeName, "Unknown");
            }

            printf("Product details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void deleteProduct(struct Product products[], int *count) {
    printf("============== Delete Product ==============\n");
    char name[50];
    int found = 0;

    printf("Enter the name of the product to delete: ");
    scanf("%s", name);

    for (int i = 0; i < *count; i++) {
        if (strcmp(name, products[i].name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                products[j] = products[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Product deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void searchProduct(struct Product products[], int count) {
    printf("============== Search Product ==============\n");
    char name[50];
    int found = 0;

    printf("Enter the name of the product to search: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(name, products[i].name) == 0) {
            printf("Product found!\n");
            printf("Name: %s\n", products[i].name);
            printf("Quantity: %.2f\n", products[i].quantity);
            printf("Price: %.2f\n", products[i].price);
            printf("Type: %s\n", products[i].type.typeName);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void uploadProducts(struct Product products[], int count) {
    printf("============== Upload Data to File ==============\n");
    writeProducts(products, count);
    printf("Data uploaded successfully.\n");
}

void downloadProducts(struct Product products[], int *count) {
    printf("============== Download Data from File ==============\n");
    readProducts(products, count);
    printf("Data downloaded successfully.\n");
}

void addProductType(struct ProductType productTypes[], int *typeCount) {
    //product type limit check
    if (*typeCount >= MAX_PRODUCT_TYPES) {
        printf("Product type limit reached. Cannot add more types.\n");
        return;
    }

    printf("============== Add Product Type ==============\n");
    printf("Enter product type name: \n");
    scanf("%s", productTypes[*typeCount].typeName);
    //total product type
    (*typeCount)++;
    writeProductTypes(productTypes, *typeCount);
    printf("Product type added successfully.\n");
}

void displayProductTypes(struct ProductType productTypes[], int typeCount) {
    printf("============== Product Types ==============\n");
    for (int i = 0; i < typeCount; i++) {
        printf("%d. %s\n", i + 1, productTypes[i].typeName);
    }
}

void readProducts(struct Product products[], int *count) {
    //open file to read products data
    FILE *file = fopen(FILENAME_PRODUCTS, "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    while(fscanf(file, "%-13s%-10.2f%-10.2f%-10.2s", products[*count].name, &products[*count].quantity, &products[*count].price, products[*count].type.typeName) != EOF) {
        (*count)++;
    }

    fclose(file);
}

void writeProducts(struct Product products[], int count) {
    //open file to write products data
    FILE *file = fopen(FILENAME_PRODUCTS, "w");
    if (file == NULL) {
        printf("Error writing to file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%-13s%-10.2f%-10.2f%-10.2s\n", products[i].name, products[i].quantity, products[i].price, products[i].type.typeName);
    }

    fclose(file);
}

void readUsers(struct User users[], int *userCount) {
    //open file to read user data
    FILE *file = fopen(FILENAME_USERS, "r");
    if (file == NULL) {
        *userCount = 0;
        return;
    }

    *userCount = 0;
    while (fscanf(file, "%s %s", users[*userCount].username, users[*userCount].password) != EOF) {
        (*userCount)++;
    }

    fclose(file);
}

void writeUsers(struct User users[], int userCount) {
    //open file to write user data
    FILE *file = fopen(FILENAME_USERS, "w");
    if (file == NULL) {
        printf("Error writing to file.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

void readProductTypes(struct ProductType productTypes[], int *typeCount) {
    //open file to read Product Types data
    FILE *file = fopen(FILENAME_PRODUCT_TYPES, "r");
    if (file == NULL) {
        *typeCount = 0;
        return;
    }

    *typeCount = 0;
    while (fscanf(file, "%s", productTypes[*typeCount].typeName) != EOF) {
        (*typeCount)++;
    }

    fclose(file);
}

void writeProductTypes(struct ProductType productTypes[], int typeCount) {
    //opening file to write Product Types Data
    FILE *file = fopen(FILENAME_PRODUCT_TYPES, "w");
    if (file == NULL) {
        printf("Error writing to file.\n");
        return;
    }

    for (int i = 0; i < typeCount; i++) {
        fprintf(file, "%s\n", productTypes[i].typeName);
    }

    fclose(file);
}
