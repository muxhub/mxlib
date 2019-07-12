//
// Created by lucoder on 2019/4/17.
//
#include <iostream>
#include <time.h>
#include <sys/time.h>
using namespace std;
#ifndef MXLIB_DATETIME_H
#define MXLIB_DATETIME_H
namespace mxlib{
    //Datetime
    class DateTime
    {
    public:
        DateTime();
        string getDateString(char splitor = '/');
        string getTimeString(char splitor = ':');
        string getMicroTimeString();
        string getMiliTimeString();
        string toString();
    };
}
#endif //MXLIB_DATETIME_H
