/************************************************************************
*
*  lap.h
   version 1.0 - 21 june 1996
   author  Roy Jonker, MagicLogic Optimization Inc.
   
   header file for LAP
*
**************************************************************************/

/*************** CONSTANTS  *******************/

  #define BIG 100000

/*************** TYPES      *******************/

  typedef int row;
  typedef int col;
  typedef float cost;
//  typedef int boolean;

/*************** FUNCTIONS  *******************/

template<class T>extern T lap(int dim, T **assigncost,
               int *rowsol, int *colsol, T *u, T *v);

template<class T>extern void checklap(int dim, T **assigncost,
                     int *rowsol, int *colsol, T *u, T *v);

