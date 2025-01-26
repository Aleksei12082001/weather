# Определите компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC

# Определите пути к заголовочным файлам
INCLUDE_DIRS = -I./interface/include -I./programming/include -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtNetwork -I/usr/include/x86_64-linux-gnu/qt5

# Определите файлы
SOURCES = interface/src/mainwindow.cpp programming/src/main.cpp programming/src/weather_dashboard.cpp interface/src/moc_mainwindow.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Определите целевую программу
TARGET = weather_dashboard

# Правило сборки
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ -lcurl -lQt5Widgets -lQt5Core -lQt5Gui -lQt5Network

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Генерация moc файла
interface/src/moc_mainwindow.cpp: interface/include/mainwindow.hpp
	moc $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: all
	./$(TARGET)


