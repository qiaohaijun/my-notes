-march=native

最早见到这个编译选项, 实在tensorflow的编译中


```bash
gcc -c -Q -march=native --help=target 
下列选项与特定目标机相关:
  -m128bit-long-double        		[禁用]
  -m32                        		[禁用]
  -m3dnow                     		[禁用]
  -m3dnowa                    		[禁用]
  -m64                        		[启用]
  -m80387                     		[启用]
  -m8bit-idiv                 		[禁用]
  -m96bit-long-double         		[启用]
  -mabi=                      		sysv
  -mabm                       		[启用]
  -maccumulate-outgoing-args  		[禁用]
  -maddress-mode=             		short
  -madx                       		[启用]
  -maes                       		[禁用]
  -malign-double              		[禁用]
  -malign-functions=          		0
  -malign-jumps=              		0
  -malign-loops=              		0
  -malign-stringops           		[启用]
  -mandroid                   		[禁用]
  -march=                     		core-avx2
  -masm=                      		att
  -mavx                       		[启用]
  -mavx2                      		[启用]
  -mavx256-split-unaligned-load 	[禁用]
  -mavx256-split-unaligned-store 	[禁用]
  -mbionic                    		[禁用]
  -mbmi                       		[启用]
  -mbmi2                      		[启用]
  -mbranch-cost=              		0
  -mcld                       		[禁用]
  -mcmodel=                   		32
  -mcpu=                      		
  -mcrc32                     		[禁用]
  -mcx16                      		[启用]
  -mdispatch-scheduler        		[禁用]
  -mf16c                      		[启用]
  -mfancy-math-387            		[启用]
  -mfentry                    		[启用]
  -mfma                       		[启用]
  -mfma4                      		[禁用]
  -mforce-drap                		[禁用]
  -mfp-ret-in-387             		[启用]
  -mfpmath=                   		387
  -mfsgsbase                  		[启用]
  -mfused-madd                		
  -mfxsr                      		[启用]
  -mglibc                     		[启用]
  -mhard-float                		[启用]
  -mhle                       		[启用]
  -mieee-fp                   		[启用]
  -mincoming-stack-boundary=  		0
  -minline-all-stringops      		[禁用]
  -minline-stringops-dynamically 	[禁用]
  -mintel-syntax              		
  -mlarge-data-threshold=     		0x10000
  -mlong-double-64            		[禁用]
  -mlong-double-80            		[启用]
  -mlwp                       		[禁用]
  -mlzcnt                     		[启用]
  -mmmx                       		[禁用]
  -mmovbe                     		[启用]
  -mms-bitfields              		[禁用]
  -mno-align-stringops        		[禁用]
  -mno-fancy-math-387         		[禁用]
  -mno-push-args              		[禁用]
  -mno-red-zone               		[禁用]
  -mno-sse4                   		[禁用]
  -momit-leaf-frame-pointer   		[禁用]
  -mpc32                      		[禁用]
  -mpc64                      		[禁用]
  -mpc80                      		[禁用]
  -mpclmul                    		[启用]
  -mpku                       		[禁用]
  -mpopcnt                    		[启用]
  -mprefer-avx128             		[禁用]
  -mpreferred-stack-boundary= 		0
  -mprfchw                    		[启用]
  -mpush-args                 		[启用]
  -mrdrnd                     		[启用]
  -mrdseed                    		[启用]
  -mrecip                     		[禁用]
  -mrecip=                    		
  -mred-zone                  		[启用]
  -mregparm=                  		0
  -mrtd                       		[禁用]
  -mrtm                       		[启用]
  -msahf                      		[启用]
  -msoft-float                		[禁用]
  -msse                       		[启用]
  -msse2                      		[启用]
  -msse2avx                   		[禁用]
  -msse3                      		[启用]
  -msse4                      		[启用]
  -msse4.1                    		[启用]
  -msse4.2                    		[启用]
  -msse4a                     		[禁用]
  -msse5                      		
  -msseregparm                		[禁用]
  -mssse3                     		[启用]
  -mstack-arg-probe           		[禁用]
  -mstackrealign              		[启用]
  -mstringop-strategy=        		[默认]
  -mtbm                       		[禁用]
  -mtls-dialect=              		gnu
  -mtls-direct-seg-refs       		[启用]
  -mtune=                     		generic
  -muclibc                    		[禁用]
  -mveclibabi=                		[默认]
  -mvect8-ret-in-mem          		[禁用]
  -mvzeroupper                		[禁用]
  -mx32                       		[禁用]
  -mxop                       		[禁用]
  -mxsave                     		[启用]
  -mxsaveopt                  		[启用]

  Known assembler dialects (for use with the -masm-dialect= option):
    att intel

  Known ABIs (for use with the -mabi= option):
    ms sysv

  Known code models (for use with the -mcmodel= option):
    32 kernel large medium small

  Valid arguments to -mfpmath=:
    387 387+sse 387,sse both sse sse+387 sse,387

  Known vectorization library ABIs (for use with the -mveclibabi= option):
    acml svml

  Known address mode (for use with the -maddress-mode= option):
    long short

  Valid arguments to -mstringop-strategy=:
    byte_loop libcall loop rep_4byte rep_8byte rep_byte unrolled_loop

  Known TLS dialects (for use with the -mtls-dialect= option):
    gnu gnu2
```
