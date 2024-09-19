#ifndef AJOUTERPERSONNELS_H
#define AJOUTERPERSONNELS_H

#include <QMainWindow>

namespace Ui {
class AjouterPersonnels;
}

class AjouterPersonnels : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterPersonnels(QWidget *parent = nullptr);
    ~AjouterPersonnels();

private:
    Ui::AjouterPersonnels *ui;
};

#endif // AJOUTERPERSONNELS_H
