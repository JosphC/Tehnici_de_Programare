// Să se creeze o structură care reține următoarele informații despre un student: nume (maxim 20 de
//     caractere), nota. Să se citească un element din structură și să se afișeze pe ecran.

#include <stdio.h>

// Definim structura Student
struct Student
{
    char nume[21]; // 20 de caractere + 1 pentru caracterul nul '\0'
    float nota;
};

int main()
{
    struct Student s;

    // Citim numele si nota
    printf("Introdu numele studentului (max 20 caractere): ");
    fgets(s.nume, sizeof(s.nume), stdin);

    printf("Introdu nota studentului: ");
    scanf("%f", &s.nota);

    printf("\n--- Informații Student ---\n");
    printf("Nume: %s", s.nume);
    printf("Nota: %.2f\n", s.nota);

    return 0;
}

// Să se codifice cu ajutorul structurilor cu câmpuri pe biți informațiile despre un fișier: nume (șir de
//     maxim 15 caractere), dimensiunea acestuia (int - număr de octeți, maxim 1024 octeți), tipul acestuia (.txt - 0, .doc
//     - 1, .xls – 2), tipul fisierului (normal – 0, read-only – 1). Să se citească informația despre un fișier, și să se afișeze
//     pe ecran.

#include <stdio.h>
#include <string.h>

// Structura cu bit fields
struct Fisier
{
    char nume[16];                 // 15 caractere + '\0'
    unsigned int dimensiune : 10;  // max 1024 -> 2^10
    unsigned int tip_extensie : 2; // 0 = .txt, 1 = .doc, 2 = .xls
    unsigned int permisiune : 1;   // 0 = normal, 1 = read-only
};

int main()
{
    struct Fisier f;
    unsigned int temp;

    // Citire
    printf("Introdu numele fisierului (max 15 caractere): ");
    fgets(f.nume, sizeof(f.nume), stdin);
    f.nume[strcspn(f.nume, "\n")] = '\0';

    printf("Introdu dimensiunea fisierului (max 1024): ");
    scanf("%u", &temp);
    f.dimensiune = temp;

    printf("Introdu tipul extensiei (0 = .txt, 1 = .doc, 2 = .xls): ");
    scanf("%u", &temp);
    f.tip_extensie = temp;

    printf("Introdu tipul fisierului (0 = normal, 1 = read-only): ");
    scanf("%u", &temp);
    f.permisiune = temp;

    // Afișare
    printf("\n--- Informații despre fișier ---\n");
    printf("Nume: %s\n", f.nume);
    printf("Dimensiune: %u octeți\n", f.dimensiune);
    printf("Extensie: ");
    switch (f.tip_extensie)
    {
    case 0:
        printf(".txt\n");
        break;
    case 1:
        printf(".doc\n");
        break;
    case 2:
        printf(".xls\n");
        break;
    default:
        printf("Necunoscut\n");
        break;
    }
    printf("Permisiune: %s\n", f.permisiune ? "read-only" : "normal");

    return 0;
}

// Cu ajutorul structurii de la problema mai sus să se salveze într-un vector de structuri declarat static
// informații despre mai multe fișiere (maxim 10). Să se citească de la tastatură informațiile despre fișiere și să se
// salveze în fișierul memorie.txt.

#include <stdio.h>
#include <string.h>

#define MAX_FISIERE 10

// Structura cu bit fields
struct Fisier
{
    char nume[16];                 // max 15 caractere + '\0'
    unsigned int dimensiune : 10;  // max 1024
    unsigned int tip_extensie : 2; // 0 = .txt, 1 = .doc, 2 = .xls
    unsigned int permisiune : 1;   // 0 = normal, 1 = read-only
};

