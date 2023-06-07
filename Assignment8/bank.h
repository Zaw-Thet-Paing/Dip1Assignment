/*
###############################################
#       Assignment 8 Using My Own Project     #
###############################################
Assignment 8 is phone validation, password validation and login function
 I use pin validation instead of password Validation
*/
#include "stdio.h"
#include "stdlib.h"
#define SIZE 100

struct transaction{
    char note[100];
};

struct information{
    int id;
    char name[50];
    char phone_number[15];
    char nrc[25];
    char dob[15];
    char gender[8];
    unsigned int pin;
    struct transaction trans[50];
};

struct information db[100];

//global variables
int users = 0;
int space_array[100];
int pValid = -1; //phone valid
int pExist = -1; //phone exist
int strCmp = -1;
int pinValid = -1;

//function declaration
void welcome();
void login();
void registration();
void loadingAllDataFromFile();
void printAllInfo();
void space_counter();
void recording_allData_toFile();
void phone_validation(char ph[15]);
int str_len(char str[50]);
void phone_exist_checking(char ph[15]);
void my_str_cmp(char first[50], char second[50]);
int int_len(unsigned int number);
void pin_validation(unsigned int pin);
void my_str_cpy(char first[100], char second[100]);

void welcome(){
    int option = 0;

    space_counter();
    loadingAllDataFromFile();
    printAllInfo();
    printf("***************************\n");
    printf("**********WavePay**********\n");
    printf("***************************\n\n");
    printf("Press 1 to Register\nPress 2 to Login\nPress 0 to Exit\n\n");
    printf("Enter your choice : ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            registration();
            break;
        case 2:
            login();
            break;
        case 0:
            recording_allData_toFile();
            exit(0);
        default:
            printf("Invalid Choice!\n\n");
            welcome();

    }

}

void login(){
    char l_phone[15];
    unsigned int l_pin;

    while(pValid == -1){
        printf("This is login page\n");
        printf("Enter your phone number : ");
        scanf(" %[^\n]", l_phone);
        printf("Enter your pin : ");
        scanf("%u", &l_pin);

        phone_exist_checking(l_phone);

        if(l_pin == db[pExist].pin){
            pValid = 1;
        }

        if(pValid == -1){
            pValid = -1;
            printf("Your login credential was wrong:\n");
        }

    }

    printf("Welcome %s\n", db[pExist].name);
}

void registration(){
    char re_name[50];
    char re_phone_number[15];
    char re_nrc[25];
    char re_dob[15];
    char re_gender[8];
    unsigned int re_pin = 0;

    printf("WavePay Registration Page\n");
    printf("You can only use telenor, ooredoo, mytel and mpt:\n");
    printf("Enter your phone number (09XXXXXXXXX) : ");
    scanf(" %[^\n]", &re_phone_number[0]);
    pValid = -1;
    phone_validation(re_phone_number);
    if(pValid != -1){
        pExist = -1;
        phone_exist_checking(re_phone_number);
        if(pExist == -1){
            printf("Enter your name : ");
            scanf(" %[^\n]", re_name);
            printf("Enter your nrc : ");
            scanf(" %[^\n]", re_nrc);
            printf("Enter your dateOfBirth (DD-MM-YYYY) : ");
            scanf(" %[^\n]", re_dob);
            printf("Enter your gender (Male/Female) : ");
            scanf(" %[^\n]", re_gender);
            pinValid = -1;
            while(pinValid == -1){
                printf("Enter your pin : ");
                scanf("%u", &re_pin);
                pin_validation(re_pin);
                if(pinValid == -1){
                    printf("Your pin must be 4 digits! Try again!\n");
                }
            }
            my_str_cpy(db[users].name, re_name);
            my_str_cpy(db[users].phone_number, re_phone_number);
            my_str_cpy(db[users].nrc, re_nrc);
            my_str_cpy(db[users].dob, re_dob);
            my_str_cpy(db[users].gender, re_gender);
            db[users].pin = re_pin;
            db[users].id = users+1;
            users++;
            welcome();
        }else{
            printf("Your phone number already in used! Try anoter number\n");
            registration();
        }
    }else{
        printf("Your phone number format is not valid!\n");
        registration();
    }

}

