#pragma once

#include <string>

#ifdef __cplusplus
extern "C" {
#endif
#include <jni.h>
typedef int (*JNI_OnLoad_func_t)(JNIEnv *env);
typedef void (*JNI_OnUnload_func_t)(JNIEnv *env);

JavaVM *JNI_GetJvm(void);

JNIEnv *JNI_GetJNIEnv(void);

bool ExceptionCheck__catchAll(JNIEnv *env);

bool ExceptionCheck__throwAny(JNIEnv *env);

int JNI_ThrowException(JNIEnv *env, const char *exception, const char *msg);
int JNI_ThrowIllegalStateException(JNIEnv *env, const char *msg);

jobject JNI_NewObjectAsGlobalRef(JNIEnv *env, jclass clazz, jmethodID methodID, ...);

void JNI_DeleteGlobalRefP(JNIEnv *env, jobject *obj_ptr);
void JNI_DeleteLocalRefP(JNIEnv *env, jobject *obj_ptr);


#ifdef __cplusplus
}
#endif

std::string JNI_GetString(JNIEnv *env, jstring j_string);
