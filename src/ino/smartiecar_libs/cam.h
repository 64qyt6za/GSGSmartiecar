int Picturemiddle_x = 0;
int Picturemiddle_y = 0;

// own split function since arduino doesn't have a default one
void splitString(String input, char delimiter, String output[], int &count)
{
    int startIndex = 0;
    int endIndex = 0;
    count = 0;
    while (endIndex != -1)
    {
        endIndex = input.indexOf(delimiter, startIndex);
        output[count] = input.substring(startIndex, endIndex);
        startIndex = endIndex + 1;
        count++;
    }
}

// 2nd tokenizing function
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

void findNextPillar()
{
    String substrings[10]; // Create an array to store the substrings

    // Block
    P_color = 'U';
    P_x = 0;
    P_height = 0;
    P_wall_L = 'N';
    P_wall_R = 'N';

    String data = raspi_get_data();
    int count = 0;
    splitString(data, ' ', substrings, count); // Split the data into substrings using a space delimiter
    P_color = substrings[0].charAt(0);
    P_x = substrings[1].toInt();
    P_height = substrings[2].toInt();
    P_wall_L = substrings[3].charAt(0);
    P_wall_R = substrings[4].charAt(0);

    return;
}