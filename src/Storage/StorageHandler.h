#include "Common/Common.h"
#include "Common/String.cpp"
#include <filesystem>
#include <vector>


namespace fs = std::filesystem;

Strings GetFileListFromFolder(char const* folderPath)
{
    Strings fileList;
    for (const auto &entry : fs::recursive_directory_iterator(folderPath))
    {
        std::string const path = entry.path().string();

		if (path.find(".cpp") != std::string::npos)
			continue;

        fileList.push_back(ConvertToString(path.c_str(), path.length()));
    }
    
    return  fileList;
}


StringConst ReadFile(char const* fileName)
{
	std::string contents;
	std::FILE* fp = std::fopen(fileName, "rb");
	if (fp)
	{
		std::fseek(fp, 0, SEEK_END);
		contents.resize(std::ftell(fp));
		std::rewind(fp);
		std::fread(&contents[0], 1, contents.size(), fp);
		std::fclose(fp);
	}

	String fileContent = ConvertToString(contents.c_str(), contents.length());
	return ToConst(fileContent);
}
