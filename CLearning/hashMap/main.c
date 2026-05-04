#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "hashMap.h"

/*************************************************************
*						  COMMENT                            *
**************************************************************/

int main(void)
{
	HashMap* map = hashmap_create();

	
	hashmap_put(map, "cx1", "xxx");
	hashmap_put(map, "cx2", "xxx");
	hashmap_put(map, "cx3", "xxx");
	hashmap_put(map, "cx4", "xxx");
	hashmap_put(map, "cx5", "xxx");
	hashmap_put(map, "cx6", "xxx");
	hashmap_put(map, "cx7", "xxx");
	hashmap_put(map, "cx8", "xxx");
	hashmap_put(map, "cx9", "xxx");
	hashmap_put(map, "cx10", "xxx");
	hashmap_put(map, "cx11", "xxx");

	/*V v1 = hashmap_get(map, "lcat");
	V v2 = hashmap_get(map, "ebo");

	hashmap_delete(map, "ebo");
	hashmap_delete(map, "lcat");*/

	return 0;
}