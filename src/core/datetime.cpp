//
// Created by lucoder on 2019/4/17.
//
#include "../../mxlib/core/datetime.h"
using namespace mxlib;

DateTime::DateTime()
{
}

string DateTime::getDateString(char splitor)
{
    time_t rawTime;
    struct tm *timeinfo;
    rawTime = time(&rawTime);
    timeinfo = localtime(&rawTime);

    char buf[12];
    sprintf(buf, "%04d%c%02d%c%02d", timeinfo->tm_year + 1900, splitor, timeinfo->tm_mon + 1, splitor, timeinfo->tm_mday);
    return buf;
}
string DateTime::getTimeString(char splitor)
{
    char buf[9];
    time_t rawTime;
    struct tm *timeinfo;
    rawTime = time(&rawTime);
    timeinfo = localtime(&rawTime);

    sprintf(buf, "%02d%c%02d%c%02d", timeinfo->tm_hour, splitor, timeinfo->tm_min, splitor, timeinfo->tm_sec);
    return buf;
}
string DateTime::getMicroTimeString()
{
    char buf[100];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sprintf(buf, "%ld", (tv.tv_sec * 1000000 + tv.tv_usec));
    return buf;
}
string DateTime::getMiliTimeString()
{
    char buf[100];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sprintf(buf, "%ld", (tv.tv_sec * 1000 + tv.tv_usec / 1000));
    return buf;
}
string DateTime::toString()
{
    char buf[50];
    sprintf(buf, "%s %s %s %s", getDateString().c_str(), getTimeString().c_str(), getMiliTimeString().c_str(), getMicroTimeString().c_str());
    return buf;
}