#ifndef __HASH_SET_H__
#define __HASH_SET_H__


typedef struct Hash Hash;

/** this function get a data, make manipulation of the data, and return size_t number*/
typedef size_t (*HashFunction)(void* _data);

/** this function get a two element return
return 1 if they are the same,
return 0 if they are the different.
*/
typedef int (*EqualityFunction)(void* _firstData, void* _secondData);

typedef enum HashSet_Result {
SET_SUCCESS = 0,
/** Uninitialized HasSeterror*/
SET_UNINITIALIZED,
/** Duplicate key error */
SET_KEY_DUPLICATE,
/** Key not found */
SET_KEY_NOT_FOUND,
/**No more space in HashSe */ 
SET_OVERFLOW, 
SET_UNDERFLOW
}HashSet_Result;

/*description- this function create a structure of HashSet
input- size -the maximum size of the item that can insert to the structure.
_hashFunction -fanction that make the manipulation of the data.
_equalityFunction - function that check if two elements are the same or not.
output- pointer of struct
	           NULL
errors- returns NULL in case there in no memory to allocate a new structure*/
Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int (*_equalityFunction)(void*, void*));

/*description- this function delete structure of HashSet and freeing the memmory
input-_hash : A previously created Hash* returned via HashCreate.
_keyDestroy : A function to destroy the data in the tree (may be NULL if unnecessary).
_equalityFunction - function that check if two elements are the same or not.
output-  NULL
errors- NULL*/
void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data));

HashSet_Result HashInsert(Hash* _hash, void* _data);

HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data);

/*description- this function check if the key is in the struct
input-_hash : A previously created Hash* returned via HashCreate.
_key:  An _key to search in the srtuct.
output-  TRUE if the _key is found.
				FALSE if the key not found.
				NULL
errors- no errors*/
int HashIsFound(const Hash* _hash, void* _key);

size_t HashNumOfItems(const Hash* _hash);

size_t HashCapacity(const Hash* _hash);

double HashAverageRehashes(const Hash* _hash);

size_t HashMaxReHash(const Hash* _hash);

void HashPrint(const Hash* _hash, void (*PrintKey)(void*));

#endif /* __HASH_SET_H__ */
