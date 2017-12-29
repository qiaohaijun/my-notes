#define CUDA_CHECK( fn ) do { \
                CUresult status = (fn); \
                if ( CUDA_SUCCESS != status ) { \
                        const char* errstr; \
                        cuGetErrorString(status, &errstr); \
                        printf("CUDA Driver Failure (line %d of file %s):\n\t%s returned 0x%x (%s)\n", __LINE__, __FILE__, #fn, status, errstr); \
                        if (hCublas)  cublasDestroy(hCublas); \
                        if (hContext) cuCtxDestroy(hContext); \
                        exit(EXIT_FAILURE); \
                } \
        } while (0)

