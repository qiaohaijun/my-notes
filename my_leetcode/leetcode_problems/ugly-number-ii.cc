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

        int min_ugly = std::min<int>(ugly_vec[idx2]*2, std::min<int>(ugly_vec[idx3]*3, ugly_vec[idx5]*5));
        
        ugly_vec[g_idx] = min_ugly;
        
        while(ugly_vec[idx2]*2 <= min_ugly)
        {
          idx2++; 
        }
        
        while(ugly_vec[idx3]*3 <= min_ugly)
        {
          idx3++;
        }
        
        while(ugly_vec[idx5]*5 <= min_ugly)
        {
          idx5++;
        }
        
      }
      
      return ugly_vec[n-1];
      
    }
};
