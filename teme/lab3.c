/*Implementati pe calculator structura de date stiva, asa cum este descrisa in laborator.*/

// Varianta 1
#include <stdio.h>

#define MAX 100

typedef struct
{
    int array[MAX];
    int top;
} Stack;

// initializare stiva
void initStack(Stack *stack)
{
    stack->top = -1;
}

// verifica daca stiva este plina
int isFull(Stack *stack)
{
    return stack->top == MAX - 1;
}

// verifica daca stiva este goala
int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

// adauga un element in stiva
void push(Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("Stiva este plina\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// elimina si returneaza un element din stiva
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stiva este goala\n");
        return -1;
    }
    return stack->array[stack->top--];
}

// afiseaza elementele din stiva
void display(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stiva este goala\n");
        return;
    }
    printf("Stiva: ");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main()
{
    Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    display(&stack);

    printf("Element extras: %d\n", pop(&stack));
    display(&stack);

    return 0;
}
////////////Varianta 2
#include <stdio.h>

#define MAX_SIZE 100
int top = -1;
int stack[MAX_SIZE];

void push(int item)
{
    if (top == MAX_SIZE - 1)
    {
        printf("Stiva este plina\n");
        return;
    }
    stack[++top] = item;
}

int pop()
{
    if (top == -1)
    {
        printf("Stiva este goala\n");
        return -1;
    }
    return stack[top--];
}

