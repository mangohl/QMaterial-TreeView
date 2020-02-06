QT += widgets

FORMS       = mainwindow.ui
HEADERS     = \
              treeitem.h \
              treemodel.h \
    qmaterialitemdelegate.h \
    qmaterialview.h \
    qtmaterialripple.h \
    qtmaterialrippleoverlay.h
RESOURCES   = editabletreemodel.qrc
SOURCES     = \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp \
    qmaterialitemdelegate.cpp \
    qmaterialview.cpp \
    qtmaterialripple.cpp \
    qtmaterialrippleoverlay.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
