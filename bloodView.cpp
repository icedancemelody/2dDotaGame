#include "bloodView.h"

USING_NS_CC;

bloodView::bloodView()//��ʼ����Ա����
	:m_bloodBackground(NULL)
	,m_bloodForeground(NULL)
	,m_totalBlood(0.0f)
	,m_currentBlood(0.0f)
	,m_scale(1.0f)
{
	}

void bloodView::setBackgroundTexture(const char *pName) {//����Ѫ����������
	m_bloodBackground = Sprite::create(pName);
	this->addChild(m_bloodBackground);
}

void bloodView::setForegroundTexture(const char *pName) {//����Ѫ����������
	m_bloodForeground = Sprite::create(pName);
	m_bloodForeground->setAnchorPoint(Vec2(0.0f, 0.5f));//����ê��
	m_bloodForeground->setPosition(Vec2(-m_bloodForeground->getContentSize().width*0.5f, 0));
	this->addChild(m_bloodForeground);
}

void bloodView::setTotalBlood(float total) {
	if (m_bloodBackground == NULL) {return;}
	m_scale = m_bloodForeground->getContentSize().width / total;//ÿ��Ѫ������
	m_totalBlood = total;
}

void bloodView::setCurrentBlood(float progress) {
	if (m_bloodForeground == NULL) { return; }
	if (progress < 0.0f) { progress = 0.0f; }
	if (progress > m_totalBlood) { progress = m_totalBlood; }
	m_currentBlood = progress;
	float rectWidth = progress * m_scale;//��ǰѪ��*ÿ��Ѫ������
	const Vec2 from = m_bloodForeground->getTextureRect().origin;
	const Rect rect = Rect(from.x, from.y, rectWidth, m_bloodForeground->getContentSize().height);//���õ�ǰѪ��
	setForegroundTextureRect(rect);
}

void bloodView::setForegroundTextureRect(const cocos2d::Rect &rect) {//���ó���
	m_bloodForeground->setTextureRect(rect);
}

float bloodView::getCurrentBlood() const//�õ���ǰѪ��
{
	return m_currentBlood;
}

float bloodView::getTotalBlood() const//�õ���Ѫ��
{
	return m_totalBlood;
}


