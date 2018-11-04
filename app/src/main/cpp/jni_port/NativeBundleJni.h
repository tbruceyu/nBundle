#pragma once
#include <jni.h>
#include <string>
#include "nbundle/Bundle.h"

using namespace std;

jobject createNativeBundle(Bundle *);
Bundle *getBundleFromJObject(jobject jBundle);


