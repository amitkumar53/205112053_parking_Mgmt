#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<windows.h>

struct node
{
    char plate [15] ;
    char time [10];
    struct node *link ;
} *front[10], *rear[10] ;

char plate[15],time[10], temp[15],t[15] ;
int i,spc=0;

void add_dq ( struct node**, struct node**, char* ,char*) ;
char* del_dq ( struct node**, struct node**, int ) ;
void push ( struct node**, char* ) ;
char* pop ( struct node** ) ;
void q_display ( struct node * ) ;

main( )
{
    int s,bay,lane,lc,ch;
    
    while(1)
    {
        printf("\n*********PARKING LOT*************\n\n");
        printf("-----------------------------------\n");
        printf("  Total Parking Spaces   :100    \n");
        printf("      Total bay         : 10    \n");
        printf("      Each bay has 10 Lane.     \n");  
        printf("  Avaialble Spaces       :%d    \n",100-spc);
        printf("-----------------------------------\n");
        printf("\t1.In                      \n");
        printf("\t2.Out                     \n");
        printf("\t3.View Parking lot Status \n");
        printf("\t4.Exit                    \n");
        
        
        printf("\n\nEnter your choice:");
        scanf("%d",&ch);
        
        
        if(ch==1)
        {
            printf ( "\nEnter Token num provided by Parking Person:" ) ;
            fflush(stdin);
            gets ( plate ) ;
            printf("Enter the arrival time (hh:mm):");
            fflush(stdin);
            gets(time);
            bay = 0 ;  
            lane = 10 ;
            lo:
            printf("Enter the Bay Number where you want to park the Vehicle :");
            scanf("%d",&bay);
            
            if(bay>10)
            {
                printf("\nWrong location. Enter it again.");
                goto lo;
            }              
            spc++;
            s = count ( front[i] ) ;
            if ( s <= lane )
            {
                add_dq ( &front[ bay ], &rear[ bay ], plate,time ) ;
                printf ( "\nVehicle parked in bay %d.\n", bay ) ;
            }    
            else
                printf ( "\nNo room available" ) ;  
            getch();      
        }
        else if(ch==2)
        {
            printf ( "\nEnter Token num:" ) ;
            fflush(stdin);
            gets ( plate ) ;
            for ( i = 1 ; i <=10 ; ++i )
            {
                s = search ( front[i], plate ) ;
                if ( s != -1 )
                {
                    bay = i ;
                    break ;
                }
            }
            if ( i == 11 )
                printf ( "\nNo such Vehicle!!\n" ) ;
            else
            {
                spc--;
                printf ( "\nVehicle found in Bay %d.", bay ) ;
                del_dq ( &front[ bay ], &rear[ bay ], s ) ;
            }
            getch();
        }
        else if(ch==3)
        {
            printf("\n\t Enter the bay :");
            scanf("%d",&bay);
            q_display(front[bay]);
            getch();
        }    
        else if(ch ==4)
            exit(0) ;
        else
            printf("\nWrong Input!!!!");
            
        printf("\n\n");
    }  
    getch();  
    
}

void add_dq ( struct node **f, struct node **r, char *p, char *t )
{
    struct node *q ;
    

    q = ( struct node * ) malloc ( sizeof ( struct node ) ) ;
    strcpy ( q -> plate, p ) ;
    strcpy ( q -> time, t);
    q -> link = NULL ;

    
    if ( *f == NULL )
        *f = q ;
    else
        ( *r ) -> link = q ;
  
    *r = q ;
}

char* del_dq ( struct node **f, struct node **r, int n )
{
    struct node *q, *top = NULL ;
    
    
    if ( *f == NULL )
        printf ( "No Vehicle." ) ;
    else
    {
        if ( n == 0 )
        {
            strcpy ( temp, ( *f ) -> plate ) ;
            q = *f ;
            *f = ( *f ) -> link ;
            free ( q ) ;
            return temp ;
        }


        
        for ( i = 1 ; i <= n ; i++ )
        {
            

            push ( &top, ( *f ) -> plate ) ;
            push ( &top, ( *f ) -> time ) ;

            

            q = *f ;
            *f = q -> link ;
            free ( q ) ;
        }

        

        q = *f ;
        *f = q -> link ;
        free ( q ) ;

        for ( i = 1 ; i <= n ; i++ )
        {
            strcpy ( t, pop ( &top ) ) ;
            strcpy ( temp, pop ( &top ) ) ;

            

            add_dq ( f, r,temp,t) ;
        }
    }
}

int count ( struct node *q )
{
    int c = 0 ;

    
    while ( q!= NULL )
    {
        q = q -> link ;
        c++ ;
    }
    return c ;
}

int search ( struct node *q, char *p )
{
    int s = -1, c = 0 ;

    while ( q != NULL )
    {
        if ( strcmp ( p, q -> plate ) == 0 )
        {
            s = c ;
            break ;
        }
        else
        {
            q = q -> link ;
            c++ ;
        }
    }
    return ( s ) ;
}


void push ( struct node **s, char* item )
{
    struct node *q ;
    q = ( struct node* ) malloc ( sizeof ( struct node ) ) ;
    strcpy ( q -> plate, item ) ;
    q -> link = *s ;
    *s = q ;
}


char* pop ( struct node **s )
{
    struct node *q ;

    
    if ( *s == NULL )
    {
        return NULL ;
    }
    else
    {
        q = *s ;
        strcpy ( temp, q -> plate ) ;
        *s = q -> link ;
        free ( q ) ;
        return ( temp ) ;
    }
}

void q_display ( struct node *q )
{
    for(i=1;i<=10;i++)
    {
        printf("\nLane %d :",i);
        if(q!=NULL)
        {
            printf ("Occupied by Vehicle No. %s @ %s",q->plate,q->time) ;
            q = q -> link ;
        }
        else
        printf("Unoccupied.");  
    }
    printf ( "\n" ) ;
}
