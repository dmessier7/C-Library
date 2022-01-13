#include "Cherno_Notes.h"
#include <iostream> //a preprocesser statement
// copies the file and all its dependencies into this file
// #if and #endif are preprocesser statements that include the code that
//follows depending on conditions
//#ifndef _FILENAME_H #endif is used to check if something was already defined
// and define it if it has not been as to avoid errors

//declaration is a promise to the compiler that a thing exists in another
// file that will be linked by the linker

class Entity
{
public:
  float X;
  float Y;
  float Z;

  Entity() // Constructor
  {
    Z = 5.5f;
  }
  Entity(float x, float y) //Also a constructor
  {
    X = x;
    Y = y;
  }

  ~Entity() //Destructor
  {
    std::cout << "Destroyed Entity" <<std::endl;
  }
};


int main()
{
  Entity objectEx(10.0f, 10.0f);
  delete objectEx;
  std::cin.get();
}
