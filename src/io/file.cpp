//
// Created by lucoder on 2019/4/17.
//
#include "../../mxlib/io/file.h"
using namespace mxlib;
File::File(string path) { _path = path; }
File::~File() {}

bool File::Exist()
{
    if (this->_path.c_str() == NULL)
        return false;

    if (access(this->_path.c_str(), F_OK) == 0)
        return true;
    return false;
}

bool File::has_suffix(const std::string &filename, const std::string &suffix)
{
    std::size_t index = filename.find(suffix, filename.size() - suffix.size());
    return (index != std::string::npos);
}
string File::getParent()
{
    int pos = _path.find_last_of("\\");
    int spos = _path.find_last_of("/");
    return _path.substr(0, pos > spos ? pos : spos);
}
string File::readRow(int i)
{
    ifstream ifs(_path.c_str());
    int count = 0;
    string v = "", line = "";

    while (getline(ifs, line))
    {
        if (count == i)
        {
            v = line;
            break;
        }

        ++count;
    }
    ifs.close();
    return v;
}
string File::getFilename() { return _path.substr(_path.find_last_of('/') + 1); }
string File::getFilenameWithoutExtension()
{
    string fname = getFilename();

    return fname.substr(0, fname.find_last_of('.'));
}
string File::getExtension()
{
    string filename = getFilename();
    return filename.substr(filename.find_last_of('.') + 1);
}
bool File::remove()
{
    char buf[1024];
    sprintf(buf, "rm -rf %s", this->_path.c_str());
    return system(buf) != -1;
}
int File::appendRow(string row)
{
    fstream ifs(this->_path.c_str(), std::ios::app);
    ifs << row << endl;
    ifs.flush();
    ifs.close();

    return row.size();
}
int File::changeIntoRow(string row)
{
    char cmd[2048];
    sprintf(cmd, "rm -rf %s", this->_path.c_str());
    if (system(cmd) < 0)
        return -1;

    fstream ifs(this->_path.c_str());
    ifs << row << endl;
    ifs.flush();
    ifs.close();

    return row.size();
}
void File::newFile(string content)
{
    ofstream ofs(this->_path.c_str());
    ofs << content;
    ofs.flush();
    ofs.close();
}
