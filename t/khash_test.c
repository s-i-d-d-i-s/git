#include <tap/basic.h>
#include "../khash.h"

int khash_testACX31HashString(){
    const char * str = "foobar";
    khint_t value = __ac_X31_hash_string(str);
    khint_t expected = 3026088333;
    if(value == expected)
        return 1;
    return 0;
}

int khash_testAC_HASH_UPPER(){
    const double expected = 0.77;
    if(expected == __ac_HASH_UPPER){
        return 1;
    }
    return 0;
}

KHASH_INIT(str, const char *, int *, 1, kh_str_hash_func, kh_str_hash_equal);

int khash_testInit(){
    kh_str_t * hashmap = kh_init_str();
    if(hashmap != NULL){
        return 1;
    }
    return 0;
}

int khash_testPut(){
    kh_str_t * hashmap = kh_init_str();
    int ret;
    int pos = kh_put_str(hashmap,"test_key",&ret);
    int value = 14;
    if(ret){
        kh_key(hashmap, pos) = xstrdup("test_key");
		kh_value(hashmap, pos) = &value;
    }else return 0;
    if(*kh_value(hashmap,pos) == value){
        return 1;
    }
    return 0;
}

int khash_testGet(){
    kh_str_t * hashmap = kh_init_str();
    int ret;
    int pos = kh_put_str(hashmap,"test_key",&ret);
    int value = 14;
    if(ret){
        kh_key(hashmap, pos) = xstrdup("test_key");
		kh_value(hashmap, pos) = &value;
    }else return 0;
    int value_pos = kh_get_str(hashmap,"test_key");    
    int returned_value = *kh_value(hashmap,value_pos);
    if(returned_value == value){
        return 1;
    }
    return 0;
}

int khash_testDelete(){
    kh_str_t * hashmap = kh_init_str();
    int ret;
    int pos = kh_put_str(hashmap,"test_key",&ret);
    int value = 14;
    if(ret){
        kh_key(hashmap, pos) = xstrdup("test_key");
		kh_value(hashmap, pos) = &value;
    }else return 0;
    int current_size = hashmap->size;
    kh_del_str(hashmap,pos);
    if(hashmap->size + 1 == current_size && !kh_exist(hashmap, pos)){
        return 1;
    }
    return 0;
}

int khash_testUpdateValueAfterDeleting(){
    kh_str_t * hashmap = kh_init_str();
    int ret;
    int pos1 = kh_put_str(hashmap,"test_key",&ret);
    int value1 = 14;
    if(ret){
        kh_key(hashmap, pos1) = xstrdup("test_key");
		kh_value(hashmap, pos1) = &value1;
    }else return 0;

    kh_del_str(hashmap,pos1);
    int pos2 = kh_put_str(hashmap,"test_key",&ret);
    int value2 = 15;
    
    if(ret){
        kh_key(hashmap, pos2) = xstrdup("test_key");
		kh_value(hashmap, pos2) = &value2;
    }else return 0;

    int value_pos = kh_get_str(hashmap,"test_key");    
    int returned_value = *kh_value(hashmap,value_pos);
    if(returned_value == value2){
        return 1;
    }
    return 0;
}

int khash_testUpdateValueBeforeDeleting(){
    kh_str_t * hashmap = kh_init_str();
    int ret;
    int pos1 = kh_put_str(hashmap,"test_key",&ret);
    int value1 = 14;
    if(ret){
        kh_key(hashmap, pos1) = xstrdup("test_key");
		kh_value(hashmap, pos1) = &value1;
    }else return 0;

    int pos2 = kh_put_str(hashmap,"test_key",&ret);
    int value2 = 15;
    
    if(ret == 0){
        return 1;
    }
    return 0;
}

int khash_testSize(){
    kh_str_t * hashmap = kh_init_str();
    int ret;
    int pos1 = kh_put_str(hashmap,"test_key1",&ret);
    int value1 = 14;
    if(ret){
        kh_key(hashmap, pos1) = xstrdup("test_key1");
		kh_value(hashmap, pos1) = &value1;
    }else return 0;

    int pos2 = kh_put_str(hashmap,"test_key2",&ret);
    int value2 = 15;
    if(ret){
        kh_key(hashmap, pos2) = xstrdup("test_key2");
		kh_value(hashmap, pos2) = &value2;
    }else return 0;


    int pos3 = kh_put_str(hashmap,"test_key3",&ret);
    int value3 = 16;
    if(ret){
        kh_key(hashmap, pos3) = xstrdup("test_key3");
		kh_value(hashmap, pos3) = &value3;
    }else return 0;

    if(kh_size(hashmap) == 3){
        return 1;
    }
    return 0;
}

int main(void){
    plan(9);
    
    ok(khash_testACX31HashString(),"__ac_X31_hash_string works");
    ok(khash_testAC_HASH_UPPER(),"__ac_HASH_UPPER has correct value");
    ok(khash_testInit(), "Initialize hashmap");
    ok(khash_testPut(), "Put Key-Value pair");
    ok(khash_testGet(), "Get the value from hashmap");
    ok(khash_testDelete(), "Delete the key-value from hashmap");
    ok(khash_testUpdateValueAfterDeleting(), "Update Value of a Key after deleting");
    ok(khash_testUpdateValueBeforeDeleting(), "Update Value of a Key before deleting");
    ok(khash_testSize(),"Test if 3 elements are present in hashmap");

    return 0;
}