#include "main.h"

/**
 * get_flags - Calculates active flags from format string
 * @format: Format string containing formatting specifiers
 * @i: Pointer to the current position in the format string
 * Return: Calculated flags
 */
int get_flags(const char *format, int *i)
{
    /* Possible flag characters and their corresponding values */
    const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    int j, curr_i;
    int flags = 0;

    /* Loop through characters after '%' to identify flags */
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        /* Check if the current character is a recognized flag character */
        for (j = 0; FLAGS_CH[j] != '\0'; j++)
        {
            if (format[curr_i] == FLAGS_CH[j])
            {
                flags |= FLAGS_ARR[j]; // Add corresponding flag value
                break;
            }
        }

        /* If the current character is not a recognized flag, exit loop */
        if (FLAGS_CH[j] == 0)
            break;
    }

    *i = curr_i - 1; // Update the position pointer

    return (flags); // Return the calculated flags
}
