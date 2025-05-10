#ifndef CUDCLUSTERPLUS_H
#define CUDCLUSTERPLUS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * CUDA-based DBSCAN implementation
 * 
 * @param points Pointer to input data points (flattened 2D array)
 * @param n Number of points
 * @param dim Dimensionality of points
 * @param eps Epsilon parameter for DBSCAN
 * @param min_pts MinPts parameter for DBSCAN
 * @param labels Output array for cluster labels
 * @return 0 if successful, error code otherwise
 */
int cudcluster_dbscan(float* points, int n, int dim, float eps, int min_pts, int* labels);

/**
 * Get version information
 * 
 * @return Version string
 */
const char* cudcluster_version();

#ifdef __cplusplus
}
#endif

#endif // CUDCLUSTERPLUS_H