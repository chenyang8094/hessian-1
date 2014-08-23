/*
 * client_impl.cpp
 *
 *  Created on: 21.08.2014
 *      Author: mike_gresens
 */

#include "client_impl.hpp"
#include "test2_service_impl.hpp"
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPResponse.h>
#include <boost/make_shared.hpp>

namespace caucho {

client_impl::client_impl(const session& session)
:
	client_base(),
	boost::enable_shared_from_this<client_impl>(),
	_session(session),
	_cookies(),
	_mutex()
{
}

test2_service
client_impl::get_test2_service()
{
	return boost::make_shared<test2_service_impl>(shared_from_this());
}

hessian::content_t
client_impl::call(const std::string& path, const hessian::string_t& method, const hessian::list_t& arguments)
{
	boost::unique_lock<boost::mutex> lock(_mutex);
	send_request(path, method, arguments);
	return receive_response();
}

void
client_impl::send_request(const std::string& path, const hessian::string_t& method, const hessian::list_t& arguments)
{
	net::NameValueCollection cookies;
	for (cookies::const_iterator cookie = _cookies.begin(); cookie != _cookies.end(); ++cookie)
		cookies.add(cookie->first, cookie->second);

	net::HTTPRequest request(net::HTTPRequest::HTTP_POST, path, net::HTTPMessage::HTTP_1_1);
	request.setChunkedTransferEncoding(true);
	request.setCookies(cookies);

	std::ostream& request_stream = _session->sendRequest(request);
	hessian::generator generate(request_stream);
	generate(method, arguments);
}

hessian::content_t
client_impl::receive_response()
{
	net::HTTPResponse response;
	std::istream& response_stream = _session->receiveResponse(response);
	if (response.getStatus() != net::HTTPResponse::HTTP_OK)
		throw std::runtime_error(response.getReason());

	std::vector<net::HTTPCookie> cookies;
	response.getCookies(cookies);
	for (std::vector<net::HTTPCookie>::const_iterator cookie = cookies.begin(); cookie != cookies.end(); ++cookie)
		_cookies[cookie->getName()] = cookie->getValue();

	hessian::parser parse(response_stream);
	return parse();
}

client
make_http_client(const std::string& host, const boost::uint16_t port)
{
	const session session = boost::make_shared<net::HTTPClientSession>(host, port);
	return boost::make_shared<client_impl>(session);
}

client
make_https_client(const std::string& host, const boost::uint16_t port)
{
	const session session = boost::make_shared<net::HTTPSClientSession>(host, port);
	// TODO: SSL context
	return boost::make_shared<client_impl>(session);
}

}