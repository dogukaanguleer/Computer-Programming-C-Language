#include <stdio.h>
#define ROWS 512
#define COLUMNS 512
#define MAX_ISLAND_NUMBER 100

struct cell
{
    char cellID;
    char isIsland;
};

void find_island(struct cell (*array)[COLUMNS], int row, int column, int water_level)
{

    if (array[row][column].cellID == 'L' && array[row][column].isIsland != 'X') /* if current cell is not belong any island and the cell is land */
    {
        array[row][column].isIsland = 'X'; /*it was marked as an island.  X means it is island.*/
        if (column != COLUMNS - 1)         /* checks if it is on the boundary */
            find_island(array, row, column + 1, water_level);
        if (row != ROWS - 1)               /* checks if it is on the boundary */
            find_island(array, row + 1, column, water_level);
        if (column != 0)                   /* checks if it is on the boundary */
            find_island(array, row, column - 1, water_level);
        if (row != 0)                      /* checks if it is on the boundary */
            find_island(array, row - 1, column, water_level);
    }
}

int main()
{
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int island_number = 0, cellValue, water_level, coordinates[MAX_ISLAND_NUMBER][2];
    struct cell array[ROWS][COLUMNS];

    if (input == NULL) /* if file is not exist.*/
        return 0;

    fscanf(input, "%d", &water_level);

    for (int rowIndex = 0; rowIndex < ROWS; rowIndex++)
        for (int columnIndex = 0; columnIndex < COLUMNS; columnIndex++)
        {
            fscanf(input, "%d", &cellValue);

            if (cellValue > water_level)                   /* Each cell will be marked according it is water or land */
                array[rowIndex][columnIndex].cellID = 'L'; /* it marks cell as Land*/
            else
                array[rowIndex][columnIndex].cellID = 'W'; /* it marks cell as Water*/
        }

    for (int rowIndex = 0; rowIndex < ROWS; rowIndex++)
        for (int columnIndex = 0; columnIndex < COLUMNS; columnIndex++)
            if (array[rowIndex][columnIndex].isIsland != 'X' && array[rowIndex][columnIndex].cellID == 'L') /* if current cell is not belong any island and the cell is land*/
            {
                coordinates[island_number][0] = rowIndex;    /* row index of first point of island */
                coordinates[island_number][1] = columnIndex; /* column index of first point of island */
                island_number++; 
                find_island(array, rowIndex, columnIndex, water_level); 
            }

    fprintf(output, "%d\n", island_number);
    for (int a = 0; a < island_number; a++) /* prints every island's first coordinates*/
        fprintf(output, "%d,%d\n", coordinates[a][0], coordinates[a][1]);

    fclose(input);
    fclose(output);
    return (0);
}