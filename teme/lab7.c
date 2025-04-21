// Să se scrie o funcție care primește două liste și returnează 1 dacă ele sunt identice, altfel 0.
#include <stdio.h>
#include <stdlib.h>

// Structura nodului
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

int lists_equal(Node *list1, Node *list2)
{
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data != list2->data)
        {
            return 0;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == NULL && list2 == NULL;
}

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int main()
{
    // Lista 1: 1 -> 2 -> 3
    Node *l1 = create_node(1);
    l1->next = create_node(2);
    l1->next->next = create_node(3);

    // Lista 2: 1 -> 2 -> 3
    Node *l2 = create_node(1);
    l2->next = create_node(2);
    l2->next->next = create_node(3);

    // Testare egalitate
    if (lists_equal(l1, l2))
    {
        printf("Listele sunt egale.\n");
    }
    else
    {
        printf("Listele NU sunt egale.\n");
    }

    return 0;
}

// Să se scrie o funcție care primește o listă și returnează lista respectivă cu elementele inversate.
// Funcția va acționa doar asupra listei originare, fără a folosi vectori sau alocare de noi elemente.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Functia care inverseaza lista
Node *reverse_list(Node *head)
{
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Functie care creeaza un nod nou
Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Funcție pentru afisarea unei liste
void print_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    // Cream lista: 1 -> 2 -> 3 -> 4
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    printf("Lista inițială: ");
    print_list(head);

    // Inversam lista
    head = reverse_list(head);

    printf("Lista inversată: ");
    print_list(head);

    // Eliberam memoria
    free_list(head);

    return 0;
}

