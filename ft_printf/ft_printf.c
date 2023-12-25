#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (*s == '\0' || s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_print_str(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	write (1, str, ft_strlen(str));
	return (ft_strlen(str));
}

void	ft_putnbr(int64_t n, int base, char *charset, int *len)
{
	if (n < 0)
	{
		*len += write(1, "-", 1);
		n = -n;
	}
	if (n >= base)
		ft_putnbr(n/base, base, charset, len);
	*len += write(1, &charset[n%base], 1);
}

void	ft_putptr(uintptr_t n, uintptr_t base, char *charset, int *len)
{
	if (n >= base)
		ft_putptr(n / base, base, charset, len);
	*len += write(1, &charset[n % base], 1);
}

int	eval_format(const char *format, va_list ap, int *len, int i)
{
	if (format[i] == 's')
		*len += ft_print_str(va_arg(ap, char*));
	else if (format[i] == 'd')
		ft_putnbr(va_arg(ap, int), 10, "0123456789", len);
	else if (format[i] == 'p')
	{
		*len += write(1, "0x", 2);
		ft_putptr(va_arg(ap, uintptr_t), 16, "0123456789abcdef", len);
	}
	else if (format[i] == 'x')
		ft_putnbr(va_arg(ap, unsigned int), 16, "0123456789abcdef", len);
	else if (format[i] == '%')
		*len += write(1, "%%", 1);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int	i;
	int	len;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			i += eval_format(format, ap, &len, i+1);
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}

// int main()
// {
// 	ft_printf("%s\n", "toto");
// 	//out: toto$

// 	ft_printf("Magic %s is %d", "number", 42);
// 	//out: Magic number is 42%

// 	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// 	//out: Hexadecimal for 42 is 2a$
// }