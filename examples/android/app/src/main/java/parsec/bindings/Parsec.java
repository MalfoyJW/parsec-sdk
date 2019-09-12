package parsec.bindings;

public class Parsec {
    static {
        System.loadLibrary("parsec-bindings");
    }

    // ParsecStatus
    public int PARSEC_OK = 0;

    // ParsecMouseButton
    public int MOUSE_L = 1;

    private long parsec; // Parsec *
    private long aaudio; // struct aaudio *

    public native void setLogCallback();
    public native void init();
    public native void destroy();
    public native int clientConnect(String sessionID, String peerID);
    public native void clientPollAudio();
    public native void clientDestroy();
    public native void clientSetDimensions(int x, int y);
    public native void clientGLRenderFrame();
    public native int clientSendMouseMotion(boolean relative, int x, int y);
    public native int clientSendMouseButton(int button, boolean pressed);
}
