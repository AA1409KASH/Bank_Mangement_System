#define _CRT_SECURE_NO_WARNINGS  // Prevents errors in VS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<time.h>

int i,j;
int main_exit;
void closed();
void fordelay(int j);
void menu();
void new_acc();
void edit();
void see();
void transact();
void erase();
void view_list();

struct date{
    int month,day,year;
};
struct {
    int acc_no,age;
    char name[50];
    char address[60];
    char citizenship[50];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
}add,upd,check,rem,transaction;

unsigned int sec=0;
clock_t stopclock=CLOCKS_PER_SEC;

int main()
{
    char pass[15],password[15]="ak";
    int i=0;

    printf("\n\n\t Enter the password to login :");
    printf("\033[8m");
    scanf("%s",pass);
    printf("\033c");
    if(strcmp(pass,password)==0)
    {
        printf("\n\n Password match ! Loading");
        system("cls");
        fordelay(5);
        menu();
    }
        else
        {

        printf("\033c");
        printf("\n\n Wrong Password ");
        login_try:
        printf("\n\n Enter 1 to try again and 0 to exit:");
        scanf ("%d",&main_exit);
        if (main_exit==1)
        {
        system("cls");
         main();
        }
        else if (main_exit==0)
        {
        closed();
        }
    }
    return 0;
}

    void menu ()
    {
    int choice;
    printf ("\033c");
    system("cls");
    printf("\n");
    printf("\33[1;31m");
    printf("\n\n\t\t CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
printf("\n\n\t\t    \33[1;31m WELCOME TO THE MENU ");
// printf("\033[0m");
// printf("\033[1;33m");
    printf("\n\n\t1. Create new account \n\t2.update information of existing account \n\t3. For transaction\n\t4.check the details of existing account\n\t5.Remove existing account\n\t6.View customer's list \n\t7.Exit \n\n\n\n\t\t Enter your choice:");
scanf("%d",&choice);
system("cls");
   printf("\033c");
   switch(choice)
   {
    case 1:new_acc();
    break;
    case 2:edit();
    break;
    case 3:transact();
    break;
    case 4:see();
    break;
    case 5:erase();
    break;
    case 6:view_list();
    break;
    case 7:closed();
    break;
    default:
    printf("Invalid Choice!");
    menu();
    break;
   }
}
void fordelay(int number_of_seconds)
{
    int end = clock() + number_of_seconds * CLOCKS_PER_SEC;

    while(clock() < end);
}
void new_acc()
{
    int choice;
    FILE *ptr;
    ptr = fopen("record.dat", "a+");

account_no:
    system("cls");
    printf("\t\t\t     ADD RECORD ");
    printf("\n\n\n Enter today's date (mm/dd/yyyy) : ");
    scanf("%d/%d/%d",&add.deposit.month,&add.deposit.day,&add.deposit.year);
    printf("Enter account Number :");
    scanf("%d",&add.acc_no);

    // Rewind file to beginning to check for duplicate
    rewind(ptr);

    while(fscanf(ptr,
    "%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",
    &check.acc_no,
    check.name,
    &check.dob.month,
    &check.dob.day,
    &check.dob.year,
    &check.age,
    check.address,
    check.citizenship,
    &check.phone,
    check.acc_type,
    &check.amt,
    &check.deposit.month,
    &check.deposit.day,
    &check.deposit.year) != EOF)
    {
        if (check.acc_no == add.acc_no)
        {
            printf("\nAccount no. already in Use!");
            fclose(ptr);
            goto account_no;
        }
    }

    printf("\n Enter the name :");
    scanf("%s",add.name);
    printf("\n Enter the date of birth (mm/dd/yyyy):");
    scanf("%d%d%d",&add.dob.month,&add.dob.day,&add.dob.year);  // Fixed!
    printf("\n Enter the Age:");
    scanf("%d",&add.age);
    printf("\n Enter the address:");
    scanf("%s",add.address);
    printf("\n Enter the citizenship Number :");
    scanf("%s",add.citizenship);
    printf("\n Enter the Phone Number :");
    scanf("%lf",&add.phone);  // Fixed! (was add.amt before)
    printf("\n Type of Account:\n\t #Saving \n\t #Current \n\t Fixed(for 1 year) \n\t Fixed(for 2 year) \n\t Fixed(for 3 year)");
    scanf("%s",add.acc_type);

    fprintf(ptr,
                "%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",
                add.acc_no,
                add.name,
                add.dob.month,
                add.dob.day,
                add.dob.year,
                add.age,
                add.address,
                add.citizenship,
                add.phone,
                add.acc_type,
                add.amt,
                add.deposit.month,
                add.deposit.day,
                add.deposit.year);
    fclose(ptr);
    printf("\n Account Created successfully !! ");

add_invalid:
    printf("\n\n\n \t Enter 1 to go the main menu and 0 to Exit \n :");
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
    {
        menu();
    }
    else if(main_exit==0)
    {
        closed();
    }
    else
    {
        printf("\n Invalid !");
        goto add_invalid;
    }
}
void edit()
{
    FILE *old, *newrec;
    int choice, test = 0;

    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    if(old == NULL || newrec == NULL)
    {
        printf("File Error!");
        exit(1);
    }

    printf("\n Enter account number to edit : ");
    scanf("%d", &upd.acc_no);

    while(fscanf(old,
    "%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",
    &add.acc_no,
    add.name,
    &add.dob.month,
    &add.dob.day,
    &add.dob.year,
    &add.age,
    add.address,
    add.citizenship,
    &add.phone,
    add.acc_type,
    &add.amt,
    &add.deposit.month,
    &add.deposit.day,
    &add.deposit.year) != EOF)
    {

        if(add.acc_no == upd.acc_no)
        {
            test = 1;

            printf("\n 1. Address");
            printf("\n 2. Phone");
            printf("\n Enter choice : ");
            scanf("%d",&choice);

            if(choice == 1)
            {
                getchar();

                printf("\n Enter new address : ");
                scanf(" %[^\n]", upd.address);

                fprintf(newrec,
                "%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",
                add.acc_no,
                add.name,
                add.dob.month,
                add.dob.day,
                add.dob.year,
                add.age,
                upd.address,
                add.citizenship,
                add.phone,
                add.acc_type,
                add.amt,
                add.deposit.month,
                add.deposit.day,
                add.deposit.year);

                printf("\n Address Updated!");
            }

            else if(choice == 2)
            {
                printf("\n Enter new phone number : ");
                scanf("%lf",&upd.phone);

                fprintf(newrec,
                "%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",
                add.acc_no,
                add.name,
                add.dob.month,
                add.dob.day,
                add.dob.year,
                add.age,
                add.address,
                add.citizenship,
                upd.phone,
                add.acc_type,
                add.amt,
                add.deposit.month,
                add.deposit.day,
                add.deposit.year);

                printf("\n Phone Updated!");
            }
        }

        else
        {
            fprintf(newrec,
            "%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",
            add.acc_no,
            add.name,
            add.dob.month,
            add.dob.day,
            add.dob.year,
            add.age,
            add.address,
            add.citizenship,
            add.phone,
            add.acc_type,
            add.amt,
            add.deposit.month,
            add.deposit.day,
            add.deposit.year);
        }
    }

    fclose(old);
    fclose(newrec);

    remove("record.dat");
    rename("new.dat","record.dat");

    if(test == 0)
    {
        printf("\n Record not found!");
    }

    printf("\n\n Enter 1 for menu and 0 to exit : ");
    scanf("%d",&main_exit);

    if(main_exit == 1)
    {
        menu();
    }
    else
    {
        closed();
    }
}
void transact()
{
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");
    if(old==NULL || newrec ==NULL)
{
    printf("File Error!");
    exit(1);
}
    printf("Enter the account no of the customer:");
    scanf("%d",&transaction.acc_no);
    while(fscanf(old,"%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",&add.acc_no,&add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,&add.address,&add.citizenship,&add.phone,&add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.acc_no==transaction.acc_no)
        {
            test=1;
            if(strcmp(add.acc_type,"fixed1")==0 ||strcmp(add.acc_type,"fixed2")==0 || strcmp(add.acc_type,"fixed3")==0 )
            {
             printf("You cannot deposit or withdraw cash in fixed account\n");
             system("cls");
             menu();
            }
            printf("\n\n Do you want to \n1.deposit \n 2.Withdraw\n\n Enter your choice:");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("Enter Amout that you want to deposit: $");
                scanf("%f",&transaction.amt);
                add.amt+=transaction.amt;
                fprintf(newrec,"%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
               printf("\n\n Deposited Succesfully !! ") ;
            }

     else if(choice==2)
        {
    printf("Enter Amount that you want to Withdraw: $");
    scanf("%f",&transaction.amt);

    if(transaction.amt > add.amt)
    {
        printf("Insufficient Balance!");
    }
    else
    {
        add.amt -= transaction.amt;

        fprintf(newrec,"%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",
        add.acc_no,add.name,add.dob.month,add.dob.day,
        add.dob.year,add.age,add.address,add.citizenship,
        add.phone,add.acc_type,add.amt,
        add.deposit.month,add.deposit.day,add.deposit.year);

        printf("\n\n Withdraw Successfully !! ");
    }
}
        }
        else
        {
          fprintf(newrec,"%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);

        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
      if(test!=1)
    {
        printf("Record not Found !!");
        transcat_invalid:
        printf("\n\n\n Enter 0 to try again, 1 to return the main menu and 2 to Exit ");
        scanf("%d",&main_exit);
        system("cls");
        if(main_exit==0)
        {
            transact();
        }
        else if(main_exit==1)
        {
            menu();
        }
        else if(main_exit==2)
        {
            closed();
        }
        else
        {
            printf("\n invalid !!");
            goto transcat_invalid;
        }
    }
    else
    {
        printf("\n Enter 1 to go main menu and 0 to exit  ");
        scanf("%d",&main_exit);
        system("cls");
        if(main_exit==1)
        {
            menu();
        }
        else if(main_exit==0)
        {
          closed();
        }
    }
}

void see()
{
    FILE *ptr;
    int test=0,rate;
    int choice;
    float intrest;
    float time;
    ptr=fopen("record.dat","r");
     if(ptr==NULL)
{
    printf("File Error!");
    exit(1);
}
    printf("\n Do you want to check \n1.Account no \n2.Name \n\n Enter your choice:");
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("Enter the account number : ");
        scanf("%d",&check.acc_no);

         while(fscanf(ptr,"%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",&add.acc_no,&add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,&add.address,&add.citizenship,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
         {
         if(add.acc_no== check.acc_no)
       {
        system("cls");
        test=1;
        printf("\n Account no .%d \n Name : %s \n DOB : %d%d%d \n Age :%d \n Address:%s citizenship No : %s \n Phone Number : %.0lf \n Type of Account:%s \n Amount deposited : $ %.2f \n Date of Deposit : %d%d%d \n\n  ",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year );
        if(strcmp(add.acc_type,"fixed1")==0 ||strcmp(add.acc_type,"fixed2")==0 || strcmp(add.acc_type,"fixed3")==0 )
        {
            printf("\n\n You will get no intrest");
        }
       }
    }
}
else if(choice==2)
{
    printf("Enter the name :");
    scanf(" %[^\n]", check.name);
    while(fscanf(ptr,"%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",&add.acc_no,&add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,&add.address,&add.citizenship,&add.phone,&add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
    if(strcmp(add.name,check.name)==0)
    {
     system("cls");
     test=1;
     printf("\n Account no .%d \n Name : %s \n DOB : %d%d%d \n Age :%d \n Address:%s citizenship No : %s \n Phone Number : %.0lf \n Type of Account:%s \n Amount deposited : $ %.2f \n Date of Deposit : %d%d%d \n\n  ",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year );

     if(strcmp(add.acc_type,"fixed1")==0 ||strcmp(add.acc_type,"fixed2")==0 || strcmp(add.acc_type,"fixed3")==0 )
        {
            printf("\n\n You will get no intrest");
        }
    }
}
}
  fclose(ptr);
  if(test !=1)
  {
    system("cls");
    printf("\n Record not found !! ");
    see_invalid :
    printf("\n Enter 0 to try again, 1 to return to the main menu and 2 to exit \n enter your choice \n");
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
    {
        menu();
    }
    else if(main_exit==2)
    {
     closed();
    }
    else if (main_exit==0)
    {
        see();
    }
  else
  {
    system("cls");
    printf("\n Invalid !!");
    goto see_invalid;
  }
  }
  else
  {
    printf("\n Enter 1 to go the main menu and 0 to exit :\n");
    scanf("%d",&main_exit);
  }
  if(main_exit==1)
  {
    system("cls");
    menu();
  }
  else
  {
    system("cls");
    closed();
  }
}
void erase()
{
    FILE *old,*newrec;
    int test=0;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");
     if(old==NULL || newrec ==NULL)
{
    printf("File Error!");
    exit(1);
}
    printf("Enter the account no of the customer that you want to delete ");
    scanf("%d",&rem.acc_no);
    while(fscanf(old,"%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",&add.acc_no,&add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,&add.address,&add.citizenship,&add.phone,&add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.acc_no!=rem.acc_no)
        {
          fprintf(newrec,"%d|%s|%d|%d|%d|%d|%s|%s|%.0lf|%s|%.2f|%d|%d|%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.citizenship,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year) ;
        }
        else
        {
          test++;
          printf("\n Record deleted sucessfully! \n\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
    if(test==0)
    {
        printf("\n Record not Found !!\n");
        erase_invalid:
        printf("\n Enter 0 to try again ,1 to return main menu and 2 to exit :");
        scanf("%d",&main_exit);
        if(main_exit==1)
        {
            menu();
        }
        else if(main_exit==2)
        {
            closed();
        }
        else if (main_exit==0)
        {
            erase();
        }
        else
        {
            printf("\n Invalid !! \n");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\n Enter 1 to go the main and 0 to exit :");
        scanf("%d",&main_exit);
        system("cls");
        if(main_exit==1)
        {
            menu();
        }
        else
        {
            closed();
        }
    }
}

void view_list()
{
    FILE *view;
    view=fopen("record.dat","r");
     if(view==NULL)
{
    printf("File Error!");
    exit(1);
}
    int test=0;
    system("cls");
    printf("\n ACC.no \t Name \t\t Address \t Phone \n ");
while(fscanf(view,"%d|%49[^|]|%d|%d|%d|%d|%59[^|]|%49[^|]|%lf|%9[^|]|%f|%d|%d|%d",&add.acc_no,&add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,&add.address,&add.citizenship,&add.phone,&add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
{
   printf("\n%6d\t %-10s\t %-10s\t %.0lf",
       add.acc_no,
       add.name,
       add.address,
       add.phone);
    test++;
}
fclose(view);
if(test==0)
{
    system("cls");
    printf("\n NO RECORD !! \n");
}
view_list_invalid:
printf("\n\n Enter 1 to go main menu and 0 to Exit :");
scanf("%d",&main_exit);
system("cls");
if(main_exit==1)
{
    menu();
}
else if(main_exit==0)
{
    closed();
}
else
{
    printf("\n Invalid ! \n");
    goto view_list_invalid;
}
}

void closed()
{
 system("cls");
 printf("\n\n Thank You For Using Banking Management System");
  exit(0);
}
