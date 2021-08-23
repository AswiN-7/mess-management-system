#include"input.h"
void main()
{
	printf("---------------------------------------------------\n");
	printf("\t\tMESS MANAGEMENT\t\n");
	printf("---------------------------------------------------\n");
	tree *t=NULL;
	FILE *file=fopen("record.dat","r");
	if(file==NULL)
	{
	
		printf("error opening file...\n");
		exit(1);
	}
	record data;
while(fread(&data,sizeof(record),1,file)){
		//printf("%s\n",data.name);
		t=insert(t,data);
	}
	fclose(file);
	int signin;
	printf("\t----------------\n");
	printf("\t| Sign Options |\n");
	printf("\t----------------\n");
	printf("\t|1 Student     |\n\t|2 Manager     |\n");
	printf("\t----------------\n");
	printf("Enter Your Choice :");
		scanf("%d",&signin);
	if(signin==2)
	{
		char login[10]="ADMIN",log[10];
		char password[10]="1!2@3#4$",pass[10];
	
		int flag2=0;
		while(1)
		{
			printf("\nEnter Login ID : ");
				scanf("%s",log);
			if(!strcmp(log,"exit"))
					break;
			printf("Enter Password : ");
				scanf("%s",pass);
			if((!strcmp(log,login))&&(!strcmp(pass,password)))
			{
				flag2=1;
				break;
			}
			else 
				printf("Invalid Login Please Try Again...\n");
		}
		if(flag2)
		{
				clrscr();
			printf("---------------------------------------------------\n");
			printf("\t\tMESS MANAGEMENT\t\n");
			printf("---------------------------------------------------\n");
			printf("\n");
			printf("....................................................");
			printf("\n\tWELCOME TO ADMIN LOGIN PAGE  \n");
			printf("....................................................\n");
			printf("\n");
			printf("\nHello Admin..\n\n");
			while(flag2)
			{

				int choice;			
				printf("\t--------------------------------\n");
				printf("\t|          Your Options        |\n");
				printf("\t--------------------------------\n");
				printf("\t|1 Data Entry                  |\n\t|2 Search student              |\n\t|3 Bill Cancellation           |\n\t|4 Bill Generation             |\n\t|5 See Suggestions             |\n\t|6 Change Food Schedule        |\n");
				printf("\t--------------------------------\n");
				printf("\nEnter Choice :");
				scanf("%d",&choice);
				if(choice==1)t=getinput(t);
				if(choice==2){
					tree*searchstud;
					int id;
					printf("Enter ID :");
					scanf("%d",&id);
					searchstud=searchbyid(t,id); 
					if(searchstud!=NULL)display_student(searchstud);
					else printf("\n%d ID is Not Found In The List  \n\n",id);
				}
				if(choice==3)t=cancelbill(t);
				if(choice==4){printf("\nID\tTotal Days\tBilling Days\tBilling Amount\tName\t\n\n");
					     generatebill(t);}
				if(choice==5)seesuggestions();
				if(choice==6)modifyfoodtable();
				if(choice==-1)flag2=0;
				
			}
		}
		int show;
		printf("To Show All Details of All Students :");
			scanf("%d",&show);
		if(show==1)inorder(t);
		FILE *file1=fopen("record.dat","w");
		if(file1==NULL){
			printf("Error Opening File...\n");
			exit(1);
		}
		else 
		writeintofile(file1,t);
		fclose(file1);
		printf("\nThe End Of The Program\n");
	}
	else if(signin==1){
			char sugg[100];
			int choice,id,flag=1;
			tree *stud=NULL;
			FILE *fptrsg;
			time_t ti;
			fptrsg=fopen("suggestion.txt","a");
			printf("....................................................");
			printf("\n\tWELCOME TO STUDENT INFO LOGIN PAGE  \n");
			printf("....................................................\n");
			while(1)
			{
				printf("\nEnter your ID number : ");
					scanf("%d",&id);
				stud=searchbyid(t,id); 
				if(stud!=NULL)
				{
				printf("\nHello %s..... \n\n",stud->data.name);
				 		break;
				}
				printf("please enter correct id \n");
			}
			int flagw=1;
		while(flagw){
			printf("Select One Of Options From Given Menu :\n\n");
			printf("\tTo See Your Bill            - 1\n\tTo See Mess Food Time Table - 2\n\tTo Give Suggestions         - 3\n\tTo Know About Our Mess      - 4\n\tTo Exit                     -(-1)\n\nEnter choice : ");
			scanf("%d",&choice);
			switch(choice)
			{
					case 1 : 	printf("\n");
							display_student(stud);
							break;
					case 2 : 
							printf("\n");
							seefoodtable();
							break;
					case 3 : 
							
							time(&ti);
							printf("\n");
							printf("\nYour Suggestions Are Welcomed..... \nYour Satisfaction Is Our Priority \nYour Suggestions :\n\t");
							scanf("%s",sugg);
							fprintf(fptrsg," by '%s' ID '%d' date : %s",stud->data.name,stud->data.id,ctime(&ti));
							printf("\n");
							fprintf(fptrsg,"\t\t%s\n",sugg);
							printf("    \nThanks.....We Will Surely Look Over It\n\n");
						break;
					case 4: 	printf("\n");
							tell_about_mess();
							break;
					case -1:
							flagw=0;
							break;
					default : 
						printf("\n");
						printf("Please Enter Correct Option \n");
			}
		}		
	}
}
