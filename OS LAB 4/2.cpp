#include <stdio.h>
#define MEM_SIZE 32
#define RAM_SIZE  5
#define SWAP_SIZE 32
static double miss=0;
static char test[20] = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
struct page_item { // ҳ����
	int ram_addr;
	int swap_addr;
	unsigned access;
	bool present;
	bool modified;
};

static char ram[RAM_SIZE];
static char swap[SWAP_SIZE];
static struct page_item page_table[MEM_SIZE];

// ��ҳ�㷨
static int algo_swap(void)
{
	int max_access = -1;
	int max_access_page = -1;
	for (int i = 0; i < MEM_SIZE; i++) {
		if (page_table[i].present &&(max_access == -1 || page_table[i].access > max_access)) {
			max_access = page_table[i].access;
			max_access_page = i;
		}
	}
	return max_access_page;
}

// �߼���ַladdrת��Ϊ�����ַpaddr
static int mem_access(int laddr)
{
	if (page_table[laddr].present) {
		for (int i = 0; i < MEM_SIZE; i++) {
			if (page_table[i].present) {
				page_table[i].access++;
			}
		}
		page_table[laddr].access=0;
		return page_table[laddr].ram_addr;
	}

	// ȱҳ����

	// �����ض��㷨ѡ�񱻻�����ҳ
	int page = algo_swap();
	miss++;

	// ����
	if (page_table[page].modified) { // д��
		int data = ram[page_table[page].ram_addr];
		swap[page_table[page].swap_addr] = data;
	}
	page_table[page].present = false;

	// �滻
	int paddr = page_table[page].ram_addr;
	page_table[laddr].ram_addr = paddr;
	ram[paddr] = swap[page_table[laddr].swap_addr];

	page_table[laddr].modified = false;
	page_table[laddr].present = true;
	page_table[laddr].access = 0;

	return paddr;
}

int mem_read(int addr, int *buf)
{
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	*buf = ram[paddr];

	return 0;
}

int mem_write(int addr, int buf)
{
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	ram[paddr] = buf;
	page_table[addr].modified = true;

	return 0;
}

void mem_init(void)
{
	// ȫ�����ص������ռ�
	for (int i = 0; i < MEM_SIZE; i++) {
		page_table[i].swap_addr = i;
		page_table[i].present = false;
		page_table[i].modified = false;
	}
	// ���ּ��ص��ڴ�
	for (int i = 0; i < RAM_SIZE; i++) {
		page_table[i].ram_addr = i;
		page_table[i].present = true;
		page_table[i].access = 0;
	}
}

void mem_state(void)
{
	printf("ram state:\t");
	for (int i = 0; i < RAM_SIZE; i++) {
		printf("%02x ", ram[i]);
	}
	printf("\nswap state:\t");
	for (int i = 0; i < SWAP_SIZE; i++) {
		printf("%02x ", swap[i]);
	}
	printf("\n\n");
}

void mem_test(void)
{
	for (int i = 0; i < sizeof(test); i++)
	{
		mem_write(test[i], test[i]);
		printf("%d\n", test[i]);
		mem_state();
	}
	double mi_percent = miss / (double)sizeof(test);
	printf("%.2f", mi_percent);
}

int main(int argc, const char *argv[])
{
	mem_init();
	mem_test();
	return 0;
}

