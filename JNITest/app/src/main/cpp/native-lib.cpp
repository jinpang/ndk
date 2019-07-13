#include <jni.h>
#include <stdio.h>
#include <string>
#include <bitset>
#include <android/log.h>

#define  LOG_TAG    "test===="
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

char *jstringToChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

JNIEXPORT jstring JNICALL
Java_com_jp_jnitest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject obj/* this */) {
    jfieldID jfieldID1 = (env)->GetFieldID(env->GetObjectClass(obj), "tag", "Ljava/lang/String;");
    jstring tag = (jstring) env->GetObjectField(obj, jfieldID1);
    //printf("%s\n", tag);
    char * str = jstringToChar(env, tag);
    printf("%s\n", str);//打印到run后台窗口
    LOGE("%s %d %f",str, 100, 200.0);//打印到Logcat窗口
    std::string hello = "Hello from C++ ";
    jclass getUserClass = (env)->FindClass("com/jp/jnitest/UserBean");
    jmethodID jmethodID1 = env->GetMethodID(env->GetObjectClass(obj), "getUser", "()Lcom/jp/jnitest/UserBean;");
    env->CallObjectMethod(obj, jmethodID1);
    return env->NewStringUTF(hello.c_str());
}

#ifdef __cplusplus
}
#endif
