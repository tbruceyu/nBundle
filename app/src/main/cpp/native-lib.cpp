#include <jni.h>
#include <string>
#include <nbundle/Bundle.h>
#include <jni_port/NativeBundleJni.h>

extern "C" JNIEXPORT jobject JNICALL
Java_com_tby_nbundle_MainActivity_helloNBundle(
        JNIEnv *env, jobject thiz, jobject jbundle) {
    Bundle* inBundle = getBundleFromJObject(jbundle);
    int64_t type = inBundle->getInt("type");
    string* res = inBundle->getString("res");
    string* name = inBundle->getString("name");
    float faceIntensity = inBundle->getFloat("faceIntensity");
    float eyeIntensity = inBundle->getFloat("eyeIntensity");

    Bundle* bundle = new Bundle();
    bundle->setFloat("intensity", faceIntensity + eyeIntensity);
    bundle->setString("nameres", *res + *name);

    return createNativeBundle(bundle);
}
