cmake_minimum_required(VERSION 3.10)
project(WeatherDashboard)

set(CMAKE_CXX_STANDARD 17)

# Найдите библиотеки Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

# Укажите путь к библиотеке curl
find_package(CURL REQUIRED)

# Укажите путь к библиотеке nlohmann/json
add_subdirectory(nlohmann_json)  # Предполагается, что библиотека находится в подкаталоге

# Добавление исполняемого файла
add_executable(weather_dashboard 
    interface/src/mainwindow.cpp 
    programming/src/main.cpp 
    programming/src/weather_dashboard.cpp
)

# Укажите пути к заголовочным файлам
target_include_directories(weather_dashboard PRIVATE 
    interface/include 
    programming/include 
    ${Qt5Widgets_INCLUDE_DIRS}
)

# Связывание библиотек
target_link_libraries(weather_dashboard PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json 
    Qt5::Widgets 
    Qt5::Core 
    Qt5::Gui
)

# Добавление цели для запуска
add_custom_target(run
    COMMAND $<TARGET_FILE:weather_dashboard>
    DEPENDS weather_dashboard
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Цель для очистки
add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:weather_dashboard>
    COMMENT "Cleaning up the weather_dashboard executable"
)

