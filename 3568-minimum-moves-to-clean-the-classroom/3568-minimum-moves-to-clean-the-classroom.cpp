class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        int sx, sy;
        vector<pair<int,int>> litter;
        
        // Locate start and litter
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(classroom[i][j]=='S'){ sx=i; sy=j; }
                if(classroom[i][j]=='L') litter.push_back({i,j});
            }
        }
        
        int litterCount = litter.size();
        int fullMask = (1<<litterCount)-1;
        
        // Map litter positions to IDs
        unordered_map<int,int> litterId;
        for(int i=0;i<litterCount;i++){
            litterId[litter[i].first*n + litter[i].second] = i;
        }
        
        vector<vector<vector<int>>> bestEnergy(m, vector<vector<int>>(n, vector<int>(1<<litterCount, -1)));
        
        queue<tuple<int,int,int,int,int>> q; 
        q.push({sx, sy, 0, energy, 0});
        bestEnergy[sx][sy][0] = energy;
        
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        
        while(!q.empty()){
            auto [x,y,mask,e,steps] = q.front(); q.pop();
            if(mask==fullMask) return steps;
            
            for(auto& d:dirs){
                int nx=x+d[0], ny=y+d[1];
                if(nx<0||ny<0||nx>=m||ny>=n||classroom[nx][ny]=='X') continue;
                if(e<=0) continue;
                
                int ne = e-1, nmask=mask;
                if(classroom[nx][ny]=='L'){
                    int id = litterId[nx*n + ny];
                    nmask |= (1<<id);
                }
                if(classroom[nx][ny]=='R') ne=energy;
                
                if(ne > bestEnergy[nx][ny][nmask]){
                    bestEnergy[nx][ny][nmask]=ne;
                    q.push({nx,ny,nmask,ne,steps+1});
                }
            }
        }
        return -1;
    }
};

