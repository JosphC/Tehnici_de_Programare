// Să se modifice exemplul 1 astfel încât el să numere de câte ori apare fiecare cuvânt în propoziție.
// Pentru aceasta, cuvintele vor fi adăugate doar cu litere mici și fiecare cuvânt va avea asociat un contor. Dacă un
// cuvânt nou nu există în propoziție, el va fi adăugat. Altfel, dacă el există deja, doar se va incrementa contorul
// cuvântului existent. La afișare, pentru fiecare cuvânt se va afișa și contorul său.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Cuvant
{
    char text[16];       // max 15 litere+terminator
    int count;           // contor de aparitii
    struct Cuvant *pred; // inlantuire la predecesor
    struct Cuvant *urm;  // inlantuire la urmator
} Cuvant;

// aloca un nou cuvant si ii seteaza campul text (to lowercase)
// initializeaza contorul la 1
Cuvant *Cuvant_nou(const char *text)
{
    Cuvant *c = (Cuvant *)malloc(sizeof(Cuvant));
    if (!c)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }

    // Convertim cuvantul la lowercase
    for (int i = 0; text[i]; i++)
    {
        c->text[i] = tolower(text[i]);
    }
    c->text[strlen(text)] = '\0';

    c->count = 1;
    return c;
}

typedef struct
{
    Cuvant *prim;  // primul cuvant din lista
    Cuvant *ultim; // ultimul cuvant din lista
} Propozitie;

// initializare propozitie noua
void Propozitie_init(Propozitie *p)
{
    p->prim = p->ultim = NULL;
}

// adauga un cuvant la propozitie sau incrementeaza contorul daca exista deja
void Propozitie_adauga(Propozitie *p, Cuvant *c_nou)
{
    // Cautam cuvantul in propozitie
    Cuvant *c;
    for (c = p->prim; c; c = c->urm)
    {
        if (!strcmp(c->text, c_nou->text))
        {
            // Daca exista deja, incrementam contorul si eliberam noul cuvant
            c->count++;
            free(c_nou);
            return;
        }
    }

    // Daca nu exista, il adaugam la sfarsit
    c_nou->pred = p->ultim;
    if (p->ultim)
    {
        p->ultim->urm = c_nou;
    }
    else
    {
        p->prim = c_nou;
    }
    p->ultim = c_nou;
    c_nou->urm = NULL;
}

// afisare propozitie cu contoare
void Propozitie_afisare(Propozitie *p)
{
    for (Cuvant *c = p->prim; c; c = c->urm)
    {
        printf("%s(%d) ", c->text, c->count);
    }
    printf(".\n");
}

// sterge un cuvant din propozitie
void Propozitie_sterge(Propozitie *p, const char *text)
{
    char lower_text[16];
    for (int i = 0; text[i]; i++)
    {
        lower_text[i] = tolower(text[i]);
    }
    lower_text[strlen(text)] = '\0';

    Cuvant *c;
    for (c = p->prim; c; c = c->urm)
    {
        if (!strcmp(c->text, lower_text))
        {
            if (c->pred)
            {
                c->pred->urm = c->urm;
            }
            else
            {
                p->prim = c->urm;
            }
            if (c->urm)
            {
                c->urm->pred = c->pred;
            }
            else
            {
                p->ultim = c->pred;
            }
            free(c);
            return;
        }
    }
    printf("cuvantul \"%s\" nu se gaseste in propozitie\n", text);
}

// elibereaza cuvintele din memorie si reinitializeaza propozitia ca fiind vida
void Propozitie_elibereaza(Propozitie *p)
{
    Cuvant *c, *urm;
    for (c = p->prim; c; c = urm)
    {
        urm = c->urm;
        free(c);
    }
    Propozitie_init(p);
}

