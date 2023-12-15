#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 30

//���ݽṹ
typedef struct my_stack
{
	int a[N];
	int top;
}ST;//ջ��������׺ת��׺

//��ʹ�õĺ���
int isempty(ST *T); //�ж�ջ�Ƿ�Ϊ��
int isfull(ST *T);  //�ж�ջ�Ƿ�Ϊ��
int gettop(ST *T);  //�õ�ջ��Ԫ��
int pop(ST *T);  //��ջ
void push(ST *T,int s);  //��ջ
void transfer(char *in,char *post);   //��׺ת��׺
float Calculate_zhong(char *post);    //������׺��ֵ��ʵ�����ú�׺�����㣩

//������
main()
{
	char zhong[N],hou[N];     //zhongΪ��׺���ʽ houΪ��׺���ʽ
	float answer;             //�洢������
	system("color 1E");
	printf("------------2226010406��ʥ�--------------\n");
	printf("\n--------------���ʽ��ֵ--------------\n\n");  //˵���ô����ʵ�ֹ���
	printf("��Ҫ�������׺���ʽΪ:  ");
	scanf("%s",zhong);
	while(strcmp(zhong,"#")!=0)   //������Ϊ"#"����
	{
		transfer(zhong,hou);     //��׺ת��׺
		printf("\n\nת����ĺ�׺���ʽΪ��");    //����Ŀո�"\n"��"-"ֻ��Ϊ������ÿ�
		printf("%s\n",hou);
		printf("\n--------------������--------------\n");
		answer=Calculate_zhong(hou);
		printf("\n           %s",hou);
		printf(" = %f\n",answer);
		printf("\n--------------�������--------------\n");
		printf("\n\n��Ҫ�������׺���ʽΪ:  ");
	    scanf("%s",zhong);
	}
}

int isempty(ST *T)  //�ж�ջ�Ƿ�Ϊ��
{
	if(T->top<0)
		return 1;
	else
		return 0;
}

int isfull(ST *T)   //�ж�ջ�Ƿ�Ϊ��
{
	if(T->top==N-1)
		return 1;
	else
		return 0;
}

int gettop(ST *T)   //�õ�ջ��Ԫ��
{
	return T->a[T->top];
}

int pop(ST *T)  //��ջ
{
	int x;
	if(T->top<0)   //ջΪ��
	{
		printf("Zhan is empty,can not pop!\n");
		exit(0);
	}
	else
	{
		x=T->a[T->top];
		(T->top)--;
		return x;
	}
}

void push(ST *T,int s)   //��ջ
{
	if(T->top==N-1)  //ջ����
	{
		printf("Zhan is full,can not push,you can modify N and then you can push again.\n");
		exit(0);
	}
	else
	{
		(T->top)++;
		T->a[T->top]=s;
	}
}

void transfer(char *in,char *post)    //����׺���ʽת��Ϊ��׺���ʽ,�ο�����ʦ�Ĵ��룬�����˹���С��������
{
	ST T;//ջ
	int i,j,flag=0;    //flag=1˵��������ջ�������������ж��Ƿ�����������������
	int count;     //��¼ÿ������С����ĸ���������һ������ʽ����
	int right=0,left=0;     //left��right������¼��ʽ�����������ŵĸ���
	T.top=-1;
	for(i=0,j=0;in[i]!='\0';i++)
	{
		switch(in[i])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':for(count=0;(in[i]<='9'&&in[i]>='0')||in[i]=='.';i++,j++)
				{
				 	post[j]=in[i];
				 	if(in[i]=='.') //��¼С������ֵĸ���
				 		count++;
				}
				i--;
				if(count>1)
				{
				 	printf("\n���ʽ����!!!!\n\n����ԭ������������С����\n");
				 	exit(0);
				}
				post[j]=' ';//�ÿո����ָ�������
				j++;
				flag=1;  //ĿǰΪ���֣���flagΪ1
				break;
		case '(':if(flag)//�������ǰ�����֣�����ʽ����
				{
				 	printf("\n���ʽ����!!!!\n\n����ԭ�����ֺ�ֱ�Ӹ�����\n");
				 	exit(0);
				}
				push(&T,in[i]);
				left++;//�����Ÿ�����һ
			    break;
		case ')':right++;   //�����Ÿ�����һ
				while(gettop(&T)!='(')
				{
					 post[j]=pop(&T);
					 j++;
				}
			     pop(&T);
				 break;
		case '+':
		case '-':if(!flag&&i!=0)//��������ǰ�������������ʽ����
				{
				 	printf("\n���ʽ����!!!!\n\n����ԭ�����������������֮��û������\n");
				 	exit(0);
				}
				while(!isempty(&T)&&gettop(&T)!='(')
				{
					post[j]=pop(&T);
					j++;
				}
			    push(&T,in[i]);
			    flag=0;//ĿǰΪ���ţ�����flagΪ0
				break;
		case '*':
		case '/':if(!flag)//��������ǰ�������������ʽ����
				{
				 	printf("\n���ʽ����!!!!\n\n����ԭ�����������������֮��û������\n");
				 	exit(0);
				}
				while(!isempty(&T)&&(gettop(&T)=='/'||gettop(&T)=='*'))
				{
					 post[j]=pop(&T);
					 j++;
				}
			    push(&T,in[i]);
			    flag=0;
				break;
		default:printf("\n���ʽ����!!!!\n\n����ԭ������Ƿ��ַ����޷��Ա�\n");
			    exit(0);
		}
	}
	if(left!=right)
	{
		printf("\n���ʽ����!!!!\n\n����ԭ���������Ų�ƥ��\n");
		exit(0);
	}
	while(!isempty(&T))
	{
		post[j]=pop(&T);
		j++;
	}
	post[j]='\0';
}

