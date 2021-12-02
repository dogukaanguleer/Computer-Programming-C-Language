#include <stdio.h>
#include <string.h>
#define lengthOfinput1 11
#define row 100
#define rowsLength 251

void find_location(char array1[][lengthOfinput1], char array2[][rowsLength], int isHorizontal, int numberOfLine, int lengthOfLine, FILE *output)
{

    int matchCount = 0, lengthOfInp1 = strlen(array1[0]), repetition;
    for (int j = 0; j < numberOfLine; j++)
    {
        for (int k = 0; k < lengthOfLine; k++)
        {
            repetition = k;                        /* assing k */
            for (int i = 0; i < lengthOfInp1; i++) /* for every k checks by the length of the input1  */
            {
                if (array1[0][i] == array2[j][repetition])
                {
                    matchCount++;
                }
                repetition++;                   /*Repats the lenght of input1*/
                if (matchCount == lengthOfInp1) /* if match count and length of input are equal it will print*/
                {
                    if (isHorizontal == 1)
                        fprintf(output, "%s (%d,%d) Horizontal\n", array1[0], (j + 1), (k + 1));

                    else if (isHorizontal == 0)
                        fprintf(output, "%s (%d,%d) Vertical\n", array1[0], (k + 1), (j + 1));
                }
            }
            matchCount = 0; /*assings 0 for every line */
        }
    }
}

int main(void)
{
    FILE *input1, *input2, *output;
    output = fopen("output.txt", "w");
    input1 = fopen("input1.txt", "r");
    input2 = fopen("input2.txt", "r");
    char array1[1][lengthOfinput1], array2[row][rowsLength]; /* array1 contains input1's data and array2 contains input2's data */
    int input1_status, input2_status, i = 1, max;
    /* Read input2's data from file */
    input2_status = fscanf(input2, "%s", array2[0]);
    while (input2_status != EOF)
    {
        input2_status = fscanf(input2, "%s", array2[i]);
        i++; /* Number of lines in input2 file */
    }
    /* Finds max length of lines */
    max = strlen(array2[0]);
    for (int x = 1; x < (i - 1); x++)
    {
        if (max < strlen(array2[x]))
            max = strlen(array2[x]);
    }
    /* Place spaceses each line until the line lenght is max length */
    for (int x = 0; x < (i - 1); x++)
    {
        for (int y = 0; y < max; y++)
        {
            if (!array2[x][y])
                array2[x][y] = ' ';
        }
    }
    /* Read vertical coloumns and it transforms horizontal version. */
    char reverse_array[rowsLength][rowsLength];
    for (int x = 0; x < max; x++)
    {
        for (int y = 0; y < (i - 1); y++)
            reverse_array[x][y] = array2[y][x];
    }
    /* Read input1 from file and send to function for each line.*/
    input1_status = fscanf(input1, "%s", array1[0]);
    while (input1_status != EOF)
    {
        find_location(array1, array2, 1, (i - 1), max, output);        /*Horizontal search*/
        find_location(array1, reverse_array, 0, max, (i - 1), output); /*Vertical search*/
        input1_status = fscanf(input1, "%s", array1[0]);
    }
}
