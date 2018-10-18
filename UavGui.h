#ifndef BUOYGUI_H
#define BUOYGUI_H

#endif // BUOYGUI_H

#include <QDialog>
#include <QComboBox>


using namespace std;

/*typedef struct filters{
    char imgThresh;
    char cannySrc; //'R'/'G'/'B'/'F'
    char HSV;
    bool canny;

    bool do_canny_r;
    bool do_canny_g;
    bool do_canny_b;

    bool do_split_rgb;
    bool createCam;



};

*/
class QCheckBox;
class QLabel;
class QPushButton;

class BuoyGui:public QDialog{
    Q_OBJECT
public:
    BuoyGui(QWidget*parent=0);
    void updateQImage(QImage*,QImage*);
  //  filters* myFilter;
  //  void settingsSetter(filters*);


private slots:
    void cannyChecked();


 private:

    QLabel *imgLabel;
    QLabel *imgSrc;
    QPushButton *close;
    QCheckBox *canny;
    QCheckBox *check_split_rgb;
    QCheckBox *check_canny_r;
    QCheckBox *check_canny_g;
    QCheckBox *check_canny_b;

    QComboBox *cannys;

    QImage qimg;

};

