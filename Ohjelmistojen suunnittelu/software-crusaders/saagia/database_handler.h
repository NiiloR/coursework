#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H
#include <memory>

#include <QJsonObject>
#include <QString>
#include <memory>
#include <vector>
#include <string>
#include <QIODevice>

class Data_structures;

// default municipalities file
const QString DEFAULT_MUNICIPALITIES_FILE = ":/settings/municipalities.txt";

class Database_handler
{

public:

    Database_handler(std::shared_ptr<Data_structures> data_structures);

    QString load_data(QString file);
    bool save_data() const;
    //bool save_data(QString start_time, int data_type) const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    std::vector<std::string> read_municipalities();

    bool save_to_file();

private:
    std::shared_ptr<Data_structures> data_structures_;

};

#endif // DATABASE_HANDLER_H
