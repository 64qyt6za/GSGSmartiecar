// code to test the tokenize function in cam.h

// tokenizing function
void tokenize(char *str, char *delim, char **tokens)
{
    int i = 0;
    char *token = strtok(str, delim);
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, delim);
    }
}

char str[] = "43 163 42 42 42";
char *tokens[5];

void setup()
{
}

void loop()
{
    tokenize(str, " ", tokens);
    printf("first part: %s", tokens[1]);
    return 0;
}