TEMPLATE = app

SOURCES += \
        main.cpp

QMAKE_CXXFLAGS += /experimental:preprocessor /permissive- /std:c++latest

HEADERS += \
    lpl/lpl.h \
