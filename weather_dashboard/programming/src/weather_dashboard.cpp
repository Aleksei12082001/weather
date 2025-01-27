#include "../include/weather_dashboard.hpp"
#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <iomanip>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

std::string formatDate(const std::string& date, int year) {
    std::tm tm = {};
    int day;
    std::string month;

    // Разбиваем строку на день и месяц
    std::istringstream ss(date);
    ss >> day >> month;

    // Приводим месяц к числовому значению
    if (month == "Января") {
        tm.tm_mon = 0; // Январь
    } else if (month == "Февраля") {
        tm.tm_mon = 1; // Февраль
    } else if (month == "Марта") {
        tm.tm_mon = 2; // Март
    } else if (month == "Апреля") {
        tm.tm_mon = 3; // Апрель
    } else if (month == "Мая") {
        tm.tm_mon = 4; // Май
    } else if (month == "Июня") {
        tm.tm_mon = 5; // Июнь
    } else if (month == "Июля") {
        tm.tm_mon = 6; // Июль
    } else if (month == "Августа") {
        tm.tm_mon = 7; // Август
    } else if (month == "Сентября") {
        tm.tm_mon = 8; // Сентябрь
    } else if (month == "Октября") {
        tm.tm_mon = 9; // Октябрь
    } else if (month == "Ноября") {
        tm.tm_mon = 10; // Ноябрь
    } else if (month == "Декабря") {
        tm.tm_mon = 11; // Декабрь
    } else {
        std::cerr << "Неизвестный месяц." << std::endl;
        return "";
    }

    tm.tm_mday = day;
    tm.tm_year = year - 1900; // Указываем год

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d"); // Преобразуем в формат "YYYY-MM-DD"
    return oss.str();
}

void getWeatherForecast(const std::string& apiKey, const std::string& city, const std::string& date, int year) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Формируем URL для запроса прогноза погоды
    std::string url = "http://api.openweathermap.org/data/2.5/forecast?q=" + city + "&appid=" + apiKey + "&units=metric";

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            auto jsonResponse = nlohmann::json::parse(readBuffer);
            std::cout << "Прогноз погоды в " << jsonResponse["city"]["name"] << " на " << date << " " << year << ":" << std::endl;

            std::string formattedDate = formatDate(date, year);
            if (formattedDate.empty()) {
                std::cerr << "Не удалось отформатировать дату." << std::endl;
                return;
            }

            bool found = false;

            for (const auto& item : jsonResponse["list"]) {
                std::string dateTime = item["dt_txt"];
                std::string time = dateTime.substr(0, 10); // Извлекаем дату (YYYY-MM-DD)

                if (time == formattedDate) {
                    double tempCelsius = item["main"]["temp"];
                    double tempFahrenheit = tempCelsius * 9.0 / 5.0 + 32;
                    std::cout << "Дата и время: " << dateTime << std::endl;
                    std::cout << "Температура: " << tempCelsius << "°C (" << tempFahrenheit << "°F)" << std::endl;
                    std::cout << "Влажность: " << item["main"]["humidity"] << "%" << std::endl;
                    std::cout << "Скорость ветра: " << item["wind"]["speed"] << " м/с" << std::endl;
                    std::cout << "Облачность: " << item["clouds"]["all"] << "%" << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Нет данных о погоде на указанную дату." << std::endl;
            }
        }
    }
}

