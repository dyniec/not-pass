#include<cstdio>
#include<vector>
#include<unordered_set>
#include<unordered_map>

std::unordered_map<int,int> nn;//new numbers
std::vector<std::vector<int> > G,G_rev;
std::vector<bool> player;
std::vector<unsigned char>colours;
int n0,n1,m,V;
void read()
{
  scanf("%d%d%d",&n0,&n1,&m);
  G.resize(n0+n1);
  G_rev.resize(n0+n1);
  colours.resize(n0+n1);
  int cnt=0;
  for(int i=0;i<n0;i++)
  {
    int v,c;
    scanf("%d%d",&v,&c);
    nn[v]=cnt;
    player[cnt]=0;
    colours[cnt]=c;
    cnt++;
  }
  for(int i=0;i<n1;i++)
  {
    int v,c;
    scanf("%d%d",&v,&c);
    nn[v]=cnt;
    player[cnt]=1;
    colours[cnt]=c;
    cnt++;
  }
  for(int i=0;i<m;i++)
  {
    int a,b;
    scanf("%d%d",&a,&b);
    G[nn[a]].push_back(nn[b]);
    G_rev[nn[b]].push_back(nn[a]);
  }
}
int main()
{
  read();
}
