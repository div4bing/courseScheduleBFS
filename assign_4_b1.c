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
  int queueCount;
};

struct AdjQueue adjQueue;

int findNextAdjacentVertex(int headVertex, int indexFrom);    // headVertex is the head node and will search next adj from indexFrom
int enqueueNode(int addNode);
int dequeueNode(void);
int printQueue(void);
int IsQueueEmpty(void);
int IsQueueFull(void);

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

int enqueueNode(int addNode)
{
  if(IsQueueFull() == 0)
  {
    if(adjQueue.tail == MAX_COURSES-1)
    {
       adjQueue.tail = -1;    // Reset Tail
    }
    adjQueue.queue[++adjQueue.tail] = addNode;
    printf("Enqueued Node: %d on tail: %d \n", adjQueue.queue[adjQueue.tail], adjQueue.tail);
    adjQueue.queueCount++;
    return 0;
  }
  else
  {
    printf("Queue Full\n");
    return -1;
  }
  // printQueue();
}

int dequeueNode(void)
{
  int retHeadNode = 0;

  if (IsQueueEmpty() == -1)
  {
    printf("Error! Queue is Empty\n");
    return -1;
  }

  retHeadNode = adjQueue.queue[adjQueue.head];
  printf("Dequeued Node: %d on head: %d\n", retHeadNode, adjQueue.head);
  adjQueue.head++;

  if(adjQueue.head == MAX_COURSES)
  {
    adjQueue.head = 0;
  }

  adjQueue.queueCount--;
  // printQueue();
  return retHeadNode;
}

int printQueue(void)
{
  int i = 0;
  printf("Printing Queue:\n");
  for (i = 0; i < MAX_COURSES; i++)
  {
    printf(" %d ", adjQueue.queue[i]);
  }
  printf("\n");
  return 0;
}

int IsQueueEmpty(void)
{
  if (adjQueue.queueCount == 0)
  {
    printf("Error! Queue is Empty\n");
    return -1;
  }

  return 0;
}

int IsQueueFull(void)
{
  if (adjQueue.queueCount == MAX_COURSES)
  {
    printf("Error! Queue is Full\n");
    return -1;
  }

  return 0;
}

int main (int argc, char *argv[])
{
  // Initialze so that we can find bad case
  adjQueue.head = 0;
  adjQueue.tail = -1;

  int currentHeadNode = 0;
  int localCurrentHeadNode = 0;
  int vertex = 0; // Use to track current adj vertext under current head node

  // Let's start with vertex 1 which is CS1 and perform the BFS to get max level of nodes
  for (currentHeadNode = 0; currentHeadNode < MAX_COURSES; currentHeadNode++)
  {
    vertex = 0;     // Reset the vertex
    adjQueue.tail = -1;  // Reset Queue
    adjQueue.head = 0;
    localCurrentHeadNode = currentHeadNode;

    printf("Head Element: %d: \n", currentHeadNode);
    if (markDoneVertex[currentHeadNode][0] != 1)  // Current Head is not discovered yet
    {
      if (enqueueNode(currentHeadNode) == -1)
      {
        return -1;
      }
      markDoneVertex[currentHeadNode][0] = 1;
      markDoneVertex[currentHeadNode][1] = 0;

      while (IsQueueEmpty() != -1)
      {
        vertex = 0;
        localCurrentHeadNode = dequeueNode();

        //*******************************************************
        while (vertex != -1)   // If no more adj nodes found
        {
          if (vertex == 0)  // If vertex 0 then start with it else increase from last found vertex and keep searching
          {
            vertex = findNextAdjacentVertex(localCurrentHeadNode, vertex);
            printf("Vertex: %d\n", vertex);
            if (vertex == -1)
            {
              continue;
            }

            if (markDoneVertex[vertex][0] != 1)  // Current Head is not discovered yet
            {
              if (enqueueNode(vertex) == -1)
              {
                return -1;
              }

              markDoneVertex[vertex][0] = 1;
              markDoneVertex[vertex][1] = markDoneVertex[localCurrentHeadNode][1] + 1;
              if (markDoneVertex[vertex][1] > csSemesterCount)
              {
                csSemesterCount = markDoneVertex[vertex][1];
              }
            }
          }
          else
          {
            vertex = findNextAdjacentVertex(localCurrentHeadNode, vertex + 1);
            printf("Vertex: %d\n", vertex);
            if (vertex == -1)
            {
              continue;
            }
            if (markDoneVertex[vertex][0] != 1)  // Current Head is not discovered yet
            {
              if (enqueueNode(vertex) == -1)
              {
                return -1;
              }

              markDoneVertex[vertex][0] = 1;
              markDoneVertex[vertex][1] = markDoneVertex[localCurrentHeadNode][1] + 1;
              if (markDoneVertex[vertex][1] > csSemesterCount)
              {
                csSemesterCount = markDoneVertex[vertex][1];
              }
            }
          }

          if (vertex != -1)
          {
            printf("--------> %d\n", vertex+1);
          }
        }
        //********************************************************
      }
    }
    printf("\n");
  }

  printf("TOTAL SEMESTERS REQUIRED IS: %d\n", csSemesterCount+1);

  return 0;
}
