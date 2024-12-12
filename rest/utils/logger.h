#include <ctime>
#include <cstdio>

#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"
#define RED_COLOR "\033[31m"
#define YELLOW_COLOR "\033[33m"

#define Log(Level, Color, Arg, ...)                                                      \
    do {                                                                                \
        time_t now = time(nullptr);                                                    \
        struct tm timeInfo;                                                            \
        localtime_s(&timeInfo, &now);                                                  \
        char timestamp[20];                                                            \
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeInfo);        \
        printf("%s %s%s" RESET_COLOR " | " Arg "\n", timestamp, Color, Level, __VA_ARGS__); \
    } while (0)

#define LogInfo(Arg, ...) Log("INFO", GREEN_COLOR, Arg, ##__VA_ARGS__)
#define LogError(Arg, ...) Log("ERROR", RED_COLOR, Arg, ##__VA_ARGS__)
#define LogWarning(Arg, ...) Log("WARNING", YELLOW_COLOR, Arg, ##__VA_ARGS__)