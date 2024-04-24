#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

int hidePassword();
char* getFileOption(FILE *file,char keyWord[20]);
void changeFileOption(FILE *file,char pathFile[150],char keyWord[20],char newPassword[20]);
void initFile(FILE *file,char nomFichier[150]);

int main(){
    system("color 3F");

    int option, count=0, amount=1, contunueTransaction=1, attent=3, sleepSec=1100, pin, enteredPin, first_time = 0;
    char *getOption, optionData[20], newPass[20], confirmPass[20];
    float balance;

    char nom_file[] = "configuration.txt";
    char pathFile[] = "Your_path_here\\conf\\configuration.txt";
    FILE *file = fopen(pathFile,"r");

    if(file == NULL){
        FILE *fileTest = fopen(pathFile,"w");
        initFile(fileTest,pathFile);
        fclose(fileTest);

        if(fileTest == NULL){
            printf("\nError 404 | Invalid fichier '%s'\n",nom_file);
            exit(0);
        }
        first_time = 1;
    }

    file = fopen(pathFile,"r");
    getOption = getFileOption(file,"password");
    strcpy(optionData,getOption);
    pin = atoi(optionData);

    freopen(pathFile,"r",file);
    getOption = getFileOption(file,"balance");
    strcpy(optionData,getOption);
    balance = atoi(optionData);

    time_t now;
    time(&now);

    printf("\t\t\t\t\t      %s",ctime(&now));
    printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================");

    do{
        system("cls");
        printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================");
        if(first_time == 1) {
            printf("\n\n First Time ");
            printf("\n\n Default Password is '0000' ");
            printf("\n\n Recommend to change Your Password ");
        }
        printf("\n\n Please enter your pin : ");
        enteredPin = hidePassword();
        if(pin != enteredPin){
            attent--;
            if(attent != 0){
                printf("\n Invalid pin %d attempts remaining!!!",attent);
                Beep(650,500);
                Sleep(sleepSec);
            }
            count++;
        }
        if(count == 3 && enteredPin != pin){
            printf("\n You have exhausted your attempts\n");
            Beep(650,500);
            exit(0);
        }
    }while(pin != enteredPin);

    while(contunueTransaction != 0){
        attent = 3;
        count = 0;
        enteredPin = 0;
        system("cls");
        printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================\n\n");
        printf("\n\t\t\t========================*Available Transactions*=========================\n");
        printf("\n\t\t1.Withdrawl");
        printf("\n\t\t2.Deposit");
        printf("\n\t\t3.Check Balance");
        printf("\n\t\t4.Change the Password");
        printf("\n\t\t5.Cancel Operation");
        printf("\n\n\tPlease select the option : ");
        scanf("%d",&option);
        switch(option){
            case 1:
                while(amount % 100 != 0){
                    system("cls");
                    printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================\n\n");
                    printf("\n\t\t\t==========================*Withdrawl Section*============================\n");
                    printf("\n\tEnter the amount : ");
                    scanf("%d",&amount);
                    if(amount % 100 != 0){
                        printf("\n\tThe amount should be multiple of 100Dh");
                        Beep(650,500);
                        Sleep(sleepSec);
                    }
                }
                if(balance < amount){
                    printf("\n\tSorry insufficient balance");
                    amount = 1;
                    break;
                } else {
                    freopen(pathFile,"r",file);
                    balance -= amount;
                    itoa(balance,optionData,10);
                    changeFileOption(file,pathFile,"balance",optionData);
                    printf("\n\t\tYou have withdrawn %dDh. Your new balance is %.2fDh\n",amount,balance);
                    printf("\n\t\t\t=============*Thank you for banking with veraBank. Learning*==============\n");
                    amount = 1;
                    break;
                }
            case 2:
                do{
                    system("cls");
                    printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================\n\n");
                    printf("\n\t\t\t===========================*Deposit Section*=============================\n");
                    printf("\n\tPlease enter the amount (100+) : ");
                    scanf("%d",&amount);
                    if(amount < 100){
                        printf("\n\tInsufficient amount");
                        Beep(650,500);
                        Sleep(sleepSec);
                    }
                }while(amount < 100);
                freopen(pathFile,"r",file);
                balance += amount;
                itoa(balance,optionData,10);
                changeFileOption(file,pathFile,"balance",optionData);
                printf("\n\t\tYou have deposited %dDh. Your new balance is %.2fDh\n",amount,balance);
                printf("\n\t\t\t=============*Thank you for banking with veraBank. Learning*=============\n");
                amount = 1;
                break;
            case 3:
                system("cls");
                printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================\n\n");
                printf("\n\t\t\t=============================*Check Balance*=============================\n");
                printf("\n\t\tYour balance is %.2fDh\n",balance);
                break;
            case 4:
                do{
                    system("cls");
                    printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================\n");
                    printf("\n\t\t\t===========================*Password Settings*===========================\n");
                    printf("\n\n Please enter your pin : ");
                    fflush(stdin);
                    enteredPin = hidePassword();
                    if(pin != enteredPin){
                        attent--;
                        if(attent != 0){
                            printf("\n Invalid pin %d attempts remaining!!!",attent);
                            Beep(650,500);
                            Sleep(sleepSec);
                        }
                        count++;
                    }
                    if(count == 3 && enteredPin != pin){
                        printf("\n You have exhausted your attempts\n");
                        printf("\n Your conexion is lost!\n");
                        Beep(650,500);
                        exit(0);
                    }
                }while(pin != enteredPin);

                freopen(pathFile,"r",file);
                do{
                    system("cls");
                    printf("\n\t\t\t===================*Welcome to veraBank. Learning ATM*===================\n");
                    printf("\n\t\t\t===========================*Password Settings*===========================\n");
                    printf(" Enter a new password: ");
                    fflush(stdin);
                    enteredPin = hidePassword();
                    itoa(enteredPin,newPass,10);
                    printf("\n Confirm you password: ");
                    fflush(stdin);
                    enteredPin = hidePassword();
                    itoa(enteredPin,confirmPass,10);
                }while(strcmp(newPass,confirmPass)!=0);
                pin = enteredPin;

                changeFileOption(file,pathFile,"password",newPass);

                printf("\n\n\t\tChanged with sucess!!!\n");
                break;
            case 5:
                printf("\n\t\t\t=============*Thank you for banking with veraBank. Learning*=============\n");
                contunueTransaction = 0;
                break;
            default:
                Beep(650,500);
                printf("\n\t\tInvalid Option!!!");
        }

        if(contunueTransaction != 0){
            printf("\n\t\tDo you wish to perform another transaction? Press 1[Yes], 0[No] ");
            scanf("%d",&contunueTransaction);
        }
    }
    printf("\n");

    return 0;
}

