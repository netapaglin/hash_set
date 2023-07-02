#include <stdio.h>/* for prints*/
#include <stdlib.h>/* for malloc*/
#include "hashSet.h"
#define FACTOR 1.3
#define TRUE 1
#define FALSE 0
#define EMPTY 0
#define NEW_EMPTY 1
#define OCCUPIED 2
#define NEW_SIZE _hash -> m_capacity
#define SIZE _hash -> m_hashSize
#define HASH_FUNC _hash -> m_hashFunction
#define REHASH _hash ->m_maxOfRehashOperations
#define IS_EQUALL _hash ->m_equalityFunction


static int CheckIfPrime(size_t _num);
static int CheckIIfFound(const Hash* _hash, void* _key);

struct Hash
{
void** m_data;
char* m_state;
size_t (*m_hashFunction)(void* _data);
int (*m_equalityFunction)(void* _firstData, void* _secondData);
size_t m_hashSize; /*original size given by the client*/
size_t m_capacity; /*real hash size */
size_t m_numOfItems; /*number of occupied places in the table*/
size_t m_maxOfRehashOperations; /*maximum amount of rehash operations
which have been done over one insertion*/
size_t m_counterOfInsertions; /*total amount of insertions into the table*/
size_t m_allRehashOperations; /*all rehash operations mutual counter*/
};

Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int (*_equalityFunction)(void*, void*))
{
	Hash* hash;
	void**  tempData;
	char* tempState;
	size_t newSize;
	if(_size == 0 ||_hashFunction == NULL || _equalityFunction == NULL)
	{
		return NULL;
	}
	hash = (Hash*)malloc( sizeof(Hash));
	 if(hash == NULL)
	 {
		 return NULL;
	 }
	newSize = _size * FACTOR;
	if (newSize > 2)
	{
		while(CheckIfPrime(newSize) == FALSE)
		{
			++newSize;
		}  	
	}
	 tempData = (void**)malloc( newSize * sizeof(void*));
	  if(tempData == NULL)
	  {
	  		free(hash);
	    	return NULL;
	  }
	  tempState = (char*)calloc( newSize , sizeof(char));
	  if(tempData == NULL)
	  {
	  		free(hash);
	  		free(tempData);
	    	return NULL;
	  }
	  hash -> m_data = tempData;
	  hash -> m_state = tempState;	  
	  hash -> m_hashFunction = _hashFunction;
	  hash -> m_equalityFunction = _equalityFunction;
	  hash -> m_hashSize = _size;
	  hash -> m_capacity = newSize; 
	  hash ->m_numOfItems = 0;
	  hash ->m_maxOfRehashOperations = 0;
	  hash ->m_counterOfInsertions = 0;
	  hash ->m_allRehashOperations = 0;
	  return hash;
}

void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data))
{
	size_t i;
	if(_hash == NULL || *_hash == NULL )
	{
		return ;
	}
	if(_keyDestroy != NULL )
	{
		for(i=0 ; i <(*_hash)  -> m_numOfItems ; ++i)
		{
			_keyDestroy((*_hash) -> m_data[i]);			
		}
	}
	free((*_hash) -> m_data);
	free((*_hash) -> m_state);
	free(*_hash);
	*_hash = NULL; /*in the tests - check null*/
}

int HashIsFound(const Hash* _hash, void* _key)
{
	if(_hash != NULL && _key != NULL)
	{
	if (CheckIIfFound(_hash , _key) == NEW_SIZE)
	{
		return  TRUE;
	}
	return  FALSE;
	}
}

HashSet_Result HashInsert(Hash* _hash, void* _data)
{
	size_t index, tempIndex , rehashCounter  = 0;
	if(_hash == NULL || _data == NULL )
	{
		return SET_UNINITIALIZED;
	}
	if(_hash -> m_hashSize == _hash -> m_numOfItems)
	{
		return SET_OVERFLOW ;
	}
	if (CheckIIfFound(_hash, _data) != NEW_SIZE)
	{
		return SET_KEY_DUPLICATE;
	}
	tempIndex = (HASH_FUNC(_data));
	index = tempIndex % NEW_SIZE;
	while(_hash -> m_state[index] == OCCUPIED)
	{
			printf( "_data %ld\n", *(size_t*)_data);
		index = ( index+ 1) % NEW_SIZE;
			printf( "hashfunc %ld\n", HASH_FUNC(_data)+1);
			printf( "NEW_SIZE %ld\n", NEW_SIZE);
		++ rehashCounter;
		printf( "rehashCounter %ld\n", rehashCounter);
	}
	printf( "index %ld\n", index);
	_hash -> m_data[index] = _data;
	_hash -> m_state[index] = OCCUPIED;
	++ _hash -> m_counterOfInsertions;
	++ _hash -> m_numOfItems;
	if(rehashCounter > REHASH )
	{
		REHASH = rehashCounter;
	}	
	return SET_SUCCESS;
}

HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data)
{
	int index;
	if(_hash == NULL || _data == NULL  || _key == NULL)
	{
		return SET_UNINITIALIZED;
	}
	if(_hash -> m_numOfItems == 0)
	{
		return SET_UNDERFLOW;
	}
	index = (CheckIIfFound(_hash, _key));
	if (index == NEW_SIZE)
	{
		return SET_KEY_NOT_FOUND;
	}
	_hash -> m_state[index] = NEW_EMPTY;
	-- _hash -> m_numOfItems;
	*_data = _hash -> m_data[index];
	return SET_SUCCESS;
}

size_t HashNumOfItems(const Hash* _hash)
{
	if(_hash != NULL)
	{
		return _hash-> m_numOfItems;
	}
}

size_t HashCapacity(const Hash* _hash)
{
	if(_hash != NULL)
	{
		return _hash-> m_capacity;
	}
}

double HashAverageRehashes(const Hash* _hash)
{
	double num;
	if(_hash != NULL)
	{
		num = (_hash-> m_allRehashOperations) / (_hash-> m_counterOfInsertions);
		return num;
	}
}

/**************** static function ************************/


static int CheckIIfFound(const Hash* _hash, void* _key)
{
	size_t i , index , tempIndex;
	tempIndex = HASH_FUNC(_key);
	index = tempIndex % NEW_SIZE;
	if (_hash -> m_state[index] == EMPTY )
	{
		return NEW_SIZE;
	}
	if (IS_EQUALL(_hash -> m_data[index] ,  _key) == TRUE)
	{
		return index;
	}else 
	{
		for(i= 0; i < REHASH ; ++i)
		{
			index = (tempIndex + i + 1)% NEW_SIZE;
			if (_hash -> m_state[index] == EMPTY)
			{
				return NEW_SIZE;
			}
			if (IS_EQUALL(_hash -> m_data[index] ,  _key) == TRUE )
			{
				return index;
			}	
		}
	}
	return NEW_SIZE;
}

static int CheckIfPrime(size_t _num)
{
	size_t i ;
	for(i = 2 ; i < _num / 2; ++i)
	{
		if(_num% i == 0) 
		{
     		return FALSE;
     	}
	}
	return TRUE;
}

void HashPrint(const Hash* _hash, void (*PrintKey)(void*))
{
	size_t i;
	if (_hash != NULL)
	{
		for(i = 0; i < NEW_SIZE ; ++ i)
		{
			if(_hash -> m_state[i] == OCCUPIED )
			{
					printf(" index %ld - ", i);
					PrintKey(_hash -> m_data[i]);
			}
		}
	}
}


