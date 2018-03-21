package org.libsdl.app;

/**
 * Created by asus on 2018/3/21.
 */

public class CallNativeMethods {
    //加载so库
    static {
        System.loadLibrary("SDL2");//注意是SDL2，错写为SDL后，logcat竟然不显示无法加载的错误，找了很久才知道是这里写错了
        System.loadLibrary("main");
    }
    //native方法
    public native static void changeHanioLevel(int level);
    public native static void changeFPS(int f);
    public native static void exitGame();
    public native static void startMove();
}
