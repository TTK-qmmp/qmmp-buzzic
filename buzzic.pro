QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -std=gnu11

HEADERS += decoderbuzzicfactory.h \
           decoder_buzzic.h \
           buzzichelper.h \
           buzzicmetadatamodel.h \
           libbuzzic/Buzzic2.h \
           libbuzzic/Instruments.h \
           libbuzzic/Operations.h

SOURCES += decoderbuzzicfactory.cpp \
           decoder_buzzic.cpp \
           buzzichelper.cpp \
           buzzicmetadatamodel.cpp \
           libbuzzic/Buzzic2.cpp \
           libbuzzic/Instruments.cpp

INCLUDEPATH += $$PWD/libbuzzic

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/buzzic

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
    }
}else{
    QT += widgets
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        equals(QT_MAJOR_VERSION, 5){
            QMMP_PKG = qmmp-1
        }else:equals(QT_MAJOR_VERSION, 6){
            QMMP_PKG = qmmp
        }else{
            error("Unsupported Qt version: 5 or 6 is required")
        }
        
        PKGCONFIG += $${QMMP_PKG}

        PLUGIN_DIR = $$system(pkg-config $${QMMP_PKG} --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config $${QMMP_PKG} --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
