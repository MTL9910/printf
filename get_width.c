#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string containing formatting specifiers
 * @i: Pointer to the current position in the format string
 * @list: List of arguments passed to the function
 *
 * Return: Calculated width
 */
int get_width(const char *format, int *i, va_list list)
{
    int curr_i;
    int width = 0;

    // Loop through characters after '%', checking for width specifier
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            width *= 10;
            width += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            curr_i++;
            width = va_arg(list, int); // Get width value from arguments
            break;
        }
        else
            break;
    }

    *i = curr_i - 1; // Update the position pointer

    return (width); // Return the calculated width
}
