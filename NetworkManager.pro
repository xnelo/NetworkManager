INCLUDEPATH += inc

SOURCES += \
    src/Manager/main.cpp \
    src/Agent/main.cpp \
    src/Common/Logger/Logger.cpp \
    src/Common/Sockets/ListeningSocket.cpp \
    src/Common/Sockets/ConnectionSocket.cpp

HEADERS += \
    inc/Common/Logger/Logging.hpp \
    inc/Common/Sockets/ListeningSocket.hpp \
    inc/Common/Sockets/ConnectionSocket.hpp \
    inc/Common/Sockets/Socket.hpp
