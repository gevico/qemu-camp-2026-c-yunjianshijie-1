#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

// 记录路径
int path[MAX_ROW][MAX_COL] = {0};

int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dfs(int x, int y)
{
	// 终点
	if ( x == MAX_ROW -1 && y == MAX_COL -1 ) {
		path[x][y] = 1;
		return 1;
	}

	// 是否越界
	if( x < 0 || x >= MAX_ROW || y < 0 || y >= MAX_COL){
		return 0;
	}

	// 标记当前位置 
	path[x][y] = 1;

	// 遍历四个方向
	for( int i = 0 ;i< 4;i++){
		int new_x = x + dir[i][0];
		int new_y = y + dir[i][1];
		// 是否是墙或者已经访问过
		if( new_x < 0 || new_x >= MAX_ROW || new_y < 0 || new_y >= MAX_COL || maze[new_x][new_y] == 1 || path[new_x][new_y] == 1){
			continue;
		}
		if(dfs(new_x, new_y)){
			return 1;
		}
	}

	// 回退
	path[x][y] = 0;
	return 0;
}



int main(void)
{
	// TODO: 在这里添加你的代码
    // I AM NOT DONE
	if(dfs(0, 0)){
		 for (int i = 0; i < MAX_ROW; i++) {
            for (int j = 0; j < MAX_COL; j++) {
                printf("%d ", path[i][j]);
            }
            printf("\n");
        }
	}else{
		printf("没有找到路径\n");
	}
    return 0;
}