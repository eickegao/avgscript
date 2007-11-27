#ifndef _IDRIVER_OGL_H_
#define _IDRIVER_OGL_H_
#include <gl/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include "math_compatible.h"
#include "datatype.h"

/**
 *  ͼ����ʾ�ӿڣ���2��ʵ�ֱַ��Ӧ2��ƽ̨���˴���������Ϊ�˱����麯���Ŀ�����
 */
class IVideoDriver
{
public:
      IVideoDriver(){ m_clrcolor = 0xff000000; };
      /**
       * ��ʾ��ʼ���������е���ʾ������������BeginScene()��EndScene()֮�䡣
       * ������������һЩ��ʼ��������Ĭ�����ú�ɫ0xff000000������������
       * SetClearColor()�ı�Ĭ��������ɫ��
       * @param flag int,�Ƿ������ı��£�Ĭ��Ϊtrue��
       * @return �޷���ֵ. 
       */
	void BeginScene(int flag = 1);
      
      /**
       * ��ʾ�������������е���ʾ������������BeginScene()��EndScene()֮�䡣
       * �������ύ��ʾ��ˢ����ʾ��
       * @return �޷���ֵ. 
       */
	void EndScene();
      
      /**
       * 2dͼ����ʾ�������ṩ����ת�����ţ���ɫ���ܡ�������ʾ2dͼƬ��
       * @param texture CTexture*, ��ͼ����غ���LoadTexture()�õ���CTexture*.
       * @param sx      float,x(left)   ��Ҫ��ʾͼƬ���ֵ�x����.Ĭ����ԭͼ����ͬ������4��������
       *                Ϊ��ֻ��ʾͼƬ�ϵ�ĳһ���ֶ����õġ�
       * @param sy      float,y(top)    ��Ҫ��ʾͼƬ���ֵ�y����.
       * @param sw      float,w(right)  ��Ҫ��ʾͼƬ���ֵĿ�.
       * @param sh      float,h(bottom) ��Ҫ��ʾͼƬ���ֵĸ�.
       * @param dx      float,����ʾ����Ļ��x����.
       * @param dy      float,����ʾ����Ļ��y����.
       * @param xscale  float,x��ˮƽ�����������ű���.Ĭ��Ϊ����1.0���������š�
       * @param yscale  float,y����ֱ�����������ű���.Ĭ��Ϊ����1.0���������š�
       * @param angle   float,��ת�Ƕ���������ʱ�룬������˳ʱ�뷽��,��ת������CTexture��rcentrex��rcentreyָ����
       *		����ת������ת����Ƕȣ�Ĭ����ת������ͼƬ�����ģ�����ͨ������rcentrex��rcentrey
       *		���ı������ת���ġ�Ĭ�ϲ�����0��
       * @param color   int,��ɫ����ɫ��������ͼƬ��alpha��ϡ��ú�RGBA(r,g,b,a)�����������ɫ
       *                ���RGBA(r,g,b,a)�е�aֵΪ0��ôͼƬΪ͸��.Ĭ�ϲ�������ʾԭͼ��
       *                ����Ҫ��ͼƬ��͸����ʾ��������RGBA(0xff,0xff,0xff,0x7f)����ʾԭͼ����RGBA(0xff,0xff,0xff,0xff)��
       * @return �޷���ֵ.
       * @see ��RenderQuadFast()��������ʾԭͼ���������Ҫ���ź���ת�Ļ�,����һ�����ٶ�������
       */
	void RenderQuad(CTexture* texture,float sx,float sy,float sw,float sh,float dx,float dy,
				float xscale = 1.0,float yscale = 1.0,float angle = 0.0,int color=0xffffffff);
      /**
       * 2dͼ����ʾ�������ṩ�˻�ɫ���ܡ�������ʾ2dͼƬ��
       * �����RenderQuad()�ļ򻯰�.
       * @param texture CTexture*, ��ͼ����غ���LoadTexture()�õ���CTexture*.
       * @param dx      float,����ʾ����Ļ��x����.
       * @param dy      float,����ʾ����Ļ��y����.
       * @see �����Ҫ��ת�����ţ���ɫ����RenderQuad().
       * @return �޷���ֵ. 
       */		
	void RenderQuadFast(CTexture* texture,float dx,float dy);
      
      /**
       * ������������ɫֵ���ú�RGBA(r,g,b,a)���������ɫֵ��
       * @param color int,��������ɫֵ��
       */
       void SetClearColor(int color){	m_clrcolor = color;};
      
      /**
       * ��ȡ��������ɫֵ��
       * @return ��ɫֵ. 
       */
       int GetClearColor(){  return m_clrcolor; }; 
      
      /**
       * ���Ժ�������ʼ��fps������
       * @return �޷���ֵ. 
       */
       void FpsInit() ;
      
      /**
       * ���Ժ�����������ʾ��ǰ��fps����Ҫ����FpsInit()��ʼ������Ȼ��õ�������.
       * @return �޷���ֵ. 
       */
       void ShowFps() ; 
       
       /**
        * ��ֱ�ߵĺ��������������4��floatֵ��
        * @param x1 float,ֱ�ߵ�һ�����x���ꡣ
        * @param y1 float,ֱ�ߵ�һ�����y���ꡣ
        * @param x2 float,ֱ�ߵڶ������x���ꡣ
        * @param y2 float,ֱ�ߵڶ������y���ꡣ
        * @param color int,ֱ�ߵ���ɫ���ú�RGBA���������ɫ��
        * @return �޷���ֵ��
        */
       void DrawLine(float x1, float y1, float x2, float y2, int color) ;
       
       /**
        * ��ֱ�ߵĺ��������������2��CPointf����ֵ��
        * @param p1 CPointf,ֱ�ߵ�һ��������ꡣ
        * @param p2 Cpointf,ֱ�ߵڶ���������ꡣ
        * @param color int,ֱ�ߵ���ɫ���ú�RGBA���������ɫ��
        * @return �޷���ֵ��
        */
       void DrawLine(Cpointf p1, Cpointf p2, int color) ;
      
       /**
        * �������߿�ĺ��������������4��floatֵ��
        * @param x float,������Ļ�ϵ�x���ꡣ
        * @param y float,������Ļ�ϵ�y���ꡣ
        * @param width float,�����߿�Ŀ�
        * @param height float,�����߿�ĸߡ�
        * @param color float,�߿���ɫ��
        * @return �޷���ֵ��
        */
       void  DrawRect(float x, float y, float width, float height,int color) ;
       
       /**
        * �������߿�ĺ��������������CRectfֵ��
        * @param rect CRectf,�����߿�Ĳ�����
        * @param color float,�߿���ɫ��
        * @return �޷���ֵ��
        */
       void DrawRect(CRectf rect,int color) ;
       
       /**
        * ��ʵ�ľ��εĺ��������������4��floatֵ��
        * @param x float,������Ļ�ϵ�x���ꡣ
        * @param y float,������Ļ�ϵ�y���ꡣ
        * @param width float,���εĿ�
        * @param height float,���εĸߡ�
        * @param color float,ʵ�ľ�����ɫ��
        * @return �޷���ֵ��
        */
       void  FillRect(float x, float y, float width, float height,int color) ;
       
       /**
        * ��ʵ�ľ��εĺ��������������CRectfֵ��
        * @param rect CRectf,���εĲ�����
        * @param color float,ʵ�ľ�����ɫ��
        * @return �޷���ֵ��
        */
       void FillRect(CRectf rect,int color) ;
       
	
private:
	int m_clrcolor;
	int m_update;
	int m_frame;
	int m_t0;
};


#endif
