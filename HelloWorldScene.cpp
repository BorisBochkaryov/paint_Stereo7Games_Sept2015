#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d::ui;
Scene* MainWindow::scene()
{
    auto scene = Scene::create();
	MainWindow *layer = MainWindow::create();
	scene->addChild(layer);
	return scene;
}
bool MainWindow::onTouchBegan(Touch* touch, Event  *event)
{
	statusDraw = 1;
	auto e = touch->getLocation();
	x = e.x;
	y = e.y;
	return true;
}
void MainWindow::onTouchEnded(Touch* touch, Event  *event)
{
	statusDraw = 0;
	auto e = touch->getLocation();
	draw->drawSegment(Vec2(x, y), Vec2(e.x, e.y), s ? s : 3, Color4F(r > 1.0f && r < 0.0f ? 1.0 : r, g > 1.0f && g < 0.0f ? 1.0 : g, b > 1.0f && b < 0.0f ? 1.0 : b, 1.0));
}

void MainWindow::onTouchMoved(Touch* touch, Event* event){
	if(statusDraw == 1){
		auto e = touch->getLocation();
		// приведение значений к нормальным, в случае неправильного ввода пользователем
		r = r > 1.0f && r < 0.0f ? 1.0 : r;
		g = g > 1.0f && g < 0.0f ? 1.0 : g;
		b = b > 1.0f && b < 0.0f ? 1.0 : b;
		s = s ? s : 3;
		// рисуем между двумя точками
		draw->drawSegment(Vec2(x,y),Vec2(e.x,e.y),s,Color4F(r, g, b, 1.0));	
		
		//draw->drawSolidCircle(Vec2(x, y),s ? s : 3, 360, Vec2(e.x, e.y), Color4F::BLACK);
		//draw->drawDot(Vec2(x, y), s ? s : 3, Color4F::BLACK);
		//draw->setLineWidth(s ? s : 3);
		//draw->drawLine(Vec2(x, y), Vec2(e.x, e.y), Color4F::BLACK);
		
		x = e.x;
		y = e.y;
	}
}
bool MainWindow::init()
{
	if (CCLayerColor::initWithColor(Color4B(255, 255, 255, 255))){
		// объект для рисования
		draw = DrawNode::create();
		addChild(draw, 1);
		
		// слушатели нажатий
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(MainWindow::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(MainWindow::onTouchEnded, this);
		listener->onTouchMoved = CC_CALLBACK_2(MainWindow::onTouchMoved, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		
		// EditBox
		auto glview = Director::getInstance()->getOpenGLView();
		auto visibleOrigin = glview->getVisibleOrigin();
		auto visibleSize = glview->getVisibleSize();
		std::string pNormalSprite = "green_edit.png";
		std::string str[4] = { "R", "G", "B", "S" };
		for (int i = 0; i < 4; i++){
			// EditText
			EditBox* temp = EditBox::create(Size(38, 20), ui::Scale9Sprite::create(pNormalSprite));
			temp->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - (i + 1) * 20));
			temp->setFontName("Paint Boy");
			temp->setFontSize(20);
			temp->setFontColor(Color3B::BLACK);
			temp->setPlaceHolder(i == 3 ? "4" : "0");
			temp->setPlaceholderFontColor(Color3B::BLACK);
			temp->setMaxLength(3);
			temp->setReturnType(EditBox::KeyboardReturnType::DONE);
			temp->setDelegate(this);
			color.insert(color.end(), temp);
			addChild(color[i]);

			// CCLabelTTF
			CCLabelTTF* temp1 = CCLabelTTF::create(str[i],"Paint Boy",20,CCSizeMake(0,0),kCCTextAlignmentCenter);
			temp1->setPosition(Vec2(visibleSize.width - 45, visibleSize.height - (i + 1) * 20));
			temp1->setColor(ccc3(0,0,0));
			labels.insert(labels.end(), temp1);
			addChild(labels[i]);
		}

		return true;
	}
    return false;
}
void MainWindow::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
}
void MainWindow::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
}
void MainWindow::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
		r = atof(color[0]->getText());
		g = atof(color[1]->getText());
		b = atof(color[2]->getText());
		s = atoi(color[3]->getText());
}
void MainWindow::editBoxReturn(ui::EditBox* editBox)
{
}
void MainWindow::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
