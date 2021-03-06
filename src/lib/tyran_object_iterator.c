#include <tyranscript/tyran_config.h>
#include <tyranscript/tyran_object_iterator.h>
#include <tyranscript/tyran_object_key.h>

tyran_object_iterator* tyran_object_iterator_new()
{
	tyran_object_iterator* iterator = TYRAN_CALLOC(tyran_object_iterator);
	return iterator;
}

void tyran_object_iterator_free(tyran_object_iterator* iterator)
{
	int i;
	for (i = 0; i < iterator->count; i++) {
		tyran_object_key_free(iterator->keys[i]);
	}
	tyran_free(iterator->keys);
	tyran_free(iterator);
}

void tyran_object_iterator_insert(tyran_object_iterator* iterator, const tyran_object_key* key)
{
	if (iterator->count >= iterator->allocated_size) {
		iterator->allocated_size++;
		iterator->allocated_size *= 2;
		iterator->keys = (const tyran_object_key**)tyran_realloc(iterator->keys, iterator->allocated_size * sizeof(tyran_object_key*) );
	}
	iterator->keys[iterator->count] = tyran_object_key_clone(key);
	iterator->count++;
}
