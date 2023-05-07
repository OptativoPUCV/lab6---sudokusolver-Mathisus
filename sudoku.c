#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  int validNumbers[10] = {0,0,0,0,0,0,0,0,0,0};

  int i,j;

  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      int currentNumber = n->sudo[i][j];

      if(currentNumber != 0)
      {
        if(validNumbers[currentNumber] == 0)
        {
          validNumbers[currentNumber] = 1;
        }
        else
        {
          return 0;
        }
      }
    }

    for(int k = 0; k < 10; k++)
    {
      validNumbers[k] = 0;
    }
  }

  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      int currentNumber = n->sudo[j][i];

      if(currentNumber != 0)
      {
        if(validNumbers[currentNumber] == 0)
        {
          validNumbers[currentNumber] = 1;
        }
        else
        {
          return 0;
        }
      }
    }

    for(int k = 0; k < 10; k++)
    {
      validNumbers[k] = 0;
    }
  }

  for(int k = 0; k < 9; k++)
  {
    int p;

    for(p = 0; p < 9; p++)
    {
      int x = (k / 3) * 3 + (p / 3);
      int y = (k % 3) * 3 + (p % 3);

      int currentNumber = n->sudo[x][y];

      if(currentNumber != 0)
      {
        if(validNumbers[currentNumber] == 0)
        {
          validNumbers[currentNumber] = 1;
        }
        else
        {
          return 0;
        }
      }
    }

    for(int k = 0; k < 10; k++)
    {
      validNumbers[k] = 0;
    }
  }

  return 1;

}


List* get_adj_nodes(Node* n)
{
  List* list=createList();

  int i,j,k;
  int encontrado = 0;

  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      if(n->sudo[i][j] == 0)
      {
        encontrado = 1;

        for(k = 1; k <= 9; k++)
        {
          Node* new = copy(n);
          new->sudo[i][j] = k;
          
          if(is_valid(new))
          {
            pushBack(list, new);
          }
          else
          {
            free(new);
          }
        }

        break;
      }
    }

    if(encontrado)
    {
      break;
    }
  }

  return list;
}

int is_final(Node* n)
{
  int i,j;

  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      if(n->sudo[i][j] == 0)
      {
        return 0;
      }
    }
  }

  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* stack = createStack();
  push(stack, initial);

  (*cont) = 0;

  while(is_empty(stack) == 0)
  {
    Node* firstNode = top(stack);
    pop(stack);

    if(is_final(firstNode))
    {
      return firstNode;
    }

    List* adjacentNodes = get_adj_nodes(firstNode);

    Node* currentNode = first(adjacentNodes);

    while(currentNode != NULL)
    {
      push(stack, currentNode);
      currentNode = next(adjacentNodes);
    }

    (*cont)++;
  }
  
  return NULL;
}




int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}