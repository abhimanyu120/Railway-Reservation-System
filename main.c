#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int i,choice;
    char search[10];
    Passenger *ptr;
    add_trains();
    int ticket_no;
    char *p;
    int *count;
    int cancel;
    int found;
    char*train;
    char *mobno;
    int *ticket;

while(1)
{
    choice=enterchoice();
    if(choice==9)
    {
        exit(0);
    }
switch(choice)
{
case 1:
    clrscr();
    view_trains();
    getch();
    clrscr();
    textcolor(WHITE);
    break;
case 2:
    clrscr();
ptr= get_passenger_details();
if(ptr!=0)
{
    ticket_no=book_ticket(*ptr);
    if(ticket_no==-1)
    {
        textcolor(LIGHTRED);
        printf("Booking failed!!!!!!!");
    }
        else
        {
            printf("Ticket successfully booked!!!!");
        printf("\nYour ticket number is %d",ticket_no);
        }
        textcolor(WHITE);
        printf("\npress any key to back main screen...");
        getch();
        clrscr();
}
clrscr();
     break;
case 3:
ticket_no=check_ticket();
if(ticket_no>0)
{
    view_ticket(ticket_no);
    getch();
    clrscr();
}

    break;
case 4:
  mobno=  mob_no();
  if(mobno!=NULL)
  {
     ticket= get_ticket_no(mobno);
     clrscr();
     view_all_tickets(mobno,ticket);
     getch();
     clrscr();
  }
    break;
case 5:
     clrscr();
      allbooking();
      getch();
      clrscr();
    break;
case 6:
 clrscr();
    train=trainno();
    clrscr();
    if(train!=NULL)
    {
        clrscr();
        trainbooking(train);
        getch();
        clrscr();
    }

    break;
case 7:
    ticket_no=check_ticket();
    clrscr();
    if(ticket_no!=0)
    {
       found=cancel_ticket( ticket_no);
       if(found==0)
   {
       printf("No ticket of this  number: %d",ticket_no);
   }
   else
    printf("Ticket should be cancelled of this number: %d",ticket_no);

    }
    getch();
    clrscr();
    break;
case 8:
    clrscr();
    train=trainno();
    if(train!=NULL)
    {
    cancel_train(train);
    }
    getch();
    clrscr();


    break;
default:
    textcolor(RED);
    printf("Wrong choice... \nplease input correct\n");
    textcolor(YELLOW);
printf("Enter a choice: ");
scanf("%d",&choice);
}
}

getch();
    return 0;

}
