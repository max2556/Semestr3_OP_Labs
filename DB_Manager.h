#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Record.hpp"

class DB_Manager
{
    // Приватные поля
private:
    inline static const char* CONFIG_FILE = "last_session.cfg";
    inline static const char* DATABASE = "data.db";
    inline static const char* SEARCHBASE = "search.db";
    static DB_Manager* instance;
    std::fstream file_stream = std::fstream();

    // Публичные статические методы
public:
    static DB_Manager* Instance() {
        if (!instance)
            instance = new DB_Manager();

        return instance;
    }

    void open_database(const std::string& file_name);
    void open_database();
    std::vector<std::string> read_all();
    void remove_line(size_t index);
    void change_line(size_t index, const std::string& line);
    size_t size_of_base();

    void add_record(Record&& record);
    Record create_record();
    Record get_record(size_t index);

    std::vector<std::string> search(Record::WeekDay target);

    void sort_name();

    // Приватные методы
private:
    // Смешной синглтон
    DB_Manager() = default;
    DB_Manager(const DB_Manager&) = delete;
    DB_Manager& operator=(const DB_Manager&) = delete;
    
    bool YN_Dialog();

    void GotoLine(std::size_t num) {
        file_stream.seekg(std::ios::beg);
        for (std::size_t i = 0; i + 1 < num; ++i) {
            file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};

