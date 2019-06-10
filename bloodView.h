#ifndef __bloodView_H__
#define __bloodView_H__

#include "cocos2d.h"

class bloodView : public cocos2d::Node
{
public:
	bloodView();

public:
	//����Ѫ������
	void setBackgroundTexture(const char *pName);
	//����Ѫ��ǰ��
	void setForegroundTexture(const char *pName);
	//������Ѫ��
	void setTotalBlood(float total);
	//���õ�ǰѪ��
	void setCurrentBlood(float progress);
	//�õ���ǰѪ��
	float getCurrentBlood() const;
	//�õ���Ѫ��
	float getTotalBlood() const;

private:
	//����ǰ��Ѫ����ʾ�ĳ���
	void setForegroundTextureRect(const cocos2d::Rect &rect);

private:
	cocos2d::Sprite *m_bloodBackground;//����Ѫ��
	cocos2d::Sprite *m_bloodForeground;//ǰ��Ѫ��
	float m_totalBlood;//��Ѫ��
	float m_currentBlood;//��ǰѪ��
	float m_scale;//�Ŵ���
};
#endif