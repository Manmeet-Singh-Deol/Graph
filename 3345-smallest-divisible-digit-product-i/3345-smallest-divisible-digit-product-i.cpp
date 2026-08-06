class Solution {
public:
    int smallestNumber(int n, int t) {
        
        for(int x=n;;x++){
           int temp=1;
           int i=x;
           while(i!=0){
                temp*=i%10;
                i=i/10;

            }
            if(temp%t==0)return x;
        }
    }
};