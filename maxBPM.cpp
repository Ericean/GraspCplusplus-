#include <iostream>
#include <cstring>
using namespace std;
const int M = 1000;
const int N = 1000;
const int NOMATCH = -1;

bool augment(bool Graph[M][N], int col, int u, bool visited[], int matched[])
{
	for (int v = 0; v < col; ++v) {
    //if current job u has already been assigned to some applicant u, then we recursively call augment on u to try a different 
    //candidate except the current one, here we use visited to keep track of the jobs we have explored to avoid loop
		if (Graph[u][v] && !visited[v]) {
			visited[v] = true;
			if (matched[v] == NOMATCH  || augment(Graph, col, matched[v], visited, matched)) {
				matched[v] = u;
				return true;
			}

		}
	}
	return false;
}

int maxBPM(bool Graph[M][N], int row, int col){

	int matched[N];
	memset(matched, NOMATCH, sizeof(matched));

	int result =0;
	for(int u=0; u< row; u++)
	{
		bool visited[N];
		memset(visited, false, sizeof(visited));
		if(augment(Graph, col, u, visited, matched)){
			result+=1;
		}
	}
	return result;
}


int main(int argc, char const *argv[])
{
	bool bpGraph[M][N] = {  {0, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1}
                      };
     cout << "Maximum number of applicants that can get job is "
         << maxBPM(bpGraph, 6, 6);
	return 0;
}
