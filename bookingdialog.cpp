#include "bookingdialog.h"
#include "ui_bookingdialog.h"
#include "ticketdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSet> 

BookingDialog::BookingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BookingDialog)
{
    ui->setupUi(this);
    loadLocations();
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    setupConnections();
    calculateFare();
}

void BookingDialog::setupConnections()
{
    connect(ui->bookButton, &QPushButton::clicked,
            this, &BookingDialog::onBookButtonClicked);
    connect(ui->sourceCombo, &QComboBox::currentTextChanged,
            this, &BookingDialog::onSourceChanged);
    connect(ui->destCombo, &QComboBox::currentTextChanged,
            this, &BookingDialog::onDestinationChanged);
    connect(ui->dateEdit, &QDateEdit::dateChanged,
            this, &BookingDialog::onDateChanged);
    connect(ui->discountSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &BookingDialog::onDiscountChanged);
}

void BookingDialog::loadLocations()
{
    QStringList locations = {"KIMARA TERMINAL", "UBUNGU TERMINAL", "KIVUKONI TERMINAL", "GEREZANI TERMINAL"};
    ui->sourceCombo->addItems(locations);
    ui->destCombo->addItems(locations);
}

int BookingDialog::getDistance(const QString &source, const QString &dest) const
{
    if((source == "KIMARA TERMINAL" && dest == "UBUNGU TERMINAL") || 
       (source == "UBUNGU TERMINAL" && dest == "KIMARA TERMINAL"))
        return 150; // 150km distance

    if((source == "KIMARA TERMINAL" && dest == "KIVUKONI TERMINAL") || 
       (source == "KIVUKONI TERMINAL" && dest == "KIMARA TERMINAL"))
        return 250; // 250km distance

    if((source == "KIMARA TERMINAL" && dest == "GEREZANI TERMINAL") || 
       (source == "GEREZANI TERMINAL" && dest == "KIMARA TERMINAL"))
        return 300; // 300km distance

    if((source == "UBUNGU TERMINAL" && dest == "KIVUKONI TERMINAL") || 
       (source == "KIVUKONI TERMINAL" && dest == "UBUNGU TERMINAL"))
        return 200; // 200km distance

    if((source == "UBUNGU TERMINAL" && dest == "GEREZANI TERMINAL") || 
       (source == "GEREZANI TERMINAL" && dest == "UBUNGU TERMINAL"))
        return 250; // 250km distance

    if((source == "KIVUKONI TERMINAL" && dest == "GEREZANI TERMINAL") || 
       (source == "GEREZANI TERMINAL" && dest == "KIVUKONI TERMINAL"))
        return 100; // 100km distance

    return 0;
}

void BookingDialog::calculateFare()
{
    QString source = ui->sourceCombo->currentText();
    QString dest = ui->destCombo->currentText();
    int distance = getDistance(source, dest);
    
    ui->distanceValue->setText(QString::number(distance) + " km");
    double fare = 750.0 + (distance / 10.0);
    ui->fareValue->setText(QString::number(fare, 'f', 2));
    
    calculateTotalFare();
}

void BookingDialog::calculateTotalFare()
{
    double fare = ui->fareValue->text().toDouble();
    int discount = ui->discountSpin->value();
    double totalFare = fare * (1.0 - (discount / 100.0));
    ui->totalFareValue->setText(QString::number(totalFare, 'f', 2));
}

void BookingDialog::updateAvailableSeats()
{
    QSqlQuery query;
    query.prepare("SELECT seat_no FROM bookings WHERE "
                 "source = :source AND destination = :dest "
                 "AND date = :date");
    query.bindValue(":source", ui->sourceCombo->currentText());
    query.bindValue(":dest", ui->destCombo->currentText());
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    
    QSet<int> bookedSeats;
    if (query.exec()) {
        while(query.next()) {
            bookedSeats.insert(query.value(0).toInt());
        }
    }

    ui->seatCombo->clear();
    for(int i = 1; i <= 50; i++) {
        if(!bookedSeats.contains(i)) {
            ui->seatCombo->addItem(QString::number(i));
        }
    }
}

bool BookingDialog::validateForm() const
{
    if (ui->nameInput->text().isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "Please enter passenger name");
        return false;
    }
    if (ui->sourceCombo->currentText() == ui->destCombo->currentText()) {
        QMessageBox::warning(nullptr, "Error", "Source and destination must be different");
        return false;
    }
    if (ui->seatCombo->currentText().isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "Please select a seat");
        return false;
    }
    return true;
}

bool BookingDialog::saveBooking()
{
    if (!validateForm()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO bookings (source, destination, date, passenger_name, "
                 "seat_no, distance, fare, discount, total_fare) "
                 "VALUES (:source, :dest, :date, :name, :seat, :distance, "
                 ":fare, :discount, :total)");
    
    query.bindValue(":source", ui->sourceCombo->currentText());
    query.bindValue(":dest", ui->destCombo->currentText());
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":seat", ui->seatCombo->currentText().toInt());
    query.bindValue(":distance", getDistance(ui->sourceCombo->currentText(), 
                                           ui->destCombo->currentText()));
    query.bindValue(":fare", ui->fareValue->text().toDouble());
    query.bindValue(":discount", ui->discountSpin->value());
    query.bindValue(":total", ui->totalFareValue->text().toDouble());

    return query.exec();
}

void BookingDialog::onBookButtonClicked()
{
    if (saveBooking()) {
        TicketDialog ticketDialog(
            ui->sourceCombo->currentText(),
            ui->destCombo->currentText(),
            ui->dateEdit->date().toString("yyyy-MM-dd"),
            ui->seatCombo->currentText().toInt(),
            getDistance(ui->sourceCombo->currentText(), ui->destCombo->currentText()),
            ui->fareValue->text().toDouble(),
            ui->discountSpin->value(),
            ui->totalFareValue->text().toDouble(),
            this
        );
        ticketDialog.exec();
        accept();
    }
}

void BookingDialog::onSourceChanged()
{
    calculateFare();
    updateAvailableSeats();
}

void BookingDialog::onDestinationChanged()
{
    calculateFare();
    updateAvailableSeats();
}

void BookingDialog::onDateChanged()
{
    updateAvailableSeats();
}

void BookingDialog::onDiscountChanged(int)
{
    calculateTotalFare();
}

BookingDialog::~BookingDialog()
{
    delete ui;
}