int hidePassword(){
    char ch,initialpass[20];
    int i=0,finalPassword;

    while((ch = _getch()) != 13){
        initialpass[i]=ch;
        printf("*");
        i++;
    }
    initialpass[i]='\0';

    finalPassword = atoi(initialpass);

    return finalPassword;
}

void initFile(FILE *file,char nomFichier[150]){

    fprintf(file,"password:0000\n");
    fprintf(file,"balance:0\n");

    fclose(file);
}

char* getFileOption(FILE *file,char keyWord[20]){
    char fileLine[100],*findLine;
    int i=0,count=0;

    while(fgets(fileLine,100,file) != NULL){
        count++;
        findLine = strstr(fileLine,keyWord);
        if(findLine != NULL){
            break;
        }
    }
    fclose(file);

    if(count==0){
        return findLine = NULL;
    }

    findLine = strstr(findLine,":");
    while(findLine[i] != '\0'){
        findLine[i] = findLine[i+1];
        i++;
    }
    return findLine;
}

void changeFileOption(FILE *file,char pathFile[150],char keyWord[20],char newPassword[20]){
    FILE *fileTemp = fopen("fileTemp.txt","w");

    if(fileTemp == NULL){
        printf("\nError 404 | Invalid file\n");
        exit(0);
    }

    char fileLine[100],*chaine;
    int line=0,count=0;

    while(fgets(fileLine,100,file) != NULL){
        chaine = strstr(fileLine,keyWord);

        if(chaine != NULL)
            break;
        line++;
    }

    freopen(pathFile,"r",file);

    while(fgets(fileLine,100,file) != NULL){
        fputs(fileLine,fileTemp);
    }

    freopen("fileTemp.txt","r",fileTemp);
    freopen(pathFile,"w",file);

    while(fgets(fileLine,100,fileTemp) != NULL){
        if(count == line){
            fprintf(file,"%s:%s\n",keyWord,newPassword);
        }
        else
            fputs(fileLine,file);

        count++;
    }

    fclose(file);
    fclose(fileTemp);
    remove("fileTemp.txt");
}
