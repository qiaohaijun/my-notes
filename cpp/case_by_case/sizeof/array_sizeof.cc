#defne _sizeof(T) ( (size_t)((T*)0 + 1))


#define array_sizeof(T) ( (size_t)(&T+1) - (size_t)(&T) )
