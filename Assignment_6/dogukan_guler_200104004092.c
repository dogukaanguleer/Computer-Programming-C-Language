#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGHT 20
#define MAX_OBJECT_NUMBER 40 /* 2 wheel 1 frame equal 4 OBJECT,  object number equals  to split number in my design*/
#define MAX_INPUT_LENGHT 250

void find_cost(char *object_name, double object_number, double *sum, char *inWhichObject)
{
    char new_input[MAX_INPUT_LENGHT], defined_object[MAX_OBJECT_NUMBER][MAX_NAME_LENGHT], previous_object[MAX_NAME_LENGHT];
    double numberOfObject,cost;
    int object_index = 0;

    if (object_number == 0) /* If object number equals to 0, it is first object  */
        printf("Define %s?:\n", object_name); /*First object is not it something, so its print message is different*/
    else
        printf("Define %s in %s?:\n", object_name, inWhichObject); /* it means it is not first object*/

    scanf("%[^\n]%*c", new_input); /* Gets input include spaceses  */

    strcpy(previous_object, object_name); /* Assings the name of previous object to be printed.*/

    for (char *token = strtok(new_input, " "); token != NULL; object_index++) /* First, splits the new objects. And continues to split if the end is not reached.*/
    {
        strcpy(defined_object[object_index], token); /*it assigns every split to defined_object array*/
        token = strtok(NULL, " ");
    }

    if (object_index != 1) /* It checks definition answer is cost or another objects.*/
    {
        for (int a = 1; a < object_index; a = a + 2) /* For every definition object*/
        {
            sscanf(defined_object[a - 1], "%lf", &numberOfObject); /* it assings object number to a double */

            if (object_number != 0) /*if the first object, it is at the top of the tree*/
                numberOfObject = object_number * numberOfObject; /* multiplies the components of the object by the number of objects*/

            find_cost(defined_object[a], numberOfObject, sum, previous_object); /* it calls function again */
        }
    }
    else /*if definition answer is just a cost*/
    {
        sscanf(defined_object[0], "%lf", &cost); /*assigns cost value to a double*/
        if(object_number==0) /* if given object dont have any component object. For Example  >>define biycle? >>100.0  */
        *sum = *sum + (1 * cost); /* Total cost will be biycle cost */
        else
        *sum = *sum + (object_number * cost); /* multiplies object costs and object numbers */
    }
    if (object_number == 0) /* it checks object number to print total cost*/
        printf("Total cost of %s is %.1lf\n", object_name, *sum);
}

int main(void)
{
    char object_name[MAX_NAME_LENGHT];
    double sum = 0;

    printf("Name of object:\n");
    scanf("%[^\n]%*c", object_name); /* Gets input include spaceses  */

    find_cost(object_name, 0, &sum,"  "); /* Calls function,  0 is sign that is the first object. Also,there is no previous object */

    return 0;
}