#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main() {

  time_t rawtime;
  struct tm *info;
  char buffer[80];

  // GET CURRENT TIME AND STORE IN rawtime.
  time(&rawtime);
  // STORE LOCAL TIME INFO INTO info STRUCT.
  info = localtime(&rawtime);
  // POINTER FOR BackupTime VARIABLE.
  char *backupTime = getenv("BackupTime");

  printf("\n\nMontreal Time: %2d:%02d:%d\n", (info->tm_hour)%24, info->tm_min, info->tm_sec);

  // FORMAT CURRENT TIME AND STORE IT IN buffer.
  strftime(buffer, sizeof(buffer), "%H:%M", info);

  while(1){
    while((strcmp(backupTime, buffer))) {
      // SLEEP FOR 1 MINUTE BEFORE GOING THROUGH LOOP AGAIN.
      sleep(60);

      // REFRESH BUFFER EVERY TIME THROUGH THE LOOP AND COMPARE WITH backupTime UNTIL
      // THEY ARE EQUAL TO EACH OTHER.
      time(&rawtime);
      info = localtime(&rawtime);
      printf("\n\nMontreal Time: %2d:%02d:%d\n", (info->tm_hour)%24, info->tm_min, info->tm_sec);
      strftime(buffer, sizeof(buffer), "%H:%M", info);
    }

    // ONCE OUT OF LOOP, WE PERFORM THE BACKUP
    system("cp $BackupSource/* $BackupDestination");
    printf("All files have been backed up!\n");

    // ONCE WE BACKED UP ONCE, WE SLEEP FOR ANOTHER 60 SECONDS TO MAKE SURE
    // WE DON'T CONTINUOUSLY COPY NON STOP FOR A FULL MINUTE.
    sleep(60);

    // REFRESH BUFFER WITH UPDATED TIME.
    time(&rawtime);
    info = localtime(&rawtime);
    printf("\n\nMontreal Time: %2d:%02d:%d\n", (info->tm_hour)%24, info->tm_min, info->tm_sec);
    strftime(buffer, sizeof(buffer), "%H:%M", info);

    printf("JUST SLEPT FOR 60 SECONDS!!\n\n");
  }
  

  return(0);

}
