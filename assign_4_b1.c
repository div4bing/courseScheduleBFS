#include <stdio.h>
#include <stdlib.h>

#define MAX_COURSES 15

int graphAdjMatrix[MAX_COURSES][MAX_COURSES] = {{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, \
                                                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 ,0, 1, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int markDoneVertex[MAX_COURSES][2];    // Used to check if the node is discovered already or not and also stores it's level, 1st Element is Done or not and 2nd is level if done
int csSemesterCount;                   // Counts max level so far, this will give us the max number of semester it will take to complete 15 courses

struct AdjQueue
{
  int queue[MAX_COURSES];
  int head;
  int tail;
};

int findNextAdjacentVertex(int headVertex, int indexFrom);    // headVertex is the head node and will search next adj from indexFrom


int findNextAdjacentVertex(int headVertex, int indexFrom)
{
  int i = 0;

  if (headVertex >= MAX_COURSES)    // Invalid adj index, valid are 0-14
  {
    return -1;
  }

  for (i = indexFrom; i < MAX_COURSES; i++)
  {
    if (graphAdjMatrix[headVertex][i] == 1)     // Found next adjacent vertex
    {
      return i;
    }
  }

  return -1;    // Could not find next adjacent vertex
}

int main (int argc, char *argv[])
{
  struct AdjQueue adjQueue;
  int currentHeadNode = 0;
  int vertex = 0; // Use to track current adj vertext under current head node

  // vertex = findNextAdjacentVertex(3, vertex) + 1;
  // printf("Next Element: %d\n", vertex);

  // Let's start with vertex 1 which is CS1 and perform the BFS to get max level of nodes
  for (currentHeadNode = 0; currentHeadNode < MAX_COURSES; currentHeadNode++)
  {
    vertex = 0;     // Reset the vertex
    printf("Head Element: %d: ", currentHeadNode+1);
    if (markDoneVertex[currentHeadNode][0] != 1)  // Current Head is not discovered yet
    {
      while (vertex != -1)   // If no more adj nodes found
      {
        if (vertex == 0)  // If vertex 0 then start with it else increase from last found vertex and keep searching
        {
          vertex = findNextAdjacentVertex(currentHeadNode, vertex);
        }
        else
        {
          vertex = findNextAdjacentVertex(currentHeadNode, vertex + 1);
        }
        if (vertex != -1)
        {
          printf("-> %d ", vertex+1);
        }
      }
    }
    printf("\n");
  }


  return 0;
}
