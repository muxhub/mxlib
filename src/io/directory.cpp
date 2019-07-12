//
// Created by lucoder on 2019/4/17.
//
#include "../../mxlib/io/directory.h"

using namespace mxlib;

Directory::Directory() {}

Directory::Directory(string path) { this->_path = path; }

void Directory::load(string v) { this->_path = v; }

int Directory::listFiles(vector<string> &files, string ext, bool topOnly) {
    return getAllFiles(files, this->_path, ext, topOnly, FIL);
}

int Directory::listFolders(vector<string> &files, bool topOnly) {
    return getAllFiles(files, this->_path, "", topOnly, DIR);
}

int Directory::getAllFiles(vector<string> &files, string folder, string ext, bool topOnly, int attrib) {
    int totalCount = 0;

#if __linux__
    DIR *dir;
    struct dirent *ptr;
    if ((dir = opendir(folder.c_str())) == NULL)
    {
        perror("Open dri error...");
        exit(1);
    }
    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        else if (ptr->d_type == 8) //file
        {
            if (has_suffix(ptr->d_name, ext))
            {
                files.push_back(folder + "/" + ptr->d_name);
                totalCount++;
            }
        }
        else if (ptr->d_type == 10) //link file
            continue;
        else if (ptr->d_type == 4)
        {
            if (!topOnly)
                totalCount += getAllFiles(files, folder + "/" + ptr->d_name, ext, topOnly);
        }
    }
    closedir(dir);
#endif

#if __WIN32__
    //文件句柄
    long hFile = 0;

    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(folder).append("\\*" + ext).c_str(), &fileinfo)) != -1) {

        do {
            if (attrib == FIL) {
                if (topOnly) {
                    if (fileinfo.attrib != _A_SUBDIR) {
                        files.push_back(p.assign(folder).append("\\").append(fileinfo.name));
                    }
                } else if (fileinfo.attrib == _A_SUBDIR) {
                    if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                        getAllFiles(files, p.assign(folder).append("\\").append(fileinfo.name), ext, topOnly);
                    }
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
#endif

    return totalCount;
}


bool Directory::mk_dirs() {
    bool iResult = false;

    int state = access(_path.c_str(), R_OK | W_OK);
    if (state == 0) {
        return true;
    } else {
        try {
            char buf[255];
            if (_path.length() > 255) {
                cout << "path input is too long!" << endl;
                return false;
            }
            sprintf(buf, "mkdir -p %s", _path.c_str());
            if (system(buf) > 0) iResult = true;
            return iResult;
        }
        catch (const std::exception e) {
            iResult = false;
            return iResult;
        }
    }


    return iResult;
}


bool Directory::remove(string ext, bool topOnly) {
    vector<string> files;
    listFiles(files, ext, topOnly);

    char buf[1024];
    for (int i = 0; i < files.size(); i++) {
        sprintf(buf, "rm -rf %s", files[i].c_str());
        if (system(buf) == -1)
            return false;
    }

    return true;
}