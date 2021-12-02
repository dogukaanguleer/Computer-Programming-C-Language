#include <stdio.h>
#include <string.h>
#define maxTextLenght 250
char find_tree(char *array, int n, int dash_number, int controlFLag, int lenght, FILE *output)
{
    if (n == lenght)  /* Condition to break recursion. If current character is last character.*/
        return (0);
    else 
    {
        if (array[n] != '(' && array[n] != ')' && array[n] != ',')  /* if current character is not " ( ) ," */
        {
            for (int i = 0; controlFLag == 0 && i < dash_number; i++) /* According dash number, prints dashes*/
                fprintf(output, "-");
            fprintf(output, "%c", array[n]); 
            find_tree(array, n + 1, dash_number, 1, lenght, output); /* It calls function again with incerased index*/
        }
        else if (array[n] == '(') /* if current characters is "("*/
            find_tree(array, n + 1, ++dash_number, 0, lenght, output); /* It calls function again with incerased index and increased dash number*/
        else if (array[n] == ',') /* if current character is comma, prints newline*/
        {
            fprintf(output, "\n");
            find_tree(array, n + 1, dash_number, 0, lenght, output); /* It calls function again with incerased index*/
        }
        else if (array[n] == ')')/* if current character is ")"*/
            find_tree(array, n + 1, --dash_number, 0, lenght, output); /* It calls function again with incerased index and decreased dash number*/
    }
}
int main(void)
{
    FILE *input, *output; 
    input = fopen("input.txt", "r"); 
    output = fopen("output.txt", "w");
    if (input == NULL) /* Checks input.txt is exist */
        return (0);

    char ch, input_array[maxTextLenght];
    int n = 0, dash_number = 0, controlFLag = 0, i = 0, isNotSpace, lenght;

    for (ch = fgetc(input); ch != '\n' && ch != EOF; ch = fgetc(input)) /* Reads char from file until EOF is reached.*/
    {
        input_array[i] = ch;  
        if (input_array[i] != ' ' && isNotSpace == 0) /* Ignore spaceses at the beginning. */
            isNotSpace = 1; 
        if (isNotSpace == 1) /* Means spaceses at the beginning are run out.*/
            i++;
    }
    lenght = strlen(input_array);
    while (input_array[lenght - 1] == ' ') /*Specify new lenght to ignore spaceses at the ending. */
        lenght--;
        
    find_tree(input_array, n, dash_number, controlFLag, lenght, output); /* Call recursion function to print */
    fclose(input);
    fclose(output);
    return (0);
}
