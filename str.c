#include "str.h"

int starts_with(const char *str, const char *prefix)
{
	for (; ; str++, prefix++)
		if (!*prefix)
			return 1;
		else if (*str != *prefix)
			return 0;
}

int istarts_with(const char *str, const char *prefix)
{
	for (; ; str++, prefix++)
		if (!*prefix)
			return 1;
		else if (tolower(*str) != tolower(*prefix))
			return 0;
}

int skip_to_optional_arg_default(const char *str, const char *prefix,
				 const char **arg, const char *def)
{
	const char *p;

	if (!skip_prefix(str, prefix, &p))
		return 0;

	if (!*p) {
		if (arg)
			*arg = def;
		return 1;
	}

	if (*p != '=')
		return 0;

	if (arg)
		*arg = p + 1;
	return 1;
}

char *xstrdup_tolower(const char *string)
{
	char *result;
	size_t len, i;

	len = strlen(string);
	result = xmallocz(len);
	for (i = 0; i < len; i++)
		result[i] = tolower(string[i]);
	return result;
}

char *xstrdup_toupper(const char *string)
{
	char *result;
	size_t len, i;

	len = strlen(string);
	result = xmallocz(len);
	for (i = 0; i < len; i++)
		result[i] = toupper(string[i]);
	return result;
}
