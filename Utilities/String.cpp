#include "stdafx.h"
#include "String.h"

void String::SplitString(vector<string>& result, string origin, const string& tok)
{
	//string 하나를 token을 받아서 token을 기준으로 string을 나눈다.
}

void String::SplitString(vector<wstring>& result, wstring origin, const wstring& tok)
{
}

bool String::StartsWith(const string& str, const string& comp)
{
	return false;
}

bool String::StartsWith(const wstring& str, const wstring& comp)
{
	return false;
}

bool String::Contain(const string& str, const string& comp)
{
	return false;
}

bool String::Contain(const wstring& str, const wstring& comp)
{
	return false;
}

void String::Replace(string str, const string& comp, const string& rep)
{
}

void String::Replace(wstring str, const wstring& comp, const wstring& rep)
{
}

string String::ToString(const Vector2& vec2)
{
	return string();
}

wstring String::ToWString(const string& value)
{
	return wstring();
}

string String::ToString(const wstring& value)
{
	return string();
}
