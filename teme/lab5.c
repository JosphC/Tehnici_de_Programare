// Scrieți un program care copiază conținutul unui fișier sursă într-un fișier destinație. Numele
// fișierelor se citesc din linia de comandă. Pentru eficiența copierii, programul va citi câte un bloc de maxim 4096
// de octeți, pe care îl va scrie în destinație.
// Exemplu: ./copiere src.dat dst.dat -> copiază src.dat în dst.dat

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    // Verificam numarul de argumente
    if (argc != 3)
    {
        fprintf(stderr, "Utilizare: %s src.dat dst.dat\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Deschidem fidierul sursa pentru citire
    FILE *src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        perror("Eroare la deschiderea fisierului sursa");
        return EXIT_FAILURE;
    }

    // Deschidem fisierul destinatie pentru scriere
    FILE *dst = fopen(argv[2], "wb");
    if (dst == NULL)
    {
        perror("Eroare la deschiderea fisierului destinasie");
        fclose(src);
        return EXIT_FAILURE;
    }

    // Alocam un buffer pentru citire/scriere
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Citim din sursa si scriem in destinatie
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0)
    {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dst);
        if (bytes_written != bytes_read)
        {
            perror("Eroare la scrierea in fisierul destinatie");
            fclose(src);
            fclose(dst);
            return EXIT_FAILURE;
        }
    }

    if (ferror(src))
    {
        perror("Eroare la citirea din fisierul sursa");
        fclose(src);
        fclose(dst);
        return EXIT_FAILURE;
    }

    fclose(src);
    fclose(dst);

    return EXIT_SUCCESS;
}

