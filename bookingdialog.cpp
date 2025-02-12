#include "bookingdialog.h"
#include "ui_bookingdialog.h"
#include "ticketdialog.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

BookingDialog::BookingDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::BookingDialog)
{
    ui->setupUi(this);

    // Load locations into comboboxes
    loadLocations();

    // Set date constraints
    ui->dateEdit->setMinimumDate(QDate::currentDate());

    // Connect signals
    connect(ui->bookButton, &QPushButton::clicked,
            this, &BookingDialog::onBookButtonClicked);
    connect(ui->sourceCombo, &QComboBox::currentTextChanged,
            this, &BookingDialog::updateAvailableSeats);
    connect(ui->destCombo, &QComboBox::currentTextChanged,
            this, &BookingDialog::updateAvailableSeats);
    connect(ui->dateEdit, &QDateEdit::dateChanged,
            this, &BookingDialog::updateAvailableSeats);
}

BookingDialog::~BookingDialog()
{
    delete ui;
}

void BookingDialog::loadLocations()
{
    QStringList locations = {"City A", "City B", "City C"};
    ui->sourceCombo->addItems(locations);
    ui->destCombo->addItems(locations);
}

bool BookingDialog::saveBooking()
{
    if (!validateForm()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO bookings (source, destination, date, seat_no) "
                 "VALUES (:source, :dest, :date, :seat)");
    query.bindValue(":source", ui->sourceCombo->currentText());
    query.bindValue(":dest", ui->destCombo->currentText());
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":seat", ui->seatSpinBox->value());

    return query.exec();
}

void BookingDialog::updateAvailableSeats()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM bookings WHERE "
                 "source = :source AND destination = :dest "
                 "AND date = :date");
    query.bindValue(":source", ui->sourceCombo->currentText());
    query.bindValue(":dest", ui->destCombo->currentText());
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    
    if (query.exec() && query.next()) {
        int bookedSeats = query.value(0).toInt();
        ui->seatSpinBox->setRange(1, 50 - bookedSeats);
    }
}

void BookingDialog::onBookButtonClicked()
{
    if (saveBooking()) {
       // Show ticket dialog with booking details
        TicketDialog ticketDialog(
            ui->sourceCombo->currentText(),
            ui->destCombo->currentText(),
            ui->dateEdit->date().toString("yyyy-MM-dd"),
            ui->seatSpinBox->value(),
            this
        );
        ticketDialog.exec();
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Failed to save booking");
    }
}

bool BookingDialog::validateForm() const
{
    if (ui->sourceCombo->currentText() == ui->destCombo->currentText()) {
        QMessageBox::warning(nullptr, "Error", "Source and destination must be different");
        return false;
    }
    return true;
}