void display()
{
    if (top == -1)
    {
        printf("Stiva este goala\n");
        return;
    }
    printf("Elementele din stiva sunt: ");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

int main()
{
    push(10);
    push(20);
    push(30);
    display();
    printf("Elementul extras din stiva: %d\n", pop());
    display();
    return 0;
}

//////////////////////////////////////////////////////////////////////////

/*2 Implementati pe calculator structura de date coada, asa cum este descrisa in
laborator*/

// varianta 1
#include <stdio.h>

#define MAX_SIZE 100
int front = -1, rear = -1;
int queue[MAX_SIZE];

void enqueue(int item)
{
    if (rear == MAX_SIZE - 1)
    {
        printf("Coada este plina\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = item;
}

int dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("Coada este goala\n");
        return -1;
    }
    return queue[front++];
}

void display()
{
    if (front == -1 || front > rear)
    {
        printf("Coada este goala\n");
        return;
    }
    printf("Elementele din coada sunt: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    printf("Elementul extras din coada: %d\n", dequeue());
    display();
    return 0;
}

// varianta 2
#include <stdio.h>

#define MAX 5 // Dimensiunea maximă a cozii

typedef struct
{
    int array[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *queue)
{
    queue->front = queue->rear = -1;
}

int isFull(Queue *queue)
{
    return queue->rear == MAX - 1;
}

int isEmpty(Queue *queue)
{
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(Queue *queue, int item)
{
    if (isFull(queue))
    {
        printf("Coada este plină!\n");
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->array[++queue->rear] = item;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Coada este goală!\n");
        return -1;
    }
    return queue->array[queue->front++];
}

void display(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Coada este goală!\n");
        return;
    }
    printf("Coada: ");
    for (int i = queue->front; i <= queue->rear; i++)
    {
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}

int main()
{
    Queue queue;
    initQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    display(&queue);

    printf("Element extras: %d\n", dequeue(&queue));
    display(&queue);

    return 0;
}

//////////////////////////////////////////////////////////////////////////

/*Sa se implementeze cu ajutorul unei stive functia undo dintr-un fisier text. Functia
undo permite utilizatorului sa se revina la o versiune mai veche a documentului, eliminand ultimile
modificari. Pentru a implementa functia undo cu o stiva fiecare modificare va fi retinuta pe stiva, iar
cand e necesar sa se revina la o versiune anterioara se va elimina din stiva ultima modificare
adaugata. Pe stiva se va retine la fiecare modificare: textul nou scris (sir de maxim 100 de
caractere), randul unde a fost scris (int).*/

#include <stdio.h>
#include <string.h>

#define MAX 10 // Numărul maxim de modificări

typedef struct
{
    char text[100]; // Modificarea efectuată
    int line;       // Linia pe care s-a făcut modificarea
} Modification;

typedef struct
{
    Modification stack[MAX];
    int top;
} UndoStack;

// Inițializare stivă
void initStack(UndoStack *stack)
{
    stack->top = -1;
}

// Verifică dacă stiva este plină
int isFull(UndoStack *stack)
{
    return stack->top == MAX - 1;
}

// Verifică dacă stiva este goală
int isEmpty(UndoStack *stack)
{
    return stack->top == -1;
}

// Adaugă o modificare în stivă
void push(UndoStack *stack, char *text, int line)
{
    if (isFull(stack))
    {
        printf("Stiva de undo este plină!\n");
        return;
    }
    stack->top++;
    strcpy(stack->stack[stack->top].text, text);
    stack->stack[stack->top].line = line;
}

// Elimină ultima modificare
void pop(UndoStack *stack)
{
    if (isEmpty(stack))
    {
        printf("Nu există modificări pentru undo!\n");
        return;
    }
    printf("Undo: Șterg linia %d: \"%s\"\n", stack->stack[stack->top].line, stack->stack[stack->top].text);
    stack->top--;
}

// Afișează toate modificările
void display(UndoStack *stack)
{
    if (isEmpty(stack))
    {
        printf("Nu există modificări.\n");
        return;
    }
    printf("Modificări înregistrate:\n");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("Linia %d: %s\n", stack->stack[i].line, stack->stack[i].text);
    }
}

int main()
{
    UndoStack stack;
    initStack(&stack);

    push(&stack, "Hello, world!", 1);
    push(&stack, "Modificare pe linia 2", 2);
    push(&stack, "Altă modificare", 3);
    display(&stack);

    pop(&stack);
    display(&stack);

    return 0;
}

//////////////////////////////////////////////////////////////////////////

/*Sa se implementeze cu ajutorul unei cozi un buffer care retine temporar informatiile
primite de la diversi transmitatori (informatia este adaugata in coada) si le transmite mai apoi catre
un receptor (informatia este eliminata din coada). Informatia primita in buffer are urmatoare
structura: numar identificare transmitator (int), mesaj (sir de caractere de maxim 256 caractere)*/

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct
{
    int id;
    char message[256];
} BufferItem;

typedef struct
{
    BufferItem queue[MAX];
    int front, rear;
} BufferQueue;

void initQueue(BufferQueue *queue)
{
    queue->front = queue->rear = -1;
}

// Verifică dacă bufferul este plin
int isFull(BufferQueue *queue)
{
    return queue->rear == MAX - 1;
}

// Verifică dacă bufferul este gol
int isEmpty(BufferQueue *queue)
{
    return queue->front == -1 || queue->front > queue->rear;
}

// Adaugă un mesaj în buffer
void enqueue(BufferQueue *queue, int id, char *message)
{
    if (isFull(queue))
    {
        printf("Bufferul este plin!\n");
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->rear++;
    queue->queue[queue->rear].id = id;
    strcpy(queue->queue[queue->rear].message, message);
}

// Elimină și procesează un mesaj din buffer
void dequeue(BufferQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Bufferul este gol!\n");
        return;
    }
    printf("Procesare mesaj: ID %d - %s\n", queue->queue[queue->front].id, queue->queue[queue->front].message);
    queue->front++;
}

// Afișează mesajele din buffer
void display(BufferQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Bufferul este gol!\n");
        return;
    }
    printf("Mesaje în buffer:\n");
    for (int i = queue->front; i <= queue->rear; i++)
    {
        printf("ID %d: %s\n", queue->queue[i].id, queue->queue[i].message);
    }
}

int main()
{
    BufferQueue queue;
    initQueue(&queue);

    enqueue(&queue, 1, "Mesaj de la transmitator 1");
    enqueue(&queue, 2, "Date importante");
    enqueue(&queue, 3, "Actualizare sistem");
    display(&queue);

    dequeue(&queue);
    display(&queue);

    return 0;
}