float Calculate_zhong(char *post)
{
	int i,j,top=-1,flag;       //topΪջ������ʼֵΪ-1��flag�����ж������Ƿ����С����
	int len;                   //len��ʾ����С����ǰ�ĳ���
	float temp,aa[N];          //aa[N]������ű��ʽ�е����֣�tempΪ��ʱ����
	char ch[N];                //�Ȱ����ֵı��ʽ�浽ch[N]�У���ת��Ϊ���ִ浽aa[N]
	for(i=0,j;post[i]!='\0';i++)  //���˿�ʼ��ȡջ�ĺ�׺���ʽ������
	{
		if(post[i]>='0'&&post[i]<='9')//�����ǰΪ���֣��Ƚ����ִ浽ch�У���ת��Ϊfloat���Ͳ��浽aa��
		{
			flag=0; //��ʼΪ0
			j=0;  //������¼�ַ����ĳ���
			while(post[i]!=' ')//����һ���������ֵ��ַ����浽ch�У�ֱ�����ֽ���
			{
				if(post[i]=='.')//�ж��Ƿ���С���㣬�ֱ�����
					flag=1; //��С����
				ch[j]=post[i];//�����ִ��뵽ch[N]��
				i++;
				j++;
			}
			ch[j]='\0'; //�����������ʾ�ַ�����β
			if(flag)//��С��������������С����ǰ�ģ�����С�����ģ��ֿ�����
			{
				for(j=0;ch[j]!='.';j++);//���󳤶ȣ��ҵ�j��λ�ã���ô����Ϊj-1
					len=j-1;
				for(j=0,temp=0.;ch[j]!='.';j++)  //����С����ǰ�ĺ�
					temp+=(ch[j]-'0')*pow(10,len-j);
				for(j++,len++;ch[j]!='\0';j++)   //����С����ǰ�ĺ�
					temp+=(ch[j]-'0')*pow(10,len-j);
			}
			else//ûС��������
			{
				for(j=0;ch[j]!='\0';j++);//�����Ӧ�ĳ���
					len=j-1;
				for(j=0,temp=0.;ch[j]!='\0';j++)
					temp+=(ch[j]-'0')*pow(10,len-j);
			}
			top++;
			aa[top]=temp;//temp��ջ������������ֵĴ���ͽ�����
		}
		else      //������������ջ����������ջ������������������������ջ����������
		{
			switch(post[i])  //���ݲ�ͬ����������������
			{
				case'+':temp=aa[top];
						top--;
						temp+=aa[top];  //����������Ҫ��top--�����Ǻ���������Ҫ��ջ������Ҫtop++�����������û����top--
						aa[top]=temp;
						break;
				case'-':temp=aa[top];
						top--;
						temp=aa[top]-temp;  //����������Ҫ��top--�����Ǻ���������Ҫ��ջ������Ҫtop++�����������û����top--
						aa[top]=temp;
						break;
				case'*':temp=aa[top];
						top--;
						temp=temp*aa[top]; //����������Ҫ��top--�����Ǻ���������Ҫ��ջ������Ҫtop++�����������û����top--
						aa[top]=temp;
						break;
				case'/':temp=aa[top];
						top--;
						temp=aa[top]/temp;   //����������Ҫ��top--�����Ǻ���������Ҫ��ջ������Ҫtop++�����������û����top--
						aa[top]=temp;
			}
		}
	}
	return aa[top];//���յļ���������ջ��
}//263��
