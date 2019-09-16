#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include"conio.h"
#include<time.h>
int fd,portno;
struct sockaddr_in srv;
struct sockaddr_in cli,srv_addr;
int newfd;
unsigned int cli_len ;
int pos[2],win=0;
char poisition[9];

int check_win(char cc[],char x)
{
    int i,j,k;
    if(cc[0]=='0' && cc[1]==x && cc[2]==x)
    {
        return(1);
    }
    else if(cc[3]==x && cc[4]==x && cc[5]==x)
    {
        return(1);
    }
    else if(cc[6]==x && cc[7]==x && cc[8]==x)
    {
        return(1);
    }
    else if(cc[0]==x && cc[3]==x && cc[6]==x)
    {
        return(1);
    }
    else if(cc[1]==x && cc[4]==x && cc[7]==x)
    {
        return(1);
    }
    else if(cc[2]==x && cc[5]==x && cc[8]==x)
    {
        return(1);
    }
    else if(cc[0]==x && cc[4]==x && cc[8]==x)
    {
        return(1);
    }
    else 
    {
        return(0);
    }

}



void create()
{
    if((fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        exit(1);
    }
}
void bind_server()
{
    bzero((char *)&srv,sizeof(srv));

    srv.sin_family=AF_INET;
    srv.sin_port=htons(portno);
    // bind a client may connect to any of server addresses

    srv.sin_addr.s_addr=INADDR_ANY;
    if(bind(fd,(struct sockaddr*) &srv,sizeof(srv))<0)
    {
        perror("Bind failed");
        exit(1);
    }


}
void listen_server()
{
    if(listen(fd,5)<0)
    {
        perror("Listen");
        exit(1);
    }
}
void accept_server()
{
    cli_len=sizeof(cli);
    newfd=accept(fd,(struct sockaddr*) &cli, &cli_len);
    if(newfd<0)
    {
        perror("accept");
        exit(1);
    }
    else
    {
        printf("Your friend is joind :\n");
    }
    
    
}
void connect_client()
{
    bzero((char *)&srv,sizeof(srv));
    srv.sin_family=AF_INET;
    srv.sin_port=htons(portno);
    //bcopy((char *)server-> h_addr ,(char *)&srv.sin_addr.s_addr,server->h_length);

    if(connect(fd,(struct sockaddr*) &srv,sizeof(srv))<0)
    {
        perror("connect");
        exit(1);
    }
    else{
        printf("You are connected with your Friend :\n");
    }
}

void write_read(int choice)
{
    char cc[9];
    int j,k;
    if(portno%2)
    {
        j=4;
        k=5;
    }
    else
    {
        j=5;
        k=4;
    }
    
    if(choice==1){
    for(int i=0;i<4;i++)
    {   
		
        recv(newfd,&pos,2*sizeof(int),0);
        recv(newfd,&win,sizeof(int),0);
        poisition[pos[0]-1]='1';
        printf(" %c | %c | %c \n",poisition[0],poisition[1],poisition[2]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[3],poisition[4],poisition[5]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[6],poisition[7],poisition[8]);
        printf("\nfriend's turn : %d\n",pos[0]);
				
        if(win==1)
        {
            printf("Friend's win:\n");
            break;
        }
		
        do
        {
            printf("Your turn:");
            scanf("%d",&pos[0]);
			system("clear");
            if(poisition[pos[0]-1]!=' ')
            {   
                printf("Invailid choice :\n");
            }
        }while(poisition[pos[0]-1]!=' ');
		system("clear");        
		poisition[pos[0]-1]='0';
        cc[pos[0]-1]='0';
        win=check_win(cc,'0');
        send(newfd,&pos,2*sizeof(int),0);
        send(newfd,&win,sizeof(int),0);
        printf(" %c | %c | %c \n",poisition[0],poisition[1],poisition[2]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[3],poisition[4],poisition[5]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[6],poisition[7],poisition[8]);
        if(win)
        {
            printf("You win \n");
            break;
        }
       
    }close(newfd);
    }
    else if(choice==2)
    for(int i=0;i<5;i++)
    {
        do
        {
			
            printf("Your turn:");
            scanf("%d",&pos[0]);
            if(poisition[pos[0]-1]!=' ')
            {   
                printf("Invailid choice :\n");
                printf("Retry...\n");
            }
        }while(poisition[pos[0]-1]!=' ');
        
		poisition[pos[0]-1]='1';
        cc[pos[0]-1]='1';
        win=check_win(cc,'1');
        send(fd,&pos,2*sizeof(int),0);
        send(fd,&win,sizeof(int),0);
        printf(" %c | %c | %c \n",poisition[0],poisition[1],poisition[2]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[3],poisition[4],poisition[5]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[6],poisition[7],poisition[8]);
        if(win)
        {
            printf("You win ");
            break;
        }
				system("clear");		
        recv(fd,&pos,2*sizeof(int),0);
        recv(fd,&win,sizeof(int),0);
        poisition[pos[0]-1]='0';
        printf(" %c | %c | %c \n",poisition[0],poisition[1],poisition[2]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[3],poisition[4],poisition[5]);
        printf("---------------\n");
        printf(" %c | %c | %c \n",poisition[6],poisition[7],poisition[8]);
        printf("\nfriend's turn : %d\n",pos[0]);
        if(win)
        {
            printf("Friend's win:");
            break;
        }
    }
    close(fd);
}

int main()
{
    system("clear");
    printf("Welcome :\n");
    printf("For start press any key :\n");
    getch();
    system("clear");
    printf("1. Create room :\n");
    printf("2. Join room :\n");
    printf("3. Offline mode :\n");
    printf("Enter your choice :\n");
    int choice,gamecode;
    scanf("%d",&choice);
    system("clear");
    char *args[]={"./simple",NULL};
    for(int i=0;i<9;i++)
    {
       poisition[i]=' '; 
    }

    switch(choice)
    {
        
        case 1:
            srand(time(0));
            gamecode = (rand()%(9999 - 5000 + 1)) + 5000;
            printf("Room code : %d\n",gamecode);
            printf("Say your friend to enter the same Room-code for join :\n");
            portno = gamecode;
            //working as a server 
            //system("clear");
            printf("Waiting for your Friend....\n");
            create();
            bind_server();
            listen_server();
            accept_server();
            //system("clear");
            
            printf(" 1 | 2 | 3 \n");
            printf("---------------\n");
            printf(" 4 | 5 | 6 \n");
            printf("---------------\n");
            printf(" 7 | 8 | 9 \n");
            write_read(choice);
        case 2:
            printf("Enter Room code :");
            scanf("%d",&gamecode);
            create();
            //system("clear");
            // working as a client
            printf("Waiting for your Friend....\n");
            portno=gamecode; 
            connect_client();
            //system("clear");
            printf(" 1 | 2 | 3 \n");
            printf("---------------\n");
            printf(" 4 | 5 | 6 \n");
            printf("---------------\n");
            printf(" 7 | 8 | 9 \n");
            write_read(choice);
        case 3:
            //offlin mode
            execv(args[0],args);
    }
}

