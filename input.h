#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct record{
	char name[10],dept[5],type[6];
	int id,year,day,bill;
};
typedef struct record record;
struct tree{
	record data;
	struct tree *left;
	struct tree *right;
};
typedef struct tree tree;
int flag=1;
struct ft{
	char foodline[7][20];
};
typedef struct ft foodtable;
tree* insert(tree *t,record data){
	if(t==NULL){
		t=(tree*)malloc(sizeof(tree));
		//printf("name : %s\n",data.name);
		t->data=data;
		t->left=t->right=NULL;
	}
	else{
		//printf("name a: %s\n",data.name);
		if((t->data.id)>data.id)t->left=insert(t->left,data);
		//printf("name b: %s\n",data.name);
		if((t->data.id)<data.id)t->right=insert(t->right,data);
	}
	return t;
}
void inorder(tree *t){
	if(t!=NULL){
		inorder(t->left);
		printf("\n\nName : %s\nId: %d\nDepartment : %s\nyear : %d\ndays : %d\nbill : %d\n",t->data.name,t->data.id,t->data.dept,t->data.year,t->data.day,t->data.bill);
		inorder(t->right);
	}
}
void search(tree *t,int id)
{
	if(t!=NULL)
	{
		if((t->data.id)>id)search(t->left,id);
		if(t->data.id==id)
		{
			printf("\nName : %s\nId: %d\nDepartment : %s\nyear : %d\nNo. of Billing days : %d\nBill amount : %d\n",t->data.name,t->data.id,t->data.dept,t->data.year,t->data.day,t->data.bill);
			flag=0;
		}
		if((t->data.id)<id)search(t->right,id);
	}
}
tree* billcancel(tree* t,int id){
	int i=0;
	tree *tr;
	if(t!=NULL){
		if((t->data.id)>id)tr=billcancel(t->left,id);
		if(t->data.id==id){
			printf("\nEnter No Of Days To Be Cancelled:");
			scanf("%d",&i);
			t->data.day=t->data.day-i;
			t->data.bill=(t->data.day-i)*84;
			return t;
		}
		if((t->data.id)<id)tr=billcancel(t->right,id);
	}
	return t;
}
tree* getinput(tree *t)
{
	record data;
	while(1)
	{
		printf("\nEnter Name  : ");
			scanf("%s",data.name);
		if(!strcmp(data.name,"exit"))
			break;
		printf("Enter Dept  : ");
			scanf("%s",data.dept);
		printf("Enter ID    : ");
			scanf("%d",&data.id);
		printf("Enter Year  : ");
			scanf("%d",&data.year);
		printf("Enter Type  :");
			scanf("%s",data.type);
		data.day=30;
		data.bill=data.day*84;
		t=insert(t,data);
	}
	return t;
}
void searchstudent(tree *t){
	int id;
	while(1)
	{
		printf("Enter ID To Show Details :");
		scanf("%d",&id);
		if(id==0)
			break;
		search(t,id);
	}
}
tree* cancelbill(tree *t){
	int id;
	while(1){
		printf("\nEnter ID To Cancel Bill :");
		scanf("%d",&id);
		if(id==0)
			break;
		t=billcancel( t, id);
	}
	return t;
}
void generatebill(tree *t){
		
	if(t!=NULL){
		generatebill(t->left);
		/*printf("ID : %d\tTotal days : 30\tBilling days : %d\tBilling Amount : %d\tName  :  %s\n\n",t->data.id,t->data.day,t->data.bill,t->data.name);*/
		printf("%d\t30\t\t%d\t\t%d\t\t%s\t\n\n",t->data.id,t->data.day,t->data.bill,t->data.name);
		generatebill(t->right);
	}
}
//new
tree* searchbyid(tree *t,int id)
{
	if(t!=NULL)
	{
		if((t->data.id)>id)
			searchbyid(t->left,id);
		else if((t->data.id)<id)
			searchbyid(t->right,id);
		else if(t->data.id==id)
			return t;
	}
	else
		return NULL;
}
//new
void display_student(tree *t)
{
	if(t!=NULL)
	printf("\tNAME  \t\t: %s\n\tID \t\t: %d\n\tDEPARTMENT  \t: %s\n\tYEAR  \t\t: %d\n\tBILLING days  \t: %d\n\tAMOUNT  \t: %d\n\n",t->data.name,t->data.id,t->data.dept,t->data.year,t->data.day,t->data.bill);
}

