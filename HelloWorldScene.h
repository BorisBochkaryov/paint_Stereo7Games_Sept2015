#ifndef __MAINWINDOW_SCENE_H__
#define __MAINWINDOW_SCENE_H__

#include "cocos2d.h"
#include "ui/UIEditBox/UIEditBox.h"
#include <vector>

class MainWindow : public cocos2d::CCLayerColor, public cocos2d::ui::EditBoxDelegate
{
public:
    virtual bool init() override;
    static cocos2d::Scene* scene();
	void menuCloseCallback(Ref* sender);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)override;
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)override;
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)override;
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox)override;

	cocos2d::ui::EditBox* _size;
	std::vector<cocos2d::ui::EditBox*> color;
	std::vector<cocos2d::CCLabelTTF*> labels;
	int statusDraw = 0;
	float r = 0,g = 0,b = 0,s = 4;
	int x,y;
	cocos2d::DrawNode* draw;
	CREATE_FUNC(MainWindow);
};

#endif // __MAINWINDOW_SCENE_H__
