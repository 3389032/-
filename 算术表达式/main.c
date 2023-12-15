#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 30

//数据结构
typedef struct my_stack
{
	int a[N];
	int top;
}ST;//栈，用来中缀转后缀

//所使用的函数
int isempty(ST *T); //判断栈是否为空
int isfull(ST *T);  //判断栈是否为满
int gettop(ST *T);  //得到栈顶元素
int pop(ST *T);  //弹栈
void push(ST *T,int s);  //入栈
void transfer(char *in,char *post);   //中缀转后缀
float Calculate_zhong(char *post);    //计算中缀的值（实际上用后缀来计算）

//主函数
main()
{
	char zhong[N],hou[N];     //zhong为中缀表达式 hou为后缀表达式
	float answer;             //存储计算结果
	system("color 1E");
	printf("------------2226010406李圣璇--------------\n");
	printf("\n--------------表达式求值--------------\n\n");  //说明该代码的实现功能
	printf("需要计算的中缀表达式为:  ");
	scanf("%s",zhong);
	while(strcmp(zhong,"#")!=0)   //当输入为"#"结束
	{
		transfer(zhong,hou);     //中缀转后缀
		printf("\n\n转化后的后缀表达式为：");    //下面的空格，"\n"，"-"只是为了输出好看
		printf("%s\n",hou);
		printf("\n--------------计算结果--------------\n");
		answer=Calculate_zhong(hou);
		printf("\n           %s",hou);
		printf(" = %f\n",answer);
		printf("\n--------------计算完毕--------------\n");
		printf("\n\n需要计算的中缀表达式为:  ");
	    scanf("%s",zhong);
	}
}

int isempty(ST *T)  //判断栈是否为空
{
	if(T->top<0)
		return 1;
	else
		return 0;
}

int isfull(ST *T)   //判断栈是否为满
{
	if(T->top==N-1)
		return 1;
	else
		return 0;
}

int gettop(ST *T)   //得到栈顶元素
{
	return T->a[T->top];
}

int pop(ST *T)  //弹栈
{
	int x;
	if(T->top<0)   //栈为空
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

void push(ST *T,int s)   //入栈
{
	if(T->top==N-1)  //栈满了
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

void transfer(char *in,char *post)    //将中缀表达式转化为后缀表达式,参考了老师的代码，加上了关于小数的讨论
{
	ST T;//栈
	int i,j,flag=0;    //flag=1说明是现在栈顶是数，用来判断是否出现连续两个运算符
	int count;     //记录每个数中小数点的个数，超过一个则表达式有误
	int right=0,left=0;     //left和right用来记录算式里面左右括号的个数
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
				 	if(in[i]=='.') //记录小数点出现的个数
				 		count++;
				}
				i--;
				if(count>1)
				{
				 	printf("\n表达式错误!!!!\n\n错误原因：数中有两个小数点\n");
				 	exit(0);
				}
				post[j]=' ';//用空格来分割两个数
				j++;
				flag=1;  //目前为数字，则flag为1
				break;
		case '(':if(flag)//如果括号前是数字，则表达式有误
				{
				 	printf("\n表达式错误!!!!\n\n错误原因：数字后直接跟括号\n");
				 	exit(0);
				}
				push(&T,in[i]);
				left++;//左括号个数加一
			    break;
		case ')':right++;   //右括号个数加一
				while(gettop(&T)!='(')
				{
					 post[j]=pop(&T);
					 j++;
				}
			     pop(&T);
				 break;
		case '+':
		case '-':if(!flag&&i!=0)//如果运算符前是运算符，则表达式有误
				{
				 	printf("\n表达式错误!!!!\n\n错误原因：有连续两个运算符之间没有数字\n");
				 	exit(0);
				}
				while(!isempty(&T)&&gettop(&T)!='(')
				{
					post[j]=pop(&T);
					j++;
				}
			    push(&T,in[i]);
			    flag=0;//目前为符号，所以flag为0
				break;
		case '*':
		case '/':if(!flag)//如果运算符前是运算符，则表达式有误
				{
				 	printf("\n表达式错误!!!!\n\n错误原因：有连续两个运算符之间没有数字\n");
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
		default:printf("\n表达式错误!!!!\n\n错误原因：输入非法字符，无法试别\n");
			    exit(0);
		}
	}
	if(left!=right)
	{
		printf("\n表达式错误!!!!\n\n错误原因：左右括号不匹配\n");
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
	int i,j,top=-1,flag;       //top为栈顶，初始值为-1，flag用来判断数字是否存在小数点
	int len;                   //len表示数字小数点前的长度
	float temp,aa[N];          //aa[N]用来存放表达式中的数字，temp为临时变量
	char ch[N];                //先把数字的表达式存到ch[N]中，再转化为数字存到aa[N]
	for(i=0,j;post[i]!='\0';i++)  //依此开始读取栈的后缀表达式的内容
	{
		if(post[i]>='0'&&post[i]<='9')//如果当前为数字，先将数字存到ch中，再转化为float类型并存到aa中
		{
			flag=0; //初始为0
			j=0;  //用来记录字符串的长度
			while(post[i]!=' ')//将这一串代表数字的字符串存到ch中，直到数字结束
			{
				if(post[i]=='.')//判断是否有小数点，分别讨论
					flag=1; //有小数点
				ch[j]=post[i];//把数字存入到ch[N]中
				i++;
				j++;
			}
			ch[j]='\0'; //加上这个，表示字符串结尾
			if(flag)//有小数点的情况，先算小数点前的，再算小数点后的，分开计算
			{
				for(j=0;ch[j]!='.';j++);//先求长度，找到j的位置，那么长度为j-1
					len=j-1;
				for(j=0,temp=0.;ch[j]!='.';j++)  //计算小数点前的和
					temp+=(ch[j]-'0')*pow(10,len-j);
				for(j++,len++;ch[j]!='\0';j++)   //计算小数点前的和
					temp+=(ch[j]-'0')*pow(10,len-j);
			}
			else//没小数点的情况
			{
				for(j=0;ch[j]!='\0';j++);//求出相应的长度
					len=j-1;
				for(j=0,temp=0.;ch[j]!='\0';j++)
					temp+=(ch[j]-'0')*pow(10,len-j);
			}
			top++;
			aa[top]=temp;//temp入栈，到这里对数字的处理就结束了
		}
		else      //如果是运算符，栈顶两个数出栈，并把这两个数的运算结果入栈！！！！！
		{
			switch(post[i])  //根据不同的运算结果进行运算
			{
				case'+':temp=aa[top];
						top--;
						temp+=aa[top];  //本来这里需要再top--，但是后面由于需要入栈，及需要top++，所以这里就没有做top--
						aa[top]=temp;
						break;
				case'-':temp=aa[top];
						top--;
						temp=aa[top]-temp;  //本来这里需要再top--，但是后面由于需要入栈，及需要top++，所以这里就没有做top--
						aa[top]=temp;
						break;
				case'*':temp=aa[top];
						top--;
						temp=temp*aa[top]; //本来这里需要再top--，但是后面由于需要入栈，及需要top++，所以这里就没有做top--
						aa[top]=temp;
						break;
				case'/':temp=aa[top];
						top--;
						temp=aa[top]/temp;   //本来这里需要再top--，但是后面由于需要入栈，及需要top++，所以这里就没有做top--
						aa[top]=temp;
			}
		}
	}
	return aa[top];//最终的计算结果就在栈顶
}//263行
