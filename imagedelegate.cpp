#include "imagedelegate.h"
#include<QPainter>
ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 9) { // Remplacez 9 par l'index de la colonne contenant l'image
        QByteArray imageData = index.data(Qt::DisplayRole).toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        QRect rect = option.rect;
        rect.setSize(QSize(100, 100)); // Ajustez la taille de l'image selon vos besoins
        painter->drawPixmap(rect, pixmap);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
