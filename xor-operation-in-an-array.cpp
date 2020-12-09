// https://leetcode.com/problems/xor-operation-in-an-array/

class Solution {
public:
    int xorOperation(int n, int start) {
        int ret = start;
        
        for(int i = 1; i < n; i++) {
            ret = ret ^ (start + 2 * i);
        }
        
        return ret;
    }
};
