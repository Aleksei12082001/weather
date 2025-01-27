cmake_minimum_required(VERSION 3.10)

project(WeatherDashboard)

set(CMAKE_CXX_STANDARD 17)

# Найдите библиотеки Qt и CURL
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(CURL REQUIRED)

# Укажите пути к заголовочным файлам
include_directories(include)

# Определите исходные файлы
set(SOURCE_EXE src/main.cpp)
set(SOURCE_LIB src/weather_dashboard.cpp)

# Добавление библиотеки
add_library(weather_dashboard STATIC ${SOURCE_LIB})

# Добавление исполняемого файла
add_executable(main ${SOURCE_EXE})

# Связывание библиотек
target_link_libraries(main PRIVATE 
    weather_dashboard 
    CURL::libcurl 
    Qt5::Widgets 
    Qt5::Core 
    Qt5::Gui
)












