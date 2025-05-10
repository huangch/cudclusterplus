#include <jni.h>
#include <string>
#include "cudclusterplus.h"
#include "com_cudclusterplus_CuDClusterPlusJNI.h"

// Implementation of native methods

/*
 * Class:     com_cudclusterplus_CuDClusterPlusJNI
 * Method:    dbscan
 * Signature: ([FIIFI[I)I
 */
JNIEXPORT jint JNICALL Java_com_cudclusterplus_CuDClusterPlusJNI_dbscan
  (JNIEnv *env, jclass cls, jfloatArray points, jint n, jint dim, jfloat eps, jint minPts, jintArray labels) {
    
    // Get input array
    jfloat *points_ptr = env->GetFloatArrayElements(points, NULL);
    jint *labels_ptr = env->GetIntArrayElements(labels, NULL);
    
    if (points_ptr == NULL || labels_ptr == NULL) {
        if (points_ptr != NULL) env->ReleaseFloatArrayElements(points, points_ptr, JNI_ABORT);
        if (labels_ptr != NULL) env->ReleaseIntArrayElements(labels, labels_ptr, JNI_ABORT);
        return -1; // Out of memory
    }
    
    // Call the CUDA function
    int result = cudcluster_dbscan(
        points_ptr,
        (int)n,
        (int)dim,
        (float)eps,
        (int)minPts,
        (int*)labels_ptr
    );
    
    // Release arrays
    env->ReleaseFloatArrayElements(points, points_ptr, JNI_ABORT);
    env->ReleaseIntArrayElements(labels, labels_ptr, 0); // 0 means copy back and free
    
    return result;
}

/*
 * Class:     com_cudclusterplus_CuDClusterPlusJNI
 * Method:    getVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_cudclusterplus_CuDClusterPlusJNI_getVersion
  (JNIEnv *env, jclass cls) {
    const char* version = cudcluster_version();
    return env->NewStringUTF(version);
}