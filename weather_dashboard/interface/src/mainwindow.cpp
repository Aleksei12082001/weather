#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <nlohmann/json.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    cityInput = new QLineEdit(this);
    cityInput->setPlaceholderText("Введите город");

    dateInput = new QLineEdit(this);
    dateInput->setPlaceholderText("Введите дату (например, 26 Января)");

    yearInput = new QLineEdit(this);
    yearInput->setPlaceholderText("Введите год (например, 2025)");

    QPushButton *fetchButton = new QPushButton("Получить погоду", this);
    resultLabel = new QLabel(this);

    layout->addWidget(cityInput);
    layout->addWidget(dateInput);
    layout->addWidget(yearInput);
    layout->addWidget(fetchButton);
    layout->addWidget(resultLabel);

    connect(fetchButton, &QPushButton::clicked, this, &MainWindow::fetchWeather);
}

void MainWindow::fetchWeather() {
    std::string apiKey = "ваш_API_ключ"; // Замените на ваш API ключ
    std::string city = cityInput->text().toStdString();
    std::string date = dateInput->text().toStdString();
    int year = yearInput->text().toInt();

    // Проверка на пустые поля
    if (city.empty() || date.empty() || year <= 0) {
        resultLabel->setText("Пожалуйста, заполните все поля.");
        return;
    }

    getWeatherForecast(apiKey, city, date, year, this);
}

void MainWindow::handleNetworkReply(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        auto json = nlohmann::json::parse(responseData.toStdString());

        // Проверка наличия данных о погоде
        if (json.contains("forecast") && json["forecast"].contains("forecastday")) {
            std::string weatherData = json["forecast"]["forecastday"][0]["day"]["condition"]["text"];
            resultLabel->setText(QString::fromStdString(weatherData));
        } else {
            resultLabel->setText("Данные о погоде не найдены.");
        }
    } else {
        resultLabel->setText("Не удалось получить данные о погоде.");
    }
    reply->deleteLater();
}

void getWeatherForecast(const std::string& apiKey, const std::string& city, const std::string& date, int year, MainWindow* mainWindow) {
    QNetworkAccessManager* manager = new QNetworkAccessManager(mainWindow); // Привязка к mainWindow для управления временем жизни
    QUrl url = QUrl("https://api.weatherapi.com/v1/history.json?key=" + QString::fromStdString(apiKey) + "&q=" + QString::fromStdString(city) + "&dt=" + QString::fromStdString(date) + "-" + QString::number(year));

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, mainWindow]() {
        mainWindow->handleNetworkReply(reply);
    });
}




