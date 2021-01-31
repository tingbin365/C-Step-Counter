// #include "gtest/gtest.h"
// TEST(GreetingShould, ReturnHelloWorld)
// {
//     // Greeting *greet = new Greeting();
//     // std::string actual = greet->getGreetingMessage();
//     // std::string expected = "Hello World!";
//     // EXPECT_EQ(expected, actual);
// }
#ifdef __cplusplus
extern "C"
{
#endif

#define DEBUG
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "StepCountingAlgo.h"
#include "scoringStage.h"
#include "detectionStage.h"
#include "postProcessingStage.h"
#define PATH "__main__/tests/data/abc.txt" //package/label

#ifdef __cplusplus
}
#endif

#include "tools/cpp/runfiles/runfiles.h" // 一定要放在extern "C" 外面
#include <memory>

using bazel::tools::cpp::runfiles::Runfiles;

static int correct_answer = 240;

int32_t getline(FILE *stream, char *buf, size_t size)
{
    int32_t count = -1;
    char c;

    while (!feof(stream) && (c = (char)getc(stream)) != '\n' && count < (int32_t)(size - 1))
    {
        buf[++count] = c;
    }
    if (count > 0)
    {
        buf[++count] = '\0';
    }
    //printf("count=%d\n", count);
    return count;
}
//return word ending position ,for example : "a,b", line[1]==',' return  1, word can copy memcpy(line,begin,return-begin)
// int32_t getword(char *buf, size_t begin, size_t end)
// {
//     int32_t pos = -1;
//     for (int i = begin; i < end; i++)
//     {
//         pos = i;
//         if (buf[i] > '0' && buf[i] < '9')
//         {
//         }
//         else
//         {
//             break;
//         }
//     }
//     return pos;
// }

static void runAlgo(void)
{
    char linep[1024];
    size_t len = 1024;
    size_t read;
    std::string error;
    std::unique_ptr<Runfiles> runfiles(Runfiles::CreateForTest(&error));

    // Important:
    //   If this is a test, use Runfiles::CreateForTest(&error).
    //   Otherwise, if you don't have the value for argv[0] for whatever
    //   reason, then use Runfiles::Create(&error).

    if (runfiles == nullptr)
    {
        printf("Error loading runfiles configuration.%s\n", error.c_str());
    }
    std::string path =
        runfiles->Rlocation(PATH);

    //printf("open file: %s\n", PATH);
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL)
    {
        printf("Error while opening the file.%s\n", PATH);
        exit(EXIT_FAILURE);
    }
    while ((read = getline(fp, linep, len)) > 0)
    {
        char *sep_location = NULL;
        long time = strtol(linep, &sep_location, 10);
        long x = strtol(sep_location + 1, &sep_location, 10);
        long y = strtol(sep_location + 1, &sep_location, 10);
        long z = strtol(sep_location + 1, &sep_location, 10);
        processSample(time, x, y, z);
        //printf("process sample:%d,%d,%d,%d\n", time, x, y, z);
    }
    fclose(fp);
}

static int diff = 100000;
int main(int argc, char *argv[])
{

    // std::string error;
    // std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));

    // // Important:
    // //   If this is a test, use Runfiles::CreateForTest(&error).
    // //   Otherwise, if you don't have the value for argv[0] for whatever
    // //   reason, then use Runfiles::Create(&error).

    // if (runfiles == nullptr)
    // {
    //     printf("Error loading runfiles configuration.%s\n", error.c_str());
    // }
    // std::string path =
    //     runfiles->Rlocation(PATH);

    for (int i = 0; i < argc; i++)
    {
        printf("param %d: %s\n", i, argv[i]);
    }
    correct_answer = atoi(argv[1]);
    initAlgo();
    for (size_t scoringWindowSize = 30; scoringWindowSize <= 40; scoringWindowSize++)
    {
        for (int detectionThreshold_whole = 1; detectionThreshold_whole <= 2; detectionThreshold_whole++)
        {
            for (int detectionThreshold_frac = 1; detectionThreshold_frac <= 9; detectionThreshold_frac++)
            {
                for (int postTimeThreshold = 230; postTimeThreshold <= 280; postTimeThreshold += 5)
                {
                    changeWindowSize(scoringWindowSize);
                    changeDetectionThreshold(detectionThreshold_whole, detectionThreshold_frac);
                    changeTimeThreshold(postTimeThreshold);
                    runAlgo();
                    if (diff >= abs(getSteps() - correct_answer))
                    {
                        diff = abs(getSteps() - correct_answer);
                        printf("Steps=%d windowSize=%zu threshold=%d+1/%d timethreshold=%d diff=%d\n", getSteps(), scoringWindowSize, detectionThreshold_whole, detectionThreshold_frac, postTimeThreshold, abs(correct_answer - getSteps()));
                    }
                    resetSteps();
                    resetAlgo();
                }
            }
        }
    }
    printf("done\n");
}
