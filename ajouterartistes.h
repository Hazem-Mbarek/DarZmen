#ifndef AJOUTERARTISTES_H
#define AJOUTERARTISTES_H

#include <QMainWindow>

namespace Ui {
class AjouterArtistes;
}

class AjouterArtistes : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterArtistes(QWidget *parent = nullptr);
    ~AjouterArtistes();

private:
    Ui::AjouterArtistes *ui;
};

#endif // AJOUTERARTISTES_H
