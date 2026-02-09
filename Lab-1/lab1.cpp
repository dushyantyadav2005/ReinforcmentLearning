#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;


class TicTacToe{
    public:
vector<vector<int>>grid;
int current=-1;

  TicTacToe()
  {
    grid.resize(3,vector<int>(3,0));
    current=1;
  }
bool winner(int cc)
{
    for(int i=0;i<3;i++)
    {
        if(grid[i][0]==grid[i][1]&&grid[i][2]==grid[i][1]&&grid[i][0]==cc)
        {
           return true;
        }
        if(grid[0][i]==grid[1][i]&&grid[2][i]==grid[1][i]&&grid[0][i]==cc)
        {
           return true;
        }
    }

    if(grid[0][0]==grid[1][1]&&grid[2][2]==grid[1][1]&&grid[0][0]==cc)
        {
           return true;
        }
    if(grid[2][0]==grid[1][1]&&grid[0][2]==grid[1][1]&&grid[0][2]==cc)
        {
           return true;
        }

        return false;

}


void play(int x,int y)
{
    // if(current==1){
    grid[x][y]=current;
    current=-1*current;
    // }
}

bool isTerminal()
{

    if(winner(-1)||winner(1))
    {
        return true;
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[i][j]==0)
            {
                return false;
            }
        }
    }
    return true;
}


vector<vector<int>> legalAction()
{
    vector<vector<int>>emptyState;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[i][j]==0)
            {
                emptyState.push_back({i,j});
            }
        }
    }
}

int outComeFor(int cc)
{
    if(winner(cc))
    {
        return 1;
    }else if(winner(-1*cc))
    {
        return -1;
    }
    return 0;
}

vector<vector<int>> encodeForPlayer(int cc)
{
    vector<vector<int>>state(3,vector<int>(3));
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            state[i][j]=grid[i][j]*cc;
        }
    }
    return state;
}
};


class rLAgentgreedy{
    public:
    TicTacToe*tt;
    vector<vector<double>>prob;
    double learning_rate;
    double ep;
    int epos;

    vector<vector<vector<int>>>states;
    rLAgentgreedy(vector<vector<double>>&ip)
    {
          prob=ip;
          tt=new TicTacToe();
          srand(time(0));
          learning_rate=0.1;
          ep=0.1;
          epos=1000;
    }


    void train()
    {
        // int current=1;
        for(int i=0;i<epos;i++)
        {
            vector<int>state=StateChoose();
          
             tt->play(state[0],state[1]);

             states.push_back(tt->grid);
             if(tt->isTerminal()){
             if(tt->winner(tt->current))
             {
                  update(1);
             }else if(tt->winner(-1*tt->current))
             {
                  update(-1);
             }else{
                   update(0);
             }
             break;
            }
        }


        for(int i=0;i<states.size();i++)
        {
            for(int r=0;r<3;r++)
            {
                for(int q=0;q<3;q++)
                {
                    cout<<states[i][r][q]<<" ";
                }cout<<"\n";

            }
        }
    }

    void update(int number)
    {
        vector<vector<int>>currentFilled;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(tt->grid[i][j]==tt->current)
                {
                    currentFilled.push_back({i,j});
                }
            }
        }

        for(int i=0;i<currentFilled.size();i++)
        {
            prob[currentFilled[i][0]][currentFilled[i][1]]+=learning_rate*number;
        }
    }

    bool explore()
    {
        return (double)rand()/RAND_MAX<=ep;
    }
    bool randomNumber(int x)
    {
        return rand()%x;
    }

    vector<int> StateChoose()
    {
        vector<vector<int>>empty=tt->legalAction();
            vector<pair<double,pair<int,int>>>winProb;
            for(int r=0;r<empty.size();r++)
            {
                winProb.push_back({prob[empty[r][0]][empty[r][1]],{empty[r][0],empty[r][1]}});
            }
               sort(winProb.begin(),winProb.end());

               if(tt->current==-1||!explore())
               {
                return {winProb[0].second.first,winProb[0].second.second};
               }
                int l=randomNumber(winProb.size());
               return {winProb[l].second.first,winProb[l].second.second};
    }
};


int main(){
   
    vector<vector<double>>initialProbablity(3,vector<double>(3,0.5));
    rLAgentgreedy* rl=new rLAgentgreedy(initialProbablity);
    rl->train();





    

}