#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#define MAX 10
void arrival(void);
void departure(void);
void display();
int avail_slot(void);
void update(void);
void file(void);

struct node
{
    char number[20];
    int data;
    struct node *next;
}*TOP=NULL;
void del_case1(void)
{
    struct node *t=TOP;
    TOP=TOP->next;
     free(t);

     update();
}
void del_case2(struct node *temp)
{
    struct node *t=TOP;
    while(t->next!=temp)
    {
	t=t->next;
    }
    t->next=NULL;
    free(temp);

}
void del_case3(struct node *temp)
{
    struct node *t1=TOP,*t2=TOP;
    while(t1->next!=temp)
    {
	t1=t1->next;
    }
   t2=temp->next;
    t1->next=t2;
    temp->next=NULL;
    free(temp);
    update();
}
void update(void)
{
    struct node *temp;
    int i=1;
    for(temp=TOP;temp!=NULL;temp=temp->next)
    {
	temp->data=i++;
    }

}
int main()
{
    int choice;
    system("cls");
    textcolor(WHITE);
    _setcursortype(_NOCURSOR);
    delay(700);
    textcolor(RED);
    gotoxy(20,12);
    cprintf("\nProject by Pritul Dave The Fundu Parking Garage\n");
    delay(1500);
    system("cls");
    file();
    delay(500);
    while(1)
    {
	clrscr();
	_setcursortype(_NOCURSOR);
	textcolor(WHITE);
	printf("enter 1 for arrival\nenter 2 for departure\nenter 3 to display\nenter 4 to exit");
	printf("\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
	    arrival();
	    break;
	case 2:
		departure();
	    textcolor(WHITE);
	    break;
	case 4:
	    exit(1);
	case 3:
	    textcolor(WHITE);
	    display();
	}
	system("cls");
    }
}
void display()
{
    struct node *t=TOP;
    for(t=TOP;t!=NULL;t=t->next)
    {
	printf("car number %s is at slot number %d\n",t->number,t->data);
    }
    getch();
}
void arrival()
{
    struct node *ptr=NULL,*t=TOP;
    if(avail_slot()==MAX+1)
    {
	textcolor(RED);
	cprintf("no slot available\n");
	getch();
	return ;
    }
    ptr=(struct node *)malloc(sizeof(struct node));
    ptr->data=avail_slot();
    if(TOP==NULL)
    {
	TOP=ptr;
	TOP->next=NULL;
    }
    else
    {
	//for(t=TOP;t->next!=NULL;t=t->next);
	while(t->next!=NULL)
		t=t->next;
	t->next=ptr;
	ptr->next=NULL;
    }
    textcolor(WHITE);
    cprintf("enter the car number\n");
    scanf("%s",ptr->number);
    //flushall();
    cprintf("Park the car at slot %d",ptr->data);
    getch();

}
void departure(void)
{
	struct node *temp=TOP;
	char arr[20];
	textcolor(YELLOW);
	cprintf("enter the car number\n");
	scanf("%s",arr);
	while(temp!=NULL)
    {
	if(!strcmp(arr,temp->number))
	{
		if(temp==TOP)
		    del_case1();
		else if(temp->next==NULL)
		    del_case2(temp);
		else
		    del_case3(temp);
		return ;
	}
	else
	    temp=temp->next;

    }
	textcolor(RED);
	cprintf("car number not found\n");
	getch();
}
int avail_slot(void)
{
    struct node *temp=TOP;
    int count=1;
    for(count=1;temp!=NULL;count++,temp=temp->next);
    return count;
}
void file(void)
{
	char ch;
	FILE *fp;
	fp=fopen("carpark.txt","r");
	if(fp==NULL)
	{
		printf("text file not found\n");
		return;
	}
	textcolor(GREEN);
	while(!feof(fp)||ch!=EOF)
	{
		ch=fgetc(fp);
		cprintf("%c",ch);
	}
	_setcursortype(_NOCURSOR);
	textcolor(WHITE);
	printf("\n\nenter any key to continue");
	getch();
	fclose(fp);
}
