#include "catch.hpp"
#include "list.h"
#include <sstream>

using namespace std;

TEST_CASE ("Index")
{

   List empty_list {};


   SECTION ("Inserting and accessing value") 
   {
      empty_list.insert(1);

      CHECK (empty_list.index(1) == 1);


   }


   SECTION ("Removing value")
   {

   }
}

/*
TEST_CASE ("Sort")
{
   SECTION("Default")
   {
        
   

   }
}
*/