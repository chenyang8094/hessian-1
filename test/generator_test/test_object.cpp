/*
 * test_object.cpp
 *
 *  Created on: 18.11.2013
 *      Author: mgresens
 */

#include "hessian_test_pch.hpp"
#include "generator_helper.hpp"
#include "../fixture/fixture_object.hpp"

namespace hessian {
namespace generator_test {

#define TEST_OBJECT(CASE) TEST_CALL(test_generate_object_##CASE, object_##CASE, hessian_##CASE)

BOOST_FIXTURE_TEST_SUITE(test_generate_object, fixture::fixture_object)

TEST_OBJECT(0);
TEST_OBJECT(1);
TEST_OBJECT(2);
TEST_OBJECT(2a);

//Skip, because generator will always use ref if possible. So test fails always.
//TEST_OBJECT(2b);

// TODO: Skipping test_object_3 because of cycles.

//Skip, because for generator all 16 objects are instances of 1st class definition. So test fails always.
//TEST_OBJECT(16);

BOOST_AUTO_TEST_SUITE_END()

}
}
