#include "tgaimage.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,  0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (float t=0.; t<1.; t+=.1) {
        int x = x0*(1.-t) + x1*t;
        int y = y0*(1.-t) + y1*t;
        image.set(x, y, color);
    }
}

int main()
{
    TGAImage image(6,6,TGAImage::RGB);
    //四个角出现颜色
    // image.set(0,0,red);
    // image.set(5,5,white);
    // image.set(0,5,blue);
    // image.set(5,0,green);
    for (int i =0;i<6;i++)
    {
        for(int j =0;j<6;j++)
        {
            if ((i + j) & 1) {
                image.set(i, j, green);
            } else {
                image.set(i, j, white);
            }
        }
    }
    image.flip_horizontally();


    image.write_tga_file("output.tga");
    return 0;

}




/*
int main() {
    TGAImage image(200, 200, TGAImage::RGB);
    line(13, 20, 80, 40, image, red);
    image.flip_vertically();
    // image.flip_horizontally();
    image.write_tga_file("output.tga");
    return 0;
}
*/

