
/*
	Kevin Carlisle
	#82682616

	Nicholas Steven Popov
	#

	CS165 
	Project # 2
	Majority Count

*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

void identifyIndexes(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used);
void exploreByFour(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used);
void processTwos(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used,
					int indicesArray[], int twosArray[], int twoLen, int l);
void processFours(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used,
					int indicesArray[], int foursArray[], int fourLen,  int l);
void processRemaining(int n,int* s, int* x1, int* x2, int* y1, int* xScore, int* yScore);


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

	// Process By Fours
	exploreByFour(n, 0, &x1, &x2, &y1, &xScore, &yScore, &used);

	// Skip processRemaining if max is already determined
	if ( used < n && xScore < (n/2)+1 && yScore < (n/2)+1 )
	{ 
		// Run processRemaining until end of array or until either score is > array_size/2. 
		processRemaining(n, &used, &x1, &x2, &y1, &xScore, &yScore);
	}

	// Return Result - Index Of Majority Element Or 0 if no majority element
	if      ( xScore > yScore ) { return x1; }
	else if ( yScore > xScore ) { return y1; }
	else                        { return 0;  }

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

	// Handle Cases of R1 & R2
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
		perror("QCOUNT Error - Identify Indices");
	}
}

void exploreByFour(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used)
{
	// n Size of Initial Array
	// s Depth of Recursive call 0 if none

	// Count 4's

	// Break up original indicies array into seperate arrays

	int i, j;
	// Calculate Number of 4's Array
	int l = (n-*used)/4;
	// Create Two Dimensional Array of size l
	int indicesMD[l][4];
	int indicesSD[l*4];

	// Create Array of Indicies with Query Result of 2
	int twosArray[l];
	memset(twosArray, -1, l*sizeof(int));
	// Create Array Of Indicies with Query Result of 4
	int foursArray[l];
	memset(foursArray, -1, l*sizeof(int));


	// Fill Array with Indicies 
	for ( i = *used, j = 0; i + 4 <= n; i += 4, j++ )
	{
		// Multi Dimensional
		indicesMD[j][0] = i+1;
		indicesMD[j][1] = i+2;
		indicesMD[j][2] = i+3;
		indicesMD[j][3] = i+4;

		// Single Dimensional
		indicesSD[j] = i+1;
		indicesSD[j+1] = i+2;
		indicesSD[j+2] = i+3;
		indicesSD[j+3] = i+4;
	}

	// Query Four Array & Store in FourResults	
	int twosCounter = 0;
	int foursCounter = 0;
	for ( i = 0; i < l; i++)
	{
		int temp = QCOUNT(1, indicesMD[i]);

		// Split By Result
		if ( temp == 0)
		{
			// 1010 -> Increment Both
			*xScore += 2;
			*yScore += 2;

		}
		else if ( temp == 2)
		{
			// 1000 || 0001 -> Add to twosArray
			// index in array corresponds to index in indicesArray
			// -1 if not valid
			twosArray[twosCounter] = i;
			twosCounter++;

		}
		else if ( temp == 4 )
		{
			// 1111 | 0000 -> Add to foursArray
			// index in array corresponds to index in indicesArray
			// -1 if not valid
			foursArray[foursCounter] = i;
			foursCounter++;
		}
		else
		{
			// QCOUNT ERROR
			perror("QCOUNT Error: exploreByFour -> Bad Val");

		}

		// CHECK FOR EARLY STOPAGE
		if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
		{
			return;
		}
	}

	// Process 4's Array
	processFours(n, 0, x1, x2, y1, xScore, yScore, used, indicesSD, foursArray, foursCounter, l);

	// Process 2's Array
	processTwos(n, 0, x1, x2, y1, xScore, yScore, used, indicesSD, twosArray, twosCounter, l);

	// Set Used To Handle Left Over
	int left = (n-*used)%4;
	*used = n-left;

}

void processTwos(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used,
	int indicesArray[], int twosArray[], int twoLen, int l)
{
	int i; 
	int j;
	int c = 0;

	int t = 0;
	// Create Array Of Indicies that are still unclassfied
	// Will be paired 11000011001100
	int subTwos[ 2*twoLen];
	memset(subTwos, -1, 2*twoLen*sizeof(int));


	for ( i = 0; i < twoLen; i++)
	{
		// Look at each 2 Case one at a time

		// Set 1st & 2nd Index
		int v1 = indicesArray[twosArray[i]];
		int v2 = indicesArray[twosArray[i]]+1;

		int temp[4] = {*x1, *x2, v1, v2};

		int r = QCOUNT(1, temp);

		if ( r == 4)
		{
			// 11 | 11 01
			*xScore += 3; 
			*yScore += 1;
		}
		else if ( r == 0)
		{
			// 11 | 00 01
			*xScore += 1; 
			*yScore += 3;
		}
		else if ( r == 2)
		{
			// 11 | 01 

			// Score What we looked at
			*xScore += 1; 
			*yScore += 1;

			// Send 3rd & 4th to array to process later
			subTwos[t]   = indicesArray[twosArray[i]]+2;
			subTwos[t+1] = indicesArray[twosArray[i]]+3;

			t += 2;

		}
		else 
		{
			perror("QCOUNT - Invalid Result - Process Twos Else");
		}

		if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
		{
			return;
		}

	}
	//printf("T: %d\n", t);

	for ( i = 0; i+4 <= t; i+=4)
	{
		// Process 2 at a time
		// Know that array is formatted:
		// 110011001111000011
		// Process subTwos
		int v3 = subTwos[i];
		int v4 = subTwos[i+2];

		int temp[4] = {*x1, *x2, v3, v4};

		int r = QCOUNT(1, temp);

		if ( r == 0)
		{
			// 11 | 00 00
			*yScore += 4; 
		}
		else if ( r == 2)
		{
			// 11 | 00 01
			*xScore += 2; 
			*yScore += 2;
		}
		else if ( r == 4 )
		{
			// 11 | 11 11
			*xScore += 4; 
		}
		else 
		{
			perror("QCOUNT - Invalid Result - Process Twos Else If Else");
		}

		if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
		{
			return;
		}

	}

	// Process Left
	int left = t%4;
	if ( left == 2 )
	{
		// Process Final 2
		int v5 = subTwos[t-1];
		int v6 = subTwos[t-2];

		int temp[4] = {*x1, *x2, v5, v6};

		int r = QCOUNT(1, temp);

		if ( r == 0)
		{
			// 11 | 00
			*yScore += 2; 
		}
		else if ( r == 4)
		{
			// 11 | 11
			*xScore += 2; 
		}
		else 
		{
			perror("QCOUNT - Invalid Result - Process Twos Else If Else");
		}

		if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
		{
			return;
		}

	}
	


}

void processFours(int n, int s, int* x1, int* x2, int* y1, int* xScore, int* yScore, int* used,
	int indicesArray[], int foursArray[], int fourLen, int l)
{
	int i;
	int j = 0;
	int c = 0;

	for ( i = 0; i < fourLen-1; i+=2)
	{
		// Get Index from each array
		int v1 = indicesArray[foursArray[i]];
		int v2 = indicesArray[foursArray[i+1]];

		int temp[4] = { *x1, *x2, v1, v2 };
		
		int r = QCOUNT(1, temp);

		if ( r == 0)
		{
			// 11 00 
			*yScore += 8;
		}
		else if ( r == 2)
		{
			// 11 01 || 11 10
			*xScore += 4;
			*yScore += 4;
		}
		else if ( r == 4)
		{
			// 1111
			*xScore += 8;
		}
		else 
		{
			perror("QCOUNT - Invalid Result - Process Fours Else");
		}

		// Early Stoppage
		if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
		{
			return;
		}
		c++;
	}

	// Early Stoppage
	if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
	{
		return;
	}

	// Handle Last Cast
	if (c*2 != fourLen)
	{

		int v1 = indicesArray[foursArray[fourLen-1]];
		int v2 = indicesArray[foursArray[fourLen-1]]+1;

		int temp[4] = {*x1, *x2, v1, v2};

		int r = QCOUNT(1, temp);

		if ( r == 0)
		{
			// 11 00 
			*yScore += 4;
		}
		else if ( r == 2)
		{
			// 11 01 || 11 10
			*xScore += 2;
			*yScore += 2;
		}
		else if ( r == 4)
		{
			// 1111
			*xScore += 4;
		}
		else 
		{
			perror("QCOUNT - Invalid Result - Process Fours Last Case");
		}

	}
}

void processRemaining(int n, int* s, int* x1, int* x2, int* y1, int* xScore, int* yScore)
{
	int r;

	// Used Saved Values X1 & X2 to make queries
	while ( (*s + 2) <= n && *xScore < ((n/2)+1) && (*yScore < (n/2)+1) )
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
			perror("QCOUNT - Invalid Result - Calc Max");
		}

		// Early Stoppage
		if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
		{
			return;
		}

	}

	// Early Stoppage
	if (*xScore > (n/2)+1 || *yScore > (n/2)+1)
	{
		return;
	}

	// Handle Single Case
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
	}

}





