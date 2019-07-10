#include "GameLog.h"
#include <fstream>
#include <iostream>

#pragma warning (disable:4996)

//send log to output
#define OUTLOG(s)  \
{                   \
    std::ostringstream os;\
    os << s << endl;\
    OutputDebugStringA(os.str().c_str());   \
}

void printLog(const LPCSTR s, ...)
{
    char buff[1024];
    int length = strlen(s);

    va_list ap;
    va_start(ap, s);
    _vsnprintf(buff, sizeof(buff), s, ap); //sizeof(szBuff)
    va_end(ap);

    OUTLOG(buff);
}