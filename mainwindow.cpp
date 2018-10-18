#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  ui->label->setPixmap();
    ui->canny_group->setEnabled(false);
    //ui->textEdit->append("Hello");
    ui->horizontalSlider->setRange(0,180);
    ui->horizontalSlider_2->setRange(0,255);
    ui->horizontalSlider_3->setRange(0,255);
    ui->horizontalSlider_4->setRange(0,180);
    ui->horizontalSlider_5->setRange(0,255);
    ui->horizontalSlider_6->setRange(0,255);
    ui->spinBox->setRange(0,180);
    ui->spinBox_2->setRange(0,255);
    ui->spinBox_3->setRange(0,255);
    ui->spinBox_4->setRange(0,180);
    ui->spinBox_5->setRange(0,255);
    ui->spinBox_6->setRange(0,255);

    //if(myFilters->do_thresh_yellow)
    // ui->checkBox_7->setChecked(true);



    yellow_checked=false;
    green_checked=false;
    red_checked=false;



}

MainWindow::~MainWindow()
{
myFlip->quit=true;
    delete ui;

}

void MainWindow::setImageLabels(QImage *src,QImage *dest){
    ui->label->setPixmap(QPixmap::fromImage(*src));
    ui->label_2->setPixmap(QPixmap::fromImage(*dest));

    ui->textBrowser->setText(QString::number(myFilters->fps));





}

void MainWindow::setLowerH(int lH){
    if(yellow_checked)
myFilters->yellow.lowerH=lH;
    else if(red_checked)
        myFilters->red.lowerH=lH;
    else if(green_checked)
        myFilters->green.lowerH=lH;

}

void MainWindow::setLowerS(int lS){
    if(yellow_checked)
myFilters->yellow.lowerS=lS;
    else if(red_checked)
        myFilters->red.lowerS=lS;
    else if(green_checked)
        myFilters->green.lowerS=lS;
}

void MainWindow::setLowerV(int lV){
    if(yellow_checked)
        myFilters->yellow.lowerV=lV;
    else if(red_checked)
        myFilters->red.lowerV=lV;
    else if(green_checked)
        myFilters->green.lowerV=lV;
}

void MainWindow::setUpperH(int uH){
    if(yellow_checked)
        myFilters->yellow.upperH=uH;
    else if(red_checked)
        myFilters->red.upperH=uH;
    else if(green_checked)
        myFilters->green.upperH=uH;
}


void MainWindow::setUpperS(int uS){
    if(yellow_checked)
        myFilters->yellow.upperS=uS;
    else if(red_checked)
        myFilters->red.upperS=uS;
    else if(green_checked)
        myFilters->green.upperS=uS;
}

void MainWindow::setUpperV(int uV){
    if(yellow_checked)
        myFilters->yellow.upperV=uV;
    else if(red_checked)
        myFilters->red.upperV=uV;
    else if(green_checked)
        myFilters->green.upperV=uV;
}


void MainWindow::passFilters(filters* local_filters){
    myFilters=local_filters;
}

void MainWindow::passFlips(switches * local_flip){
    myFlip=local_flip;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"uav","uav Vision Debugging Suite <Version 1.0.1> \n For any technical assitance contact abhishek");
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    myFilters->createCam=!(myFilters->createCam);

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
   // qDebug()<<QString::number(arg1);
    if(arg1){
        ui->canny_group->setEnabled(true);

    }
    else{
        ui->canny_group->setEnabled(false);
        myFilters->do_canny_b=false;
        myFilters->do_canny_binary=false;
        myFilters->do_canny_g=false;
        myFilters->do_canny_r=false;
        myFilters->do_canny_src=false;

    }




}


void MainWindow::on_radioButton_clicked()
{

}

void MainWindow::on_radioButton_toggled(bool checked)
{
    //do canny red

    if(checked)
        myFilters->do_canny_r=true;
    else
        myFilters->do_canny_r=false;
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    //do canny green
    if(checked)
        myFilters->do_canny_g=true;
    else
        myFilters->do_canny_g=false;

}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    //do canny blue
    if(checked)
        myFilters->do_canny_b=true;
    else
        myFilters->do_canny_b=false;

}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    //do canny src
    if(checked)
        myFilters->do_canny_src=true;
    else
        myFilters->do_canny_src=false;
}

void MainWindow::on_radioButton_5_toggled(bool checked)
{
    //do canny binary
    if(checked)
        myFilters->do_canny_binary=true;
    else
        myFilters->do_canny_binary=false;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

    myFlip->show_orig=false;
    myFlip->show_canny=false;
    myFlip->show_thresh_green=false;
    myFlip->show_thresh_red=false;
    myFlip->show_thresh_yellow=false;
    myFlip->show_b=false;
    myFlip->show_g=false;
    myFlip->show_r=false;
    myFlip->show_thresh_flat=false;


    if(arg1=="Canny")
        myFlip->show_canny=true;
    else if(arg1=="Tracked uavs")
        myFlip->show_orig=true;
    else if (arg1=="Thresh_Red")
        myFlip->show_thresh_red=true;
    else if(arg1=="Thresh_Green")
        myFlip->show_thresh_green=true;
    else if (arg1=="Thresh_Yellow")
        myFlip->show_thresh_yellow=true;
    else if(arg1=="R")\
        myFlip->show_r=true;
    else if(arg1=="G")
        myFlip->show_g=true;
    else if(arg1=="B")
        myFlip->show_b=true;
    else if (arg1=="Thresh_Flat")
        myFlip->show_thresh_flat=true;







}

