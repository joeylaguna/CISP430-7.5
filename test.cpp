#include <iostream>
#include <string.h>
using namespace std;

#define MAX 40
struct node {
    char item;
    node *next;
};
int i=0;
char a[30]={0};

char pop(struct node *&top);
bool operand(char a);
void push(char item, struct node *&top);
void solve(char item);
void printArray();
void putInArray(char item);
bool empty(struct node *top);
void reset(struct node *top);
int precedence (char item);
bool PrecedenceBigger(struct node *top,char item);
void infixPostfix();

int main(){
       infixPostfix();

       int c;
       cin>>c;
}

char pop(struct node *&top){
   struct node *temp;
   char item;
   //make sure there is something on the stack before popping.
   if(top){
       temp=top;
       top=top->next;
       item=temp->item;
       delete temp;
   }
    return (item);
}

bool operand(char a){
   bool operrand=false;

   if (isdigit(a) || isalpha(a))
       operrand=true;

   return operrand;
}

void push(char item, struct node *&top){
   struct node *newNode=new node;

   //create a new node. Put the item and connect it to the last node which was
     //sitting at the top.
   newNode->item=item;
   newNode->next=top;
   top=newNode;
   //cout << top->item << " ";
}

void solve(char item)
{
    struct node *operators;
    if (operand(item))
    {
        push(item, operators);
    }
    cout << operators->item << "-";
}

void printArray(){
    char temp;
    char c;
    struct node *operators;
    for (int b=0; b<i; b++)
    {
        cout<<a[b];
        temp = a[b];
        /*if (operand(temp))
        {
            push(temp, operators);
        }
        else
        {
            while (PrecedenceBigger(operators, temp) == false)
            {
                c=pop(operators);
                putInArray(c);
                cout << "test";
                //cout << "test";
            }
            push(temp,operators);
        }*/
        //solve(a[b]);
    }
    cout << "success";

}

void putInArray(char item){
 a[i]=item;
 i++;
}

bool empty(struct node *top){
   bool emptie=false;

   if (!top)
     emptie=true;

   return emptie;
}

void reset(struct node *top){
   struct node *temp;

   //As long as the stack is not empty, make the top
   //the previous one and remove the old top
   while(top){
       putInArray(top->item);
       temp=top;
       top=top->next;
       delete temp;
   }
}

int precedence (char item){
   int precedence;

   switch (item){
       case '+':
       case '-':
           precedence=1;
           break;
       case '*':
       case '/':
           precedence=2;
           break;
       case '(':
            precedence=0;//lowest order to force other operators to be pushed.
   }
   return (precedence);
}

bool PrecedenceBigger(struct node *top,char item){
   bool push=false;

   if(  empty(top) || (precedence(item)>precedence(top->item))   )
       push=true;

   return (push);
}

void infixPostfix(){
   struct node *operators;
   char s[MAX];
   bool error;
   char c;

   operators=NULL;  //Being that the stack is empty, top needs to be reset to NULL
   cout<<" Give me a number ";
   cin>>s;

   //Process each element separately
   for (int i=0; s[i]!='\0' ; i++){

           //If it is a digit then display it
           if (s[i]==' ')
               continue;
           else if (s[i]=='('){  //push the left paranthesis onto the stack
              push(s[i],operators);
           }
           else if(s[i]==')')  //If right, then continue to pop from the stack including the left paranethesis
                do{
                      c=pop(operators);
                      if (c!='(')
                         putInArray(c);
                }while (c!='(');
           else if (operand(s[i])){
               putInArray(s[i]);
           }
           else{
               while (PrecedenceBigger(operators, s[i]) == false){
                 c=pop(operators);
                 putInArray(c);
               }

               push(s[i],operators);
           }
   }
   reset(operators);
   printArray();
}
