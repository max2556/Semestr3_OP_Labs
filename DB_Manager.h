#pragma once

#include <string>
#include <vector>
#include <array>
#include <fstream>

#include "Record.hpp"

class DB_Manager
{
    // Приватные поля
private:
    inline static const char* DATABASE = "data.db";
    inline static const char* SEARCHBASE = "search.db";
    std::array<Record, 512> buffer;

    // Публичные статические методы
public:
    DB_Manager();
    std::vector<std::string> read_all();
    void remove_line(size_t index);
    void change_line(size_t index, const std::string& line);
    size_t size_of_base();

    void add_record(Record const& record);
    Record create_record();
    Record get_record(size_t index);

    std::vector<std::string> search(Record::WeekDay target);

    void sort_name();

    // Приватные методы
private:
    
    bool YN_Dialog();

    void GotoLine(std::size_t num, std::fstream& file_stream) {
        file_stream.seekg(std::ios::beg);
        for (std::size_t i = 0; i + 1 < num; ++i) {
            file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};

