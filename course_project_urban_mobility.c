#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#  define M_SIZE 10
#  define V 10
# define d 256
/**structure for routes and vehicles list(array implementation)**/
typedef struct route
{
    int distance;
    int seats;
    int fare;
    int start;
    int end;
    char type[100];


}CP;
/**structure for finding pollution of a particular vehicle(list implementation)**/
typedef struct pollution
{
    float p_level;
    char tov[15];
    struct pollution* next;
}NODE;

/**structure for finding resorts nearby once the user reaches desired destination(binary search tree implementation**/
struct Resort
{
    char name[50];
    char location[50];
    float rating;
    struct Resort *left;
    struct Resort *right;
};



/**structure for payment after the end of journey(stack implementation)**/
typedef struct stack
{

char tov[20][20];
float cost[20];
char mode_of_payment[20][20];
int top;
}PAYMENT;

/**structure for minimum spanning tree(kruskals implementation)**/
struct edge
{
    int src;
    int dest;
    int weight;
};

/**structure for printing the feedback to the user at the start of the program(simple array implementation)**/
struct Feedback
{
    char username[20];
    float ratings;
    char feedback[20];
    char timestamp[20];
};

/**structure for entering the feedback by the user(queue implementation)**/
struct myqueue
{
    char name[20][20];
    float rating[20];
    char message[20][20];
    int front;
    int rear;

};

/**globally declared variables**/
int global_count=0;
CP details[100];
CP result_list[50];
CP final_list[20];
CP choice_list[10];

int visited[10];
int fenwick_tree[30];

/**Function Name: write_into_file
Input Params: NILL
Return Type: void
Description: writes all the data available with details into appropriate data structure
**/
void write_into_file()
{
    FILE *fp;
    fp = fopen("commute.txt", "w");

    if (fp == NULL)
    {
        printf("File open error");
        return;
    }

    int i;
    for (i = 0; i <97; i++)
{
    int res = scanf("%d%d%d%d%d%[^\n]", &details[i].distance, &details[i].seats, &details[i].fare, &details[i].start, &details[i].end, details[i].type);

    if (res != 6) {
        printf("Error in input format. Loop terminated.\n");
        break;
    }

    fprintf(fp, "%d %d %d %d %d %s\n", details[i].distance, details[i].seats, details[i].fare, details[i].start, details[i].end, details[i].type);
}
 fclose(fp);
}

/**Function Name: load_from_file
Input Params: NILL
Return Type: void
Description: loads all the data available with details into appropriate data structure**/

