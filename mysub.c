
/*
	Kevin Carlisle
	#82682616
	CS165 
	Project # 2
	Majority Count

*/


#include <stdio.h>

void identifyIndexes(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used);
void calcMax(int n,int* s, int* x1, int* x2, int* y1, int* xScore, int* yScore);


int mysub(int n)
{

	// Indexes
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int used = 0; // Number of indexes used in identifyIndexes

	// Score Results
	int xScore = 0;
	int yScore = 0;

	// Call Function to Identify Indexes
	identifyIndexes(n, 0, &x1, &x2, &y1, &xScore, &yScore, &used);


	/*
		Identify Indexes has used "used" 
		elements to determine 2 pos for X
		& 1 for Y. Has also scored "used"
		indexes to scores of X or Y.

	*/

	// Skip calcMax if max is already determined
	if ( used < n && xScore < (n/2)+1 && yScore < (n/2)+1 )
	{ 
		// Run calcMax until end of array or until either score is > array_size/2. 
		calcMax(n, &used, &x1, &x2, &y1, &xScore, &yScore);
	}

	//printf("X1: %d X2: %d Y1: %d\n", x1, x2, y1);
	//printf("xScore: %d yScore %d Used: %d\n", xScore, yScore, used);
	//printf("SIZE/2+1: %d\n", (n/2)+1);
	//printf("SIZE: %d\n", n);


	if ( xScore > yScore )
	{
		//printf("Result: %d\n", x1);

		return x1;
	}
	else if ( yScore > xScore )
	{
		//printf("Result: %d\n", y1);

		return y1;
	}
	else 
	{
		//printf("Result: %d\n", 0);

		return 0;
	}


}

void identifyIndexes(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used)
{
	// Determine Indexes for X1, X2, Y1
	// Determine Scores for X & Y
	// Update Used
	int r1;
	int r2;

	if ( s == 0 )
	{	
		// Initial Query - Not Recursive Call
		// Run Two Queries
		int q1[4] = {1,2,3,4};
		int q2[4] = {2,3,4,5};

		// Results of Two Queries  QCOUNT - External Function Compares Array Elements
		r1 = QCOUNT(1, q1);
		r2 = QCOUNT(1, q2);
	}
	else
	{
		// Not Initial Check - Recursive Call
		// Know that Last 2 Queries -> 4, 4
		// Want to shift over 1 pos
		
		int q[4] = {s+2, s+3, s+4, s+5};

		// Set Results
		r1 = 4;
		r2 = QCOUNT(1, q);

	}

	//printf("\n\nQ1: %d Q2: %d\n", r1, r2);

	if ( r1 == 0 && r2 == 2)
	{
		// 0, 2

		// Set X1 & Y1
		*x1 = 5;
		*y1 = 1;

		// Set X2
		int perms[3][2] = {{2,3}, {2,4}, {3,4}};
		int i;
		for ( i = 0; i < 3; i++)
		{
			int a = perms[i][0];
			int b = perms[i][1];

			int t[4] = {*x1, a, b, *y1};

			int r = QCOUNT(1, t);

			if ( r == 2 )
			{
				// Set X2
				*x2 = a;
				break;
			}
		}

		// X2 is Set. 
		// Update Scores
		*xScore = 3;
		*yScore = 2;

		// Update Used
		*used = 5;

	}
	else if ( r1 == 2 && r2 == 0)
	{
		// 2, 0

		// CODED AT NIGHT RECHECK!!

		// Set X1 & Y1
		*x1 = 1;
		*y1 = 5;

		// Set X2
		int perms[3][2] = {{2,3}, {2,4}, {3,4}};
		int i;
		for ( i = 0; i < 3; i++)
		{
			int a = perms[i][0];
			int b = perms[i][1];

			int t[4] = {*x1, a, b, *y1};

			int r = QCOUNT(1, t);

			if ( r == 2 )
			{
				// Set X2
				*x2 = a;
				break;
			}
		}

		// X2 is Set. 
		// Update Scores
		*xScore = 3;
		*yScore = 2;

		// Update Used
		*used = 5;
	}
	else if ( r1 == 0 && r2 == 0)
	{
		// 0, 0

		// CODED AT NIGHT RECHECK!!

		// Set X1 & X2
		*x1 = 1;
		*x2 = 5;

		// Set Y1
		int perms[3][2] = {{2,3}, {2,4}, {3,4}};
		int i;
		for ( i = 0; i < 3; i++)
		{
			int a = perms[i][0];
			int b = perms[i][1];

			int t[4] = {*x1, a, b, *x2};

			int r = QCOUNT(1, t);

			if ( r == 0 )
			{
				// Set Y1
				*y1 = a;
				break;
			}
		}

		// Y1 is Set. 
		// Update Scores
		*xScore = 3;
		*yScore = 2;

		// Update Used
		*used = 5;

	}
	else if ( r1 == 2 && r2 == 2)
	{
		// 2, 2

		// CODED AT NIGHT RECHECK!!

		// Set X1 & X2
		*x1 = 1;
		*x2 = 5;

		// Set Y1
		int perms[3][3] = {{2,3,4}, {2,4,3}, {3,4,2}};
		int sum = 0;

		int i;
		for ( i = 0; i < 3; i++)
		{
			int a = perms[i][0];
			int b = perms[i][1];
			int c = perms[i][2];

			int t[4] = {*x1, a, b, *x2};

			int r = QCOUNT(1, t);

			sum = sum + r;

			if ( r == 4 )
			{
				// Set Y1
				*y1 = c;
				break;
			}
		}
		
		if ( sum == 0 )
		{
			// Case 1 -> 10001
			// Set Y to any 2, 3, 4
			*y1 = 2;

			// Set Scores
			*xScore = 2;
			*yScore = 3;
		}
		else
		{
			// Case 2 -> 01000
			// Y Is Set in for loop above
			// Set Scores
			*xScore = 4;
			*yScore = 1;
		}

		// Update Used
		*used = 5;

	}
	else if ( r1 == 2 && r2 == 4)
	{
		// 2, 4

		// Set X1 & X2
		*x1 = 2;
		*x2 = 3;

		// Set Y1
		*y1 = 1;

		// Set Scores
		*xScore = 4;
		*yScore = 1;

		// Update Used
		*used = 5;

	}
	else if ( r1 == 4 && r2 == 2)
	{
		// 4, 2 

		// ** Only End Case for Recursive Call **

		// Set X1 & X2
		*x1 = 1;
		*x2 = 2;

		// Set Y1
		*y1 = 5 + s;

		// Set Scores
		*xScore = *xScore + s + 4;
		*yScore = 1;

		// Update Used
		*used = *used + s +  5;

	}
	else if ( r1 == 4 && r2 == 4)
	{
		// 4, 4 
		// Need to Check Next Pos
		// Make recursive call 
		if ( s + 5 < (n/2 + 1) )
		{
			// If not indexing outside of the array
			identifyIndexes(n, s+1, x1, x2, y1, xScore, yScore, used);

		}
		else
		{
			// If array is filled with same number 000...0
			// Only need to look at half the array to determine max element. 
			*used = n/2 +1;
			*xScore = n/2 + 1;
			*yScore = 0;

			*x1 = 1;
			*x2 = 2;
			// Set y1 -1 indicate not found
			*y1 = -1;
		}

	}
	else
	{
		// All Cases Should be Handled
		printf("Error** - Else Not Handled\n");
	}
}

