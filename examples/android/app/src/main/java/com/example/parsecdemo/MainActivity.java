package com.example.parsecdemo;

import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;

import parsec.bindings.Parsec;

public class MainActivity extends AppCompatActivity {
    private Parsec parsec;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        int uiFlag = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LOW_PROFILE
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;

        getWindow().getDecorView().setSystemUiVisibility(uiFlag);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }

    @Override
    protected void onStart() {
        super.onStart();

        this.parsec = new Parsec();

        this.parsec.setLogCallback();
        this.parsec.init();
        this.parsec.appInit();

        this.parsec.clientConnect("sessionID", "peerID");

        ClientSurface surface = new ClientSurface(this.getApplicationContext());
        surface.setParsec(parsec);

        ViewGroup vg = findViewById(android.R.id.content);
        ViewGroup.LayoutParams params = vg.getLayoutParams();
        this.addContentView(surface, params);
    }

    @Override
    protected void onDestroy() {
        this.parsec.appDestroy();
        this.parsec.clientDestroy();
        this.parsec.destroy();

        super.onDestroy();
    }
}
