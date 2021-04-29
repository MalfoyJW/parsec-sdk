package com.example.parsecdemo;

import android.content.Context;
import android.view.SurfaceView;
import android.view.SurfaceHolder;

import android.view.MotionEvent;

import parsec.bindings.Parsec;

public class ClientSurface extends SurfaceView implements SurfaceHolder.Callback {

    private Parsec parsec;

    public ClientSurface(Context context) {
        super(context);
        this.getHolder().addCallback(this);
    }

    public void setParsec(Parsec parsec) {
        this.parsec = parsec;
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        this.parsec.appDestroySurface();
        this.parsec.appSetSurface(holder.getSurface());
        this.parsec.clientSetDimensions(w, h);
    }

    public void surfaceCreated(SurfaceHolder holder) {

    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        this.parsec.appDestroySurface();
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
