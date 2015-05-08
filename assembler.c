// ADHISH SINGLA
// ASSEMBLER for a self made ISA

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Function to make symbol table
void pass1(int prog)
{
	FILE *p,*q,*s;
	int i=0,ct,line=1;
	char c,c1,array[12];
	switch(prog)
	{
		case 1:	p= fopen("program1.txt","r");
			s= fopen("symbol1.txt","w");
			break;
		case 2:	p= fopen("program2.txt","r");
			s= fopen("symbol2.txt","w");
			break;
		case 3:	p= fopen("program3.txt","r");
			s= fopen("symbol3.txt","w");
			break;
		case 4:	p= fopen("program4.txt","r");
			s= fopen("symbol4.txt","w");
			break;
	}
	while((c=fgetc(p))!= EOF)
	{
		if(c!=' ' && c!='\n' && c!=',' && c!='\r')
		{ 
		   array[i]=c; 
		       i++; 
        	}
		else
		{ 
			array[i]='\0'; 	
			i=0; 
		}
		if(c == '\n') 
			line++;
		else if( c == ':') 
		{
			array[i-1]='\0';
			fprintf(s,"%s\t",array);
			int z=0,num,k;
			num=line;
				for (z = 15; z >= 0; z--)
				{
					k = num >> z;
 
					if (k & 1)
						fprintf(s,"1");
					else
						fprintf(s,"0");
				}
			fputc('\n',s);
		}
	}
	fclose(p);
	fclose(s);
	printf("***SYMBOL TABLE***\n");
	switch(prog)
	{
		case 1: s= fopen("symbol1.txt","r");
			break;
		case 2:	s= fopen("symbol2.txt","r");
			break;
		case 3:	s= fopen("symbol3.txt","r");
			break;
		case 4:	s= fopen("symbol4.txt","r");
			break;
	}
	while((c=fgetc(s))!= EOF)
		printf("%c",c);
	printf("\n");
	fclose(s);
}

