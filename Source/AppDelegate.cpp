#include "AppDelegate.h"
#include "MainScene.h"

#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#    include "audio/AudioEngine.h"
#endif

USING_NS_AX;

static const ax::Size desktopResolutionSize     = ax::Size(1280, 720);
static const ax::Size tvResolution              = ax::Size(1920, 1080);
static const ax::Size mobilePortraitResolution  = ax::Size(720, 1280);
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
    auto glView   = director->getGLView();
    if (!glView)
    {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || \
    (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
        glView = GLViewImpl::createWithRect("fairygui-bug",
                                            ax::Rect(0, 0, desktopResolutionSize.width, desktopResolutionSize.height));
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
    auto director  = Director::getInstance();
    auto glView    = director->getGLView();
    auto frameSize = glView->getFrameSize();

    float designWidth       = 720;
    float designHeight      = 1280;
    float targetAspectRatio = designWidth / designHeight;

    float screenAspectRatio = frameSize.width / frameSize.height;

    float newDesignWidth, newDesignHeight;

    if (screenAspectRatio > targetAspectRatio)
    {
        newDesignHeight = designHeight;
        newDesignWidth  = designHeight * screenAspectRatio;
    }
    else
    {
        newDesignWidth  = designWidth;
        newDesignHeight = designWidth / screenAspectRatio;
    }

    ResolutionPolicy policy = ResolutionPolicy::EXACT_FIT;
    glView->setDesignResolutionSize(newDesignWidth, newDesignHeight, policy);

    float scaleFactor = std::min(frameSize.width / newDesignWidth, frameSize.height / newDesignHeight);
    director->setContentScaleFactor(scaleFactor);
}
