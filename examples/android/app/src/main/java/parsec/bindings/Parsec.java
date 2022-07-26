package parsec.bindings;

import android.view.Surface;

public class Parsec {
    static {
        System.loadLibrary("parsec-bindings");
    }

    // ParsecStatus
    public int PARSEC_OK = 0;

    // ParsecMouseButton
    public int MOUSE_L = 1;

    private long parsec; // Parsec *
    private long impl; // app implementation *

    // bindings
    public native void setLogCallback();
    public native void init();
    public native void destroy();
    public native int clientConnect(String sessionID, String peerID);
    public native int clientGetStatus();
    public native void clientDestroy();
    public native void clientSetDimensions(int x, int y);
    public native int clientSendMouseMotion(boolean relative, int x, int y);
    public native int clientSendMouseButton(int button, boolean pressed);

    // app implementation
    public native void appInit();
    public native void appDestroy();
    public native void appSetSurface(Surface surface);
    public native void appDestroySurface();
}
