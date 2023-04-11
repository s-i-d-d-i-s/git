#include <tap/basic.h>
#include "../strbuf.h"

int strbuf_init_test() {
	struct strbuf *buf = malloc(sizeof(void*));
	strbuf_init(buf, 0);

	if (buf->buf[0] != '\0')
		return 0;
	if (buf->alloc != 0)
		return 0;
	if (buf->len != 0)
		return 0;
	return 1;
}

/* 
 * Should test functions have a numbering system?
 * Simple, but would make it hard to tests in between
 * 
 * This could also be combined with the above test, but we would
 * lose a description of the test and wouldn't be able to tell
 * where we failed.
 */
int strbuf_init_test2() {
	struct strbuf *buf = malloc(sizeof(void*));
	strbuf_init(buf, 100);

	if (buf->buf[0] != '\0')
		return 0;
	if (buf->alloc != 101)
		return 0;
	if (buf->len != 0)
		return 0;
	return 1;
}

int strbuf_grow_test() {
	struct strbuf *buf = malloc(sizeof(void*));
	strbuf_grow(buf, 100);

	if (buf->buf[0] != '\0')
		return 0;
	if (buf->alloc != 101)
		return 0;
	if (buf->len != 0)
		return 0;
	return 1;
}

int main(void)
{
	plan(3);
	ok(strbuf_init_test(), "strbuf_init initializes properly");
	ok(strbuf_init_test2(), "strbuf_init with hint initializes properly");
	ok(strbuf_grow_test(), "strbuf_grow grows properly");
	return 0;
}