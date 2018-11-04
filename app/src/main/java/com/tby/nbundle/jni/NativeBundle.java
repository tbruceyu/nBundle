package com.tby.nbundle.jni;

/**
 * 这个类主要是用于传递Java的参数到C++层。由于Java的GC可能导致这个类被释放，
 * 请不要在C++里面持有handle里的Bundle对象。实在需要则拷贝构造一个新的，
 * Bundle对象可以手动释放，也可以等虚拟机GC自动释放
 */
public final class NativeBundle {
    private long handle = 0;

    public NativeBundle() {
        handle = nativeCreate();
    }

    // 这个方法一般是用于从底层创建这个对象的时候用的
    private NativeBundle(long handle) {
        this.handle = handle;
    }

    public void putInt(String key, int value) {
        if (handle == 0) return;
        nativePutInt(handle, key, value);
    }

    public int getInt(String key) {
        if (handle == 0) return 0;
        return nativeGetInt(handle, key);
    }

    public void putString(String key, String value) {
        if (handle == 0) return;
        nativePutString(handle, key, value);
    }

    public void putStringArray(String key, String[] values) {
        if (handle == 0) return;
        nativePutStringArray(handle, key, values);
    }

    public void putFloatArray(String key, float[] values) {
        nativePutFloatArray(handle, key, values);
    }

    public String getString(String key) {
        if (handle == 0) return null;

        return nativeGetString(handle, key);
    }

    public void putFloat(String key, float value) {
        nativePutFloat(handle, key, value);
    }

    public float getFloat(String key) {
        return nativeGetFloat(handle, key);
    }

    public void destroy() {
        if (handle == 0) return;
        nativeDestroy(handle);
        handle = 0;
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        destroy();
    }

    private native long nativeCreate();

    private native void nativeDestroy(long handle);

    private native void nativePutInt(long handle, String key, int value);

    private native int nativeGetInt(long handle, String key);

    private native void nativePutString(long handle, String key, String value);

    private native String nativeGetString(long handle, String key);

    private native void nativePutStringArray(long handle, String key, String[] strArr);

    private native void nativePutFloatArray(long handle, String key, float[] values);

    private native void nativePutFloat(long handle, String key, float speed);

    private native float nativeGetFloat(long handle, String key);
}
