#include <tap/basic.h>

#include "../git-compat-util.h"
#include "../strbuf.h"

int strbuf_init_test()
{
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

int main(void)
{
	plan(1);
	ok(strbuf_init_test(), "strbuf_init initializes properly");
	return 0;
}
