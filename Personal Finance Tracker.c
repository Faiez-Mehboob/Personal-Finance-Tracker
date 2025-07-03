#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define MaxEntries 1000

struct Transactions{   
    char type[10];
    double amount;
} data[MaxEntries];

struct Goals{
    double expense_goal;
    double savings_goal;
    double balance_goal;
} goal;

struct Currencies{
    char Dollar[2];
    double dollar_rate;
    char Yen[2];
    double Yen_rate;
    char Pound[2];
    double Pound_rate;
    char Euro[2];
    double Euro_rate;
    char Rupees[3];
    double rupees_rate;
} currencies;

char current_currency[3];
int entry=0;
double savings_amount=0;
double balance=0;
int converted=0;

void Add_Money(char* type,double amount){
    strcpy(data[entry].type,type);
    data[entry].amount=amount;
    entry++;
    if(strcmp(type,"budget")==0){
        printf("Budget added\n");
    }
    else if(strcmp(type,"expense")==0){
        printf("Expense added\n");
    }
}

void Calculate_Balance(){
    int i;
    double sum=0;
    for(i=0;i<entry;i++){
        if(strcmp(data[i].type,"budget")==0){
            sum+=data[i].amount;
        } 
		else if(strcmp(data[i].type,"expense")==0){
            sum-=data[i].amount;
        }
        else if(strcmp(data[i].type,"savings")==0){
            sum-=data[i].amount;
        }
    }
    balance=sum;
}

void Set_Saving(char* type,double amount){
    strcpy(data[entry].type,type);
    data[entry].amount=amount;
    entry++;
    savings_amount+=amount;
    printf("Saving amount transferred\n");
}

void Transaction_History(){
    int i;
    printf("\n\tTransaction History:\n");
    printf("-----------------------------------------------------------\n");
    for(i=0;i<entry;i++){
        if(strcmp(data[i].type,"budget")==0){
            printf("%-18s%5s %.2lf\n","Budget added",current_currency,data[i].amount);
        }
        else if(strcmp(data[i].type,"expense")==0){
            printf("%-18s%5s %.2lf\n","Expense recorded",current_currency,data[i].amount);
        }
        else if(strcmp(data[i].type,"savings")==0){
            printf("%-18s%5s %.2lf\n","Savings secured",current_currency,data[i].amount);
        }
    }
    printf("\n");
}

void Financial_Goal(){
    printf("Enter Expense Goal: ");
    scanf("%lf",&goal.expense_goal);
    printf("Enter Savings Goal: ");
    scanf("%lf",&goal.savings_goal);
    printf("Enter Balance Goal: ");
    scanf("%lf",&goal.balance_goal);
}

void Financial_Report(){
    int i;
    double inc=0,exp=0;
    for(i=0;i<entry;i++){
        if(strcmp(data[i].type,"budget") == 0){
            inc+=data[i].amount;
        } 
		else if(strcmp(data[i].type,"expense") == 0){
            exp+=data[i].amount;
        }
    }
    printf("\n\tFinancial Report:\n");
    printf("-----------------------------------------------------------\n");
    printf("%-18s%5s %.2lf\n","Total Budget",current_currency,inc);
    printf("%-18s%5s %.2lf\n","Total Expenses",current_currency,exp);
    printf("%-18s%5s %.2lf\n","Total Savings",current_currency,savings_amount);
    printf("%-18s%5s %.2lf\n","Balance",current_currency,balance);
    if(balance<0){
        printf("Budget exceeded. Negative balance!\n");
    }
    
    if(goal.balance_goal!=0 && goal.expense_goal!=0 && goal.savings_goal!=0){
        printf("-----------------------------------------------------------\n");
		printf("\tFinancial Goals Status:\n");
        printf("-----------------------------------------------------------\n");
        printf("Expense Goal: %s %.2lf\tYour Expenses: %s %.2lf\n",current_currency,goal.expense_goal,current_currency,exp);
        if(exp<=goal.expense_goal){
            printf("\tGOAL MET!\n");
        }
        else{
            printf("\tFailed to meet goal.\n");
        }
        printf("-----------------------------------------------------------\n");
        printf("Savings Goal: %s %.2lf\tYour Savings: %s %.2lf\n",current_currency,goal.savings_goal,current_currency,savings_amount);
        if(savings_amount>=goal.savings_goal){
            printf("\tGOAL MET!\n");
        }
        else{
            printf("\tFailed to meet goal.\n");
        }
        printf("-----------------------------------------------------------\n");
        printf("Balance Goal: %s %.2lf\tYour Balance: %s %.2lf\n",current_currency,goal.balance_goal,current_currency,balance);
        if(balance>=goal.balance_goal){
            printf("\tGOAL MET!\n");
        }
        else{
            printf("\tFailed to meet goal.\n");
        }
    }
    printf("\n");
}

