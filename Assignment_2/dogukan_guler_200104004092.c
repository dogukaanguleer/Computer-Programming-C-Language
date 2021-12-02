#include <stdio.h>
#define p1 0.5
#define p2 20
int main(void)
{
    FILE *inp, *output;
    inp = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    double n, a = 0, b = 0, sum, input_status;
    int i = 0, j = 1;

    input_status = fscanf(inp, "%lf", &n); /* Reads first input from input file. */
    while (input_status != EOF)            /* It checks the file is empty or not. */
    {
        sum = a * (j - 1); /* It gives sum of the numbers which calculated average. */
        b = (sum + n) / j; /* New average. */

        if (!(b > a * (1 + p1) || b < a * (1 - p1) || a > n * p2 || a < n / p2)) /* Condition of adding chunk. */
        {
            a = b; /* New average a becomes old b for chunk. */
            j++;   /* Number of elements in chunk. */
            fprintf(output, "%.4f ", n);
        }
        else
        {
            if (a != 0) /* If chunk has element.*/
                fprintf(output, "average: %.4f\n", sum / (j - 1));

            fprintf(output, "%.4f ", n);
            a = n;  /* New chunk has only n */
            b = n;
            j = 2;
        }

        input_status = fscanf(inp, "%lf", &n); /* Reads remaining inputs from input file.*/
    }
    if (b != 0)
        fprintf(output, "average: %.4f\n", b); /* For the last chunk it prints average.*/

    fclose(inp);
    fclose(output);
    return (0);
}
