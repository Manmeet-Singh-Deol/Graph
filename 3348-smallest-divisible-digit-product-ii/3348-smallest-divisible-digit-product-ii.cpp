class Solution {
public:
    struct PC { int c2=0,c3=0,c5=0,c7=0; };

    PC factorsOfDigit(int d) {
        static const int c2[10]={0,0,1,0,2,0,1,0,3,0};
        static const int c3[10]={0,0,0,1,0,0,1,0,0,2};
        static const int c5[10]={0,0,0,0,0,1,0,0,0,0};
        static const int c7[10]={0,0,0,0,0,0,0,1,0,0};
        PC r; r.c2=c2[d]; r.c3=c3[d]; r.c5=c5[d]; r.c7=c7[d];
        return r;
    }

    PC sub(const PC&a, const PC&b) {
        PC r;
        r.c2 = max(0, a.c2-b.c2);
        r.c3 = max(0, a.c3-b.c3);
        r.c5 = max(0, a.c5-b.c5);
        r.c7 = max(0, a.c7-b.c7);
        return r;
    }

    bool isSubset(const PC&a, const PC&b) {
        return b.c2>=a.c2 && b.c3>=a.c3 && b.c5>=a.c5 && b.c7>=a.c7;
    }

    struct DigitCounts { int cnt[10]={0}; }; // indices 2..9 used

    DigitCounts getFactorCount(PC count) {
        DigitCounts res;
        int count8 = count.c2/3;
        int remaining2 = count.c2%3;
        int count9 = count.c3/2;
        int count3 = count.c3%2;
        int count4 = remaining2/2;
        int count2 = remaining2%2;
        int count6 = 0;
        if (count2==1 && count3==1) {
            count2=0; count3=0; count6=1;
        }
        if (count3==1 && count4==1) {
            count2=1; count6=1; count3=0; count4=0;
        }
        res.cnt[2]=count2;
        res.cnt[3]=count3;
        res.cnt[4]=count4;
        res.cnt[5]=count.c5;
        res.cnt[6]=count6;
        res.cnt[7]=count.c7;
        res.cnt[8]=count8;
        res.cnt[9]=count9;
        return res;
    }

    int sumValues(const DigitCounts& f) {
        int s=0;
        for (int d=2; d<=9; d++) s+=f.cnt[d];
        return s;
    }

    string construct(const DigitCounts& f) {
        string res;
        for (int d=2; d<=9; d++)
            res.append(f.cnt[d], char('0'+d));
        return res;
    }

    PC getPrimeCountFromString(const string& num) {
        PC r;
        for (char ch : num) {
            PC f = factorsOfDigit(ch-'0');
            r.c2+=f.c2; r.c3+=f.c3; r.c5+=f.c5; r.c7+=f.c7;
        }
        return r;
    }

    string smallestNumber(string num, long long t) {
        PC primeCount;
        long long tt = t;
        int primes[4] = {2,3,5,7};
        for (int p : primes) {
            int cnt = 0;
            while (tt % p == 0) { tt/=p; cnt++; }
            if (p==2) primeCount.c2=cnt;
            else if (p==3) primeCount.c3=cnt;
            else if (p==5) primeCount.c5=cnt;
            else primeCount.c7=cnt;
        }
        if (tt != 1) return "-1";

        DigitCounts factorCount = getFactorCount(primeCount);
        int need = sumValues(factorCount);
        int n = (int)num.size();
        if (need > n) {
            return construct(factorCount);
        }

        PC primeCountPrefix = getPrimeCountFromString(num);
        int firstZeroIndex = -1;
        for (int i=0;i<n;i++) if (num[i]=='0') { firstZeroIndex=i; break; }
        if (firstZeroIndex == -1) {
            firstZeroIndex = n;
            if (isSubset(primeCount, primeCountPrefix)) return num;
        }

        for (int i=n-1; i>=0; i--) {
            int d = num[i]-'0';
            primeCountPrefix = sub(primeCountPrefix, factorsOfDigit(d));
            int spaceAfter = n-1-i;
            if (i > firstZeroIndex) continue;
            for (int biggerDigit=d+1; biggerDigit<10; biggerDigit++) {
                PC remaining = sub(sub(primeCount, primeCountPrefix), factorsOfDigit(biggerDigit));
                DigitCounts fc = getFactorCount(remaining);
                int s = sumValues(fc);
                if (s <= spaceAfter) {
                    int fillOnes = spaceAfter - s;
                    string result = num.substr(0, i);
                    result += char('0'+biggerDigit);
                    result += string(fillOnes, '1');
                    result += construct(fc);
                    return result;
                }
            }
        }

        DigitCounts factorsAfterExtension = getFactorCount(primeCount);
        int s = sumValues(factorsAfterExtension);
        string result = string(n+1-s, '1') + construct(factorsAfterExtension);
        return result;
    }
};
