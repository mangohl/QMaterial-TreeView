#include <QApplication>
#include "qmaterialview.h"
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(editabletreemodel);

    QApplication app(argc, argv);
    QMaterialView window;
    window.show();
    return app.exec();
}
