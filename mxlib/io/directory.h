//
// Created by lucoder on 2019/4/17.
//
#include <iostream>
#include <vector>

#if __WIN32__

#include <direct.h>
#include <io.h>

#endif
#if __linux__
#include <dirent.h>
#include <unistd.h>
#include <unistd.h>	/* gethostname */
#include <netdb.h>	 /* struct hostent */
#include <arpa/inet.h> /* inet_ntop */
#endif

using namespace std;
#ifndef MXLIB_DIRECTORY_H
#define MXLIB_DIRECTORY_H
namespace mxlib {
    class Directory {
    private:
        string _path;
        int DIR = 0x01;
        int FIL = 0x02;
        int getAllFiles(vector<string> &files, string folder, string ext = "*", bool topOnly = true, int attrib = 0x01);

    public:
        Directory();

        Directory(string path);

        void load(string v);

        bool Exist();

        bool remove();

        bool remove(string ext, bool topOnly = false);

        bool mk_dirs();

        string getParent();

        string pwd();

        int listFiles(vector<string> &files, string ext = "*", bool topOnly = true);

        int listFolders(vector<string> &folder, bool topOnly = true);
    };
}
#endif //MXLIB_DIRECTORY_H
