#include "../include/weather_dashboard.hpp"
#include <iostream>

int main() {
    std::string apiKey = "e65d6931bc3a7c70f342b41daa78f990"; // Замените на ваш реальный API ключ
    std::string city;
    std::string date;
    int year;

    std::cout << "Введите город: ";
    std::getline(std::cin, city); // Вводим город с клавиатуры

    std::cout << "Введите дату (например, 26 Января): ";
    std::getline(std::cin, date); // Вводим дату с клавиатуры

    std::cout << "Введите год (например, 2025): ";
    std::cin >> year; // Вводим год с клавиатуры

    getWeatherForecast(apiKey, city, date, year);

    return 0;
}

