//
//  Utils.cpp
//  XcodeProject
//
//  Created by taojiang on 13-12-23.
//  Copyright (c) 2013年 taojiang. All rights reserved.
//

#include "Utils.h"

//从输入编码转换到办理出编码
CodeConvert::CodeConvert(const char* fromeCode,const char* toCode)
{
    cd = iconv_open(toCode,fromeCode);
}

int CodeConvert::convert(char *inbuf,int inlen,char *outbuf,int outlen) {
    char **pin = &inbuf;
    char **pout = &outbuf;
    memset(outbuf,0,outlen);
    return iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen);
}

CodeConvert::~CodeConvert(void)
{
    if(cd > 0)
    {
        iconv_close(cd);
    }
}
