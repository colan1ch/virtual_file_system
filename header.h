#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <chrono>


struct Date{
    int seconds;
    int minutes;
    int hours;
    int day;
    std::string month;
    int year;

    Date(std::string _date);
};

std::ostream& operator << (std::ostream &out, Date &date);

struct FileObject{
    std::filesystem::path path;
    std::string directory_name;
    Date date_of_change;
    std::string type;

    FileObject(std::filesystem::path _path);

    void showPath();

    void openTxtFile(std::string name);

    void createTxtFile(std::string name);

    void deleteFile(std::string name);

    void showSize(std::string name);

    void showDirDate();

    void showDate(std::string name);

    void changeFileName(std::string old_name, std::string new_name);

    void showFiles();
};

void changeDirUp(FileObject &cur_file);

void changeDir(FileObject &cur_file, std::string name);

void help();

void programLaunch();

std::string timeToString(std::filesystem::file_time_type ftime);
