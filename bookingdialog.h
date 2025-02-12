#ifndef BOOKINGDIALOG_H
#define BOOKINGDIALOG_H

#include <QDialog>

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

private:
    Ui::BookingDialog *ui;
        
    // Database operations
    void loadLocations();
    bool saveBooking();
    
    // Validation methods
    bool validateForm() const;
    bool isSeatAvailable(int seatNo) const;
    bool isValidRoute() const;
};

#endif // BOOKINGDIALOG_H