int main()
{
    Propozitie p;
    int op; // optiune
    char text[16];
    Propozitie_init(&p);

    do
    {
        printf("\n1 - propozitie noua\n");
        printf("2 - afisare\n");
        printf("3 - stergere cuvant\n");
        printf("4 - iesire\n");
        printf("optiune: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            Propozitie_elibereaza(&p);
            printf("Introduceti propozitia (terminati cu .):\n");
            while (1)
            {
                scanf("%s", text);
                if (!strcmp(text, "."))
                    break;
                Cuvant *c = Cuvant_nou(text);
                Propozitie_adauga(&p, c);
            }
            break;
        case 2:
            Propozitie_afisare(&p);
            break;
        case 3:
            printf("cuvant de sters: ");
            scanf("%s", text);
            Propozitie_sterge(&p, text);
            break;
        case 4:
            break;
        default:
            printf("optiune invalida\n");
        }
    } while (op != 4);

    Propozitie_elibereaza(&p);
    return 0;
}

// La exemplul 1 să se adauge operația de inserare a unui cuvânt. Pentru aceasta se cere un cuvânt
// de inserat și un cuvânt succesor. Dacă succesorul există în propoziție, cuvântul de inserat va fi inserat înaintea sa.
// Dacă succesorul nu există în lista, cuvântul de inserat va fi adăugat la sfârșitul listei.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Cuvant
{
    char text[16];
    int count;
    struct Cuvant *pred;
    struct Cuvant *urm;
} Cuvant;

Cuvant *Cuvant_nou(const char *text)
{
    Cuvant *c = (Cuvant *)malloc(sizeof(Cuvant));
    if (!c)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; text[i]; i++)
    {
        c->text[i] = tolower(text[i]);
    }
    c->text[strlen(text)] = '\0';

    c->count = 1;
    c->pred = c->urm = NULL;
    return c;
}

typedef struct
{
    Cuvant *prim;
    Cuvant *ultim;
} Propozitie;

void Propozitie_init(Propozitie *p)
{
    p->prim = p->ultim = NULL;
}

void Propozitie_adauga(Propozitie *p, Cuvant *c_nou)
{
    Cuvant *c;
    for (c = p->prim; c; c = c->urm)
    {
        if (!strcmp(c->text, c_nou->text))
        {
            c->count++;
            free(c_nou);
            return;
        }
    }

    c_nou->pred = p->ultim;
    if (p->ultim)
    {
        p->ultim->urm = c_nou;
    }
    else
    {
        p->prim = c_nou;
    }
    p->ultim = c_nou;
    c_nou->urm = NULL;
}

// Functia noua pentru inserare inaintea unui succesor
void Propozitie_insereaza(Propozitie *p, const char *cuvant_inserat, const char *succesor)
{
    // Convertim cuvintele la lowercase
    char lower_inserat[16], lower_succesor[16];
    for (int i = 0; cuvant_inserat[i]; i++)
        lower_inserat[i] = tolower(cuvant_inserat[i]);
    lower_inserat[strlen(cuvant_inserat)] = '\0';
    for (int i = 0; succesor[i]; i++)
        lower_succesor[i] = tolower(succesor[i]);
    lower_succesor[strlen(succesor)] = '\0';

    // Cautam succesorul in lista
    Cuvant *succ = NULL;
    for (succ = p->prim; succ; succ = succ->urm)
    {
        if (!strcmp(succ->text, lower_succesor))
        {
            break;
        }
    }

    Cuvant *c_nou = Cuvant_nou(cuvant_inserat);

    if (succ)
    { // Daca am gasit succesorul
        // Verificam daca succesorul are predecesor
        if (succ->pred)
        {
            succ->pred->urm = c_nou;
            c_nou->pred = succ->pred;
        }
        else
        {
            p->prim = c_nou;
            c_nou->pred = NULL;
        }
        c_nou->urm = succ;
        succ->pred = c_nou;
    }
    else
    {                                // Daca nu am gasit succesorul
        Propozitie_adauga(p, c_nou); // Adaugam la sfârsit
    }
}

void Propozitie_afisare(Propozitie *p)
{
    for (Cuvant *c = p->prim; c; c = c->urm)
    {
        printf("%s(%d) ", c->text, c->count);
    }
    printf(".\n");
}

void Propozitie_sterge(Propozitie *p, const char *text)
{
    char lower_text[16];
    for (int i = 0; text[i]; i++)
        lower_text[i] = tolower(text[i]);
    lower_text[strlen(text)] = '\0';

    Cuvant *c;
    for (c = p->prim; c; c = c->urm)
    {
        if (!strcmp(c->text, lower_text))
        {
            if (c->pred)
            {
                c->pred->urm = c->urm;
            }
            else
            {
                p->prim = c->urm;
            }
            if (c->urm)
            {
                c->urm->pred = c->pred;
            }
            else
            {
                p->ultim = c->pred;
            }
            free(c);
            return;
        }
    }
    printf("cuvantul \"%s\" nu se gaseste in propozitie\n", text);
}

