#include <stdio.h>
#ifdef _WIN32
#include <windows.h>

void get_memory_usage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG total = memInfo.ullTotalPhys / (1024 * 1024);
    DWORDLONG used = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024);

    printf("Memory Usage: %llu MB / %llu MB\n", used, total);
}

void get_cpu_usage() {
    FILETIME idleTime, kernelTime, userTime;
    FILETIME prevIdleTime, prevKernelTime, prevUserTime;

    GetSystemTimes(&prevIdleTime, &prevKernelTime, &prevUserTime);
    Sleep(1000); // wait 1 second
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    ULONGLONG idleDiff =
        (((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime) -
        (((ULONGLONG)prevIdleTime.dwHighDateTime << 32) | prevIdleTime.dwLowDateTime);

    ULONGLONG kernelDiff =
        (((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime) -
        (((ULONGLONG)prevKernelTime.dwHighDateTime << 32) | prevKernelTime.dwLowDateTime);

    ULONGLONG userDiff =
        (((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime) -
        (((ULONGLONG)prevUserTime.dwHighDateTime << 32) | prevUserTime.dwLowDateTime);

    ULONGLONG total = kernelDiff + userDiff;
    float cpuUsage = 100.0f * (1.0f - ((float)idleDiff / (float)total));

    printf("CPU Usage: %.2f%%\n", cpuUsage);
}
#else
#include <stdlib.h>
#include <string.h>

void get_memory_usage() {
    FILE* file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    long total_mem, free_mem;
    fscanf(file, "MemTotal: %ld kB\nMemFree: %ld kB", &total_mem, &free_mem);
    fclose(file);

    long used_mem = total_mem - free_mem;
    printf("Memory Usage: %ld MB / %ld MB\n", used_mem / 1024, total_mem / 1024);
}

void get_cpu_usage() {
    FILE* file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Failed to open /proc/stat");
        return;
    }

    long user, nice, system, idle;
    fscanf(file, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);
    fclose(file);

    long total = user + nice + system + idle;
    float cpu_usage = 100.0 * (total - idle) / total;

    printf("CPU Usage Estimate: %.2f%%\n", cpu_usage);
}
#endif

int main() {
    printf("Cross-Platform System Resource Monitor\n");
    get_cpu_usage();
    get_memory_usage();
    return 0;
}
