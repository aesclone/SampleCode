#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Set of code that takes and string as an input in the function get_char()
   and will return a double */

/* s_prec() and i_prec return the precedence for determining the order
   operations are placed the postfix stack */
char s_prec(char c){

  switch(c){

  case '(': return -1;

  case ')': return 0;

  case '+': return 1;

  case '-': return 1;

  case '*': return 2;

  case '/': return 2;

  case '%': return 2;

  case '^': return 3;

  }

}

char i_prec(char c){

  switch(c){

  case '(': return 5;

  case ')': return 0;

  case '+': return 1;

  case '-': return 1;

  case '*': return 2;

  case '/': return 2;

  case '%': return 2;

  case '^': return 4;

  }

}

/* Struct for a stack that will hold mathmatical operators when solving the
   postfix equation */
struct opStack{

  int capacity, size;
  char *elements;

};

/* Function that takes an int of the total number of operators to create
   that stack and return the stuct */
struct opStack *createStack(int maxelen){

  struct opStack *s;
  s = (struct opStack *)malloc(sizeof(struct opStack));
  s->elements = (char *)malloc(sizeof(char) * maxelen);
  s->size = 0;
  s->capacity = maxelen;

  return s;

}

/* Function that takes an opStack and returns the first element in the
   stack*/
char pop(struct opStack *s){

  if(s->size == 0){

    printf("No more elements in stack!\n");
    exit(0);

  }

  s->size--;
  return s->elements[s->size];

}

/* Function that take an opStack and and operator as a char and addes the
   operator to the stack */
void push(struct opStack *s, char operator){

  if(s->size == s->capacity){

    printf("Stack is full\n");

  }else{

    s->elements[s->size++] = operator;

  }

}

/* Function that takes an opStack and returns the first element in the stack
   without removing it */
char peek(struct opStack *s){

  if(s->size == 0){

    printf("There are no elements in the stack!\n");
    exit(-1);

  }

  return s->elements[s->size - 1];

}

/* Function to check if an opStack is empty */
int isEmpty(struct opStack *s){

  if(s->size == 0){ return 1; }

  return 0;

}

/* Struct for a stack that aids the process of solving the postfix equation */
struct mathStack{

  int capacity, size;
  double *elements;

};

/* Function that takes the max number indices that may be needed and
   returns a mathStack */
struct mathStack *createMathStack(int maxSize){

  struct mathStack *s;
  s = (struct mathStack *)malloc(sizeof(struct mathStack));
  s->elements = (double *)malloc(sizeof(double) * maxSize);
  s->size = 0;
  s->capacity = maxSize;

  return s;

}

/* Function that takes a mathStack and returns and removes the first element
   of the stack */
double mathPop(struct mathStack *s){

  if(s->size == 0){

    printf("No more elements in mathStack!\n");
    exit(0);

  }

  s->size--;
  return s->elements[s->size];

}

/* Function that takes a mathStack and a double and add that double to
   the stack */
void mathPush(struct mathStack *s, double num){

  if(s->size == s->capacity){

    printf("The mathStack is full!\n");

  }else{

    s->elements[s->size++] = num;

  }

}

/* Function that takes a mathStack and returns the first element without
   removing it */
double mathPeek(struct mathStack *s){

  if(s->size == 0){

    printf("There are no elements in the mathStack!\n");
    exit(-1);

  }

  return s->elements[s->size -1];

}

/* Function that takes a mathStack and determins if it is empty */
int mathIsEmpty(struct mathStack *s){

  if(s->size == 0){ return 1; }

  return 0;

}

/* Struct that will hold the inputted equation in postfix notation using
   a singlely linked list */
struct postfix{ 

  char operator, is;
  double value;
  struct postfix *next;

};

/* Function that creates the head of the list and returns a postfix struct */
struct postfix *create_postfix(void){

  struct postfix *a;
  a = (struct postfix *)malloc(sizeof(struct postfix));
  a->operator = 0;
  a->is = -1;
  a->value = 0.0;
  a->next = NULL;

  return a;

}

/* Function that creates and returns a postfix struct that is not the head */
struct postfix *new_postfix(void){

  struct postfix *a;
  a = (struct postfix *)malloc(sizeof(struct postfix));
  a->operator = 0;
  a->is = 0;
  a->value = 0.0;
  a->next = NULL;

  return a;

}

/* Function that takes a posfix struct and a double and adds that double to
   the list */
void add_double(struct postfix *lst , double num){

  if(lst->is == -1){

    lst->value = num;
    lst->is = 0;

  }else{

    struct postfix *new = new_postfix();
    new->value= num;

    while(lst->next != NULL){ lst = lst->next; }

    lst->next = new;

  }

}

/* Function that take a posfix struct and an operator as a char and add that
   to the list */
void add_operator(struct postfix *lst, char s){

  struct postfix *new = new_postfix();
  new->operator = s;
  new->is = 1;

  while(lst->next != NULL){ lst = lst->next; }

  lst->next = new;

}

/* Function that takes a char returns a value if the char is an operator or
   0 elsewise */
char isoperator(char s){

  if(s == '+' || s == '-' || s == '*' || s == '/' || s == '^'){ return 1;

  }else if(s == '('){ return 2;

  }else if(s == ')'){ return 3; }

  return 0;

}

