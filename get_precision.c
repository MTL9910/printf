#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string containing formatting specifiers
 * @i: Pointer to the current position in the format string
 * @list: List of arguments passed to the function
 *
 * Return: Calculated precision
 */
int get_precision(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int precision = -1;

    // Check for presence of precision specifier (dot)
    if (format[curr_i] != '.')
        return (precision);

    precision = 0;

    // Loop through characters after dot to calculate precision
    for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            precision *= 10;
            precision += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            curr_i++;
            precision = va_arg(list, int); // Get precision value from arguments
            break;
        }
        else
            break;
    }

    *i = curr_i - 1; // Update the position pointer

    return (precision); // Return the calculated precision
}