// Se citesc m și n de la tastatură, iar apoi o matrice a[m][n] cu elemente de tip întreg. Să se scrie
// matricea într-un fișier binar, prima oară scriindu-se m și n, iar apoi elementele, așa cum sunt dispuse ele în
// memorie. Să se citească matricea din fișier într-o variabilă b și să se afișeze.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;

    // Citirea dimensiunilor matricei
    printf("Introdu m și n: ");
    scanf("%d %d", &m, &n);

    // Alocare matrice a[m][n]
    int **a = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        a[i] = (int *)malloc(n * sizeof(int));
    }

    // Citirea elementelor matricei
    printf("Introdu elementele matricei:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    // Scrierea în fișier binar
    FILE *file = fopen("matrice.bin", "wb");
    if (file == NULL)
    {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    // Scriem m și n (dimensiunile)
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&n, sizeof(int), 1, file);

    // Scriem elementele (pe rând, linie cu linie)
    for (int i = 0; i < m; i++)
    {
        fwrite(a[i], sizeof(int), n, file);
    }

    fclose(file);

    // Eliberăm memoria lui a (deoarece o vom citi din nou în b)
    for (int i = 0; i < m; i++)
    {
        free(a[i]);
    }
    free(a);

    // Citirea din fișier în matricea b
    file = fopen("matrice.bin", "rb");
    if (file == NULL)
    {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    int m_b, n_b;
    fread(&m_b, sizeof(int), 1, file);
    fread(&n_b, sizeof(int), 1, file);

    // Alocare matrice b[m_b][n_b]
    int **b = (int **)malloc(m_b * sizeof(int *));
    for (int i = 0; i < m_b; i++)
    {
        b[i] = (int *)malloc(n_b * sizeof(int));
    }

    // Citim elementele in b
    for (int i = 0; i < m_b; i++)
    {
        fread(b[i], sizeof(int), n_b, file);
    }

    fclose(file);

    // Afișarea matricei b
    printf("Matricea citită din fișier:\n");
    for (int i = 0; i < m_b; i++)
    {
        for (int j = 0; j < n_b; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    // Eliberăm memoria lui b
    for (int i = 0; i < m_b; i++)
    {
        free(b[i]);
    }
    free(b);

    return 0;
}

// Să se modifice exemplul 4, astfel încât la începutul fișierului să fie scris numărul de produse.
// Citirea va fi modificată pentru a folosi această informație, în loc de a se testa sfârșitul de fișier.

// Din exemplul 4 din laborator
// void scriere()
// {
//     FILE *fis;
//     if ((fis = fopen("produse.dat", "wb")) == NULL)
//     {
//         printf("Eroare la deschiderea fisierului\n");
//         return;
//     }

//     // Scriem numărul de produse la începutul fișierului
//     fwrite(&nProduse, sizeof(unsigned int), 1, fis);

//     for (unsigned int i = 0; i < nProduse; i++)
//     {
//         unsigned short nNume = strlen(produse[i].nume);
//         fwrite(&nNume, sizeof(unsigned short), 1, fis);
//         fwrite(produse[i].nume, sizeof(char), nNume, fis);
//         fwrite(&produse[i].pret, sizeof(float), 1, fis);
//     }

//     fclose(fis);
// }

// void citire()
// {
//     FILE *fis;
//     if ((fis = fopen("produse.dat", "rb")) == NULL)
//         return;

//     // Citim numărul de produse de la începutul fișierului
//     unsigned int nrProduse;
//     if (fread(&nrProduse, sizeof(unsigned int), 1, fis) != 1)
//     {
//         fclose(fis);
//         return;
//     }

//     for (unsigned int i = 0; i < nrProduse; i++)
//     {
//         unsigned short nNume;
//         if (fread(&nNume, sizeof(unsigned short), 1, fis) != 1)
//             break;

//         char *pNume = (char *)malloc((nNume + 1) * sizeof(char));
//         if (pNume == NULL)
//         {
//             printf("Memorie insuficienta\n");
//             fclose(fis);
//             eliberare();
//             exit(EXIT_FAILURE);
//         }

//         if (fread(pNume, sizeof(char), nNume, fis) != nNume)
//         {
//             free(pNume);
//             break;
//         }

//         pNume[nNume] = '\0';
//         produse[nProduse].nume = pNume;

//         if (fread(&produse[nProduse].pret, sizeof(float), 1, fis) != 1)
//         {
//             free(pNume);
//             break;
//         }

//         nProduse++;
//     }

//     fclose(fis);
// }

// Să se scrie un program similar cu hexdump, care primește un nume de fișier în linia de comandă,
// citește câte 16 octeți din el și îi afișează pe câte o linie. Fiecare linie începe cu offsetul ei în fișier, afișat în
// hexazecimal pe 8 cifre cu 0 în față, după care valorile hexa ale celor 16 octeți pe câte 2 cifre și în final
// caracterele. Dacă codul unui caracter este în intervalul 32-255 se va afișa ca atare, altfel se va afișa un punct în
// locul său. Dacă ultima linie este incompletă, se va completa cu octeți de 0.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 16

void hexdump(FILE *file)
{
    unsigned char buffer[BUFFER_SIZE];
    unsigned long offset = 0;
    size_t bytes_read;
    int i;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        // Afiseaza offset-ul in hexazecimal pe 8 cifre cu leading zeros
        printf("%08lx  ", offset);

        // Afiseaza hexdump-ul pentru cei 16 octeti
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (i < bytes_read)
            {
                printf("%02x ", buffer[i]);
            }
            else
            {
                printf("   ");
            }

            if (i == 7)
            {
                printf(" ");
            }
        }

        printf(" |");

        // Afiseaza caracterele vizibile
        for (i = 0; i < bytes_read; i++)
        {
            if (isprint(buffer[i]) && buffer[i] < 128)
            {
                putchar(buffer[i]);
            }
            else
            {
                putchar('.');
            }
        }

        // Completeaza cu spatii daca linia este incompleta
        for (; i < BUFFER_SIZE; i++)
        {
            putchar(' ');
        }

        printf("|\n");

        offset += bytes_read;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Utilizare: %s <nume_fisier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        perror("Eroare la deschiderea fisierului");
        return EXIT_FAILURE;
    }

    hexdump(file);

    fclose(file);
    return EXIT_SUCCESS;
}

// Să se scrie un program care primește 2 fișiere în linia de comandă și le compară între ele. Pentru
// fiecare octet diferit găsit, se afișează offsetul acestuia și valorile sale din fiecare fișier, în hexazecimal, pe câte 2
// cifre. Dacă fișierele sunt de dimensiuni diferite, în final se vor afișa toți octeții din fișierul mai mare. Dacă fișierele
// sunt identice, programul nu va afișa nimic.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Utilizare: %s <fisier1> <fisier2>\n", argv[0]);
        return 1;
    }

    FILE *f1 = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "rb");

    if (!f1 || !f2)
    {
        perror("Eroare la deschiderea fisierelor");
        if (f1)
            fclose(f1);
        if (f2)
            fclose(f2);
        return 1;
    }

    int different = 0;
    long offset = 0;
    unsigned char byte1, byte2;
    size_t read1, read2;

    do
    {
        read1 = fread(&byte1, 1, 1, f1);
        read2 = fread(&byte2, 1, 1, f2);

        if (read1 != read2)
        {
            // Un fișier s-a terminat mai devreme
            different = 1;
            FILE *longer = read1 ? f1 : f2;
            unsigned char *byte = read1 ? &byte1 : &byte2;

            do
            {
                printf("%08lx: %02x vs --\n", offset, *byte);
                offset++;
            } while (fread(byte, 1, 1, longer));

            break;
        }

        if (read1 && byte1 != byte2)
        {
            printf("%08lx: %02x vs %02x\n", offset, byte1, byte2);
            different = 1;
        }

        offset++;
    } while (read1 && read2);

    fclose(f1);
    fclose(f2);

    return different ? 0 : 2;
}

