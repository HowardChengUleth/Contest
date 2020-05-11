#include <stdio.h>

int read_guess(int *guess, int N)
{
  int i;
  int done = 1;

  for (i = 0; i < N; i++) {
    scanf("%d", guess+i);
    if (guess[i] != 0) {
      done = 0;
    }
  }
  return !done;
}

void process(int *secret, int *guess, int N)
{
  int strong, weak;
  int i;
  int freqs[10], freqg[10];

  strong = weak = 0;

  for (i = 0; i < 10; i++) {
    freqs[i] = freqg[i] = 0;
  }

  for (i = 0; i < N; i++) {
    if (secret[i] == guess[i]) {
      strong++;
    } else {
      freqs[secret[i]]++;
      freqg[guess[i]]++;
    }
  }
  
  for (i = 1; i <= 9; i++) {
    weak += (freqs[i] < freqg[i]) ? freqs[i] : freqg[i];
  }
  printf("    (%d,%d)\n", strong, weak);
}

int main(void)
{
  int N;
  int secret[1000], guess[1000];
  int i, game = 1;

  while (scanf("%d", &N) == 1 && N) {
    for (i = 0; i < N; i++) {
      scanf("%d", secret+i);
    }

    printf("Game %d:\n", game++);

    while (read_guess(guess, N)) {
      process(secret, guess, N);
    }
  }

  return 0;
}
