#include<cstdio>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<utility>
#include<tuple>

std::vector<std::vector<int> > G_or,G_rev;
std::vector<bool> player;
using subgraph=std::unordered_set<int>;
using vertices=subgraph;
subgraph operator-(const subgraph &a, const subgraph &b)
{
  subgraph res;
  for (int e:a)
  {
    if(b.count(e)==0)
      res.insert(e);
  }
  return std::move(res);
}
subgraph operator+(const subgraph &a, const subgraph &b)
{
  subgraph res;
  for (int e:a)
  {
    res.insert(e);
  }
  for (int e:b)
  {
    res.insert(e);
  }
  return std::move(res);
}
std::vector<unsigned char>colours;
int n,n0,n1,m,V;
void read()
{
  scanf("%d%d%d",&n0,&n1,&m);
  n=n0+n1;
  G_or.resize(n);
  G_rev.resize(n);
  colours.resize(n);
  player.resize(n);
  for(int i=0;i<n0;i++)
  {
    int v,c;
    scanf("%d%d",&v,&c);
    //nn[v]=cnt;
    player[v]=0;
    colours[v]=c;
  }
  for(int i=0;i<n1;i++)
  {
    int v,c;
    scanf("%d%d",&v,&c);
    player[v]=1;
    colours[v]=c;
  }
  for(int i=0;i<m;i++)
  {
    int a,b;
    scanf("%d%d",&a,&b);
    G_or[a].push_back(b);
    G_rev[b].push_back(a);
  }
  scanf("%d",&V);
}
bool implies(bool a,bool b)
{
  return !a || b;
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
      if(player[e]==cur_player and std::any_of(G_or[e].begin(),G_or[e].end(),[res,G](int x){return G.count(x)==1 && res.count(x)==1;}))
      {
        res.insert(e);
        cont=true;
      }
      if(player[e]!=cur_player and std::all_of(G_or[e].begin(),G_or[e].end(),[res,G](int x){return implies(G.count(x)==1,res.count(x)==1);}))
      {
        res.insert(e);
        cont=true;
      }
    }
  }
  return std::move(res);
}
std::tuple<vertices,vertices> solve(const subgraph& G)
//returns winning set for player 0,winning set for player 2 on graph G
//https://arxiv.org/pdf/1307.4465.pdf
{
  if(G.size()==0)return make_tuple(vertices(),vertices());
  //kopniety kwadrat 0
  //zwykly   kwadrat 1

  unsigned char max_prio=0;
  for(int e:G)
  {
    max_prio=std::max(max_prio,colours[e]);
  }
  unsigned int p=max_prio %2;
  vertices U;
  for(int e:G)
    if(colours[e]==max_prio)
      U.insert(e);

  vertices A=attr(G,U,p);
  vertices W [2];
  vertices Wp[2];
  std::tie(Wp[0],Wp[1])=solve(G-A);
  if( Wp[1-p].size()==0)
  {
    W[p]=A+Wp[p];
    W[1-p]=vertices();
  }
  else
  {
    vertices B=attr(G,Wp[1-p],1-p);
    std::tie(Wp[0],Wp[1])=solve(G-B);
    W[p]=Wp[p];
    W[1-p]=Wp[1-p]+B;
  }
  /*
  fprintf(stderr,"For vertices: ");
  for(int e:G)
    fprintf(stderr,"%d ",e);
  fprintf(stderr,"\nPlayer 0 wins on:");
  for(int e:W[0])
    fprintf(stderr,"%d ",e);
  fprintf(stderr,"\nPlayer 1 wins on:");
  for(int e:W[1])
    fprintf(stderr,"%d ",e);
  fprintf(stderr,"\n\n");
  */
  return std::move(make_tuple(W[0],W[1]));

}
int main()
{
  read();
  subgraph full;
  for (int i=0;i<n;i++)
    full.insert(i);
  vertices p0=std::get<0>(solve(full));
  
  if(p0.count(V)==1)
    printf("0\n");
  else
    printf("1\n");
}
