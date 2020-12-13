#include "conio2.h"
#include<stdio.h>
#include "rlyres.h"
#include <string.h>
#include <malloc.h>
int enterchoice()
{
    int  i;
    int choice;
    textcolor(YELLOW);
    for(i=1;i<125;i++)
    {
        printf("-");
    }
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM");
    for(i=1;i<126;i++)
        printf("-");
printf("\nSelect an option: ");
printf("\n1-View trains\n2-Book ticket\n3-View ticket\n4-Search ticket no\n5-View all ticket booking\n6-View train bookings\n7-Cancel ticket\n8-Cancel train\n9-Quit");
printf("\n\nEnter a choice:");
scanf("%d",&choice);
return choice;
}
void add_trains()
                {
                FILE *fp;
                fp=fopen("D:\\traindetail.dat","rb");
                if(fp==NULL)
                {
                    Train alltrains[4]=
                    {
                    {"12185","BPL","REWA",2100,1500},
                    {"12186","REWA","DEL",3500,2240},
                    {"34598","Hbj","AGRA",1560,1135},
                    {"89670","SATNA","MUM",4500,3360}
                };
                fp=fopen("D:\\traindetail.dat","wb");
                fwrite(alltrains,4*sizeof(Train),1,fp);
                printf("FIle should save successfully\n");
                clrscr();
                getch();
                fclose(fp);
                }
                else
                {
                    printf("File already presents\n");
                    clrscr();
                }
                }
                void view_trains()
                {
                    int i;
                    Train tr;
                    printf("Tr.N.\tFrom\tTO\tFirst Ac Fair\tSecond Ac Fair");
                    for(i=1;i<=80;i++)
                        printf("-");
                        FILE *fp=fopen("D:\\traindetail.dat","rb");
                        while(fread(&tr,sizeof(tr),1,fp)==1)
                        {
                        printf("\n%s \t%s \t%s \t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
                        printf("\n\n\n");
                        }
                        printf("Press any key to back home screen");

                        fclose(fp);
                }
                int check_train_no(char *p)
                {
                    Train tr;
                    int x;
                    FILE *fp;
                    fp=fopen("D:\\traindetail.dat","rb");
                    while(fread(&tr,sizeof(tr),1,fp)==1)
                    {
                        x=strcmp(tr.train_no,p);
                        if(x==0)
                            return 1;

                    }
                    return 0;
                }
                int check_mob_no(char *p)
                {
                    if(strlen(p)!=10)
                        return 0;
                    while(*p!='\0')
                    {
                        if(*p>='A'&&*p<='Z')
                            return 0;
                        if(*p>='a'&&*p<='z')
                            return 0;
                     p++;
                    }
                    return 1;
                }

                int get_booked_ticket_count(char *train_no,char *tc)
                {
                    FILE *fp;
                    fp=fopen("D:\\allbooking.dat","rb");
                    if(fp==NULL)
                    {
                        return 0;
                    }
                    Passenger pr;
                    int count=0;
                     while(fread(&pr,sizeof(pr),1,fp)==1)
                    {
                        if(strcmp(pr.train_no,train_no)==0&&pr.p_class==tc)
                            count++;
                    }
                    fclose(fp);
                    return count;
                }
                int last_ticket_no()
                {
                    FILE *fp;
                    Passenger pr;
                    fp=fopen("D:\\allbooking.dat","rb");
                    if(fp==NULL)
                    {
                        return 0;
                    }
                    fseek(fp,-1*sizeof(pr),SEEK_END);
                    fread(&pr,sizeof(pr),1,fp);
                    fclose(fp);
                     return pr.ticketno;
                }

                Passenger * get_passenger_details()
                {
                    clrscr();
                    char * pos;
                    int valid=1;
                    int i;
                    gotoxy(70,1);
                    textcolor(LIGHTGREEN);
                    printf("Press 0 to exit");
                    textcolor(YELLOW);
                    gotoxy(1,1);
                    static Passenger psn;
                    printf("Enter passenger name:");
                    fflush(stdin);
                    fgets(psn.p_name,20,stdin);
                    pos=strchr(psn.p_name,'\n');
                    *pos='\0';
                    if(strcmp(psn.p_name,"0")==0)
                    {
                        textcolor(LIGHTRED);
                        gotoxy(1,22);
                        printf("Reservation cancelled");
                        getch();
                        textcolor(YELLOW);
                        return 0;
                    }
                    gotoxy(1,2);
                    printf("Enter your gender in upper case(M/F):");
                    do
                    {
                        valid=1;
                    scanf("%c",&psn.gender);
                    if(psn.gender=='0')
                    {
                       gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,22);
                       textcolor(LIGHTRED);
                       printf("Reservation cancelled");
                       getch();
                       textcolor(YELLOW);
                       return 0;
                    }
                    if(psn.gender!='M'&&psn.gender!='F')
                    {
                        valid=0;
                        gotoxy(1,22);
                        printf("\t\t\t\t\t\t\t");
                        gotoxy(1,22);
                        textcolor(LIGHTRED);
                        printf("wrong input please input correct..");
                        textcolor(YELLOW);
                        gotoxy(38,2);
                        printf("\t\t\t\t\t\t\t\t");
                        gotoxy(38,2);
                    }
                    }while(valid==0);
                    gotoxy(1,22);
                    printf("\t\t\t\t\t");
                    gotoxy(1,3);
                    printf("Enter a train number:");
                    do
                    {
                    fflush(stdin);
                    fgets(psn.train_no,20,stdin);
                    pos=strchr(psn.train_no,'\n');
                    *pos='\0';
                    if(strcmp(psn.train_no,"0")==0)
                    {
                        gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,22);
                       textcolor(LIGHTRED);
                       printf("Reservation cancelled");
                       getch();
                       textcolor(YELLOW);
                       return 0;
                    }
                    i=check_train_no(psn.train_no);
                    if(i==0)
                    {
                        textcolor(LIGHTRED);
                       gotoxy(1,22);
                       printf("\t\t\t\t\t\t");
                       gotoxy(1,22);
                    printf("Wrong train number you input");
                        textcolor(YELLOW);
                        gotoxy(22,3);
                        printf("\t\t\t\t\t");
                        gotoxy(22,3);

                    }
                    }while(i==0);
                    gotoxy(1,22);
                    printf("\t\t\t\t");
                    gotoxy(1,4);
                    printf("Enter your address:");
                    fflush(stdin);
                    fgets(psn.address,20,stdin);
                    pos=strchr(psn.address,'\n');
                    *pos='\0';
                    if(strcmp(psn.address,"0")==0)
                    {
                        textcolor(LIGHTRED);
                        gotoxy(1,22);
                        printf("\t\t\t\t\t\t");
                        gotoxy(1,22);
                        printf("Train reservation cancelled..");
                        textcolor(YELLOW);
                        gotoxy(1,5);
                        return 0;
                    }
                    gotoxy(1,5);
                    printf("Enter your mobile number:");
                    do
                    {
                    fflush(stdin);
                    scanf("%s",psn.mob_no);
                    if(strcmp(psn.mob_no,"0")==0)
                    {
                        gotoxy(1,22);
                        printf("\t\t\t\t");
                        gotoxy(1,22);
                        textcolor(LIGHTRED);
                        printf("train reservation should be cancelled..");
                        gotoxy(25,1);
                        textcolor(YELLOW);
                        printf("\t\t\t\t\t\t");
                        gotoxy(25,1);
                        return 0;
                    }
                    i=check_mob_no(psn.mob_no);
                    if(i==0)
                    {
                        gotoxy(1,22);
                        textcolor(LIGHTRED);
                        printf("\t\t\t\t\t\t\t");
                        gotoxy(1,22);
                        printf("please input correct mobile number...");
                        textcolor(YELLOW);
                        gotoxy(26,5);
                        printf("\t\t\t\t");
                        gotoxy(26,5);
                    }
                    }while(i==0);
                    gotoxy(1,22);
                    printf("\t\t\t\t\t\t\t\t");
                    gotoxy(1,6);
                    textcolor(YELLOW);
                    printf("Enter your age:");
                    do
                    {
                        i=1;
                        scanf("%d",&psn.age);
                        if(psn.age==0)
                        { gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,22);
                       textcolor(LIGHTRED);
                       printf("Reservation cancelled");
                       textcolor(YELLOW);
                            return 0;

                        }
                        if(psn.age<=0)
                        {
                            i=0;
                            gotoxy(1,22);
                            textcolor(LIGHTRED);
                            printf("\t\t\t\t\t");
                            gotoxy(1,22);
                            printf("please input correct age");
                            textcolor(YELLOW);
                            gotoxy(16,6);
                            printf("\t\t\t\t");
                            gotoxy(16,6);
                        }
                    }while(i==0);
                    textcolor(YELLOW);
                    gotoxy(1,22);
                    printf("\t\t\t\t\t\t\t\t");
                    gotoxy(1,7);
                    printf("Enter a class of ticket(F/S):");
                    do
                    {
                        i=1;
                        fflush(stdin);
                    scanf("%c",&psn.p_class);
                    if(psn.p_class=='0')
                    {
                       gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,22);
                       textcolor(LIGHTRED);
                       printf("Reservation cancelled");
                       getch();
                       textcolor(YELLOW);
                       return 0;
                    }

                    if(psn.p_class!='F'&&psn.p_class!='S')
                    {
                        gotoxy(1,22);
                        printf("\t\t\t\t\t\t\t");
                        textcolor(LIGHTRED);
                        gotoxy(1,22);
                        printf("Please input correct class(in upper case)...");
                        i=0;
                        textcolor(YELLOW);
                        gotoxy(30,7);
                        printf("\t\t\t\t\t");
                        gotoxy(30,7);
                        textcolor(YELLOW);
                    }}while(i==0);
                    gotoxy(1,2);
                    printf("\t\t\t\t\t\t\t\t");
                    textcolor(YELLOW);
                    gotoxy(1,8);
                return(&psn);
                }
                    int book_ticket(Passenger p)
                    {
                        int ticket_count;

                        ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
                        if(ticket_count==2)
                        {
                            textcolor(LIGHTRED);
                            printf("All seats full in train no %s in %c class !\n",p.train_no,p.p_class);
                            return -1;
                        }
                    p.ticketno=last_ticket_no()+1;

                        FILE *fp=fopen("D:\\allbooking.dat","ab");
                        if(fp==NULL)
                        {
                            textcolor(LIGHTRED);
                            printf("sorry file should not open..");
                            return  0;
                        }
                        fwrite(&p,sizeof(p),1,fp);
                        fclose(fp);
                        return p.ticketno;
                        }

