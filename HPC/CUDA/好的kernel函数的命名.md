```
__global__ void KERNEL_EWFloatAdd(float* des, float* ina, float* inb,
		int single_size, int batch_cnt,
		int ld_des, int ld_ina, int ld_inb) {
	int batch_idx = blockIdx.y * blockDim.y + threadIdx.y;
	int idx_in_batch_start = (blockIdx.x * blockDim.x + threadIdx.x) * REPEAT_IN_THREAD;
	for (int i = 0; i < REPEAT_IN_THREAD; i++) {
		int idx_in_batch = idx_in_batch_start + i;
		if (idx_in_batch < single_size && batch_idx < batch_cnt) {
			des[batch_idx * ld_des + idx_in_batch] =
					ina[batch_idx * ld_ina + idx_in_batch] + inb[batch_idx * ld_inb + idx_in_batch];
		}
	}
	return;
}

int EWFloatAdd(float* des, float* ina, float* inb, int single_size, int batch_cnt,
		int ld_des, int ld_ina, int ld_inb, dl_kernel::ThreadContext* context) {
	if (single_size <= 0 || single_size > ld_des || single_size > ld_ina || single_size > ld_inb) {
		_ERROR_RETURN(-1, "[EWFloatAddProduction] input not correct! single_size: %d, ld_des: %d, ld_ina: %d, ld_inb:%d",
				single_size, ld_des, ld_ina, ld_inb);
	}
	int blockx = 1, blocky = 1;
	int threadx = WARP_SIZE, thready = WARPS_IN_BLOCK;
	if (single_size > WARP_SIZE * REPEAT_IN_THREAD) {
		blockx = (single_size + WARP_SIZE * REPEAT_IN_THREAD - 1) / (WARP_SIZE * REPEAT_IN_THREAD);
	} else {
		threadx = (single_size + REPEAT_IN_THREAD - 1) / REPEAT_IN_THREAD;
	}
	if (batch_cnt > WARPS_IN_BLOCK) {
		blocky = (batch_cnt + WARPS_IN_BLOCK - 1) / WARPS_IN_BLOCK;
	} else {
		thready = batch_cnt;
	}
	dim3 threads_per_block(threadx, thready);
	dim3 block_dim(blockx, blocky);
	KERNEL_EWFloatAdd<<<block_dim, threads_per_block, 0, context->thread_default_stream>>>(
			des, ina, inb, single_size, batch_cnt, ld_des, ld_ina, ld_inb);
	return 0;
}

```