int main()
{
    struct Fisier fisiere[MAX_FISIERE];
    int n;

    printf("Introdu numarul de fisiere (max %d): ", MAX_FISIERE);
    scanf("%d", &n);
    getchar(); // Consumăm '\n' după scanf

    if (n < 1 || n > MAX_FISIERE)
    {
        printf("Numar invalid!\n");
        return 1;
    }

    // Citire fisiere
    for (int i = 0; i < n; i++)
    {
        unsigned int temp;

        printf("\n--- Fisierul %d ---\n", i + 1);

        printf("Nume: ");
        fgets(fisiere[i].nume, sizeof(fisiere[i].nume), stdin);
        fisiere[i].nume[strcspn(fisiere[i].nume, "\n")] = '\0';

        printf("Dimensiune (max 1024): ");
        scanf("%u", &temp);
        fisiere[i].dimensiune = temp;

        printf("Extensie (0=.txt, 1=.doc, 2=.xls): ");
        scanf("%u", &temp);
        fisiere[i].tip_extensie = temp;

        printf("Permisiune (0=normal, 1=read-only): ");
        scanf("%u", &temp);
        fisiere[i].permisiune = temp;

        getchar(); // Consumăm '\n'
    }

    // Scriere în fișier
    FILE *fout = fopen("memorie.txt", "w");
    if (!fout)
    {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "Fisierul %d:\n", i + 1);
        fprintf(fout, "Nume: %s\n", fisiere[i].nume);
        fprintf(fout, "Dimensiune: %u octeti\n", fisiere[i].dimensiune);

        fprintf(fout, "Extensie: ");
        switch (fisiere[i].tip_extensie)
        {
        case 0:
            fprintf(fout, ".txt\n");
            break;
        case 1:
            fprintf(fout, ".doc\n");
            break;
        case 2:
            fprintf(fout, ".xls\n");
            break;
        default:
            fprintf(fout, "necunoscuta\n");
        }

        fprintf(fout, "Permisiune: %s\n\n", fisiere[i].permisiune ? "read-only" : "normal");
    }

    fclose(fout);
    printf("\nDatele au fost salvate cu succes în memorie.txt!\n");

    return 0;
}

// Modificați problema de mai sus astfel încât vectorul de structuri să fie alocat dinamic
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FISIERE 10

// Structura cu bit fields
struct Fisier
{
    char nume[16];                 // max 15 caractere + '\0'
    unsigned int dimensiune : 10;  // max 1024
    unsigned int tip_extensie : 2; // 0 = .txt, 1 = .doc, 2 = .xls
    unsigned int permisiune : 1;   // 0 = normal, 1 = read-only
};

int main()
{
    int n;
    struct Fisier *fisiere;
    unsigned int temp;

    printf("Introdu numarul de fisiere (max %d): ", MAX_FISIERE);
    scanf("%d", &n);
    getchar(); // Consumam '\n'

    if (n < 1 || n > MAX_FISIERE)
    {
        printf("Numar invalid!\n");
        return 1;
    }

    // Alocare dinamica
    fisiere = (struct Fisier *)malloc(n * sizeof(struct Fisier));
    if (!fisiere)
    {
        perror("Eroare la alocarea memoriei");
        return 1;
    }

    // Citire fisiere
    for (int i = 0; i < n; i++)
    {
        printf("\n--- Fisierul %d ---\n", i + 1);

        printf("Nume: ");
        fgets(fisiere[i].nume, sizeof(fisiere[i].nume), stdin);
        fisiere[i].nume[strcspn(fisiere[i].nume, "\n")] = '\0';

        printf("Dimensiune (max 1024): ");
        scanf("%u", &temp);
        fisiere[i].dimensiune = temp;

        printf("Extensie (0=.txt, 1=.doc, 2=.xls): ");
        scanf("%u", &temp);
        fisiere[i].tip_extensie = temp;

        printf("Permisiune (0=normal, 1=read-only): ");
        scanf("%u", &temp);
        fisiere[i].permisiune = temp;

        getchar(); // Consumam '\n'
    }

    // Scriere in fisier
    FILE *fout = fopen("memorie.txt", "w");
    if (!fout)
    {
        perror("Eroare la deschiderea fisierului");
        free(fisiere);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "Fisierul %d:\n", i + 1);
        fprintf(fout, "Nume: %s\n", fisiere[i].nume);
        fprintf(fout, "Dimensiune: %u octeti\n", fisiere[i].dimensiune);

        fprintf(fout, "Extensie: ");
        switch (fisiere[i].tip_extensie)
        {
        case 0:
            fprintf(fout, ".txt\n");
            break;
        case 1:
            fprintf(fout, ".doc\n");
            break;
        case 2:
            fprintf(fout, ".xls\n");
            break;
        default:
            fprintf(fout, "necunoscuta\n");
        }

        fprintf(fout, "Permisiune: %s\n\n", fisiere[i].permisiune ? "read-only" : "normal");
    }

    fclose(fout);
    free(fisiere);

    printf("\nDatele au fost salvate cu succes în memorie.txt!\n");

    return 0;
}

// Folosind câmpuri pe biți, definiţi o structură pentru memorarea următoarelor informaţii despre
// animale:
// ● numărul de picioare: număr întreg, minim 0 (ex. şarpe), maxim 1000 (ex. miriapod)
// ● greutatea în kg: număr real
// ● periculos pentru om: da/nu
// ● abrevierea ştiinţifică a speciei: şir de maxim 8 caractere
// ● vârsta maximă în ani: număr întreg, minim 0, maxim 2000
// Unde este posibil, codificaţi informaţiile prin numere întregi de dimensiune cât mai mică, spre exemplu “da”=1,
// “nu”=0. Definiţi structura în aşa fel încât să ocupe spaţiul minim de memorie posibil. Afişaţi spaţiul de memorie
// ocupat, folosind operatorul sizeof. Folosind structura definită, citiţi de la tastatură informaţii despre un animal, iar
// pe urmă afişaţi-le pe ecran.
// Exemplu: valoare=147000, unitate:gram => 147 kilogram
#include <stdio.h>
#include <string.h>

