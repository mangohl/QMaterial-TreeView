#include "qmaterialitemdelegate.h"
#include "qpainter.h"
#include "qdebug.h"
#include "treeitem.h"
#include "qmaterialview.h"
#include "qevent.h"
QMaterialItemDelegate::QMaterialItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

    bgNormalColor = QColor(255, 255, 255);
    bgSelectedColor = QColor(242, 242, 242);
    bgHoverColor = QColor(242, 242, 242);
    textNormalColor = QColor(0, 0, 0);
    textSelectedColor = QColor(64,154,233);
    textHoverColor = QColor(0, 0, 0);


}

void QMaterialItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    painter->setRenderHint(QPainter::Antialiasing);

    QRect optionRect = option.rect;
    int x = optionRect.x();
    int y = optionRect.y();
    int width = optionRect.width();
    int height = optionRect.height();

    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
    if (option.state & QStyle::State_Selected)
    {
        bgColor =  this->bgSelectedColor;
        textColor =  this->textSelectedColor ;
        tipBgColor =  this->textSelectedColor ;
        tipTextColor =  this->bgSelectedColor;
        iconColor =  this->textSelectedColor ;

    } else if (option.state & QStyle::State_MouseOver)
    {
        bgColor =  this->bgHoverColor ;
        textColor =  this->textHoverColor ;
        tipBgColor =  this->textSelectedColor ;
        tipTextColor =  this->bgSelectedColor ;
        iconColor =  this->textHoverColor;
    } else
    {
        bgColor =  this->bgNormalColor ;
        textColor =  this->textNormalColor ;
        tipBgColor =  this->bgSelectedColor;
        tipTextColor =  this->textSelectedColor ;
        iconColor =  this->textNormalColor ;
    }


    //draw bg
    painter->fillRect(optionRect, bgColor);

    //draw text
    QString text = index.data(Qt::DisplayRole).toString();
    if (!text.isEmpty())
    {

        TreeItem *item = getItem(index);
        int delta = 0;
        bool hasChildren = false;
        if(item)
        {
            delta = item->level();
            if(item->childCount()>0)
                hasChildren = true;
        }

        QRect textRect = optionRect;
        textRect.setWidth(width);
        textRect.setX(x+delta*25);

        QFont font;
        font.setPixelSize(16);
        if(hasChildren)
            font.setBold(true);

        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, text);
    }

}

QSize QMaterialItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(60,40);
}

TreeItem *QMaterialItemDelegate::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return nullptr;
}
