#include <tap/basic.h>

int unit_test() {
	if (1 != 1)
		return 0;
	return 1;
}

int main(void)
{
	plan(1);
	ok(unit_test(), "unit test runs successfully");
	return 0;
}