//Function to generate machine language file
void pass2(int prog)
{
	FILE *p,*q,*s,*t;
	int i=0,ct,line=1,cout=0;
	char c,c1,array[35],*array1;
	int jumpflag=0,syntaxflag=0,dataflag=0,flag=0,ctflag=0;
	array1=(char *)malloc(35*sizeof(char));
	t= fopen("isa.txt","r");
	switch(prog)
	{
		case 1:	p= fopen("program1.txt","r");
			q= fopen("binary1.txt","w");
			s= fopen("symbol1.txt","r");
			break;
		case 2:	p= fopen("program2.txt","r");
			q= fopen("binary2.txt","w");
			s= fopen("symbol2.txt","r");
			break;
		case 3:	p= fopen("program3.txt","r");
			q= fopen("binary3.txt","w");
			s= fopen("symbol3.txt","r");
			break;
		case 4:	p= fopen("program4.txt","r");
			q= fopen("binary4.txt","w");
			s= fopen("symbol4.txt","r");
			break;
	}
		printf("\n");
	i=0;
	ct = 0; line=1;
	while((c=fgetc(p))!= EOF)
	{
		if(c!=' ' && c!='\n' && c!=',' && c!='\r')
		{ 
		   array[i]=c; 
		       i++; 
        	}
		else
		{ 
			array[i]='\0'; 	
			i=0; 
			flag=1;
		}
		if(c == '\n') 
			line++;
		else if( c == ':') 
			fputc('\n',q);
		
			
		if(i==0 && c!='\n' && array[0]!='\0')
		{
			int j=0;
			while(array[j]!='\0')
			{
				if(array[j]>='0' && array[j]<='9')
				{
					dataflag=0;
				}
				else
				{
					dataflag=1;
					break;
				}
				j++;
			}
			if(ct >= 32)
			{ 	
				fprintf(q,"\n"); 
				ct = 0;
			}
			
			if(array[0] >= '0' && array[0] <='9' && dataflag==0)
			{
				int z=0,num,k;
				sscanf(array, "%d", &num);
				for (z = 15; z >= 0; z--)
				{
					k = num >> z;
 
					if (k & 1)
						fprintf(q,"1");
					else
						fprintf(q,"0");
				}
				ct+=16;
			}
			if(flag==1)
			{
				i=0;
				int isaflag=0;
				while((c1=fgetc(t))!= EOF)
				{
					if(c1!=' ' && c1!='\t' && c1!='\n' && c1!='\r')
					{ 
						   *(array1+i)=c1; 
						       i++;
			        	}
					else if(c1=='\t' || c1=='\n')
					{
						*(array1+i)='\0';
						i=0;
					}
					if(i==0)
					{
						if(ctflag==1)
						{
							sscanf(array1, "%d", &cout);
							ct+=cout;
							ctflag=0;
						}
						if(isaflag==1)
						{
							fprintf(q,"%s",array1);
							ctflag=1;
							isaflag=0;
							flag=0;
						}
						if(!(strcmp(array1,array)))
						{
							isaflag=1;
						}
					}
				}
			}
			if(!(strcmp("JPC", array)) || !(strcmp("JPNC", array)) || !(strcmp("JPZ", array)) || !(strcmp("JPNZ", array)) || !(strcmp("JPP", array)) || !(strcmp("JPN", array)))
		{
				jumpflag=1;
		}
			if(jumpflag==1)
			{
				i=0;
				int labelflag=0;
				while((c1=fgetc(s))!= EOF)
				{
					if(c1!=' ' && c1!='\t' && c1!='\n' && c1!='\r')
					{ 
						   *(array1+i)=c1; 
						       i++;
			        	}
					else if(c1=='\t' || c1=='\n')
					{
						*(array1+i)='\0';
						i=0;
					}
					if(i==0)
					{
						if(labelflag==1)
						{
							fprintf(q,"%s",array1);
							ct+=16;
							labelflag=0;
							jumpflag=0;
						}
						if(!(strcmp(array1,array)))
						{
							labelflag=1;
						}
					}
				}
			}
			else if(array[0] >= '0' && array[0] <='9' && dataflag==1)
			{
				printf("SYNTAX ERROR in line %d\n",line);
			}
			t= fopen("isa.txt","r");
			switch(prog)
			{
				case 1: s= fopen("symbol1.txt","r");
					break;
				case 2:	s= fopen("symbol2.txt","r");
					break;
				case 3:	s= fopen("symbol3.txt","r");
					break;
				case 4:	s= fopen("symbol4.txt","r");
					break;
			}
		}
	}
	fclose(p);
	fclose(q);
	fclose(s);
	fclose(t);
	switch(prog)
	{
		case 1: q= fopen("binary1.txt","r");
			break;
		case 2:	q= fopen("binary2.txt","r");
			break;
		case 3:	q= fopen("binary3.txt","r");
			break;
		case 4:	q= fopen("binary4.txt","r");
			break;
	}
	printf("\n***BINARY CODE***\n");
	while((c=fgetc(q))!= EOF)
		printf("%c",c);
	printf("\n");
	fclose(q);
}

main()
{
	FILE *p;
	char c;
	int ch,prog;
	do
	{
		printf("1. Display a program \n");
		printf("2. Binary of Program\n");
		printf("3. Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
						
			case 1:    		printf("1. Factorial of a Number\n");
						printf("2. Reverse of a Number\n");
						printf("3. Prime\n");
						printf("4. Sum of Numbers\n");
						scanf("%d",&prog);
					switch(prog)
					{
						case 1:	p= fopen("program1.txt","r");
								break;
						case 2:	p= fopen("program2.txt","r");
								break;
						case 3:	p= fopen("program3.txt","r");
								break;
						case 4:	p= fopen("program4.txt","r");
								break;
					}
					printf("\n");
					while((c=fgetc(p))!= EOF)
						printf("%c",c);
					printf("\n");						
					fclose(p);					
						break;
						
			case 2:			printf("1. Factorial of a Number\n");
						printf("2. Reverse of a Number\n");
						printf("3. Prime\n");
						printf("4. Sum of Numbers\n");
						scanf("%d",&prog);
					pass1(prog);
					pass2(prog);
					break;
						
												
			case 3:	      	break;
		}
	}
	while(ch != 3);
}
