//============================================================================
// Name        : KnapsackProblem.cpp
// Author      : Disha Chavan
// Class 	   : TE 10
// Batch       : L 10
// Roll No     : 33212
// Description : Knapsack problem
//============================================================================

#include <iostream>
#include <chrono>
# define MAX 10
#include <bits/stdc++.h>
using namespace std;

class item{
public:
	int value ;				// attributes of item
	int weight ;

	item(){					// constructor of item
		value = 0 ;
		weight = 0 ;
	}

};

bool comparer(item i1, item i2){	// method used while sorting items to sort by their ratio of value and weight
	float v1 = float(i1.value)/float(i1.weight) ;
	float v2 = float(i2.value)/float(i2.weight) ;
	return (v1 > v2) ;
}

class KnapSack{
	int W,N ;			// W is weight of knapsack and N is number of items
	item items [MAX] ;	// array of items
public:
	KnapSack(){			// constructor to initialize
		W = 0 ;
		N = 0 ;
	}
	void input(){		// method to take input for items

		do{												// Validation for number of items
			cout << "\nEnter number of items: " ;
			cin >> N ;
			if(N < 0 || N > MAX){
				cout << "\nInvalid Value! Please enter non negative or value less than 10!" << endl ;
			}
			else break ;

		}while(true) ;


		for(int i = 0 ; i < N ; i++ ){			// loop to take values and weights for items
			do{									// loop for validating items
				cout << "\nEnter value: " ;
				cin >> items[i].value ;
				cout << "\nEnter weight: " ;
				cin >> items[i].weight ;
				if(items[i].value < 0 || items[i].weight < 0){
					cout << "\nInvalid Value! Please enter non negative value!" << endl ;
				}
				else break ;
			}while(true) ;

		}

		do{									// Validation for knapsack weight
			cout << "\nEnter knapsack weight: " ;
			cin >> W ;
			if(W < 0){
				cout << "\nInvalid Value! Please enter non negative or value less than 10!" << endl ;
			}
			else break ;

		}while(true) ;

	}

	bool checkItems(){						// function to check if items are entered
		if(N == 0) return false ;
		else return true ;
	}

	void display(){							// function to display item info
		cout << "\n======================================================================================" << endl ;
		cout << "\tValue\tWeight" ;
		cout << "\n======================================================================================" << endl ;
		for(int i = 0 ; i < N ; i++){
			cout << "\nitem" << (i+1) << "\t" << items[i].value << "\t" << items[i].weight << endl ;
		}
		cout << "\n======================================================================================" << endl ;
	}
	void knapsack01(){						// function to calculate knapsack weight using dynamic approach

			int DP[N+1][W+1];				// 2D array for storing max applicable weight

			for(int i= 0 ; i<=N ; i++){		// loop for item
				for(int j = 0 ; j<=W ; j++) // loop for knapsack weight
				{
					if(i == 0 || j == 0){	// if knapsack weight is 0
						DP[i][j] = 0 ;
					}
					else if(items[i-1].weight <= j){
						DP[i][j] = max(items[i-1].value + DP[i-1][j-items[i-1].weight] , DP[i-1][j] ) ;
					}
					else{
						DP[i][j] = DP[i-1][j] ;
					}
				}

			}
			cout << "\n======================================================================================" << endl ;
			cout << "\nKnapsack Value: " << DP[N][W] << endl ;
			cout << "\n======================================================================================" << endl ;


		}
	void fractional_knapsack(){				// function to calculate fractional knapsack with greedy approach
		sort(items, items+N, comparer) ;	// sort items according to ratio
		int currWeight = 0 ;
		int currValue = 0 ;

		for(int i = 0 ; i < N ; i++ ){		// loop to calculate knapsack value

			if(items[i].weight + currWeight <= W ){		// the weight should be less than knapsack weight
				currWeight = items[i].weight + currWeight ;
				currValue = items[i].value + currValue ;
			}
			else{							// considering fractional weight
				int temp = W-items[i].weight ;
				if(temp + currWeight <= W ){
					currWeight = temp + currWeight ;
					float ratio = (float)items[i].weight / (float)temp ;
					int val = items[i].value / ratio ;
					currValue = currValue + val ;
				}
				else{
					break ;
				}
			}
		}
		cout << "\n======================================================================================" << endl ;
		cout << "\n Kanpsack Value: " << currValue ;
		cout << "\n======================================================================================" << endl ;
	}


};


int main() {								// main method
	KnapSack obj  ;
	int choice = 0 ;
	do{						// loop for menu
		cout << "\n---------------------------------------------------------------------------------------------" << endl ;
		cout << "\nEnter Choice: \n1.Input items\n2.Display items\n3.Apply Fractional Knapsack\n4.Apply 0/1 Knapsack\n5.Exit" << endl ;
		cout << "\n---------------------------------------------------------------------------------------------" << endl ;
		cin >> choice ;
		switch(choice){
		case 1 : obj.input();
				 cout << "\nItems entered Successfully !!" << endl ;
				 break ;
		case 2 : if(!obj.checkItems()) cout << "\nNo Items entered to display!" << endl ;
				 else{
					 cout << "\nItems entered are : " ;
					 obj.display() ;
				 }
				 break ;
		case 3 : if(!obj.checkItems()) cout << "\nNo Items entered to display!" << endl ;
		 	 	 else{
		 	 		 cout << "\nItems entered are : " ;
		 	 		 obj.display() ;
		 	 		 auto start = chrono::high_resolution_clock::now();
		 	 		 obj.fractional_knapsack() ;
		 	 		 auto end = chrono::high_resolution_clock::now();
		 	 	     double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		 	 		 time_taken *= 1e-9;
		 	 		 cout << "Time taken by program is : " << fixed << time_taken << setprecision(9);
		 	 	     cout << " sec" << endl;
		 	 	 }
				 break ;
		case 4: if(!obj.checkItems()) cout << "\nNo Items entered to display!" << endl ;
				 else{
					 cout << "\nItems entered are : " ;
					 obj.display() ;
					 auto start = chrono::high_resolution_clock::now();
					 obj.knapsack01() ;
					 auto end = chrono::high_resolution_clock::now();
					 double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
					 time_taken *= 1e-9;
					 cout << "Time taken by program is : " << fixed << time_taken << setprecision(9);
					 cout << " sec" << endl;
				 }
				 break ;
		case 5 : cout << "\nThankyou!" << endl ;
				 break ;

		default: cout << "\nInvalid choice!" << endl ;
		}
	}while(choice != 5) ;



}
