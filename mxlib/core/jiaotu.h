//
// Created by lucoder on 2019/4/17.
//
#include <iostream>
#include <vector>
#include <stdarg.h>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;
#ifndef MXLIB_JIAOTU_H
#define MXLIB_JIAOTU_H

#include "datetime.h"
namespace mxlib{
    class Jiaotu
    {
    private:
        bool isRelease, isLog;
        vector<string> logFactory;
        int cache;
        string logFolder;
        DateTime current;
        void WriteLine(string v);

    public:
        ~Jiaotu();
        Jiaotu(bool release = false, bool isLog = false, string logfolder = ".", int cache = 1000);
        void Configuration(bool release = false, bool isLog = false, string logfolder = ".", int cache = 1000);
        void WriteLine(const char *info, ...);
        void WriteLine(int level, const char *info, ...);
        void Save();
    };
}
#endif //MXLIB_JIAOTU_H
