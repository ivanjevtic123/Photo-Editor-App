/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class poop_ImageCanvas */

#ifndef _Included_poop_ImageCanvas
#define _Included_poop_ImageCanvas
#ifdef __cplusplus
extern "C" {
#endif
#undef poop_ImageCanvas_FOCUS_TRAVERSABLE_UNKNOWN
#define poop_ImageCanvas_FOCUS_TRAVERSABLE_UNKNOWN 0L
#undef poop_ImageCanvas_FOCUS_TRAVERSABLE_DEFAULT
#define poop_ImageCanvas_FOCUS_TRAVERSABLE_DEFAULT 1L
#undef poop_ImageCanvas_FOCUS_TRAVERSABLE_SET
#define poop_ImageCanvas_FOCUS_TRAVERSABLE_SET 2L
#undef poop_ImageCanvas_TOP_ALIGNMENT
#define poop_ImageCanvas_TOP_ALIGNMENT 0.0f
#undef poop_ImageCanvas_CENTER_ALIGNMENT
#define poop_ImageCanvas_CENTER_ALIGNMENT 0.5f
#undef poop_ImageCanvas_BOTTOM_ALIGNMENT
#define poop_ImageCanvas_BOTTOM_ALIGNMENT 1.0f
#undef poop_ImageCanvas_LEFT_ALIGNMENT
#define poop_ImageCanvas_LEFT_ALIGNMENT 0.0f
#undef poop_ImageCanvas_RIGHT_ALIGNMENT
#define poop_ImageCanvas_RIGHT_ALIGNMENT 1.0f
#undef poop_ImageCanvas_serialVersionUID
#define poop_ImageCanvas_serialVersionUID -7644114512714619750i64
#undef poop_ImageCanvas_serialVersionUID
#define poop_ImageCanvas_serialVersionUID -2284879212465893870i64
#undef poop_ImageCanvas_serialVersionUID
#define poop_ImageCanvas_serialVersionUID 1i64
	/*
	 * Class:     poop_ImageCanvas
	 * Method:    readBMPData
	 * Signature: (Ljava/lang/String;)[B
	 */
	JNIEXPORT jbyteArray JNICALL Java_poop_ImageCanvas_readBMPData
	(JNIEnv *, jobject, jstring);

	/*
	 * Class:     poop_ImageCanvas
	 * Method:    readPAMData
	 * Signature: (Ljava/lang/String;)[B
	 */
	JNIEXPORT jbyteArray JNICALL Java_poop_ImageCanvas_readPAMData
	(JNIEnv *, jobject, jstring);

	/*
	 * Class:     poop_ImageCanvas
	 * Method:    writeBMPData
	 * Signature: (Ljava/lang/String;Ljava/nio/ByteBuffer;I)V
	 */
	JNIEXPORT void JNICALL Java_poop_ImageCanvas_writeBMPData
	(JNIEnv *, jobject, jstring, jobject, jint);

	/*
	 * Class:     poop_ImageCanvas
	 * Method:    writePAMData
	 * Signature: (Ljava/lang/String;Ljava/nio/ByteBuffer;I)V
	 */
	JNIEXPORT void JNICALL Java_poop_ImageCanvas_writePAMData
	(JNIEnv *, jobject, jstring, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
