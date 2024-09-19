#ifndef AGENDAPERSONNELS_H
#define AGENDAPERSONNELS_H

#include <QMainWindow>

namespace Ui {
class AgendaPersonnels;
}

class AgendaPersonnels : public QMainWindow
{
    Q_OBJECT

public:
    explicit AgendaPersonnels(QWidget *parent = nullptr);
    ~AgendaPersonnels();

private:
    Ui::AgendaPersonnels *ui;
};

#endif // AGENDAPERSONNELS_H
