#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using std::endl; using std::cout;
using std::find;
using std::vector;
using std::fixed; using std::setprecision;
using std::iterator;


const int TOBE_SEARCHED = 5000;

/*                                                                genRndNums()

   Parameters:
       v - 'v' is a vector<int> that will act as a container for the numbers
          being stored.

       vec_size - the size of how long the vector is and how many numbers will be
          put in the vector

       seed - the number being used to generate random numbers via the "srand()"
          function.

   Objective:
       This is a function that will generate a random number between the values
       between 1 and 10000 and push that value into the vector 'v' via a for loop.

   Return:
       Void function - won't return a value


******************************************************************************/
void genRndNums( vector<int>& v, int vec_size, int seed )
{
    srand(seed);

    int i, rn;

    for (i=0; i<vec_size; i++)
    {
        rn = rand()%10000 + 1;
        v.push_back(rn);
    }
}



/*                                                                linearSearch()
   Parameters:
      const vector<int>& v - the vector container being searched.
      int x - represents the number being searched for.

   Objectives:
      Searches the vector linearly using the find() function.

   Returns:
      Returns a number that represents the position of the item found if
      it != v.end(), else it will return -1.

******************************************************************************/
int linearSearch( const vector<int>& v, int x)
{

     vector<int>::const_iterator it = find(v.begin(), v.end(), x);

     if(it != v.end())
        return (it - v.begin());
     else
        return -1;
}



/*                                                                binarySearch()
   Parameters:
      const vector<int>& v - vector container
      int x - represents the number being searched for

   Objectives:
      The point of this function is to call the function equal_range and get the
      values that represent the upper and lower bounds. You can compare these
      numbers and return a value.

   Returns:
      The value being returned represents the position of the found item if
      bounds.first != bounds.second else it will return -1.

******************************************************************************/
int binarySearch( const vector<int>& v, int x)
{

    std::pair<vector<int>::const_iterator, vector<int>::const_iterator> bounds;
    bounds = equal_range(v.begin(),v.end(), x);

    if (bounds.first != bounds.second)
        return (bounds.first - v.begin());
    else
        return -1;
}




/*                                                                      search()
   Objective:
      The objective of the function is to search through the searchNums values in
      the container vector and test if they successfully searched.

   returns:
        the total number of times a successful search occured.

******************************************************************************/
int search( const vector<int>& container, const vector<int>& searchNums,
            int (*p)( const vector<int>&, int) )
{
    int count = 0;
    int vec_size = searchNums.size();

    for (int i = 0; i < vec_size; i++)
    {
        if ( p(container, searchNums[i]) > -1 )
        {
           count++;
        }
    }
    return count;
}


/*                                                                   sortVec()
   Objective:
       The objective of this function is to sort vector 'v'.

   Returns:
       void - function returns no value.

******************************************************************************/
void sortVec (vector<int>& v)
{
    sort(v.begin(), v.end());
}



/*                                                                  printStat()
  Paramters:
       int totalSucCnt - integer that represents the value of total times a
                         successful search had taken place.
       int vec_size - represents the value of the total number of numbers in the
                      container vector.
  Objectives:
       The objective of the this function was to calculate a float value from the
       paramters and print the percent of successful searches.

  returns:
       void - function returns no value.

******************************************************************************/
void printStat (int totalSucCnt, int vec_size)
{
   float vec_percent = (static_cast<float>(totalSucCnt) / static_cast<float>(vec_size)) * 100;
   cout << "Successful searches: " << fixed << setprecision(2) << vec_percent;
   cout << "%" << endl;
}




                                                                   //main() start
int main() {
    vector<int> container, tobeSearched;
    genRndNums(container, 10000, 7);
    genRndNums(tobeSearched, TOBE_SEARCHED, 5);

    cout << "\nConducting linear search ..." << endl;
    int linear_search_count = search( container, tobeSearched, linearSearch );
    printStat ( linear_search_count, TOBE_SEARCHED );


    cout << "\nConducting binary search on unsorted container ..." << endl;
    int binary_search_count = search( container, tobeSearched, binarySearch );
    printStat ( binary_search_count, TOBE_SEARCHED );

    sortVec( container );

    cout << "\nConducting binary search on sorted container ..." << endl;
    binary_search_count = search( container, tobeSearched, binarySearch );
    printStat ( binary_search_count, TOBE_SEARCHED );

    return 0;
}



