// Caleb Stanberry
// OS Assignment #2
// Banker's Algorithm

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
int main()
{
    //Processes P0, P1, P2, P3, P4

    const int n = 5; //Number of processes
    const int m = 3; //Number of resources
    char ch = 0;
    char input;
    int result;

    int allocation[5][3];
    int max[5][3];
    int available[3];

    std::ifstream in;
    in.open("input.txt");

    
    if (in.fail())
        exit(1);

for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
        in >> allocation[i][j];
    }
}

for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
        in >> max[i][j];
    }
}

for (int i = 0; i < 3; i++) {
    in >> available[i];
}

    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++)
    {
        f[k] = 0;
    }

    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    
    int y = 0;
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        available[y] += allocation[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    //Checks if the sequence is safe or not
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            cout << "This sequence is not safe";
            break;
        }
    }

    if (flag == 1)
    {
        cout << "This is a safe Sequence:" << endl;
        for (int i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
    }

    return (0);
}
