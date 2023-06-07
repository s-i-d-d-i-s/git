#include "../khash.h"

#include <tap/basic.h>

#include "../git-compat-util.h"

int test_acx31_hash_string() {
  const char *str = "foobar";
  khint_t value = __ac_X31_hash_string(str);
  khint_t expected = 3026088333;
  return value == expected;
}

int test_ac_hash_upper() {
  const double expected = 0.77;
  return expected == __ac_HASH_UPPER;
}

KHASH_INIT(str, const char *, int *, 1, kh_str_hash_func, kh_str_hash_equal);

int test_init() {
  kh_str_t *hashmap = kh_init_str();
  return hashmap != NULL;
}

int test_put() {
  int64_t ret, pos, value;
  kh_str_t *hashmap = kh_init_str();
  pos = kh_put_str(hashmap, "test_key", &ret);
  value = 14;
  if (ret) {
    kh_key(hashmap, pos) = xstrdup("test_key");
    kh_value(hashmap, pos) = &value;
  } else {
    return 0;
  }
  return *kh_value(hashmap, pos) == value;
}

int test_get() {
  int64_t ret, pos, value, value_pos, returned_value;
  kh_str_t *hashmap = kh_init_str();
  pos = kh_put_str(hashmap, "test_key", &ret);
  value = 14;
  if (ret) {
    kh_key(hashmap, pos) = xstrdup("test_key");
    kh_value(hashmap, pos) = &value;
  } else {
    return 0;
  }
  value_pos = kh_get_str(hashmap, "test_key");
  returned_value = *kh_value(hashmap, value_pos);
  return returned_value == value;
}

int test_delete() {
  int64_t ret, ret, value, current_size, pos;
  kh_str_t *hashmap = kh_init_str();
  pos = kh_put_str(hashmap, "test_key", &ret);
  value = 14;
  if (ret) {
    kh_key(hashmap, pos) = xstrdup("test_key");
    kh_value(hashmap, pos) = &value;
  } else {
    return 0;
  }
  current_size = hashmap->size;
  kh_del_str(hashmap, pos);
  return (hashmap->size + 1 == current_size && !kh_exist(hashmap, pos));
}

int test_update_value_after_deleting() {
  int64_t ret, pos1, value1, pos2, value2, value_pos, returned_value;
  kh_str_t *hashmap = kh_init_str();

  pos1 = kh_put_str(hashmap, "test_key", &ret);
  value1 = 14;
  if (ret) {
    kh_key(hashmap, pos1) = xstrdup("test_key");
    kh_value(hashmap, pos1) = &value1;
  } else {
    return 0;
  }

  kh_del_str(hashmap, pos1);
  pos2 = kh_put_str(hashmap, "test_key", &ret);
  value2 = 15;

  if (ret) {
    kh_key(hashmap, pos2) = xstrdup("test_key");
    kh_value(hashmap, pos2) = &value2;
  } else {
    return 0;
  }

  value_pos = kh_get_str(hashmap, "test_key");
  returned_value = *kh_value(hashmap, value_pos);
  return returned_value == value2;
}

int test_update_value_before_deleting() {
  int64_t ret, pos1, value1, pos2, value2;
  kh_str_t *hashmap = kh_init_str();

  pos1 = kh_put_str(hashmap, "test_key", &ret);
  value1 = 14;
  if (ret) {
    kh_key(hashmap, pos1) = xstrdup("test_key");
    kh_value(hashmap, pos1) = &value1;
  } else {
    return 0;
  }

  pos2 = kh_put_str(hashmap, "test_key", &ret);
  value2 = 15;

  return ret == 0;
}

int test_size() {
  int64_t ret, pos1, value1, pos2, value2, pos3, value3;
  kh_str_t *hashmap = kh_init_str();

  pos1 = kh_put_str(hashmap, "test_key1", &ret);
  value1 = 14;
  if (ret) {
    kh_key(hashmap, pos1) = xstrdup("test_key1");
    kh_value(hashmap, pos1) = &value1;
  } else {
    return 0;
  }

  pos2 = kh_put_str(hashmap, "test_key2", &ret);
  value2 = 15;
  if (ret) {
    kh_key(hashmap, pos2) = xstrdup("test_key2");
    kh_value(hashmap, pos2) = &value2;
  } else {
    return 0;
  }

  pos3 = kh_put_str(hashmap, "test_key3", &ret);
  value3 = 16;
  if (ret) {
    kh_key(hashmap, pos3) = xstrdup("test_key3");
    kh_value(hashmap, pos3) = &value3;
  } else {
    return 0;
  }

  return kh_size(hashmap) == 3;
}

int main(void) {
  plan(9);

  ok(test_acx31_hash_string(), "__ac_X31_hash_string works");
  ok(test_ac_hash_upper(), "__ac_HASH_UPPER has correct value");
  ok(test_init(), "Initialize hashmap");
  ok(test_put(), "Put Key-Value pair");
  ok(test_get(), "Get the value from hashmap");
  ok(test_delete(), "Delete the key-value from hashmap");
  ok(test_update_value_after_deleting(),
     "Update Value of a Key after deleting");
  ok(test_update_value_before_deleting(),
     "Update Value of a Key before deleting");
  ok(test_size(), "Test if 3 elements are present in hashmap");

  return 0;
}