#include "MainWindow.h"
#include "Trip.h"
#include "FileManager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QDoubleValidator>
#include <QFont>
#include <QLocale>
#include <QGroupBox>
#include <QSpacerItem>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), hasCalculated(false)
{
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(18, 16, 18, 14);
    mainLayout->setSpacing(8);

    // Keep the same simple, clean appearance shown in the report screenshots.
    QLabel *titleLabel = new QLabel("Road Trip Planner (India)", this);
    QFont titleFont("Arial", 12, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addSpacing(22);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(18);

    // Narrow, centered form area to match the compact form shown in the report.
    QWidget *formContainer = new QWidget(this);
    formContainer->setMaximumWidth(390);
    QFormLayout *formLayout = new QFormLayout(formContainer);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setHorizontalSpacing(12);
    formLayout->setVerticalSpacing(5);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    sourceEdit = new QLineEdit(this);
    sourceEdit->setPlaceholderText("e.g. Mumbai");

    destEdit = new QLineEdit(this);
    destEdit->setPlaceholderText("e.g. Pune");

    distanceEdit = new QLineEdit(this);
    distanceEdit->setPlaceholderText("e.g. 200");

    vehicleTypeCombo = new QComboBox(this);
    vehicleTypeCombo->addItem("Bike");
    vehicleTypeCombo->addItem("Car");
    vehicleTypeCombo->addItem("SUV");

    mileageEdit = new QLineEdit(this);
    mileageEdit->setPlaceholderText("e.g. 15.0");

    priceEdit = new QLineEdit(this);
    priceEdit->setPlaceholderText("e.g. 100.00");

    speedEdit = new QLineEdit(this);
    speedEdit->setPlaceholderText("e.g. 60");

    QDoubleValidator *doubleValidator =
        new QDoubleValidator(0.001, 999999.9, 3, this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setLocale(QLocale::c());

    distanceEdit->setValidator(doubleValidator);
    mileageEdit->setValidator(doubleValidator);
    priceEdit->setValidator(doubleValidator);
    speedEdit->setValidator(doubleValidator);

    formLayout->addRow("Source City:", sourceEdit);
    formLayout->addRow("Destination City:", destEdit);
    formLayout->addRow("Distance (km):", distanceEdit);
    formLayout->addRow("Vehicle Type:", vehicleTypeCombo);
    formLayout->addRow("Vehicle Mileage (km/l):", mileageEdit);
    formLayout->addRow("Fuel Price (Rs./litre):", priceEdit);
    formLayout->addRow("Average Speed (km/h):", speedEdit);

    QHBoxLayout *formCenter = new QHBoxLayout();
    formCenter->setContentsMargins(0, 0, 0, 0);
    formCenter->addStretch();
    formCenter->addWidget(formContainer);
    formCenter->addStretch();
    mainLayout->addLayout(formCenter);

    mainLayout->addSpacing(12);

    // Five compact buttons, arranged exactly as in the report screenshots.
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(7);

    calculateBtn = new QPushButton("Calculate Trip", this);
    saveBtn = new QPushButton("Save Trip", this);
    viewBtn = new QPushButton("View Saved Trips", this);
    clearBtn = new QPushButton("Clear", this);
    exitBtn = new QPushButton("Exit", this);

    calculateBtn->setMinimumHeight(24);
    saveBtn->setMinimumHeight(24);
    viewBtn->setMinimumHeight(24);
    clearBtn->setMinimumHeight(24);
    exitBtn->setMinimumHeight(24);

    buttonLayout->addWidget(calculateBtn);
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(viewBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addWidget(exitBtn);
    mainLayout->addLayout(buttonLayout);

    // Results area shown as the light grey rounded section in the report.
    QGroupBox *resultsBox = new QGroupBox("Calculation Results", this);
    resultsBox->setStyleSheet(
        "QGroupBox {"
        " background: #f2f2f2;"
        " color: #222222;"
        " border: 1px solid #d8d8d8;"
        " border-radius: 6px;"
        " margin-top: 7px;"
        " padding: 9px 10px 10px 10px;"
        "}"
        "QGroupBox::title {"
        " subcontrol-origin: margin;"
        " left: 2px;"
        " padding: 0 3px;"
        " color: #222222;"
        " font-size: 8pt;"
        "}"
        "QLabel { color: #222222; background: transparent; }"
    );

    QFormLayout *resultLayout = new QFormLayout(resultsBox);
    resultLayout->setContentsMargins(8, 8, 8, 6);
    resultLayout->setVerticalSpacing(2);
    resultLayout->setHorizontalSpacing(10);
    resultLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    resultDistanceLabel = new QLabel("-", this);
    resultFuelRequiredLabel = new QLabel("-", this);
    resultFuelCostLabel = new QLabel("-", this);
    resultTravelTimeLabel = new QLabel("-", this);

    resultDistanceLabel->setAlignment(Qt::AlignLeft);
    resultFuelRequiredLabel->setAlignment(Qt::AlignLeft);
    resultFuelCostLabel->setAlignment(Qt::AlignLeft);
    resultTravelTimeLabel->setAlignment(Qt::AlignLeft);

    resultLayout->addRow("Total Distance:", resultDistanceLabel);
    resultLayout->addRow("Fuel Required:", resultFuelRequiredLabel);
    resultLayout->addRow("Estimated Fuel Cost (Rs.):", resultFuelCostLabel);
    resultLayout->addRow("Estimated Travel Time:", resultTravelTimeLabel);

    mainLayout->addWidget(resultsBox);

    // The report screenshots were captured with a light desktop theme.
    // Force the main window to keep that same light appearance even when
    // Qt Creator/Windows is using a dark theme.
    setStyleSheet(
        "QMainWindow, QWidget { background: #ffffff; color: #222222; }"
        "QLineEdit, QComboBox { min-height: 20px; background: #ffffff; color: #222222; border: 1px solid #cfcfcf; border-radius: 4px; padding: 2px 4px; }"
        "QLineEdit:focus, QComboBox:focus { border: 1px solid #5aa9e6; }"
        "QPushButton { background: #eeeeee; color: #222222; border: 1px solid #d0d0d0; border-radius: 4px; padding: 2px 8px; }"
        "QPushButton:hover { background: #e5e5e5; }"
        "QLabel { color: #222222; background: transparent; font-size: 8pt; }"
        "QComboBox { padding-left: 3px; }"
    );

    connect(calculateBtn, &QPushButton::clicked,
            this, &MainWindow::onCalculateClicked);
    connect(saveBtn, &QPushButton::clicked,
            this, &MainWindow::onSaveClicked);
    connect(viewBtn, &QPushButton::clicked,
            this, &MainWindow::onViewClicked);
    connect(clearBtn, &QPushButton::clicked,
            this, &MainWindow::onClearClicked);
    connect(exitBtn, &QPushButton::clicked,
            this, &MainWindow::close);

    connect(vehicleTypeCombo,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onVehicleTypeChanged);

    setWindowTitle("Road Trip Planner (India)");
    resize(600, 480);
}

bool MainWindow::validateInputs()
{
    if (sourceEdit->text().isEmpty() ||
        destEdit->text().isEmpty() ||
        distanceEdit->text().isEmpty() ||
        mileageEdit->text().isEmpty() ||
        priceEdit->text().isEmpty() ||
        speedEdit->text().isEmpty()) {

        QMessageBox::warning(this, "Validation Error",
                             "All fields are required.");
        return false;
    }

    return true;
}

void MainWindow::onCalculateClicked()
{
    if (!validateInputs())
        return;

    double dist = distanceEdit->text().toDouble();
    double mil = mileageEdit->text().toDouble();
    double price = priceEdit->text().toDouble();
    double speed = speedEdit->text().toDouble();

    if (mil <= 0.0 || speed <= 0.0) {
        QMessageBox::warning(this, "Validation Error",
                             "Mileage and average speed must be greater than zero.");
        return;
    }

    double fuelRequired = dist / mil;
    double fuelCost = fuelRequired * price;
    double travelTime = dist / speed;

    resultDistanceLabel->setText(QString::number(dist, 'f', 2) + " km");
    resultFuelRequiredLabel->setText(QString::number(fuelRequired, 'f', 2) + " litres");
    resultFuelCostLabel->setText("Rs. " + QString::number(fuelCost, 'f', 2));
    resultTravelTimeLabel->setText(QString::number(travelTime, 'f', 2) + " hours");

    hasCalculated = true;
}

void MainWindow::onSaveClicked()
{
    if (!hasCalculated) {
        QMessageBox::warning(this, "Error",
                             "Please calculate trip before saving.");
        return;
    }

    Trip trip(
        sourceEdit->text().toStdString(),
        destEdit->text().toStdString(),
        distanceEdit->text().toDouble(),
        mileageEdit->text().toDouble(),
        priceEdit->text().toDouble(),
        speedEdit->text().toDouble(),
        vehicleTypeCombo->currentText().toStdString()
    );

    if (FileManager::saveTrip("trips.txt", trip)) {
        QMessageBox::information(this, "Trip Saved",
                                 "Successfully saved trip details\nto trips.txt!");
    } else {
        QMessageBox::critical(this, "Error",
                              "Failed to save trip.");
    }
}

void MainWindow::onViewClicked()
{
    QDialog *viewDialog = new QDialog(this);
    viewDialog->setWindowTitle("Saved Road Trips History");
    viewDialog->resize(500, 400);

    QVBoxLayout *layout = new QVBoxLayout(viewDialog);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    QTextEdit *historyText = new QTextEdit(viewDialog);
    historyText->setReadOnly(true);

    QString trips =
        QString::fromStdString(FileManager::loadTrips("trips.txt"));

    if (trips.trimmed().isEmpty())
        trips = "No saved trips found.";

    historyText->setPlainText(trips);
    layout->addWidget(historyText);

    QHBoxLayout *historyButtons = new QHBoxLayout();
    QPushButton *clearHistoryBtn = new QPushButton("Clear History", viewDialog);
    QPushButton *closeBtn = new QPushButton("Close", viewDialog);
    historyButtons->addStretch();
    historyButtons->addWidget(clearHistoryBtn);
    historyButtons->addWidget(closeBtn);
    layout->addLayout(historyButtons);

    connect(clearHistoryBtn, &QPushButton::clicked, viewDialog, [viewDialog, historyText]() {
        FileManager::clearTrips("trips.txt");
        historyText->clear();
        historyText->setPlainText("No saved trips found.");
    });

    connect(closeBtn, &QPushButton::clicked,
            viewDialog, &QDialog::accept);

    viewDialog->exec();
}

void MainWindow::onClearClicked()
{
    sourceEdit->clear();
    destEdit->clear();
    distanceEdit->clear();
    mileageEdit->clear();
    priceEdit->clear();
    speedEdit->clear();

    resultDistanceLabel->setText("-");
    resultFuelRequiredLabel->setText("-");
    resultFuelCostLabel->setText("-");
    resultTravelTimeLabel->setText("-");

    hasCalculated = false;
}

void MainWindow::onVehicleTypeChanged(int index)
{
    if (index == 0)
        mileageEdit->setText("40.0");
    else if (index == 1)
        mileageEdit->setText("15.0");
    // The report does not specify an automatic SUV mileage value, so it is
    // intentionally left editable rather than inventing one.
}
