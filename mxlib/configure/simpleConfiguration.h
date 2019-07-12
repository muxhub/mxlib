//
// Created by lucoder on 2019/4/17.
//
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
using namespace std;
#ifndef MXLIB_SIMPLECONFIGURATION_H
#define MXLIB_SIMPLECONFIGURATION_H
namespace  mxlib{
    class SimpleConfiguration{
    private:
        string _file;
        map<string, string> factory;
        void setValue(string k,string v);
    public:
        SimpleConfiguration();
        bool load(string v);
        string get(string key);
        void set(string k,string v);
        bool hasKey(string key);
        string getAbsolute();
        void print();
    };
}
#endif //MXLIB_SIMPLECONFIGURATION_H
