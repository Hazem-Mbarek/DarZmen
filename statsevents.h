#ifndef STATSEVENTS_H
#define STATSEVENTS_H

#include <QMainWindow>

namespace Ui {
class StatsEvents;
}

class StatsEvents : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatsEvents(QWidget *parent = nullptr);
    ~StatsEvents();

private:
    Ui::StatsEvents *ui;
};

#endif // STATSEVENTS_H
