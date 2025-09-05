#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define LONG_LONG_INPUT_BUFFER_SIZE 64

void flush_stdin()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}
bool readLine(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL)
    {
        return false;
    }

    if (!strchr(buffer, '\n'))
    {
        printf("Warning: input was too long and has been truncated.\n");
        flush_stdin();
        return false;
    }

    return true;
}

void request_long_long(long long *output, const char *instructions)
{
    char line[LONG_LONG_INPUT_BUFFER_SIZE];
    bool valid = false;

    do
    {
        printf("%s", instructions);

        if (!readLine(line, sizeof(line)))
        {
            printf("Error reading input. Try again.\n");
            continue;
        }

        // Remove newline if present
        line[strcspn(line, "\n")] = '\0';

        char *endptr;
        errno = 0; // Reset errno before conversion
        long long value = strtoll(line, &endptr, 10);

        if (endptr == line || *endptr != '\0')
        {
            printf("Invalid input. Please enter a valid integer.\n");
        }
        else if ((errno == ERANGE && (value == LLONG_MAX || value == LLONG_MIN)))
        {
            printf("Input is out of range for a long long integer.\n");
        }
        else
        {
            *output = value;
            valid = true;
        }

    } while (!valid);
}
long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, char **argv)
{
    long long numerator;
    long long denominator;

    request_long_long(&numerator, "Enter a numerator. It must be an integer.\n");

    do
    {
        request_long_long(&denominator, "Enter a denominator. It must be an integer.\n");
        if (denominator == 0)
            printf("Denominator cannot be zero. Please try again.\n");
    } while (denominator == 0);

    printf("Fraction: %lld / %lld\n", numerator, denominator);
    long long fraction_gcd = gcd(numerator, denominator);
    printf("Reduced Fraction: %lld / %lld\n", numerator / fraction_gcd, denominator / fraction_gcd);
    return 0;
}
