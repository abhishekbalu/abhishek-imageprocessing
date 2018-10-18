#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCore>
#include<QtGui>
#include "structures.h"


//#include<uavGui.h>






namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow

{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setImageLabels(QImage*,QImage*);
    void passFilters(filters*);
    void passFlips(switches*);
    filters *myFilters;
    switches *myFlip;
    
private slots:
    void on_actionAbout_triggered();

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_radioButton_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_checkBox_5_toggled(bool checked);

    void on_checkBox_9_toggled(bool checked);

    void on_checkBox_8_toggled(bool checked);

    void on_checkBox_7_toggled(bool checked);

    void on_YellowHSV_toggled(bool checked);

    void setLowerH(int lH);
    void setLowerV(int lV);
    void setLowerS(int lS);

    void setUpperH(int uH);
    void setUpperS(int uS);
    void setUpperV(int uV);

    void on_GreenHSV_toggled(bool checked);


    void on_RedHSV_toggled(bool checked);

    //void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    QLabel *imgSrc,*imgDest;
    int lowerH,lowerS,lowerV;
    int upperH,upperS,upperV;
    bool yellow_checked,red_checked,green_checked;



};

#endif // MAINWINDOW_H
