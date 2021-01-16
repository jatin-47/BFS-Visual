/**********************************************************************
**  A visual representation of BFS for shortest path problem         **
**  implemented using a grid.                                        **
**  For graphics, WinBGIm is used which is NOT cross-platform        **
***********************************************************************
/*  Name: Jatin Saini                                                **
*                                                                    **
/*  Roll No.: 19ME30068                                              **
*                                                                    **
/*  Course: Artificial Intelligence (MA60038)                        **
/*  Professor: Bodhyan Roy                                           **
/**********************************************************************/

#include<graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// a point in a 2D grid with x and y coordinates
typedef struct
{
    int x;
    int y;

}point;

int ROWS;
int COLS;
// setting side length of each square
int len;
int len_Half;
// special null point
const point null_pt = {-1, -1};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   QUEUE data structure is implemented.
   enqueue, dequeue and isEmpty functions are utility to queue.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// a node in a queue data structure
typedef struct queueNode
{
   point pt;
   struct queueNode *link;

} queueNode;

// tells if the queue is empty or not
bool isEmpty(queueNode *front)
{
   if(front == NULL)                     //if the front pointer points to null
     return true;                        //queue is empty
   else
     return false;                       //else it is not empty
}

// adds a new node at the end of the queue
void enqueue(queueNode **front_ptr, queueNode **rear_ptr, point item)
{
   queueNode *newItem = (queueNode *)malloc(sizeof(queueNode));      //allocating memory for a new node
   newItem->pt = item;                                               //entering the new pt into it
   newItem->link = NULL;                                             //making its link variable NULL

   if(*rear_ptr != NULL)                                             //if the node to be added is the first node, don't run this command
     (*rear_ptr)->link = newItem;                                    //otherwise link the new node to the end of the queue

   *rear_ptr = newItem;                                              //updating the rear pointer to point to the new end node

   if(*front_ptr == NULL)                                            //case when the very first node is added to the queue
     *front_ptr = *rear_ptr;                                         //make the front pointer to point to the same first and the only node in the queue
}

// removes a node from the start of the queue
point dequeue(queueNode **front_ptr, queueNode **rear_ptr)
{
   if(*front_ptr == NULL)                                            //if the queue is already empty
   {
       return null_pt;
   }

   point oldItem_value;                                              //variable to store the deleted value
   queueNode *oldItem = *front_ptr;                                  //pointer to point to the node to be deleted
   *front_ptr = (*front_ptr)->link;                                  //updating the front pointer to point to the next node
   oldItem_value = oldItem->pt;                                      //getting the data from the node to be deleted
   free(oldItem);                                                    //freeing/deleting the node

   if(*front_ptr == NULL)                                            //case when the list becomes empty after deleting the node
     *rear_ptr = NULL;                                               //make the rear pointer NULL

   return oldItem_value;                                             //returning the deleted pt
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   UTILITY FUNCTIONS
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// reads grids from the text fie using file data handling and returns the last character read in the file
char getGrid( FILE *fptr, int **grid, point *source, point *target )
{
    int val;
    char capture_end;

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            // 8 will mean source and 9 will mean target
            // reading from text file and storing in the grid matrix
            fscanf(fptr, "%1d", &val);
            if(val == 8)
            {
                grid[i][j] = 1;
                source->x = i; source->y = j;
            }
            else if(val == 9)
            {
                grid[i][j] = 1;
                target->x = i; target->y = j;
            }
            else
            {
                grid[i][j] = val;
            }
        }
        capture_end = fgetc(fptr); // to move the file pointer to the next line
    }
    return capture_end;
}

//converts a point in the grid matrix to its equivalent point on the screen
point GridToScr( point ij , point org )
{
    point xy = { ij.y * len + org.x, ij.x * len + org.y};
    return xy;
}

// fills color in a cell of a grid on the screen
void colorCell( point cell, point origin, int fillcolor, int bordercolor )
{
    setfillstyle(SOLID_FILL, fillcolor);
    point pt = GridToScr(cell, origin);
    floodfill( pt.x, pt.y, bordercolor);
    return;
}

