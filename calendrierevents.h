#ifndef CALENDRIEREVENTS_H
#define CALENDRIEREVENTS_H

#include <QMainWindow>

namespace Ui {
class CalendrierEvents;
}

class CalendrierEvents : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalendrierEvents(QWidget *parent = nullptr);
    ~CalendrierEvents();

private:
    Ui::CalendrierEvents *ui;
};

#endif // CALENDRIEREVENTS_H
