#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations
class QLineEdit;
class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    // Login validation
    bool validateCredentials(const QString &username, const QString &password);

private slots:
    void onLoginButtonClicked();

private:
    Ui::MainWindow *ui;
    
    // UI Components
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
};

#endif // MAINWINDOW_H