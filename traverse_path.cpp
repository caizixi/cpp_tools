#include <algorithm> //remove
#include<vector>
#include<string>
#include <fstream>
#include <iostream>
#include <dirent.h> // opendir
#include <sys/stat.h> //S_ISDIR
using namespace std;

bool IsDir(const string& fileFullName)
{
    struct stat statbuf;
    if(0 == lstat(fileFullName.c_str(), &statbuf))
    {
        return S_ISDIR(statbuf.st_mode) != 0;   //判断是否为目录
    }
    return false;
}

bool GetChildDir(const string &dir, vector<string> &childDir)
{
    childDir.clear();

    if(false == IsDir(dir))
    {
        cout<<dir<<"不是目录"<<endl;
        // ERROR_MESSAGE(dir + "不是目录\n");
        return false;
    }
    DIR *directory = NULL;
    dirent *dir_info;
    if((directory = opendir(dir.c_str())) == NULL)
    {
        cout<<dir<<"打开失败"<<endl;
        // ERROR_MESSAGE("打开" + dir + "目录错误\n");
        return false;
    }
    while((dir_info = readdir(directory)) != NULL)
    {
        string filename = dir_info->d_name;
        if("." == filename or ".." == filename)
        {
            continue;
        }
        string fullFilename = dir + "/" + filename;
        if(true == IsDir(fullFilename))
        {
            childDir.push_back(filename);
        }
    }
    closedir(directory);
    return true;
}


inline bool filterInvalidInc(const std::string& inc) {
    int len = inc.length();
    if (len != 14)  // 20170705160019
        return true;
    int i = 0;
    while (i < len) {
        if (inc[i] < '0' || inc[i] > '9') return true;
        ++i;
    }
    return false;
}

void print_size_top10(vector<string> &inc_data_dirs) {
    cout<<inc_data_dirs.size()<<" before size"<<endl;
	for(int i =0 ;i<10;i++) {
        cout<<inc_data_dirs[i]<<endl;
    }
}

int main(){
    string path="/searcher/inc_update";
    std::vector<std::string> inc_data_dirs;
    GetChildDir(path,inc_data_dirs);

    print_size_top10(inc_data_dirs);
    inc_data_dirs.erase(std::remove_if(inc_data_dirs.begin(),inc_data_dirs.end(), filterInvalidInc),inc_data_dirs.end());    
    print_size_top10(inc_data_dirs);
    return 0;
}


