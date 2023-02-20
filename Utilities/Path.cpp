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
//경로
string Path::GetDirectoryName(string path)
{
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}
//확장자
string Path::GetExtension(string path)
{
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}
//파일의 이름 = 확장자포함
string Path::GetFileName(string path)
{
	String::Replace(path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}
//확장자없는 파일의 이름
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
//필터의 설정
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg;";
const WCHAR* Path::ShaderFilter = L"HLSL File\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text File\0*.txt";
//대화 상자 열기.
void Path::OpenFileDialog(const wstring& file, const WCHAR* filter, const wstring& folder, function<void(wstring)>& func, const HWND& hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(tempFolder, L"/", L"\\");
	//파일에 대한 정보를 가지고 있는 구조체 OPENFILENAME
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	//Dialog창의 이름
	ofn.lpstrTitle = L"불러오기";
	//파일이름의 최대 길이
	ofn.nMaxFile = 255;
	//Dialog가 보여줄 폴더의 경로를 지정.
	ofn.lpstrInitialDir = tempFolder.c_str();
	//맨처음에 넣은 경로로 매번 열리게 해준다.
	//OFN_NOCHANGEDIR를 안넣을 경우 마지막 경로로 창이 열린다.
	ofn.Flags = OFN_NOCHANGEDIR;
	//실행이 잘되었다면 조건문에 들어갈 수 있다.
	//옛날에 만들어진 기능이라 예약어 true오류가 발생
	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != nullptr)
		{
#pragma warning(disable : 6054)
			wstring loadName = name;
			//경로를 원하는 형태로 바꿔 준다.
			String::Replace(loadName, L"\\", L"/");
			func(loadName);
#pragma warning(default : 6054)
		}
	}	

}

void Path::SaveFileDialog(const wstring& file, const WCHAR* filter, const wstring& folder, function<void(wstring)>& func, const HWND& hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(tempFolder, L"/", L"\\");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;
	//기본확장자, 파일명에 확장자가 없더라도 기본확장자가 알아서 들어간다.
	if (filter == TextFilter)
		ofn.lpstrDefExt = L".txt";
	else if (filter == ShaderFilter)
		ofn.lpstrDefExt = L".hlsl";

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != nullptr)
		{
#pragma warning(disable : 6054)
			wstring saveName = name;
			String::Replace(saveName, L"\\", L"/");
			func(saveName);
#pragma warning(default : 6054)
		}
	}
}

void Path::GetFiles(vector<string> files, const string& path, const string& filter, const bool& bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);

	GetFiles(wFiles, wPath, wFilter, bFindSubFolder);
	for (const auto& str : wFiles)
		files.push_back(String::ToString(str));
}

void Path::GetFiles(vector<wstring> files, const wstring& path, const wstring& filter, const bool& bFindSubFolder)
{
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);
	//파일을 찾기 위해 findeFirstFile을 통해서 handle에 값을 받아온다.
	//handle의 값이 있다면 조건문에 들어간다.
	if (handle != INVALID_HANDLE_VALUE)
	{
		do 
		{
			//찾는 data가 folder이면 실행
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				//bFindSubFolder가 true면 하위 폴더까지 들어간다.
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					//그러려면 경로를 수정해야한다.
					wstring folder = path + wstring(findData.cFileName) + L"/";
					//그곳에서 data를 찾는다.
					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			//찾는 data가 file이면 실행된다
			else
			{
				wstring fileName = path + wstring(findData.cFileName);
				files.push_back(fileName);
			}
		} while (FindNextFile(handle, &findData));
		//반복문을 나왔다면 값을 찾은 것이기 때문에 handle을 닫아준다.
		FindClose(handle);
	}
	
}

void Path::CreateFolder(const string& path)
{
	CreateFolder(String::ToWString(path));
}

void Path::CreateFolder(const wstring& path)
{
	//이미 존재하면 경로를 만들 필요가 없다.
	if (ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), nullptr);
}

void Path::CreateFolders(const string& path)
{
	CreateFolders(String::ToWString(path));
}
//경로 중에 하위폴더를 갖는 경우 폴더가 없는 곳은 생성한다.
void Path::CreateFolders(wstring path)
{
	String::Replace(path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(folders, path, L"/");

	wstring temp = L"";
	for (const auto& folder : folders)
	{
		temp += folder + L"/";
		CreateFolder(temp);
	}
}
