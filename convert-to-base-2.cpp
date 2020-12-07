// https://leetcode.com/problems/convert-to-base-2/
class Solution {
public:
    string baseNeg2(int N) {
        std::string ret;
        int base = -2;
        int remainder;
        int quotient = N;
        
        if(N == 0) {
            ret = "0";
            return ret;
        }
        
        while(quotient != 0) {
            remainder = quotient % base;
            quotient = quotient / base;
            
            if (remainder < 0) {
                remainder = remainder + abs(base);
                quotient = quotient + 1;
            }

            ret.insert(0, std::to_string(remainder));
        }
         return ret;
    }
};
