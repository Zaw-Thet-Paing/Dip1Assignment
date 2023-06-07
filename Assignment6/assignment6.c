#include "stdio.h"
#include "stdlib.h"
#define SIZE 100

struct Worker{
    int id;
    char name[50];
    int age;
    char email[50];
    char password[50];
};

struct Worker info[SIZE];

int globalIndex = 0;
int eFound = -1;
int pFound = -1;
int eValid = -1;

void loadDataFromFile();
void printAllData();
void lobby();
void registration();
void login();
void recodingAllDataToFile();
int myStrCmp(char str1[50], char str2[50]);
void emailChecking(char email[50]);
void passChecking(char pass[50], int userIndex);
void userActionSector();
void validEmail(char email[50]);
int charCounting(char str[50]);

int main(){

    loadDataFromFile();
    printAllData();
    lobby();

    return 0;
}

void loadDataFromFile(){
    FILE *fptr = fopen("ass6DB.txt", "r");

    if(fptr == NULL){
        printf("Error: File Loading or No Data in File!\n");
    }else{
        for(int i = 0; i<SIZE; i++){
            fscanf(fptr, "%d%s%d%s%s", &info[i].id, &info[i].name, &info[i].age, &info[i].email, &info[i].password);

            if(info[i].name[0] == '\0'){
                break;
            }

            globalIndex++;

        }
    }
    fclose(fptr);
}

void printAllData(){
    for(int i = 0; i<globalIndex; i++){
        printf("ID: %d - Name: %s - Age: %d - Email: %s - Password: %s\n", info[i].id, info[i].name, info[i].age, info[i].email, info[i].password);
    }
    printf("\n");
}

void lobby(){
    int choice = 0;
    printf("This is Lobby Sector!\n");
    printf("Press 1 to Register:\n");
    printf("Press 2 to Login:\n");
    printf("Press 3 to Exit:");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            registration();
            break;
        case 2:
            login();
            break;
        case 3:
            recodingAllDataToFile();
            exit(1);
        default:
            printf("Invalid Option!\n");
            lobby();

    }
}

void registration(){

    char rEmail[50];

    printf("This is registration Sector!\n");
    printf("Enter your email : ");
    scanf(" %[^\n]", &rEmail);
    eValid = -1;
    validEmail(rEmail);

    if(eValid == 1){

        emailChecking(rEmail);
        if(eFound == -1){
            info[globalIndex].id = globalIndex+1;
            int sizeREmail = charCounting(rEmail);
            for(int i = 0; i<sizeREmail; i++){
                info[globalIndex].email[i] = rEmail[i];
            }
            printf("Enter your name : ");
            scanf(" %[^\n]", &info[globalIndex].name);
            printf("Enter your age : ");
            scanf("%d", &info[globalIndex].age);
            printf("Enter your password : ");
            scanf(" %[^\n]", &info[globalIndex].password);
            globalIndex++;
            lobby();
        }else{
            printf("Error: User Already Exist!\n");
            registration();
        }
    }else{
        printf("Error: Invalid Format! Only accept gmail to register!\n");
        registration();
    }
}

void login(){
    char lEmail[50];
    char lPassword[50];

    printf("This is login Sector!\n");
    printf("Enter your email to login: ");
    scanf(" %[^\n]", &lEmail);

    emailChecking(lEmail);

    printf("Enter your password: ");
    scanf(" %[^\n]", &lPassword);

    passChecking(lPassword, eFound);

    if(eFound != -1 && pFound == 1){
        userActionSector();

    }else{
        printf("Invalid: Email or Password! \n");
        login();
    }

}

void recodingAllDataToFile(){
    FILE *fptr = fopen("ass6DB.txt", "w");

    if(fptr == NULL){
        printf("Error: Recoding All Data To File!\n");
    }else{
        for(int i = 0; i<globalIndex; i++){
            fprintf(fptr, "%d\t%s\t%d\t%s\t%s\n", info[i].id, info[i].name, info[i].age, info[i].email, info[i].password);
        }
        printf("Recording all data to ass6DB.txt is complete!\n");
    }

    fclose(fptr);

}

int myStrCmp(char str1[50], char str2[50]){
    int i = 0;
    while(str1[i] && str2[i]){
        if(str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void emailChecking(char email[50]){
    int cmpResult = 0;
    eFound = -1;
    for(int i = 0; i<globalIndex; i++){
        cmpResult = myStrCmp(email, info[i].email);
        if(cmpResult == 0){
            eFound = i;
            break;
        }
    }
}

void passChecking(char pass[50], int userIndex){
    int cmpResult = 0;
    pFound = -1;
    cmpResult = myStrCmp(pass, info[userIndex].password);
    if(cmpResult == 0){
        pFound = 1;
    }
}

void userActionSector(){
    int userAction = 0;

    printf("Welcome Sir: %s\n",info[eFound].name);
    printf("Press 1 to User Action Sector:\n");
    printf("Press 2 to Home:\n");
    printf("Press 3 to Exit:");
    scanf(" %d",&userAction);

    switch(userAction){
        case 1:
            printf("This is user action sector:\n");
            break;
        case 2:
            login();
            break;
        case 3:
            recodingAllDataToFile();
            break;
        default:
            printf("Invalid option!\n");
            userActionSector();
    }
}

void validEmail(char email[50]){

    int eSize = charCounting(email);
    int at = 0;
    int atIndex = 0;
    char gmail[50] = "@gmail.com";
    char getGmail[50];
    int checkGmail = 0;
    eValid = -1;

    for(int i = 0; i<eSize; i++){
        if(email[i]=='@'){
            at++;
            atIndex = i;
            break;
        }
    }

    if(at == 1){
        int index = 0;
        for(int j = atIndex; j<eSize; j++){
            getGmail[index] = email[j];
            index++;
        }
        checkGmail = myStrCmp(gmail, getGmail);

        if(checkGmail == 0){
            eValid = 1;
        }else{
            eValid = -1;
        }
    }else{
        eValid = -1;
    }
}

int charCounting(char str[50]){
    int count = 0;

    for(int i = 0; i<50; i++){
        if(str[i] == '\0'){
            break;
        }else{
            count++;
        }
    }
    return count;
}