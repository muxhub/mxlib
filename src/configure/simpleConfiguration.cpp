//
// Created by lucoder on 2019/4/17.
//
#include "../../mxlib/configure/simpleConfiguration.h"

using namespace mxlib;
SimpleConfiguration::SimpleConfiguration() {}
bool SimpleConfiguration::load(string v) {
    this->_file = v;
    ifstream ifs(this->_file.c_str());

    if (!ifs)
        return false;

    string line;

    string key = "", value = "";
    size_t pos = -1;
    while (getline(ifs, line)) {
        if (line.substr(0, 1) == "#" || line.length() <= 0)
            continue;

        pos = line.find("=");
        key = line.substr(0, pos);
        value = line.substr(pos + 1);

        set(key, value);
    }
    ifs.close();

    return true;
}

string SimpleConfiguration::get(string key) {
    map<string, string>::iterator iter = this->factory.find(key);
    if (iter != this->factory.end())
        return iter->second;
    else
        return NULL;
}

string SimpleConfiguration::getAbsolute() {
    const char *file_name = this->_file.c_str();
    char abs_path_buff[PATH_MAX];
#if __linux__
    if (!realpath(file_name, abs_path_buff))
    {
        return nullptr;
    }
#endif
#if __WIN32__
    cout<<"xxx"<<endl;
#endif
    return abs_path_buff;
}

void SimpleConfiguration::set(string key, string value) {
    map<string, string>::iterator iter = this->factory.find(key);

    if (iter != this->factory.end())
        iter->second = value;
    else
        this->factory.insert(pair<string, string>(key, value));
}

bool SimpleConfiguration::hasKey(string key) {
    map<string, string>::iterator iter = this->factory.find(key);
    return iter != this->factory.end();
}

void SimpleConfiguration::print() {
    map<string, string>::iterator iter;
    printf("==========	SimpleConfiguration	==========\n");
    for (iter = this->factory.begin(); iter != this->factory.end(); iter++) {
        printf("[%s] = %s\n", iter->first.c_str(), iter->second.c_str());
    }
    printf("==========	SimpleConfiguration	==========\n");
}