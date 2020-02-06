#ifndef QMATERIALVIEW_H
#define QMATERIALVIEW_H

#include <QTreeView>
class QtMaterialRippleOverlay;
class QMaterialView : public QTreeView
{
    Q_OBJECT
public:
    explicit QMaterialView(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

    void setRect(QRect rect);
private:
    void init();

private slots:
    void expandItem(const QModelIndex &index);
private:
    QRect m_rect;

    QPainterPath m_path;

    QPoint m_pos;

    QtMaterialRippleOverlay *const m_overlay;
};

#endif // QMATERIALVIEW_H
