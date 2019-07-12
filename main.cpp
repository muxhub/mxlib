//
// Created by lucoder on 2019/4/17.
//
#include "mxlib/core/jiaotu.h"
#include "mxlib/configure/simpleConfiguration.h"
#include "mxlib/io/directory.h"

using namespace mxlib;

int main() {
    Jiaotu log;
    log.Configuration();
    log.WriteLine("log");

    log.Save();
    return 0;
}