#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "cudclusterplus.h"

namespace py = pybind11;

// Wrapper for the DBSCAN function
py::array_t<int> py_dbscan(py::array_t<float> points, float eps, int min_pts) {
    py::buffer_info buf_points = points.request();
    
    if (buf_points.ndim != 2) {
        throw std::runtime_error("Input points must be a 2-dimensional array");
    }
    
    int n = buf_points.shape[0];
    int dim = buf_points.shape[1];
    
    // Create output array for labels
    py::array_t<int> labels({n}, {sizeof(int)});
    py::buffer_info buf_labels = labels.request();
    
    // Call the CUDA function
    int result = cudcluster_dbscan(
        static_cast<float*>(buf_points.ptr),
        n,
        dim,
        eps,
        min_pts,
        static_cast<int*>(buf_labels.ptr)
    );
    
    if (result != 0) {
        throw std::runtime_error("DBSCAN algorithm failed with error code: " + std::to_string(result));
    }
    
    return labels;
}

// Python module definition
PYBIND11_MODULE(cudclusterplus, m) {
    m.doc() = "CuDClusterPlus: CUDA-based DBSCAN implementation";
    
    m.def("dbscan", &py_dbscan, 
          py::arg("points"), 
          py::arg("eps"), 
          py::arg("min_pts"),
          "Run DBSCAN clustering on the input points");
    
    m.def("version", &cudcluster_version, 
          "Get the version of CuDClusterPlus");
}