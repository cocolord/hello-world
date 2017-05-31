#include <stdio.h>

#define MEM_SIZE 128
#define MINBLK 16

static char mem[MEM_SIZE];

struct block
{
	struct block *next;
	size_t length;
	//可变长数组
	char data[0];
};
//declare free_list
static struct block *free_list = NULL;

void malloc_init(void)
{
	//initialize free_list
	free_list = (struct block *)mem;
	free_list->next = NULL;
	free_list->length = MEM_SIZE - sizeof(struct block);
}
//first fit
void *malloc(size_t size)
{
	//对齐
	size = (size + 7) & ~7;
	struct block *prev = (struct block *)&free_list;
	struct block *cur = free_list;

	while (cur != NULL)
	{
		if (cur->length >= size)
			break;
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
		return NULL;

	if ((cur->length - size) >= MINBLK)
	{
		struct block *temp = (struct block *)(cur->data + size);
		temp->next = cur->next;
		temp->length = cur->length - size - sizeof(struct block);
		prev->next = temp;
		cur->length = size;
	}
	else
	{
		prev->next = cur->next;
	}

	return cur->data;
}

void free(struct block *ptr)
{
	if (ptr == NULL)
		return;

	struct block *temp = (struct block *)((char *)ptr - sizeof(struct block));
	struct block *tempn = ptr + temp->length; // 和temp物理上相邻的下一个block的地址

	struct block *prev = (struct block *)&free_list;
	struct block *cur = free_list;
	char *curn; 
	// 和cur物理上相邻的下一个block的地址
	// 考虑多种情况，完成free函数

	if (cur == NULL)
	{
		temp->next = NULL;
		prev->next = temp;
	}
	else if (cur == tempn)
	{
		temp->next = tempn->next;
		temp->length += tempn->length + sizeof(struct block);
	}
	else if (cur > tempn)
	{
		temp->next = cur;
		prev->next = temp;
	}
	else
	{
		while (cur->next < temp&&cur->next != NULL)
			cur = cur->next;
		if (cur->next == NULL || cur->next > tempn)
		{
			cur->length += temp->length + sizeof(struct block);
		}
		else
		{
			cur->next = tempn->next;
			cur->length += temp->length + tempn->length + 2 * sizeof(struct block);
		}
	}
	// ... ...
}

void malloc_state(void)
{
	printf("free blocks:\n");
	struct block *ptr;
	for (ptr = free_list; ptr != NULL; ptr = ptr->next)
	{
		int i;
		printf("%p:", ptr);
		for (i = 0; i < ptr->length; i++)
		{
			printf("=");
		}
		printf(" ");
	}
	printf("\n");
}

void malloc_test(void)
{
	malloc_state();
	block *test = (struct block *)malloc(10);
	malloc_state();
	free(test);
	malloc_state();
}

int main(int argc, const char *argv[])
{
	malloc_init();

	malloc_test();
	getchar();getchar();
	return 0;
}
