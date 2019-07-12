//
// Created by lucoder on 2019/4/17.
//
#include <iostream>
#include <fstream>
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

#ifndef MXLIB_FILE_H
#define MXLIB_FILE_H
namespace mxlib {
    class File {
    private:
        string _path;

    public:
        File(string v);
        ~File();
        bool Exist();
        bool createFile();
        bool remove();

        string getParent();
        string getFilename();
        string getFilenameWithoutExtension();
        string getExtension();
        string pwd();
        string readRow(int count);
        bool has_suffix(const std::string &filename, const std::string &suffix);
        // append a content in a row into the file
        int appendRow(string row);
        // change the content into a row of content
        int changeIntoRow(string row);
        void newFile(string content);
    };
}
#endif //MXLIB_FILE_H
