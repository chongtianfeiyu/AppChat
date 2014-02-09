//
//  Utils.h
//  XcodeProject
//
//  Created by taojiang on 13-12-23.
//  Copyright (c) 2013年 taojiang. All rights reserved.
//

#ifndef __XcodeProject__Utils__
#define __XcodeProject__Utils__

#include <iostream>
#include <iconv.h>

using namespace std;

class CodeConvert
{
private:
    iconv_t cd;
public:
    CodeConvert(const char* fromeCode,const char* toCode);
    virtual ~CodeConvert(void);
    
    int convert(char* inbuf,int inlen,char* outbuf,int outlen);
};


#endif /* defined(__XcodeProject__Utils__) */
