#include "NativeBundleJni.h"
#include "AndroidJni.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativeCreate(JNIEnv *env, jclass instance) {
    Bundle *bundle = new Bundle();
    return reinterpret_cast<jlong>(bundle);
}

JNIEXPORT void JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativePutInt(JNIEnv *env, jobject instance, jlong handle,
        jstring jkey, int value) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    bundle->setInt(key, value);
}

JNIEXPORT jint JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativeGetInt(JNIEnv *env, jobject instance, jlong handle,
        jstring jkey) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    return (int) bundle->getInt(key);
}

JNIEXPORT void JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativePutString(JNIEnv *env, jobject instance,
        jlong handle, jstring jkey, jstring jvalue) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    string value = JNI_GetString(env, jvalue);
    bundle->setString(key, value);
}

JNIEXPORT jstring JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativeGetString(JNIEnv *env, jobject instance,
        jlong handle, jstring jkey) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    string *value = bundle->getString(key);
    jstring jvalue = env->NewStringUTF(value->c_str());
    return jvalue;
}

JNIEXPORT void JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativePutStringArray(JNIEnv *env, jobject instance,
        jlong handle, jstring jkey, jobjectArray jvalue) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    jsize valueSize = env->GetArrayLength(jvalue);
    vector<string> stringArr;
    for (int i = 0; i < valueSize; ++i) {
        jstring jele = (jstring) env->GetObjectArrayElement(jvalue, i);
        stringArr.push_back(JNI_GetString(env, jele));
    }
    bundle->setStringArray(key, stringArr);
}

JNIEXPORT void JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativePutFloatArray(JNIEnv *env, jobject instance,
        jlong handle, jstring jkey, jfloatArray jvalue) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    jsize valueSize = env->GetArrayLength(jvalue);
    float *values = env->GetFloatArrayElements(jvalue, NULL);
    vector<float> floatArr;
    for (int i = 0; i < valueSize; ++i) {
        floatArr.push_back(values[i]);
    }
    bundle->setFloatArray(key, floatArr);
}

JNIEXPORT void JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativePutFloat(JNIEnv *env, jobject instance, jlong handle,
        jstring jkey, jfloat value) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    bundle->setFloat(key, value);
}

JNIEXPORT jfloat JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativeGetFloat(JNIEnv *env, jobject instance, jlong handle,
        jstring jkey) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    string key = JNI_GetString(env, jkey);
    return bundle->getFloat(key);
}

JNIEXPORT void JNICALL
Java_com_tby_nbundle_jni_NativeBundle_nativeDestroy(JNIEnv *env, jobject instance,
        jlong handle) {
    Bundle *bundle = reinterpret_cast<Bundle *>(handle);
    delete bundle;
}

#ifdef __cplusplus
}
#endif
static jmethodID nativeBundleConsMId = nullptr;
static jfieldID nativeHandleFId = nullptr;

static void ensureJNI(JNIEnv *env) {
    if (!nativeBundleConsMId || !nativeHandleFId) {
        jclass nativeBundleClass = env->FindClass("com/tby/nbundle/jni/NativeBundle");
        nativeBundleConsMId = env->GetMethodID(nativeBundleClass, "<init>", "(J)V");
        nativeHandleFId = env->GetFieldID(nativeBundleClass, "handle", "J");
    }
}

jobject createNativeBundle(Bundle *bundle) {
    JNIEnv *env = JNI_GetJNIEnv();
    ensureJNI(env);
    jclass nativeBundleClass = env->FindClass("com/tby/nbundle/jni/NativeBundle");
    jobject javaNBObj = env->NewObject(nativeBundleClass, nativeBundleConsMId,
            reinterpret_cast<jlong>(bundle));
    return javaNBObj;
}

Bundle *getBundleFromJObject(jobject jObj) {
    if (!jObj)
        return nullptr;
    JNIEnv *env = JNI_GetJNIEnv();
    ensureJNI(env);

    int64_t handle = env->GetLongField(jObj, nativeHandleFId);
    return reinterpret_cast<Bundle *>(handle);
}
