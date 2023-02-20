#include "stdafx.h"
#include "String.h"

void String::SplitString(vector<string>& result, string origin, const string& tok)
{
	result.clear();
	//자를 위치
	int cutAt = 0;
	//npos = no position 못찾을 경우 npos가 나온다.
	while ((cutAt = (int)origin.find_first_of(tok) != origin.npos))
	{
		if (cutAt > 0)
			result.push_back(origin.substr(0, cutAt));

		origin = origin.substr((size_t)cutAt + 1);
	}
	//뒤에 값이 아직 남아있다면, 다시 한번 자른다.
	if (origin.length() > 0)
		result.push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>& result, wstring origin, const wstring& tok)
{
	result.clear();
	//자를 위치
	int cutAt = 0;
	//npos = no position 못찾을 경우 npos가 나온다.
	while ((cutAt = (int)origin.find_first_of(tok) != origin.npos))
	{
		if (cutAt > 0)
			result.push_back(origin.substr(0, cutAt));

		origin = origin.substr((size_t)cutAt + 1);
	}
	//뒤에 값이 아직 나마있다면, 다시 한번 자른다.
	if (origin.length() > 0)
		result.push_back(origin.substr(0, cutAt));
}
//비교
bool String::StartsWith(const string& str, const string& comp)
{
	//comp할 string을 받는다.
	string::size_type index = str.find(comp);

	if (index != string::npos && (int)index == 0)
		return true;

	return false;
}

bool String::StartsWith(const wstring& str, const wstring& comp)
{
	wstring::size_type index = str.find(comp);

	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}
//포함
bool String::Contain(const string& str, const string& comp)
{
	size_t found = str.find(comp);

	return found != string::npos;
}

bool String::Contain(const wstring& str, const wstring& comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}
//대체 특정 문자열을 comp str에서 찾아 rep로 대체한다.
void String::Replace(string& str, const string& comp, const string& rep)
{
	size_t startPos = 0;
	while ((startPos = str.find(comp, startPos)) != string::npos)
	{
		str.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}
}

void String::Replace(wstring& str, const wstring& comp, const wstring& rep)
{
	size_t startPos = 0;
	while ((startPos = str.find(comp, startPos)) != wstring::npos)
	{
		str.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}
}
//vector2를 문자열로 바꾸는 함수.
string String::ToString(const Vector2& vec2)
{
	string temp;	
	temp = to_string(vec2.x) + to_string(vec2.y);

	return temp;
}

wstring String::ToWString(const string& value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

string String::ToString(const wstring& value)
{
	//disable은 오류 메시지를 끈다.
#pragma warning(disable : 4244)
	//오류 코드 C 4244 발생원인
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
	//default은 기본값으로 바꾼다.
#pragma warning(default : 4244)
}
