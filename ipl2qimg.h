#ifndef IPL2QIMG_H
#define IPL2QIMG_H

#endif // IPL2QIMG_H
void  IplImage22QImage(IplImage* iplImg,QImage *qimg)
{
int h = iplImg->height;
int w = iplImg->width;
int channels = iplImg->nChannels;
QImage *qimg1 = new QImage(w, h, QImage::Format_ARGB32);
char *data = iplImg->imageData;

for (int y = 0; y < h; y++, data += iplImg->widthStep)
{
for (int x = 0; x < w; x++)
{
char r, g, b, a = 0;
if (channels == 1)
{
r = data[x * channels];
g = data[x * channels];
b = data[x * channels];
}
else if (channels == 3 || channels == 4)
{
r = data[x * channels + 2];
g = data[x * channels + 1];
b = data[x * channels];
}

if (channels == 4)
{
a = data[x * channels + 3];
qimg1->setPixel(x, y, qRgba(r, g, b, a));
}
else
{
qimg1->setPixel(x, y, qRgb(r, g, b));
}
}
}
//return qimg;
*qimg=*qimg1;
delete(qimg1);

}
