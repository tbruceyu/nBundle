package com.tby.nbundle;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.tby.nbundle.jni.NativeBundle;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        NativeBundle inBundle = new NativeBundle();
        inBundle.putInt("type", 1);
        inBundle.putString("res", "/sdcard/");
        inBundle.putString("name", "nativeBundle");
        inBundle.putFloat("faceIntensity", 0.5f);
        inBundle.putFloat("eyeIntensity", 0.88f);
        NativeBundle outBundle = helloNBundle(inBundle);
        String intensities = String.valueOf("intensity:" + outBundle.getFloat("intensity") + "\n");
        String nameres = String.valueOf("nameres:" + outBundle.getString("nameres"));
        tv.setText(intensities + nameres);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private native NativeBundle helloNBundle(NativeBundle bundle);
}
