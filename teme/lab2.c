/*: Se cere un număr n și apoi un vector de n rezultate ale studenților la un examen. Fiecare rezultat
este definit prin (nume,nota). Se cere să se sorteze folosind qsort vectorul în ordinea notelor, notele cele mai mari
fiind primele. Dacă două note sunt identice, rezultatele respective se vor sorta în ordinea alfabetică a numelor.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct
{
    char nume[MAX_NAME];
    float nota;
} Student;

int compara(const void *a, const void *b)
{
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;

    if (sa->nota != sb->nota)
    {
        return (sb->nota - sa->nota) > 0 ? 1 : -1; // Sortare descrescătoare după notă
    }
    return strcmp(sa->nume, sb->nume); // Sortare alfabetică după nume
}

int main()
{
    int n;
    printf("Introduceți numărul de studenți: ");
    scanf("%d", &n);

    Student *studenti = malloc(n * sizeof(Student));
    if (!studenti)
    {
        printf("Eroare la alocarea memoriei!\n");
        return 1;
    }

    printf("Introduceți numele și nota fiecărui student:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Student %d: ", i + 1);
        scanf("%s %f", studenti[i].nume, &studenti[i].nota);
    }

    qsort(studenti, n, sizeof(Student), compara);

    printf("\nLista sortată:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %.2f\n", studenti[i].nume, studenti[i].nota);
    }

    free(studenti);
    return 0;
}

//////////////////////////////////////////////////////////
/*Să se implementeze o funcție care primește ca parametri un vector de întregi, numărul elementelor
din vector transmis prin adresă și un predicat care testează dacă un întreg îndeplinește o anumită condiție. Funcția
va sterge din vector toate elementele care nu îndeplinesc condiția dată și va actualiza numărul elementelor cu
numărul de elemente rămas în vector. Să se testeze funcția cu un predicat care testează dacă un număr este
negativ și să se afișeze vectorul rezultat.*/
#include <stdio.h>
#include <stdlib.h>

typedef int (*Predicat)(int);

void filtrare_vector(int **v, int *n, Predicat functie_p)
{
    int j = 0;

    for (int i = 0; i < *n; i++)
    {
        if (functie_p((*v)[i]))
        {
            (*v)[j++] = (*v)[i];
        }
    }

    *n = j;
    *v = realloc(*v, (*n) * sizeof(int));
}

int este_negativ(int x)
{
    return x < 0;
}

int main()
{
    int *v = malloc(7 * sizeof(int));
    int n = 7;

    int valori[] = {4, -3, 7, -1, 0, -9, 5};
    for (int i = 0; i < n; i++)
        v[i] = valori[i];

    printf("Vector initial: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");

    filtrare_vector(&v, &n, este_negativ);

    printf("Vector filtrat (doar numere negative): ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");

    free(v);
    return 0;
}

//////////////////////////////////////////////////////////
/*: Se introduce un număr întreg n<10 și apoi n numere de tip float. Să se folosească funcția qsort
pentru a sorta aceste numere în mod crescător. Se va introduce apoi un număr x de tip float. Folosind funcția
bsearch, să se determine dacă x există în vectorul sortat. Se pot consulta paginile de manual pentru funcțiile qsort
și bsearch.*/

#include <stdio.h>
#include <stdlib.h>

int compara_float(const void *a, const void *b)
{
    float fa = *(const float *)a;
    float fb = *(const float *)b;
    return (fa > fb) - (fa < fb);
}

int main()
{
    int n;
    float x;

    // Citirea lui n (cu verificare)
    do
    {
        printf("Introduceti numarul de elemente (n < 10): ");
        scanf("%d", &n);
    } while (n >= 10 || n <= 0);

    float *v = (float *)malloc(n * sizeof(float));
    if (v == NULL)
    {
        printf("Eroare de alocare a memoriei!\n");
        return 1;
    }

    printf("Introduceti %d numere float:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &v[i]);
    }

    qsort(v, n, sizeof(float), compara_float);

    printf("Vector sortat: ");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f ", v[i]);
    }
    printf("\n");

    printf("Introduceti numarul x pentru cautare: ");
    scanf("%f", &x);

    float *gasit = (float *)bsearch(&x, v, n, sizeof(float), compara_float);

    if (gasit)
    {
        printf("Numarul %.2f a fost gasit in vector.\n", x);
    }
    else
    {
        printf("Numarul %.2f NU a fost gasit in vector.\n", x);
    }

    // Eliberare memorie
    free(v);

    return 0;
}

//////////////////////////////////////////////////////////
/*Să se implementeze o funcție care tabelează o funcție matematică de un parametru, primită ca
argument. Funcția tabelată primește un parametru de tip double și returnează o valoare tot de tip double. Funcția
de tabelare va primi ca parametri: a și b - capetele de tip double ale intervalului închis de tabelat, n - un număr
întreg care arată în câte segmente egale se împarte intervalul [a,b], incluzând capetele acestuia și f - funcția de
tabelat. Să se testeze funcția de tabelare cu valori a,b și n citite de la tastatură, tabelând funcțiile cos, sqrt și fabs
din math.h
Exemplu: tabelare(-10,10,20,fabs) va afișa pe câte o linie valori de forma f(-10)=10 f(-9)=9 … f(10)=10*/
#include <stdio.h>
#include <math.h>

typedef double (*FunctieMatematica)(double);

void tabelare(double a, double b, int n, FunctieMatematica f)
{
    if (n < 2)
    {
        printf("Trebuie cel putin 2 puncte pentru tabelare.\n");
        return;
    }

    double pas = (b - a) / n;

    for (int i = 0; i < n; i++)
    {
        double x = a + i * pas;
        printf("f(%.2f) = %.6f\n", x, f(x));
    }
}

