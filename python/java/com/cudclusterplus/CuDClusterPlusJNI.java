package com.cudclusterplus;

/**
 * JNI Native methods for CuDClusterPlus
 * This class provides the native method declarations that will be implemented in C++
 */
class CuDClusterPlusJNI {
    
    /**
     * Native implementation of DBSCAN
     * 
     * @param points Input points array (flattened row-major)
     * @param n Number of points
     * @param dim Dimensionality of each point
     * @param eps Epsilon parameter for DBSCAN
     * @param minPts MinPts parameter for DBSCAN
     * @param labels Output labels array
     * @return 0 if successful, error code otherwise
     */
    protected static native int dbscan(float[] points, int n, int dim, float eps, int minPts, int[] labels);
    
    /**
     * Get version information
     * 
     * @return Version string
     */
    protected static native String getVersion();
}