// Un program primește în linia de comandă un nume de fișier, un offset dat în hexazecimal și apoi o
// serie de octeți, specificați tot în hexazecimal. Programul va scrie în fișierul specificat, începând de la offsetul dat
// toți octeții primiți în linia de comandă. Restul fișierului va rămâne nemodificat.
// Exemplu: ./inlocuire 1.dat 4a0f 9e b0 51 -> scrie octeții {9e, b0, 51} în fișierul 1.dat, începând cu poziția 4a0f

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    if (argc < 4)
    {
        fprintf(stderr, "Utilizare: %s <fisier> <offset_hex> <octeti_hex...>\n", argv[0]);
        return 1;
    }

    // Deschidere fișier în mod binar pentru citire/scriere
    FILE *file = fopen(argv[1], "r+b");
    if (!file)
    {
        fprintf(stderr, "Eroare la deschiderea fisierului: %s\n", strerror(errno));
        return 1;
    }

    // Convertire offset din hexazecimal
    char *endptr;
    long offset = strtol(argv[2], &endptr, 16);
    if (*endptr != '\0' || offset < 0)
    {
        fprintf(stderr, "Offset invalid: %s\n", argv[2]);
        fclose(file);
        return 1;
    }

    // Mutare la offset
    if (fseek(file, offset, SEEK_SET) != 0)
    {
        fprintf(stderr, "Eroare la pozitionare in fisier: %s\n", strerror(errno));
        fclose(file);
        return 1;
    }

    // Procesare octeti
    for (int i = 3; i < argc; i++)
    {
        // Verificare daca sirul este hexazecimal valid
        if (strlen(argv[i]) > 2 || !isxdigit(argv[i][0]) ||
            (argv[i][1] && !isxdigit(argv[i][1])))
        {
            fprintf(stderr, "Octet invalid: %s\n", argv[i]);
            fclose(file);
            return 1;
        }

        // Convertire octet din hexazecimal
        unsigned char byte = (unsigned char)strtol(argv[i], NULL, 16);

        // Scriere octet in fisier
        if (fwrite(&byte, 1, 1, file) != 1)
        {
            fprintf(stderr, "Eroare la scriere in fisier: %s\n", strerror(errno));
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    printf("Operatie realizata cu succes.\n");
    return 0;
}

// Să se scrie un program care primește în linia de comandă un nume de fișier și o serie de octeți,
// dați în hexazecimal. Programul va afișa toate pozițiile din fișier la care se află secvența de octeți specificați.
// Exemplu: ./cautare 1.dat 01 aa b2 45 -> caută în fișierul 1.dat secvența {01, aa, b2, 45} și afișează toate
// pozițiile la care o găsește

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Utilizare: %s <fisier> <octet1> <octet2> ...\n", argv[0]);
        return 1;
    }

    // Convertim argumentele in octeti
    int seq_len = argc - 2;
    unsigned char *sequence = malloc(seq_len);
    if (!sequence)
    {
        perror("Eroare la alocarea memoriei");
        return 1;
    }

    // Validare si conversie octeti
    for (int i = 0; i < seq_len; i++)
    {
        char *arg = argv[i + 2];
        size_t arg_len = strlen(arg);

        if (arg_len == 0 || arg_len > 2 ||
            !isxdigit(arg[0]) || (arg_len == 2 && !isxdigit(arg[1])))
        {
            fprintf(stderr, "Octet invalid: %s\n", arg);
            free(sequence);
            return 1;
        }

        sequence[i] = (unsigned char)strtol(arg, NULL, 16);
    }

    // Deschidere fisier
    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        perror("Eroare la deschiderea fisierului");
        free(sequence);
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];
    long current_pos = 0;
    int match_index = 0;
    size_t bytes_read;

    printf("Cautare secventa: ");
    for (int i = 0; i < seq_len; i++)
    {
        printf("%02x ", sequence[i]);
    }
    printf("\n");

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        for (size_t i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == sequence[match_index])
            {
                match_index++;
                if (match_index == seq_len)
                {
                    printf("Gasit la pozitia: 0x%08lx\n", current_pos + i - seq_len + 1);
                    match_index = 0;
                    // Repornim cautarea de la urmatorul byte
                    if (fseek(file, current_pos + i - seq_len + 2, SEEK_SET) != 0)
                    {
                        perror("Eroare la repozitionare");
                        fclose(file);
                        free(sequence);
                        return 1;
                    }
                    current_pos = current_pos + i - seq_len + 2;
                    break; // Iesim din bucla pentru a citi noul bloc
                }
            }
            else
            {
                // Daca nu se potriveste, resetam indexul
                if (match_index > 0)
                {
                    i--; // Revenim la pozitia anterioara pentru a verifica din nou
                }
                match_index = 0;
            }
        }
        current_pos += bytes_read;
    }

    // Curatare resurse
    fclose(file);
    free(sequence);
    return 0;
}

