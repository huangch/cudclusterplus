package com.cudclusterplus;

/**
 * Java interface for the CuDClusterPlus library
 */
public class CuDClusterPlus {
    
    static {
        try {
            System.loadLibrary("cudclusterplus_jni");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native library: " + e.getMessage());
            throw e;
        }
    }
    
    /**
     * Run DBSCAN clustering algorithm
     * 
     * @param points Input points as a flattened 2D array (row-major order)
     * @param n Number of points
     * @param dim Dimensionality of each point
     * @param eps Epsilon parameter for DBSCAN
     * @param minPts MinPts parameter for DBSCAN
     * @return Array of cluster labels
     */
    public int[] dbscan(float[] points, int n, int dim, float eps, int minPts) {
        int[] labels = new int[n];
        int result = CuDClusterPlusJNI.dbscan(points, n, dim, eps, minPts, labels);
        
        if (result != 0) {
            throw new RuntimeException("DBSCAN algorithm failed with error code: " + result);
        }
        
        return labels;
    }
    
    /**
     * Get library version
     * 
     * @return Version string
     */
    public static String getVersion() {
        return CuDClusterPlusJNI.getVersion();
    }
}