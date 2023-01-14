#include <vector>
#include <cmath>
#include "tgaimage.h"   //tga��ͼ��
#include "model.h"      //ģ���࣬��Ҫʵ��ģ�͵Ķ�ȡ
#include "geometry.h"   //���ο⣬��Ҫ������Vec2��Vec3����

//������ɫ
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
//������ȸ߶�
const int width  = 800;
const int height = 800;

//�����㷨(����1������2��tgaĿ��ָ�룬ָ����ɫ)
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    //�ж��߶�б�ʵľ���ֵ�Ƿ����1
    bool steep = false;
    //����1��Ϊtrue������������Ե�x��y�����任Ϊ����y=x��y=-x�ԳƵĵ�
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    //��֤����2��x,y��������1��x,y��
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    //��ʱx1����x0����б����-1��1֮�䣬��x��ѭ�����Ʊ���
    for (int x=x0; x<=x1; x++) {
        //����x�����߶ζ�Ӧ��y
        float t = (x-x0)/(float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        //��б�ʴ���1����ʵ����Ϊ(y,x)������Ϊ(x,y)
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

int main(int argc, char** argv) {
    //�����п��Ʒ�ʽ�ʹ��뷽ʽ����model
    //����ģ��(obj�ļ�·��)
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }
    //����tga(�����ߣ�ָ����ɫ�ռ�)
    TGAImage image(width, height, TGAImage::RGB);
    //ģ�͵�����Ϊѭ�����Ʊ���
    for (int i=0; i<model->nfaces(); i++) {
        //����face�������ڱ���һ��face��������������
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            //����v0
            Vec3f v0 = model->vert(face[j]);
   
            Vec3f v1 = model->vert(face[(j+1)%3]);
    
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            //����
            line(x0,y0, x1,y1, image, white);
        }
    }

    //tgaĬ��ԭ�������Ͻǣ�����Ҫָ��Ϊ���½ǣ����Խ�����ֱ��ת
    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}

