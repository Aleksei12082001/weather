#ifndef WEATHER_DASHBOARD_HPP
#define WEATHER_DASHBOARD_HPP

#include <string>
#include <nlohmann/json.hpp>

// Функция для обработки ответа от API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

// Функция для форматирования даты
std::string formatDate(const std::string& date, int year);

// Функция для получения прогноза погоды
void getWeatherForecast(const std::string& apiKey, const std::string& city, const std::string& date, int year);

#endif // WEATHER_DASHBOARD_HPP
