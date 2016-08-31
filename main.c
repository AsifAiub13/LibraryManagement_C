#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define IN 1
#define OUT 0

void Addbook();
void Searchbook();
void Displaybook();
void Issue();
void Exit();
char info[500];


struct
{
  int bid;
  char bname[25] ;
  char author[25];
  int nooftitles;
  char titles[500];
  int status;
}book;


FILE *librecord;

FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
int main()
{
    int choice=0,i;


    do{
    printf("Library Management System----[RAHMAN MD. HABIBUR]\n");
    printf("\n 1.Add A New Book \n 2.Search a book \n 3.Display all book's info\n 4.Issue \n 5.Exit\n\t Enter your choice <1-5>: ");
    scanf("%i",&choice);


    switch (choice)
    {
        case 1:
            Addbook();
            break;
        case 2:
            Searchbook();
            break;
        case 3:
            Displaybook();
            break;
        case 4:
            Issue();
            break;


        case 5:
            Exit();
        default:
            printf(" ! Invalid Input...\n");
    }
}while(choice!=5);
 return (0);
}

void Addbook()
{
    int i;
    book.status=IN;
            //opening the librecord file
    librecord = fopen("librecord.txt","a+");
    printf("Enter The unique id of The Book :(Integer) \n");
        scanf("%d",&book.bid);
    printf("Enter The Name of The Book :\n");
        scanf("%s",book.bname);
    printf("Enter The Name of Author :\n");
        scanf("%s",book.author);
    printf("Enter The Number of Copies Of The Book:(Integer)\n");
        scanf("%d",&book.nooftitles);
    fprintf(librecord,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,book.status,book.nooftitles);
    //printf("Enter The Copies Of The Book : \n");

        fprintf(librecord,"%s\t",book.titles);

    fclose(librecord);
    printf("A New Book has been Added Successfully...\n");

}

void Searchbook()
{
    int i;
    char Target[25],stats[25];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        while(!feof(librecord)&& Found==0)
        {
        fscanf(librecord,"%d %s %s %d %d", &book.bid,&book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.bname)==0)
                Found=1;

        }
        if(Found)
        {
            if(book.status==IN)
                strcpy(stats,"IN");
            else
                strcpy(stats,"OUT");

            printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n",book.bid,book.bname,book.author,stats);
            }
        else if(!Found)
            printf("! There is no such Entry...\n");
        fclose(librecord);
    }

}

void Displaybook()
{
    librecord = fopen("librecord.txt","a+");
    printf("\nBookid\tName\tAuthor\tStatus\tNo.\tTitles\n",info);
    do
    {
        fgets(info,500,librecord);
        printf("%s\n",info);
    }while(!feof(librecord));
    fclose(librecord);
}
void Issue()
{
    int mid,i,Found1=0,Found2=0;char issubookname[20];
    printf("\nEnter The Name of book :");
                scanf("%s",issubookname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf(" ! The file is empty...\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                        if(strcmp(issubookname,book.bname)==0)
                            Found2=1;

                    }
                    if(Found2)
                    {
                        if(book.status==0)
                        {
                            printf(" ! Book already issued...\n");
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");

                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issubookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,0,book.nooftitles);
                                    }
                                    for(i=0;i<book.nooftitles;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);

                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");

                            printf("Book Successfully issued...\n");
                        }

                    else
                        printf(" ! There is no such Book...\n");
                }
                }

void Exit()
{
  exit(0);
}