void Export_Data(){
    int i;
    double inc=0,exp=0;
    FILE* ptr;
    ptr=fopen("Budget_Tracker.bin","wb");
    
    if(ptr==NULL){
        printf("Error accessing file for export!\n");
        fclose(ptr);
        return;
    }
    
    else{
        fwrite(&entry,sizeof(int),1,ptr);
        for(i=0;i<entry;i++){
            fwrite(&data[i],sizeof(struct Transactions),1,ptr);
        }
        fwrite(&goal.expense_goal,sizeof(double),1,ptr);
        fwrite(&goal.savings_goal,sizeof(double),1,ptr);
        fwrite(&goal.balance_goal,sizeof(double),1,ptr);
        fwrite(&current_currency,sizeof(char)*3,1,ptr);

        fclose(ptr);
        printf("Data Exported successfully\n");
    }
    
}

void Currency_Symbols(){
    strcpy(currencies.Dollar,"$");
    strcpy(currencies.Euro,"€");
    strcpy(currencies.Yen,"¥");
    strcpy(currencies.Pound,"£");
    strcpy(currencies.Rupees,"Rs");
}

void Set_Currencies(){
    if(strcmp(current_currency,currencies.Rupees)==0){
        currencies.rupees_rate=1;
        currencies.dollar_rate=0.0035;
        currencies.Euro_rate=0.0032;
        currencies.Pound_rate=0.0028;
        currencies.Yen_rate=0.53;
    }
    else if(strcmp(current_currency,currencies.Dollar)==0){
        currencies.rupees_rate=285.50;
        currencies.dollar_rate=1;
        currencies.Euro_rate=0.91;
        currencies.Pound_rate=0.79;
        currencies.Yen_rate=149.47;
    }
    else if(strcmp(current_currency,currencies.Euro)==0){
        currencies.rupees_rate=312.61;
        currencies.dollar_rate=1.09;
        currencies.Euro_rate=1;
        currencies.Pound_rate=0.87;
        currencies.Yen_rate=163.65;
    }
    else if(strcmp(current_currency,currencies.Yen)==0){
        currencies.rupees_rate=1.91;
        currencies.dollar_rate=0.0067;
        currencies.Euro_rate=0.0061;
        currencies.Pound_rate=0.0053;
        currencies.Yen_rate=1;
    }
    else if(strcmp(current_currency,currencies.Pound)==0){
        currencies.rupees_rate=359.76;
        currencies.dollar_rate=1.26;
        currencies.Euro_rate=1.15;
        currencies.Pound_rate=1;
        currencies.Yen_rate=188.34;
    }
}

