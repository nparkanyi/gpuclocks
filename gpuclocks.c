//run as root, or setuid'd
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int notify;

void do_notify(const char *str)
{
	if (notify) {
		char outbuf[100] = "notify-send \"";
		strcat(outbuf, str);
		strcat(outbuf, "\"");
		system(outbuf);
	} else {
		puts(str);
	}
}

int main(int argc, char **argv)
{
	if ((argc == 2) && (strcmp(argv[1], "-n") == 0)) {
		notify = 1;
	}

	FILE *f = fopen("/sys/class/drm/card0/device/power_profile", "r");
	if (!f) { return 1; }
	char level[10];
	fscanf(f, "%s", level);
	fclose(f);

	//sysfs entries don't seem to like having rw together
	f = fopen("/sys/class/drm/card0/device/power_profile", "w");
	if (!f) { return 2; }

	if (strcmp(level, "low") == 0 || strcmp(level, "default") == 0) {
		fprintf(f, "mid\n");
		do_notify("GPU: mid\n");
	} else if (strcmp(level, "mid") == 0){
		fprintf(f, "high\n");
		do_notify("GPU: high\n");
	} else if (strcmp(level, "high") == 0) {
		fprintf(f, "low\n");
		do_notify("GPU: low\n");
	}
	fclose(f);
	return 0;
}
