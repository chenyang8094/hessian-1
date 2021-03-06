/*
 * test_object.cpp
 *
 *  Created on: 09.08.2014
 *      Author: mike_gresens
 */

#include "hessian_test_pch.hpp"
#include "value_helper.hpp"
#include "../fixture/fixture_object.hpp"

namespace hessian {
namespace value_test {

typedef mpl::remove<all_types, object_t>::type other_types;

BOOST_FIXTURE_TEST_SUITE(test_value_object, fixture::fixture_object)

TEST_EQUAL_SAME_TYPE(object_0, object_1);
TEST_EQUAL_OTHER_TYPES(object_t, other_types);
TEST_LESS_SAME_TYPE(object_0, object_1);
TEST_LESS_OTHER_TYPES(object_t, other_types);
TEST_HASH(object_0, object_1);
TEST_OUTPUT(object_1, L"object(string('_value') = int(0))");

BOOST_AUTO_TEST_SUITE_END()

}
}
