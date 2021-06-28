#include "Common.h"
#include "String.h"
#include <filesystem>
#include <vector>


namespace fs = std::filesystem;

Strings GetFileListFromFolder(char const* folderPath)
{
	Strings fileList;
	for (const auto& entry : fs::recursive_directory_iterator(folderPath))
	{
		std::string const path = entry.path().string();

		if (path.find(".cpp") != std::string::npos)
			continue;

		fileList.push_back(new String(path.c_str(), path.length()));
	}

	return  fileList;
}


String* ReadFile(String const* fileName)
{
	std::string contents;
	std::FILE* fp = fopen(fileName->characters, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		contents.resize(std::ftell(fp));
		rewind(fp);
		fread(&contents[0], 1, contents.size(), fp);
		fclose(fp);
	}

	return new String(contents.c_str(), contents.length());
}

inline void WriteFile(FILE* stream, String* string)
{
	fprintf(stream,"%s", string->characters);
}

inline void WriteFile(FILE* stream, u8 uInteger)
{
	fprintf(stream,"%u", uInteger);
}

inline void WriteFile(FILE* stream, u16 uInteger)
{
	fprintf(stream,"%u", uInteger);
}

inline void WriteFile(FILE* stream, u32 uInteger)
{
	fprintf(stream,"%u", uInteger);
}

inline void WriteFile(FILE* stream, u64 uInteger)
{
	fprintf(stream,"%llu", uInteger);
}

inline void WriteFile(FILE* stream, f32 floatValue)
{
	fprintf(stream,"%f", floatValue);
}

inline void WriteFile(FILE* stream, f64 floatValue)
{
	fprintf(stream,"%lf", floatValue);
}

inline void WriteFile(FILE* stream, i8 integer)
{
	fprintf(stream,"%i", integer);
}

inline void WriteFile(FILE* stream, i16 integer)
{
	fprintf(stream,"%i", integer);
}

inline void WriteFile(FILE* stream, i32 integer)
{
	fprintf(stream,"%i", integer);
}

inline void WriteFile(FILE* stream, i64 integer)
{
	fprintf(stream,"%lld", integer);
}