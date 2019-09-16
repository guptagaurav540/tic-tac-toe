#include<stdio.h>
char poisition[9];
    int win=0;
int check_win(char x)
{
    int i,j,k;
    if(poisition[0]==x && poisition[1]==x && poisition[2]==x)
    {
        return(1);
    }
    else if(poisition[3]==x && poisition[4]==x && poisition[5]==x)
    {
        return(1);
    }
    else if(poisition[6]==x && poisition[7]==x && poisition[8]==x)
    {
        return(1);
    }
    else if(poisition[0]==x && poisition[3]==x && poisition[6]==x)
    {
        return(1);
    }
    else if(poisition[1]==x && poisition[4]==x && poisition[7]==x)
    {
        return(1);
    }
    else if(poisition[2]==x && poisition[5]==x && poisition[8]==x)
    {
        return(1);
    }
    else if(poisition[0]==x && poisition[4]==x && poisition[8]==x)
    {
        return(1);
    }
    else 
    {
        return(0);
    }

}


int main()
{
    char f_name[10],s_name[10];
    printf("Player 1 :");
    scanf("%s",f_name);
    
    for(int i=0;i<9;i++)
    {
       poisition[i]=' '; 
    }
    printf("Player 2 :");
    scanf("%s",s_name);

    for(int i=1;i<10;i++)
    {
        
            printf(" %c | %c | %c \n",poisition[0],poisition[1],poisition[2]);
            printf("---------------\n");
            printf(" %c | %c | %c \n",poisition[3],poisition[4],poisition[5]);
            printf("---------------\n");
            printf(" %c | %c | %c \n",poisition[6],poisition[7],poisition[8]);
        

        int pos;
        if(i%2!=0)
        {
            printf("%s 0 and %s 1\n",f_name,s_name);
            printf("%s turn :",f_name);
            do
            {
                scanf("%d",&pos);
                pos=pos-1;
                if(poisition[pos]!=' ')
                {   
                    printf("Invailid choice :");
                }
            }while(poisition[pos]!=' ');
            poisition[pos]='0';
            win=check_win('0');
            if(win)
            {
                printf("win %s",f_name);
                break;
            }if(i==9){

                printf("GAME ENDED");
                }
        }
        else
        {
            printf("%s 0 and %s 1\n",f_name,s_name);
            printf("%s turn :",s_name);
            do
            {
                scanf("%d",&pos);
                pos=pos-1;
                if(poisition[pos]!=' ')
                {
                    printf("Invailid choice :");
                }
            }while(poisition[pos]!=' ');
            poisition[pos]='1';
            win=check_win('1');
            if(win)
            {
                printf("win %s",s_name);
                break;
            }

        }
    }
}