// Să se scrie o funcție care primește ca parametri două liste și returnează o listă care reprezintă
// reuniunea elementelor lor, fiecare element apărând o singură dată, chiar dacă în listele originare el este duplicat

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Functie care verifica daca un element exista in lista
int contains(Node *head, int value)
{
    while (head != NULL)
    {
        if (head->data == value)
        {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

// Functie care adauga un nod la finalul listei (cu referinta la coada pentru eficienta)
void append(Node **head, Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

// Functia de reuniune (fara duplicate)
Node *list_union(Node *list1, Node *list2)
{
    Node *result = NULL;
    Node *tail = NULL;

    Node *current = list1;
    while (current != NULL)
    {
        if (!contains(result, current->data))
        {
            append(&result, &tail, current->data);
        }
        current = current->next;
    }

    current = list2;
    while (current != NULL)
    {
        if (!contains(result, current->data))
        {
            append(&result, &tail, current->data);
        }
        current = current->next;
    }

    return result;
}

void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head)
{
    Node *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main()
{
    // Lista 1: 1 -> 2 -> 3
    Node *l1 = create_node(1);
    l1->next = create_node(2);
    l1->next->next = create_node(3);

    // Lista 2: 3 -> 4 -> 5
    Node *l2 = create_node(3);
    l2->next = create_node(4);
    l2->next->next = create_node(5);

    printf("Lista 1: ");
    print_list(l1);

    printf("Lista 2: ");
    print_list(l2);

    // Reuniunea celor 2
    Node *rezultat = list_union(l1, l2);
    printf("Reuniune (fără duplicate): ");
    print_list(rezultat);

    free_list(l1);
    free_list(l2);
    free_list(rezultat);

    return 0;
}

// Pentru implementarea listei care memorează adresa ultimului element, să se scrie o funcție șterge,
// care șterge din listă un element dat.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
} List;

void init_list(List *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// Adaugă la final
void append(List *list, int value)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

// Șterge prima aparitie a unui element
void delete_node(List *list, int value)
{
    Node **pp = &list->head;
    Node *current = list->head;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->data == value)
        {
            *pp = current->next;
            if (current->next == NULL)
            {
                list->tail = prev;
            }
            free(current);
            return;
        }
        prev = current;
        pp = &current->next;
        current = current->next;
    }
}

// Afiseaza lista
void print_list(List *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Elibereaza lista
void free_list(List *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *tmp = current;
        current = current->next;
        free(tmp);
    }
    list->head = list->tail = NULL;
}

int main()
{
    List myList;
    init_list(&myList);

    append(&myList, 1);
    append(&myList, 2);
    append(&myList, 3);
    append(&myList, 4);

    printf("Lista inițială: ");
    print_list(&myList);

    delete_node(&myList, 3);
    printf("După ștergerea lui 3: ");
    print_list(&myList);

    delete_node(&myList, 1);
    printf("După ștergerea lui 1 (primul nod): ");
    print_list(&myList);

    delete_node(&myList, 4);
    printf("După ștergerea lui 4 (ultimul nod): ");
    print_list(&myList);

    free_list(&myList);
    return 0;
}

// Să se scrie o funcție care primește două liste și returnează 1 dacă ele sunt egale, indiferent de
// ordinea și numărul elementelor, altfel returnează 0.
// Exemple: listele {1, 7, 3, 1, 3} și {7, 1, 3, 7} sunt egale. Listele {1,2} și {2} nu sunt egale.

int lists_equal_unordered(Node *list1, Node *list2)
{
    // Cream o lista temporara pentru a putea marca elementele gasite
    Node *temp = copy_list(list2);
    Node *curr1 = list1;
    int found;

    // Verificam fiecare element din list1 in list2
    while (curr1 != NULL)
    {
        found = 0;
        Node *prev = NULL;
        Node *curr2 = temp;

        while (curr2 != NULL)
        {
            if (curr2->data == curr1->data)
            {
                found = 1;
                // stergem elementul gasit din lista temporara
                if (prev == NULL)
                {
                    temp = curr2->next;
                }
                else
                {
                    prev->next = curr2->next;
                }
                free(curr2);
                break;
            }
            prev = curr2;
            curr2 = curr2->next;
        }

        if (!found)
        {
            free_list(temp);
            return 0;
        }
        curr1 = curr1->next;
    }

    // Verificam daca au ramas elemente in list2
    if (temp != NULL)
    {
        free_list(temp);
        return 0;
    }

    return 1;
}

// Să se scrie o funcție care primește ca parametri o listă (posibil vidă) de elemente sortate și un
// element. Funcția va insera în listă noul element, astfel încât lista să rămână sortată. Folosind aceasta funcție, să
// se scrie o funcție de sortare a unei liste, care primește ca parametru o listă nesortată și returnează una sortată.
// Programul nu va folosi niciun vector.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *create_node(int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void insert_sorted(Node **head, int value)
{
    Node *new_node = create_node(value);
    Node **current = head;

    while (*current != NULL && (*current)->data < value)
    {
        current = &(*current)->next;
    }

    new_node->next = *current;
    *current = new_node;
}

Node *sort_list(Node *head)
{
    Node *sorted = NULL;
    Node *current = head;

    while (current != NULL)
    {
        insert_sorted(&sorted, current->data);
        current = current->next;
    }

    return sorted;
}

void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

Node *list_from_array(int values[], int n)
{
    if (n == 0)
        return NULL;
    Node *head = create_node(values[0]);
    Node *tail = head;
    for (int i = 1; i < n; i++)
    {
        tail->next = create_node(values[i]);
        tail = tail->next;
    }
    return head;
}

void free_list(Node *head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    int values[] = {5, 1, 9, 3, 7, 2};
    int n = sizeof(values) / sizeof(values[0]);

    Node *unsorted = list_from_array(values, n);
    printf("Lista nesortată: ");
    print_list(unsorted);

    Node *sorted = sort_list(unsorted);
    printf("Lista sortată:   ");
    print_list(sorted);

    free_list(sorted);
    return 0;
}

// Pentru implementarea listei care memorează ultimul element, să se scrie o funcție care primește
// două liste sortate și returnează lista sortată care conține toate elementele lor. Pentru lista rezultată se va folosi
// doar operația de adăugare la sfârșit de listă.
// Exemplu: {1, 2, 7, 8} și {2, 9} -> {1, 2, 2, 7, 8, 9}

#include <stdio.h>
#include <stdlib.h>

// Structura nodului
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
} List;

List *create_list()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *create_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

void append(Node **head, Node **tail, int value)
{
    Node *new_node = create_node(value);
    if (*head == NULL)
    {
        *head = *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(Node *head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

List *merge_sorted_lists(List *list1, List *list2)
{
    List *result = create_list();
    Node *p1 = list1->head;
    Node *p2 = list2->head;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->data <= p2->data)
        {
            append(&result->head, &result->tail, p1->data);
            p1 = p1->next;
        }
        else
        {
            append(&result->head, &result->tail, p2->data);
            p2 = p2->next;
        }
    }

    while (p1 != NULL)
    {
        append(&result->head, &result->tail, p1->data);
        p1 = p1->next;
    }

    while (p2 != NULL)
    {
        append(&result->head, &result->tail, p2->data);
        p2 = p2->next;
    }

    return result;
}

int main()
{
    // Prima lista sortata: 1 3 5 7
    List *list1 = create_list();
    append(&list1->head, &list1->tail, 1);
    append(&list1->head, &list1->tail, 3);
    append(&list1->head, &list1->tail, 5);
    append(&list1->head, &list1->tail, 7);

    // A doua listă sortata: 2 4 6 8
    List *list2 = create_list();
    append(&list2->head, &list2->tail, 2);
    append(&list2->head, &list2->tail, 4);
    append(&list2->head, &list2->tail, 6);
    append(&list2->head, &list2->tail, 8);

    printf("Lista 1: ");
    print_list(list1->head);
    printf("Lista 2: ");
    print_list(list2->head);

    List *merged = merge_sorted_lists(list1, list2);

    printf("Lista îmbinată: ");
    print_list(merged->head);

    free_list(list1->head);
    free(list1);
    free_list(list2->head);
    free(list2);
    free_list(merged->head);
    free(merged);

    return 0;
}
