package com.jp.jnitest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public String tag = "MainActivity";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        UserBean userBean = new UserBean();
        userBean.setAge(30);
        userBean.setUsername("调用C层本地接口");
        String mAge =  userBean.getAge() + "";
        String userName =  userBean.getUsername();
        userBean.setIncome(632);
        long income = userBean.getIncome();
        tv.setText(income + ":" + mAge + ":" + userName);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public UserBean getUser(){
        UserBean userBean = new UserBean();
        userBean.setAge(20);
        return userBean;
    }
}
