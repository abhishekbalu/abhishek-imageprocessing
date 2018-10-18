#include<QtGui>
#include "BuoyGui.h"


BuoyGui::BuoyGui(QWidget *parent)
    :QDialog(parent)
{
    imgLabel=new QLabel();
    imgSrc=new QLabel();
    close=new QPushButton(tr("Close"));
    close->setEnabled(true);
    canny=new QCheckBox(tr("Canny"));
    cannys=new QComboBox;
    check_split_rgb=new QCheckBox(tr("Split_RGB"));
    check_canny_r=new QCheckBox(tr("Canny_R"));
    check_canny_g=new QCheckBox(tr("Canny_G"));
    check_canny_b=new QCheckBox(tr("Canny_B"));

    connect(canny,SIGNAL(stateChanged(int)),this,SLOT(cannyChecked()));


    QHBoxLayout *images=new QHBoxLayout;
    images->addWidget(imgSrc);
    images->addWidget(imgLabel);

    QVBoxLayout *settings=new QVBoxLayout;
    settings->addWidget(canny);
    settings->addWidget(cannys);
    settings->addWidget(check_split_rgb);
    settings->addWidget(check_canny_r);
    settings->addWidget(check_canny_g);
    settings->addWidget(check_canny_b);


    settings->addStretch();

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->addLayout(images);
    mainLayout->addLayout(settings);

    setLayout(mainLayout);
    setWindowTitle("Buoy Task SRMAUV");





}

void BuoyGui::updateQImage(QImage *newimage,QImage *src){

    imgSrc->setPixmap(QPixmap::fromImage(*src));
    imgLabel->setPixmap(QPixmap::fromImage(*newimage));

}
/*
void BuoyGui::settingsSetter(filters *tempFilter){
    myFilter=tempFilter;

}
*/
void BuoyGui::cannyChecked(){
   // myFilter->canny=!(myFilter->canny);
}