void Propozitie_elibereaza(Propozitie *p)
{
    Cuvant *c, *urm;
    for (c = p->prim; c; c = urm)
    {
        urm = c->urm;
        free(c);
    }
    Propozitie_init(p);
}

int main()
{
    Propozitie p;
    int op;
    char text[16], succesor[16];
    Propozitie_init(&p);

    do
    {
        printf("\n1 - propozitie noua\n");
        printf("2 - afisare\n");
        printf("3 - stergere cuvant\n");
        printf("4 - inserare cuvant\n");
        printf("5 - iesire\n");
        printf("optiune: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            Propozitie_elibereaza(&p);
            printf("Introduceti propozitia (terminati cu .):\n");
            while (1)
            {
                scanf("%s", text);
                if (!strcmp(text, "."))
                    break;
                Cuvant *c = Cuvant_nou(text);
                Propozitie_adauga(&p, c);
            }
            break;
        case 2:
            Propozitie_afisare(&p);
            break;
        case 3:
            printf("cuvant de sters: ");
            scanf("%s", text);
            Propozitie_sterge(&p, text);
            break;
        case 4:
            printf("cuvant de inserat: ");
            scanf("%s", text);
            printf("succesor: ");
            scanf("%s", succesor);
            Propozitie_insereaza(&p, text, succesor);
            break;
        case 5:
            break;
        default:
            printf("optiune invalida\n");
        }
    } while (op != 5);

    Propozitie_elibereaza(&p);
    return 0;
}

// Să se scrie un program care primește un nume de fișier în linia de comandă. Programul va citi toate
// liniile din fișier într-o listă care este mereu sortată în ordine alfabetică. O linie poate avea maxim 1000 de caractere.
// Pentru ca lista să fie mereu sortată alfabetic, adăugarea unei linii noi se face prin inserarea ei la poziția corectă din
// listă, astfel încât să se mențină proprietatea de sortare. În final se va afișa lista.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1001

typedef struct Linie
{
    char text[MAX_LINE_LENGTH];
    struct Linie *prev;
    struct Linie *next;
} Linie;

typedef struct
{
    Linie *prim;
    Linie *ultim;
} ListaSortata;

Linie *creaza_linie(const char *text)
{
    Linie *linie = (Linie *)malloc(sizeof(Linie));
    if (!linie)
    {
        perror("Eroare la alocarea memoriei");
        exit(EXIT_FAILURE);
    }
    strncpy(linie->text, text, MAX_LINE_LENGTH - 1);
    linie->text[MAX_LINE_LENGTH - 1] = '\0';
    linie->prev = linie->next = NULL;
    return linie;
}

void initializeaza_lista(ListaSortata *lista)
{
    lista->prim = lista->ultim = NULL;
}

void insereaza_sortat(ListaSortata *lista, Linie *linie_noua)
{
    // Cazul listei vide
    if (lista->prim == NULL)
    {
        lista->prim = lista->ultim = linie_noua;
        return;
    }

    Linie *current = lista->prim;

    // Cautam pozitia de inserare
    while (current != NULL && strcmp(linie_noua->text, current->text) > 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        // Inserare la sfarsit
        linie_noua->prev = lista->ultim;
        lista->ultim->next = linie_noua;
        lista->ultim = linie_noua;
    }
    else if (current == lista->prim)
    {
        // Inserare la început
        linie_noua->next = lista->prim;
        lista->prim->prev = linie_noua;
        lista->prim = linie_noua;
    }
    else
    {
        // Inserare in mijloc
        linie_noua->prev = current->prev;
        linie_noua->next = current;
        current->prev->next = linie_noua;
        current->prev = linie_noua;
    }
}

void afiseaza_lista(ListaSortata *lista)
{
    Linie *current = lista->prim;
    while (current != NULL)
    {
        printf("%s", current->text);
        if (current->next != NULL)
        {
            printf("\n");
        }
        current = current->next;
    }
}