void Change_Currency(int currency){
    int i;
    if(strcmp(current_currency,currencies.Rupees)==0){
        switch(currency){
            case 1:
                if(entry>0){
                    for(i=0;i<entry;i++){
                        data[i].amount*=currencies.dollar_rate;
                    }
                    goal.expense_goal*=currencies.dollar_rate;
                    goal.savings_goal*=currencies.dollar_rate;
                    goal.balance_goal*=currencies.dollar_rate;
                    savings_amount*=currencies.dollar_rate;
                    balance*=currencies.dollar_rate;
                }
                strcpy(current_currency,currencies.Dollar);
                break;
            case 2:
                if(entry>0){
                    for(i=0;i<entry;i++){
                        data[i].amount*=currencies.Euro_rate;
                    }
                    goal.expense_goal*=currencies.Euro_rate;
                    goal.savings_goal*=currencies.Euro_rate;
                    goal.balance_goal*=currencies.Euro_rate;
                    savings_amount*=currencies.Euro_rate;
                    balance*=currencies.Euro_rate;
                }
                strcpy(current_currency,currencies.Euro);
                break;
            case 3:
                if(entry>0){
                    for(i=0;i<entry;i++){
                        data[i].amount*=currencies.Yen_rate;
                    }
                    goal.expense_goal*=currencies.Yen_rate;
                    goal.savings_goal*=currencies.Yen_rate;
                    goal.balance_goal*=currencies.Yen_rate;
                    savings_amount*=currencies.Yen_rate;
                    balance*=currencies.Yen_rate;
                }
                strcpy(current_currency,currencies.Yen);
                break;
            case 4:
                if(entry>0){
                    for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Pound_rate;
                    }
                    goal.expense_goal*=currencies.Pound_rate;
                    goal.savings_goal*=currencies.Pound_rate;
                    goal.balance_goal*=currencies.Pound_rate;
                    savings_amount*=currencies.Pound_rate;
                    balance*=currencies.Pound_rate;
                }
                strcpy(current_currency,currencies.Pound);
                break;
            default:
                printf("Invalid Option\n");
                break;
        }
    }
    else if(strcmp(current_currency,currencies.Dollar)==0){
        switch(currency){
            case 1:
                if(entry>0){
                    for(i=0;i<entry;i++){
                        data[i].amount*=currencies.rupees_rate;
                    }
                    goal.expense_goal*=currencies.rupees_rate;
                    goal.savings_goal*=currencies.rupees_rate;
                    goal.balance_goal*=currencies.rupees_rate;
                    savings_amount*=currencies.rupees_rate;
                    balance*=currencies.rupees_rate;
                }
                strcpy(current_currency,currencies.Rupees);
                break;
            case 2:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Euro_rate;
                }
                goal.expense_goal*=currencies.Euro_rate;
                goal.savings_goal*=currencies.Euro_rate;
                goal.balance_goal*=currencies.Euro_rate;
                savings_amount*=currencies.Euro_rate;
                balance*=currencies.Euro_rate;
                }
                strcpy(current_currency,currencies.Euro);
                break;
            case 3:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Yen_rate;
                }
                goal.expense_goal*=currencies.Yen_rate;
                goal.savings_goal*=currencies.Yen_rate;
                goal.balance_goal*=currencies.Yen_rate;
                savings_amount*=currencies.Yen_rate;
                balance*=currencies.Yen_rate;
                }
                strcpy(current_currency,currencies.Yen);
                break;
            case 4:
                if(entry>0){
                for(i=0;i<entry;i++){
                data[i].amount*=currencies.Pound_rate;
                }
                goal.expense_goal*=currencies.Pound_rate;
                goal.savings_goal*=currencies.Pound_rate;
                goal.balance_goal*=currencies.Pound_rate;
                savings_amount*=currencies.Pound_rate;
                balance*=currencies.Pound_rate;
                }
                strcpy(current_currency,currencies.Pound);
                break;
            default:
                printf("Invalid Option\n");
                break;
        }
    }
    else if(strcmp(current_currency,currencies.Euro)==0){
        switch(currency){
            case 1:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.dollar_rate;
                }
                goal.expense_goal*=currencies.dollar_rate;
                goal.savings_goal*=currencies.dollar_rate;
                goal.balance_goal*=currencies.dollar_rate;
                savings_amount*=currencies.dollar_rate;
                balance*=currencies.dollar_rate;
                }
                strcpy(current_currency,currencies.Dollar);
                break;
            case 2:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.rupees_rate;
                }
                goal.expense_goal*=currencies.rupees_rate;
                goal.savings_goal*=currencies.rupees_rate;
                goal.balance_goal*=currencies.rupees_rate;
                savings_amount*=currencies.rupees_rate;
                balance*=currencies.rupees_rate;
                }
                strcpy(current_currency,currencies.Rupees);
                break;
            case 3:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Yen_rate;
                }
                goal.expense_goal*=currencies.Yen_rate;
                goal.savings_goal*=currencies.Yen_rate;
                goal.balance_goal*=currencies.Yen_rate;
                savings_amount*=currencies.Yen_rate;
                balance*=currencies.Yen_rate;
                }
                strcpy(current_currency,currencies.Yen);
                break;
            case 4:
                if(entry>0){
                for(i=0;i<entry;i++){
                data[i].amount*=currencies.Pound_rate;
                }
                goal.expense_goal*=currencies.Pound_rate;
                goal.savings_goal*=currencies.Pound_rate;
                goal.balance_goal*=currencies.Pound_rate;
                savings_amount*=currencies.Pound_rate;
                balance*=currencies.Pound_rate;
                }
                strcpy(current_currency,currencies.Pound);
                break;
            default:
                printf("Invalid Option\n");
                break;
        }
    }
    else if(strcmp(current_currency,currencies.Yen)==0){
        switch(currency){
            case 1:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.dollar_rate;
                }
                goal.expense_goal*=currencies.dollar_rate;
                goal.savings_goal*=currencies.dollar_rate;
                goal.balance_goal*=currencies.dollar_rate;
                savings_amount*=currencies.dollar_rate;
                balance*=currencies.dollar_rate;
                }
                strcpy(current_currency,currencies.Dollar);
                break;
            case 2:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Euro_rate;
                }
                goal.expense_goal*=currencies.Euro_rate;
                goal.savings_goal*=currencies.Euro_rate;
                goal.balance_goal*=currencies.Euro_rate;
                savings_amount*=currencies.Euro_rate;
                balance*=currencies.Euro_rate;
                }
                strcpy(current_currency,currencies.Euro);
                break;
            case 3:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.rupees_rate;
                }
                goal.expense_goal*=currencies.rupees_rate;
                goal.savings_goal*=currencies.rupees_rate;
                goal.balance_goal*=currencies.rupees_rate;
                savings_amount*=currencies.rupees_rate;
                balance*=currencies.rupees_rate;
                }
                strcpy(current_currency,currencies.Rupees);
                break;
            case 4:
                if(entry>0){
                for(i=0;i<entry;i++){
                data[i].amount*=currencies.Pound_rate;
                }
                goal.expense_goal*=currencies.Pound_rate;
                goal.savings_goal*=currencies.Pound_rate;
                goal.balance_goal*=currencies.Pound_rate;
                savings_amount*=currencies.Pound_rate;
                balance*=currencies.Pound_rate;
                }
                strcpy(current_currency,currencies.Pound);
                break;
            default:
                printf("Invalid Option\n");
                break;
        }
    }
    else if(strcmp(current_currency,currencies.Pound)==0){
        switch(currency){
            case 1:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.dollar_rate;
                }
                goal.expense_goal*=currencies.dollar_rate;
                goal.savings_goal*=currencies.dollar_rate;
                goal.balance_goal*=currencies.dollar_rate;
                savings_amount*=currencies.dollar_rate;
                balance*=currencies.dollar_rate;
                }
                strcpy(current_currency,currencies.Dollar);
                break;
            case 2:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Euro_rate;
                }
                goal.expense_goal*=currencies.Euro_rate;
                goal.savings_goal*=currencies.Euro_rate;
                goal.balance_goal*=currencies.Euro_rate;
                savings_amount*=currencies.Euro_rate;
                balance*=currencies.Euro_rate;
                }
                strcpy(current_currency,currencies.Euro);
                break;
            case 3:
                if(entry>0){
                for(i=0;i<entry;i++){
                    data[i].amount*=currencies.Yen_rate;
                }
                goal.expense_goal*=currencies.Yen_rate;
                goal.savings_goal*=currencies.Yen_rate;
                goal.balance_goal*=currencies.Yen_rate;
                savings_amount*=currencies.Yen_rate;
                balance*=currencies.Yen_rate;
                }
                strcpy(current_currency,currencies.Yen);
                break;
            case 4:
                if(entry>0){
                for(i=0;i<entry;i++){
                data[i].amount*=currencies.rupees_rate;
                }
                goal.expense_goal*=currencies.rupees_rate;
                goal.savings_goal*=currencies.rupees_rate;
                goal.balance_goal*=currencies.rupees_rate;
                savings_amount*=currencies.rupees_rate;
                balance*=currencies.rupees_rate;
                }
                strcpy(current_currency,currencies.Rupees);
                break;
            default:
                printf("Invalid Option\n");
                break;
        }
    }
    if(entry>0){
        converted=1;
    }
}

