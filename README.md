# matrix
Repo contains a simple Matrix class template for working with 2d matrices.

features:
  * calculates determinant
  * get/set values via get() and set() member functions
  * Appropriate overloaded operators
  * Inverse matrix (IN PROGRESS)
  

example:
  
  ``` c++
  #include <iostream>
  #include "matrix.h"
  using namespace std;
  
  int main()
  {
      Matrix <short> matrix(3,3);
      matrix.setAll(5);
      matrix.set(8, 1,0);
      matrix(0,2) = 100;
      try{
          cout << matrix << endl;
          cout << "det : " << matrix.getDeterminant() << endl;
      }catch(const char *msg){
          cerr << msg << endl;
      }
      return 0;
  }
  ```
  
  output:
  ```
  5	5	100	
  8	5	5	
  5	5	5	

  det : 1425
  ```
