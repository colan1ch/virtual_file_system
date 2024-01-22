#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

struct Date{
    int day;
    int month;
    int year;
    Date(int _day, int _month, int _year);
    //Date(std::string _date);
};

std::ostream& operator << (std::ostream &out, Date &date);


struct FileObject{
    std::filesystem::path path;
    std::string directory_name;
    Date date_of_creation;
    Date date_of_change;
    std::string type;

    FileObject(std::filesystem::path _path);

    void showPath();

    void openTxtFile(std::string name);

    void createTxtFile(std::string name);

    void deleteFile(std::string name);

    void showSize(std::string name);

    void showDate();

    void changeFileName(std::string old_name, std::string new_name);

    void showFiles();

};

void changeDirUp(FileObject &cur_file);

void changeDir(FileObject &cur_file, std::string name);

void help();

void programLaunch();
