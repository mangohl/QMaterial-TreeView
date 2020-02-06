#ifndef QMATERIALITEMDELEGATE_H
#define QMATERIALITEMDELEGATE_H

#include <QObject>
#include"QStyledItemDelegate"
class TreeItem;
class QMaterialItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QMaterialItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
    TreeItem *getItem(const QModelIndex &index) const;

private:
    QColor bgNormalColor;
    QColor bgSelectedColor;
    QColor bgHoverColor;
    QColor textNormalColor;
    QColor textSelectedColor;
    QColor textHoverColor;

signals:

public slots:
};

#endif // QMATERIALITEMDELEGATE_H
