// Să se modifice exemplul 2 astfel încât funcția err să încapsuleze și condiția de eroare. Pentru
// aceasta, ea primește în plus pe prima poziție o variabilă de tip int care reprezintă o valoare logică. Dacă valoarea
// este true, se va executa err ca în exemplu, altfel err nu va avea niciun efect.
// Exemplu de folosire: err(n<=0||n>100,"n invalid: %d\n",n); // fără if în față, deoarece err încapsulează condiția

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void err(int condition, const char *fmt, ...)
{
    if (!condition)
        return;

    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "eroare: ");
    vfprintf(stderr, fmt, va);
    va_end(va);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

int main()
{
    int i, n;
    float x, y, e, min, max;

    printf("n=");
    scanf("%d", &n);
    err(n <= 0 || n > 100, "n invalid: %d\n", n); // Folosire fara if

    printf("x=");
    scanf("%g", &x);
    printf("y=");
    scanf("%g", &y);
    err(x >= y, "x=%g nu este mai mic decat y=%g\n", x, y); // Folosire fara if

    max = x;
    min = y;

    for (i = 0; i < n; i++)
    {
        printf("e=");
        scanf("%g", &e);
        err(e < x || e > y, "element invalid: %g\n", e); // Folosire fara if

        if (e < min)
            min = e;
        if (e > max)
            max = e;
    }

    printf("min: %g, max: %g\n", min, max);
    return 0;
}

// Să se scrie o funcție float *allocVec(int n,...) care primește pe prima poziție un număr de elemente
// iar apoi n elemente reale. Funcția va aloca dinamic un vector de tip float în care va depune toate elementele.
// Exemplu: allocVec(3,7.2,-1,0) => {7.2, -1, 0}

#include <stdarg.h>
#include <stdlib.h>

float *allocVec(int n, ...)
{
    float *vec = malloc(n * sizeof(float));
    if (!vec)
        return NULL;

    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = (float)va_arg(args, double);
    }
    va_end(args);

    return vec;
}

// Să se scrie o funcție absN(int n,...) care primește un număr n de adrese de tip float și setează la
// fiecare dintre aceste adrese valoarea absolută de la acea locație.
// Exemplu: absN(2,&x,&y); // echivalent cu x=fabs(x); y=fabs(y);

#include <stdarg.h>
#include <math.h>

void absN(int n, ...)
{
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++)
    {
        float *ptr = va_arg(args, float *);
        *ptr = fabs(*ptr);
    }

    va_end(args);
}

// Să se scrie o funcție crescator(int n,char tip,...) care primește un număr n de valori și returnează 1
// dacă ele sunt în ordine strict crescătoare, altfel 0. Caracterul tip indică tipul valorilor și poate fi ‘d’ - int, ‘f’ - double.
// Exemplu: printf(“%d”,crescator(3,’d’,-1,7,9));

#include <stdarg.h>
#include <string.h>

int crescator(int n, char tip, ...)
{
    va_list args;
    va_start(args, tip);

    int prev_int, current_int;
    double prev_double, current_double;

    if (tip == 'd')
    {
        prev_int = va_arg(args, int);
        for (int i = 1; i < n; i++)
        {
            current_int = va_arg(args, int);
            if (current_int <= prev_int)
            {
                va_end(args);
                return 0;
            }
            prev_int = current_int;
        }
    }
    else if (tip == 'f')
    {
        prev_double = va_arg(args, double);
        for (int i = 1; i < n; i++)
        {
            current_double = va_arg(args, double);
            if (current_double <= prev_double)
            {
                va_end(args);
                return 0;
            }
            prev_double = current_double;
        }
    }

    va_end(args);
    return 1;
}

//     Să se implementeze o funcție input(const char *fmt,...). În șirul fmt pot fi caractere obișnuite (orice
//     în afară de %) și placeholdere (% urmat de o literă). Pentru fiecare placeholder posibil ( %d - int, %f -float, %c -
//     char ), în lista de argumente variabile se va afla adresa unei variabile de tipul corespunzător. Funcția afișează pe
//     ecran caracterele obișnuite și citește de la tastatură pentru placeholdere.
//     Exemplu: input(”n=%dch=%c”,&n,&ch); // citește o valoare de tip int în n și de tip char în ch

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void input(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
            case 'd':
            {
                int *ptr = va_arg(args, int *);
                scanf("%d", ptr);
                break;
            }
            case 'f':
            {
                float *ptr = va_arg(args, float *);
                scanf("%f", ptr);
                break;
            }
            case 'c':
            {
                char *ptr = va_arg(args, char *);
                scanf(" %c", ptr);
                break;
            }
            }
        }
        else
        {
            putchar(*fmt);
        }
        fmt++;
    }

    va_end(args);
}

