/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_scriptographer_ai_Color */

#ifndef _Included_com_scriptographer_ai_Color
#define _Included_com_scriptographer_ai_Color
#ifdef __cplusplus
extern "C" {
#endif
#undef com_scriptographer_ai_Color_CONVERSION_MONO
#define com_scriptographer_ai_Color_CONVERSION_MONO 0L
#undef com_scriptographer_ai_Color_CONVERSION_GRAY
#define com_scriptographer_ai_Color_CONVERSION_GRAY 1L
#undef com_scriptographer_ai_Color_CONVERSION_RGB
#define com_scriptographer_ai_Color_CONVERSION_RGB 2L
#undef com_scriptographer_ai_Color_CONVERSION_ARGB
#define com_scriptographer_ai_Color_CONVERSION_ARGB 3L
#undef com_scriptographer_ai_Color_CONVERSION_CMYK
#define com_scriptographer_ai_Color_CONVERSION_CMYK 4L
#undef com_scriptographer_ai_Color_CONVERSION_ACMYK
#define com_scriptographer_ai_Color_CONVERSION_ACMYK 5L
#undef com_scriptographer_ai_Color_CONVERSION_AGRAY
#define com_scriptographer_ai_Color_CONVERSION_AGRAY 6L
#undef com_scriptographer_ai_Color_MODEL_GRAY
#define com_scriptographer_ai_Color_MODEL_GRAY 0L
#undef com_scriptographer_ai_Color_MODEL_RGB
#define com_scriptographer_ai_Color_MODEL_RGB 1L
#undef com_scriptographer_ai_Color_MODEL_CMYK
#define com_scriptographer_ai_Color_MODEL_CMYK 2L
/*
 * Class:     com_scriptographer_ai_Color
 * Method:    convert
 * Signature: (I)Lcom/scriptographer/ai/Color;
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Color_convert
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_scriptographer_ai_Color
 * Method:    getWSProfile
 * Signature: (I)Ljava/awt/color/ICC_Profile;
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_Color_getWSProfile
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif