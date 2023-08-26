#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a character.
 * @c: The character to be printed.
 * @buffer: Buffer array for print handling.
 * @flags: Calculation of active flags.
 * @width: Width specification.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
                      int flags, int width, int precision, int size)
{
    // The character is stored on the left and padding is added to the right of the buffer.
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
        padd = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) +
                    write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
                    write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a number.
 * @is_negative: Indicates if the number is negative.
 * @ind: Character index.
 * @buffer: Buffer array for print handling.
 * @flags: Calculation of active flags.
 * @width: Width specification.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
                 int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';
    if (is_negative)
        extra_ch = '-';
    else if (flags & F_PLUS)
        extra_ch = '+';
    else if (flags & F_SPACE)
        extra_ch = ' ';

    return (write_num(ind, buffer, flags, width, precision,
                      length, padd, extra_ch));
}

/**
 * write_num - Writes a number using a buffer.
 * @ind: Index where the number starts in the buffer.
 * @buffer: Buffer array for print handling.
 * @flags: Calculation of active flags.
 * @width: Width specification.
 * @prec: Precision specifier.
 * @length: Number length.
 * @padd: Padding character.
 * @extra_c: Extra character.
 *
 * Return: Number of printed characters.
 */
int write_num(int ind, char buffer[],
              int flags, int width, int prec,
              int length, char padd, char extra_c)
{
    int i, padd_start = 1;

    // Handle special cases when printing zero with precision and width.
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return (0); // No character is printed for printf(".0d", 0).

    // Adjust padding for zero and precision cases.
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        buffer[ind] = padd = ' '; // Display width with padding ' '.
    if (prec > 0 && prec < length)
        padd = ' ';

    // Fill buffer with leading zeros if needed.
    while (prec > length)
        buffer[--ind] = '0', length++;

    // Adjust length for extra character.
    if (extra_c != 0)
        length++;

    // Handle padding and alignment.
    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = padd;
        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ')
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        }
        else if (!(flags & F_MINUS) && padd == ' ')
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
        else if (!(flags & F_MINUS) && padd == '0')
        {
            if (extra_c)
                buffer[--padd_start] = extra_c;
            return (write(1, &buffer[padd_start], i - padd_start) +
                    write(1, &buffer[ind], length - (1 - padd_start)));
        }
    }

    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number.
 * @is_negative: Number indicating if the number is negative.
 * @ind: Index where the number starts in the buffer.
 * @buffer: Buffer array for print handling.
 * @flags: Calculation of active flags.
 * @width: Width specification.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of written characters.
 */
int write_unsgnd(int is_negative, int ind,
                 char buffer[],
                 int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    // Handle special case when printing zero with precision.
    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return (0); // No character is printed for printf(".0d", 0).

    // Adjust padding for precision cases.
    if (precision > 0 && precision < length)
        padd = ' ';

    // Fill buffer with leading zeros if needed.
    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    // Adjust padding based on flags.
    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    // Handle padding and alignment.
    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS)
        {
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        }
        else
        {
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
        }
    }

    return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writes a memory address.
 * @buffer: Buffer array for print handling.
 * @ind: Index where the number starts in the buffer.
 * @length: Length of the number.
 * @width: Width specification.
 * @flags: Calculation of active flags.
 * @padd: Padding character.
 * @extra_c: Extra character.
 * @padd_start: Index where padding should start.
 *
 * Return: Number of written characters.
 */
int write_pointer(char buffer[], int ind, int length,
                  int width, int flags, char padd, char extra_c, int padd_start)
{
    int i;

    // Handle padding and alignment.
    if (width > length)
    {
        for (i = 3; i < width - length + 3; i++)
            buffer[i] = padd;
        buffer[i] = '\0';

        if (flags & F_MINUS)
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
    }

    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
