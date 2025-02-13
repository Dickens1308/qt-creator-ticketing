#ifndef BOOKINGDIALOG_H
#define BOOKINGDIALOG_H

#include <QDialog>
#include <QDate>
#include <QSqlDatabase>

namespace Ui {
class BookingDialog;
}

class BookingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookingDialog(QWidget *parent = nullptr);
    ~BookingDialog();

private slots:
    void onBookButtonClicked();
    void updateAvailableSeats();
    void calculateFare();
    void calculateTotalFare();
    void onSourceChanged();
    void onDestinationChanged();
    void onDateChanged();
    void onDiscountChanged(int value);

private:
    Ui::BookingDialog *ui;
    void setupConnections();
    void loadLocations();
    bool saveBooking();
    bool validateForm() const;
    int getDistance(const QString &source, const QString &dest) const;
    double calculateBaseFare(int distance) const;
    void showError(const QString &message) const;
    void clearForm();
    bool checkSeatAvailability(int seatNo) const;
    double applyDiscount(double fare, int discountPercent) const;
};

#endif // BOOKINGDIALOG_H