void elibereaza_lista(ListaSortata *lista)
{
    Linie *current = lista->prim;
    while (current != NULL)
    {
        Linie *urm = current->next;
        free(current);
        current = urm;
    }
    lista->prim = lista->ultim = NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Utilizare: %s <nume_fisier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fisier = fopen(argv[1], "r");
    if (!fisier)
    {
        perror("Eroare la deschiderea fisierului");
        return EXIT_FAILURE;
    }

    ListaSortata lista;
    initializeaza_lista(&lista);

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fisier) != NULL)
    {

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        Linie *linie = creaza_linie(buffer);
        insereaza_sortat(&lista, linie);
    }

    fclose(fisier);

    printf("Continutul fisierului sortat alfabetic:\n");
    afiseaza_lista(&lista);

    elibereaza_lista(&lista);

    return EXIT_SUCCESS;
}

// Să se scrie un program care implementează o listă de categorii, fiecare categorie având asociată o
// listă de produse. O categorie se definește prin numele său. Un produs se definește prin nume și preț. Programul
// va prezenta utilizatorului un meniu cu următoarele opțiuni: 1-adaugă categorie; 2-adaugă produs (prima oară cere
// o categorie și apoi un produs pe care îl adaugă la acea categorie); 3-afișare categorii (afișează doar numele tuturor
// categoriilor); 4-afișare produse (cere o categorie și afișează toate produsele din ea); 5-ieșire

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct Produs
{
    char nume[MAX_NAME_LENGTH];
    float pret;
    struct Produs *urm;
} Produs;

typedef struct Categorie
{
    char nume[MAX_NAME_LENGTH];
    Produs *produse;
    struct Categorie *urm;
} Categorie;

Categorie *lista_categorii = NULL;

void adauga_categorie()
{
    Categorie *noua = (Categorie *)malloc(sizeof(Categorie));
    printf("Introduceti numele categoriei: ");
    scanf("%s", noua->nume);
    noua->produse = NULL;
    noua->urm = lista_categorii;
    lista_categorii = noua;
    printf("Categoria '%s' a fost adaugata.\n", noua->nume);
}

Categorie *gaseste_categorie(const char *nume)
{
    Categorie *c = lista_categorii;
    while (c != NULL)
    {
        if (strcmp(c->nume, nume) == 0)
        {
            return c;
        }
        c = c->urm;
    }
    return NULL;
}

void adauga_produs()
{
    char nume_categorie[MAX_NAME_LENGTH];
    printf("Introduceti numele categoriei: ");
    scanf("%s", nume_categorie);

    Categorie *c = gaseste_categorie(nume_categorie);
    if (c == NULL)
    {
        printf("Categoria '%s' nu exista.\n", nume_categorie);
        return;
    }

    Produs *nou = (Produs *)malloc(sizeof(Produs));
    printf("Introduceti numele produsului: ");
    scanf("%s", nou->nume);
    printf("Introduceti pretul produsului: ");
    scanf("%f", &nou->pret);
    nou->urm = c->produse;
    c->produse = nou;

    printf("Produsul '%s' a fost adaugat in categoria '%s'.\n", nou->nume, c->nume);
}

void afiseaza_categorii()
{
    printf("\nLista categorii:\n");
    Categorie *c = lista_categorii;
    while (c != NULL)
    {
        printf("- %s\n", c->nume);
        c = c->urm;
    }
}

void afiseaza_produse()
{
    char nume_categorie[MAX_NAME_LENGTH];
    printf("Introduceti numele categoriei: ");
    scanf("%s", nume_categorie);

    Categorie *c = gaseste_categorie(nume_categorie);
    if (c == NULL)
    {
        printf("Categoria '%s' nu exista.\n", nume_categorie);
        return;
    }

    printf("\nProduse din categoria '%s':\n", c->nume);
    Produs *p = c->produse;
    while (p != NULL)
    {
        printf("- %s (%.2f RON)\n", p->nume, p->pret);
        p = p->urm;
    }
}

void elibereaza_memorie()
{
    Categorie *c = lista_categorii;
    while (c != NULL)
    {
        Produs *p = c->produse;
        while (p != NULL)
        {
            Produs *temp_p = p;
            p = p->urm;
            free(temp_p);
        }
        Categorie *temp_c = c;
        c = c->urm;
        free(temp_c);
    }
}

