#include "AppDelegate.h"
#include "MainScene.h"

#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#    include "audio/AudioEngine.h"
#endif

USING_NS_AX;

static const ax::Size desktopResolutionSize = ax::Size(1280, 720);
static const ax::Size tvResolution = ax::Size(1920, 1080);
static const ax::Size mobilePortraitResolution = ax::Size(720, 1280);
static const ax::Size mobileLandscapeResolution = ax::Size(1280, 720);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glView = director->getGLView();
    if (!glView)
    {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
        glView = GLViewImpl::createWithRect("fairygui-bug", ax::Rect(0, 0, desktopResolutionSize.width, desktopResolutionSize.height));
#else
        glView = GLViewImpl::create("fairygui-bug");
#endif
        director->setGLView(glView);
    }

    director->setStatsDisplay(true);
    director->setAnimationInterval(1.0f / 60);
    setDesignResolution();
    auto scene = utils::createInstance<MainScene>();
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}

void AppDelegate::setDesignResolution()
{
    auto director = Director::getInstance();
    auto glView = director->getGLView();
    auto frameSize = glView->getFrameSize();
    bool isPortrait = frameSize.height > frameSize.width;
    
    // calculate the aspect ratio of the design layout and the screen
    float designAspectRatio = 720.0f / 1280.0f;  // aspect ratio of the design layout (720x1280)
    float screenAspectRatio = frameSize.width / frameSize.height;
    
    // set the policy based on the comparison of aspect ratios
    ResolutionPolicy policy;
    if (screenAspectRatio >= designAspectRatio) {
        // the screen is wider than the design needs, so fix the height to fit all content vertically
        policy = ResolutionPolicy::FIXED_HEIGHT;
    } else {
        // the screen is narrower than the design needs, so fix the width to fit all content horizontally
        policy = ResolutionPolicy::FIXED_WIDTH;
    }
    
    // adjust the design resolution based on the platform and orientation
    if (AX_TARGET_PLATFORM == AX_PLATFORM_TVOS)
    {
        glView->setDesignResolutionSize(tvResolution.width, tvResolution.height, policy);
    }
    else if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32 || AX_TARGET_PLATFORM == AX_PLATFORM_MAC || AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
    {
        glView->setDesignResolutionSize(desktopResolutionSize.width, desktopResolutionSize.height, policy);
    }
    else if (isPortrait)
    {
        glView->setDesignResolutionSize(mobilePortraitResolution.width, mobilePortraitResolution.height, policy);
    }
    else
    {
        glView->setDesignResolutionSize(mobileLandscapeResolution.width, mobileLandscapeResolution.height, policy);
    }

    // adjust the scaleFactor to maximize visual quality
    float scaleFactor = (policy == ResolutionPolicy::FIXED_HEIGHT) ? frameSize.height / 1280.0f : frameSize.width / 720.0f;
    director->setContentScaleFactor(scaleFactor);
}
