#include <stdio.h>
#include <stdlib.h>

int main() {

  int beginning = 1;
  int gameisover = 0;
  int team1 = 0;
  int team2 = 0;

  while (beginning == 1) {

    int point = 0;

    printf("%d-%d\n", team1, team2);
    printf("Point: ");
    scanf("%d", &point);

    if (point == 1) {

      if (team1 == 0) {
        team1 += 15;
      } else if (team1 == 15) {
        team1 += 15;
      } else if (team1 == 30) {
        team1 += 10;
      } else if (team1 == 40) {
        printf("GAME: PLAYER 1\n");
        beginning = 0;
        gameisover = 1;
      }
    }

    if (point == 2) {

      if (team2 == 0) {
        team2 += 15;
      } else if (team2 == 15) {
        team2 += 15;
      } else if (team2 == 30) {
        team2 += 10;
      } else if (team2 == 40) {
        printf("GAME: PLAYER 2\n");
        beginning = 0;
        gameisover = 1;
      }
    }

    if (team1 == 40 && team2 == 40) {
      printf("DEUCE\n");
      beginning = 0;
    }
  }

  int team1_overtime = 0;
  int team2_overtime = 0;

  while (gameisover == 0) {
    int point = 0;

    printf("Point: ");
    scanf("%d", &point);

    if (point == 1) {
      team1_overtime++;
    }

    if (point == 2) {
      team2_overtime++;
    }

    if (team1_overtime == team2_overtime) {
      printf("DEUCE\n");
    }

    if (team1_overtime - 1 == team2_overtime) {
      printf("ADVANTAGE: PLAYER 1\n");
    }

    if (team1_overtime + 1 == team2_overtime) {
      printf("ADVANTAGE: PLAYER 2\n");
    }

    if (team1_overtime - 2 == team2_overtime) {
      printf("GAME: PLAYER 1\n");
      gameisover = 1;
    }

    if (team1_overtime + 2 == team2_overtime) {
      printf("GAME: PLAYER 2\n");
      gameisover = 1;
    }
  }

  if (gameisover == 1) {
    return 0;
  }
}