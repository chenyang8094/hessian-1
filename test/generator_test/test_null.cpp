/*
 * test_null.cpp
 *
 *  Created on: 18.11.2013
 *      Author: mgresens
 */

#include "generator_helper.hpp"

namespace hessian {
namespace generator_test {

BOOST_AUTO_TEST_SUITE(test_null)

TEST_CALL
(
	test_null,
	null_t(),
	string_t("N", 1)
)

BOOST_AUTO_TEST_SUITE_END()

}
}
