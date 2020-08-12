#import "AppDelegate.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>

#import <ParsecSDK/parsec.h>

#include "audio.h"

#define SESSION_ID "sessionID"
#define PEER_ID    "peerID"

static void logCallback(ParsecLogLevel level, const char *msg, void *opaque)
{
    printf("[%s] %s\n", level == LOG_DEBUG ? "D" : "I", msg);
}

@interface AppDelegate ()
@end

@implementation AppDelegate

struct audio *_audio = NULL;
Parsec *_parsec = NULL;
bool _glInit = false;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];

    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    GLKView *view = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    view.context = context;
    view.delegate = self;

    GLKViewController * viewController = [[GLKViewController alloc] initWithNibName:nil bundle:nil];
    viewController.view = view;
    viewController.delegate = self;
    viewController.preferredFramesPerSecond = 60;
    self.window.rootViewController = viewController;

    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];

    ParsecSetLogCallback(logCallback, NULL);

    audio_init(&_audio);

    ParsecInit(PARSEC_VER, NULL, NULL, &_parsec);

    ParsecStatus e = ParsecClientConnect(_parsec, NULL, SESSION_ID, PEER_ID); // Performs peer-to-peer connection

    if (e != PARSEC_OK)
        NSLog(@"ParsecClientConnect=%d", e);

    return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
    if (!_parsec)
        return;

    ParsecDestroy(_parsec);
    audio_destroy(&_audio);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    ParsecClientPollAudio(_parsec, audio_cb, 0, _audio);
    ParsecClientSetDimensions(_parsec, DEFAULT_STREAM, self.window.frame.size.width,
                              self.window.frame.size.height, [[UIScreen mainScreen] scale]);
    ParsecClientGLRenderFrame(_parsec, DEFAULT_STREAM, NULL, NULL, 8);
    glFinish(); // May improve latency
}

- (void)glkViewControllerUpdate:(GLKViewController *)controller {
}

static void mouseMotion(Parsec *parsec, NSSet *touches, id window)
{
    UITouch *touch = [touches anyObject];
    CGPoint point = [touch locationInView:window];

    ParsecMessage msg = {};
    msg.type = MESSAGE_MOUSE_MOTION;
    msg.mouseMotion.relative = false;
    msg.mouseMotion.x = (int32_t) point.x;
    msg.mouseMotion.y = (int32_t) point.y;
    ParsecClientSendMessage(_parsec, &msg);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    mouseMotion(_parsec, touches, self.window);

    ParsecMessage msg = {};
    msg.mouseButton.button = MOUSE_L;
    msg.mouseButton.pressed = true;
    ParsecClientSendMessage(_parsec, &msg);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    mouseMotion(_parsec, touches, self.window);
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    mouseMotion(_parsec, touches, self.window);

    ParsecMessage msg = {};
    msg.mouseButton.button = MOUSE_L;
    msg.mouseButton.pressed = false;
    ParsecClientSendMessage(_parsec, &msg);
}

@end
