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
  t_block *block;
  int m_ps;
  
  block = sbrk(0);
  if(size > PAGE_SIZE)
    m_ps = size;
  else
    m_ps = PAGE_SIZE;

  if(sbrk(m_ps + S_BLOCK_SIZE) == (void *)-1)
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
  t_block *current;
  current = BASE_BLOCK;

  while(current && ((current->size == size && current->is_free == 1) || (current->size >= size && current->is_free == 1 && current->next == NULL)))
    {
      *last = current;
      current = current->next;
    }
  return (current);
}


t_block *split_page(t_block *block, size_t size)
{
  t_block *new_block;

  new_block = block + size;
  new_block->size = block->size - size - S_BLOCK_SIZE;
  block->size = size;
  block->is_free = 1;
  block->next = new_block;
  return new_block;
}

t_block *check_size(t_block *block, size_t size)
{
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
  //  size = ALIGN(size);

  if (size <= 0)
    return NULL;
  
  block = NULL;
  if(BASE_BLOCK)
    {
      last = BASE_BLOCK;
      block = internal_get_free_block(&last, size);
      if(block)
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
  char *ptr;

  ptr = my_malloc(800);
  printf("ptr : 0x%x\n", ptr);
  ptr = "coucoucouxdcfgvhjlmlkj";
  
  return 0;
}

*/