void read_from_file()
{
    FILE *fp;

    fp = fopen("commute.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    char line[200];
    printf("DISTANCE SEATS  FARE STARTPOINT ENDPOINT TYPE OF TRANSPORT\n");
    while (global_count < 100 && fgets(line, sizeof(line), fp) != NULL)
    {
        int res = sscanf(line, "%d %d %d %d %d %[^\n]", &details[global_count].distance, &details[global_count].seats, &details[global_count].fare, &details[global_count].start, &details[global_count].end, details[global_count].type);
        if (res == 6)
        {
            printf("%d\t%d\t%d\t%d\t%d\t%s\n", details[global_count].distance, details[global_count].seats, details[global_count].fare, details[global_count].start, details[global_count].end, details[global_count].type);
            global_count++;
        }
    }

    fclose(fp);
}

/**
Function name:floyd_warshall
Input Params:matrix from main
Return type:void
Description:prints all pair shortest path from each vertices
**/
void print_solution(int dist[10][10]);
void floyd_warshall(int dist[10][10])
{
    int i, j, k;


    for (k = 0; k < 10; k++)
        {
        for (i = 0; i < 10; i++)
        {

            for (j = 0; j < 10; j++)
            {

                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    print_solution(dist);
}
/**Function name:printsolution
Input Params:matrix from main
Return type:void
Description:prints all pair shortest path from each vertices
**/
void print_solution(int dist[10][10])
{ int i,j;
    printf("\nThe following matrix shows the shortest distances between every pair of vertices(places here)\n");
    printf("*****************************\n");
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (i==j)
             printf(" 0");
            else
                printf("%3d", dist[i][j]);
        }
        printf("\n");
    }
    printf("*****************************\n");
}

/**Function name:search_from_file
Input Params:start point of the journey
Return type:void
Description:prints all pair of vertices with the details having their starting point as s
**/
void search_from_file(int s)
{
    FILE *fp;

    fp = fopen("commute.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    char line[100];

    printf("The following shows the\n");
    printf("DISTANCE SEATS  FARE STARTPOINT ENDPOINT TYPE OF TRANSPORT\n");
           printf("all starting from %d\n",s);



    while (global_count < 100 && fgets(line, sizeof(line), fp) != NULL)
    {
        int res = sscanf(line, "%d %d %d %d %d %[^\n]", &details[global_count].distance, &details[global_count].seats, &details[global_count].fare, &details[global_count].start, &details[global_count].end, details[global_count].type);
        if (res == 6)
        {
            if(details[global_count].start==s)
            {
            printf("%d\t%d\t%d\t%d\t%d\t%s\n", details[global_count].distance, details[global_count].seats, details[global_count].fare, details[global_count].start, details[global_count].end, details[global_count].type);
            result_list[global_count].distance=details[global_count].distance;
            result_list[global_count].distance=details[global_count].distance;
            result_list[global_count].seats=details[global_count].seats;
            result_list[global_count].fare=details[global_count].fare;
            result_list[global_count].start=details[global_count].start;
            result_list[global_count].end=details[global_count].end;
            strcpy(result_list[global_count].type,details[global_count].type);

            global_count++;
            }
            else
                continue;
        }
    }

fclose(fp);

}



/**Function name:result
Input Params:start point of the journey,end point of the journey
Return type:int
Description:Returns the shortest distance of those vertices whose start point=s and end point=e
**/
int get_distance_associated(int s,int e)
{
    int i;
    int k;
    for(i=0;i<8 ;i++)
    {
        if(result_list[i].start==s&&result_list[i].end==e)
        {
           k =result_list[i].distance;


        }
        else
            continue;
    }
    return k;
}
/**Function name:all_distances
Input Params:start point of the journey,end point of the journey,distance associated with it
Return type:int
Description:Returns the number of entities present in final_list
**/
int all_distances(int s,int e,int k)
{
    int i;
    int c=0;
    int l=0;
    printf("\n\n");
    printf("The following shows the vertices all starting from %d\n and having distance greater than or equal to %d\n",s,k);
        printf("DISTANCE SEATS  FARE STARTPOINT END POINT TYPE OF TRANSPORT\n");

    for(i=0;i<10;i++)
    {

        if(result_list[i].start==s&&result_list[i].distance>=k)
        {   c++;

            printf("%d\t%d\t%d\t%d\t%d\t%s\n", result_list[i].distance,result_list[i].seats, result_list[i].fare, result_list[i].start,result_list[i].end, result_list[i].type);
            final_list[l].distance=result_list[i].distance;
            final_list[l].distance=result_list[i].distance;
            final_list[l].seats=result_list[i].seats;
            final_list[l].fare=result_list[i].fare;
            final_list[l].start=result_list[i].start;
            final_list[l].end=result_list[i].end;
            strcpy(final_list[l].type,result_list[i].type);
            l++;
        }



    }

            return c;
}
/**Function name:search_vehicle_list
Input Params:number of elements in final_list,vehicle user has opted for
Return type:-
Description:Returns the number of entities present in final_list
**/
void search_vehicle( int p,  char* name)
{
    int found = 0;
    int i;
    int k     =0;
    int a[5];
    int count = 0;
    printf("The following is/are the options to opt for\n");
    for (i = 0; i <p; i++)
    {
        if (strstr(final_list[i].type,name) != NULL)
        {
            found = 1;
            a[k]=i;
            printf("%d\t%d\t%d\t%d\t%d\t%s\n", final_list[a[k]].distance,final_list[a[k]].seats, final_list[a[k]].fare, final_list[a[k]].start,final_list[a[k]].end, final_list[a[k]].type);
            k++;
            count++;


        }
    }
        if(count==1)
        {
            printf("Thus distance to travel in kms in order to reach your desired destination and the vehicle chosen\n");
            printf("distance:%d\topted for:%s\n", final_list[a[0]].distance, final_list[a[0]].type);

        }

        else if(count>1)
    {


        printf("The user always chooses the first option i.e the following\n");
        printf("%d\t%d\t%d\t%d\t%d\t%s\n", final_list[a[0]].distance,final_list[a[0]].seats, final_list[a[0]].fare, final_list[a[0]].start,final_list[a[0]].end, final_list[a[0]].type);
        printf("Thus distance to travel in kms in order to reach your desired destination and the vehicle chosen\n");
        printf("distance:%d\topted for:%s\n", final_list[a[0]].distance, final_list[a[0]].type);




    }
}
/**Function name:bubble sort
Input Params:no of items in the final list presented to the user
Return type:void
Description:sorts the final_list based on amount(fare) to be given by the user
**/
void bubble_sort_distance(int p)
{
    int i;
    int j;
    for (i = 0; i < p - 1; i++)
    {
        for (j = 0; j < p - i - 1; j++)
        {
            if (final_list[j + 1].distance < final_list[j].distance)
            {

                CP temp = final_list[j];
                final_list[j] = final_list[j + 1];
                final_list[j + 1] = temp;
            }
        }
    }
}

/**function to swap to values(used commonly for buble,insertion,selection sort**/
void swap(CP *a, CP *b)
{
    CP temp = *a;
    *a = *b;
    *b = temp;
}
/**Function name:selection sort
Input Params:no of items in the final list presented to the user
Return type:void
Description:sorts the final_list based on distance
**/
void selection_sort_fare(int p)
{
    int i, j, min;

    for (i = 0; i < p - 1; i++)
    {
        min = i;
        for (j = i + 1; j < p; j++)
        {
            if (final_list[j].fare <final_list[min].fare)
            {
                min = j;
            }
        }
        swap(&final_list[min], &final_list[i]);
    }
}
/**Function name:insertion sort
Input Params:no of items in the final list presented to the user
Return type:void
Description:sorts the final_list based on number of seats available
**/
void insertion_sort_seats( int p)
{
    int i, j;
    CP key;

    for (i = 1; i < p; i++)
    {
        key =final_list[i];
        j = i - 1;


        while (j >= 0 && final_list[j].seats > key.seats)
        {
            final_list[j + 1] =final_list[j];
            j = j - 1;
        }
        final_list[j + 1] = key;
    }
}

/**function to display the final_list once it is sorted as required**/
void display_sorted_list()
{
    int i;
    printf("\n\n");
    printf("DISTANCE SEATS  FARE STARTPOINT END POINT TYPE OF TRANSPORT\n");

    for(i=0;i<8;i++)
    {

    if(final_list[i].distance!=0)

    printf("%d\t%d\t%d\t%d\t%d\t%s\n", final_list[i].distance,final_list[i].seats, final_list[i].fare, final_list[i].start,final_list[i].end, final_list[i].type);

    }

}

/**Function name:creates_node
Input Params:
Return type:NODE*
Description:creates the node for storing vehicle and its associated pollution type
**/
NODE* create_node()
{
   NODE* temp;
   temp=(NODE*)malloc(sizeof(NODE));
   if(temp==NULL)
  {
    printf("INSUFFICIENT MEMORY\n");
    return 0;
  }
   temp->next=NULL;
   return temp;
}
/**Function name:read_details
Input Params:-
Return type:NODE*
Description:reads the details of vehicle and the pollution level
**/
NODE* read_details(NODE* t)
{

   scanf("%s%f",t->tov,&t->p_level);
   return t;
}
/**Function name:insert_end
Input Params:head,node to be inserted
Return type:NODE*
Description:inserts the node one by one serially
**/
NODE* insert_end(NODE* head,NODE* t)
{   NODE* ptr;

    if(head==NULL)
  {
      head=t;
  }
  else
  {
     ptr=head;
     while(ptr->next!=NULL)
     {
         ptr=ptr->next;
     }
     ptr->next=t;

  }
  return head;
}
/**Function name:display_list
Input Params:head
Return type:void
Description:displays all the vehicles and their associated pollution level
**/
void display_list(NODE* head)
{
    if (head == NULL)
    {
        printf("Empty list\n");
    }
    else
    {
        printf("%-15s%-10s\n", "Vehicle", "Pollution Level");
        printf("-------------------------\n");

        NODE* cur = head;
        while (cur != NULL)
        {
            printf("%-15s%-10.2f\n", cur->tov, cur->p_level);
            cur = cur->next;
        }
    }
}

/**Function name:search_vehicle_pollution
Input Params:head of the list and the vehicle type whose pollution you wish to search
Return type:void
Description:gives the pollution level of searched vehicle
**/
void search_vehicle_pollution(NODE *head, const char *vehicletype)
{
    NODE *cur = head;

    while (cur != NULL)
    {
        if (strcmp(cur->tov, vehicletype) == 0)
        {
            printf("Vehicle: %s, Pollution Level: %.2f\n", cur->tov, cur->p_level);

        }
        cur = cur->next;
    }




}



/**function to check if the stack is empty or not**/
int is_empty(PAYMENT* stack)
{
    return stack->top == -1;
}

/**function to check if the stack is full or not**/
int is_full(PAYMENT* stack)
{
    return stack->top == M_SIZE - 1;
}

//stack operations are maintained for payment purpose//
/**Function name:push the elements into the stack
Input Params:stack,and the elements to be pushed into the stack
Return type:void
Description:gives the pollution level of searched vehicle
**/
void push(PAYMENT *stack, char vehicle[20], float cost, char mode_of_transaction[20])
{
    if (is_full(stack))
    {
        printf("Stack overflow.\n");
        return;
    }

    stack->top++;

    strcpy(stack->tov[stack->top], vehicle);
    stack->cost[stack->top] = cost;
    strcpy(stack->mode_of_payment[stack->top], mode_of_transaction);
}

/**Function name:pop_cost_of vehicle
Input Params:stack,vehicle name
Return type:float
Description:gives out the cost of the vehicle the user has opted for
**/
float pop_cost_of_vehicle(PAYMENT* stack, const char* vehicle)
{
    if (is_empty(stack))
    {
        printf("Stack underflow.\n");
        return;
    }

    int i,j;
    float cost;


    for (i = stack->top; i >= 0; i--)
    {
        if (strcmp(stack->tov[i], vehicle) == 0)
        {


            printf("options availabe is/are %s",stack->mode_of_payment[i]);
            cost=stack->cost[i];

            for (j = i; j < stack->top; j++)
            {
                stack->cost[j] = stack->cost[j + 1];
            }

           stack->top--;
        }
    }
return cost;

}
/**Function name:display_stack
Input Params:stack
Return type:float*
Description:copies the cost/km of vehicletype into a vehicle to sort the cost and present it to the user
**/
float* display_stack(PAYMENT stack)
{
    int i;
    printf("%-20s%-10s%-20s\n", "Vehicle", "Cost", "Mode of Payment");
    printf("-----------------------------------------------------\n");

    float* cost_array = (float*)malloc((stack.top + 1) * sizeof(float));

    if (cost_array == NULL)
    {

        printf("Memory allocation failed.\n");
        return NULL;
    }
    for(i=stack.top;i>=0;i--)
    {
        cost_array[i]=stack.cost[i];
        printf("%-20s%-10.1f%-20s\n", stack.tov[i], stack.cost[i], stack.mode_of_payment[i]);

    }
    return cost_array;
}
/**function to heapify the cost array**/
void heapify(int n, float a[n], int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
    {
        largest = left;
    }

    if (right < n && a[right] > a[largest])
    {
        largest = right;
    }

    if (largest != i)
    {

        float temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;


        heapify(n, a, largest);
    }
}
/**function to build the heap**/
void max_heap(int n, float a[n])
{   int i;
    for (i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(n, a, i);
    }
}
/**Function name:heap_sort
Input Params:elements in stack,cost array to be sorted
Return type:void
Description:gives a sorted cost array to the user
**/
void heap_sort(int n, float a[n])
{
    int i;
    max_heap(n, a);

    for ( i = n - 1; i > 0; i--)
    {

        float temp = a[0];
        a[0] = a[i];
        a[i] = temp;


        heapify(i, a, 0);
    }
}
/**Function name:display_array
Input Params:cost array
Return type:void
Description:displays a sorted cost array to the user
**/
void display_array(float a[8])
{
    int i;

    printf("The sorted order of cost(rs/km) is\n");
    for (i = 0; i < 8; i++)
    {
       printf("%.1f  ",a[i]);
    }


}

/**function to swap the elements of stack**/
void swap_quick(PAYMENT* stack, int i, int j)
{
    char temp_vehicle[20];
    float temp_cost;
    char temp_mode[20];

    strcpy(temp_vehicle, stack->tov[i]);
    temp_cost = stack->cost[i];
    strcpy(temp_mode, stack->mode_of_payment[i]);

    strcpy(stack->tov[i], stack->tov[j]);
    stack->cost[i] = stack->cost[j];
    strcpy(stack->mode_of_payment[i], stack->mode_of_payment[j]);

    strcpy(stack->tov[j], temp_vehicle);
    stack->cost[j] = temp_cost;
    strcpy(stack->mode_of_payment[j], temp_mode);
}
/**function to partition the stack**/
int partition(PAYMENT* stack, int l, int h)
{
    int j;
    float pivot = stack->cost[h];
    int i = l - 1;

    for (j = l; j <= h - 1; j++)
    {
        if (stack->cost[j] <= pivot)
        {
            i++;
            swap_quick(stack, i, j);
        }
    }

    swap_quick(stack, i + 1, h);
    return i + 1;
}
/**Function name:quick sort
Input Params: stack,input parameters required for quick sort
Return type:void
Description:gives a sorted(decreasing order) stack to the user
**/
void quick_sort(PAYMENT* stack, int l, int h)
{
    if (l < h)
    {
        int pi = partition(stack, l, h);

        quick_sort(stack, l, pi - 1);
        quick_sort(stack, pi + 1, h);
    }
}
/**function to display the stack**/
void display_sorted_stack(PAYMENT stack)
{
    int i;
    printf("%-20s%-10s%-20s\n", "Vehicle", "Cost", "Mode of Payment");
    printf("-----------------------------------------------------\n");

    for ( i =stack.top; i>=0; i--)
    {
        printf("%-20s%-10.2f%-20s\n", stack.tov[i], stack.cost[i], stack.mode_of_payment[i]);
    }
}

/**Function name:calculate_distances
Input Params: no of elements in final_list,vehicle name
Return type:int
Description:returns distance associated with the vehicle chosen by the user
**/
int calculate_distance( int c,const char* searchType)
{
    int found = 0;
    int i,k;
    int count = 0;
    for (i = 0; i <c; i++)
    {
        if (strstr(final_list[i].type, searchType) != NULL)
        {
            found = 1;
            count++;
            k=i;
        }
    }
        if(count==1)
        {
            return final_list[k].distance;

        }

        else if(count>1)
    {
        return final_list[count-1].distance;



    }
}
/**Function name:dfs
Input Params: souce vertex,graph
Return type:void
Description:displays the path the user must visit
**/
void DFS(int vertex,int graph[10][10])
{   int i;
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (i = 0; i < 10; i++)
    {
        if (graph[vertex][i] && !visited[i])
        {
            DFS(i,graph);
        }
    }
}
//dijktras implementation//(line 846-941)
/**function to return the min_index**/
int min_distance(int dist[], int arr[])
{
    int min = INT_MAX, min_index,v;

    for (v = 0; v < V; v++)
        if (arr[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
/**prints the path the user has to take**/
void print_path(int parent[], int j)
{
    if (parent[j] == -1)
        return;

    print_path(parent, parent[j]);

    printf("%d ", j);
}

void print(int dist[], int parent[])
{
    int i;
    printf("Vertex   Distance from Source   Path\n");
    for ( i = 0; i < V; i++)
    {
        printf("%-8d%-23d", i, dist[i]);
        print_path(parent, i);
        printf("\n");
    }
}

/**Function name:dijktras
Input Params: souce vertex,graph
Return type:void
Description:displays the path the user must visit
**/
void dijkstra(int graph[V][V], int source)
{
    int i,v;
    int dist[V], parent[V];
    int arr[V];
    int count;

    for (i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        arr[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (count = 0; count < V - 1; count++)
    {
        int u = min_distance(dist, arr);

        arr[u] = 1;

        for (v = 0; v < V; v++)
            if (!arr[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    print(dist, parent);
}
/**Function name:bfs
Input Params: souce vertex,graph
Return type:void
Description:displays the path the user must visit
**/
void bfs(int graph[10][10],int source)
{
    int queue[100];

    int front = 0, rear = 0, u, i;

    int visited[10];

    for (i= 0; i < V; i ++)
       visited[i] = 0;

    queue[rear] = source;


    visited[source] = 1;

    printf("The BFS Traversal is \n");
    while (front <= rear)
    {

        u = queue[front];
        printf("%d ", u);
        front = front + 1;

    for(i=0;i<V;i++)
    {
       if(graph[u][i]==1&&visited[i]==0)
       {
        visited[i]=1;

       rear=rear+1;
       queue[rear]=i;

       }
    }
    }
}
//prims implementation(line 958-1015)
/**fuction to find min_index **/
int min_key(int key[], int mst_set[])
{   int v;
    int min = INT_MAX, min_index;

    for ( v = 0; v < V; v++)
        if (mst_set[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}
/**function to print mst**/
void print_mst(int parent[], int graph[V][V])
{   int i;
    int sum=0;
    printf("Edge \tWeight\n");
    for ( i = 1; i < V; i++)
    {

        sum=sum+graph[i][parent[i]];


    }
    printf("\nYOU HAVE TO TRAVEL A DISTANCE OF %d kms IN ORDER TO VISIT ALL THE PLACES AT A MINIMUM DISTANCE\n",sum);


}


/**Function name:prim_mst
Input Params: graph
Return type:void
Description:displays the path the user must visit
**/
void prim_mst(int graph[V][V])
{
    int parent[V],v,count,i;
    int key[V];
    int mst_set[V];

    for ( i = 0; i < V; i++)
    {
      key[i] = INT_MAX;
      mst_set[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for ( count = 0; count < V - 1; count++)
    {
        int u = min_key(key, mst_set);
        mst_set[u] = 1;

        for ( v = 0; v < V; v++)
            if (graph[u][v] && mst_set[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    print_mst(parent, graph);
}
//kruskals implementation(line 1020 -1170)//
/**function to create_set**/
void create_set(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = i;
    }
}
/**find function**/
int find(int a[], int u)
{

    return a[u];
}
/**union function**/
void union_sets(int a[], int n, int u, int v)
{int i;
    int temp = a[u];
    for (i = 0; i < n; i++)
    {
        if (a[i] == temp)
        {
            a[i] = a[v];
        }
    }
}

/**Function name:merge and merge sort
Input Params: edges,left,mid,right
Return type:void
Description:sorts the edges for kruskals
**/
void merge(struct edge edges[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int i,j,k;

    struct edge L[n1], R[n2];

    for ( i = 0; i < n1; i++)
    {
        L[i] = edges[left + i];
    }
    for ( j = 0; j < n2; j++)
    {
        R[j] = edges[mid + 1 + j];
    }

   i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].weight <= R[j].weight)
        {
            edges[k] = L[i];
            i++;
        } else {
            edges[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        edges[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        edges[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(struct edge edges[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort(edges, left, mid);
        merge_sort(edges, mid + 1, right);

        merge(edges, left, mid, right);
    }
}

void sort_edges(struct edge edges[], int edge_count)
{
    merge_sort(edges, 0, edge_count - 1);
}
/**Function name:kruskals
Input Params: souce vertex,graph
Return type:void
Description:displays the shortest non-connected path the user must visit
**/
void kruskals(int graph[V][V])
{
    struct edge edges[V * V];
    int edge_count = 0;
    int i,j;

    for (i = 0; i < V; i++)
    {
        for (j = i + 1; j < V; j++)
    {
            if (graph[i][j] != 0)
            {
                edges[edge_count].src = i;
                edges[edge_count].dest = j;
                edges[edge_count].weight = graph[i][j];
                edge_count++;
            }
        }
    }


   sort_edges(edges, edge_count);
   int sets[V];
   create_set(sets, V);

   int sum = 0;

   for (i = 0; i < edge_count; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;

        int setU = find(sets, u);
        int setV = find(sets, v);

        if (setU != setV)
        {


            sum += edges[i].weight;
            union_sets(sets, V, setU, setV);
        }
    }
    printf("THE PERSON HAS TO TRAVEL A DISTANCE OF %dkms IN INORDER TO TRAVEL ALL THE PLACES BUT IN A DISCONNECTED WAY.",sum);

}
/**Function name:look_table
Input Params: matrix,look up matrix
Return type:void
Description:searches for time taken to travel betwen any two vertices(places)
**/
void look_up_table(int matrix[10][10], int look_up[10][10])
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j <10; j++)
        {
            look_up[i][j] = matrix[i][j] * 2;
        }
    }
}
//data look_up//
int data_look_up(int look_up[10][10], int i, int j)
{
    return look_up[i][j];
}
/**Function name:rabin_karp
Input Params: text,pattern
Return type:void
Description:matches the input string(YES) to enter into the loop to proceed further
**/
int rabin_karp(char text[10],char opt[10])
{
    int M = strlen(opt);
    int N = strlen(text);
    int Q = 101;/**prime number**/

    int i, j;
    int p = 0;  /**hash value of the pattern**/
    int t = 0;  /**hash value of current substring of text**/
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % Q;


    for (i = 0; i < M; i++)
    {
        p = (d * p + opt[i]) % Q;
        t = (d * t + text[i]) % Q;
    }


    for (i = 0; i <= N - M; i++)
        {

        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (text[i + j] != opt[j])
                    break;
            }
            if (j == M)
                printf("Pattern matched.You can search for the vehicle now\n");


        }


        if (i < N - M)
        {
            t = (d * (t - text[i] * h) + text[i + M]) % Q;
            if (t < 0)
            t = (t + Q);
        }
    }
    return i;

}

//fenwick tree implementation(line 1247-1300)

void update(int i, int delta)
{
    i++;
    while (i <= 2)
    {
        fenwick_tree[i] += delta;
        i += i & -i;
    }
}

int query(int i)
{
    int sum = 0;
    i++;
    while (i > 0)
    {
        sum += fenwick_tree[i];
        i -= i & -i;
    }
    return sum;
}
//queue implementation(line 1271-1294)
/**function to initialize queue**/
void initialize_queue(struct myqueue *q)
{
    q->front = -1;
    q->rear = -1;
}

/**Function name:enqueue
Input Params: queue,name,rating,message
Return type:void
Description:enqueues the feedback details provided by the user as feedback
**/
void enqueue(struct myqueue *q, const char *name, float rating, const char *message)
{


    q->rear++;
    strcpy(q->name[q->rear], name);
    q->rating[q->rear] = rating;
    strcpy(q->message[q->rear], message);
}
/**displays the queue**/
void display_queue(struct myqueue *q)
{
    int i;

    for (i = q->front; i <= q->rear; i++)
    {
        printf("%s\t%.1f\t%s\n", q->name[i], q->rating[i], q->message[i]);
    }
}
/**function to simply the elements of the feedback structure to the user as a user-history record**/
void print_table_header()
{
    printf("%-10s%-10s%-10s%-15s\n", "Username", "Ratings", "Feedback", "Timestamp");
    printf("--------------------------------------------------\n");
}

/**prints the feedback **/
void print_feedback_row(struct Feedback *feedback)
{
    printf("%-10s%-10.1f%-10s%-15s\n", feedback->username, feedback->ratings, feedback->feedback, feedback->timestamp);
}

/**Function name:create-resort
Input Params:name,location,rating
Return type:struct resort*
Description:creates the tree
**/
struct Resort* create_resort(const char *name, const char *location, float rating)
{
    struct Resort* newnode = (struct Resort*)malloc(sizeof(struct Resort));
    if (newnode == NULL)
    {
        printf("Memory allocation error\n");

    }

    strcpy(newnode->name, name);
    strcpy(newnode->location, location);
    newnode->rating = rating;
    newnode->left = newnode->right = NULL;

    return newnode;
}
/**Function name:insert_resort
Input Params: root,name,location,rating
Return type:struct resort*
Description:
**/
struct Resort* insert_resort(struct Resort* root, const char *name, const char *location, float rating)
{
    if (root == NULL)
    {
        return create_resort(name, location, rating);
    }


    if (rating < root->rating)
    {
        root->left = insert_resort(root->left, name, location, rating);
    } else
    {
        root->right = insert_resort(root->right, name, location, rating);
    }

    return root;
}

/**Function name:inorder_traversal
Input Params: root
Return type:void
Description:displays the resort,location and rating given to it
**/
void inorder_traversal(struct Resort* root)
{
    if (root != NULL)
    {
        inorder_traversal(root->left);
        printf("Name: %s, Location: %s, Rating: %.2f\n", root->name, root->location, root->rating);
        inorder_traversal(root->right);
    }
}
/**Function name:search_resort_by_rating
Input Params: root,rating
Return type:struct resort*
Description:returns the searched resort along with its rating
**/
struct Resort* search_resort_by_rating(struct Resort* root, float rating)
{
    if (root == NULL || rating == root->rating)
    {
        return root;
    }

    if (rating < root->rating)
    {
        return search_resort_by_rating(root->left, rating);
    }
    else
    {
        return search_resort_by_rating(root->right, rating);
    }
}
/**Function name:compute_LPS_array
Input Params: pattern
Return type:void
Description:generates the longest suffix and prefix needed for KMP algo
**/
void compute_LPS_array(const char* pattern, int M, int* lps)
{
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
             if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
/**Function name:KMP_search
Input Params: pattern and text(security pin:text)(input string:pattern)
Return type:int
Description:return the sum of indices(if the text and pattern match)
**/

int KMP_search(const char* pattern, const char* text)
{
    int M = strlen(pattern);
    int N = strlen(text);

    if (M == 0 || N == 0)
    {
        return -1;
    }

    int* lps = (int*)malloc(sizeof(int) * M);
    int j = 0;

    compute_LPS_array(pattern, M, lps);

    int i = 0;
        while (i < N)
        {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            free(lps);
            return i - j;
        } else if (i < N && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            } else
            {
                i++;
            }
        }
    }

    free(lps);
    return -1;
}


int main()
{


        /**all declarations**/
        int matrix[10][10];
        int time_matrix[10][10];
        NODE* head=NULL;
        NODE* t   =NULL;
        int choice;
        int s;
        int e;
        int k;
        int c;
        int n;
        int i;
        int j;
        char tov[15];
        char opt[15];
        PAYMENT stack;
        stack.top = -1;
        float* a;
        int p;
        int source;
        int found;
        /**end of declarations**/

        /**security to the program(KMP implementation)**/
        char security[15]="Shradha@249";
        char pin[15];
        printf("Enter the security key to use the app\n");
        printf("Hint:Name@rollno\n");
        scanf("%s",pin);
        found = KMP_search(pin, security);
        if (found != -1)
        {
        printf("Security key matched. Access granted!\n");
        /**structure implementation**/
        struct Feedback list[7] =
        {
        {"Shradha", 4.5, "Best", "2daysago"},
        {"Soujanya", 3.0, "Good", "1dayago"},
        {"Riya", 5.0, "Best", "23hrsago"},
        {"Savita", 2.0, "Notgood", "15hrsago"},
        {"Sanjana", 4.0, "Average", "20daysago"},
        {"Pooja", 3.5, "Average", "12minago"},
        {"Vasudev", 5.0, "Best", "30minago"}
        };
        printf("\nGiven below are some of the feedback we received recently\n");

        print_table_header();

        for (i = 0; i < 7; i++)
        {
        print_feedback_row(&list[i]);
        }

        /**this graph is taken as input for person who wishes to wanderlust(graph algorithms)**/
        int graph[10][10]= {

        {0, 68, 35, 1, 70, 25, 79, 59, 63, 65},
        {6, 0, 82, 28, 62, 92, 96, 43, 28, 37},
        {92, 5, 0, 54, 93, 83, 22, 17, 19, 96},
        {48, 27, 72, 0, 70, 13, 68, 100, 36, 95},
        {4, 12, 23, 34, 0, 65, 42, 12, 54, 69},
        {48, 45, 63, 58, 38, 0, 24, 42, 30, 79},
        {17, 36, 91, 43, 89, 7, 0, 43, 65, 49},
        {47, 6, 91, 30, 71, 51, 7, 0, 94, 49},
        {30, 24, 85, 55, 57, 41, 67, 77, 0, 9},
        {45, 40, 27, 24, 38, 39, 19, 83, 30, 0}

                            };

       /**Map for an area(represented in the form of a graph generated randomly)**/
        for (i = 0; i < 10; i++)
        {
        for (j = 0; j < 10; j++)
        {
            if(i==j)
                matrix[i][j]=0;
            matrix[i][j] = rand() % 100 + 1;
        }
        }
        printf("\nGiven below is map for an area which the user is presently in\n");
        printf("*****************************\n");
        for (i = 0; i < 10; ++i)
        {
        for (j = 0; j < 10; ++j)
        {
            if(i==j)
            printf("0 ");

            printf("%d ",matrix[i][j]);
        }
        printf("\n");
        }
        printf("*****************************\n");
        printf("\n");

        /**floyad warshall implementation**/
        floyd_warshall(matrix);

        /**user input**/
        /**matrix that tells the time taken to travel betwwen any two places**/
        printf("Do you wish the time travel matrix between the places you want to visit?press 1 for yes..any other number for no\n");
        scanf("%d",&p);

        if(p==1)
        {
             srand(time(NULL));
          for (i = 0; i < 10; i++)
          {
            for (j = 0; j < 10; j++)
             {
              if (i == j)
            {

               time_matrix[i][j] = 0;
            } else
            {
               time_matrix[i][j] = rand() % 100 + 1;
            }
            }
          }
         printf("The time matrix for the given area is\n");
         printf("*****************************\n");
         for (i = 0; i < 10; i++)
         {
         for (j = 0; j < 10; j++)
         {
            if(i==j)
            printf("0 ");
            printf("%d ", time_matrix[i][j]);
         }
         printf("\n");
         }
         printf("*****************************\n");
       }
         else
        printf("No i don't need a time matrix\n");

         p=0;

        printf("\nDo you prefer to travel(tourist)or in a need of immediate emergency\n");
        printf("PRESS 0 FOR WANDERLUST(travel without cost)OR 1 FOR IMMEDIATE EMERGENCY\n");
        scanf("%d",&p);
        if(p==0)
        {
            printf("Please prefer the following options available\n");
            while(1)
	    {
        printf("\n******** Menu *************\n");
        printf("0-IF THE USER WANTS TO SEARCH TIME BETWEEN ANY TWO PLACES\n");/**LOOK UP TABLE**/
        printf("1-IF THE USER WANTS TO JUST WANDERLUST THE PLACES NOT PARTICULARLY IN NEED OF SHORTEST PATH(wants to find immediate cities)\n");/**DFS**/
        printf("2-IF THE USER WANTS TO FIND THE SHORTEST PATH FROM A PARTICULAR POINT TO ANY PARTICULAR PLACE WITHOUT ANY DISCONNECTIVITY\n");/**DIJKTRAS**/
        printf("3-IF THE USER WANTS TO VISIT LEVEL BY LEVEL\n");/**BFS**/
        printf("4-IF THE USER WANTS TO VISIT IN A CONNECTED WAY WITH SHORTEST PATH BEEN COVERED AND ALL THE PLACES VISITED\n");/**PRIMS**/
        printf("5-IF THE USER DOES NOT WISH TO TRAVEL IN A CONNECTED WAY BUT WITH SHORTEST PATH BEEN COVERED AND ALL THE PLACES VISITED\n");/**KRUSKALS**/
        printf("6-IF THE USER WISHES TO SEE NEARBY RESORTS FOR A STAY\n");/**BINARY SEARCH TREE**/
        printf("*****************************\n");
        printf("Enter your choice\n");
        scanf("%d", &choice);

	 switch(choice)
	 {

	         case 0:{
	                   /**Lookup table implementation**/
                       int table[10][10];
                       look_up_table(time_matrix,table);
                       int s,e;
                       printf("Enter any two start and end values(any 2(different)vertices) about which you want to see the time taken\n");
                       scanf("%d %d",&s,&e);
                       printf("Time taken to travel from[%d] to [%d] is : %dminutes\n", s, e, data_look_up(table,s, e));
                        break;

                    }
             case 1:{

                    /**DFS implementation**/

                    printf("\nEnter the place(vertex)from which you wish to start: ");
                    scanf("%d", &source);

                    for (i = 0; i < 10; i++)
                    {
                      visited[i] = 0;
                    }

                    printf("\nTHE PATH THAT THE USER HAS TO OPT IN ORDER TO REACH THE END DESTINATION%d: ", source);
                    DFS(source,graph);
                    break;
                   }
            case 2:{
                    /**DIJKTRAS implementation**/
                    printf("Enter the source vertex where which you wish to start the journey\n");
                    scanf("%d",&source);
                    printf("YOU CAN CHOOSE ANY OF THE PATHS GIVEN BESIDES(as path)\n");
                    dijkstra(graph,source);
                    break;
                    }
            case 3:{
                   /**BFS implementation**/
                     int bfs_graph[10][10] = {
                    {0, 1, 0, 0, 1, 0, 1, 1, 1, 1},
                    {0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
                    {1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
                    {0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
                    {0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
                    {0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
                    {0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                    {0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
                    {0, 0, 1, 1, 1, 0, 1, 1, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
                                           };

                   printf("enter the starting place(vertex)from which you wish to start your journey\n");
                   scanf("%d",&source);
                   printf("\nTHE PATH THAT THE USER HAS TO OPT IN ORDER TO REACH THE END DESTINATION%d: ", source);
                   bfs(bfs_graph,source);
                   break;
                   }
            case 4:{
                    /**PRIMS implementation**/
                    prim_mst(graph);
                    break;

                   }
            case 5:
                   /**KRUSKALS implementation**/
                   kruskals(graph);
                   break;
            case 6:
                   {/**Binary tree implementation for searching of resort**/
                       struct Resort* root = NULL;
                       root = insert_resort(root, "EMERALD", "KARWAR", 4.5);
                       root = insert_resort(root, "LOTUS", "SADASHIVGAD", 3.8);
                       root = insert_resort(root, "KAMATLUXURIES", "KANASGIRI", 4.1);
                       root = insert_resort(root, "RESERVELAND", "KAJUBAG",4.2);
                       root = insert_resort(root, "S_HOSPITALITY", "KODIBAG",2);
                       printf("Nearby Resorts:\n");
                       inorder_traversal(root);

                       float target_rating;
                       printf("\nEnter the rating of the resort you want to search:\n");
                       scanf("%f", &target_rating);

                       struct Resort* found_resort = search_resort_by_rating(root, target_rating);

                       if (found_resort != NULL)
                       {
                        printf("Congratulations! We found a resort with the specified rating:\n");
                        printf("Name: %s, Location: %s, Rating: %.2f\n", found_resort->name, found_resort->location, found_resort->rating);
                       }
                      else
                      {
                      printf("Sorry, no matching results found for the specified rating.\n");
                      }
                       break;

                    }

            default:printf("exciting code");
        }
	    }
        }
        else if(p==1)
        {
        printf("Please prefer the following options available\n");
        while(1)
       {


        printf("\n******** Menu *************\n");
        printf("6-IF THE USER WANTS TO SEARCH TIME BETWEEN ANY TWO PLACES\n");
        printf("7-FILE WRITING\n");
        printf("8-FILE LOADING\n");
        printf("9-VEHICLES,COST AND MODE OF PAYMENT\n");
        printf("10-USER INPUT TO GO TO DESIRED LOCATION\n");
        printf("11-PAYMENT AFTER TRAVELLING\n");
        printf("12-FEEDBACK SHARING\n");
        printf("*****************************\n");


        printf("\nCAUTION**:Please do not select case 7 & 8 because they are already being implemented..if you choose it may lead to any discrepancies in the code\n");
        printf("\nCase 11 must be choosen only after case 10 is implemented and case 12 chosen at last\n");
        printf("Enter your choice\n");
        scanf("%d", &choice);
        switch(choice)
        {

            case 6:{
                    /**Look up table implementation**/
                   int table[10][10];
                   look_up_table(time_matrix,table);
                   int s,e;
                   printf("Enter any two start and end values about which you want to see the time taken\n");
                   scanf("%d %d",&s,&e);
                   printf("Time taken to travel from[%d] to [%d] is : %dminutes\n", s, e, data_look_up(table,s, e));
                    break;
                   }
            case 7:write_into_file();
                   break;
            case 8:read_from_file();
                   break;
            case 9: {/**Stack implementation**/
                    int n=8;
                    char vehicle[20];
                    float cost;
                    char mop[20];

                    push(&stack, "RAPIDO", 10.0, "CASH/PPAY/PAY");
                    push(&stack, "OLA", 25.0, "GPAY");
                    push(&stack, "METRO", 7.0, "PPAY/GPAY/CASH");
                    push(&stack, "PUBLICBUS", 6.0, "CASH");
                    push(&stack, "PRIVATEVEHICLE", 0.0, "0");
                    push(&stack, "TRAIN", 5.0, "CASH/ONLINE");
                    push(&stack, "UBERAUTO", 16.0, "CASH/GPAY/PPAY");
                    push(&stack, "RICKSHAW", 20.0, "CASH/PPAY/GPAY");

                    printf("\n\n");
                    float* cost_array = display_stack(stack);
                    heap_sort(n,cost_array);
                    printf("\nThe following just gives the sorted list of cost that the vehicles takes for each kms\n");
                    display_array(cost_array);
                    printf("\n");
                    quick_sort(&stack,0,stack.top);
                    printf("The following displays the sorted(descreasing order)for the elements of the stack\n");
                    display_sorted_stack(stack);
                    break;
                    }
            case 10:
                     {
                    j=0;
                    s=0;
                    e=0;
                    printf("Enter the start(space)end point of the journey(0-9)\n");
                    printf("CAUTION** START AND END POINT SHOULD NOT BE THE SAME\n");
                    scanf("%d %d",&s,&e);
                    search_from_file(s);
                    k=get_distance_associated(s,e);
                    c=all_distances(s,e,k);
                    if(c==1)
                    {
                        printf("There is only one option available to you\n");

                    }
                    else
                    {

                    printf("Enter the details of vehicle and pollution caused by them\n");
                    printf("Sample is provided in the code for reference (line 1822-1833)\n");

                    for(i=0;i<8;i++)
                    {                          /**sample input**/
                    t=create_node();           /**RAPIDO 15
                                                  OLA 30
                                                  METRO 20
                                                  PUBLICBUS 63.4
                                                  PRIVATEVEHICLE 87.5
                                                   TRAIN 76.54
                                                  UBERAUTO 21
                                                  RICKSHAW 41.7
                                                               **/
                    t=read_details(t);
                    head=insert_end(head,t);
                    }
                    printf("\n");
                    display_list(head);
                    printf("\nEnter either 0 or 1 or 2 for sorting on basis of fare,distance,and seats respectively\n");
                    printf("**CAUTION-SORTING ON BAIS OF SEATS IS GENERALLY NOT PREFERRED**\n");
                    printf("\nPlease prefer to go with distance based sorting as that would give you the expected result with accuracy!\n");
                    scanf("%d",&j);
                    if(j==0)
                    {
                    selection_sort_fare(c);
                    printf("\nThe sorted list(according to fare)\n");
                    display_sorted_list();
                    }
                    if(j==1)
                    {
                    printf("\nThe sorted list(according to distance)");
                    bubble_sort_distance(c);
                    display_sorted_list();
                    }
                    if(j==2)
                    {
                    printf("\nThe sorted list(according to seats)");
                    insertion_sort_seats(c);
                    display_sorted_list();

                    }
                    char text[]="YES";
                    char pattern[20];

                    printf("Do you want to search for any vehicles pollution in particular?..if yes..types YES.else you can't\n");
                    scanf("%s",pattern);
                    int r=rabin_karp(text,pattern);
                    for(i=0;i<2;i++)

                    if(r==1)
                    {

                          /**searching for a particular vehicle and pollution caused by it**/
                          printf("Please enter the preferable type of transport(ENTER IN CAPS)");
                          printf(" the transport must be choosen from any one of the vehicles listed above in the sorted list");
                          scanf("%s",tov);
                          search_vehicle_pollution(head,tov);
                          break;

                     }
                    else
                    {
                        printf("re-enter YES..this is your last chance else you will be redirected to the front page!");
                        scanf("%s",pattern);
                        r=rabin_karp(text,pattern);
                    }

                    printf("Which vehicle do you wish to opt for(ENTER IN CAPS)\n");
                       scanf("%s",opt);
                       search_vehicle(c,opt);

                     }
                    break;
                     }

               case 11: {
                    int n=8;
                    char vehicle[20];
                    float cost;
                    char mop[20];

                    printf("Here are the details of vehicle type,cost/km and mode of payment the transport provides\n");
                    push(&stack, "RAPIDO", 10.0, "CASH/PPAY/PAY");
                    push(&stack, "OLA", 25.0, "GPAY");
                    push(&stack, "METRO", 7.0, "PPAY/GPAY/CASH");
                    push(&stack, "PUBLICBUS", 6.0, "CASH");
                    push(&stack, "PRIVATEVEHICLE", 0.0, "0");
                    push(&stack, "TRAIN", 5.0, "CASH/ONLINE");
                    push(&stack, "UBERAUTO", 16.0, "CASH/GPAY/PPAY");
                    push(&stack, "RICKSHAW", 20.0, "CASH/PPAY/GPAY");

                    printf("\n\n");
                    float* cost_array = display_stack(stack);
                    printf("\n");
                    quick_sort(&stack,0,stack.top);
                    printf("The following displays the sorted(descreasing order)for the elements of the stack\n");

                    display_sorted_stack(stack);
                    printf("Enter the vehicle that you had opted for previously in case 10(ENTER IN CAPS)\n");
                    scanf("%s",opt);
                    if(strcmp(opt,"PRIVATE VEHICLE")==0)
                    {
                        printf("The user uses his/her own vehicle and travels to the required destination\n");
                    }
                    else
                    {
                    int distance=calculate_distance(c,opt);

                    float rupees=pop_cost_of_vehicle(&stack,opt);

                    printf("and the cost needed to travel on %s is %.2f",opt,rupees*distance);

                    printf("\nDo you want to pay the amount in installments or you wish to pay it now?\n");
                    printf("1-YES 0-NO\n");
                    i=0;
                    scanf("%d",&i);
                    if(i==1)
                    {
                    printf("You have only two installments to pay\n");


                    for (i = 0; i <30; i++)
                    {
                     fenwick_tree[i] = 0;
                    }


                    int installment_amounts[30];
                    printf("Enter the installment amounts:\n");
                    for (i = 0; i < 2; i++)
                    {
                    scanf("%d", &installment_amounts[i]);
                    update(i, installment_amounts[i]);
                    }


                    int amount = query(2+1);

                    printf("Remaining amount to be paid after installment %d: %d\n",2 + 1,(distance*rupees)-amount );



                   }
                   else
                   printf("Ill pay the desired amount now itself.");
                   printf("\nCongratulation!!%d amount is amount paid..Have a safe journey!!");

                     break;
                   }
                   }
                case 12:{struct myqueue q;
                        char name[20];
                        float rating;
                        char message[20];
                        initialize_queue(&q);

                        printf("Enter feedback details for entry %d:\n", i + 1);
                        printf("Name: ");
                        scanf("%s", name);

                        printf("Rating: ");
                        scanf("%f", &rating);

                        printf("Message: ");
                        scanf("%s", message);

                        enqueue(&q, name, rating, message);


                        printf("THANKYOU! %s,have a safe journey!",name);
                        //display_queue(&q);

                        }


             default:printf("Exciting code");


        }
        }
        }
        }
        else
        {
        printf("Invalid security key. Access denied!\n");
        }



    return 0;

 }