/* Function that takes a string and will return a double of that number */
double *make_double(char *str){

  int sign = 1; //Tracks the signage of the double
  int dec = -1; //Tracks the position after the decimal
  int index = 0; //Tracks the current index being read from the string
  int len = strlen(str); //length of the string to read
  double *ret = (double *)malloc(sizeof(double));
  *ret = 0.0; //Starting the value at 0

  //Checking that the inputted value has at least one number
  if(len < 1){ return NULL; }

  //Checking the signage of the number and storring it
  if(str[0] == '-'){

    sign = -1;
    index++;

  }

  //Loop to add up all the digits with the respective power before the decimal
  while(index < len && str[index] != '.'){

    if(isdigit(str[index]) == 0){ return NULL; }

    *ret = (*ret * 10) + str[index] - '0';
    index++;

  }

  //Movine the index one past the decimal point
  if(str[index] == '.'){ index++; }

  //Loop to add up all the digits after the decimal with their respective power
  while(index < len){

    if(isdigit(str[index]) == 0){ return NULL; }

    *ret += (str[index] - '0') * pow(10, dec--);
    index++;

  }

  //Adding the signage to the double
  *ret = *ret * sign;

  return ret;


}

double *get_double(char *str){

  struct postfix *post = create_postfix(); //Creating the postfix structure

  //Making sure that the string length inputted is not 0
  if(strlen(str) == 0){ return NULL; }
  //if(isoperator(str[0]) && str[0] != '-') { return NULL; }

  //Creating an array to identify the location of operators in the string
  char *operators = (char *)malloc(sizeof(char) * strlen(str));
  int i = 0;
  int count = 0;
  //Checking if the first char is a minus for a number
  if(str[0] == '-') { operators[0] = 0; i = 1; }

  //Loop to identify the location of operators in the string
  for(i = i; i < strlen(str); i++){

    if(isdigit(str[i]) || str[i] == '.'){ operators[i] = 0;

    }else if(str[i] == '-' && isoperator(str[i - 1]) != 0) { operators[i] = 0;

    }else if(isoperator(str[i]) != 0){ count ++; operators[i] = isoperator(str[i]);

    }else { return NULL; }

  }

  //Creating and operator stack
  struct opStack *stack = createStack(count);
  int index = 0; //
  count = 0; //Reseting cout to 0
  char *temp = (char *)malloc(sizeof(char));
  //Loop to put the numbers and operators into postfix notation
  while(index < strlen(str)){

    int j = index;

    //while loop to find the last index in a number
    while(operators[j] == 0 && j < strlen(str)){ j++; }

    //If a number is founy by a length that is not 0
    if(j - index != 0){

      int k;
      //Array to hold the number as a string
      temp = (char *)realloc(temp, j - index); 
      //Loop to add the chars to a string
      for(k = index; k < j; k++){

	temp[k - index] = str[k];

      }

      //Turning the string into a double
      double *d = make_double(temp);
      temp = (char *)malloc(sizeof(char));
      //Checking that the string was a valid number
      if(d == NULL){ return NULL; };

      count++;
      //Adding the number to the postfix stack
      add_double(post, *d);
      free(d);
      index = k;

    }

    //If a found indes is an operator
    if(operators[index] == 1 || operators[index] == 2){

      //Loop to determine the order of operations
      while(!isEmpty(stack) && i_prec(str[index]) <= s_prec(peek(stack))){

	count++;
	add_operator(post, pop(stack));

      }

      push(stack, str[index]);
      index++;

    }

    //If statement if the index is ')' to find its pair
    if(operators[index] == 3){

      while(peek(stack) != '(' && !isEmpty(stack)){

	count++;
	add_operator(post, pop(stack));

      }

      pop(stack);
      index++;

    }

  }

  free(temp);

  //adding any left over operators to the postfix stack
  while(!isEmpty(stack)){ count++;  add_operator(post, pop(stack)); }

  //Creating the math stack
  struct mathStack *math = createMathStack(count);
  //Loop that solves the eqaution in the postfix stack
  while(post != NULL){

    //If statement to catch doubles and add them to the mathStack
    if(!post->is){

      mathPush(math, post->value);
      post = post->next;

    //Statement to catch operators and do the operation on the numbers in
    //in the mathStack and pushed the new number back
    }else if(post->is){

      double b = mathPop(math);
      double a = mathPop(math);

      switch(post->operator){

      case '+': mathPush(math, a + b); break;

      case '-': mathPush(math, a - b); break;

      case '*': mathPush(math, a * b); break;

      case '/': mathPush(math, a / b); break;

      case '^': mathPush(math, pow(a, b)); break;

      }

      post = post->next;

    }

  }

  //Freeing up malloced variables
  free(operators);
  free(stack);
  free(post);

  //Placing the last number in the mathStack to the return number 
  double *ret = (double *)malloc(sizeof(double));
  *ret = mathPop(math);

  free(math);

  return ret;

}

int main(int argc, char* argv[]){

  if(argc < 2){

    printf("No input argument given to solve!\n");
    return -1;

  }

  double* test = get_double(argv[1]);
  if(test == NULL){

    printf("The given equation is invalid!\n");
    return -1;

  }

  printf("The answer is: %lf\n", *test);
  free(test);

  return 0;

}
