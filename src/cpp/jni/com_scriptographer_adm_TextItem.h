/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_scriptographer_adm_TextItem */

#ifndef _Included_com_scriptographer_adm_TextItem
#define _Included_com_scriptographer_adm_TextItem
#ifdef __cplusplus
extern "C" {
#endif
#undef com_scriptographer_adm_TextItem_POPUP_MENU_RIGHT
#define com_scriptographer_adm_TextItem_POPUP_MENU_RIGHT 0L
#undef com_scriptographer_adm_TextItem_POPUP_MENU_BOTTOM
#define com_scriptographer_adm_TextItem_POPUP_MENU_BOTTOM 1L
#undef com_scriptographer_adm_TextItem_POPUP_MENU_ROUND
#define com_scriptographer_adm_TextItem_POPUP_MENU_ROUND 2L
#undef com_scriptographer_adm_TextItem_POPUP_MENU_ROUND_HIERARCHY
#define com_scriptographer_adm_TextItem_POPUP_MENU_ROUND_HIERARCHY 4L
#undef com_scriptographer_adm_TextItem_SPINEDIT_VERTICAL
#define com_scriptographer_adm_TextItem_SPINEDIT_VERTICAL 0L
#undef com_scriptographer_adm_TextItem_SPINEDIT_HORIZONTAL
#define com_scriptographer_adm_TextItem_SPINEDIT_HORIZONTAL 1L
#undef com_scriptographer_adm_TextItem_SPINEDIT_POPUP_VERTICAL
#define com_scriptographer_adm_TextItem_SPINEDIT_POPUP_VERTICAL 0L
#undef com_scriptographer_adm_TextItem_SPINEDIT_POPUP_HORIZONTAL
#define com_scriptographer_adm_TextItem_SPINEDIT_POPUP_HORIZONTAL 4L
#undef com_scriptographer_adm_TextItem_JUSTIFY_LEFT
#define com_scriptographer_adm_TextItem_JUSTIFY_LEFT 0L
#undef com_scriptographer_adm_TextItem_JUSTIFY_CENTER
#define com_scriptographer_adm_TextItem_JUSTIFY_CENTER 1L
#undef com_scriptographer_adm_TextItem_JUSTIFY_RIGHT
#define com_scriptographer_adm_TextItem_JUSTIFY_RIGHT 2L
#undef com_scriptographer_adm_TextItem_UNITS_NO
#define com_scriptographer_adm_TextItem_UNITS_NO 0L
#undef com_scriptographer_adm_TextItem_UNITS_POINT
#define com_scriptographer_adm_TextItem_UNITS_POINT 1L
#undef com_scriptographer_adm_TextItem_UNITS_INCH
#define com_scriptographer_adm_TextItem_UNITS_INCH 2L
#undef com_scriptographer_adm_TextItem_UNITS_MILLIMETER
#define com_scriptographer_adm_TextItem_UNITS_MILLIMETER 3L
#undef com_scriptographer_adm_TextItem_UNITS_CENTIMETER
#define com_scriptographer_adm_TextItem_UNITS_CENTIMETER 4L
#undef com_scriptographer_adm_TextItem_UNITS_PICA
#define com_scriptographer_adm_TextItem_UNITS_PICA 5L
#undef com_scriptographer_adm_TextItem_UNITS_PERCENT
#define com_scriptographer_adm_TextItem_UNITS_PERCENT 6L
#undef com_scriptographer_adm_TextItem_UNITS_DEGREE
#define com_scriptographer_adm_TextItem_UNITS_DEGREE 7L
#undef com_scriptographer_adm_TextItem_UNITS_Q
#define com_scriptographer_adm_TextItem_UNITS_Q 8L
#undef com_scriptographer_adm_TextItem_UNITS_BASE16
#define com_scriptographer_adm_TextItem_UNITS_BASE16 9L
#undef com_scriptographer_adm_TextItem_UNITS_PIXEL
#define com_scriptographer_adm_TextItem_UNITS_PIXEL 10L
#undef com_scriptographer_adm_TextItem_UNITS_TIME
#define com_scriptographer_adm_TextItem_UNITS_TIME 11L
#undef com_scriptographer_adm_TextItem_UNITS_HA
#define com_scriptographer_adm_TextItem_UNITS_HA 12L
/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    getFont
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_TextItem_getFont
  (JNIEnv *, jobject);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    setFont
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_TextItem_setFont
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    nativeSetText
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_TextItem_nativeSetText
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    setJustify
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_TextItem_setJustify
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    getJustify
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_TextItem_getJustify
  (JNIEnv *, jobject);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    setUnits
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_TextItem_setUnits
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    getUnits
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_adm_TextItem_getUnits
  (JNIEnv *, jobject);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    setShowUnits
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_scriptographer_adm_TextItem_setShowUnits
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_scriptographer_adm_TextItem
 * Method:    getShowUnits
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_scriptographer_adm_TextItem_getShowUnits
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif