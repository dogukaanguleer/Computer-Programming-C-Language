#include <stdio.h>
#include <string.h>
#include <math.h>
#define lenghtOfPolynom 1000

void summation(double *sum, int sign, double value, char polynom[][lenghtOfPolynom]) /*Funtction adds each of seperated polyom's values to sum.*/
{
    if (sign == -1 || polynom[0][sign] == '+') /* -1 means is for first seperarted polynoms.*/
        *sum = *sum + value;
    else if (polynom[0][sign] == '-')
        *sum = *sum - value;
}
void evaluate(char seperated[][lenghtOfPolynom], int lenght, int sign, char polynom[][lenghtOfPolynom], double *sum, double value)
{
    double power, result, coefficient, constant;
    char print_array[2][lenghtOfPolynom] = {' '}; /* Clear print_ array at each call of function */
    int q = 0;
    for (int i = 0; i < lenght; i++)
    {
        if (seperated[0][i] == 'x' && i == 0 && i == (lenght - 1)) /*if seperated array doesnt have coefficent and power */
        {
            summation(sum, sign, value, polynom); /* calls the function to sum*/
            q++;
        }
        else if (seperated[0][i] == 'x' && i != (lenght - 1) && seperated[0][i + 1] == '^') /*if seperated array contaions power*/
        {
            if (i != 0) /* if seperated array contains coefficent */
            {
                for (int a = 0; a < i; a++)
                    print_array[1][a] = seperated[0][a];
                sscanf(print_array[1], "%lf", &coefficient); /* assing coefficent value to double*/
            }
            else /* if seperated array doesnt contain coefficent*/
                coefficient = 1;
            for (; i + 2 < lenght; i++)
            {
                print_array[0][q] = seperated[0][i + 2];
                q++;
            }
            sscanf(print_array[0], "%lf", &power);                 /* assing power value to double */
            result = pow(value, power);                            /* calculate result*/
            summation(sum, sign, (result * coefficient), polynom); /* calls the function to sum*/
        }
        else if (seperated[0][i] == 'x' && i == (lenght - 1) && i != 0) /*if seperated array contains only coeficent*/
        {
            for (int a = 0; a < i; a++)
                print_array[0][a] = seperated[0][a];
            sscanf(print_array[0], "%lf", &coefficient); /*assing coefficent value to double*/
            summation(sum, sign, (value * coefficient), polynom);
            q++;
        }
        else if (seperated[0][i] != 'x' && i == (lenght - 1) && q == 0)
        {
            for (int a = 0; a < lenght; a++)
                print_array[0][a] = seperated[0][a];
            sscanf(print_array[0], "%lf", &constant);
            summation(sum, sign, constant, polynom);
        }
    }
}

void separator(char polynom_array[][lenghtOfPolynom], int lenght, double value, FILE *evaluations) /* Function splits polynomial array according to delimiters*/
{
    int j = 1, indexOfSign, indexOfSeperated = 0, isEndOfPolynom = 0, c,flag=0;
    double sum = 0;
    char seperated_polynom[2][lenghtOfPolynom];

    if (polynom_array[0][0] == '-') /* check first character is mines */
        j = 1;
    for (; j < lenght; j++) /* loop for first delimeter*/
    {
        if (polynom_array[0][j] == '+' || polynom_array[0][j] == '-') /* if found sign ,then it assign values to seperated polynom*/
        {   flag=1;
            for (int i = 0; i < j; i++)
                seperated_polynom[0][i] = polynom_array[0][i];
            evaluate(seperated_polynom, j, -1, polynom_array, &sum, value); /* calls the function to determine calculation of sum for seperated polynom  */
            break;
        }
        if(j==(lenght-1) && flag==0 ){ /* if there is only one monomial or constant expression */
            for (int i = 0; i <=j; i++)
                seperated_polynom[0][i] = polynom_array[0][i];
            evaluate(seperated_polynom, lenght, -1, polynom_array, &sum, value);
        }
    }
    while (j < lenght && (polynom_array[0][j] == '+' || polynom_array[0][j] == '-')) /* Remaning parts will check and calculate */
    {
        indexOfSign = j;                                                      /* Position of sign*/
        j++;                                                                  /*to continue the next index*/
        for (; polynom_array[0][j] != '+' && polynom_array[0][j] != '-'; j++) /* if next index is not a delimeter it assing values to seperated polynom */
        {
            if (j == (lenght - 1)) /*if current index is last index it breaks loop*/
            {
                isEndOfPolynom = 1;
                break;
            }
            seperated_polynom[0][indexOfSeperated] = polynom_array[0][j]; /* assing values which are between last sing and current sign */
            indexOfSeperated++;
        }
        if (isEndOfPolynom != 1) /* if current index is not end of polynom it calls evealute function to calculation.*/
            evaluate(seperated_polynom, indexOfSeperated, indexOfSign, polynom_array, &sum, value);
        else /* last index */
        {
            indexOfSeperated = 0;
            c = indexOfSign + 1; /* position of next value which will be calculated */
            for (; c < lenght; c++)
            {
                seperated_polynom[0][indexOfSeperated] = polynom_array[0][c]; /* assing values which are between last sing  and last index */
                indexOfSeperated++;
            }
            evaluate(seperated_polynom, indexOfSeperated, indexOfSign, polynom_array, &sum, value);
            break;
        }
        indexOfSeperated = 0;
    }
    fprintf(evaluations, "%.2lf\n", sum);
}
int main(void)
{
    FILE *values, *polynom, *evaluations;
    values = fopen("values.txt", "r");
    polynom = fopen("polynomial.txt", "r");
    evaluations = fopen("evaluations.txt", "w");
    int input_status, input2_status, i = 0;
    char polynomial[1][lenghtOfPolynom];
    double value;

    if (values == NULL || polynom == NULL) /* Checks values.txt and polynomial.txt are exist.*/
        return (0);

    while (input2_status != EOF) /* Checks if the end of file is reached.*/
    {
        input2_status = fscanf(polynom, "%c", &polynomial[0][i]); /* Reads the character one by one from file*/
        if (input2_status == 1 && polynomial[0][i] != ' ')        /* if reading is successful and  to get rid of spaceses in file */
            i++;                                                  /* increases lenght */
    }

    input_status = fscanf(values, "%lf", &value); /* Scan first value from values.txt file */
    while (input_status != EOF)                   /* Checks if the end of file is reached.*/
    {
        separator(polynomial, (i - 1), value, evaluations); /* calls the function to split*/
        input_status = fscanf(values, "%lf", &value);
    }
    fclose(values);
    fclose(polynom);
    fclose(evaluations);
    return (0);
}