#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>

typedef enum stoi_error
{
	stoi_success,
	stoi_overflow,
	stoi_invalid_char,
	stoi_unexpected_end,
}
stoi_error;

static int digit_value(char c)
{
	if (c >= '0' &&
		c <= '9')
	{
		return (c - '0');
	}
	
	c = tolower(c);
	
	if (c >= 'a' &&
		c <= 'z')
	{
		return (c - 'a' + 10);
	}
	
	return -1;
}

static stoi_error stoi(int *result, char const *str, unsigned base)
{
	int negative = 0;
	unsigned absolute = 0;
	unsigned limit = INT_MAX;
	
	assert(result);
	assert(str);
	assert(base >= 2);
	assert(base <= 36);
	
	switch (*str)
	{
	case '-':
		negative = 1;
		limit += 1;
		/*fall through*/
	case '+':
		++str;
		break;
	default:
		break;
	}
	
	if (!*str)
	{
		return stoi_unexpected_end;
	}
	
	do
	{
		int const digit = digit_value(*str);
		if ((digit < 0) ||
			((unsigned)digit >= base))
		{
			return stoi_invalid_char;
		}
		
		if ((limit / base) < absolute)
		{
			return stoi_overflow;
		}
		
		absolute *= base;
		
		if ((limit - digit) < absolute)
		{
			return stoi_overflow;
		}
		
		absolute += digit;
		
		++str;
	}
	while (*str);
	
	*result = negative ? -absolute : absolute;
	return stoi_success;
}

static void test_stoi(void)
{
	int result;
	unsigned i;
	
	assert(stoi(&result, "2147483648", 10) == stoi_overflow);
	
	result = 0;
	assert(stoi(&result, "2147483647", 10) == stoi_success);
	assert(result == 2147483647);
	
	result = 0;
	assert(stoi(&result, "-2147483648", 10) == stoi_success);
	assert(result == -2147483647 - 1);
	
	for (i = 2; i <= 10; ++i)
	{
		assert(stoi(&result, "a", i) == stoi_invalid_char);
		assert(stoi(&result, "-a", i) == stoi_invalid_char);
		assert(stoi(&result, "-1a", i) == stoi_invalid_char);
	}
	
	for (i = 2; i <= 36; ++i)
	{
		assert(stoi(&result, "", i) == stoi_unexpected_end);
		assert(stoi(&result, "-", i) == stoi_unexpected_end);
		assert(stoi(&result, "+", i) == stoi_unexpected_end);
		
		assert(stoi(&result, " ", i) == stoi_invalid_char);
		assert(stoi(&result, "- ", i) == stoi_invalid_char);
		assert(stoi(&result, "-1 ", i) == stoi_invalid_char);
	}
}

static int svs_atoi(char const *str)
{
	int result;
	stoi_error const error = stoi(&result, str, 10);
	assert(error == stoi_success);
	return result;
}

int main(void)
{
	test_stoi();
	
	assert(svs_atoi("0") == 0);
	assert(svs_atoi("1") == 1);
	assert(svs_atoi("10") == 10);
	assert(svs_atoi("123") == 123);
	assert(svs_atoi("5566") == 5566);
	assert(svs_atoi("12345") == 12345);
	assert(svs_atoi("219540062") == 219540062);
	assert(svs_atoi("2147483647") == 2147483647);
	
	assert(svs_atoi("-0") == 0);
	assert(svs_atoi("-1") == -1);
	assert(svs_atoi("-10") == -10);
	assert(svs_atoi("-123") == -123);
	assert(svs_atoi("-5566") == -5566);
	assert(svs_atoi("-219540062") == -219540062);
	
	assert(svs_atoi("+0") == 0);
	assert(svs_atoi("+1") == 1);
	assert(svs_atoi("+10") == 10);
	assert(svs_atoi("+123") == 123);
	assert(svs_atoi("+5566") == 5566);
	assert(svs_atoi("+219540062") == 219540062);
	
	assert(svs_atoi("-2147483648") == -2147483647 - 1);
	assert(svs_atoi("+2147483647") == 2147483647);
	
	return 0;
}
