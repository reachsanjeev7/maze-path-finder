#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char maze[10][10] = {0};
int r, c;
int srow, scol;
int error_check(int *s_and_d)
{
	int i, j;
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
				s_and_d[0] = i;
				s_and_d[1] = j;
			} else if (maze[i][j] == 'G') {
				d++;
				s_and_d[2] = i;
				s_and_d[3] = j;
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
int check(int dir, int row, int col)
{
	int ret;
	int up = 1;
	int down = 2;
	int left = 3;
	int right = 4;

	if (dir == up)
		ret = find(row - 1, col);
	else if (dir == down)
		ret = find(row + 1, col);
	else if (dir == left)
		ret = find(row, col - 1);
	else if (dir == right)
		ret = find(row, col + 1);
	return ret;
}
int find(int row, int col)
{
	if (maze[row][col] == '.')
		return 1;
	else if (maze[row][col] == '#')
		return -1;
	else if (maze[row][col] == 'G')
		return 5;
}
void maze_display(void)
{
	int i, j;

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++)
			printf("%c", maze[i][j]);
	printf("\n");
	}
}
int retracing(int *p_pos, int *v_row, int *v_col, int v_pos)
{
	if (p_pos[0] == srow && p_pos[1] == scol)
		return -1;
	printf("*************retracing***********\n");
	maze[p_pos[0]][p_pos[1]] = '-';
	maze[v_row[v_pos]][v_col[v_pos]] = '.';
	p_pos[0] = v_row[v_pos];
	p_pos[1] = v_col[v_pos];
}
int check_direction(int dir, int *p_pos)
{
	int up = 1;
	int down = 2;
	int left = 3;
	int right = 4;
	int ret;

	if (dir == right) {
		ret = check(right, p_pos[0], p_pos[1]);
		if (ret == 1) {
			p_pos[1] = p_pos[1] + 1;
			return 1;
		} else if (ret == 5) {
			return 5;
		}
	} else if (dir == down) {
		ret = check(down, p_pos[0], p_pos[1]);
		if (ret == 1) {
			p_pos[0] = p_pos[0] + 1;
			return 1;
		} else if (ret == 5) {
			return 5;
		}
	} else if (dir == left) {
		ret = check(left, p_pos[0], p_pos[1]);
		if (ret == 1) {
			p_pos[1] = p_pos[1] - 1;
			return 1;
		} else if (ret == 5) {
			return 5;
		}
	} else if (dir == up) {
		ret = check(up, p_pos[0], p_pos[1]);
		if (ret == 1) {
			p_pos[0] = p_pos[0] - 1;
			return 1;
		} else if (ret == 5) {
			return 5;
		}
	}
}
int main(void)
{
	int i, j, drow, dcol;
	int s_and_d[4];
	int ret;
	int p_pos[2];
	int up = 1;
	int down = 2;
	int left = 3;
	int right = 4;
	int v_row[30];
	int v_col[30];
	int v_pos = 0;
	int re;

	printf("number of rows and columns\n");
	scanf("%d %d", &r, &c);
	printf("# - Wall\n. - Path\nS - Start\nG - End\n");
	printf("- Enter only above characters in maze\n");
	printf("- Enter only 1 start and 1 stop\n");
	printf("enter %d rows of size %d\n", r, c);
	for (i = 1; i <= r; i++)
		scanf("%s", maze[i]);
	for (i = 1; i <= r; i++) {
		for (j = c; j >= 0; j--)
			maze[i][j + 1] = maze[i][j];
	}
	printf("----entered maze is----\n");
	maze_display();
	ret = error_check(s_and_d);
	if (ret == -1)
		return 0;
	srow = s_and_d[0];
	scol = s_and_d[1];
	drow = s_and_d[2];
	dcol = s_and_d[3];
	p_pos[0] = srow;
	p_pos[1] = scol;
	while (1) {
		sleep(1);
		system("clear");
		printf("%d %d\n", p_pos[0], p_pos[1]);
		maze[p_pos[0]][p_pos[1]] = '+';
		v_row[v_pos] = p_pos[0];
		v_col[v_pos++] = p_pos[1];
		maze_display();
		if (p_pos[0] == 1 && p_pos[1] == 1) {
			ret = check_direction(right, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(down, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		} else if (p_pos[1] == r && p_pos[1] == c) {
			ret = check_direction(left, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(up, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		} else if (p_pos[0] == 1) {
			ret = check_direction(left, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(right, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(down, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		} else if (p_pos[1] == 1) {
			ret = check_direction(up, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(right, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(down, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		} else if (p_pos[0] == r) {
			ret = check_direction(up, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(right, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(left, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		} else if (p_pos[1] == c) {
			ret = check_direction(down, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(left, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(up, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		} else {
			ret = check_direction(left, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(right, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(down, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			ret = check_direction(up, p_pos);
			if (ret == 1)
				continue;
			else if (ret == 5)
				break;
			v_pos = v_pos-2;
			re = retracing(p_pos, v_row, v_col, v_pos);
			if (re == -1) {
				printf("no path found\n");
				break;
			}
		}
	}
	system("clear");
	maze[srow][scol] = 'S';
	maze_display();
}