void loadingAllDataFromFile(){
    FILE *fptr;
    fptr = fopen("database.txt", "r");

    if(fptr == NULL){
        printf("Error: Loading Data From File\n");
    }else{
        for(int i = 0; i<SIZE; i++){
            fscanf(fptr, "%d%s%s%s%s%s%u", &db[i].id, db[i].name,
                   db[i].phone_number, db[i].nrc, db[i].dob, db[i].gender, &db[i].pin);

            for(int j = 0; j<(space_array[i] - 6); j++){
                fscanf(fptr, "%s", db[i].trans[j].note);
            }

            if(db[i].name[0] == '\0'){
                break;
            }

            users++;
        }
    }

    fclose(fptr);
}

void printAllInfo(){
    for(int i = 0; i<users; i++){
        printf("%d %s %s %s %s %s %u", db[i].id, db[i].name, db[i].phone_number,
               db[i].nrc, db[i].dob, db[i].gender, db[i].pin);
        for(int j = 0; j<(space_array[i] - 6); j++){
            printf(" %s", db[i].trans[j].note);
        }
        printf("\n");
    }
}

void recording_allData_toFile(){
    FILE *fptr;
    fptr = fopen("database.txt", "w");
    if(fptr == NULL){
        printf("Error: Recording all data to file\n");
    }else{
        for(int i = 0; i<users; i++){
            fprintf(fptr, "%d %s %s %s %s %s %u", db[i].id, db[i].name, db[i].phone_number,
                    db[i].nrc, db[i].dob, db[i].gender, db[i].pin);
            for(int j = 0; j<(space_array[i]-6); j++){
                fprintf(fptr, " %s", db[i].trans[j].note);
            }
            fprintf(fptr, "%c", '\n');
        }
    }
    fclose(fptr);
}

void space_counter(){
    FILE *fptr;
    fptr = fopen("database.txt", "r");

    if(fptr == NULL){
        printf("Error: Space Counter\n");
    }else{
        int index = 0;
        char c = fgetc(fptr);
        while(!feof(fptr)){
            if( c !='\n'){
                if(c==' '){
                    space_array[index]+=1;

                }
                c = fgetc(fptr);

            } else{

                index++;
                c = fgetc(fptr);
            }


        }

        printf("SpaceArray : ");
        for(int i = 0; i<50; i++){
            printf("%d, ", space_array[i]);
        }
        printf("\n");

    }

    fclose(fptr);

}

void phone_validation(char ph[15]){
    int ph_len = str_len(ph);

    if(ph_len == 11){
        if(ph[0] == '0' && ph[1] == '9'){
            // Telenor Ooredoo Mytel MPT
            if((ph[2] == '7') || (ph[2] == '9') || (ph[2] == '6') || (ph[2] == '2')){
                pValid = 1;
            }else{
                pValid = -1;
            }
        }else{
            pValid = -1;
        }
    }else{
        pValid = -1;
    }
}

int str_len(char str[50]){
    int len = 0;
    while(str[len] != '\0'){
        len++;
    }

    return len;
}

void phone_exist_checking(char ph[15]){
    for(int i = 0; i<users; i++){
        strCmp = -1;
        my_str_cmp(ph, db[i].phone_number);
        if(strCmp == 1){
            pExist = i;
        }
    }
}

void my_str_cmp(char first[50], char second[50]){
    int first_counter = str_len(first);
    int second_counter = str_len(second);
    int counter = 0;

    if(first_counter == second_counter){
        for(int i = 0; i<first_counter; i++){
            if(first[i] != second[i]){
                break;
            }
            counter++;
        }
        if(counter == first_counter){
            strCmp = 1;
        }
    }else{
        strCmp = -1;
    }
}

int int_len(unsigned int number){
    int len = 0;
    while(number != 0){
        number /= 10;
        len++;
    }
    return len;
}

void pin_validation(unsigned int pin){
    int pin_length = int_len(pin);
    if(pin_length == 4){
        pinValid = 1;
    }
}

void my_str_cpy(char first[100], char second[100]){
    int second_counter = str_len(second);
    for(int i = 0; i<second_counter; i++){
        first[i] = second[i];
    }
}