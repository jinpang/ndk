package com.jp.jnitest;

/**
 * @projectName: JNITest
 * @package: com.jp.jnitest
 * @className: UserBean
 * @description: java类作用描述
 * @author: pangjingzhong
 * @email: jingzhongp@gmail.com
 * @createDate: 2019/7/11 9:43
 * @updateUser: 更新者
 * @updateDate: 2019/7/11 9:43
 * @updateRemark: 更新说明
 * @version: 1.0
 * @copyright: 2018-2019 (C)深圳市冰禾网络科技有限公司 Inc. All rights reserved.
 */
public class UserBean {
    //保存c++类的地址
    long nativePerson;
    //构造函数
    public UserBean(){
        nativePerson = createNativeObject();
    }
    public void setAge(int age){
        setAge(nativePerson,age);
        return;
    }

    public int getAge(){
        return getAge(nativePerson);
    }

    public void setUsername(String name){
        setUsername(nativePerson, name);
    }

    public String getUsername(){
        return getUsername(nativePerson);
    }

    public void setIncome(long age){
        setIncome(nativePerson, age);
        return;
    }

    public int getIncome(){
        return getIncome(nativePerson);
    }

    /**本地方法：创建c++对象并返回地址*/
    private native long createNativeObject();
    private native void setAge(long addr,int age);
    private native int getAge(long addr);
    private native String getUsername(long addr);
    private native void setUsername(long addr, String username);
    private native void setIncome(long addr, long age);
    private native int getIncome(long addr);
}
