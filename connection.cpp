#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("");
db.setUserName("");
db.setPassword("");

if (db.open())
test=true;
    return  test;
}

