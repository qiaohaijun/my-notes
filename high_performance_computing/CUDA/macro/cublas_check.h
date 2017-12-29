
#define CUBLAS_CHECK( fn ) do { \
                cublasStatus_t status = (fn); \
                if ( CUBLAS_STATUS_SUCCESS != status ) { \
                        printf("Cublas Failure (line %d of file %s):\n\t%s returned %d\n", __LINE__, __FILE__, #fn, status); \
                        if (hCublas)  cublasDestroy(hCublas); \
                        if (hContext) cuCtxDestroy(hContext); \
                        exit(EXIT_FAILURE); \
                } \
        } while (0)
