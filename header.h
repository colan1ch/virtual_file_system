#pragma once
#include <iostream>
#include <vector>

struct Date{
    int date;
    int month;
    int year;
    Date(int _date, int _month, int _year);
    Date(std::string _date);
};

struct FileObject{
    std::string path;
    Date date_of_creation;
    Date date_of_change;
    std::string type;

    //BaseFileObject(std::string _path, Date _date_of_creation, Date _date_of_change, std::string _type);

    void showPath();

    void changeDir(std::string name);

    void changeDirUp();

    void openFile(std::string name);

    void deleteFile(std::string name);

    void showSize();

    void showDate();

    void changeFileName(std::string new_name);

    void showFiles();

};

std::ostream& operator << (std::ostream& out, FileObject object);


