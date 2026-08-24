#include<stdio.h>
#include <stdlib.h>

//STACK FUNCTIONS
void push(char *stk, int size, int *top,char push_ele) {
    if (*top == size - 1) {
        printf("Stack Overflow! Cannot push element.\n");
        return;
    } else {
        (*top)++;
        stk[*top] = push_ele;
    }
}
char pop(char* stk, int *top) {
    if (*top == -1) {
        printf("Stack Underflow! Code cannot pop.\n");
        return -1;
    } else {
        char pop_ele = stk[*top];
        (*top)--;
        return pop_ele;
    }
}
int precedance(char s){
	if (s=='*' || s=='/'){
    	return 2;
	}
    if (s=='^'){
    	return 3;
	}
	if (s=='+' || s=='-'){
		return 1;
	}
	if (s=='#'){
		return 0;
	}
	return -1;
}
int main(){
	//char infix array input expression
	int size1;
	printf("size of infix");
	scanf("%d",&size1);
	char* infix;
	infix=(char*)malloc((size1+1)*sizeof(char));
	scanf("%s",infix);
	infix[size1] = '#';
	//stack making for operator
	char* stk;
    stk = (char*)malloc((size1+1) * sizeof(char));
    if (stk == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    int top = -1;
    // array making for storing output postfix
    char* arr=(char*)malloc((size1+1)*sizeof(char));
    //populate stack 1st element with #
    push(stk,size1+1,&top,'#');
    int j=0;
    int i;
    for (i=0;i<size1+1;i++){
	//for 1st brace
    	if(infix[i]=='('){
    		push(stk,size1+1,&top,infix[i]);
		}
	//for 2nd brace
		else if (infix[i]==')'){
			while (top >= 0 && stk[top]!='('){
				arr[j]=pop(stk,&top);
				j++;
			}
			pop(stk,&top);
		}
	//for operator
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
			while (top >= 0 && stk[top] != '#' && stk[top] != '(' && precedance(infix[i]) <= precedance(stk[top])) {
				// For right-associative '^'
				if (infix[i] == '^' && stk[top] == '^') {
					break;
				}
				arr[j] = pop(stk, &top);
				j++;
			}
			push(stk, size1 + 1, &top, infix[i]);
		}
	//for #
		else if(infix[i]=='#'){
			while (top >= 0 && stk[top] != '#') {
        	arr[j++] = pop(stk, &top);
        }
    	pop(stk, &top);
	}
	//for operand	
		else{
			arr[j]=infix[i];
			j++;
		}
	}
	arr[j]='\0';
	printf("%s",arr);
	free(infix);
	free(stk);
	free(arr);
	return 0;
}
