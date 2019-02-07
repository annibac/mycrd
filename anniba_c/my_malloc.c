#include "my_malloc.h"

void free(void *addr)
{
  if(!addr)
    {
      printf("No ptr");
      return;
    }
  t_block *block;
  block = (t_block *)addr;
  if(block->is_free == 1)
    block->is_free = 0;
}

t_block *create_new_page(t_block *last, size_t size)
{
  printf("In create new page \n");
  t_block *block;
  int m_ps;
  
  block = sbrk(0);
  if(size > PAGE_SIZE)
    m_ps = size + S_BLOCK_SIZE;
  else
    m_ps = PAGE_SIZE + S_BLOCK_SIZE;
  
  if(sbrk(m_ps) == (void *)-1)
    return NULL;
  
  block->size = m_ps;
  block->is_free = 1;
  block->next = NULL;

  if(last)
    last->next = block;

  return block;
}

t_block* internal_get_free_block(t_block **last, size_t size)
{
  printf("In internal free block \n");
  t_block *current;
  current = BASE_BLOCK;

  while(current && ((current->size != size+S_BLOCK_SIZE && current->is_free == 1) || (current->size >= size+S_BLOCK_SIZE && current->is_free == 1 && current->next == NULL)))
    {
      *last = current;
      current = current->next;
    }
  //printf("current : %x \n", current);
  //printf("last : %x \n", (current-1));
  return (current);
}


t_block *split_page(t_block *block, size_t size)
{
  printf("In split page \n");
  t_block *new_block;
  
  new_block = (t_block *)(unsigned int*)block + size;
  new_block->size = block->size - size - S_BLOCK_SIZE;
  new_block->next = NULL;
  block->size = size;
  block->is_free = 1;
  block->next = new_block;
  return (new_block-1);
}

t_block *check_size(t_block *block, size_t size)
{
  printf("Check size \n");
  if(block->size == size)
    {
      block->is_free = 1;
      return block;
    }
  else
    {
      block = split_page(block, size);
      return block;
    }
}

t_block *create_and_split(t_block *block, t_block *last, size_t size)
{
  printf("Create and split \n");
  if(last)
    block = create_new_page(last, size);
  else
    block = create_new_page(NULL, size);
  if(block)
    {
      block = split_page(block, size);
      if(!BASE_BLOCK)
	BASE_BLOCK = block;
      if(!block)
	return NULL;
      return block;
    }
  else
    return NULL;
}

void *malloc(size_t size)
{
  t_block *block;
  t_block *last;
  unsigned int i;

  if (size <= 0)
    return NULL;
  
  i = 0;
  while (i < size)
    i += 8;
  size = i;
  
  block = NULL;
  if(BASE_BLOCK)
    {
      last = BASE_BLOCK;
      block = internal_get_free_block(&last, size);
      if(block && (block->size >= size))
	block = check_size(block, size);
      else
	block = create_and_split(block, last, size);
      return block;
    }
  else
    {
      block = create_and_split(block, NULL, size);
      return block;
    }
  return NULL;
}

/*int main()
{
  
  int i;
  
  char *ptr2 = my_malloc(3000);
  char *ptr3 = my_malloc(5000);
  char *ptr4 = my_malloc(10000);
  char *ptr5 = my_malloc(100000);
  
  
  for (i = 1; i < 500; i += 10){
    char *ptr;
    ptr = my_malloc(i);
    printf("ptr : 0x%x\n", ptr);
    ptr = "coucoucouxdcfgvhjlmlkj";  
  }
  
   // printf("Ox%x\n", sbrk(0));
  // printf("Ox%x\n", sbrk(600));
  // printf("Ox%x\n", sbrk(0));
   
  return 0;
}
*/
