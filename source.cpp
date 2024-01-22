#include "header.h"


Date::Date(int _day, int _month, int _year) :
    day(_day),
    month(_month),
    year(_year)
{}

//Date::Date(const std::string _date){
//    day = stoi(_date.substr(0, 2));
//    month = stoi(_date.substr(3, 2));
//    year = stoi(_date.substr(6, 4));
//}

std::ostream& operator << (std::ostream &out, Date &date) {
    out << date.day << '.' << date.month << '.' << date.year;
    return out;
}


FileObject::FileObject(std::filesystem::path _path) :
    path(_path),
    directory_name(_path.filename()),
    date_of_creation(13, 9, 2005),
    date_of_change(22, 1, 2023),
    type(".exe")
{}


void FileObject::showPath(){
    std::cout << path << '\n';
}

void FileObject::openTxtFile(std::string name){
    std::ifstream fin(path.string() + "/" + name);
    if (!fin) {
        std::cout << "No such file in this directory\n";
        return;
    }
    char chr;
    while (fin.get(chr)) {
        std::cout << chr;
    }
    std::cout << std::endl;
}

void FileObject::createTxtFile(std::string name) {
    std::ofstream fout(path.string() + "/" + name);
    char chr;
    std::cin.get(chr);
    while (chr != '`') {
        fout << chr;
        std::cin.get(chr);
    }
}

void FileObject::deleteFile(std::string name){
    if (remove((path.string() + "/" + name).c_str())) {
        std::cout << "No such file in this directory\n";
    }
}

void FileObject::showSize(std::string name){
    std::cout << file_size(std::filesystem::path(path.string() + "/" + name)) << " Bytes\n";
}

void FileObject::showDate(){
    std::cout << "File was created on " << date_of_creation << '\n';
    std::cout <<"Last change was on " << date_of_change << '\n';
}

void FileObject::changeFileName(std::string old_name, std::string new_name){
    rename((path.string() + "/" + old_name).c_str(), (path.string() + "/" + new_name).c_str());
}

void FileObject::showFiles(){
    if (std::filesystem::is_directory(path)) {
        for (auto file : std::filesystem::directory_iterator(path)) {
            std::cout << file << '\n';
        }
    }
    else {
        std::cout << "This is not a directory\n";
    }
}


void changeDirUp(FileObject &cur_file){
    cur_file = FileObject(cur_file.path.parent_path());
}

void changeDir(FileObject &cur_file, std::string name){
    std::filesystem::path new_path = cur_file.path.string() + "/" + name;
    if (is_directory(new_path)) {
        cur_file = FileObject(new_path);
    }
    else {
        std::cout << "This is not a directory\n";
    }
}

void help() {
    std::cout << "showpath - show current directory path\n";
    std::cout << "cd <name> - go to directory <name>\n";
    std::cout << "cdup - go to parent directory\n";
    std::cout << "opentxt <filename> - open txt file <filename>\n";
    std::cout << "createtxt <filename> - create txt file <filename>\n";
    std::cout << "delete <filename> - delete file <filename>\n";
    std::cout << "showsize <filename> - show size of <filename> in bytes\n";
    std::cout << "showdate <filename> - show dates of creation and changing of <filename>\n";
    std::cout << "changename <old_name> <new_name> - change name <old_name> to <new_name>\n";
    std::cout << "showfiles - show all files in current directory\n";
    std::cout << "end - end program\n";
}

void programLaunch() {
    bool run = true;
    FileObject cur_file(std::filesystem::current_path().parent_path());
    std::string cmd, filename, old_name;
    while (run) {
        std::cout << cur_file.directory_name << ": ";
        std::cin >> cmd;
        if (cmd == "showpath") {
            cur_file.showPath();
        }
        else if (cmd == "cd") {
            std::cin >> filename;
            changeDir(cur_file, filename);
        }
        else if (cmd == "cdup") {
            changeDirUp(cur_file);
        }
        else if (cmd == "opentxt") {
            std::cin >> filename;
            cur_file.openTxtFile(filename);
        }
        else if (cmd == "createtxt") {
            std::cin >> filename;
            cur_file.createTxtFile(filename);
        }
        else if (cmd == "delete") {
            std::cin >> filename;
            cur_file.deleteFile(filename);
        }
        else if (cmd == "showsize") {
            std::cin >> filename;
            cur_file.showSize(filename);
        }
        else if (cmd == "showdate") {
            cur_file.showDate();
        }
        else if (cmd == "changename") {
            std::cin >> old_name >> filename;
            cur_file.changeFileName(old_name, filename);
        }
        else if (cmd == "showfiles") {
            cur_file.showFiles();
        }
        else if (cmd == "end") {
            run = false;
        }
        else {
            std::cout << "Not such command\n";
        }
    }
}
