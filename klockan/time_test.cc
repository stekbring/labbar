#include "catch.hpp"
#include "time.h"
#include <sstream>

using namespace std;

TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{0,0,0};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }
}

TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );

   // Fill with extra corner cases!
   Time t2{"00:00:00"};
   Time t3{"12:00:00"};
   Time t4{"13:37:00"};
   CHECK       ( t2.is_am() );
   CHECK_FALSE ( t3.is_am() );
   CHECK_FALSE ( t4.is_am() );
}

TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   Time t5{0,0,0};

   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
   }
   
   SECTION("24 hour format with argument")
   {
      CHECK( t0.to_string(false) == "00:00:00" );
      CHECK( t1.to_string(false) == "11:59:59" );
      CHECK( t2.to_string(false) == "12:00:00" );
      CHECK( t3.to_string(false) == "13:00:00" );
      CHECK( t4.to_string(false) == "23:59:59" );
   } 

   SECTION("12 hour format")
   {
      CHECK( t0.to_string(true) == "12:00:00 am" );
      CHECK( t1.to_string(true) == "11:59:59 am" );
      CHECK( t2.to_string(true) == "12:00:00 pm" );
      CHECK( t3.to_string(true) == "01:00:00 pm" );
      CHECK( t4.to_string(true) == "11:59:59 pm" );
      CHECK( t5.to_string(true) == "12:00:00 am" );

   }
}

// Fill with more tests of other functions and operators!

TEST_CASE ("add time")
{
   Time t1{12, 00, 00};
   Time t2{12, 00, 59};
   Time t3{12, 59, 59};
   Time t4{23, 59, 59};
   Time t5{10, 0, 0};

   ++t1; 
   CHECK( t1.to_string() == "12:00:01" );
   
   ++t2;
   CHECK( t2.to_string() == "12:01:00" );
   
   ++t3;
   CHECK( t3.to_string() == "13:00:00" );
   
   ++t4;
   CHECK( t4.to_string() == "00:00:00" );
   
   CHECK( (t5++).to_string() == "10:00:00" ); 
   CHECK( t5.to_string() == "10:00:01" );
   CHECK( (++t5).to_string() == "10:00:02" );
}

TEST_CASE ("compare")
{
   Time t1{10, 30, 00};
   Time t2{10, 30, 00}; 
   Time t3{10, 30, 01}; 
   Time t4{11, 00, 00};

   CHECK( t1 == t2 );
   CHECK_FALSE( t1 == t3 );

   CHECK( t1 != t3 );
   CHECK_FALSE( t1 != t2 );

   CHECK( t1 < t3 );  
   CHECK( t1 < t4 );  

   CHECK_FALSE( t3 < t1 );

   CHECK( t3 > t1 );
   CHECK( t4 > t1 );

   CHECK( t1 <= t2 ); 
   CHECK( t1 <= t3 ); 
}

TEST_CASE ("Print")
{
    Time t1{13, 37, 00};
    std::ostringstream ss;
    
    ss << t1;
    
    CHECK( ss.str() == "13:37:00" );
    CHECK_FALSE( ss.str() == "12:00:00");
}