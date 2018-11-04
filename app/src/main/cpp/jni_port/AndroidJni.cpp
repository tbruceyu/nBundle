#include <unistd.h>
#include <pthread.h>
#include <jni.h>
#include <utils/Log.h>
#include "AndroidJni.h"
#undef TAG
#define TAG "AndroidJni"


static JavaVM *g_jvm = NULL;
static pthread_key_t g_threadKey;

extern "C"
{

JavaVM *JNI_GetJvm() {
    return g_jvm;
}

JNIEnv *JNI_GetJNIEnv() {
    JNIEnv *p_env = nullptr;
    int status = g_jvm->GetEnv((void **) &p_env, JNI_VERSION_1_6);
    if (status == JNI_EDETACHED) {
        if (g_jvm->AttachCurrentThread(&p_env, NULL) != JNI_OK) {
            Log::i(TAG, "%s: AttachCurrentThread() failed", __FUNCTION__);
            return p_env;
        }
        pthread_setspecific(g_threadKey, (void *) p_env);
        return p_env;
    }
    return p_env;
}

int JNI_ThrowException(JNIEnv *env, const char *className, const char *msg) {
    if (env->ExceptionCheck()) {
        jthrowable exception = env->ExceptionOccurred();
        env->ExceptionClear();

        if (exception != NULL) {
            Log::i(TAG, "Discarding pending exception (%s) to throw", className);

            env->DeleteLocalRef(exception);
        }
    }

    jclass exceptionClass = env->FindClass(className);
    if (exceptionClass == NULL) {
        Log::i(TAG, "Unable to find exception class %s", className);
        /* ClassNotFoundException now pending */
        goto fail;
    }

    if (env->ThrowNew(exceptionClass, msg) != JNI_OK) {
        Log::i(TAG, "Failed throwing '%s' '%s'", className, msg);
        /* an exception, most likely OOM, will now be pending */
        goto fail;
    }

    return 0;
    fail:
    if (exceptionClass)
        env->DeleteLocalRef(exceptionClass);
    return -1;
}

int JNI_ThrowIllegalStateException(JNIEnv *env, const char *msg) {
    return JNI_ThrowException(env, "java/lang/IllegalStateException", msg);
}

void JNI_DeleteGlobalRefP(JNIEnv *env, jobject *obj_ptr) {
    if (!obj_ptr || !*obj_ptr)
        return;

    env->DeleteGlobalRef(*obj_ptr);
    *obj_ptr = NULL;
}

void JNI_DeleteLocalRefP(JNIEnv *env, jobject *obj_ptr) {
    if (!obj_ptr || !*obj_ptr)
        return;

    env->DeleteLocalRef(*obj_ptr);
    *obj_ptr = NULL;
}

bool ExceptionCheck__throwAny(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        return true;
    }

    return false;
}

bool ExceptionCheck__catchAll(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return true;
    }

    return false;
}


static void JNI_ThreadDestroyed(void *value) {
    JNIEnv *env = (JNIEnv *) value;
    if (env != NULL) {
        g_jvm->DetachCurrentThread();
        pthread_setspecific(g_threadKey, NULL);
    }
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    g_jvm = vm;
    if (g_jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        Log::e(TAG, "Failed to get the environment using GetEnv()");
        return JNI_ERR;
    }

    if (pthread_key_create(&g_threadKey, JNI_ThreadDestroyed) != JNI_OK) {
        Log::e(TAG, "Error initializing pthread key");
    }
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if (g_jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        Log::e(TAG, "Failed to get the environment using GetEnv()");
        return;
    }
}

}


string JNI_GetString(JNIEnv *env, jstring j_string) {
    const char *c_str = j_string == nullptr ? "" : env->GetStringUTFChars(j_string, nullptr);
    string cppStr = c_str;
    if (j_string) env->ReleaseStringUTFChars(j_string, c_str);
    return cppStr;
}