int main()
{
    double a, b;
    int n;

    printf("Introduceti a si b: ");
    scanf("%lf %lf", &a, &b);

    printf("Introduceti numarul de puncte n: ");
    scanf("%d", &n);

    printf("\nTabelare pentru fabs:\n");
    tabelare(a, b, n, fabs);

    printf("\nTabelare pentru sqrt (doar pentru valori pozitive):\n");
    if (a >= 0)
        tabelare(a, b, n, sqrt);
    else
        printf("Nu se poate calcula sqrt pentru numere negative.\n");

    printf("\nTabelare pentru cos:\n");
    tabelare(a, b, n, cos);

    return 0;
}

//////////////////////////////////////////////////////////

/*Să se scrie un program pentru tabelarea unor funcţii matematice. Programul trebuie să tabeleze
funcţiile (x*x*x+4)/(x*x+5), x+10 şi 2*x*x-1.
Tabelarea se va realiza pe intervalul [A,B] cu pasul P. Valorile A, B şi P se vor citi de la tastatură. Programul va
afişa valorile funcţiilor sub formă de tabel.
Trebuie să se folosească pointeri la funcţii. Scrieţi o funcţie generică pentru tabelarea unei funcţii matematice
oarecare. Această funcţie generică va avea un parametru de tip pointer la funcţie.
Folosind funcţia generică, tabelaţi cele patru funcţii matematice amintite mai sus.*/

#include <stdio.h>

typedef double (*FunctieMatematica)(double);

double f1(double x)
{
    return (x * x * x + 4) / (x * x + 5);
}

double f2(double x)
{
    return x + 10;
}

double f3(double x)
{
    return 2 * x * x - 1;
}

void tabela(FunctieMatematica f, double A, double B, double P, const char *nume)
{
    printf("Tabelarea functiei %s pe intervalul [%.2f, %.2f] cu pasul %.2f:\n\n", nume, A, B, P);
    printf(" x\tf(x)\n");

    for (double x = A; x <= B; x += P)
    {
        printf("%.2f\t%.4f\n", x, f(x));
    }

    printf("\n");
}

int main()
{
    double A, B, P;

    printf("Introduceti valoarea lui A: ");
    scanf("%lf", &A);
    printf("Introduceti valoarea lui B: ");
    scanf("%lf", &B);
    printf("Introduceti pasul P: ");
    scanf("%lf", &P);

    if (P <= 0 || A > B)
    {
        printf("Eroare: Pasul trebuie sa fie pozitiv, iar A trebuie sa fie mai mic sau egal cu B.\n");
        return 1;
    }

    tabela(f1, A, B, P, "(x^3 + 4) / (x^2 + 5)");
    tabela(f2, A, B, P, "x + 10");
    tabela(f3, A, B, P, "2*x^2 - 1");

    return 0;
}

//////////////////////////////////////////////////////////
/*Se citesc mai multe cuvinte din linia de comandă. Cu ajutorul pointerilor la funcții (un vector de
pointeri la funcții) să se apeleze într-o structură repetitivă următoarele funcții. Să se afișeze rezultatele pentru
fiecare cuvânt pe ecran și în fișierul text CUVINTE.TXT.
a) Primește parametru un șir de caractere și returneză lungimea șirului.
b) Primește parametru un șir de caractere și returneză numărul de vocale din text.
c) Primește parametru un șir de caractere și returneză numărul de litere mari din text.
Primește parametru un șir de caractere și returneză diferența codurilor ASCII ale primului caracter și al ultimului
caracter.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Functie care returneaza lungimea unui sir de caractere
int lungime_sir(const char *s)
{
    return strlen(s);
}

// Functie care returneaza numarul de vocale dintr-un sir de caractere
int numara_vocale(const char *s)
{
    int count = 0;
    while (*s)
    {
        char c = tolower(*s);
        if (strchr("aeiou", c))
        {
            count++;
        }
        s++;
    }
    return count;
}

// Functie care returneaza numarul de litere mari dintr-un sir de caractere
int numara_litere_mari(const char *s)
{
    int count = 0;
    while (*s)
    {
        if (isupper(*s))
        {
            count++;
        }
        s++;
    }
    return count;
}

// Functie care returneaza diferenta dintre codurile ASCII ale primului si ultimului caracter
int diferenta_ascii(const char *s)
{
    if (strlen(s) == 0)
        return 0; // Daca sirul este gol
    return s[0] - s[strlen(s) - 1];
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Utilizare: %s cuvant1 cuvant2 ...\n", argv[0]);
        return 1;
    }

    // vector de pointeri la functii
    int (*functii[])(const char *) = {lungime_sir, numara_vocale, numara_litere_mari, diferenta_ascii};
    const char *nume_functii[] = {"Lungime", "Vocale", "Majuscule", "Diferenta ASCII"};

    // deschidem fisierul pentru scriere
    FILE *fout = fopen("CUVINTE.TXT", "w");
    if (!fout)
    {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        printf("Cuvant: %s\n", argv[i]);
        fprintf(fout, "Cuvant: %s\n", argv[i]);

        for (int j = 0; j < 4; j++)
        {
            int rezultat = functii[j](argv[i]);
            printf("%s: %d\n", nume_functii[j], rezultat);
            fprintf(fout, "%s: %d\n", nume_functii[j], rezultat);
        }
        printf("\n");
        fprintf(fout, "\n");
    }

    fclose(fout);
    return 0;
}