// Să se scrie o funcție char *concat(int n,...) care primește un număr de șiruri de caractere și apoi
// șirurile propriu-zise. Funcția va concatena într-un nou șir, alocat dinamic, conținuturile tuturor șirurilor date, cu câte
// un spațiu între ele și va returna acest șir.
// Exemplu: concat(3,”Ion”,”si”,”Ana”) => “Ion si Ana”

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char *concat(int n, ...)
{
    va_list args;
    va_start(args, n);

    // Calculăm lungimea totală
    size_t total_len = 0;
    for (int i = 0; i < n; i++)
    {
        total_len += strlen(va_arg(args, char *));
        if (i < n - 1)
            total_len++; // pentru spațiu
    }
    va_end(args);

    // Alocăm memorie
    char *result = malloc(total_len + 1);
    if (!result)
        return NULL;

    // Construim șirul
    va_start(args, n);
    char *ptr = result;
    for (int i = 0; i < n; i++)
    {
        char *str = va_arg(args, char *);
        strcpy(ptr, str);
        ptr += strlen(str);
        if (i < n - 1)
        {
            *ptr++ = ' ';
        }
    }
    *ptr = '\0';

    va_end(args);
    return result;
}

// Să se scrie o funcție int comune(int nVec,...) care primește un număr de vectori cu valori de tip int și
// vectorii propriu-ziși. Fiecare vector se dă prin 2 argumente: un pointer la elementele sale și dimensiunea. Funcția
// va returna numărul de elemente comune care se regăsesc în toți vectorii.
// Exemplu: comune(3,v1,2,v2,3,v3,3) => returnează 2 pentru v1={5,8}, v2={8,3,5}, v3={5,0,8}

#include <stdarg.h>
#include <stdlib.h>

int contains(int *vec, int size, int val)
{
    for (int i = 0; i < size; i++)
    {
        if (vec[i] == val)
            return 1;
    }
    return 0;
}

int comune(int nVec, ...)
{
    va_list args;
    va_start(args, nVec);

    // Citim primul vector ca referință
    int *first_vec = va_arg(args, int *);
    int first_size = va_arg(args, int);

    int count = 0;
    for (int i = 0; i < first_size; i++)
    {
        int val = first_vec[i];
        int found_in_all = 1;

        va_list temp_args;
        va_copy(temp_args, args);
        for (int j = 1; j < nVec; j++)
        {
            int *vec = va_arg(temp_args, int *);
            int size = va_arg(temp_args, int);
            if (!contains(vec, size, val))
            {
                found_in_all = 0;
                break;
            }
        }
        va_end(temp_args);

        if (found_in_all)
            count++;
    }

    va_end(args);
    return count;
}

// Să se scrie o funcție sortare(int n,...) care pe prima poziție are numărul de elemente de sortat, iar
// pe următoarele poziții n adrese de valori de tip int. Funcția va sorta crescător valorile de la adresele date.
// Exemplu: sortare(3,&i,&j,&k); // sortează crescător valorile lui i, j și k

#include <stdarg.h>

void sortare(int n, ...)
{
    va_list args;
    va_start(args, n);

    int *addrs[n];
    int values[n];

    // Citim adresele și valorile
    for (int i = 0; i < n; i++)
    {
        addrs[i] = va_arg(args, int *);
        values[i] = *addrs[i];
    }

    // Sortăm valorile
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (values[i] > values[j])
            {
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }

    // Scriem valorile sortate înapoi
    for (int i = 0; i < n; i++)
    {
        *addrs[i] = values[i];
    }

    va_end(args);
}

// parametrii în linia de comanda

// Scrieți un program care calculează suma parametrilor primiți din linia de comandă (numere reale).
// Exemplu: execuția fără parametri va fișa 0, iar execuția cu parametrii 1.1 6.57 99.122 va afișa 106.792

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    double sum = 0.0;

    for (int i = 1; i < argc; i++)
    {
        sum += atof(argv[i]);
    }

    printf("%.3f\n", sum);
    return 0;
}

// Să se scrie un program denumit criptare, care criptează/decriptează un text primit în linia de
// comandă. Programul va fi apelat în felul următor: ./criptare operatie cheie cuvant1 cuvant2 ...
// Operația poate fi enc pentru criptare sau dec decriptare. Cheia este un număr întreg. Algoritmul de criptare este
// următorul: pentru fiecare literă din cuvinte se consideră codul său ASCII, la care se adună cheia specificată,
// rezultând un nou cod ASCII, cel al literei criptate. Adunarea este circulară, adică ‘z’ incrementat cu 1 devine ‘a’.
// Decriptarea este inversă: din cuvintele criptate se scade circular cheia specificată. Literele mari se transformă la
// început în litere mici.
// Exemple:
// ./criptare enc 1 zaraza -> absbab
// ./criptare dec 1 bcfdfebs -> abecedar
// ./criptare enc 10 vine VINE primavara PRImaVAra -> fsxo fsxo zbswkfkbk zbswkfkbk

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void process_word(const char *word, int key, int encrypt)
{
    for (int i = 0; word[i]; i++)
    {
        char c = tolower(word[i]);
        if (isalpha(c))
        {
            int base = c - 'a';
            if (encrypt)
            {
                base = (base + key) % 26;
            }
            else
            {
                base = (base - key + 26) % 26;
            }
            putchar('a' + base);
        }
        else
        {
            putchar(c);
        }
    }
    putchar(' ');
}

