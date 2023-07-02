#include <stdio.h>/* for prints*/
#include "hashSet.h"
#define TRUE 1
#define FALSE 0

/*********** Hash function ***********/
static size_t HashFuncSizeT(void* _element);

/*********** compare function ***********/
static int HashIntIsEqual(void* _a , void* _b);


static void testCreateNoremal();

static void testDestroy();
static void testDoubleDestroy();

static void testInsertNoremal();
static void testInsert();

static void testRemove();

int main(void)
{
	testCreateNoremal();

	testDestroy();
	testDoubleDestroy();
	
	testInsertNoremal();
	testInsert();
	
	 testRemove();
	
	return 1;
}

static void PrintInt( void* _element)
{
	printf("%d \n" , *(int*)_element);

}


static void testRemove()
{
	Hash* h;
	int item;
	int *data= &item;
	size_t a =13 , b = 26 , c = 1, d = 4, e = 5;
	h =  HashCreate(10, HashFuncSizeT, HashIntIsEqual);
	HashInsert(h, &a);
	HashInsert(h, &b);
	HashInsert(h, &c);
	HashInsert(h, &d);
	HashInsert(h, &e);
	HashPrint(h, PrintInt);
	printf("\n-----------------\n");
	HashRemove(h, &a, (void*)&data);
	
		HashPrint(h, PrintInt);
	printf("\n-----------------\n");
}



static void testInsert()
{
	Hash* h;
	size_t a =13 , b = 26 , c = 1, d = 4, e = 5;
	h =  HashCreate(10, HashFuncSizeT, HashIntIsEqual);
	HashInsert(h, &a);
	HashInsert(h, &b);
	HashInsert(h, &c);
	HashInsert(h, &d);
	HashInsert(h, &e);
	HashPrint(h, PrintInt);

}



static void testInsertNoremal()
{
	Hash* h;
	int a =7 , b = 3 , c = 9, d = 20, e = 1, f =8;
	h =  HashCreate(10, HashFuncSizeT, HashIntIsEqual);
	if (HashInsert(h, &a) == SET_SUCCESS)
	 {
	 	printf("test insert  normal -PASS\n");
	 }else
	 {
	 	printf("test insert  normal -FAIL\n");
	 }
}


static void testDoubleDestroy()
{
	Hash* h;
	h =  HashCreate(10, HashFuncSizeT, HashIntIsEqual);
	HashDestroy(&h , NULL);
	HashDestroy(&h , NULL);
	printf("test Double destroy -PASS\n");
}

static void testDestroy()
{
	Hash* h;
	h =  HashCreate(10, HashFuncSizeT, HashIntIsEqual);
	HashDestroy(&h , NULL);
	printf("test destroy -PASS\n");
}

static size_t HashFuncSizeT(void* _element)
{
	return *(size_t*)_element;
}


static int HashIntIsEqual(void* _a , void* _b)
{
	if (*(int*)_a == *(int*)_b)
	{
		return TRUE;
	}	
	return FALSE;
}

static void testCreateNoremal()
{
	Hash* h;
	h =  HashCreate(10, HashFuncSizeT, HashIntIsEqual);
	if (h  != NULL)
	 {
	 	printf("test create  normal -PASS\n");
	 }else
	 {
	 	printf("test create  normal -FAIL\n");
	 }
	 HashDestroy(&h , NULL);
}