void MainWindow::on_checkBox_5_toggled(bool checked)
{
    if(checked)
        myFilters->do_circular_hough=true;
    else
        myFilters->do_circular_hough=false;
}

void MainWindow::on_checkBox_9_toggled(bool checked)
{
    //red img thresholding
    if(checked)
        myFilters->do_thresh_red=true;
    else
        myFilters->do_thresh_red=false;
}

void MainWindow::on_checkBox_8_toggled(bool checked)
{
    //green img thresholding
    if(checked)
        myFilters->do_thresh_green=true;
    else
        myFilters->do_thresh_green=false;
}



void MainWindow::on_checkBox_7_toggled(bool checked)
{
    //yellow img thresholding
    if(checked)
        myFilters->do_thresh_yellow=true;
    else
        myFilters->do_thresh_yellow=false;
   // qDebug()<<checked;


}

void MainWindow::on_YellowHSV_toggled(bool checked)
{
    if(checked){
        yellow_checked=true;
    ui->LowerHSV->setEnabled(true);
    ui->UpperHSV->setEnabled(true);


    ui->horizontalSlider->setValue(myFilters->yellow.lowerH);
    ui->horizontalSlider_2->setValue(myFilters->yellow.lowerS);
    ui->horizontalSlider_3->setValue(myFilters->yellow.lowerV);
    ui->horizontalSlider_4->setValue(myFilters->yellow.upperH);
    ui->horizontalSlider_5->setValue(myFilters->yellow.upperS);
    ui->horizontalSlider_6->setValue(myFilters->yellow.upperV);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(setLowerS(int)));
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(setLowerV(int)));
    connect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(setUpperH(int)));
    connect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(setUpperS(int)));
    connect(ui->horizontalSlider_6,SIGNAL(valueChanged(int)),this,SLOT(setUpperV(int)));
}

    else{
    yellow_checked=false;
    disconnect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));
    disconnect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(setLowerS(int)));
    disconnect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(setLowerV(int)));
    disconnect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(setUpperH(int)));
    disconnect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(setUpperS(int)));
    disconnect(ui->horizontalSlider_6,SIGNAL(valueChanged(int)),this,SLOT(setUpperV(int)));
    }

   // connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));

}

void MainWindow::on_GreenHSV_toggled(bool checked)
{

    if(checked){

        green_checked=true;
    ui->LowerHSV->setEnabled(true);
    ui->UpperHSV->setEnabled(true);


    ui->horizontalSlider->setValue(myFilters->green.lowerH);
    ui->horizontalSlider_2->setValue(myFilters->green.lowerS);
    ui->horizontalSlider_3->setValue(myFilters->green.lowerV);
    ui->horizontalSlider_4->setValue(myFilters->green.upperH);
    ui->horizontalSlider_5->setValue(myFilters->green.upperS);
    ui->horizontalSlider_6->setValue(myFilters->green.upperV);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(setLowerS(int)));
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(setLowerV(int)));
    connect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(setUpperH(int)));
    connect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(setUpperS(int)));
    connect(ui->horizontalSlider_6,SIGNAL(valueChanged(int)),this,SLOT(setUpperV(int)));


}
    else{
    green_checked=false;
    disconnect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));
    disconnect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(setLowerS(int)));
    disconnect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(setLowerV(int)));
    disconnect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(setUpperH(int)));
    disconnect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(setUpperS(int)));
    disconnect(ui->horizontalSlider_6,SIGNAL(valueChanged(int)),this,SLOT(setUpperV(int)));
    }

}


void MainWindow::on_RedHSV_toggled(bool checked)
{
    if(checked){

        red_checked=true;
    ui->LowerHSV->setEnabled(true);
    ui->UpperHSV->setEnabled(true);


    ui->horizontalSlider->setValue(myFilters->red.lowerH);
    ui->horizontalSlider_2->setValue(myFilters->red.lowerS);
    ui->horizontalSlider_3->setValue(myFilters->red.lowerV);
    ui->horizontalSlider_4->setValue(myFilters->red.upperH);
    ui->horizontalSlider_5->setValue(myFilters->red.upperS);
    ui->horizontalSlider_6->setValue(myFilters->red.upperV);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(setLowerS(int)));
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(setLowerV(int)));
    connect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(setUpperH(int)));
    connect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(setUpperS(int)));
    connect(ui->horizontalSlider_6,SIGNAL(valueChanged(int)),this,SLOT(setUpperV(int)));


}
    else{
    red_checked=false;
    disconnect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setLowerH(int)));
    disconnect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(setLowerS(int)));
    disconnect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),this,SLOT(setLowerV(int)));
    disconnect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),this,SLOT(setUpperH(int)));
    disconnect(ui->horizontalSlider_5,SIGNAL(valueChanged(int)),this,SLOT(setUpperS(int)));
    disconnect(ui->horizontalSlider_6,SIGNAL(valueChanged(int)),this,SLOT(setUpperV(int)));
    }


}
