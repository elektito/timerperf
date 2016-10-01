#include <sys/time.h>
#include <time.h>
#include <stdio.h>

int
timeval_diff(struct timeval tv1, struct timeval tv2)
{
  if (tv1.tv_sec < tv2.tv_sec ||
      (tv1.tv_sec == tv2.tv_sec && tv1.tv_usec < tv2.tv_usec))
    return -1;

  if (tv1.tv_sec == tv2.tv_sec)
    return tv1.tv_usec - tv2.tv_usec;

  return (tv1.tv_sec - tv2.tv_sec) * 1000000 + (tv1.tv_usec - tv2.tv_usec);
}

int
main(int argc, char *argv[])
{
  const int N = 10000000;
  struct timeval before, after;
  struct timeval now;
  struct timespec nowspec;
  int i;
  float diff;

  fprintf(stderr, "Please wait a few moments...\n");

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    gettimeofday(&now, 0);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("gettimeofday: %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_REALTIME, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_REALTIME): %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_REALTIME_COARSE, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_REALTIME_COARSE): %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_MONOTONIC, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_MONOTONIC): %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_MONOTONIC_RAW): %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_BOOTTIME, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_BOOTTIME): %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_PROCESS_CPUTIME_ID): %f ns\n", diff / N * 1000);

  gettimeofday(&before, 0);
  for (i = 0; i < N; i++) {
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &nowspec);
  }
  gettimeofday(&after, 0);

  diff = timeval_diff(after, before);
  printf("clock_gettime (CLOCK_THREAD_CPUTIME_ID): %f ns\n", diff / N * 1000);

  return 0;
}
