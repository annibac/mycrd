#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct s_block {
  size_t size;
  int is_free;
  struct s_block *next;
} t_block;

#define S_BLOCK_SIZE sizeof(struct s_block)+4
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1)
#define PAGE_SIZE 2048
t_block *BASE_BLOCK = NULL;


/* Prototype */

void free(void *addr);
t_block *create_new_page(t_block *last, size_t size);
t_block *internal_get_free_block(t_block **last,size_t size);
t_block *split_page(t_block *block, size_t size);
t_block* check_size(t_block *block, size_t size);
t_block *create_and_split(t_block *block, t_block *last, size_t size);
void *malloc(size_t size);
