#ifndef TRACE2_STUB_H
#define TRACE2_STUB_H

/**
 * Temporary stub file for trace2 to compile with git-std-lib.
 * Currently being called from usage.c.
*/

void trace2_cmd_name_fl(const char *file, int line, const char *name);

#define trace2_cmd_name(v) trace2_cmd_name_fl(__FILE__, __LINE__, (v))

void trace2_cmd_error_va_fl(const char *file, int line, const char *fmt,
			    va_list ap);

#define trace2_cmd_error_va(fmt, ap) \
	trace2_cmd_error_va_fl(__FILE__, __LINE__, (fmt), (ap))

#endif /* TRACE2_STUB_H */