void afiseaza_meniu()
{
    printf("\nMENIU\n");
    printf("1. Adauga categorie\n");
    printf("2. Adauga produs\n");
    printf("3. Afiseaza categorii\n");
    printf("4. Afiseaza produse\n");
    printf("5. Iesire\n");
    printf("Selectati optiunea: ");
}

int main()
{
    int optiune;

    do
    {
        afiseaza_meniu();
        scanf("%d", &optiune);

        switch (optiune)
        {
        case 1:
            adauga_categorie();
            break;
        case 2:
            adauga_produs();
            break;
        case 3:
            afiseaza_categorii();
            break;
        case 4:
            afiseaza_produse();
            break;
        case 5:
            printf("Programul se inchide...\n");
            break;
        default:
            printf("Optiune invalida!\n");
        }
    } while (optiune != 5);

    elibereaza_memorie();
    return 0;
}

// Să se imlementeze o listă dublu înlănțuită care gestionează un parc de automobile. Informaţiile
// relative la un automobil sunt: codul mașinii (număr între 1 si 9000), numărul de locuri (între 1 și 9), puterea (în cai
// putere între 1 și 500), marca, culoarea, anul fabricaţiei maşinii (între 1800 și 2017). Parcul conține n automobile,
// datele sunt citite de la tastatură. Să se scrie următoarele funcții de gestiune a mașinilor:
// a) Introducerea unui automobil nou în listă la începutul listei;
// b) Ștergerea unui anumit automobil din listă, al cărui cod e citit de la tastatură;
// c) Afișarea întregii liste pe ecran;
// d) Afișarea pe ecran doar a automobilelor cu un anumit număr de locuri, citit de la tastatură;
// e) Ordonarea listei în funcție de anul fabricației.
// Să se definească structura pentru o mașină cu ajutorul structurilor cu câmpuri pe biți astfel încât spațiul ocupat să
// fie minim.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int cod : 14;           // 14 biti pentru cod (1-9000, necesita log2(9000) = ~13.14 biti)
    unsigned int nr_locuri : 4;      // 4 biti pentru nr_locuri (1-9, necesita log2(9) = ~3.17 biti)
    unsigned int putere : 9;         // 9 biti pentru putere (1-500, necesita log2(500) = ~8.97 biti)
    unsigned int an_fabricatie : 11; // 11 biti pentru an (1800-2017, necesita log2(2017-1800+1) = ~7.78 biti)
    char marca[20];                  // Marca masinii
    char culoare[15];                // Culoarea masinii
} Automobil;

// Definirea structurii pentru un nod din lista dublu inlantuita
typedef struct Nod
{
    Automobil auto_info;
    struct Nod *prev;
    struct Nod *next;
} Nod;

// Functia pentru crearea unui nou nod
Nod *creareNod(Automobil auto_info)
{
    Nod *nod_nou = (Nod *)malloc(sizeof(Nod));
    if (nod_nou == NULL)
    {
        printf("Eroare la alocarea memoriei!\n");
        exit(1);
    }

    nod_nou->auto_info = auto_info;
    nod_nou->prev = NULL;
    nod_nou->next = NULL;

    return nod_nou;
}

// a) Introducerea unui automobil nou in lista la inceputul listei
void adaugaLaInceput(Nod **cap, Automobil auto_info)
{
    Nod *nod_nou = creareNod(auto_info);

    if (*cap == NULL)
    {
        *cap = nod_nou;
        return;
    }

    nod_nou->next = *cap;
    (*cap)->prev = nod_nou;
    *cap = nod_nou;
}

// b) stergerea unui anumit automobil din lista, al carui cod e citit de la tastatura
int stergeAutomobil(Nod **cap, int cod)
{
    if (*cap == NULL)
    {
        printf("Lista este goala!\n");
        return 0;
    }

    Nod *curent = *cap;

    // Cautam nodul cu codul specificat
    while (curent != NULL && curent->auto_info.cod != cod)
    {
        curent = curent->next;
    }

    // Daca nu am gasit nodul
    if (curent == NULL)
    {
        printf("Automobilul cu codul %d nu a fost gasit!\n", cod);
        return 0;
    }

    // Daca nodul este capul listei
    if (curent == *cap)
    {
        *cap = curent->next;
    }

    // Actualizsm legăturile
    if (curent->prev != NULL)
    {
        curent->prev->next = curent->next;
    }

    if (curent->next != NULL)
    {
        curent->next->prev = curent->prev;
    }

    free(curent);
    printf("Automobilul cu codul %d a fost șters!\n", cod);
    return 1;
}

