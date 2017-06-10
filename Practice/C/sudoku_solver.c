#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ROW 0
#define COL 1

/* Search key in row_col(0:row 1:col) of 9x9 sudoku */
int search_key(int key, int row_col, int row_col_num, int sudoku[][9], int start_index)
{
    int index;
    for (index = start_index; index < 9; index++) {
        if (row_col == ROW) {
           if(key == sudoku[row_col_num][index]) {
              return index;
           }
        } else if (row_col == COL) {
            if (key == sudoku[index][row_col_num]) {
                return index;
            }
        }
    }
    return -1;
}

int
search_key_in_row_col(int row_col, int row_col_num, int sudoku[][9], int start_index)
{
    int index;
    for (index = start_index; index < 9; index++) {
       if (row_col == ROW) {
          if (sudoku[row_col_num][index] != 0) {
              return index;
          }
       } else if (row_col == COL) {
           if (sudoku[index][row_col] != 0) {
               return index;
           }
       }
    }
    return -1;
}

void
take_input(int sudoku[][9]) 
{
    int row, col, key, key_count, col_index;
    for (row = 1; row <= 9; row++) {
        printf("\nEnter count of keys in row-%d: ",row);
        scanf("%d",&key_count);
        for (col = 1; col <= key_count; col++) {
            printf("\Enter col index(1..9): ");
            scanf("%d",&col_index);
            printf("Enter key for sudoku[%d][%d]: ",row, col_index);
            scanf("%d",&key);
            sudoku[row-1][col_index-1] = key;
        }
    }
}

void
show_sudoku(int sudoku[][9])
{
    int row, col;
    printf("\nSUDOK::\n");
    printf("----------\n");
    for (row = 0; row < 9; row++) {
        printf("    ");
        for (col = 0; col < 9; col++) {
            printf("    %d",sudoku[row][col]);
        }
        printf("\n\n");
    }
}

void
solve_sudoku(int sudoku[][9])
{
    int i, j, k, m, n, index;
    index = search_key_in_row_col(ROW, 0, sudoku, 0);
    key = sudoku[0][index];
    search_key(key, ROW, 1, sudoku, 0);
    search_key(key, ROW, 2, sudoku, 0);


}

int
main()
{
   int sudoku[9][9];
   memset(&sudoku, 0, sizeof(sudoku));
   take_input(sudoku);
   show_sudoku(sudoku);

   return 0;
}
