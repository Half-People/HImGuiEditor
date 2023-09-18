#pragma once
#include <io.h>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <fstream>
#include <GLFW/glfw3.h>
#include <ctime>
#include <direct.h>
#include <filesystem>

static ImTextureID DefaultLogo;

static bool HHaveFile(std::string path)
{
	std::ifstream file(path);
	if (file.good())
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

static bool HCopyFile(std::string CopyTarget, std::string CopyToPath)
{
	std::ofstream CWFile(CopyToPath);
	if (CWFile.good())
	{
		CWFile << "";
		CWFile.close();
	}
	else
	{
		CWFile.close();
		return false;
	}

	std::ifstream RFile(CopyTarget);
	std::ofstream WFile(CopyToPath, std::ios::app);
	if (!(WFile.good() && RFile.good()))
	{
		WFile.close();
		RFile.close();
		return false;
	}

	std::string line;
	while (std::getline(RFile, line))
	{
		WFile << line;
	}

	RFile.close();
	WFile.close();
	return true;
}

static void getFileNames(std::string path, std::vector<std::string>& files)
{
	intptr_t hFile = 0;

	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

static void getFileNames(std::string path, std::vector<std::string>& files, std::vector<std::string>& filename, std::string& filter_)
{
	intptr_t hFile = 0;

	struct _finddata_t fileinfo;
	std::string p;

	if (filter_.empty())
	{
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						files.push_back(p.assign(path).append("\\").append(fileinfo.name));
						filename.push_back(fileinfo.name);
					}
				}
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					filename.push_back(fileinfo.name);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
	else
	{
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						files.push_back(p.assign(path).append("\\").append(fileinfo.name));
						filename.push_back(fileinfo.name);
					}
				}
				else
				{
					if (std::string(fileinfo.name).find(filter_) < 1000000000)
					{
						files.push_back(p.assign(path).append("\\").append(fileinfo.name));
						filename.push_back(fileinfo.name);
					}
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
}

static void getFolderNames(std::string path, std::vector<std::string>& files, std::vector<std::string>& filename)
{
	intptr_t hFile = 0;

	struct _finddata_t fileinfo;
	std::string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					filename.push_back(fileinfo.name);
				}
			}
			//else
			//{
			//	//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			//}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

std::vector<std::string> getListOfDrives() {
	std::vector<std::string> arrayOfDrives;
	char* szDrives = new char[MAX_PATH]();
	if (GetLogicalDriveStringsA(MAX_PATH, szDrives));
	for (int i = 0; i < 100; i += 4)
		if (szDrives[i] != (char)0)
			arrayOfDrives.push_back(std::string{ szDrives[i],szDrives[i + 1] });
	delete[] szDrives;
	return arrayOfDrives;
}

#define GLuintToImTextureID (void*)(intptr_t)
static bool HLoadImage(const char* filename, ImTextureID& out_texture)
{
	int image_width = 0;
	int image_height = 0;

	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F); // Same

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	out_texture = (void*)(intptr_t)image_texture;

	return true;
}

static bool HLoadImage1(const char* filename, ImVec2& ImageSize, std::vector<unsigned char>& ImageData)
{
	int image_width = 0;
	int image_height = 0;
	int image_channels = 0;

	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, &image_channels, 4);
	if (image_data == NULL)
		return false;
	ImageData.clear();
	ImageData.resize((image_width * image_height) * image_channels);
	memcpy(ImageData.data(), image_data, ImageData.size());

	ImageSize.x = image_width;
	ImageSize.y = image_height;

	//stbi_image_free(image_data);
	return true;
}

static bool HLoadImage2(const unsigned char* imageData, ImVec2 ImageSize, GLuint& ImageBuffer)
{
	int image_width = ImageSize.x;
	int image_height = ImageSize.y;

	if (imageData == NULL)
		return false;

	glGenTextures(1, &ImageBuffer);
	glBindTexture(GL_TEXTURE_2D, ImageBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F); // Same

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	//stbi_image_free(imageData);

	return true;
}

static std::string GetTime()
{
	time_t now = time(0);
	char SaveTimeData[150];
	ctime_s(SaveTimeData, 150, &now);
	return SaveTimeData;
}

//#include <Windows.h>
//void SaveToClipboard(char* str)
//{
//	if (OpenClipboard(NULL))
//	{
//		HGLOBAL clipbuffer;
//		char* buffer;
//		EmptyClipboard();
//		clipbuffer = GlobalAlloc(GMEM_MOVEABLE, strlen(str) + 1);
//		buffer = (char*)GlobalLock(clipbuffer);
//		strcpy(buffer, (LPCSTR)str);
//		GlobalUnlock(clipbuffer);
//		SetClipboardData(CF_TEXT, clipbuffer);
//		CloseClipboard();
//	}
//}

#define HCopyFolder(A,B) std::filesystem::copy(A, B,std::filesystem::copy_options::recursive)

#ifdef _WIN32
#include <Windows.h>
#else
#if __APPLE__
//const char* open_executable = "open";
#else
//const char* open_executable = "xdg-open";
#endif
#endif

void OsOpenInShell(const char* path)
{
#ifdef _WIN32
	// Note: executable path must use backslashes!
	::ShellExecuteA(NULL, "open", path, NULL, NULL, 10);
#else
#if __APPLE__
	const char* open_executable = "open";
#else
	const char* open_executable = "xdg-open";
#endif
	char command[256];
	snprintf(command, 256, "%s \"%s\"", open_executable, path);
	system(command);
#endif
}
