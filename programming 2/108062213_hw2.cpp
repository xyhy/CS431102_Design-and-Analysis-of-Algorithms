#include<iostream>
#include<cstdlib>
#include<queue>
#include<vector>
#include<utility>
#include<climits>
#include<cstring>
#include<algorithm>

#define N 31

struct Node{
    int level;
    int vertex_num;
    int lower_bound;
    int matrix[N][N];
    std::vector< std::pair<int,int> > path;
};

struct compare{
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->lower_bound > rhs->lower_bound;
    }
};


Node* createnode(int level, int i, int j, std::vector<std::pair<int,int> > const& path, int parentMat[N][N]);
void solve(int mat[N][N]);
void print(std::vector<std::pair<int,int> > const &path);
void colReduction(int mat[N][N], int col[N]);
void rowReduction(int mat[N][N], int row[N]);
int cal(int mat[N][N]);

Node *ans;
int n = 0;
int minlength = INT_MAX;

int main(){
    int origin_matrix[N][N] = {0};
    std::cin>>n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cin>>origin_matrix[i][j];
            if(origin_matrix[i][j] == 0){
                origin_matrix[i][j] = INT_MAX;
            }
        }
    }

    solve(origin_matrix);
    std::cout<<minlength<<std::endl;
    print(ans->path);

    return 0;
}




Node* createnode(int level, int parent, int child, std::vector<std::pair<int,int> > const& path, int parentMat[N][N]){
    Node *newNode = new Node;
    newNode->path = path;
    newNode->level = level;
    newNode->vertex_num = child;

    
    if(level != 0){
        newNode->path.push_back(std::make_pair(parent, child));
    }

    memcpy(newNode->matrix, parentMat, sizeof(newNode->matrix));

    for(int i = 0; level!=0 && i<n; i++){
        newNode->matrix[parent][i] = INT_MAX;
        newNode->matrix[i][child] = INT_MAX;
    }

    newNode->matrix[child][0] = INT_MAX;

    return newNode;
}

void solve(int mat[N][N]){
    std::priority_queue <Node*, std::vector<Node*>, compare> pq;
    std::vector < std::pair<int, int> > v;

    Node *root = createnode(0, -1, 0, v, mat);
    root->lower_bound = cal(root->matrix);
    pq.push(root);

    while (!pq.empty()){
        Node* cur = pq.top();
        pq.pop();

        int index = cur->vertex_num;
        if(cur->lower_bound < minlength){
            for (int j = 0; j < n; j++){
                if (cur->matrix[index][j] != INT_MAX){
                    Node* u = createnode(cur->level+1, index, j, cur->path, cur->matrix);
                    if (u->level == n - 1){
                        u->path.push_back(std::make_pair(u->vertex_num, 0));
                        u->lower_bound = cur->lower_bound + cur->matrix[index][j] + cal(u->matrix);
                        if(u->lower_bound < minlength){
                            ans = u;
                            minlength = u->lower_bound;
                        }
                    }else{
                        u->lower_bound = cur->lower_bound + cur->matrix[index][j] + cal(u->matrix);
                        if(u->lower_bound < minlength){
                            pq.push(u);
                        }
                    } 
                }
            }
        }

        delete cur;
    }
    // return ans->lower_bound;
}

void colReduction(int mat[N][N], int col[N]){
    std::fill_n(col, n, INT_MAX);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j] < col[j]){
                col[j] = mat[i][j];
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j]!=INT_MAX && col[j]!=INT_MAX){
                mat[i][j] -= col[j];
            }
        }
    }
}

void rowReduction(int mat[N][N], int row[N]){
    std::fill_n(row, n, INT_MAX);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j] < row[i]){
                row[i] = mat[i][j];
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j]!=INT_MAX && row[i]!=INT_MAX){
                mat[i][j] -= row[i];
            }
        }
    }
}

int cal(int mat[N][N]){
    int lower_cost = 0;

    int col[n], row[n];
    rowReduction(mat, row);
    colReduction(mat, col);

    for (int i = 0; i < n; i++){
        lower_cost += (row[i] != INT_MAX) ? row[i] : 0,
        lower_cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    return lower_cost;
}



void print(std::vector<std::pair<int,int> > const &path){
    int i = 0;
    for(i = 0; i < path.size()-1; i++){
        std::cout<<path[i].first+1<<" ";
    }
    std::cout<<path[i].first<<std::endl;
}