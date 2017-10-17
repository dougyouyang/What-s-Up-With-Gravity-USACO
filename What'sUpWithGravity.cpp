//  Copyright © 2017 Dougy Ouyang. All rights reserved.

#include <iostream>
#include <queue>

using namespace std;
char mat[502][502];
int step[502][502], n, m;

int good(int x, int y)
{
    if(mat[x][y]!='.')
        return 0;
    return 1;
}

int fall(int x, int y, int gravity, int s)
{
    if(mat[x][y]!='.')
        return x;
    if(gravity){
        while(mat[x-1][y]=='.')
            step[x][y]=min(step[x][y], s), x--;
        if(mat[x-1][y]==' ')
            return 0;
        return x;
    }
    else{
        while(mat[x+1][y]=='.')
            step[x][y]=min(step[x][y], s), x++;
        if(mat[x+1][y]==' ')
            return 0;
        return x;
    }
}

int main()
{
    queue<int> x, y, steps, gravity;
    int cx, cy, dx, dy;
    int i, j;
    for(i=0;i<=501;i++)
        for(j=0;j<=501;j++)
            mat[i][j]=' ', step[i][j]=1000000000;
    
    cin >> n >> m;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            cin >> mat[i][j];
            if(mat[i][j]=='C')
                cx=i, cy=j, mat[i][j]='.';
            if(mat[i][j]=='D')
                dx=i, dy=j, mat[i][j]='.';
        }
    x.push(fall(cx, cy, 0, 1)), y.push(cy), steps.push(1), gravity.push(0);
    if(mat[x.front()][y.front()]!='.'){
        cout << -1 << endl;
        return 0;
    }
    
    while(!x.empty()){
        int curx=x.front(), cury=y.front(), s=steps.front(), g=gravity.front(), xx, yy;
        x.pop(), y.pop(), steps.pop(), gravity.pop();
        step[xx][yy]=s;
        //go right
        yy=cury+1, xx=fall(curx, yy, g, s);
        while(good(xx, yy)){
            if(s<step[xx][yy])
                step[xx][yy]=s, x.push(xx), y.push(yy), steps.push(s), gravity.push(g);
            xx=fall(xx, yy+1, g, s), yy++;
        }
        //go left
        yy=cury-1, xx=fall(curx, yy, g, s);
        while(good(xx, yy)){
            if(s<step[xx][yy])
                step[xx][yy]=s, x.push(xx), y.push(yy), steps.push(s), gravity.push(g);
            xx=fall(xx, yy-1, g, s), yy--;
        }
        g=1-g, s++;
        curx=fall(curx, cury, g, s);
        step[curx][cury]=min(step[curx][cury], s);
        //go right
        yy=cury+1, xx=fall(curx, yy, g, s);
        while(good(xx, yy)){
            if(s<step[xx][yy])
                step[xx][yy]=s, x.push(xx), y.push(yy), steps.push(s), gravity.push(g);
            xx=fall(xx, yy+1, g, s), yy++;
        }
        //go left
        yy=cury-1, xx=fall(curx, yy, g, s);
        while(good(xx, yy)){
            if(s<step[xx][yy])
                step[xx][yy]=s, x.push(xx), y.push(yy), steps.push(s), gravity.push(g);
            xx=fall(xx, yy-1, g, s), yy--;
        }
    }
    
    if(step[dx][dy]!=1000000000)
        cout << step[dx][dy]-1 << endl;
    else
        cout << -1 << endl;
    
    return 0;
}
