这个题目确实很有意思.

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
      
      if(n<0) {
        return 0;
      }
      
      std::vector<int> ugly_vec;
      ugly_vec.resize(n);
      
      int g_idx = 0;
      int idx2 = 0;
      int idx3 = 0;
      int idx5 = 0;
      
      ugly_vec[0] = 1;
      
      while(g_idx<n-1) 
      {
        
        g_idx++;

        int val2 = ugly_vec[idx2]*2;
        int val3 = ugly_vec[idx3]*3;
        int val5 =  ugly_vec[idx5]*5;
        
        // 动态规划, 说的是这个一行吧
        int new_ugly = std::min<int>(val2, std::min<int>(val3,val5));
        
        ugly_vec[g_idx] = new_ugly;
        
        while(ugly_vec[idx2]*2 == new_ugly)
        {
          idx2++; 
        }
        
        while(ugly_vec[idx3]*3 == new_ugly)
        {
          idx3++;
        }
        
        while(ugly_vec[idx5]*5 == new_ugly)
        {
          idx5++;
        }
        
      }
      
      return ugly_vec[n-1];
      
    }
};

```

这个题目其实很有意思的.

### 解题角度
- k 路归并
- 动态规划

### 如果是面试官
