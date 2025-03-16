// /* Se citește de la tastatură un număr n<=10 și un număr m<=20. Se cere să se scrie un program care
// generează o matrice cu m linii și n coloane în care sunt puse toate numerele de la 1,2,3,...,m*n. Se vor utiliza
// pointeri.*/

#include <stdio.h>
#include <stdlib.h>

void generateMatrix(int *matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {

            *(matrix + i * n + j) = i * n + j + 1;
        }
    }
}

void printMatrix(int *matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(matrix + i * n + j));
        }
        printf("\n");
    }
}

int main(void)
{

    int n, m;
    printf("Introduceti numarul de linii (m<=20): ");
    scanf("%d", &m);

    printf("Introduceti numarul de coloane (n<=10): ");
    scanf("%d", &n);

    if (m > 20 || n > 10 || m <= 0 || n <= 0)
    {
        printf("Dimensiuni invalide\n");
        return 1;
    }
    int *matrix = (int *)malloc(m * n * sizeof(int));
    if (matrix == NULL)
    {
        printf("Nu s-a putut aloca memorie\n");
        return 1;
    }

    generateMatrix(matrix, m, n);
    printMatrix(matrix, m, n);
    free(matrix);

    return 0;
}

/////////////////////////////////////////////////

/*Se citește de la tastatură o matrice pătratică cu n<=50 linii și coloane. Să se interschimbe elementele
de deasupra diagonalei principale, considerată ca axă de simetrie, cu elementele de sub diagonala principală,
elementele de pe diagonala principală rămânând la fel.*/
#include <stdio.h>

#define MAX_N 50

