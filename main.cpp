#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>

int main(int argc, char* argv[]) {

    SetConsoleOutputCP(CP_UTF8);

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -c|-w filename" << std::endl;
        return 1;
    }

    std::string param = argv[1];
    std::string filename = argv[2];
    if (param != "-c" && param != "-w") {
        std::cerr << "Invalid parameter. Use -c or -w." << std::endl;
        return 1;
    }

    // 打开文件
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    if (param == "-c") {
        // 统计字符数
        long char_count = 0;
        char ch;
        while (infile.get(ch)) {   // 读取每个字符，包括空格、制表符、换行符
            char_count++;
        }
        std::cout << "字符数：" << char_count << std::endl;
    } else { // param == "-w"
        // 统计单词数（由空格或逗号分隔）
        long word_count = 0;
        bool in_word = false;
        char ch;
        while (infile.get(ch)) {
            if (ch == ' ' || ch == ',') {
                // 遇到分隔符，结束当前单词
                if (in_word) {
                    word_count++;
                    in_word = false;
                }
            } else {
                // 非分隔符，开始新单词或延续当前单词
                if (!in_word) {
                    in_word = true;
                }
            }
        }
        // 处理文件末尾的单词
        if (in_word) {
            word_count++;
        }
        std::cout << "单词数：" << word_count << std::endl;
    }

    infile.close();
    return 0;
}