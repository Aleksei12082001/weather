#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <string>

// Объявление класса MainWindow
class MainWindow; // Предварительное объявление класса

// Объявление функции получения прогноза погоды
void getWeatherForecast(const std::string& apiKey, const std::string& city, const std::string& date, int year, MainWindow* mainWindow);

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void fetchWeather();
    void handleNetworkReply(QNetworkReply* reply);

private:
    QLineEdit *cityInput;
    QLineEdit *dateInput;
    QLineEdit *yearInput;
    QLabel *resultLabel;
};

#endif // MAINWINDOW_H



