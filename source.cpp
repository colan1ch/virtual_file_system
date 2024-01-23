#include "header.h"


Date::Date(const std::string _date){
    seconds = stoi(_date.substr(17, 2));
    minutes = stoi(_date.substr(14, 2));
    hours = stoi(_date.substr(11, 2));
    day = stoi(_date.substr(8, 2));
    month = _date.substr(4, 3);
    year = stoi(_date.substr(20, 4));
}

std::ostream& operator << (std::ostream &out, Date &date) {
    out << std::setfill('0') << std::setw(2) << date.hours << ':' ;
    out << std::setfill('0') << std::setw(2) << date.minutes << ':';
    out << std::setfill('0') << std::setw(2) << date.seconds << ", ";
    out << date.day << ' ' << date.month << ' ' << date.year;
    return out;
}


FileObject::FileObject(std::filesystem::path _path) :
    path(_path),
    directory_name(_path.filename()),
    date_of_change(timeToString(std::filesystem::last_write_time(_path)))
{}


void FileObject::showPath(){
    std::cout << path << '\n';
}

void FileObject::openFile(std::string name){
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

void FileObject::createFile(std::string name) {
    std::ofstream fout(path.string() + "/" + name);
    std::cout << name << " //Use 'esc' to finish\n";
    char chr = getchar();
    while (chr != 27) {
        fout << chr;
        chr = getchar();
    }
}

void FileObject::deleteFile(std::string name){
    if (remove((path.string() + "/" + name).c_str())) {
        std::cout << "No such file in this directory\n";
    }
}

void FileObject::showSize(std::string name) {
    std::filesystem::path file_path(path.string() + "/" + name);
    if (std::filesystem::exists(file_path)) {
        std::cout << file_size(file_path) << " Bytes\n";
    }
    else {
        std::cout << "No such file in this directory\n";
    }
}

void FileObject::showDirDate() {
    std::cout <<"Last change of directory was in " << date_of_change << '\n';
}

void FileObject::showDate(std::string name) {
    std::filesystem::path file_path(path.string() + "/" + name);
    if (std::filesystem::exists(file_path)) {
        Date file_date(timeToString(std::filesystem::last_write_time(file_path)));
        std::cout << "Last change of file was in " << file_date << '\n';
    }
    else {
        std::cout << "No such file in this directory\n";
    }
}

void FileObject::changeFileName(std::string old_name, std::string new_name){
    if (rename((path.string() + "/" + old_name).c_str(), (path.string() + "/" + new_name).c_str())) {
        std::cout << "No such file in this directory\n";
    }
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
    std::cout << "path - show current directory path\n";
    std::cout << "cd <name> - go to directory <name>\n";
    std::cout << "cdup - go to parent directory\n";
    std::cout << "open <filename> - open txt file <filename>\n";
    std::cout << "create <filename> - create txt file <filename>\n";
    std::cout << "delete <filename> - delete file <filename>\n";
    std::cout << "size <filename> - show size of <filename> in bytes\n";
    std::cout << "dirdate - show date of changing a current directory\n";
    std::cout << "date <filename> - show date of changing <filename>\n";
    std::cout << "rename <old_name> <new_name> - change name <old_name> to <new_name>\n";
    std::cout << "files - show all files in current directory\n";
    std::cout << "end - end program\n";
}

void programLaunch() {
    bool run = true;
    FileObject cur_file(std::filesystem::current_path().parent_path());
    std::string cmd, filename, old_name;
    while (run) {
        std::cout << cur_file.directory_name << ": ";
        std::cin >> cmd;
        if (cmd == "path") {
            cur_file.showPath();
        }
        else if (cmd == "cd") {
            std::cin >> filename;
            changeDir(cur_file, filename);
        }
        else if (cmd == "cdup") {
            changeDirUp(cur_file);
        }
        else if (cmd == "open") {
            std::cin >> filename;
            cur_file.openFile(filename);
        }
        else if (cmd == "create") {
            std::cin >> filename;
            cur_file.createFile(filename);
        }
        else if (cmd == "delete") {
            std::cin >> filename;
            cur_file.deleteFile(filename);
        }
        else if (cmd == "size") {
            std::cin >> filename;
            cur_file.showSize(filename);
        }
        else if (cmd == "dirdate") {
            cur_file.showDirDate();
        }
        else if (cmd == "date") {
            std::cin >> filename;
            cur_file.showDate(filename);
        }
        else if (cmd == "rename") {
            std::cin >> old_name >> filename;
            cur_file.changeFileName(old_name, filename);
        }
        else if (cmd == "files") {
            cur_file.showFiles();
        }
        else if (cmd == "help") {
            help();
        }
        else if (cmd == "end") {
            run = false;
        }
        else {
            std::cout << "Not such command\n";
        }
    }
}


std::string timeToString(std::filesystem::file_time_type ftime) {
    std::time_t cftime = std::chrono::system_clock::to_time_t(
            std::chrono::time_point<std::chrono::system_clock>(
                    std::chrono::seconds(ftime.time_since_epoch() / std::chrono::seconds(1))
            )
    );
    std::string str = std::asctime(std::localtime(&cftime));
    str.pop_back();
    return str;
}
