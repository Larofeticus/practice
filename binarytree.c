#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct node
{
  int payload;
  int color;
  struct node* parent;
  struct node* lchild;
  struct node* rchild;
};

struct node* newNode()
{
  struct node* out = (struct node*)malloc(sizeof(struct node));
  out->payload = 0;
  out->color = 1;
  out->parent = NULL;
  out->lchild = NULL;
  out->rchild = NULL;
  return out;
}

void freeNode(struct node* n)
{
  free(n);
}

void freeTree(struct node* head)
{
  if(head->lchild)
  {
    freeTree(head->lchild);
  }
  if(head->rchild)
  {
    freeTree(head->rchild);
  }
  free(head);
}

void printNode(struct node* n)
{
  printf("%d %s\n", n->payload, n->color == 0 ? "black" : "red");
}

void printInOrder(struct node* head, int layer)
{
  int x;
  if(head->lchild)
  {
    printInOrder(head->lchild, layer+1);
  }
  for(x = 0; x < layer; x++)
    printf("\t");
  printNode(head);
  if(head->rchild)
  {
    printInOrder(head->rchild, layer+1);
  }
}

void rotateLeft(struct node* down)
{
  struct node* parent = down->parent;
  struct node* up = down->rchild;
  struct node* mSub = up->lchild;

  if(parent->lchild == down)
  {
    parent->lchild = up;
  }
  else
  {
    parent->rchild = up;
  }
  up->parent = parent;

  down->parent = up;
  up->lchild = down;

  down->rchild = mSub;
  mSub->parent = down;
}

void rotateRight(struct node* down)
{
  struct node* parent = down->parent;
  struct node* up = down->lchild;
  struct node* mSub = up->rchild;

  if(parent->rchild == down)
  {
    parent->rchild = up;
  }
  else 
  {
    parent->lchild = up;
  }
  up->parent = parent;

  down->parent = up;
  up->rchild = down;

  down->lchild = mSub;
  mSub->parent = down;
}

void insertColorBalance(struct node* n)
{
  printf("open %d\n", n->payload);

  struct node* p = n->parent;
  struct node* g = NULL;
  struct node* u = NULL;

  if(p == NULL) //at the root, make it black
  {
    n->color = 0;
    return;
  }

  printf("mark\n");
  g = p->parent;

  if(p->color == 0)
  {
    return;
  }

  printf("mark2\n");
  printf("g %d\n", g);
  printf("g lc %d\n", g->lchild);
  printf("g rc %d\n", g->rchild);

  printf("mark4\n");
  printf("2 g p %d %d\n", g, p);

  if(p == g->lchild)
  {
    u = g->rchild;

    if(g->lchild && g->rchild && g->lchild->color == 1 && g->rchild->color == 1)
    {
      printf("mark1.5\n");
      p->color = 0;
      u->color = 0;
      g->color = 1;
      printf("mark3\n");
      insertColorBalance(g);
      return;
    }

    printf("mark5\n");
    printf("p %d\n", p);
    printf("u %d\n", u);
    if(p->color == 1 && (!u || u->color == 0) && p->rchild == n)
    {
      printf("mark6\n");
      rotateLeft(p);
      printf("mark7\n");
    }
    printf("mark8\n");
    rotateRight(g);
    printf("mark9\n");
    p->color = 0;
    g->color = 1;
  }
  else //p == g->rchild
  {
    printf("mark10\n");
    u = g->lchild;
    printf("mark11\n");
    printf("1 g %d\n", g);
    printf("1 g lc %d\n", g->lchild);
    printf("1 g rc %d\n", g->rchild);
    if(g->lchild && g->rchild && g->lchild->color == 1 && g->rchild->color == 1)
    {
      printf("mark1.5\n");
      p->color = 0;
      u->color = 0;
      g->color = 1;
      printf("mark3\n");
      insertColorBalance(g);
      return;
    }
    printf("mark12\n");
    printf("p %d\n", p);
    printf("u %d\n", u);
    if(p->color == 1 && (!u || u->color == 0) && p->lchild == n)
    {
      rotateRight(p);
    }
    rotateLeft(g);
    p->color = 0;
    g->color = 1;
  }
  printf("markmark\n");
}

void deleteColorBalance(struct node* n)
{

}

struct node* insert(struct node* head, int payload)
{
  if(head == NULL)
  {
    struct node* out = newNode();
    out->payload = payload;
    insertColorBalance(out);
    return out;
  }

  if(payload > head->payload)
  {
    if(head->lchild == NULL)
    {
      struct node* out = newNode();

      out->parent = head;
      head->lchild = out;
      out->payload = payload;

      //insertColorBalance(out);
      return(out);
    }
    else
    {
      return insert(head->lchild, payload);
    }
  }
  else
  {
    if(head->rchild == NULL)
    {
      struct node* out = newNode();

      out->parent = head;
      head->rchild = out;
      out->payload = payload;

      //insertColorBalance(out);
      return(out);
    }
    else
    {
      return insert(head->rchild, payload);
    }
  }
}

int main(int argc, char** argv)
{
  struct node* head;
  int x;

  srand(time(NULL));

  head = insert(NULL, rand() % 10000);

  for(x = 0; x < 10; x++)
  {
    insert(head, rand() % 10000);
  }

  printInOrder(head, 0);

  freeTree(head);

  return 0;
}
