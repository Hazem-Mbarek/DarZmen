#ifndef AJOUTERSALLES_H
#define AJOUTERSALLES_H

#include <QMainWindow>

namespace Ui {
class AjouterSalles;
}

class AjouterSalles : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterSalles(QWidget *parent = nullptr);
    ~AjouterSalles();

private:
    Ui::AjouterSalles *ui;
};

#endif // AJOUTERSALLES_H
