#include "stdafx.h"
#include "Path.h"

bool Path::ExistFile(const string& path)
{
	return ExistFile(String::ToWString(path));
}

bool Path::ExistFile(const wstring& path)
{
	//file의 유무를 알아볼 때
	//file의 속성을 알아볼 때 활용한다.
	DWORD fileValue = GetFileAttributes(path.c_str());
	//unsigned이기 때문에 -1이 들어오면 최댓값이 나온다.(오버플로)
	return fileValue < 0xFFFFFFFF;
}

bool Path::ExistDirectory(const string& path)
{
	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(const wstring& path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && (attribute & FILE_ATTRIBUTE_DIRECTORY));

	return temp == TRUE;
}

string Path::Combine(const string& path1, const string& path2)
{
	return path1 + path2;
}

wstring Path::Combine(const wstring& path1, const wstring& path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string>& paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring>& paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(const string& path)
{
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(const wstring& path)
{
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(const string& path)
{
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(const wstring& path)
{
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

string Path::GetFileName(const string& path)
{
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(const wstring& path)
{
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

string Path::GetFileNameWithoutExtension(const string& path)
{
	string fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(const wstring& path)
{
	wstring fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0, index);
}

const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg;";
const WCHAR* Path::ShaderFilter = L"HLSL File\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text File\0*.txt";

void Path::OpenFileDialog(const wstring& file, const WCHAR* filter, const wstring& folder, function<void(wstring)>& func, const HWND& hwnd)
{
	//다음 수업 시작
}

void Path::SaveFileDialog(const wstring& file, const WCHAR* filter, const wstring& folder, function<void(wstring)>& func, const HWND& hwnd)
{
}

void Path::GetFiles(vector<string> files, const string& path, const string& filter, const bool& bFindSubFolder)
{
}

void Path::GetFiles(vector<wstring> files, const wstring& path, const wstring& filter, const bool& bFindSubFolder)
{
}

void Path::CreateFolder(const string& path)
{
}

void Path::CreateFolder(const wstring& path)
{
}

void Path::CreateFolders(const string& path)
{
}

void Path::CreateFolders(const wstring& path)
{
}
