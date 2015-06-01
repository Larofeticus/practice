#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define H_SIZE 20

struct store 
{
  int key;
  int payload;
  struct store* next;
};

void printTable(struct store** table)
{
  int x;
  for(x = 0; x < H_SIZE; x++)
  {
    if(!table[x])
    {
      printf("X ");
    }
    else
    {
      struct store* next = table[x];
      printf("s: %d ", x);
      while(next)
      {
        printf("%d:%d, ", next->key, next->payload);
        next = next->next;
      }
    }
    printf("\n");
  }
  printf("\n");
}

int hashFunction(int key)
{
  return key % H_SIZE;
}

void save(int key, int value, struct store** table)
{
  struct store* next = NULL;
  struct store* new = NULL;
  int slot = hashFunction(key);

  new = (struct store*)malloc(sizeof(struct store));
  new->key = key;
  new->payload = value;
  new->next = NULL;

  if(!table[slot])
  {
    table[slot] = new;
    return;
  }
  next = table[slot];
  while(next->next)
  {
    next = next->next;
  }
  next->next = new;
}

int find(int key, int def, struct store** table)
{
  int slot = hashFunction(key);
  struct store* this = NULL;

  if(!table[slot])
    return def;

  this = table[slot];
  while(this)
  {
    if(this->key == key)
      return this->payload;
    this = this->next;
  }
  return def;
}

int main(int argc, char** argv)
{
  struct store** hTable = NULL;
  int x;

  hTable = (struct store**)malloc(sizeof(struct store*) * H_SIZE);
  for(x = 0; x < H_SIZE; x++)
  {
    hTable[x] = NULL;
  }

  srand(time(NULL));
  for(x = 0; x < 50; x++)
  {
    int r = rand() % 600;
    save(r, x, hTable);
  }

  printTable(hTable);

  for(x = 0; x < 50; x++)
  {
    int r = rand() % 600;
    printf("seek %d found %d\n", r, find(r, -1, hTable));
  }

  return 0;
}
