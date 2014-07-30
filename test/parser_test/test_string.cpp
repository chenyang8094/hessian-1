/*
 * test_string.cpp
 *
 *  Created on: 18.11.2013
 *      Author: mgresens
 */

#include "parser_helper.hpp"
#include <boost/algorithm/string/erase.hpp>
#include <boost/format.hpp>

using boost::algorithm::erase_tail_copy;

namespace hessian {
namespace parser_test {

BOOST_AUTO_TEST_SUITE(test_string)

static string_t
make_string_1024()
{
	string_t value;
	boost::format f("%02d 456789012345678901234567890123456789012345678901234567890123\n");
	for (std::size_t i = 0; i < 16; i++)
	{
		f % i;
		value += f.str();
	}
	return value;
}

static string_t
make_string_1023()
{
	return erase_tail_copy(make_string_1024(), 1);
}

static string_t
make_string_65536()
{
	string_t value;
	boost::format f("%03d 56789012345678901234567890123456789012345678901234567890123\n");
	for (std::size_t j = 0; j < 2; j++)
		for (std::size_t i = 0; i < 32 * 16; i++)
		{
			f % i;
			value += f.str();
		}
	return erase_tail_copy(value, 1);
}

static const string_t string_0 = string_t();
static const string_t string_1 = string_t("0");
static const string_t string_31 = string_t("0123456789012345678901234567890");
static const string_t string_32 = string_t("01234567890123456789012345678901");
static const string_t string_1023 = make_string_1023();
static const string_t string_1024 = make_string_1024();
static const string_t string_65536 = make_string_65536();

TEST_REPLY
(
	test_string_0,
	string_t("\x00", 1) + string_0,
	string_0
)

TEST_REPLY
(
	test_string_1,
	string_t("\x01", 1) + string_1,
	string_1
)

TEST_REPLY
(
	test_string_31,
	string_t("\x1f", 1) + string_31,
	string_31
)

TEST_REPLY
(
	test_string_32,
	string_t("\x30\x20", 2) + string_32,
	string_32
)

TEST_REPLY
(
	test_string_1023,
	string_t("\x33\xff", 2) + string_1023,
	string_1023
)

TEST_REPLY
(
	test_string_1024,
	string_t("S\x04\x00", 3) + string_1024,
	string_1024
)

TEST_REPLY
(
	test_string_65536,
	string_t("\x52\x80\x00", 3) + make_string_65536().insert(32768, string_t("S\x7f\xff", 3)),
	string_65536
)

BOOST_AUTO_TEST_SUITE_END()

}
}
