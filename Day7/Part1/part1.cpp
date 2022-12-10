#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

class File
{
private:
    int size;
    std::string name;
public:
    File(/* args */) = default;
    File(const File& rhs)
    :size(rhs.size),name(rhs.name)
    {}
    ~File() = default;

    File operator=(const File& rhs)
    {
        size = rhs.getSize();
        name = rhs.getName();
        return *this;
    }

    void setSize(int rhs) {size = rhs;}
    int getSize() const {return size;}

    void setName(const std::string& rhs) {name = rhs;}
    std::string getName() const {return name;}
};

class Directory
{
public:
    Directory* parent = nullptr;
    int size = 0;
    std::string name;
    std::vector<File> files;
    std::vector<Directory> dirs;
    Directory(/* args */) = default;
    Directory(Directory* parent, const std::string name)
    :parent(parent),name(name)
    {}
    Directory(const Directory& rhs)
    :parent(rhs.parent),size(rhs.size),name(rhs.name),files(rhs.files), dirs(rhs.dirs)
    {}
    ~Directory() = default;

    Directory operator=(const Directory& rhs)
    {
        parent = rhs.getParent();
        size = rhs.getSize();
        files = rhs.getFiles();
        dirs = rhs.getDirectories();
        name = rhs.getName();
        return *this;
    }

    void operator+=(const File& file)
    {
        addFile(file);
        *this += file.getSize();
    }

    void operator+=(int rhssize)
    {
        size += rhssize;
        if(parent != nullptr)
        {
            *parent += rhssize;
        }
    }

    void setParent(Directory* rhs) {parent = rhs;}
    Directory* getParent() const {return parent;}

    void addFile(const File& file) {files.push_back(file);}
    std::vector<File> getFiles() const {return files;}

    void addDirectory(const Directory& dir) {dirs.push_back(dir);}
    std::vector<Directory> getDirectories() const {return dirs;}

    void setSize(int rhs) {size = rhs;}
    int getSize() const {return size;}

    void setName(const std::string& rhs) {name = rhs;}
    std::string getName() const {return name;}
};

std::vector<std::string> split(const std::string str, const std::string& sep)
{
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL)
    {
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
}

int findAtMostTenThousand(const Directory& dir)
{
    int sum = 0;
    if(dir.size <= 100000)
    {
        std::cout << dir.name << ": " << dir.size << "\n";
        sum += dir.size;
    }
    for(auto x : dir.dirs)
    {
        sum += findAtMostTenThousand(x);
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        return -1;
    }
    else
    {
        std::string filename = argv[1];
        std::ifstream file(filename);

        int charcount = 0;
        Directory root;
        root.setName("/");
        Directory* fsptr;
        fsptr = &root;
        bool ls = false;
        int i;
        while(!file.eof())
        {
            std::string temp;
            std::getline(file, temp);
            if(temp != "")
            {
                std::vector<std::string> cmd = split(temp, " ");
                if(cmd[0] == "$" && cmd[1] != "ls")
                {
                    ls = false;
                }
                if(cmd[1] == "cd")
                {
                    if(cmd[2] == "/")
                    {
                        fsptr = &root;
                    }
                    else if(cmd[2] == "..")
                    {
                        fsptr = fsptr->getParent();
                    }
                    else
                    {
                        for(i = 0; i < fsptr->getDirectories().size(); ++i)
                        {
                            if(cmd[2] == fsptr->getDirectories()[i].getName())
                            {
                                Directory* parnt = fsptr;
                                fsptr = &fsptr->dirs[i];
                                fsptr->setParent(parnt);
                                break;
                            }
                        }
                    }
                }
                else if(cmd[1] == "ls" || ls)
                {
                    if(ls)
                    {
                        if(cmd[0] == "dir")
                        {
                            Directory tmp(fsptr,cmd[1]);
                            fsptr->addDirectory(tmp);
                        }
                        else
                        {
                            File tmp;
                            tmp.setName(cmd[1]);
                            tmp.setSize(std::stoi(cmd[0]));
                            *fsptr += tmp;
                        }
                    }
                    ls = true;
                }
            }
        }
        int sum = findAtMostTenThousand(root);
        std::cout << sum << "\n";
    }
    return 0;
}