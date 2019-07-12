//
// Created by lucoder on 2019/4/17.
//
#include "../../mxlib/core/jiaotu.h"
using namespace mxlib;

Jiaotu::~Jiaotu()
{
    Configuration(false, false, ".", 1000);
}
Jiaotu::Jiaotu(bool release, bool isLog, string logfolder, int cache)
{
    Configuration(release, isLog, logFolder, cache);
}

void Jiaotu::Configuration(bool release, bool isLog, string logfolder, int cache)
{
    this->isRelease = release;
    this->isLog = isLog;
    this->logFolder = logfolder;
    this->cache = cache;
}

void Jiaotu::WriteLine(const char *info, ...)
{
    va_list v;
    char logbuf[1000];
    va_start(v, info);
    vsprintf(logbuf, info, v);
    va_end(v);
    WriteLine(1, logbuf);
}
void Jiaotu::WriteLine(int level, const char *info, ...)
{
    if (!this->isRelease || this->isLog)
    {
        va_list v;
        char logbuf[1000];
        va_start(v, info);
        vsprintf(logbuf, info, v);
        va_end(v);
        char tbuf[1024];

        switch (level)
        {
            case 1:
                sprintf(tbuf, " %s [INFO] : %s \n", this->current.getTimeString().c_str(), logbuf);
                break;
            case 2:
                sprintf(tbuf, " %s [WARN] : %s \n", this->current.getTimeString().c_str(), logbuf);
                break;
            case 3:
                sprintf(tbuf, " %s [ERR] : %s \n", this->current.getTimeString().c_str(), logbuf);
                break;
            case 4:
                sprintf(tbuf, " %s [SYSTEM] : %s \n", this->current.getTimeString().c_str(), logbuf);
                break;
            default:
                sprintf(tbuf, " %s [INFO] : %s \n", this->current.getTimeString().c_str(), logbuf);
                break;
        }

        if (level == 4)
        {
            cout << tbuf;
            if (this->isLog)
            {
                this->logFactory.push_back(tbuf);
                if (this->logFactory.size() >= this->cache)
                    Save();
            }
        }
        else
        {
            if (!this->isRelease)
                cout << tbuf;

            if (this->isLog)
            {
                this->logFactory.push_back(tbuf);
                if (this->logFactory.size() >= this->cache)
                    Save();
            }
        }
    }
}

void Jiaotu::Save()
{
    if (this->isLog)
    {
        char logFile[1000];
        sprintf(logFile, "%s/%s.log", this->logFolder.c_str(), this->current.getDateString('#').c_str());
        ofstream writer(logFile, std::ios::app);
        for (vector<string>::iterator iter = this->logFactory.begin(); iter != this->logFactory.end(); iter++)
        {
            writer.write(iter->c_str(), 100);
        }
        writer.close();
        this->logFactory.clear();
    }
}