#ifndef AJOUTEVENTS_H
#define AJOUTEVENTS_H

#include <QMainWindow>

namespace Ui {
class AjoutEvents;
}

class AjoutEvents : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjoutEvents(QWidget *parent = nullptr);
    ~AjoutEvents();

private:
    Ui::AjoutEvents *ui;
};

#endif // AJOUTEVENTS_H
