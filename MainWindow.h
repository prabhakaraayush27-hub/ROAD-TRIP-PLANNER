#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <string>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalculateClicked();
    void onSaveClicked();
    void onViewClicked();
    void onClearClicked();
    void onVehicleTypeChanged(int index);

private:
    void setupUI();
    bool validateInputs();

    QLineEdit *sourceEdit;
    QLineEdit *destEdit;
    QLineEdit *distanceEdit;
    QLineEdit *mileageEdit;
    QLineEdit *priceEdit;
    QLineEdit *speedEdit;
    QComboBox *vehicleTypeCombo;

    QPushButton *calculateBtn;
    QPushButton *saveBtn;
    QPushButton *viewBtn;
    QPushButton *clearBtn;
    QPushButton *exitBtn;

    QLabel *resultDistanceLabel;
    QLabel *resultFuelRequiredLabel;
    QLabel *resultFuelCostLabel;
    QLabel *resultTravelTimeLabel;

    bool hasCalculated;
    std::string currentSource, currentDest;
};

#endif // MAINWINDOW_H
