#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGHT_OF_IDENTIFIER 10
#define MAX_LENGHT_OF_INPUT 100

struct gate
{
    char name[MAX_LENGHT_OF_IDENTIFIER];
    int type;
    char input1[MAX_LENGHT_OF_IDENTIFIER];
    char input2[MAX_LENGHT_OF_IDENTIFIER];
    int in1;
    int in2;
    int out;
    int memory;
    struct gate *inp1;
    struct gate *inp2;
};

int evaluate(struct gate *g)
{
    if (g->type == 0) // input
        return g->out;
    else if (g->type == 1) // and
    {
        int i1 = evaluate(g->inp1);
        int i2 = evaluate(g->inp2);
        return i1 && i2;
    }
    else if (g->type == 2) //or
    {
        int i1 = evaluate(g->inp1);
        int i2 = evaluate(g->inp2);
        return i1 || i2;
    }
    else if (g->type == 3) //not
    {
        int i1 = evaluate(g->inp1);
        return !i1;
    }
    else if (g->type == 4) //flipflop
    {
        int i1 = evaluate(g->inp1);
        if (i1 == 1)
        {
            int temp_memory = g->memory;
            g->memory = !(g->memory);
            return !temp_memory;
        }
        else
            return g->memory;
    }
}

int fill_circuit_array(struct gate *circuit, char *array, char *token, int tpye, int i)
{
    if (tpye == 1 || tpye == 2) // if "AND" or "OR"
    {
        circuit->type = tpye;
        token = strtok(NULL, " ");
        strcpy(circuit->name, token);
        token = strtok(NULL, " ");
        strcpy(circuit->input1, token);
        token = strtok(NULL, " ");
        strcpy(circuit->input2, token);
        return ++i;
    }
    else if (tpye == 3 || tpye == 4) // if "NOT" or "FLIPFLOP"
    {
        circuit->type = tpye;
        token = strtok(NULL, " ");
        strcpy(circuit->name, token);
        token = strtok(NULL, " ");
        strcpy(circuit->input1, token);
        return ++i;
    }
}

int main()
{
    FILE *input, *circuit, *output;
    input = fopen("input.txt", "r");
    circuit = fopen("circuit.txt", "r");
    output = fopen("output.txt", "w");

    if (input == NULL || circuit == NULL) // if files are not exist.
        return 0;

    char array[MAX_LENGHT_OF_INPUT]; /*store new line in array*/
    int inputflag = 0, numberOfGates = 0, inputGatesNumber, input_status, indexOfCircuit = 0;

    /*  Counts number of gates for malloc */
    while (fscanf(circuit, "%[^\n]%*c", array) != EOF)
    {
        if (inputflag == 0) /* to distinguish number of gates in first line*/
        {
            for (char *token = strtok(array, " "); token != NULL; numberOfGates++) /* split the first line and count number of gates*/
                token = strtok(NULL, " ");

            inputflag = 1;
            numberOfGates--;
            inputGatesNumber = numberOfGates;
        }
        else
            numberOfGates++;
    }

    /*Allocate memory for circuit array*/
    struct gate **circuit_array = (struct gate **)malloc(sizeof(struct gate *) * numberOfGates);
    for (int index = 0; index < numberOfGates; index++)
        circuit_array[index] = (struct gate *)malloc(sizeof(struct gate)); /*Allocate memory for each object in circuit array*/

    fseek(circuit, 0, SEEK_SET); /* To read file again.*/

    /* Reads circuit.txt and assings values to circuit_array*/
    while (fscanf(circuit, "%[^\n]%*c", array) != EOF)
    {
        char *token = strtok(array, " "); /* splits first word of lines*/
        if (strcmp(token, "INPUT") == 0)
        {
            for (token = strtok(NULL, " "); token != NULL; indexOfCircuit++)
            {
                strcpy(circuit_array[indexOfCircuit]->name, token);
                circuit_array[indexOfCircuit]->type = 0;
                token = strtok(NULL, " ");
            }
        }
        else if (strcmp(token, "AND") == 0)
            indexOfCircuit = fill_circuit_array(circuit_array[indexOfCircuit], array, token, 1, indexOfCircuit); /* cals function to fill circuit_array according gate type.*/
        else if (strcmp(token, "OR") == 0)
            indexOfCircuit = fill_circuit_array(circuit_array[indexOfCircuit], array, token, 2, indexOfCircuit);
        else if (strcmp(token, "NOT") == 0)
            indexOfCircuit = fill_circuit_array(circuit_array[indexOfCircuit], array, token, 3, indexOfCircuit);
        else if (strcmp(token, "FLIPFLOP") == 0)
            indexOfCircuit = fill_circuit_array(circuit_array[indexOfCircuit], array, token, 4, indexOfCircuit);
    }

    /* connects circuit's gate's inputs*/
    for (int index = inputGatesNumber; index < numberOfGates; index++)
        for (int a = 0; a < numberOfGates; a++)
        {
            if (strcmp(circuit_array[index]->input1, circuit_array[a]->name) == 0)
                circuit_array[index]->inp1 = circuit_array[a];
            if (strcmp(circuit_array[index]->input2, circuit_array[a]->name) == 0)
                circuit_array[index]->inp2 = circuit_array[a];
        }

    int a;
    /* Reads input.txt.  And calls the function.*/
    while (1)
    {
        for (a = 0; a < inputGatesNumber && input_status!=EOF; a++)
            input_status = fscanf(input, "%d", &circuit_array[a]->out); 
        if (input_status == EOF)
            break;
        if (a == inputGatesNumber)
        {
            int result = evaluate(circuit_array[numberOfGates - 1]);
            fprintf(output, "%d\n", result);
        }
    }

    for (int index = 0; index < numberOfGates; index++)
        free(circuit_array[index]);
    free(circuit_array);
    fclose(input);
    fclose(circuit);
    fclose(output);
    return 0;
}