// c) Afisarea întregii liste pe ecran
void afiseazaLista(Nod *cap)
{
    if (cap == NULL)
    {
        printf("Lista este goală!\n");
        return;
    }

    printf("\n----- Lista de automobile -----\n");
    Nod *curent = cap;
    int index = 1;

    while (curent != NULL)
    {
        printf("Automobilul %d:\n", index++);
        printf("  Cod: %d\n", curent->auto_info.cod);
        printf("  Număr locuri: %d\n", curent->auto_info.nr_locuri);
        printf("  Putere: %d CP\n", curent->auto_info.putere);
        printf("  Marca: %s\n", curent->auto_info.marca);
        printf("  Culoare: %s\n", curent->auto_info.culoare);
        printf("  An fabricație: %d\n", curent->auto_info.an_fabricatie);
        printf("----------------\n");

        curent = curent->next;
    }
}

// d) Afisarea pe ecran doar a automobilelor cu un anumit numar de locuri
void afiseazaAutomobileDupaLocuri(Nod *cap, int nr_locuri)
{
    if (cap == NULL)
    {
        printf("Lista este goala!\n");
        return;
    }

    printf("\n- Automobile cu %d locuri --\n", nr_locuri);
    Nod *curent = cap;
    int index = 1;
    int gasit = 0;

    while (curent != NULL)
    {
        if (curent->auto_info.nr_locuri == nr_locuri)
        {
            printf("Automobilul %d:\n", index++);
            printf("  Cod: %d\n", curent->auto_info.cod);
            printf("  Numar locuri: %d\n", curent->auto_info.nr_locuri);
            printf("  Putere: %d CP\n", curent->auto_info.putere);
            printf("  Marca: %s\n", curent->auto_info.marca);
            printf("  Culoare: %s\n", curent->auto_info.culoare);
            printf("  An fabricatie: %d\n", curent->auto_info.an_fabricatie);
            printf("---------------------------\n");
            gasit = 1;
        }

        curent = curent->next;
    }

    if (!gasit)
    {
        printf("Nu exista automobile cu %d locuri!\n", nr_locuri);
    }
}

// Functie pentru interschimbarea datelor a 2 noduri
void interschimbaDate(Nod *a, Nod *b)
{
    Automobil temp = a->auto_info;
    a->auto_info = b->auto_info;
    b->auto_info = temp;
}

// e) Ordonarea listei in functie de anul fabricatiei
void ordonareDupaAnFabricatie(Nod *cap)
{
    if (cap == NULL || cap->next == NULL)
    {
        return; // Lista goala sau cu un singur element este deja ordonata
    }

    int schimbat;
    Nod *curent;
    Nod *ultimul = NULL;

    do
    {
        schimbat = 0;
        curent = cap;

        while (curent->next != ultimul)
        {
            if (curent->auto_info.an_fabricatie > curent->next->auto_info.an_fabricatie)
            {
                interschimbaDate(curent, curent->next);
                schimbat = 1;
            }
            curent = curent->next;
        }
        ultimul = curent;
    } while (schimbat);

    printf("Lista a fost ordonata dupa anul fabricatiei!\n");
}

// Validare date introduse
int validareDate(Automobil auto_info)
{
    if (auto_info.cod < 1 || auto_info.cod > 9000)
    {
        printf("Codul masinii trebuie sa fie intre 1 si 9000!\n");
        return 0;
    }

    if (auto_info.nr_locuri < 1 || auto_info.nr_locuri > 9)
    {
        printf("Numarul de locuri trebuie sa fie intre 1 si 9!\n");
        return 0;
    }

    if (auto_info.putere < 1 || auto_info.putere > 500)
    {
        printf("Puterea trebuie sa fie intre 1 si 500 CP!\n");
        return 0;
    }

    if (auto_info.an_fabricatie < 1800 || auto_info.an_fabricatie > 2017)
    {
        printf("Anul fabricatiei trebuie sa fie intre 1800 si 2017!\n");
        return 0;
    }

    return 1;
}