int main(int argc, char *argv[])
{
    if (argc < 4 || (strcmp(argv[1], "enc") && strcmp(argv[1], "dec")))
    {
        fprintf(stderr, "Utilizare: %s enc/dec cheie cuvinte...\n", argv[0]);
        return 1;
    }

    int encrypt = !strcmp(argv[1], "enc");
    int key = atoi(argv[2]);

    for (int i = 3; i < argc; i++)
    {
        process_word(argv[i], key, encrypt);
    }

    putchar('\n');
    return 0;
}

// Un program primește în linia de comandă o expresie formată din numere reale și operatorii {addadunare, sub-scădere, mul-înmulțire, div-împărțire}. Programul va calcula valoarea expresiei și va afișa rezultatul.
// Expresia se calculează de la stânga la dreapta, fără a ține cont de precedența matematică a operatorilor.
// Exemplu: ./calcul 10.5 add 1.5 div 3 va afișa: 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Utilizare: %s num1 op num2 op...\n", argv[0]);
        return 1;
    }

    double result = atof(argv[1]);

    for (int i = 2; i < argc; i += 2)
    {
        char *op = argv[i];
        double num = atof(argv[i + 1]);

        if (!strcmp(op, "add"))
        {
            result += num;
        }
        else if (!strcmp(op, "sub"))
        {
            result -= num;
        }
        else if (!strcmp(op, "mul"))
        {
            result *= num;
        }
        else if (!strcmp(op, "div"))
        {
            result /= num;
        }
    }

    printf("%g\n", result);
    return 0;
}

// Un program primește în linia de comandă o serie de opțiuni și de cuvinte, mixate între ele. Opțiunile
// specifică operații care se execută asupra cuvintelor. Opțiunile încep cu - (minus) și pot fi: u-transformă toate literele
// cuvintelor în majuscule; f-transformă prima literă în majusculă și următoarele în minuscule; r-inversează literele din
// cuvinte. După fiecare cuvânt se resetează toate opțiunile anterioare. Să se afișeze cuvintele primite în linia de
// comandă cu transformările aplicate.
// Exemplu: ./procesare -f mAria -r -u abac va afișa: Maria CABA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void process_word(char *word, int u, int f, int r)
{
    if (u)
    {
        for (int i = 0; word[i]; i++)
        {
            word[i] = toupper(word[i]);
        }
    }
    if (f)
    {
        word[0] = toupper(word[0]);
        for (int i = 1; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }
    }
    if (r)
    {
        int len = strlen(word);
        for (int i = 0; i < len / 2; i++)
        {
            char temp = word[i];
            word[i] = word[len - 1 - i];
            word[len - 1 - i] = temp;
        }
    }
    printf("%s ", word);
}

int main(int argc, char *argv[])
{
    int u = 0, f = 0, r = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            u = f = r = 0;
            for (int j = 1; argv[i][j]; j++)
            {
                if (argv[i][j] == 'u')
                    u = 1;
                if (argv[i][j] == 'f')
                    f = 1;
                if (argv[i][j] == 'r')
                    r = 1;
            }
        }
        else
        {
            process_word(argv[i], u, f, r);
        }
    }

    putchar('\n');
    return 0;
}

// Un program primește în linia de comandă ca prim argument un cod de operație și pe urmă o serie
// de cuvinte. Codul poate fi: 0-afișează numărul total de litere din toate cuvintele: 1-afișează fiecare literă de câte ori
// apare în toate cuvintele.
// Exemplu: ./statistica 0 ion merge la film va afișa: 14

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Utilizare: %s 0/1 cuvinte...\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);
    int counts[26] = {0};
    int total = 0;

    for (int i = 2; i < argc; i++)
    {
        for (int j = 0; argv[i][j]; j++)
        {
            if (isalpha(argv[i][j]))
            {
                char c = tolower(argv[i][j]);
                counts[c - 'a']++;
                total++;
            }
        }
    }

    if (mode == 0)
    {
        printf("%d\n", total);
    }
    else if (mode == 1)
    {
        for (int i = 0; i < 26; i++)
        {
            if (counts[i] > 0)
            {
                printf("%c: %d\n", 'a' + i, counts[i]);
            }
        }
    }

    return 0;
}