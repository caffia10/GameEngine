#include "Common/Common.h"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

CharsConst GetFileListFromFolder(char const* folderPath)
{
    CharsConst fileList;
    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        char const* path = entry.path().string().c_str();
        fileList.push_back(path);
    }
    
    return  fileList;
}


std::string ReadFile(char const* fileName)
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

	return(contents);
}