void writeintofile(FILE *file,tree* t){
	if(t!=NULL){
		writeintofile(file,t->left);
		fwrite(&t->data,sizeof(record),1,file);
		writeintofile(file,t->right);
	}
}

void seesuggestions()
{
	FILE*fptrrsg;
	fptrrsg=fopen("suggestion.txt","r");
	char c;
	c=fgetc(fptrrsg);
	while(c!=EOF)
	{
		printf("%c",c);
		c=fgetc(fptrrsg);
	}
	printf("\n\n");
	fclose(fptrrsg);
}	 

void tell_about_mess()
{
	printf("\n\t----------MESS----------\n\t(being runned by HAD rentals)\n\n\tOur Mess Started In The Year 2000\n\tOwned by  : Mr.EX\n\tOur Motto : To Deliver A Healthy World Class Food To Students\n\n");
}
void clrscr()
{
	system("@cls||clear");
}
void modifyfoodtable(){
	FILE *file=fopen("foodschedule.dat","r");
	if(file==NULL){
		printf("Error Opening File...");
		exit(1);
	}
	foodtable temp[4];
	char food[20];
	int i=0,day,time;
	char breakfast[7][20],lunch[7][20],snacks[7][20],dinner[7][20];
	while(fread(&temp[i++],sizeof(foodtable),1,file)){};
	fclose(file);
	while(1){
		printf("\nSelect \n\n1-Monday\n2-Tuesday\n3-Wednesday\n4-Thursday\n5-Friday\n6-saturday\n7-Sunday\n0-Exit\n\nEnter Choice :");
		scanf("%d",&day);
		if(day==0)break;
		printf("\n1.Breakfast\n2.Lunch\n3.Snacks\n4.Dinner\n\n");
		printf("Enter Choice :");
		scanf("%d",&time);
		printf("\nEnter Food :");
		scanf("%s",food);
		strcpy(temp[time-1].foodline[day-1],food);
	}
	FILE *file1=fopen("foodschedule.dat","w");
	if(file1==NULL){
		printf("error opening file...");
		exit(1);
	}
	for(int i=0;i<4;i++){
		fwrite(&temp[i],sizeof(foodtable),1,file1);	
	}
	fclose(file1);
}
void seefoodtable(){
	FILE *file=fopen("foodschedule.dat","r");
	if(file==NULL){
		printf("error in opening file...");
		exit(1);
	}
	foodtable temp;
	/*while(fread(&temp,sizeof(foodtable),1,file)){
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",temp.foodline[0],temp.foodline[1],temp.foodline[2],temp.foodline[3],temp.foodline[4],temp.foodline[5],temp.foodline[6]);
	}*/
	printf("\n-----------------------------------------------------------------------------------------------\n");
	printf("Monday\t\tTuesday\t\tWednesday\tThursday\tFriday\t\tSaturday  Sunday\n");
	printf("\n-----------------------------------------------------------------------------------------------\n");
	fread(&temp,sizeof(foodtable),1,file);
printf("%s\t\t%s\t%s\t\t%s\t%s\t%s\t%s\n",temp.foodline[0],temp.foodline[1],temp.foodline[2],temp.foodline[3],temp.foodline[4],temp.foodline[5],temp.foodline[6]);
	fread(&temp,sizeof(foodtable),1,file);
printf("%s\t%s\t%s\t%s\t%s\t\t%s\t%s\n",temp.foodline[0],temp.foodline[1],temp.foodline[2],temp.foodline[3],temp.foodline[4],temp.foodline[5],temp.foodline[6]);
	fread(&temp,sizeof(foodtable),1,file);
printf("%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s%s\n",temp.foodline[0],temp.foodline[1],temp.foodline[2],temp.foodline[3],temp.foodline[4],temp.foodline[5],temp.foodline[6]);
	fread(&temp,sizeof(foodtable),1,file);
printf("%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n",temp.foodline[0],temp.foodline[1],temp.foodline[2],temp.foodline[3],temp.foodline[4],temp.foodline[5],temp.foodline[6]);
	printf("\n------------------------------------------------------------------------------------------------\n");
	fclose(file);
}
