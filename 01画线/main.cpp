#include "tgaimage.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0, 255,  0,   255);
const TGAColor blue  = TGAColor(0, 0,   255,   255);


/*
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (float t=0.; t<1.; t+=.1) {
        int x = x0*(1.-t) + x1*t;
        int y = y0*(1.-t) + y1*t;
        image.set(x, y, color);
    }
}
*/

void line(int x0, int y0, int x1, int y1, TGAColor color, TGAImage &image) {
    bool fg = false;
    if (1.0 * std::abs(y1-y0) / std::abs(x1-x0) > 1) {  // 如果斜率>1, 则根据y轴递增绘制线段, 否则线段不连续, 直接交换x,y轴, 并用fg记录下来
        std::swap(x0, y0);
        std::swap(x1, y1);
        fg = true;
    }
    if (x0 > x1) {  // 保证(x0, y0)在(x1, y1)的左侧
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    for (int x = x0; x <= x1; x++) {
        double t = 1.0 * (x - x0) / (x1 - x0);
        int y = t * y1 + (1-t) * y0;
        if (!fg) image.set(x, y, color);
        else image.set(y, x, color);  // 反转了x,y轴
    }
}
int main()
{
    TGAImage image(100, 100, TGAImage::RGB);
    line(0, 1, 99, 20, white, image);
    line(99, 21, 0, 40, red, image);
    line(99, 21, 90, 99, blue, image);
    line(99, 21, 0, 99, green, image);
    image.write_tga_file("output.tga");
    return 0;
}
    




/*
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

*/



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

