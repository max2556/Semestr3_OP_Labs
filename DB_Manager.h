#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Record.h"


class DB_Manager
{
    // ��������� ����
private:
    inline static const char* CONFIG_FILE = "last_session.cfg";
    inline static const char* DATABASE = "data.db";
    inline static const char* SEARCHBASE = "search.db";
    static DB_Manager* instance;
    std::fstream file_stream = std::fstream();

    // ��������� ����������� ������
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

    // ��������� ������
private:
    DB_Manager() = default;
    bool YN_Dialog();

    void GotoLine(unsigned int num) {
        file_stream.seekg(std::ios::beg);
        for (int i = 0; i < num - 1; ++i) {
            file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};
