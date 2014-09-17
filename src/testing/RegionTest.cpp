/******************************************************************************************************
 * TileMapEditor
 * Copyright (C) 2014 Brandon Whitehead (tricksterguy87[AT]gmail[DOT]com)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * excluding commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    An acknowledgement in your documentation and link to the original version is required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 ******************************************************************************************************/

#define BOOST_TEST_DYN_LINK
#include <boost/test/auto_unit_test.hpp>
#include <sstream>
#include "Logger.hpp"
#include "Region.hpp"


BOOST_AUTO_TEST_CASE(RegionSubtract0Formed)
{
    // DDD
    // D1D
    // DDD
    Region r1({Rectangle(5, 5, 5, 5)});
    r1.Subtract(Rectangle(0, 0, 15, 15));

    BOOST_REQUIRE(!r1.Contains(Rectangle(5, 5, 5, 5)));
    BOOST_REQUIRE(!r1.Intersects(Rectangle(0, 0, 15, 15)));
    BOOST_REQUIRE_EQUAL(r1.Size(), 0);
}

BOOST_AUTO_TEST_CASE(RegionSubtract1Formed)
{
    // DDD
    // 1
    // 1
    Region r1({Rectangle(0, 0, 10, 30)});
    r1.Subtract(Rectangle(0, 0, 30, 10));

    BOOST_REQUIRE(!r1.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(!r1.Intersects(Rectangle(0, 0, 30, 10)));
    BOOST_REQUIRE(r1.Contains(Rectangle(0, 10, 10, 20)));
    BOOST_REQUIRE_EQUAL(r1.Size(), 1);

    // DDD
    //   1
    //   1
    Region r2({Rectangle(0, 0, 10, 30)});
    r2.Subtract(Rectangle(-20, 0, 30, 10));

    BOOST_REQUIRE(!r2.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(!r2.Intersects(Rectangle(-20, 0, 30, 10)));
    BOOST_REQUIRE(r2.Contains(Rectangle(0, 10, 10, 20)));
    BOOST_REQUIRE_EQUAL(r2.Size(), 1);

    //   1
    //   1
    // DDD
    Region r3({Rectangle(0, 0, 10, 30)});
    r3.Subtract(Rectangle(-20, 20, 30, 10));

    BOOST_REQUIRE(!r3.Contains(Rectangle(0, 20, 10, 10)));
    BOOST_REQUIRE(!r3.Intersects(Rectangle(-20, 20, 30, 10)));
    BOOST_REQUIRE(r3.Contains(Rectangle(0, 0, 10, 20)));
    BOOST_REQUIRE_EQUAL(r3.Size(), 1);

    // 1
    // 1
    // DDD
    Region r4({Rectangle(0, 0, 10, 30)});
    r4.Subtract(Rectangle(0, 20, 30, 10));

    BOOST_REQUIRE(!r4.Contains(Rectangle(0, 20, 10, 10)));
    BOOST_REQUIRE(!r4.Intersects(Rectangle(0, 20, 30, 10)));
    BOOST_REQUIRE(r4.Contains(Rectangle(0, 0, 10, 20)));
    BOOST_REQUIRE_EQUAL(r4.Size(), 1);


    // DDDD
    //  11
    //
    Region r1({Rectangle(0, 0, 10, 30)});
    r1.Subtract(Rectangle(0, 0, 30, 10));

    BOOST_REQUIRE(!r1.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(!r1.Intersects(Rectangle(0, 0, 30, 10)));
    BOOST_REQUIRE(r1.Contains(Rectangle(0, 10, 10, 20)));
    BOOST_REQUIRE_EQUAL(r1.Size(), 1);

    // DDD
    //   1
    //   1
    Region r2({Rectangle(0, 0, 10, 30)});
    r2.Subtract(Rectangle(-20, 0, 30, 10));

    BOOST_REQUIRE(!r2.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(!r2.Intersects(Rectangle(-20, 0, 30, 10)));
    BOOST_REQUIRE(r2.Contains(Rectangle(0, 10, 10, 20)));
    BOOST_REQUIRE_EQUAL(r2.Size(), 1);

    //   1
    //   1
    // DDD
    Region r3({Rectangle(0, 0, 10, 30)});
    r3.Subtract(Rectangle(-20, 20, 30, 10));

    BOOST_REQUIRE(!r3.Contains(Rectangle(0, 20, 10, 10)));
    BOOST_REQUIRE(!r3.Intersects(Rectangle(-20, 20, 30, 10)));
    BOOST_REQUIRE(r3.Contains(Rectangle(0, 0, 10, 20)));
    BOOST_REQUIRE_EQUAL(r3.Size(), 1);

    // 1
    // 1
    // DDD
    Region r4({Rectangle(0, 0, 10, 30)});
    r4.Subtract(Rectangle(0, 20, 30, 10));

    BOOST_REQUIRE(!r4.Contains(Rectangle(0, 20, 10, 10)));
    BOOST_REQUIRE(!r4.Intersects(Rectangle(0, 20, 30, 10)));
    BOOST_REQUIRE(r4.Contains(Rectangle(0, 0, 10, 20)));
    BOOST_REQUIRE_EQUAL(r4.Size(), 1);
}


BOOST_AUTO_TEST_CASE(RegionSubtract3Formed)
{
    // 11
    // 2DD
    // 33
    Region r1({Rectangle(0, 0, 10, 30)});
    r1.Subtract(Rectangle(5, 10, 30, 10));

    BOOST_REQUIRE(!r1.Contains(Rectangle(5, 10, 5, 10)));
    BOOST_REQUIRE(!r1.Intersects(Rectangle(5, 10, 30, 10)));
    BOOST_REQUIRE(r1.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(r1.Contains(Rectangle(0, 10, 5, 10)));
    BOOST_REQUIRE(r1.Contains(Rectangle(0, 20, 10, 10)));
    BOOST_REQUIRE_EQUAL(r1.Size(), 3);

    //  11
    // DD2
    //  33
    Region r2({Rectangle(0, 0, 10, 30)});
    r2.Subtract(Rectangle(-25, 10, 30, 10));
    BOOST_REQUIRE(!r2.Contains(Rectangle(0, 10, 5, 10)));
    BOOST_REQUIRE(!r2.Intersects(Rectangle(-25, 10, 30, 10)));
    BOOST_REQUIRE(r2.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(r2.Contains(Rectangle(5, 10, 5, 10)));
    BOOST_REQUIRE(r2.Contains(Rectangle(0, 20, 10, 10)));
    BOOST_REQUIRE_EQUAL(r2.Size(), 3);

    // 123
    // 1D3
    //  D
    Region r3({Rectangle(0, 0, 30, 10)});
    r3.Subtract(Rectangle(10, 5, 10, 30));
    BOOST_REQUIRE(!r3.Contains(Rectangle(10, 5, 10, 5)));
    BOOST_REQUIRE(!r3.Intersects(Rectangle(10, 5, 10, 30)));
    BOOST_REQUIRE(r3.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(r3.Contains(Rectangle(10, 0, 10, 5)));
    BOOST_REQUIRE(r3.Contains(Rectangle(20, 0, 10, 10)));
    BOOST_REQUIRE_EQUAL(r3.Size(), 3);

    //  D
    // 1D3
    // 123
    Region r4({Rectangle(0, 0, 30, 10)});
    r4.Subtract(Rectangle(10, -25, 10, 30));
    BOOST_REQUIRE(!r4.Contains(Rectangle(10, 0, 10, 5)));
    BOOST_REQUIRE(!r4.Intersects(Rectangle(10, -25, 10, 30)));
    BOOST_REQUIRE(r4.Contains(Rectangle(0, 0, 10, 10)));
    BOOST_REQUIRE(r4.Contains(Rectangle(10, 5, 10, 5)));
    BOOST_REQUIRE(r4.Contains(Rectangle(20, 0, 10, 10)));
    BOOST_REQUIRE_EQUAL(r4.Size(), 3);
}