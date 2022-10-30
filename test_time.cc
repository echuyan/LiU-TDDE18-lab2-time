#include "catch.hpp"
#include "Time_text.h"
#include <sstream>

using namespace std;


// TODO: Complementary work. You need to test all of your
// functionality, eg << och >> operators as well.
//---DONE---

TEST_CASE("Creating time structs")
{
    Time t0{20, 01, 31};
    CHECK(t0.hh == 20);
    CHECK(t0.mm == 01);
    CHECK(t0.ss == 31);

    Time t1{};
    REQUIRE(t1.hh == 00);
    REQUIRE(t1.mm == 00);
    REQUIRE(t1.ss == 00);
}

TEST_CASE("is_am")
{
    Time t0{11,59,59};
    CHECK(is_am(t0));
	  Time t1{13,59,59};
	REQUIRE_FALSE(is_am(t1));
}

TEST_CASE("is_valid")
{
    Time t0{20, 01, 31};
    Time t1{25, 01, 23};
    CHECK(is_valid(t0));
    CHECK_FALSE(is_valid(t1));
}

TEST_CASE("to_string")
{
    Time t0{20, 01, 31};
    CHECK(to_string(t0, true) =="20:01:31");
    CHECK(to_string(t0, false) == "08:01:31 pm");
}

TEST_CASE("increment")
{
    Time t0{23, 59, 59};
    t0++;
    CHECK(t0.hh == 0);
    t0--;
    CHECK(t0.hh == 23);
}

TEST_CASE("Addition and subtraction")
{
    Time t0{12,06,59};
    Time t1{13,54,02};
    Time t2{t0};
    Time t3{};

    t0 = t0 + t1;
    t2 = t2 + 86401;
    t1 = 58 + t1;
    Time t4{2,1,1};

    CHECK((t0==t4));
    t4={12,7,0};
    CHECK((t2==t4));
     t4={13,55,0};
     CHECK((t1 ==t4));

    t2 = 86400 - t2;
    t1 = t1 - 1;
    t0 = t1-t3;

    t4={11,53,0};
    CHECK((t2==t4));
     t4={13,54,59};
     CHECK((t1 ==t4));
      t4={2,1,1};
      CHECK((t0 ==t4));

    t0 + 10;
     t4={0,0,0};
    CHECK((t0==t4));
}


TEST_CASE("Logic")
{
    Time t0{};
    Time t1{t0+10};
    Time t2{t0-2};
    Time t3{23, 59, 58};

    REQUIRE((t0<t1));
    CHECK((t0<t2));

    CHECK((t2>t1));

    REQUIRE_FALSE((t3 == t1));
    CHECK((t3 == t2));

    CHECK((t0 != t3));

    CHECK((t0<= t2));
    CHECK((t2 <= t3));

    CHECK_FALSE((t0 >= t2));
    CHECK_FALSE((t2 >= t3));

}

TEST_CASE( "Test operator <<" ) {
  Time t{18, 20, 10};
  REQUIRE( (std::cout << t << "\n").good() == true );
}


TEST_CASE( "Test operator >>" ) {
  Time t1{23,59,59};
  Time t2{};
  istringstream iss{"23:59:59"};
  iss>>t2;
  REQUIRE((t1==t2));
  REQUIRE((std::cin >> t1).good() == true );
}
