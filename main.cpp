#include "header.h"

namespace fs = std::filesystem;

int main() {
    auto cur_path = fs::path("/Users/nachernev/Desktop/labs_inf/virtual_file_system");
    //auto a = last_write_time(cur_path);
    FileObject cur_file(cur_path);
    cur_file.createTxtFile("mem.txt");
    cur_file.showDate();
    cur_file.deleteFile("mem.txt");
    return 0;
}
