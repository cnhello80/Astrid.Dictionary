#include "stdafx.h"
#include "YoudaoHelper.h"
#include <boost\network\protocol\http\client.hpp>


YoudaoHelper::YoudaoHelper(string key, string keyfrom)
{
	this->key = key;
	this->keyfrom = keyfrom;
	this->hasKey = true;
}
YoudaoHelper::YoudaoHelper()
{
}

YoudaoHelper::~YoudaoHelper()
{
}

namespace http = boost::network::http;

string YoudaoHelper::GetResponseXml(string requestStr) {
	http::client client;

	string keyfrom = hasKey ? this->keyfrom : DEFAULT_KEYFROM;
	string key = hasKey ? this->key : DEFAULT_KEY;

	http::client::request request("http://fanyi.youdao.com/openapi.do?keyfrom=" + keyfrom + "&key=" + key + "&type=data&doctype=xml&version=1.1&q=" + requestStr);
	http::client::response response = client.get(request);
	string s = static_cast<std::string>(body(response));
	return s;
}