struct Animal
{
    char abreviere[9]; // max 8 caractere + '\0'
    float greutate;    // nu putem pune float în bit-field

    unsigned int picioare : 10;   // max 1024
    unsigned int varsta_max : 11; // max 2048
    unsigned int periculos : 1;   // 0 = nu, 1 = da
};

int main()
{
    struct Animal a;
    unsigned int temp;

    printf("Abrevierea speciei (max 8 caractere): ");
    fgets(a.abreviere, sizeof(a.abreviere), stdin);
    a.abreviere[strcspn(a.abreviere, "\n")] = '\0';

    printf("Greutate (kg): ");
    scanf("%f", &a.greutate);

    printf("Numar de picioare (0-1000): ");
    scanf("%u", &temp);
    a.picioare = temp;

    printf("Varsta maxima (0-2000): ");
    scanf("%u", &temp);
    a.varsta_max = temp;

    printf("Periculos pentru om? (0 = Nu, 1 = Da): ");
    scanf("%u", &temp);
    a.periculos = temp;

    printf("\n=== INFORMATII ANIMAL ===\n");
    printf("Specie: %s\n", a.abreviere);
    printf("Greutate: %.2f kg\n", a.greutate);
    printf("Numar de picioare: %u\n", a.picioare);
    printf("Varsta maxima: %u ani\n", a.varsta_max);
    printf("Periculos pentru om: %s\n", a.periculos ? "Da" : "Nu");

    printf("\nStructura ocupa %zu bytes in memorie.\n", sizeof(a));

    return 0;
}

// Să se codifice următoarele informații despre un medicament, astfel încât ele să ocupe în total un
// singur octet. Să se scrie un program care să citească datele unui medicament și ulterior să le afișeze.
// ● gradul de periculozitate: scăzută, medie, mare
// ● dacă se eliberează doar pe bază de rețetă: da, nu
// ● vârsta minimă de administrare: 1...18 ani inclusiv
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    unsigned int varsta : 5;         // 5 biti pentru varsta (1-18)
    unsigned int reteta : 1;         // 1 bit pentru reteta (0-nu, 1-da)
    unsigned int periculozitate : 2; // 2 biti pentru periculozitate
} Medicament;

void afisare_medicament(Medicament m)
{
    printf("\nMedicament:\n");
    printf("Grad de periculozitate: ");
    switch (m.periculozitate)
    {
    case 0:
        printf("scazuta\n");
        break;
    case 1:
        printf("medie\n");
        break;
    case 2:
        printf("mare\n");
        break;
    }

    printf("Eliberare pe baza de reteta: %s\n",
           m.reteta ? "da" : "nu");
    printf("Varsta minima de administrare: %d ani\n",
           m.varsta);
}

int main()
{
    Medicament med;
    int temp_varsta, temp_reteta, temp_peric;

    // Citire date
    printf("Introduceti gradul de periculozitate (0-scazuta, 1-medie, 2-mare): ");
    scanf("%d", &temp_peric);
    printf("Eliberare doar pe baza de reteta? (0-nu, 1-da): ");
    scanf("%d", &temp_reteta);
    printf("Varsta minima de administrare (1-18): ");
    scanf("%d", &temp_varsta);

    // Validare si setare valori
    if (temp_peric < 0 || temp_peric > 2)
    {
        printf("Eroare: grad de periculozitate invalid!\n");
        return 1;
    }
    med.periculozitate = temp_peric;

    if (temp_reteta < 0 || temp_reteta > 1)
    {
        printf("Eroare: valoare reteta invalida!\n");
        return 1;
    }
    med.reteta = temp_reteta;

    if (temp_varsta < 1 || temp_varsta > 18)
    {
        printf("Eroare: varsta invalida!\n");
        return 1;
    }
    med.varsta = temp_varsta;

    unsigned char *octet = (unsigned char *)&med;
    printf("\nOctetul codificat: 0x%X\n", *octet);

    afisare_medicament(med);

    return 0;
}

// Se consideră că o măsurătoare are asociată unitatea de măsură (gram, metru, litru) și multiplicatorul
// acesteia (pico, nano, mili, centi, deci, deca, hecto, kilo, mega, giga).
// ● Să se codifice o măsurătoare astfel încât să conțină o valoare întreagă pozitivă care să acopere un interval
// cât mai mare de valori, unitatea de măsură și multiplicatorul acesteia. O măsurătoare va ocupa exact 2
// octeți.
// ● Să se citească o valoare unsigned și o unitate de măsură. La citire nu există multiplicator. Să se determine
// multiplicatorul astfel încât valoarea stocată să fie cât mai mică, fără a se pierde precizie, iar apoi să se
// stocheze într-o măsurătoare. Dacă valoarea nu încape, se va afișa o eroare. Să se afișeze toate câmpurile
// măsurătorii.

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

