// BEGIN CUT HERE
// PROBLEM STATEMENT
// Fox Ciel is going to play Gomoku with her friend Fox Jiro.
Ciel plays better, so before they start she allowed Jiro to put some of his pieces on the board.


You are given a vector <string> board that represents a square board.
The character board[i][j] represents the cell with coordinates (i,j).
Each of those characters is either '.' (representing an empty cell) or 'o' (representing a cell with Jiro's piece).


Of course, Ciel does not want Jiro to win the game before she has a chance to play.
Thus she now has to check the board and determine whether there are five consecutive tokens somewhere on the board.


Determine whether there are 5 consecutive cells (horizontally, vertically, or diagonally) that contain Jiro's tokens.
Return "found" (quotes for clarity) if there are five such cells anywhere on the board.
Otherwise, return "not found".

DEFINITION
Class:FoxAndGomoku
Method:win
Parameters:vector <string>
Returns:string
Method signature:string win(vector <string> board)


CONSTRAINTS
-n will be between 5 and 15, inclusive.
-board will contain exactly n elements.
-Each element in board will contain exactly n characters.
-Each character in board will be 'o' or '.'.


EXAMPLES

0)
{"....o.",
 "...o..",
 "..o...",
 ".o....",
 "o.....",
 "......"}

Returns: "found"

There is five continue pieces diagonally.

1)
{"oooo.",
 ".oooo",
 "oooo.",
 ".oooo",
 "....."}
 

Returns: "not found"

There is no five-in-a-row on this board.

2)
{"oooo.",
 ".oooo",
 "oooo.",
 ".oooo",
 "....o"}
 

Returns: "found"

Five consecutive tokens can be found in the following cells: (0,0), (1,1), (2,2), (3,3), and (4,4).

3)
{"o.....",
 ".o....",
 "..o...",
 "...o..",
 "....o.",
 "......"}

Returns: "found"



4)
{"o....",
 "o.o..",
 "o.o.o",
 "o.o..",
 "o...."}

Returns: "found"



5)
{"..........",
 "..........",
 "..oooooo..",
 "..o.......",
 "..o.......",
 "..oooooo..",
 ".......o..",
 ".......o..",
 "..oooooo..",
 ".........."}
 


Returns: "found"



6)
{"..........",
 "..........",
 "..oooo.o..",
 "..o.......",
 "..o.......",
 "..o.oooo..",
 ".......o..",
 ".......o..",
 "..oooo.o..",
 ".........."}


Returns: "not found"



7)
{"ooooo",
 "ooooo",
 "ooooo",
 "ooooo",
 "ooooo"}

Returns: "found"



8)
{".....",
 ".....",
 ".....",
 ".....",
 "....."}

Returns: "not found"



// END CUT HERE
#line 155 "FoxAndGomoku.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;

class FoxAndGomoku {
	public:
  bool check(vector<string> &b, int x, int y, int n, int m, int dx, int dy) {
    int rv = 1, tx = x, ty = y;
    for (int i = 0; i < 5; i++) {
      x = x+dx, y = y+dy;
      if (0 <= x && x < n && 0 <= y && y < m && b[x][y] == 'o')
        rv++;
      else break;
    }
    x = tx, y = ty;
    for (int i = 0; i < 5; i++) {
      x = x-dx, y = y-dy;
      if (0 <= x && x < n && 0 <= y && y < m && b[x][y] == 'o')
        rv++;
      else break;
    }
    return rv >= 5;
  }
	string win(vector <string> b) {
    int n = b.size(), m = b[0].length(), yes = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (b[i][j] == 'o')
          yes |= check(b, i, j, n, m, 0, 1)
            | check(b, i, j, n, m, 1, 1)
            | check(b, i, j, n, m, 1, 0)
            | check(b, i, j, n, m, 1, -1);
    return yes? "found": "not found";
	}
};