void calcMax(int n, int* s, int* x1, int* x2, int* y1, int* xScore, int* yScore)
{
	//printf("calcMax\n");
	int r;
	//printf("xScore: %d yScore %d Used: %d\n", *xScore, *yScore, *s);

	// Used Saved Values X1 & X2 to make queries
	//while ( (*s + 1) < n && *xScore < ((n/2)+2) && (*yScore < (n/2)+2) )
	while ( (*s +2 ) <= n  )

	{

		int q[4] = {*x1, *x2, *s+1, *s+2};

		// Set Result
		r = QCOUNT(1, q);

		// increment s
		*s += 2;

		// Determine cases to score X & Y
		if ( r == 0 )
		{
			// xxyy
			*yScore += 2;
		}
		else if ( r == 2 )
		{
			// xxxy || xxyx
			*xScore += 1;
			*yScore += 1;
		}
		else if ( r == 4)
		{
			// xxxx
			*xScore += 2;
		}
		else
		{
			// Error 
			printf("***ERROR CALC MAX: %d\n", r);
		}
		//printf("xScore: %d yScore %d Used: %d\n", *xScore, *yScore, *s);



	}
	//printf("BEFORE SINGLE CASE: S: %d N/2+1: %d\n", *s, (n/2)+1);
	// Handle Single Case
	//if ( *xScore < (n/2)+1 && *yScore < (n/2)+1 && *s <= n)
	if (  *s <= n)

	{
		// S will be incremented past n to break out of above for loop
		// Run query on last remaining index
		int q[4] = {*x1, *x2, *y1, *s+1};

		// Update s
		*s += 1;

		// Set Result
		r = QCOUNT(1, q);

		// Determine case to score X & Y
		if ( r == 0 )
		{
			// xxyy
			*yScore +=1;
		}
		else if ( r == 2 )
		{
			// xxyx
			*xScore +=1;
		}

		//printf("Inside Single CASE: S: %d N/2+1: %d\n", *s, (n/2)+1);

		//printf("xScore: %d yScore %d Used: %d\n", *xScore, *yScore, *s);


	}

}





