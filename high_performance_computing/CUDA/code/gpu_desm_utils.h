#include "gpu_desm_utils.h"
#include "cuda.h"
#include "stdio.h"

__global__
void KERNEL_EW_FloatMultiVecAdd(const float * ptr_dict_d_,
                                const int * title_word_matrix,
                                const int * title_sent_len,
                                const int batch_size,
                                const int max_len,
                                const int vec_dim,
                                float * ptr_out_d_){




    float *local_ptr_d_out = ptr_out_d_ + blockIdx.x*vec_dim;

    for(int j=0; j<title_sent_len[blockIdx.x]; j++) {

        int word_offset = title_word_matrix[blockIdx.x*max_len+j];

        const float * word_vec_start = ptr_dict_d_ + word_offset*vec_dim;

        for(int i=threadIdx.x; i<vec_dim; i+=blockDim.x){
            local_ptr_d_out[i] += word_vec_start[i];
        }
    }
 }


void EW_FloatMultiVecAdd( const float * ptr_dict_d_,
                          const int * title_word_matrix,
                          const int * title_sent_len,
                          const int batch_size,
                          const int max_len,
                          const int vec_dim,
                          float * ptr_out_d_)
{

    int block_size  = batch_size;
    int thread_size = 32;

    cudaMemset(ptr_out_d_, 0,sizeof(float)*batch_size*vec_dim);

    KERNEL_EW_FloatMultiVecAdd <<< block_size, thread_size >>> (
            ptr_dict_d_,
            title_word_matrix,
            title_sent_len,
            batch_size
            max_len,
            vec_dim,
            ptr_out_d_);

#if 0
    float *tmp = NULL;



    tmp = static_cast<float *> (malloc(sizeof(float)*batch_size*100));

    cudaMemcpy(tmp,ptr_d_out_start,sizeof(float)*batch_size*100,cudaMemcpyDeviceToHost);
    for(int i=0; i< batch_size; ++i) {
        for(int k =0; k<100; ++k) {
            printf("%g ",tmp[i*100+k]);

        }
        printf("\n");
                printf("\n");

        printf("\n");


    }
#endif


}
