//============================================================================
// Name        : NQueens.cpp
// Author      : Disha Chavan
// Version     :
// Copyright   : Your copyright notice
// Description : Nqueens problem using backtracking
//============================================================================

#include <iostream>
#define MAX 20
using namespace std;


class NQueens{									// class to solve n queens problem
	int N ;										// N is the number of queens and dimension of board
	int chessboard[MAX][MAX] ;					// 2D matrix for chessboard

public:
	NQueens(){									// constructor to initialize data members
		N = 0 ;
		for(int i=0; i<MAX; i++)
					for(int j=0; j<MAX; j++)
						chessboard[i][j] = 0 ;
	}

	void setN(){								// take input for value of N
		cout << "\nEnter N: " << endl ;
		cin >> N ;

	}

	bool checkSafe(int row, int col){			// function to check if the position for the queen to be placed is safe or not

		for(int i=0; i<col; i++){				// places in same column of queen is not safe
			if(chessboard[row][i])
				return false;
		}
		int i,j ;
		for (i = row, j = col; i >= 0 && j >= 0; i--, j--)	// places in diagonal are not not safe
			if(chessboard[i][j])
				return false;

		    /* Check lower diagonal on left side */
		    for ( i = row,  j = col; j >= 0 && i < N; i++, j--)
		        if (chessboard[i][j])
		            return false;
		return true ;
	}

	bool solveNqueen(int col){					// function to solve n queens problem
		if(col>=N)								// when all queens are placed
			return true ;

		for(int i=0; i<N; i++){					// placing queens row wise
			if(checkSafe(i,col)){				// if place is safe
				chessboard[i][col] = 1 ;		// add queen on that position

			if(solveNqueen(col+1))				// for further queens to be placed call function again
				return true ;

			chessboard[i][col] = 0 ;			// removing queen if there is no solution
			}

		}

		return false;
	}

	void printBoard(){							// function to print chess board
		for(int i=0 ; i<N; i++){
			for(int j=0 ; j<N; j++){
				cout << chessboard[i][j] << " " ;
			}
			cout << "\n" ;
		}
	}
};
int main() {

	NQueens obj ;
	do{
		int choice ;
		cout << "\nEnter choice: \n1.N queens problem using backtracking\n2.Exit" ;
		cin >> choice ;
		if(choice == 1){
			obj.setN();
				if(obj.solveNqueen(0) == false)
					cout << "\nNo solution" ;
				else
					obj.printBoard() ;
		}
		else
			break ;

	}while(1) ;


}