void swapMatrix(int matrix[MAX_N][MAX_N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void printMatrix(int matrix[MAX_N][MAX_N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    int matrix[MAX_N][MAX_N];

    printf("Introduceti dimensiunea matricei (n <= 50): ");
    scanf("%d", &n);

    if (n > MAX_N || n <= 0)
    {
        printf("Dimensiune invalida!\n");
        return 1;
    }

    printf("Introduceti elementele matricei:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    swapMatrix(matrix, n);

    printf("Matricea transformata:\n");
    printMatrix(matrix, n);

    return 0;
}

/////////////////////////////////////////////////
/*: Se citește de la tastatură o matrice cu n<=20 linii și coloane. Să se memoreze într-un vector suma
tuturor elementelor de pe fiecare linie și într-un alt vector, suma tuturor elementelor de pe fiecare coloană. Să se
afișeze cei doi vectori. Se vor utiliza pointeri atât pentru vectori cât și pentru matrici.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

void computeSums(int *matrix, int *rowSums, int *colSums, int n)
{
    // Initializare vectori de sume cu 0
    for (int i = 0; i < n; i++)
    {
        *(rowSums + i) = 0;
        *(colSums + i) = 0;
    }

    // Calculul sumelor
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(rowSums + i) += *(matrix + i * n + j);
            *(colSums + j) += *(matrix + i * n + j);
        }
    }
}

void printArray(int *arr, int n, const char *msg)
{
    printf("%s:", msg);
    for (int i = 0; i < n; i++)
    {
        printf(" %d", *(arr + i));
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Introduceti dimensiunea matricei (n <= 20): ");
    scanf("%d", &n);

    if (n > MAX_N || n <= 0)
    {
        printf("Dimensiune invalida!\n");
        return 1;
    }

    int *matrix = (int *)malloc(n * n * sizeof(int));
    int *rowSums = (int *)malloc(n * sizeof(int));
    int *colSums = (int *)malloc(n * sizeof(int));

    if (!matrix || !rowSums || !colSums)
    {
        printf("Eroare la alocarea memoriei!\n");
        return 1;
    }

    printf("Introduceti elementele matricei:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (matrix + i * n + j));
        }
    }

    computeSums(matrix, rowSums, colSums, n);

    printArray(rowSums, n, "Sumele liniilor");
    printArray(colSums, n, "Sumele coloanelor");

    free(matrix);
    free(rowSums);
    free(colSums);

    return 0;
}

/////////////////////////////////////////////////

/* Se citește un număr n<=10 de persoane, fiecare persoană fiind identificată printr-un număr între
0..n-1. O persoană poate fi prietenă cu oricare alte persoane. După ce s-a citit n, se vor citi pentru fiecare persoană
prietenii ei pe rând. Să se afișeze pentru fiecare persoană câți prieteni are.*/

#include <stdio.h>

#define MAX_N 10

void countFriends(int friends[MAX_N][MAX_N], int n)
{
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (friends[i][j] == 1)
            {
                count++;
            }
        }
        printf("Persoana %d are %d prieteni.\n", i, count);
    }
}

int main()
{
    int n;
    int friends[MAX_N][MAX_N] = {0};

    printf("Introduceti numarul de persoane (n <= 10): ");
    scanf("%d", &n);

    if (n > MAX_N || n <= 0)
    {
        printf("Dimensiune invalida!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Introduceti prietenii pentru persoana %d (introduceti -1 pentru a termina): ", i);
        int friend_id;
        while (1)
        {
            scanf("%d", &friend_id);
            if (friend_id == -1)
                break;
            if (friend_id >= 0 && friend_id < n)
            {
                friends[i][friend_id] = 1;
            }
        }
    }

    countFriends(friends, n);

    return 0;
}

/////////////////////////////////////////////////

/*Se citesc numerele m,n,p fiecare mai mici decat 10, apoi se citesc matricile a[m][n] și b[n][p]. Se
cere să se calculeze matricea „c” care rezultă din înmulțirea matricilor a cu b și să se afișeze*/

#include <stdio.h>

#define MAX_SIZE 10

void multiplyMatrices(int a[MAX_SIZE][MAX_SIZE], int b[MAX_SIZE][MAX_SIZE], int c[MAX_SIZE][MAX_SIZE], int m, int n, int p)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void readMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols, const char *name)
{
    printf("Introduceti elementele matricii %s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols, const char *name)
{
    printf("Matricea %s:\n", name);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int m, n, p;
    int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], c[MAX_SIZE][MAX_SIZE];

    printf("Introduceti dimensiunile matricilor (m, n, p < 10): ");
    scanf("%d %d %d", &m, &n, &p);

    if (m >= MAX_SIZE || n >= MAX_SIZE || p >= MAX_SIZE || m <= 0 || n <= 0 || p <= 0)
    {
        printf("Dimensiuni invalide!\n");
        return 1;
    }

    readMatrix(a, m, n, "A");
    readMatrix(b, n, p, "B");

    multiplyMatrices(a, b, c, m, n, p);

    printMatrix(c, m, p, "C");

    return 0;
}

/////////////////////////////////////////////////////////

/*Se citește un număr n<=10. Se cere să se inițializeze o matrice a[n][n] cu 1 pe diagonale și cu 0 în
rest. Să se afișeze matricea.*/

#include <stdio.h>

int main(void)
{

    int n;
    printf("Introduceti dimensiunea matricei (n <= 10): ");
    scanf("%d", &n);

    if (n > 10 || n <= 0)
    {
        printf("Dimensiune invalida!\n");
        return 1;
    }

    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        a[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j || i + j == n - 1)
            {
                a[i][j] = 1;
            }
            else
            {
                a[i][j] = 0;
            }
        }
    }

    printf("Matricea rezultata:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    // Eliberarea memoriei
    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);

    return 0;
}

/////////////////////////////////////////////////////////

/*Se citește un număr n<=10 de produse și pentru fiecare produs vânzările lui trimestriale pe un an
(4 valori). Se cere să se afișeze care produse au înregistrat o creștere continuă a vânzărilor în decurs de un an.*/