// Să se scrie un program care primește o serie de n programe în linia de comandă și le
// concatenează pe primele n-1 într-un nou fișier având numele specificat pe ultima poziție din linia de comandă.
// Exemplu: ./concat 1.dat 2.dat 3.dat rez.dat -> concatenează conținutul fișierelor {1.dat, 2.dat, 3.dat} într-un
// nou fișier, denumit rez.dat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Utilizare: %s <fisier1> <fisier2> ... <fisier_destinatie>\n", argv[0]);
        return 1;
    }

    const char *output_filename = argv[argc - 1];
    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file)
    {
        perror("Eroare la deschiderea fisierului de iesire");
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];
    int success = 1;

    for (int i = 1; i < argc - 1; i++)
    {
        FILE *input_file = fopen(argv[i], "rb");
        if (!input_file)
        {
            fprintf(stderr, "Eroare la deschiderea fisierului de intrare %s: %s\n",
                    argv[i], strerror(errno));
            success = 0;
            continue;
        }

        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file)) > 0)
        {
            if (fwrite(buffer, 1, bytes_read, output_file) != bytes_read)
            {
                perror("Eroare la scrierea in fisierul de iesire");
                success = 0;
                break;
            }
        }

        if (ferror(input_file))
        {
            fprintf(stderr, "Eroare la citirea fisierului %s\n", argv[i]);
            success = 0;
        }

        fclose(input_file);
        if (!success)
            break;
    }

    if (fclose(output_file) != 0)
    {
        perror("Eroare la inchiderea fisierului de iesire");
        success = 0;
    }

    if (success)
    {
        printf("Concatenare realizata cu succes in fisierul %s\n", output_filename);
        return 0;
    }
    else
    {
        fprintf(stderr, "Concatenarea a esuat\n");
        remove(output_filename);
        return 1;
    }
}