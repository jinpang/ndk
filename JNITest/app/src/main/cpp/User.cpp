#include "User.h"
#include <jni.h>
#include <string>
#include <android/log.h>

jstring chartoJstring(JNIEnv* env, const char* pat)
{
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

char* jstringTostring(JNIEnv* env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_jp_jnitest_UserBean_createNativeObject(JNIEnv *env, jobject obj) {
    jlong result;
    result = (jlong) new User();
    return result;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jp_jnitest_UserBean_setAge__JI(JNIEnv *env, jobject obj, jlong addr, jint age) {
    //对象指针调用方法
    ((User *) addr)->setAge(age + 20);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_jp_jnitest_UserBean_getAge__J(JNIEnv *env, jobject obj, jlong addr) {
    return ((User *) addr)->getAge();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jp_jnitest_UserBean_getUsername(JNIEnv *env, jobject instance, jlong addr) {
    char* nickname = ((User *) addr)->getNickname();//使用c
    std::string username = ((User *) addr)->getUsername();//使用c++
    char* chardata = (char*)username.c_str();
    // char* 转 string
    jstring jstr = chartoJstring(env, chardata);
    __android_log_print(ANDROID_LOG_ERROR, "getUsername", "%s   %s", nickname, chardata);
    return jstr;
//    return chartoJstring(env, nickname);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jp_jnitest_UserBean_setUsername(JNIEnv *env, jobject instance, jlong addr,
                                         jstring username_) {
    char* username = jstringTostring(env, username_);
    std::string s = env->GetStringUTFChars(username_, NULL);
    ((User *) addr)->setNickname(username);
    ((User *) addr)->setUsername(s);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jp_jnitest_UserBean_setIncome(JNIEnv *env, jobject instance, jlong addr, jlong age) {
    //对象指针调用方法
    ((User *) addr)->setIncome(age + 20);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_jp_jnitest_UserBean_getIncome(JNIEnv *env, jobject instance, jlong addr) {
    return ((User *) addr)->getIncome();
}

int User::getAge() {
    return this->age;
}

void User::setAge(int age) {
    this->age = age;
}

User::User() {

}

std::string User::getUsername() {
    return this->username;
}

void User::setUsername(std::string username) {
    this->username = username;
}

long User::getIncome() const {
    return income;
}

void User::setIncome(long income) {
    User::income = income;
}

char *User::getNickname() const {
    return nickname;
}

void User::setNickname(char *nickname) {
    this->nickname = nickname;
}
