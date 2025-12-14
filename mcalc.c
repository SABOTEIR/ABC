#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void print_matrix(int a[MAX][MAX], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            printf("%6d", a[i][j]);
        printf("\n");
    }
}

int main()
{

    char tfile[10];
    char mt[15];
    printf("Nhap ten file ('Book1' hoac 'Book2'): ");
    fgets(tfile, sizeof(tfile), stdin);
    tfile[strcspn(tfile, "\n")] = 0;

    strcpy(mt, tfile);
    strcat(mt, ".csv");

    printf("Tên file: %s\n", mt);

    FILE *fp1 = fopen(mt, "r");
    if (!fp1)
    {
        printf("Cannot open file\n");
        return 1;
    }
    printf("Đọc từ file: Book1.csv\n");
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    char line[256];
    int mode = 0; // 1 = read A, 2 = read B

    while (fgets(line, sizeof(line), fp1))
    {
        // Xóa ký tự xuống dòng
        line[strcspn(line, "\r\n")] = 0;

        // Bỏ BOM nếu có
        if ((unsigned char)line[0] == 0xEF)
            memmove(line, line + 3, strlen(line + 3) + 1);

        if (strncmp(line, "matran1", 7) == 0)
        {
            mode = 1;
            continue;
        }

        else if (strncmp(line, "matran2", 7) == 0)
        {
            mode = 2;
            continue;
        }

        if (strchr(line, ','))
        {
            int col = 0;
            char *token = strtok(line, ",");

            if (mode == 1)
            {
                while (token)
                {
                    A[r1][col++] = atoi(token);
                    token = strtok(NULL, ",");
                }
                if (r1 == 0)
                    c1 = col;
                r1++;
            }
            else if (mode == 2)
            {
                while (token)
                {
                    B[r2][col++] = atoi(token);
                    token = strtok(NULL, ",");
                }
                if (r2 == 0)
                    c2 = col;
                r2++;
            }
        }
    }

    fclose(fp1);

    /* Cộng & Trừ */
    if (r1 != r2 || c1 != c2)
    {
        printf("Phép cộng & trừ: NULL\n");
    }
    else
    {
        printf("Phép cộng:\n");
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c1; j++)
                C[i][j] = A[i][j] + B[i][j];
        print_matrix(C, r1, c1);

        printf("\nPhép trừ:\n");
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c1; j++)
                C[i][j] = A[i][j] - B[i][j];
        print_matrix(C, r1, c1);
    }

    /* Nhân */
    if (c1 != r2)
    {
        printf("\nPhép nhân: NULL\n");
    }
    else
    {
        printf("\nPhép nhân:\n");
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c2; j++)
            {
                C[i][j] = 0;
                for (int k = 0; k < c1; k++)
                    C[i][j] += A[i][k] * B[k][j];
            }
        }
        print_matrix(C, r1, c2);
    }

    return 0;
}
