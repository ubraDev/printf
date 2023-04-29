#include "main.h"

/**
 * _printf - prints formatted output
 * @format: the format string
 *
 * Return: the number of characters printed
 */
int _printf(const char *format, ...)
{
int count = 0;
va_list arg_list;
char *str_ptr, *start_ptr;
params_t params = PARAMS_INIT;

va_start(arg_list, format);
if (!format || (format[0] == '%' && !format[1]))
return (-1);
if (format[0] == '%' && format[1] == ' ' && !format[2])
return (-1);
for (str_ptr = (char *)format; *str_ptr; str_ptr++)
{
init_params(&params, arg_list);
if (*str_ptr != '%') 
{
count += _putchar(*str_ptr);
continue;
}
start_ptr = str_ptr;
str_ptr++;
while (get_flag(str_ptr, &params))
{
str_ptr++;
}
str_ptr = get_width(str_ptr, &params, arg_list);
str_ptr = get_precision(str_ptr, &params, arg_list);
if (get_modifier(str_ptr, &params))
str_ptr++;
if (!get_specifier(str_ptr))
count += print_from_to(start_ptr, str_ptr,
params.l_modifier || params.h_modifier ? str_ptr - 1 : 0);
else
count += get_print_func(str_ptr, arg_list, &params);
}
_putchar(BUF_FLUSH);
va_end(arg_list);
return (count);
}