int check_ticket()
{
    clrscr();
    int ticket;
    int i;
    gotoxy(75,1);
    textcolor(GREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
   printf("Enter your ticket no:");
                    do
                    {
                        i=1;
                        scanf("%d",&ticket);
                        if(ticket==0)
                        {
                            gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,22);
                       textcolor(LIGHTRED);
                       printf("not ticket view");
                       getch();
                       gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,1);
                       printf("\t\t\t");
                       textcolor(YELLOW);
                            return 0;

                        }
                        if(ticket<=0)
                        {
                            i=0;
                            gotoxy(1,22);
                            textcolor(LIGHTRED);
                            printf("\t\t\t\t\t");
                            gotoxy(1,22);
                            printf("please input correct ticket no");
                            textcolor(YELLOW);
                            gotoxy(22,1);
                            printf("\t\t\t\t");
                            gotoxy(22,1);
                        }
                    }while(i==0);
                  return ticket;
}
                     void view_ticket(int tickettn)
                    {

                        int found=0;
                      textcolor(YELLOW);
                      gotoxy(1,2);
                      FILE *fp;
                      Passenger pr;
                      fp=fopen("D:\\allbooking.dat","rb");
                      if(fp==NULL)
                      {
                        printf("Booking should not done");
                        return;

                       }
                       clrscr();
                       while(fread(&pr,sizeof(pr),1,fp)==1)
                       {
                           if(tickettn==pr.ticketno)
                           {
                        printf("NAME: %s\nMOBNO: %s\nTICKETN: %d\nAGE:%d\nTRAINN: %s\nGENDER: %c\nCLASS: %c\nADDRESS: %s",pr.p_name,pr.mob_no,pr.ticketno,pr.age,pr.train_no,pr.gender,pr.p_class,pr.address);
                         found++;
                           }

                       }
                       if(found==0)
                       printf("No ticket number found");
                       fclose(fp);
                    }
                    char *  mob_no()
                    {
                        clrscr();
                       static char mobno[11];
                        int i;
                         textcolor(GREEN);
                      gotoxy(74,1);
                      printf("Press 0 to exit");
                      textcolor(YELLOW);
                      gotoxy(1,1);
                      printf("Enter your mobile number to search the ticket:");
                      getch();
                    do
                    {
                    fflush(stdin);
                    scanf("%s",mobno);
                    if(strcmp(mobno,"0")==0)
                    {
                        gotoxy(1,22);
                        printf("\t\t\t\t");
                        gotoxy(1,22);
                        textcolor(LIGHTRED);
                        printf("User not want to search the ticket...");
                        getch();
                        clrscr();
                        textcolor(YELLOW);
                        return NULL;
                    }
                    i=check_mob_no(mobno);
                    if(i==0)
                    {
                        gotoxy(1,22);
                        textcolor(LIGHTRED);
                        printf("\t\t\t\t\t\t\t");
                        gotoxy(1,22);
                        printf("please input correct mobile number...");
                        textcolor(YELLOW);
                        gotoxy(47,1);
                        printf("\t\t\t\t");
                        gotoxy(47,1);
                    }
                    }while(i==0);
                     return mobno;
                    }

                    int cancel_ticket(int ticket_no)
                    {
                       FILE *fp1;
                       FILE *fp2;
                       int found=0;
                       Passenger pr;
                       fp1=fopen("D:\\allbooking.dat","rb");
                       if(fp1==NULL)
                       {
                           printf("Any booking should be not done by the customer...");
                           return 0;
                       }
                       fp2=fopen("D:\\mybooking.dat","wb+");
                       while(fread(&pr,sizeof(pr),1,fp1)==1)
                       {
                        if(ticket_no!=pr.ticketno)
                           {
                            fwrite(&pr,sizeof(pr),1,fp2);
                           }
                           else
                            found=1;
                       }
                       fclose(fp1);
                       fclose(fp2);
                       if(found==0)
                       {
                       remove("D:\\mybooking.dat");
                       }
                       else
                       {
                           remove("D:\\allbooking.dat");
                           rename("D:\\mybooking.dat","D:\\allbooking.dat");
                       }
                        return found;
                    }

                    int *get_ticket_no(char * p_mob_no)
                    {
                        int count=0;
                        int *p;
                        FILE *fp=fopen("D:\\allbooking.dat","rb");
                        if(fp==NULL)
                        {
                            return NULL;
                        }
                        Passenger pr;
                        while(fread(&pr,sizeof(pr),1,fp)==1)
                        {
                            if(strcmp(pr.mob_no,p_mob_no)==0)
                                count++;
                        }
                        if(count==0)
                        {
                            fclose(fp);
                            return NULL;
                        }
                        p=(int*)malloc((count+1)*sizeof(int));
                        int i=0;
                          while(fread(&pr,sizeof(pr),1,fp)==1)
                        {
                            if(strcmp(pr.mob_no,p_mob_no)==0)
                                *(p+i)=pr.ticketno;
                                i++;
                        }
                        *(p+i)=-1;
                        fclose(fp);
                        return p;
                    }
                    char *trainno()
                    {
                         static char train_no[20];
                         char *pos;
                         int i;
                         textcolor(GREEN);
                         gotoxy(74,1);
                         printf("Press 0 to exit");
                         gotoxy(1,1);
                         textcolor(YELLOW);
                      printf("Enter a train number:");
                    do
                    {

                    fflush(stdin);
                    fgets(train_no,20,stdin);
                    pos=strchr(train_no,'\n');
                    *pos='\0';
                    if(strcmp(train_no,"0")==0)
                    {
                        gotoxy(1,22);
                       printf("\t\t\t\t\t");
                       gotoxy(1,22);
                       textcolor(LIGHTRED);
                       printf("You not want to cancel the train");
                       getch();
                       textcolor(YELLOW);
                       return 0;
                    }
                    i=check_train_no(train_no);
                    if(i==0)
                    {
                        textcolor(LIGHTRED);
                       gotoxy(1,22);
                       printf("\t\t\t\t\t\t");
                       gotoxy(1,22);
                    printf("Wrong train number you input");
                        textcolor(YELLOW);
                        gotoxy(22,1);
                        printf("\t\t\t\t\t");
                        gotoxy(22,1);

                    }
                    }while(i==0);
                    gotoxy(1,22);
                    printf("\t\t\t\t\t\t");
                    return train_no;
                    }
                    int cancel_train(char *p)
                    {
                        char train[20];
                        strcpy(train,p);
                       FILE *fp1;
                       FILE *fp2;
                       int found=0;
                       Passenger pr;
                       fp1=fopen("D:\\allbooking.dat","rb");
                       if(fp1==NULL)
                       {
                           printf("Any booking should be not done by the customer...");
                           return 0;
                       }
                       fp2=fopen("D:\\mybooking.dat","wb+");
                       while(fread(&pr,sizeof(pr),1,fp1)==1)
                       {
                        if(strcmp(pr.train_no,train)!=0)
                           {
                            fwrite(&pr,sizeof(pr),1,fp2);
                           }
                           else
                            found=1;
                       }
                       fclose(fp1);
                       fclose(fp2);
                       if(found==0)
                       {
                       remove("D:\\mybooking.dat");
                       }
                       else
                       {
                           remove("D:\\allbooking.dat");
                           rename("D:\\mybooking.dat","D:\\allbooking.dat");
                       }
                       gotoxy(1,2);
                       printf("Train should be cancelled of  given number..... ");
                       printf("%s",train);
                    }
                    void allbooking()
                    {
                        Passenger pr;
                        FILE *fp;
                       int count=0;
                        fp=fopen("D:\\allbooking.dat","rb");
                        if(fp==NULL)
                        {
                            printf("any ticket should be not booked yet...");
                            return;
                        }
                         while(fread(&pr,sizeof(pr),1,fp)==1)
                       {
                           {
                               count++;
                        printf("NAME: %s\nMOBNO: %s\nTICKETN: %d\nAGE:%d\nTRAINN: %s\nGENDER: %c\nCLASS: %c\nADDRESS: %s\n\n",pr.p_name,pr.mob_no,pr.ticketno,pr.age,pr.train_no,pr.gender,pr.p_class,pr.address);
                           }


                    }
                    if(count==0)
                        printf("No booking done.....");
                        return;
                    }
                    void trainbooking(char *p)
                    {
                       char train[20];
                        strcpy(train,p);
                        Passenger pr;
                        int count=0;
                        int i;
                        FILE *fp;
                         fp=fopen("D:\\allbooking.dat","rb");
                         gotoxy(1,1);
                         for(i=1;i<90;i++)
                            printf("-");

                        if(fp==NULL)
                        {
                            printf("any ticket should be not booked yet...");
                            return;
                        }
                         while(fread(&pr,sizeof(pr),1,fp)==1)
                       {
                           if(strcmp(pr.train_no,train)==0)
                           {

                        printf("NAME: %s\nMOBNO: %s\nTICKETN: %d\nAGE:%d\nTRAINN: %s\nGENDER: %c\nCLASS: %c\nADDRESS: %s\n\n",pr.p_name,pr.mob_no,pr.ticketno,pr.age,pr.train_no,pr.gender,pr.p_class,pr.address);
                           count++;
                           }
                       }

                        if(count==0)
                        {
                            printf("No ticket should be booked on this train");
                        }
                         fclose(fp);
                         return;

                    }
                    void view_all_tickets(char *pmob_no,int *pticket_no)
                    {
                     if(pticket_no==NULL)
                     {
                     textcolor(LIGHTRED);
                     printf("Sorry! No tickets booked against mobile no %s",pmob_no);
                     textcolor(WHITE);
                     printf("\n\nPress any key to go back to the main screen");
                     textcolor(YELLOW);
                     getch();
                     return;
                     }
                     clrscr();
                     int i;

                   printf("Following are tickets booked for mobile no %s",pmob_no);
                   printf("\n\nTICKET NO\n");
                    printf("---------");
                    for(i=0;*(pticket_no+i)!=-1;i++)
                    {
                    printf("\n\n%d\n",*(pticket_no+i));
                    }
                    textcolor(WHITE);
                    printf("\n\nPress any key to go back to the main screen");
                    textcolor(YELLOW);
                    free(pticket_no);
                    getch();
                    return;
               }