void elibereazaMemorie(Nod **cap)
{
    Nod *curent = *cap;
    Nod *urmator;

    while (curent != NULL)
    {
        urmator = curent->next;
        free(curent);
        curent = urmator;
    }

    *cap = NULL;
}

int main()
{
    Nod *cap = NULL;
    int optiune, n, i, cod, nr_locuri;
    int temp_cod, temp_locuri, temp_putere, temp_an; // Variabile temporare pentru citire
    Automobil auto_info;

    printf("Introduceti numarul de automobile din parc: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nIntroduceti datele pentru automobilul %d:\n", i + 1);

        printf("Cod (1-9000): ");
        scanf("%d", &temp_cod);
        auto_info.cod = temp_cod;

        printf("Numar de locuri (1-9): ");
        scanf("%d", &temp_locuri);
        auto_info.nr_locuri = temp_locuri;

        printf("Putere (CP, 1-500): ");
        scanf("%d", &temp_putere);
        auto_info.putere = temp_putere;

        printf("Marca: ");
        scanf("%s", auto_info.marca);

        printf("Culoare: ");
        scanf("%s", auto_info.culoare);

        printf("Anul fabricatiei (1800-2017): ");
        scanf("%d", &temp_an);
        auto_info.an_fabricatie = temp_an;

        if (validareDate(auto_info))
        {
            adaugaLaInceput(&cap, auto_info);
            printf("Automobil adaugat cu succes!\n");
        }
        else
        {
            printf("Date invalide! Automobilul nu a fost adaugat.\n");
            i--;
        }
    }

    do
    {

        printf("1. Adauga un automobil nou la inceputul listei\n");
        printf("2. Sterge un automobil dupa cod\n");
        printf("3. Afiseaza toate automobilele\n");
        printf("4. Afiseaza automobilele cu un anumit numar de locuri\n");
        printf("5. Ordoneaza lista dupa anul fabricatiei\n");
        printf("0. Iesire\n");
        printf("Optiune: ");
        scanf("%d", &optiune);

        switch (optiune)
        {
        case 1:
            printf("\nIntroduceti datele pentru noul automobil:\n");

            printf("Cod (1-9000): ");
            scanf("%d", &temp_cod);
            auto_info.cod = temp_cod;

            printf("Numar de locuri (1-9): ");
            scanf("%d", &temp_locuri);
            auto_info.nr_locuri = temp_locuri;

            printf("Putere (CP, 1-500): ");
            scanf("%d", &temp_putere);
            auto_info.putere = temp_putere;

            printf("Marca: ");
            scanf("%s", auto_info.marca);

            printf("Culoare: ");
            scanf("%s", auto_info.culoare);

            printf("Anul fabricatiei (1800-2017): ");
            scanf("%d", &temp_an);
            auto_info.an_fabricatie = temp_an;

            if (validareDate(auto_info))
            {
                adaugaLaInceput(&cap, auto_info);
                printf("Automobil adăugat cu succes!\n");
            }
            else
            {
                printf("Date invalide! Automobilul nu a fost adaugat.\n");
            }
            break;

        case 2:
            printf("Introduceti codul automobilului de sters: ");
            scanf("%d", &cod);
            stergeAutomobil(&cap, cod);
            break;

        case 3:
            afiseazaLista(cap);
            break;

        case 4:
            printf("Introduceti numarul de locuri pentru filtrare: ");
            scanf("%d", &nr_locuri);
            if (nr_locuri < 1 || nr_locuri > 9)
            {
                printf("Numarul de locuri trebuie să fie intre 1 si 9!\n");
            }
            else
            {
                afiseazaAutomobileDupaLocuri(cap, nr_locuri);
            }
            break;

        case 5:
            ordonareDupaAnFabricatie(cap);
            break;

        case 0:
            printf("Program incheiat!\n");
            break;

        default:
            printf("Optiune invalida! incercati din nou.\n");
        }
    } while (optiune != 0);

    elibereazaMemorie(&cap);

    return 0;
}