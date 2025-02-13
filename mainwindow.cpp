#include "mainwindow.h"
#include "welcomescreendialog.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

       // Setup database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("login.db");
    
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", 
                            "Could not open database");
        return;
    }

    // Create users table if not exists
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users "
              "(username TEXT PRIMARY KEY, password TEXT)");

    // Create booking table
    query.exec("CREATE TABLE IF NOT EXISTS bookings "
              "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
              "source TEXT NOT NULL, "
              "destination TEXT NOT NULL, "
              "date TEXT NOT NULL, "
              "passenger_name TEXT NOT NULL, "
              "seat_no INTEGER NOT NULL, "
              "distance REAL NOT NULL DEFAULT 0.0, "
              "fare REAL NOT NULL DEFAULT 0.0, "
              "discount REAL NOT NULL DEFAULT 0.0, "
              "total_fare REAL NOT NULL DEFAULT 0.0)");

    query.exec("PRAGMA table_info(bookings)");
    
    QStringList columns;
    while (query.next()) {
        columns << query.value(1).toString();
    }
    
    if (!columns.contains("fare")) {
        query.exec("ALTER TABLE bookings ADD COLUMN fare REAL NOT NULL DEFAULT 0.0");
    }

    if (!columns.contains("discount")) {
        query.exec("ALTER TABLE bookings ADD COLUMN discount REAL NOT NULL DEFAULT 0.0");
    }

    if (!columns.contains("total_fare")) {
        query.exec("ALTER TABLE bookings ADD COLUMN total_fare REAL NOT NULL DEFAULT 0.0");
    }

        
    if (!columns.contains("passenger_name")) {
        query.exec("ALTER TABLE bookings ADD COLUMN passenger_name TEXT NOT NULL DEFAULT ''");
    }
    
    if (!columns.contains("distance")) {
        query.exec("ALTER TABLE bookings ADD COLUMN distance REAL NOT NULL DEFAULT 0.0");
    }                 
    
    // Add admin user if not exists
    query.prepare("INSERT OR IGNORE INTO users (username, password) "
                 "VALUES (:username, :password)");
    query.bindValue(":username", "admin");
    query.bindValue(":password", "password");
    query.exec();
    
    // Initialize UI components
    usernameInput = ui->usernameInput;
    passwordInput = ui->passwordInput;
    loginButton = ui->loginButton;

    // Connect button click to slot
    connect(loginButton, &QPushButton::clicked, 
            this, &MainWindow::onLoginButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginButtonClicked()
{
    QString username = usernameInput->text().trimmed();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", 
                           "Please enter both username and password");
        return;
    }

    if (validateCredentials(username, password)) {
        WelcomeScreenDialog dialog(this);
        dialog.exec();
        
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", 
                           "Invalid username or password");
        passwordInput->clear();
        passwordInput->setFocus();
    }
}

bool MainWindow::validateCredentials(const QString &username, 
                                  const QString &password)
{
   QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);
    
    if (query.exec() && query.next()) {
        return query.value(0).toString() == password;
    }
    return false;
}
