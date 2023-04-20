#include <tap/basic.h>
#include <../hashmap.h>
#include <../hashmap.c>

struct hashmap get_hashmap(int n)
{
	struct hashmap map;
	hashmap_init(&map, NULL, NULL, n);
	return map;
}

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
	struct hashmap map = get_hashmap(0);

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

int rehash_RehashWithSize(int n)
{
	struct hashmap map;
	alloc_table(&map, 1);
	int old_size = map.tablesize;

	rehash(&map, n);

	int new_size = map.tablesize;

	if (new_size == n) {
		return 1;
	}
	return 0;
}

int hashmap_Initialization(int n)
{
	struct hashmap map = get_hashmap(n);

	if (map.tablesize == (1 << (n + 1))) {
		return 1;
	}
	return 0;
}

int hashmap_remove_RemoveElementWhichExist(int hash_value)
{
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = hash_value;
	hashmap_add(&map, &e1);

	struct hashmap_entry *removed = hashmap_remove(&map, &e1, NULL);

	if (removed->hash == hash_value) {
		return 1;
	}
	return 0;
}

int hashmap_remove_RemoveElementWhichDoesNotExist(int hash_value)
{
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = hash_value;

	struct hashmap_entry *removed = hashmap_remove(&map, &e1, NULL);

	if (removed == NULL) {
		return 1;
	}
	return 0;
}

int hashmap_put_PutElementWhichDoesNotExist(int hash_value)
{
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = hash_value;

	struct hashmap_entry *e2 = hashmap_put(&map, &e1);
	if (e2 == NULL) {
		return 1;
	}
	return 0;
}

int hashmap_put_PutElementWhichExist(int hash_value)
{
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = hash_value;

	hashmap_add(&map, &e1);

	struct hashmap_entry *e2 = hashmap_put(&map, &e1);
	if (e2->hash == hash_value) {
		return 1;
	}
	return 0;
}


int entry_equals_EqualEntry(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1;

	struct hashmap_entry e2;
	e2.hash = 1;

	int result = entry_equals(&map,&e1,&e2,NULL);
	if(result == 1){
		return 1;
	}
	return 0;
}

int entry_equals_UnequalEntry(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1;

	struct hashmap_entry e2;
	e2.hash = 2;

	int result = entry_equals(&map,&e1,&e2,NULL);
	if(result == 0){
		return 1;
	}
	return 0;
}

int entry_equals_SameEntry(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1;

	int result = entry_equals(&map,&e1,&e1,NULL);
	if(result == 1){
		return 1;
	}
	return 0;
}

int bucket_Value(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1234;

	int bucket_value = bucket(&map,&e1);
	int expected_bucket_value = 18;
	if(bucket_value == expected_bucket_value){
		return 1;
	}
	return 0;
}

int find_entry_ptr_FindPtr(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1234;
	hashmap_add(&map,&e1);
	struct hashmap_entry ** result_ptr = find_entry_ptr(&map,&e1,NULL);
	if(*result_ptr == &e1){
		return 1;
	}
	return 0;
}

int hashmap_iter_next_NextEntry(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1;
	struct hashmap_entry e2;
	e2.hash = 2;	
	hashmap_add(&map,&e1);
	hashmap_add(&map,&e2);
	struct hashmap_iter iter;
	
	hashmap_iter_init(&map, &iter);
	struct hashmap_entry *e;
	e = hashmap_iter_next(&iter);
	if(e->hash != 1){
		return 0;
	}
	e = hashmap_iter_next(&iter);
	if(e->hash != 2){
		return 0;
	}
	return 1;
}

int hashmap_partial_clear_PartialClear(int total){

	struct hashmap map = get_hashmap(0);
	for(int i=0;i<total;i++){
		struct hashmap_entry e;
		e.hash = i+1;
		hashmap_add(&map,&e);
	}
	hashmap_partial_clear_(&map,-1);

	if(map.table && map.tablesize == 64 && map.private_size == 0){
		return 1;
	}
	return 0;
}

int hashmap_clear_Clear(int total){

	struct hashmap map = get_hashmap(0);
	for(int i=0;i<total;i++){
		struct hashmap_entry e;
		e.hash = i+1;
		hashmap_add(&map,&e);
	}
	hashmap_clear_(&map,-1);

	if(map.table == NULL){
		return 1;
	}
	return 0;
}

int hashmap_get_GetEntry(){
	struct hashmap map = get_hashmap(0);

	struct hashmap_entry e1;
	e1.hash = 1234;
	hashmap_add(&map,&e1);
	struct hashmap_entry * result = hashmap_get(&map,&e1,NULL);
	if(result == &e1){
		return 1;
	}
	return 0;
}

int hashmap_get_next_GetNext(){
	struct hashmap map = get_hashmap(0);
	
	struct hashmap_entry e1;
	e1.hash = 1;
	hashmap_add(&map,&e1);

	struct hashmap_entry e2;
	e2.hash = 1;
	hashmap_add(&map,&e2);

	struct hashmap_entry e3;
	e3.hash = 1;
	hashmap_add(&map,&e3);

	struct hashmap_entry * result = hashmap_get_next(&map,&e3);
	if(result == &e2){
		return 1;
	}
	return 0;
}


int main(void)
{
	plan(31);

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
	ok(allocate_table_GrowAt(), "allocated a new hashmap and test grow at");

	ok(hashmap_add_AddElement(1), "added 1 new element to hashmap");
	ok(hashmap_add_AddElement(2), "added 2 new element to hashmap");

	ok(rehash_RehashWithSize(5), "rehash to get size: 5");
	ok(rehash_RehashWithSize(10), "rehash to get size: 10");

	ok(hashmap_Initialization(5), "initialize a hashmap");

	ok(hashmap_remove_RemoveElementWhichExist(2),
	   "Remove element in hashmap which exists");
	ok(hashmap_remove_RemoveElementWhichDoesNotExist(2),
	   "Remove element in hashmap which does not exists");

	ok(hashmap_put_PutElementWhichDoesNotExist(2),
	   "Put element which does not exist.");

	ok(hashmap_put_PutElementWhichExist(10), "Put element which exist.");

	ok(entry_equals_EqualEntry(),"Check for equal hashmap entry");
	ok(entry_equals_UnequalEntry(),"Check for unequal hashmap entry");
	ok(entry_equals_SameEntry(),"Check for same hashmap entry");

	ok(bucket_Value(),"Check for bucket value");

	ok(find_entry_ptr_FindPtr(), "Find ptr of a hashmap entry");

	ok(hashmap_iter_next_NextEntry(),"Iterate over hashmap");
	ok(hashmap_partial_clear_PartialClear(10),"Perform partial clear");
	ok(hashmap_clear_Clear(10),"Perform Clear");
	ok(hashmap_get_GetEntry(),"Get entry from hashmap");
	ok(hashmap_get_next_GetNext(),"Get next equal hashmap entry");
	return 0;
}