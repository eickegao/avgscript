#ifndef _IDRIVER_H_
#define _IDRIVER_H_
#include "math_compatible.h"
#include "datatype.h"
#include <vector>
using namespace std;

/**
 *  ͼ����ʾ�ӿڣ��˽ӿ���һ�������࣬��2������ֱ��Ӧ2��ƽ̨��
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
	virtual void BeginScene(int flag = 1) = 0;
      
      /**
       * ��ʾ�������������е���ʾ������������BeginScene()��EndScene()֮�䡣
       * �������ύ��ʾ��ˢ����ʾ��
       * @return �޷���ֵ. 
       */
	virtual void EndScene() = 0;
      
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
	virtual void RenderQuad(CTexture* texture,float sx,float sy,float sw,float sh,float dx,float dy,
				float xscale = 1.0,float yscale = 1.0,float angle = 0.0,int color=0xffffffff) = 0;
      /**
       * 2dͼ����ʾ�������ṩ�˻�ɫ���ܡ�������ʾ2dͼƬ��
       * �����RenderQuad()�ļ򻯰�.
       * @param texture CTexture*, ��ͼ����غ���LoadTexture()�õ���CTexture*.
       * @param dx      float,����ʾ����Ļ��x����.
       * @param dy      float,����ʾ����Ļ��y����.
       * @see �����Ҫ��ת�����ţ���ɫ����RenderQuad().
       * @return �޷���ֵ. 
       */		
	virtual void RenderQuadFast(CTexture* texture,float dx,float dy) = 0;
      
      /**
       * ������������ɫֵ���ú�RGBA(r,g,b,a)���������ɫֵ��
       * @param color int,��������ɫֵ��
       */
       virtual void SetClearColor(int color){	m_clrcolor = color;};
      
      /**
       * ��ȡ��������ɫֵ��
       * @return ��ɫֵ. 
       */
       virtual int GetClearColor(){  return m_clrcolor; }; 
      
      /**
       * ���Ժ�������ʼ��fps������
       * @return �޷���ֵ. 
       */
       virtual void FpsInit() = 0;
      
      /**
       * ���Ժ�����������ʾ��ǰ��fps����Ҫ����FpsInit()��ʼ������Ȼ��õ�������.
       * @return �޷���ֵ. 
       */
       virtual void ShowFps() = 0; 	
protected:
	int m_clrcolor;
private:
};


#endif
