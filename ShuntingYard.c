#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 4096

//////////////////////////////////////////////////////////////////
typedef struct {
    char data[MAX_SIZE];
    int top;
} charStack;
//////////////////////////////////////////////////////////////////

void stack_init(charStack *stack);
int stack_is_empty(charStack *stack);
char stack_pop(charStack *stack);
char stack_peek(charStack *stack);
void stack_push(charStack *stack, char value);

int operator_precedence(char op);
int operator_is_right_associative(char op);
int operator_is_valid(char c);

int is_identifier_start(char c);
int is_identifier_char(char c);

void convert_infix_to_postfix(char *infix, char *postfix);
void menu();

//////////////////////////////////////////////////////////////////

int main()
{
    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("Exiting program.\n");
            return 0;
        }

        if (choice == 1)
        {
            char infix[MAX_SIZE];
            char postfix[MAX_SIZE];

            printf("Enter infix expression (example: A+2*(B-C/4)): ");
            scanf(" %4095[^\n]", infix);

            convert_infix_to_postfix(infix, postfix);

            printf("\nPostfix: %s\n", postfix);
        }
        else
        {
            printf("Invalid option!\n");
        }
    }
}

//////////////////////////////////////////////////////////////////

void menu()
{
    printf("\n==================== SHUNTING YARD MENU ====================\n");
    printf("1- Convert Infix to Postfix (Supports letters + numbers)\n");
    printf("0- Exit\n");
    printf("=============================================================\n");
}

void stack_init(charStack *stack)
{
    stack->top = -1;
}

int stack_is_empty(charStack *stack)
{
    return stack->top == -1;
}

void stack_push(charStack *stack, char value)
{
    stack->top++;
    stack->data[stack->top] = value;
}

char stack_pop(charStack *stack)
{
    char value = stack->data[stack->top];
    stack->top--;
    return value;
}

char stack_peek(charStack *stack)
{
    return stack->data[stack->top];
}

int operator_precedence(char op)
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int operator_is_right_associative(char op)
{
    return op == '^';
}

int operator_is_valid(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int is_identifier_start(char c)
{
    return (isalpha((unsigned char)c) || c == '_');
}

int is_identifier_char(char c)
{
    return (isalnum((unsigned char)c) || c == '_');
}

void convert_infix_to_postfix(char *infix, char *postfix)
{
    charStack stack;
    stack_init(&stack);

    int i = 0;
    int k = 0;

    while (infix[i] != '\0')
    {
        char currentChar = infix[i];

        if (isspace((unsigned char)currentChar))
        {
            i++;
            continue;
        }

        // number (multi-digit)
        if (isdigit((unsigned char)currentChar))
        {
            while (isdigit((unsigned char)infix[i]))
            {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            continue;
        }

        // identifier / variable (A, var1, _x2)
        if (is_identifier_start(currentChar))
        {
            while (is_identifier_char(infix[i]))
            {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            continue;
        }

        // (
        if (currentChar == '(')
        {
            stack_push(&stack, currentChar);
            i++;
            continue;
        }

        // )
        if (currentChar == ')')
        {
            while (!stack_is_empty(&stack) && stack_peek(&stack) != '(')
            {
                postfix[k++] = stack_pop(&stack);
                postfix[k++] = ' ';
            }

            if (!stack_is_empty(&stack) && stack_peek(&stack) == '(')
                stack_pop(&stack);

            i++;
            continue;
        }

        // operator
        if (operator_is_valid(currentChar))
        {
            while (!stack_is_empty(&stack) && operator_is_valid(stack_peek(&stack)))
            {
                char topOp = stack_peek(&stack);

                int p1 = operator_precedence(currentChar);
                int p2 = operator_precedence(topOp);

                if ((!operator_is_right_associative(currentChar) && p1 <= p2) ||
                    ( operator_is_right_associative(currentChar) && p1 <  p2))
                {
                    postfix[k++] = stack_pop(&stack);
                    postfix[k++] = ' ';
                }
                else
                {
                    break;
                }
            }

            stack_push(&stack, currentChar);
            i++;
            continue;
        }

        // unknown character
        // (İstersen burada hata bastırabiliriz)
        i++;
    }

    while (!stack_is_empty(&stack))
    {
        char op = stack_pop(&stack);
        if (op != '(')
        {
            postfix[k++] = op;
            postfix[k++] = ' ';
        }
    }

    if (k > 0) k--; // remove last space
    postfix[k] = '\0';
}
