#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string containing formatting specifiers
 * @i: Pointer to the current position in the format string
 *
 * Return: Calculated size specifier (S_LONG or S_SHORT)
 */
int get_size(const char *format, int *i)
{
    int curr_i = *i + 1;
    int size = 0;

    // Check for size specifier (l or h)
    if (format[curr_i] == 'l')
        size = S_LONG;
    else if (format[curr_i] == 'h')
        size = S_SHORT;

    // Update the position pointer based on whether a size specifier was found
    if (size == 0)
        *i = curr_i - 1;
    else
        *i = curr_i;

    return (size); // Return the calculated size specifier
}
