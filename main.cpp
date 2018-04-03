#include<cstdio>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>

std::unordered_map<int,int> nn;//new numbers
std::vector<std::vector<int> > G_or,G_rev;
std::vector<bool> player;
using subgraph=std::unordered_set<int>;
std::vector<unsigned char>colours;
int n,n0,n1,m,V;
void read()
{
  scanf("%d%d%d",&n0,&n1,&m);
  n=n0+n1;
  G_or.resize(n);
  G_rev.resize(n);
  colours.resize(n);
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
    G_or[nn[a]].push_back(nn[b]);
    G_rev[nn[b]].push_back(nn[a]);
  }
}
subgraph attr(const subgraph &G, const subgraph &U, int cur_player)
{
  bool cont=true;
  subgraph res=U;
  while(cont)
  {
    cont=false;
    for(int e:G)
    {
      if(res.count(e))continue;
      if(player[e]==cur_player and std::any_of(G_or[e].begin(),G_or[e].end(),[U](int x){return U.count(x);}))
      {
        res.insert(e);
        cont=true;
      }
      else if(player[e]!=cur_player and std::all_of(G_or[e].begin(),G_or[e].end(),[U](int x){return U.count(x);}))
      {
        res.insert(e);
        cont=true;
      }
    }
  }
  return res;
}
int main()
{
  read();
}
