#include "Common.h"

void WriteDataToBinaryFile()
{
    FILE* stream;

    fopen_s(&stream, "fprintf_s.out", "w");

    ASSERT(stream);

    fprintf_s(stream, "%s%c", s, c);
    fprintf_s(stream, "%d\n", i);
    fprintf_s(stream, "%f\n", fp);

    fclose(stream);
}