// draws the grid on the screen and slash fills the blocked squares
void drawGrid(int **grid, int drawcolor, int fillcolor, int fillpattern, point source, point target, point origin)
{
    // select drawing color
    setcolor(drawcolor);
    // select fill color and fill pattern
    setfillstyle(fillpattern, fillcolor);

    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            point sq_center = { origin.x + x*len, origin.y + y*len };
            rectangle( sq_center.x - len_Half , sq_center.y - len_Half, sq_center.x + len_Half, sq_center.y + len_Half );
            if( grid[y][x] == 0 )                 // x and y are screen axis coordinated, the grid coordinates are just the swap of them
                floodfill(sq_center.x, sq_center.y, drawcolor); // first two are the seed point coordinates, border color is the color which will be considered as border
            delay(25);
        }
    }
    delay(500);

    //color filling and writing the text at source and target
    colorCell( source, origin, GREEN, drawcolor );
    setbkcolor(GREEN);
    outtextxy(GridToScr(source, origin).x - 4, GridToScr(source, origin).y - 6, (char *)"A");
    delay(1000);

    colorCell( target, origin, RED, drawcolor );
    setbkcolor(RED);
    outtextxy(GridToScr(target, origin).x - 4, GridToScr(target, origin).y - 6, (char *)"B");
    delay(500);

    return;
}

// check whether given cell (x, y) is a valid cell in the grid or not.
bool isValid(int x, int y)
{
    // return true if row index and column index is in range of the grid matrix
    return (x >= 0) && (x < ROWS) &&
           (y >= 0) && (y < COLS);
}

// fills the parentRecord matrix passed to it using the grid by applying BFS
int BFS( int **grid, point source, point target, point origin, point **parentRecord )
{
    //Create a queue for BFS, front and rear pointers of the queue initially set to NULL
    queueNode *front, *rear;
    front = rear = NULL;

    // check whether source and target cells are not blocked
    if (!grid[source.x][source.y] || !grid[target.x][target.y])
        return -1;

    /* We will update the grid matrix itself to keep a track of visited cells */
    /* We will add the parent of a cell to parentRecord matrix for each cell
    /* to keep a record of how we reached it                                  */

    // Mark the source cell as visited
    grid[source.x][source.y] = 0;
    // Enqueue source cell
    enqueue(&front, &rear, source);

    // there is no parent of source cell, we started our BFS from it
    // we give a special value for parent cell of the source i.e. {-1, -1}
    parentRecord[source.x][source.y] = null_pt;

    int fillcolor = YELLOW;

    // counters for color algorithm
    int count = 0;
    int tot_count = 1;


    // Do a BFS starting from source cell
    while (!isEmpty(front))
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /* this code is used when we want each level of graph/grid to be colored differently *
        if(tot_count == 0)
        {
            tot_count = count;
            count = 0;
            fillcolor = (fillcolor + 1)%getmaxcolor();
            if(fillcolor == BLACK || fillcolor == GREEN || fillcolor == RED || fillcolor == WHITE)
                fillcolor = (fillcolor + 1)%getmaxcolor();
        }
        tot_count--;
        *//////////////////////////////////////////////////////////////////////////////////////////////////


        point curr_pt = front->pt;

        // If we have reached the target cell, we are done
        if (curr_pt.x == target.x && curr_pt.y == target.y)
            return 1;

        /*
        Else dequeue the front cell in the queue
        and enqueue its adjacent cells
        */
        dequeue(&front, &rear);

        // These arrays are used to get row and column
        // indexes of 4 neighbors of a given cell
        int rowIdx[] = {-1, 0, 0, 1};
        int colIdx[] = { 0,-1, 1, 0};

        for(int i = 0; i < 4; i++)
        {
            int row = curr_pt.x + rowIdx[i];
            int col = curr_pt.y + colIdx[i];

            // if adjacent cell is valid, is not blocked and
            // not visited yet, enqueue it.
            // We will make visited cell value as 0 as if they are blocked after visiting.
            if( isValid(row, col) && grid[row][col] )
            {
                count++;
                point cell = {row, col};
                // mark this cell as visited, record its parent, enqueue it and color it yellow
                grid[row][col] = 0;
                parentRecord[row][col] = curr_pt;  // the current pt is the parent of the enqueued cells
                enqueue(&front, &rear, cell );
                colorCell( cell, origin, fillcolor, WHITE );
            }
        }
        delay(500);
    }

    // return 0 if target cannot be reached
    return 0;
}

