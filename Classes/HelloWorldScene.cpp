#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Basic Shader — Channel Swapping", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
// Leave the visibleSize and origin variables in place in the init method of the default project. Add the following to the init method.
// Put an unmodified sprite on the left. Put another sprite that's treated with a shader on the right. Scale and place them so they both fit side-by-side. 

// Sprite without shader
    Sprite* spriteWithoutShader = Sprite::create("colorMarket1280_rgb.jpg");
    spriteWithoutShader->setScale( ( visibleSize.width / spriteWithoutShader->getContentSize().width ) / 2 );
    spriteWithoutShader->setPosition( Vec2( origin.x + visibleSize.width/2 - spriteWithoutShader->getBoundingBox().size.width/2, origin.y + visibleSize.height / 2 ) );
    this->addChild(spriteWithoutShader);

// Sprite with shader applied
    auto spriteWithShader = Sprite::create("colorMarket1280_rgb.jpg");
    spriteWithShader->setScale( ( visibleSize.width / spriteWithShader->getContentSize().width ) / 2 );
    spriteWithShader->setPosition( Vec2( origin.x + visibleSize.width/2 + spriteWithShader->getBoundingBox().size.width/2, origin.y + visibleSize.height / 2 ) );
    this->addChild(spriteWithShader);

// Create and apply the shader
// Load the external shader file into the application as a CString cast as a GLchar*. Note that the ChannelSwap.fsh shader file can be found in the Resources/shaders folder of our project. 
    GLchar * fragmentSource = (GLchar*) String::createWithContentsOfFile( FileUtils::getInstance()->fullPathForFilename( "shaders/ChannelSwap.fsh" ).c_str() )->getCString();
// Create a GLProgram with the shader file.
	auto p = GLProgram::createWithByteArrays( ccPositionTextureColor_noMVP_vert, fragmentSource );
// Create a GLProgramState from te GLProgram. 
	auto glProgramState = GLProgramState::getOrCreateWithGLProgram( p );
// Apply the shader to the Sprite.
	spriteWithShader->setGLProgramState( glProgramState );
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
