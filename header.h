#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <chrono>
#ifdef _WIN64
#include <conio.h>
#define YEAR_DIFF 369
#define file_input std::cout << name << " //Use 'esc' to finish, use ctrl+j instead of 'enter' \n"; \
char chr = _getch(); \
char s[4000]; \
int ind = 0; \

while (chr != 27) { \
    if (chr != 8) { \
        s[ind++] = chr; \
        _putch(chr); \
    } \
    if (chr == '\n') { \
        _putch('\r'); \
        _putch('\n'); \
        s[ind++] = chr; \
    } \
    if ((chr == 8) && (ind > 0)) { \
        _putch(chr); \
        _putch(' '); \
        _putch(chr); \
        s[ind--] = ' '; \
    } \
    chr = _getch(); \
} \
for (int i = 0; i < ind; i++) { \
    fout << s[i]; \
}
#else
#include <curses.h>
#define YEAR_DIFF 0
#define file_input std::cout << name << " //Use 'esc' to finish\n"; \
char chr = getchar(); \
bool flag = true; \
while (chr != 27) { \
    if (!(flag && chr == '\n')) \
        fout << chr; \
    flag = false; \
    chr = getchar(); \
}
#endif


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

    FileObject(std::filesystem::path _path);

    void showPath();

    void createDirectory(std::string name);

    void openFile(std::string name);

    void createFile(std::string name);

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

int getSizeOfDirectory();
