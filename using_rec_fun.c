#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char maze[10][10] = {0};
int r;
int c;

int error_check(int *s_n_d)
{
	int i;
	int j;
	int s = 0;
	int d = 0;

	for (i = 1; i <= r; i++) {
		if (strlen(maze[i]) < c)
			break;
	}
	if (i < r+1) {
		printf("maze length error\n");
		return -1;
	}
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (maze[i][j] == 'S') {
				s++;
				s_n_d[0] = i;
				s_n_d[1] = j;
			} else if (maze[i][j] == 'G') {
				d++;
				s_n_d[2] = i;
				s_n_d[3] = j;
			} else if (!(maze[i][j] == '.' || maze[i][j] == '#')) {
				printf("unknown character in maze\n");
				return -1;
			}
		}
	}
	if (s != 1 || d != 1) {
		printf("start and destination error\n");
		return -1;
	}
}
void maze_display(void)
{
	int i;
	int j;

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++)
			printf("%c", maze[i][j]);
		printf("\n");
	}
	printf("\n");
}
int outside_maze(int row, int col)
{
	if (row < 1 || row > r || col < 1 || col > c)
		return 1;
	else
		return 0;
}
int goal(int row, int col)
{
	if (maze[row][col] == 'G')
		return 1;
	else
		return 0;
}
int not_open(int row, int col)
{
	if (maze[row][col] == 'S' || maze[row][col] == '.')
		return 0;
	else if (maze[row][col] == '#')
		return 1;
}
int find_path(int row, int col)
{
	if (outside_maze(row, col))
		return -1;
	if (goal(row, col))
		return 1;
	if (not_open(row, col))
		return -1;
	maze[row][col] = '+';
	if (find_path(row, col-1) == 1)
		return 1;
	if (find_path(row+1, col) == 1)
		return 1;
	if (find_path(row, col+1) == 1)
		return 1;
	if (find_path(row-1, col) == 1)
		return 1;
	maze[row][col] = '.';
	return -1;
}

int main(void)
{
	int i;
	int j;
	int srow;
	int scol;
	int drow;
	int dcol;
	int s_n_d[4];
	int ret;

	printf("number of rows and columns\n");
	scanf("%d %d", &r, &c);
	printf("# - Wall\n. - Path\nS - Start\nG - End\n");
	printf("- Enter only above characters in maze\n");
	printf("- Enter only 1 start and 1 stop\n");
	printf("enter %d rows of size %d\n", r, c);
	for (i = 1; i <= r; i++)
		scanf("%s", maze[i]);
	for (i = 1; i <= r; i++)
		for (j = c; j >= 0; j--)
			maze[i][j+1] = maze[i][j];
	printf("----entered maze is----\n");
	maze_display();
	ret = error_check(s_n_d);
	if (ret == -1)
		return 1;
	srow = s_n_d[0];
	scol = s_n_d[1];
	drow = s_n_d[2];
	dcol = s_n_d[3];
	ret = find_path(srow, scol);
	maze[srow][scol] = 'S';
	printf("****************\n");
	maze_display();
	if (ret == -1)
		printf("no path found\n");
	return 0;
}
