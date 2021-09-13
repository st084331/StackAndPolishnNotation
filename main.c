#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int val;
    struct Node *next;
};

struct Node_char {
    char symb;
    struct Node_char *next;
};

void Cpush(struct Node_char **head, char val) {
    struct Node_char *newNode = (struct Node_char *) malloc(sizeof(struct Node_char));
    newNode->symb = val;
    if (*head == NULL) {
        newNode->next = NULL;
    } else { newNode->next = *head; }
    *head = newNode;
}

char Cpop(struct Node_char **head) {
    if (*head == NULL) {
        printf("Stack is empty\n");
        return 0;
    }
    struct Node_char *current = *head;
    char val = (*head)->symb;
    (*head) = (*head)->next;
    free(current);
    return val;
}

int lenght(struct Node *head) {
    struct Node *current = head;
    int i = 0;
    while (current != NULL) {
        i++;
        current = current->next;
    }
    return i;
}

int Clenght(struct Node_char *head) {
    struct Node_char *current = head;
    int i = 0;
    while (current != NULL) {
        i++;
        current = current->next;
    }
    return i;
}

void listprint(struct Node *head) {
    struct Node *current = head;
    if (head == NULL) {
        return;
    }
    do {
        printf("%d ", current->val);
        current = current->next;
    } while (current != NULL);
    printf("\n");
}

void Clistprint(struct Node_char *head) {
    struct Node_char *current = head;
    if (head == NULL) {
        return;
    }
    do {
        printf("%c ", current->symb);
        current = current->next;
    } while (current != NULL);
    printf("\n");
}

//1
void push(struct Node **head, int val) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->val = val;
    if (*head == NULL) {
        newNode->next = NULL;
    } else { newNode->next = *head; }
    *head = newNode;
}

int pop(struct Node **head) {
    if (*head == NULL) {
        printf("Stack is empty\n");
        return 0;
    }
    struct Node *current = *head;
    int val = (*head)->val;
    (*head) = (*head)->next;
    free(current);
    return val;
}

//2
int f2(struct Node **head) {
    char val;
    int check = 0;
    int power = 0;
    int dig = 0;
    while (check != 1) {
        while (val != '#') {
            scanf("%c", &val);
            if (isdigit(val)) {
                dig = dig * ((int) pow(10, power)) + ((int) val - '0');
                power++;
            } else if (val == ' ') {
                if (dig != -1) {
                    push(head, dig);
                    listprint(*head);
                    power = 0;
                }
                dig = 0;
            } else if (val == '+' || val == '-' || val == '*' || val == '/' || val == 's') {
                power = 0;
                dig = -1;
                switch (val) {
                    case '+':
                        push(head, pop(head) + pop(head));
                        listprint(*head);
                        break;
                    case '-':
                        push(head, pop(head) - pop(head));
                        listprint(*head);
                        break;
                    case '*':
                        push(head, pop(head) * pop(head));
                        listprint(*head);
                        break;
                    case '/':
                        push(head, pop(head) / pop(head));
                        listprint(*head);
                        break;
                    case 's':
                        push(head, sin(pop(head)));
                        listprint(*head);
                        break;
                }

            }
        }
        if (lenght(*head) == 1) {
            check = 1;
        }
        val = '@';
    }
    return pop(head);
}

//3
void f1(struct Node_char **head) {
    char symbol;
    char key;
    int dig_bool = 0;
    while (symbol != '#') {
        scanf("%c", &symbol);
        while (isdigit(symbol)) {
            dig_bool = 1;
            printf("%c", symbol);
            scanf("%c", &symbol);
        }
        if (dig_bool) { printf(" "); dig_bool = 0;}
        if (symbol == '*' || symbol == '/') {
            while (Clenght(*head) != 0 && key != '-' && key != '+' && key != '(') {
                key = Cpop(head);
                if (key != '-' && key != '+' && key != '(') printf("%c ", key);
            }
            if (key == '-' || key == '+' || key == '(') { Cpush(head, key); }
            Cpush(head, symbol);
            key = '.';
        } else if (symbol == '+' || symbol == '-') {
            while (Clenght(*head) != 0 && key != '(') {
                key = Cpop(head);
                if (key != '(') printf("%c ", key);
            }
            if (key == '(') { Cpush(head, key); }
            Cpush(head, symbol);
            key = '.';
        } else if (symbol == '(') {
            Cpush(head, symbol);
        } else if (symbol == ')') {
            while (key != '(') {
                key = Cpop(head);
                if (key != '(') { printf("%c ", key); }
            }
            key = '.';
        }
    }
    while (Clenght(*head) != 0) {
        key = Cpop(head);
        if (key != '(' && key != ')') { printf("%c ", key); }
    }
}


int main() {
    struct Node_char *head = NULL;
    //printf("%d", f2(&head));
    f1(&head);
    return 0;
}