typedef enum
{
    GRAM,
    METRU,
    LITRU,
    UNITATE_INVALIDA
} UnitateMasura;

typedef enum
{
    PICO = -6,
    NANO = -3,
    MILI = -2,
    CENTI = -1,
    DECI = 0,
    DECA = 1,
    HECTO = 2,
    KILO = 3,
    MEGA = 6,
    GIGA = 9,
    MULTIPLICATOR_INVALID
} Multiplicator;

typedef struct
{
    uint16_t valoare : 12;
    uint16_t unitate : 2;
    uint16_t multiplicator : 2;
} Masuratoare;

UnitateMasura string_to_unitate(const char *unitate)
{
    if (strcmp(unitate, "gram") == 0)
        return GRAM;
    if (strcmp(unitate, "metru") == 0)
        return METRU;
    if (strcmp(unitate, "litru") == 0)
        return LITRU;
    return UNITATE_INVALIDA;
}

Multiplicator determina_multiplicator(double valoare)
{
    if (valoare == 0)
        return DECI;

    int exponent = (int)log10(valoare);

    if (exponent <= -6)
        return PICO;
    if (exponent <= -3)
        return NANO;
    if (exponent <= -2)
        return MILI;
    if (exponent <= -1)
        return CENTI;
    if (exponent <= 0)
        return DECI;
    if (exponent <= 1)
        return DECA;
    if (exponent <= 2)
        return HECTO;
    if (exponent <= 3)
        return KILO;
    if (exponent <= 6)
        return MEGA;
    return GIGA;
}

double aplica_multiplicator(double valoare, Multiplicator mult)
{
    return valoare / pow(10, mult);
}

void afiseaza_multiplicator(Multiplicator mult)
{
    switch (mult)
    {
    case PICO:
        printf("pico");
        break;
    case NANO:
        printf("nano");
        break;
    case MILI:
        printf("mili");
        break;
    case CENTI:
        printf("centi");
        break;
    case DECI:
        printf("deci");
        break;
    case DECA:
        printf("deca");
        break;
    case HECTO:
        printf("hecto");
        break;
    case KILO:
        printf("kilo");
        break;
    case MEGA:
        printf("mega");
        break;
    case GIGA:
        printf("giga");
        break;
    default:
        printf("invalid");
    }
}

void afiseaza_unitate(UnitateMasura unitate)
{
    switch (unitate)
    {
    case GRAM:
        printf("gram");
        break;
    case METRU:
        printf("metru");
        break;
    case LITRU:
        printf("litru");
        break;
    default:
        printf("invalid");
    }
}

int main()
{
    double valoare_input;
    char unitate_str[10];
    Masuratoare masuratoare;

    // Citire input
    printf("Introduceti valoarea: ");
    scanf("%lf", &valoare_input);
    printf("Introduceti unitatea de masura (gram/metru/litru): ");
    scanf("%s", unitate_str);

    // Validare unitate
    masuratoare.unitate = string_to_unitate(unitate_str);
    if (masuratoare.unitate == UNITATE_INVALIDA)
    {
        printf("Eroare: Unitate de masura invalida!\n");
        return 1;
    }

    // Determinare multiplicator optim
    Multiplicator mult = determina_multiplicator(valoare_input);
    double valoare_ajustata = aplica_multiplicator(valoare_input, mult);

    // Verificare daca valoarea incape in 12 biti
    if (valoare_ajustata < 0 || valoare_ajustata > 4095)
    {
        printf("Eroare: Valoarea nu poate fi reprezentata (depaseste 12 biti)!\n");
        return 1;
    }

    // Rotunjire si stocare
    masuratoare.valoare = (uint16_t)round(valoare_ajustata);
    masuratoare.multiplicator = mult;

    // Afisare rezultate
    printf("\nMasuratoare codificata (hex): 0x%04X\n", *(uint16_t *)&masuratoare);
    printf("Valoare: %d\n", masuratoare.valoare);
    printf("Unitate: ");
    afiseaza_unitate(masuratoare.unitate);
    printf("\nMultiplicator: ");
    afiseaza_multiplicator(masuratoare.multiplicator);
    printf("\n");

    // Reconstructie valoare originala
    double valoare_reconstruita = masuratoare.valoare * pow(10, masuratoare.multiplicator);
    printf("Valoare reconstruita: %.2f %s\n", valoare_reconstruita, unitate_str);

    return 0;
}