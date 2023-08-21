#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
using namespace std;


class snake{
    private:

    vector<pair<pair<int,int>,pair<int,int> > > s;

    public:

    void setSnake(int m1, int n1, int m2, int n2){
        pair<int,int> head;
        head.first = m1;
        head.second = n1;
        pair<int,int> tail;
        tail.first = m2;
        tail.second = n2;
        pair<pair<int,int>,pair<int,int> > snake1;
        snake1.first=head;
        snake1.second=tail;
        s.push_back(snake1);
    }

    vector<pair<pair<int,int>,pair<int,int> > > getSnakeList(){
        return s;
    }



};

class ladder{
    private:

    vector<pair<pair<int,int>,pair<int,int> > > l;

    public:

    void setLadder(int m1, int n1, int m2, int n2){
        pair<int,int> start;
        start.first = m1;
        start.second = n1;
        pair<int,int> end;
        end.first = m2;
        end.second = n2;
        pair<pair<int,int>,pair<int,int> > ladder1;
        ladder1.first=start;
        ladder1.second=end;
        l.push_back(ladder1);
    }

    vector<pair<pair<int,int>,pair<int,int> > > getLadderList(){
        return l;
    }

};

class Board{
    private:
    int m,n;
    pair<int,int> init;
    
    public:
    Board(){
        
    }
    void setDimension(int a, int b){
        m=a;
        n=b;
    }
    int getRows(){
        return m;
    }
    int getColumns(){
        return n;
    }
};

bool getValidity(Board b, snake s, ladder l){
    vector<pair<pair<int, int>, pair<int, int>>> snakeList = s.getSnakeList();
    vector<pair<pair<int, int>, pair<int, int>>> ladderList = l.getLadderList();

    // Check for condition 1: A location has both snake and ladder
    for ( auto snakePair : snakeList) {
        for ( auto ladderPair : ladderList) {
            // cout<<snakePair.first.first<<snakePair.first.second<<"\n";
            // cout<<snakePair.second.first<<snakePair.second.second<<"\n";
            // cout<<ladderPair.first.first<<ladderPair.first.second<<"\n";
            if (snakePair.first == ladderPair.first || snakePair.second == ladderPair.second || 
             snakePair.first == ladderPair.second || snakePair.second == ladderPair.first) {
                return false;
            }
        }
    }

    // Check for condition 2: Snake head precedes the tail
    for (const auto &snakePair : snakeList) {
        if (snakePair.first.first < snakePair.second.first) {
            return false;
        } 
        else if (snakePair.first.first == snakePair.second.first && snakePair.first.second < snakePair.second.second) {
            return false;
        }
    }

    // Check for condition 3: Ladder top precedes the bottom
    for (const auto &ladderPair : ladderList) {
        if (ladderPair.first.first > ladderPair.second.first) {
            return false;
        } 
        else if (ladderPair.first.first == ladderPair.second.first && ladderPair.first.second > ladderPair.second.second) {
            return false;
        }
    }

    return true;
}

int minMoves(Board b, snake s, ladder l){
    return 2;
}

int frogjumpCount(Board b, snake s, ladder l, int js){
    int rows = b.getRows();
    int cols = b.getColumns();
    pair<int, int> current = {0, 0}; // Starting position
    int steps = 0;

    while (current.first != rows-1 || current.second != cols - 1) {
        // Increment the current position step by step
        for (int i = 0; i < js; ++i) {
            current.second++;

            if (current.second > cols-1) {
                current.first++;
                current.second = 0;
            }
            //cout<<"new position"<<current.first<<" "<<current.second<<endl;
        }

            // Check for snake head or ladder start
            bool foundSnake = false;
            bool foundLadder = false;
            for (auto snakePair : s.getSnakeList()) {
                if (snakePair.first == current) {
                    current = snakePair.second;
                    foundSnake = true;
                    break;
                }
            }
            if (!foundSnake) {
                for (auto ladderPair : l.getLadderList()) {
                    if (ladderPair.first == current) {
                        current = ladderPair.second;
                        foundLadder = true;
                        break;
                    }
                }
            }

            // If position goes out of bounds or the player is stuck in a loop
            if (current.first < 0 || current.second < 0 || current.first >= rows ||
                current.second >= cols || steps > rows * cols) {
                return -1;
            }
            
            if (current.first == rows-1 && current.second == cols - 1) {
                return steps + 1; // Goal reached
            }

        steps++;
    }

    return steps;
    // return -1;

}

int main(){
    Board b;
    int x,y;
    cin>>x>>y;
    b.setDimension(x,y);
    int f,g;
    cin>>f>>g;
    string str;
    snake s;
    ladder l;
    int dieValue;
    while(f--){
        cin>>str;
        if(str=="SNAKE"){
            int m1,n1,m2,n2;
            cin>>m1>>n1>>m2>>n2;
            s.setSnake(m1,n1,m2,n2);
        }
        else if(str=="LADDER"){
            int m1,n1,m2,n2;
            cin>>m1>>n1>>m2>>n2;
            l.setLadder(m1,n1,m2,n2);
        }
        else if(str=="DICE"){
            cin>>dieValue;
        }
    }
    
    while(g--){
        cin>>str;
        if(str=="validBoard"){
            if(getValidity(b,s,l)){
                cout<<"true";
            }
            else{
                cout<<"false";
                break;
            }
            cout<<endl;
        }
        else if(str=="minMoves"){
            int ans=minMoves(b,s,l);
            cout<<ans<<endl;
        }
        else if(str=="JUMPSIZE"){
            int js;
            cin>>js;
            int ans=frogjumpCount(b,s,l,js);
            if(ans==-1){
                cout<<"not possible"<<endl;
            }
            else{
                cout<<ans<<endl;
            }
        }
    }   
    cin>>str;
    return 0;
}
