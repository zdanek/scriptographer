/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_scriptographer_ai_Curve */

#ifndef _Included_com_scriptographer_ai_Curve
#define _Included_com_scriptographer_ai_Curve
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_scriptographer_ai_Curve
 * Method:    nativeGetLength
 * Signature: (FFFFFFFFF)F
 */
JNIEXPORT jfloat JNICALL Java_com_scriptographer_ai_Curve_nativeGetLength
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_scriptographer_ai_Curve
 * Method:    nativeGetPartLength
 * Signature: (FFFFFFFFFFF)F
 */
JNIEXPORT jfloat JNICALL Java_com_scriptographer_ai_Curve_nativeGetPartLength
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_scriptographer_ai_Curve
 * Method:    nativeGetPositionWithLength
 * Signature: (FFFFFFFFFF)F
 */
JNIEXPORT jfloat JNICALL Java_com_scriptographer_ai_Curve_nativeGetPositionWithLength
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_scriptographer_ai_Curve
 * Method:    nativeAdjustThroughPoint
 * Signature: ([FFFF)V
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_Curve_nativeAdjustThroughPoint
  (JNIEnv *, jobject, jfloatArray, jfloat, jfloat, jfloat);

#ifdef __cplusplus
}
#endif
#endif