// reconstruct the shortest path found by BFS from target to source
void reconstructPath( point target, point origin, point **parentRecord )
{
    // array to store the path
    point path[ROWS*COLS];
    // looping through the parentRecord to get the path
    int i = 0;
    point newtarget = { target.x, target.y };
    while(newtarget.x != null_pt.x && newtarget.y != null_pt.y)
    {
        path[i++] = newtarget;
        colorCell(newtarget, origin, RED, WHITE); // coloring RED when going from target to source
        delay(250);
        newtarget = parentRecord[newtarget.x][newtarget.y];
    }
    int path_len = --i;

    // finally just to make visual, we are coloring the shortest path found with green from source to target
    for(int i = path_len-1; i >= 0; i--)
    {
        colorCell(path[i], origin, GREEN, WHITE);
        delay(100);
    }
    return;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
     MAIN STARTS HERE
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /* setting the graphics window at 1530x795 */
    initwindow(1530, 795);
//        int gd=DETECT, gm;
//        initgraph(&gd, &gm, (char *)"");


    FILE *fptr;
    fptr = fopen("Grids.txt", "r");
    // getting rows and columns count and side length of a cell on screen from the file
    fscanf(fptr, "%d", &ROWS); fgetc(fptr);
    fscanf(fptr, "%d", &COLS); fgetc(fptr);
    fscanf(fptr, "%d", &len);  fgetc(fptr);
    len_Half = len/2;


    /* dynamic allocation of 2d array
       because of the problem of passing variable size array to functions */
    //int grid[ROWS][COLS];
    int **grid = (int **)malloc(ROWS * sizeof(int *));
    for (int i=0; i < ROWS; i++)
         grid[i] = (int *)malloc(COLS * sizeof(int));
    //point parentRecord[ROWS][COLS];
    point **parentRecord = (point **)malloc(ROWS * sizeof(point *));
    for (int i=0; i < ROWS; i++)
         parentRecord[i] = (point *)malloc(COLS * sizeof(point));


    // getting the reference/origin point on the screen to draw grid
    point origin = {(getmaxx() - COLS*len)/2 , (getmaxy() - ROWS*len)/2};
    point source, target;

    // loop till we reach the end of text file i.e. all grids stored in file are simulated
    char check_end;
    while(check_end != EOF)
    {
        // if there are more grids in the file, move file pointer to the next grid
        if(check_end == '\n')
            fgetc(fptr);
        check_end = getGrid(fptr, grid, &source, &target);

        drawGrid(grid, WHITE, WHITE, SLASH_FILL, source, target, origin);
        delay(600);
        int status = BFS(grid, source, target, origin, parentRecord);

        if( status == -1 )
        {
            setbkcolor(RED);
            outtextxy( 0, 0, (char *)"Source(A) and/or Target(B) are themselves blocked!");
        }
        else if( status == 0 )
        {
            setbkcolor(RED);
            outtextxy( 0, 0, (char *)"No Target(B) found!");
        }
        else if( status == 1)
        {
            setbkcolor(GREEN);
            outtextxy( 0, 0, (char *)"Target(B) found!");
            delay(500);

            reconstructPath( target, origin, parentRecord );
        }
        getch();
        setbkcolor(BLACK);
        cleardevice();

    }

    fclose(fptr);
    closegraph();
    return 0;
}
