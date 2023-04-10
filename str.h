#ifndef STR_H
#define STR_H

#include "git-compat-util.h"

int starts_with(const char *str, const char *prefix);
int istarts_with(const char *str, const char *prefix);

/*
 * If the string "str" begins with the string found in "prefix", return 1.
 * The "out" parameter is set to "str + strlen(prefix)" (i.e., to the point in
 * the string right after the prefix).
 *
 * Otherwise, return 0 and leave "out" untouched.
 *
 * Examples:
 *
 *   [extract branch name, fail if not a branch]
 *   if (!skip_prefix(ref, "refs/heads/", &branch)
 *	return -1;
 *
 *   [skip prefix if present, otherwise use whole string]
 *   skip_prefix(name, "refs/heads/", &name);
 */
static inline int skip_prefix(const char *str, const char *prefix,
			      const char **out)
{
	do {
		if (!*prefix) {
			*out = str;
			return 1;
		}
	} while (*str++ == *prefix++);
	return 0;
}

/*
 * If the string "str" is the same as the string in "prefix", then the "arg"
 * parameter is set to the "def" parameter and 1 is returned.
 * If the string "str" begins with the string found in "prefix" and then a
 * "=" sign, then the "arg" parameter is set to "str + strlen(prefix) + 1"
 * (i.e., to the point in the string right after the prefix and the "=" sign),
 * and 1 is returned.
 *
 * Otherwise, return 0 and leave "arg" untouched.
 *
 * When we accept both a "--key" and a "--key=<val>" option, this function
 * can be used instead of !strcmp(arg, "--key") and then
 * skip_prefix(arg, "--key=", &arg) to parse such an option.
 */
int skip_to_optional_arg_default(const char *str, const char *prefix,
				 const char **arg, const char *def);

static inline int skip_to_optional_arg(const char *str, const char *prefix,
				       const char **arg)
{
	return skip_to_optional_arg_default(str, prefix, arg, "");
}

/*
 * Like skip_prefix, but promises never to read past "len" bytes of the input
 * buffer, and returns the remaining number of bytes in "out" via "outlen".
 */
static inline int skip_prefix_mem(const char *buf, size_t len,
				  const char *prefix,
				  const char **out, size_t *outlen)
{
	size_t prefix_len = strlen(prefix);
	if (prefix_len <= len && !memcmp(buf, prefix, prefix_len)) {
		*out = buf + prefix_len;
		*outlen = len - prefix_len;
		return 1;
	}
	return 0;
}

/*
 * If buf ends with suffix, return 1 and subtract the length of the suffix
 * from *len. Otherwise, return 0 and leave *len untouched.
 */
static inline int strip_suffix_mem(const char *buf, size_t *len,
				   const char *suffix)
{
	size_t suflen = strlen(suffix);
	if (*len < suflen || memcmp(buf + (*len - suflen), suffix, suflen))
		return 0;
	*len -= suflen;
	return 1;
}

/*
 * If str ends with suffix, return 1 and set *len to the size of the string
 * without the suffix. Otherwise, return 0 and set *len to the size of the
 * string.
 *
 * Note that we do _not_ NUL-terminate str to the new length.
 */
static inline int strip_suffix(const char *str, const char *suffix, size_t *len)
{
	*len = strlen(str);
	return strip_suffix_mem(str, len, suffix);
}

static inline int ends_with(const char *str, const char *suffix)
{
	size_t len;
	return strip_suffix(str, suffix, &len);
}

/*
 * Like skip_prefix, but compare case-insensitively. Note that the comparison
 * is done via tolower(), so it is strictly ASCII (no multi-byte characters or
 * locale-specific conversions).
 */
static inline int skip_iprefix(const char *str, const char *prefix,
			       const char **out)
{
	do {
		if (!*prefix) {
			*out = str;
			return 1;
		}
	} while (tolower(*str++) == tolower(*prefix++));
	return 0;
}

/*
 * Like skip_prefix_mem, but compare case-insensitively. Note that the
 * comparison is done via tolower(), so it is strictly ASCII (no multi-byte
 * characters or locale-specific conversions).
 */
static inline int skip_iprefix_mem(const char *buf, size_t len,
				   const char *prefix,
				   const char **out, size_t *outlen)
{
	do {
		if (!*prefix) {
			*out = buf;
			*outlen = len;
			return 1;
		}
	} while (len-- > 0 && tolower(*buf++) == tolower(*prefix++));
	return 0;
}

static inline int strtoul_ui(char const *s, int base, unsigned int *result)
{
	unsigned long ul;
	char *p;

	errno = 0;
	/* negative values would be accepted by strtoul */
	if (strchr(s, '-'))
		return -1;
	ul = strtoul(s, &p, base);
	if (errno || *p || p == s || (unsigned int) ul != ul)
		return -1;
	*result = ul;
	return 0;
}

static inline int strtol_i(char const *s, int base, int *result)
{
	long ul;
	char *p;

	errno = 0;
	ul = strtol(s, &p, base);
	if (errno || *p || p == s || (int) ul != ul)
		return -1;
	*result = ul;
	return 0;
}

char *xstrdup_tolower(const char *);
char *xstrdup_toupper(const char *);

#endif /* STR_H */