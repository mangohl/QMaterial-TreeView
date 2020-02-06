#include "qmaterialview.h"
#include "qfile.h"
#include "treemodel.h"
#include "qmaterialitemdelegate.h"
#include "QMouseEvent"
#include "qtmaterialripple.h"
#include "qtmaterialrippleoverlay.h"
#include "qpainterpath.h"
QMaterialView::QMaterialView(QWidget *parent) : QTreeView(parent),\
    m_overlay(new QtMaterialRippleOverlay(this))
{
    init();

    setExpandsOnDoubleClick(false);
    connect(this,SIGNAL(pressed(QModelIndex)),this,SLOT(expandItem(QModelIndex)));

    this->resize(330,500);
}

void QMaterialView::mousePressEvent(QMouseEvent *event)
{

    m_pos = event->pos();
    QTreeView::mousePressEvent(event);

}

void QMaterialView::setRect(QRect rect)
{
    m_rect = rect;
    QPainterPath path;
    path.addRect(rect);
    m_path=path;
}

void QMaterialView::init()
{
    QStringList headers;
    headers << tr("Title");

    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();

    this->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column)
        this->resizeColumnToContents(column);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setAnimated(true);
    this->setHeaderHidden(true);

    QMaterialItemDelegate *delegate = new QMaterialItemDelegate(this);
    this->setItemDelegate(delegate);
    this->setRootIsDecorated(false);
    this->setIndentation(0);

    this->setStyleSheet("QTreeView::branch:has-children:!has-siblings:closed,\
    QTreeView::branch:closed:has-children:has-siblings{border-image: none; image: none;}\
    QTreeView::branch:open:has-children:!has-siblings,\
    QTreeView::branch:open:has-children:has-siblings{border-image: none; image: none;}");

}

void QMaterialView::expandItem(const QModelIndex &index)
{

    QRect rect = this->visualRect(index);

    if(rect.contains(m_pos))
    {
        m_overlay->setGeometry(rect);

        //can use mapToGlobal and mapFromGlobal in not parent-child widgets
        QPoint p =m_overlay->mapFrom(this,m_pos);

        QtMaterialRipple *ripple = new QtMaterialRipple(p);

        ripple->setRadiusEndValue(rect.width());
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(QColor(0,0.7*255,0.8*255,255));
        ripple->radiusAnimation()->setDuration(800);
        ripple->opacityAnimation()->setDuration(1300);

        m_overlay->addRipple(ripple);

    }

    if(index.child(0,0).isValid())
             this->isExpanded(index)? this->collapse(index) : this->expand(index);
}