#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n;
    printf("introduceti numarul de produse (max 10):");
    scanf("%d", &n);

    if (n > 10 || n <= 1)
    {
        printf("Numar invalid\n");
        return 1;
    }

    int **vanzari = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        vanzari[i] = (int *)malloc(4 * sizeof(int));
    }

    char **numeProduse = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        numeProduse[i] = (char *)malloc(50 * sizeof(char));
    }

    for (int i = 0; i < n; i++)
    {
        printf("Introduceti numele produsului %d:", i + 1);
        scanf("%s", numeProduse[i]);

        printf("Introduceti vanzarile trimestriale pentru produsul %s:", numeProduse[i]);
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &vanzari[i][j]);
        }
    }

    printf("\nProdusele cu crestere continua a vanzarilor sunt:\n");
    int found = 0;

    for (int i = 0; i < n; i++)
    {
        if (vanzari[i][0] < vanzari[i][1] &&
            vanzari[i][1] < vanzari[i][2] &&
            vanzari[i][2] < vanzari[i][3])
        {
            printf("- %s\n", numeProduse[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Niciun produs nu are crestere continua a vanzarilor.\n");
    }

    // Eliberarea memoriei
    for (int i = 0; i < n; i++)
    {
        free(vanzari[i]);
        free(numeProduse[i]);
    }
    free(vanzari);
    free(numeProduse);

    return 0;
}

/////////////////////////////////////////////////////////

/*Se citesc de la tastatură două numere n și m, n>=m. Pe urmă se citesc două matrici pătratice de
dimensiuni n, respectiv m, conținând numere întregi. Afișați toate pozitiile unde a doua matrice apare în prima
matrice. Afișarea se va face pe ecran sub forma unor perechi de forma (linie, coloană). Dacă a doua matrice nu
apare în prima matrice, se va afișa textul “Nu apare”.
Spre exemplu dacă se introduce:
5 3
1 0 1 1 1
0 1 0 1 1
1 0 1 1 1
0 1 0 1 1
1 0 1 1 1

0 1 1
1 0 1
0 1 1
se va afișa pe ecran:
(0,1) (2,1) */
#include <stdio.h>

#define MAX 100

void afisareMatrice(int mat[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int verificaSubmatrice(int mat1[MAX][MAX], int mat2[MAX][MAX], int n, int m, int startI, int startJ)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat1[startI + i][startJ + j] != mat2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{

    // am folosit valori hardcodate pentru a testa programul
    int n = 5, m = 3;
    int mat1[MAX][MAX] = {
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 1, 1}};

    int mat2[MAX][MAX] = {
        {0, 1, 1},
        {1, 0, 1},
        {0, 1, 1}};

    int found = 0;

    for (int i = 0; i <= n - m; i++)
    {
        for (int j = 0; j <= n - m; j++)
        {
            if (verificaSubmatrice(mat1, mat2, n, m, i, j))
            {
                printf("(%d,%d) ", i, j);
                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("Nu apare");
    }

    return 0;
}

////////////////////////////////////////////////////////
/*Se citesc de la tastatură un număr n și o matrice pătratică de dimensiune n conținând litere din
alfabet. Pe urmă se citește de la tastatură un cuvânt. Verificați dacă respectivul cuvânt se poate construi
parcurgând literele matricii pe verticală în sus sau în jos sau pe orizontală spre stânga sau spre dreapta. Afișați
toate pozițiile de unde trebuie începută parcurgerea, precum și sensul de parcurgere necesar pentru a construi
cuvântul.
Spre exemplu, dacă de la tastatură se introduce:
5
e r e m a
h e r e b
b m e r e
b a m e r
a e m r e
mere
pe ecran se va afișa:
De la linia 0 coloana 3 spre stânga.
De la linia 0 coloana 3 în jos.
De la linia 2 coloana 1 spre dreapta.
De la linia 3 coloana 2 în sus.*/

#include <stdio.h>
#include <string.h>
#define MAX_N 100

char matrix[MAX_N][MAX_N];
int n;
char word[MAX_N];

void checkWord(int row, int col, int drow, int dcol, char *direction)
{
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int r = row + i * drow;
        int c = col + i * dcol;
        if (r < 0 || r >= n || c < 0 || c >= n || matrix[r][c] != word[i])
        {
            return;
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf(" %c", &matrix[i][j]);
        }
    }
    scanf("%s", word);

    int found = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == word[0])
            {
            }
        }
    }

    return 0;
}