#ifndef RLYRES_H_INCLUDED
#define RLYRES_H_INCLUDED
typedef struct train
{
    char train_no[10];
    char from[10];
    char to[10];
    int fac_fare;
    int sac_fare;
}Train;
typedef struct passenger
{
    char p_name[10];
    char gender;
    char train_no[20];
    char p_class;
    char address[20];
    int age;
    int ticketno;
    char mob_no[11];

} Passenger;

int enterchoice();
void add_trains();
void view_trains();
int book_ticket(passenger);
int* get_ticket_no(char *);
void view_ticket(int);
void view_all_bookings();
void view_bookings(char *);
int cancel_ticket(int);
int cancel_train(char *);
Passenger * get_passenger_details();
int check_train_no(char *);
int get_booked_ticket_count(char *,char *);
int last_ticket_no();
int book_ticket(passenger);
int check_mob_no(char *);
int check_ticket();
void view_ticket(int);
int search_ticket(char *);
char * mob_no();
char *accept_mob_no();
int check_mob_no(char*);
int *get_ticket_no(char *);
 char *trainno();
 void allbooking();
 void trainbooking(char *);
 void view_all_tickets(char *,int *);
#endif // RLYRES_H_INCLUDED
