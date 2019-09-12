package com.example.parsecdemo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import javax.microedition.khronos.opengles.GL10;

import parsec.bindings.Parsec;

public class ClientGLSurface extends GLSurfaceView {
    private Parsec parsec;

    public ClientGLSurface(Context context) {
        super(context);
    }

    public void setParsec(Parsec parsec) {
        this.parsec = parsec;
    }

    public void renderInit() {
        setEGLContextClientVersion(2);

        this.setRenderer(new Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl10, javax.microedition.khronos.egl.EGLConfig eglConfig) {}

            @Override
            public void onSurfaceChanged(GL10 gl10, int width, int height) {
                parsec.clientSetDimensions(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl10) {
                parsec.clientPollAudio();
                parsec.clientGLRenderFrame();
            }
        });

        this.setRenderMode(RENDERMODE_CONTINUOUSLY);
        this.setPreserveEGLContextOnPause(true);
    }

    @Override
    public boolean onTouchEvent(MotionEvent touchEvent) {
        super.onTouchEvent(touchEvent);

        int x = (int) touchEvent.getX();
        int y = (int) touchEvent.getY();

        if (touchEvent.getAction() == MotionEvent.ACTION_DOWN ||
                touchEvent.getAction() == MotionEvent.ACTION_UP) {
            parsec.clientSendMouseMotion(false, x, y);
            parsec.clientSendMouseButton(parsec.MOUSE_L,touchEvent.getAction() == MotionEvent.ACTION_DOWN);

        } else if (touchEvent.getAction() == MotionEvent.ACTION_MOVE) {
            parsec.clientSendMouseMotion(false, x, y);
        }

        return true;
    }
}