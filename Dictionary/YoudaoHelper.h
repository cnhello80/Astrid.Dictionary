#pragma once
#include <string>
using namespace std;
class YoudaoHelper
{
private:

	string keyfrom;
	string key;
	bool hasKey = false;
	const string DEFAULT_KEYFROM = "ipsolpu";
	const string DEFAULT_KEY = "2014689998";
public:
	YoudaoHelper(string key, string keyfrom);
	YoudaoHelper();
	~YoudaoHelper();

	string GetResponseXml(string requestStr);
};

