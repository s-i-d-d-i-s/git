#include <tap/basic.h>
#include <../hashmap.h>
#include <../hashmap.c>

int strhash_HashValue_string()
{
	const char *str = "foobar";
	unsigned int hash_value = strhash(str);
	unsigned int expected_hash_value = 837857890;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int strhash_HashValue_emptyString()
{
	const char *str = "";
	unsigned int hash_value = strhash(str);
	unsigned int expected_hash_value = 2166136261;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int strihash_HashValue_string()
{
	const char *str = "foobar";
	unsigned int hash_value = strihash(str);
	unsigned int expected_hash_value = 3932965794;

	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int strihash_HashValue_emptyString()
{
	const char *str = "";
	unsigned int hash_value = strihash(str);
	unsigned int expected_hash_value = 2166136261;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int memhash_HashValue_string()
{
	const char *str = "foobar";
	unsigned int hash_value = memhash(str, 6);
	unsigned int expected_hash_value = 837857890;

	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int memhash_HashValue_emptyString()
{
	const char *str = "";
	unsigned int hash_value = memhash(str, 0);
	unsigned int expected_hash_value = 2166136261;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int memihash_HashValue_string()
{
	const char *str = "foobar";
	unsigned int hash_value = memihash(str, 6);
	unsigned int expected_hash_value = 3932965794;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int memihash_HashValue_emptyString()
{
	const char *str = "";
	unsigned int hash_value = memihash(str, 0);
	unsigned int expected_hash_value = 2166136261;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int memihash_cont_HashValue_string()
{
	const char *str = "foobar";
	int hash_seed = 1234;
	unsigned int hash_value = memihash_cont(hash_seed, str, 6);
	unsigned int expected_hash_value = 4193430053;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int memihash_cont_HashValue_emptyString()
{
	const char *str = "";
	int hash_seed = 1234;
	unsigned int hash_value = memihash_cont(hash_seed, str, 0);
	unsigned int expected_hash_value = 1234;
	if (expected_hash_value == hash_value) {
		return 1;
	}
	return 0;
}

int allocate_table_TableSize()
{
	struct hashmap map;
	unsigned int size = 6;
	alloc_table(&map, size);
	int expected_tablesize = 6;
	if (map.tablesize == expected_tablesize) {
		return 1;
	}
	return 0;
}

int allocate_table_GrowAt()
{
	struct hashmap map;
	unsigned int size = 6;
	alloc_table(&map, size);
	int expected_grow_at = 4;
	if (map.grow_at == expected_grow_at) {
		return 1;
	}
	return 0;
}

int hashmap_add_AddElement(int n)
{
	struct hashmap map;
	hashmap_init(&map, NULL, NULL, 0);

	int old_size = map.private_size;

	for (int i = 0; i < n; i++) {
		struct hashmap_entry e;
		hashmap_add(&map, &e);
	}

	int new_size = map.private_size;

	if (new_size == old_size + n) {
		return 1;
	}
	return 0;
}

int main(void)
{
	plan(14);

	ok(strhash_HashValue_string(), "strhash with string argument");
	ok(strhash_HashValue_emptyString(),
	   "strhash with empty string argument");
	ok(strihash_HashValue_string(), "strihash with string");
	ok(strihash_HashValue_emptyString(), "strihash with empty string");

	ok(memhash_HashValue_string(), "memhash with string works");
	ok(memhash_HashValue_emptyString(), "memhash with empty string");

	ok(memihash_HashValue_string(), "memihash with string");
	ok(memihash_HashValue_emptyString(), "memihash with empty string");

	ok(memihash_cont_HashValue_string(), "memihash_cont with string");

	ok(memihash_cont_HashValue_emptyString(),
	   "memihash_cont with empty string");

	ok(allocate_table_TableSize(),
	   "allocated a new hashmap and test table size");
	ok(allocate_table_GrowAt(),
	   "allocated a new hashmap and test grow at");

	ok(hashmap_add_AddElement(1), "added 1 new element to hashmap");
	ok(hashmap_add_AddElement(2), "added 2 new element to hashmap");
	return 0;
}