void Import_Data(){
    int i;
    FILE *ptr;
    ptr=fopen("Budget_Tracker.bin","rb");
    if(ptr==NULL){
        printf("Error accessing file\n");
    }
    else{
        fread(&entry,sizeof(int),1,ptr);
        for(i=0;i<entry;i++){
            fread(&data[i],sizeof(struct Transactions),1,ptr);
        }
        fread(&goal.expense_goal,sizeof(double),1,ptr);
        fread(&goal.savings_goal,sizeof(double),1,ptr);
        fread(&goal.balance_goal,sizeof(double),1,ptr);
        fread(&current_currency,sizeof(char)*3,1,ptr);
        fclose(ptr);
        printf("Data Imported successfully\n");
    }
    Set_Currencies(current_currency);
}

void clearInputBuffer() {
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void clrsrc(){
    system("cls");
}

int main(){
    int check,choice=0;
    double amount=0;
    int currency;
    Currency_Symbols();
    do{
    printf("\t\t\tWelcome to Personal Budget Tracker!\n----------------------------------------------------------------------------------------"
            "\n-> You can use a variety of features to help you in managing your budget.\n"
            "-> You may select your default income currency at the start.\n" 
            "-> You can change the currency only once after adding Budget.\n"
            "-> You may change it however many times as you want before adding a budget.\n");
    
    printf("\n1. Rupees\n2. Dollar\n3. Euro\n4. Yen\n5. Pound\n");
    printf("Select the starting currency: ");
    scanf("%d",&currency);
    
    if(currency==1){
        strcpy(current_currency,currencies.Rupees);
        Set_Currencies(current_currency);
        getchar();
        clrsrc();
    } 
    else if(currency==2){
        strcpy(current_currency,currencies.Dollar);
        Set_Currencies(current_currency);
        getchar();
        clrsrc();
    } 
    else if(currency==3){
        strcpy(current_currency,currencies.Euro);
        Set_Currencies(current_currency);
        getchar();
        clrsrc();
    } 
    else if(currency==4){
        strcpy(current_currency,currencies.Yen);
        Set_Currencies(current_currency);
        getchar();
        clrsrc();
    } 
    else if(currency==5){
        strcpy(current_currency,currencies.Pound);
        Set_Currencies(current_currency);
        getchar();
        clrsrc();
    }
    else{
        printf("Invalid Choice!");
        Sleep(1000);
        clrsrc();
    }
    }while(currency!=1&&currency!=2&&currency!=3&&currency!=4&&currency!=5);
    
    do
    {
        printf("\nSelect Command:\n");
        printf("--------------------------------------\n");
        printf("1. Add Budget \n");
        printf("2. Record Expense \n");
        printf("3. Reposit Saving\n");
        printf("4. Set Financial goal\n");
        printf("5. View Transaction History\n");
        printf("6. View Balance\n");
        printf("7. Generate Financial Report\n");
        printf("8. Export Data\n");
        printf("9. Import Data\n");
        printf("10. Change Currency\n");
        printf("0. Exit\n");
        printf("--------------------------------------\n\n");

        printf("\nEnter your command: ");
        check=scanf("%d", &choice);
        if(check==1){
        switch (choice){
            case 1:
                    printf("\nEnter Budget Amount: ");
                    check=scanf("%lf", &amount);
                    if(check==1){
                        Add_Money("budget",amount);
                        Calculate_Balance();
                    }
                    else{
                        printf("Error reading input\n");
                    }
                break;
            case 2:
                if(entry==0){
                    printf("No Budget Added yet\n");
                }
                else{
                    printf("\nEnter Expense Amount: ");
                    check=scanf("%lf", &amount);
                    if(check==1){
                        Add_Money("expense",amount);
                        Calculate_Balance();
                    }
                    else{
                        printf("Error reading input\n");
                    }
                }
                break;
            case 3:
                if(entry==0){
                    printf("No Budget added yet\n");
                }
                else{
                    printf("\nEnter Saving amount: ");
                    check=scanf("%lf",&amount);
                    if(check==1){
                        Set_Saving("savings",amount);
                        Calculate_Balance();
                    }
                    else{
                        printf("Error reading input\n");
                    }
                }
                break;
            case 4:
                Financial_Goal();
                break;
            case 5:
                if(entry==0){
                    printf("No Budget Added yet\n");
                }
                else{
                    Transaction_History();
                }
                break;
            case 6:
                if(entry==0){
                    printf("No Budget Added yet\n");
                }
                else{
                    Calculate_Balance();
                    if(balance<0){
                        printf("\nCurrent Balance: %s %.2lf\nBudget exceeded. Negative balance!\n",current_currency,balance);
                    }
                    else{
                        printf("\nCurrent Balance: %s %.2lf\n",current_currency,balance);
                    }
                }
                break;
            case 7:
                if(entry==0){
                    printf("No Budget Added yet\n");
                }
                else{
                    Financial_Report();
                }
                break;
            case 8:
                if(entry==0){
                    printf("No Budget Added yet\n");
                }
                else{
                    Export_Data();
                }
                break;
            case 9:
                Import_Data();
                break;
            case 10:
                if(converted==0){
                    if(strcmp(current_currency,currencies.Rupees)==0){
                        printf("1. Dollar\n2. Euro\n3. Yen\n4. Pound\n");
                        printf("Select the currency for conversion from Rupees: ");
                        scanf("%d",&currency);
                    } 
                    else if(strcmp(current_currency,currencies.Dollar)==0){
                        printf("1. Rupees\n2. Euro\n3. Yen\n4. Pound\n");
                        printf("Select the currency for conversion from Dollar: ");
                        scanf("%d",&currency);
                    }
                    else if(strcmp(current_currency,currencies.Euro)==0){
                        printf("1. Dollar\n2. Rupees\n3. Yen\n4. Pound\n");
                        printf("Select the currency for conversion from Euro: ");
                        scanf("%d",&currency);
                    }
                    else if(strcmp(current_currency,currencies.Yen)==0){
                        printf("1. Dollar\n2. Euro\n3. Rupees\n4. Pound\n");
                        printf("Select the currency for conversion from Yen: ");
                        scanf("%d",&currency);
                    }
                    else if(strcmp(current_currency,currencies.Pound)==0){
                        printf("1. Dollar\n2. Euro\n3. Yen\n4. Rupees\n");
                        printf("Select the currency for conversion from Pound: ");
                        scanf("%d",&currency);
                    }
                    Change_Currency(currency);
                    Set_Currencies(current_currency);
                }
                else if(converted==1){
                    printf("-> Currency has already been converted once. Can not change further\n");
                }
                break;
            case 0:
                printf("-> Thank you for using the Personal Budget Tracker.Goodbye!");
                break;
            default:
                printf("Invalid command.\n");
            break;
        }
        }
        else{
            clearInputBuffer();
            printf("error reading command\n");
            choice=-1;
        }
        if(choice==-1){
            printf("Press Enter to conitnue:");
            getchar();
            clrsrc();
        }
        
        else if(choice!=0 && choice!=-1){
            clearInputBuffer();
            printf("Press Enter to conitnue:");
            getchar();
            clrsrc();
        }
    } while(choice!=0);
    return 0;
}
