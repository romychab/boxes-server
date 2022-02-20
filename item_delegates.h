#ifndef ITEM_DELEGATES_H
#define ITEM_DELEGATES_H

#include <QStyledItemDelegate>
#include <QDebug>
#include <QPainter>
#include <QApplication>


class ColorDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    void paint(QPainter *painter,
                   const QStyleOptionViewItem &option, const QModelIndex &index) const {
            QStyleOptionViewItem op(option);

            QString colorValue = index.data(Qt::DisplayRole).toString();
            QColor color = QColor(colorValue);
            op.backgroundBrush.setColor(color);
            op.backgroundBrush.setStyle(Qt::BrushStyle::SolidPattern);
            op.font.setBold(true);
            op.palette.setColor(QPalette::Text, QColor("#ffffff"));

            painter->fillRect(op.rect, op.backgroundBrush);

            QStyledItemDelegate::paint(painter, op, index);
        }
};

class CheckBoxDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    void paint(QPainter *painter,
                   const QStyleOptionViewItem &option, const QModelIndex &index) const {
            QStyleOptionViewItem op(option);

            QStyleOptionButton btnStyle;
            bool isActive = index.data(Qt::DisplayRole).toBool();
            if (isActive) {
                btnStyle.state = QStyle::State_On;
            } else {
                btnStyle.state = QStyle::State_Off;
            }
            btnStyle.rect = option.rect;
            btnStyle.rect.setLeft(btnStyle.rect.left() + 20);
            QApplication::style()->drawControl(QStyle::CE_CheckBox, &btnStyle, painter);
        }
};

#endif // ITEM_DELEGATES_H
