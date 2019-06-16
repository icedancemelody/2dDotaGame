#include "bloodView.h"

USING_NS_CC;

bloodView::bloodView()//初始化成员变量
	:m_bloodBackground(NULL)
	,m_bloodForeground(NULL)
	,m_totalBlood(0.0f)
	,m_currentBlood(0.0f)
	,m_scale(1.0f)
{
	}

void bloodView::setBackgroundTexture(const char *pName) {//创建血条背景精灵
	m_bloodBackground = Sprite::create(pName);
	this->addChild(m_bloodBackground);
}

void bloodView::setForegroundTexture(const char *pName) {//创建血条背景精灵
	m_bloodForeground = Sprite::create(pName);
	m_bloodForeground->setAnchorPoint(Vec2(0.0f, 0.5f));//设置锚点
	m_bloodForeground->setPosition(Vec2(-m_bloodForeground->getContentSize().width*0.5f, 0));
	this->addChild(m_bloodForeground);
}

void bloodView::setTotalBlood(float total) {
	if (m_bloodBackground == NULL) {return;}
	m_scale = m_bloodForeground->getContentSize().width / total;//每格血量长度
	m_totalBlood = total;
}

void bloodView::setCurrentBlood(float progress) {
	if (m_bloodForeground == NULL) { return; }
	if (progress < 0.0f) { progress = 0.0f; }
	if (progress > m_totalBlood) { progress = m_totalBlood; }
	m_currentBlood = progress;
	float rectWidth = progress * m_scale;//当前血量*每格血量长度
	const Vec2 from = m_bloodForeground->getTextureRect().origin;
	const Rect rect = Rect(from.x, from.y, rectWidth, m_bloodForeground->getContentSize().height);//设置当前血量
	setForegroundTextureRect(rect);
}

void bloodView::setForegroundTextureRect(const cocos2d::Rect &rect) {//设置长度
	m_bloodForeground->setTextureRect(rect);
}

float bloodView::getCurrentBlood() const//得到当前血量
{
	return m_currentBlood;
}

float bloodView::getTotalBlood() const//得到总血量
{
	return m_totalBlood;
}


