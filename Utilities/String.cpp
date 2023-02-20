#include "stdafx.h"
#include "String.h"

void String::SplitString(vector<string>& result, string origin, const string& tok)
{
	result.clear();
	//�ڸ� ��ġ
	int cutAt = 0;
	//npos = no position ��ã�� ��� npos�� ���´�.
	while ((cutAt = (int)origin.find_first_of(tok) != origin.npos))
	{
		if (cutAt > 0)
			result.push_back(origin.substr(0, cutAt));

		origin = origin.substr((size_t)cutAt + 1);
	}
	//�ڿ� ���� ���� �����ִٸ�, �ٽ� �ѹ� �ڸ���.
	if (origin.length() > 0)
		result.push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>& result, wstring origin, const wstring& tok)
{
	result.clear();
	//�ڸ� ��ġ
	int cutAt = 0;
	//npos = no position ��ã�� ��� npos�� ���´�.
	while ((cutAt = (int)origin.find_first_of(tok) != origin.npos))
	{
		if (cutAt > 0)
			result.push_back(origin.substr(0, cutAt));

		origin = origin.substr((size_t)cutAt + 1);
	}
	//�ڿ� ���� ���� �����ִٸ�, �ٽ� �ѹ� �ڸ���.
	if (origin.length() > 0)
		result.push_back(origin.substr(0, cutAt));
}
//��
bool String::StartsWith(const string& str, const string& comp)
{
	//comp�� string�� �޴´�.
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
//����
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
//��ü Ư�� ���ڿ��� comp str���� ã�� rep�� ��ü�Ѵ�.
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
//vector2�� ���ڿ��� �ٲٴ� �Լ�.
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
	//disable�� ���� �޽����� ����.
#pragma warning(disable : 4244)
	//���� �ڵ� C 4244 �߻�����
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
	//default�� �⺻������ �ٲ۴�.
#pragma warning(default : 4244)
}
