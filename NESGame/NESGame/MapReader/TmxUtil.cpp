//-----------------------------------------------------------------------------
// TmxUtil.cpp
//
// Copyright (c) 2010-2014, Tamir Atias
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <algorithm>

#ifdef USE_MINIZ
#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"
#else
#include "zlib.h"
#endif

#include <stdio.h>

#include "TmxUtil.h"
#include "base64.h"
#include <functional>
#include <cctype>
#include <locale>


namespace Tmx {

	// trim from start (in place)
	static inline void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	// trim from end (in place)
	static inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	// trim from start (copying)
	static inline std::string ltrim_copy(std::string s) {
		ltrim(s);
		return s;
	}

	// trim from end (copying)
	static inline std::string rtrim_copy(std::string s) {
		rtrim(s);
		return s;
	}

	// trim from both ends (copying)
	static inline std::string trim_copy(std::string s) {
		trim(s);
		return s;
	}

    std::string &Util::Trim(std::string &str)
    {
		trim(str);
		return str;
    }

    std::string Util::DecodeBase64(const std::string &str) 
    {
        return base64_decode(str);
    }

    char *Util::DecompressGZIP(const char *data, int dataSize, int expectedSize) 
    {
        int bufferSize = expectedSize;
        int ret;
        z_stream strm;
        char *out = (char*)malloc(bufferSize);

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.next_in = (Bytef*)data;
        strm.avail_in = dataSize;
        strm.next_out = (Bytef*)out;
        strm.avail_out = bufferSize;

        ret = inflateInit2(&strm, 15 + 32);

        if (ret != Z_OK) 
        {
            free(out);
            return NULL;
        }

        do 
        {
            ret = inflate(&strm, Z_SYNC_FLUSH);

            switch (ret) 
            {
                case Z_NEED_DICT:
                case Z_STREAM_ERROR:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&strm);
                    free(out);
                    return NULL;
            }

            if (ret != Z_STREAM_END) 
            {
                out = (char *) realloc(out, bufferSize * 2);

                if (!out) 
                {
                    inflateEnd(&strm);
                    free(out);
                    return NULL;
                }

                strm.next_out = (Bytef *)(out + bufferSize);
                strm.avail_out = bufferSize;
                bufferSize *= 2;
            }
        }
        while (ret != Z_STREAM_END);

        if (strm.avail_in != 0) 
        {
            free(out);
            return NULL;
        }

        inflateEnd(&strm);

        return 0;
    }
}
