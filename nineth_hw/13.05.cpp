#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void remove_empty_lines(fs::path filepath) {
    std::ifstream filein(filepath.native(), std::ios::in);
    if (!filein.is_open()) {
        throw std::runtime_error("cannot open input file");
    }
    auto temppath = fs::temp_directory_path() / "temp.txt";
    std::ofstream fileout(temppath.native(), std::ios::out | std::ios::trunc);
    if (!fileout.is_open()) {
        throw std::runtime_error("cannot create temporary file");
    }
    std::string line;
    while (std::getline(filein, line)) {
        if (line.length() > 0 && line.find_first_not_of(' ') != line.npos) {
            fileout << line << '\n';
        }
    }
    filein.close();
    fileout.close();
    fs::remove(filepath);
    fs::rename(temppath, filepath);
}

int main() {
    auto temppath = fs::current_path() / "my_file.txt";
    std::ofstream file(temppath.native(), std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("cannot create my file");
    }
    file << "\n";
    file << "               \n";
    file << "nhldgl hhh\n";
    file.close();
    
    remove_empty_lines(temppath);
    std::ifstream file_changed(temppath.native(), std::ios::in);
    if (!file_changed.is_open()) {
        throw std::runtime_error("cannot open input file");
    }
    std::string line;
    while (std::getline(file_changed, line)) {
        std::cout << line << "\n";
    }

    file.close();
    fs::remove(temppath);
}
