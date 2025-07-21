#include "Pch.h"
#include "Utils.h"

//#include <libloaderapi.h>
//#include <shlwapi.lib>
//#include <Shlwapi.h>

namespace Hi_Engine::Utils
{
	std::string GetWorkingDirectory()
	{
		std::filesystem::path exePath = std::filesystem::current_path();
		return exePath.string();
	}

	std::vector<std::string> GetFilesWithExtension(std::string_view path, std::string_view extension)
	{
		std::vector<std::string> files;

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_regular_file() && entry.path().extension() == extension)
			{
				files.push_back(entry.path().string());
			}
		}

		return files;
	}

	/*std::string GetExecutableDirectory()
	{
		wchar_t wpath[MAX_PATH];
		GetModuleFileNameW(nullptr, wpath, MAX_PATH);
		std::filesystem::path exePath(wpath);
		exePath.remove_filename();
		return exePath.string();
	}*/

	std::wstring ConvertToWideString(const std::string& string)
	{
		std::wstring wString{ string.begin(), string.end() };
		return wString;
	}

	std::string ToLowerCase(std::string text)
	{
		for (auto t : text)
			t = std::tolower(t);

		return text;
	}
}