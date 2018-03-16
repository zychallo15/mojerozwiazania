//
// Created by michal on 16.03.18.
//

#include "Array2D.h"

int **NewArray2D(int n_rows, int n_columns)
{
    if(n_rows<=0 || n_columns<=0)
    {
        return nullptr;
    }
    auto **tab= new int *[n_rows];
    for(int i=0;i<n_rows;i++)
    {
        tab[i]= new int [n_columns];
    }
    return tab;
}

int **FillArray2D(int k_rows, int k_cols, int ** to_fill)
{
    int x=1;
    for(int i=0;i<k_rows;i++)
    {
        for(int j=0;j<k_cols;j++)
        {
           to_fill[i][j]=x;
            x++;
        }
    }
    return to_fill;
}

int **Array2D(int n_rows, int n_columns)
{
    int **tab=NewArray2D(n_rows, n_columns);
    tab=FillArray2D(n_rows,n_columns,tab);
    return tab;
}



void DeleteArray2D(int **array, int n_rows, int n_columns)
{
    for(int i=0;i<n_rows;i++)
    {
        delete [] array[i];
    }
    delete [] array;
}