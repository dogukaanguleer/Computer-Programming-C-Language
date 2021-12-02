#include <stdio.h>
#define Repetition 10
#define divideByZeroValue 0.0001   /*Temp value for divide by 0 situations*/
int main(void)
{
    int continueFlag = 1, i, j;
    double x, y, sumx1 = 0, sumy1 = 0, sumx2 = 0, sumy2 = 0;

    for (i = 0; i < Repetition; i++)  /*Get points from user times Repetition*/
    {
        if (scanf("%lf", &x) == 1)  /*It checks given input is valid for double*/
        {
            if (scanf("%lf", &y) == 1) /*It checks given input is valid for double*/
            {
                sumx1 = sumx1 + x;    
                sumy1 = sumy1 + y;
            }
            else
            {
                continueFlag = 0;
                break;
            }
        }
        else
        {
            continueFlag = 0;
            break;
        }
    }
    if (continueFlag == 1) /* Program continues if continueFlag is true(inputs are valid)*/
    {
        for (j = 0; j < Repetition; j++) /*Get points from user times Repetition*/
        {
            if (scanf("%lf", &x) == 1) /*It checks given input is valid for double*/
            {
                if (scanf("%lf", &y)) /*It checks given input is valid for double*/
                {
                    sumx2 = sumx2 + x;
                    sumy2 = sumy2 + y;
                }
                else
                {
                    continueFlag = 0;
                    break;
                }
            }
            else
            {
                continueFlag = 0;
                break;
            }
        }
        if (continueFlag == 1) /* Program continues if continueFlag is true(inputs are valid)*/
        {
            double x1, y1, averageX1, averageY1, averageX2, averageY2, midX, midY, slopeAverage, slopeSL, averageDiffx;
            averageX1 = sumx1 / Repetition;
            averageY1 = sumy1 / Repetition;
            averageX2 = sumx2 / Repetition;
            averageY2 = sumy2 / Repetition;
            midX = (averageX1 + averageX2) / 2;  /*Finds X coordinate of mid point*/
            midY = (averageY1 + averageY2) / 2;  /*Finds Y coordinate of mid point*/
            averageDiffx = averageX2 - averageX1;
            if (averageDiffx == 0) /* Checks if devide by 0 exception is exist*/
                averageDiffx = divideByZeroValue;

            slopeAverage = (averageY2 - averageY1) / (averageDiffx);

            if (slopeAverage == 0) /* Checks if devide by 0 exception is exist*/
                slopeAverage = divideByZeroValue;

            slopeSL = -1 / slopeAverage; /*Calculation of seperate line's slope*/
            while (1)
            {
                if (scanf("%lf", &x1) == 1) /*It checks given input is valid for double*/
                {
                    if (scanf("%lf", &y1) == 1) /*It checks given input is valid for double*/
                    {       /*classifications conditions according to calculated values*/ 
                        if (((y1 - midY > slopeSL * (x1 - midX)) && (averageY1 - midY > slopeSL * (averageX1 - midX))) || ((y1 - midY < slopeSL * (x1 - midX)) && (averageY1 - midY < slopeSL * (averageX1 - midX))))
                            printf("Class 1\n");  /* Print if test point and average1 coordinates are located in same location*/
                        else if (((y1 - midY > slopeSL * (x1 - midX)) && (averageY2 - midY > slopeSL * (averageX2 - midX))) || ((y1 - midY < slopeSL * (x1 - midX)) && (averageY2 - midY < slopeSL * (averageX2 - midX))))
                            printf("Class 2\n");  /* Print if test point and average2 coordinates are located in same location*/
                        else
                            break;
                    }
                    else
                        break;
                }
                else
                    break;
            }
        }
    }
    return (0);
}
