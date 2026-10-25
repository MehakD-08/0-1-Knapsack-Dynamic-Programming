#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000
#define LINE_SIZE 500

void displayTable(int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1],
                  int items, int capacity)
{
    printf("\nDP Table after processing %d item(s):\n\n", items);
    printf("       ");
    for (int w = 0; w <= capacity; w++)
        printf("%4d", w);
    printf("\n");
    printf("     +");
    for (int w = 0; w <= capacity; w++)
        printf("----");
    printf("\n");
    for (int i = 0; i <= items; i++) {
        printf("%3d  |", i);
        for (int w = 0; w <= capacity; w++) {
            printf("%4d", dp[i][w]);
        }
        printf("\n");
    }
    printf("\n");
}

int knapsack(int n, int W, int weight[], int value[])
{
    int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1];
    for (int w = 0; w <= W; w++)
        dp[0][w] = 0;
    printf("\nInitial DP Table:\n");
    displayTable(dp, 0, W);
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weight[i - 1] <= w) {
                int include =
                    value[i - 1] +
                    dp[i - 1][w - weight[i - 1]];
                int exclude =
                    dp[i - 1][w];
                dp[i][w] =
                    (include > exclude) ? include : exclude;
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
        printf("Item %d -> Weight = %d, Value = %d\n",
               i, weight[i - 1], value[i - 1]);

        displayTable(dp, i, W);
    }

    return dp[n][W];
}

int main()
{
    FILE *input;
    FILE *output;
    char line[LINE_SIZE];
    int n, W;
    int weight[MAX_ITEMS];
    int value[MAX_ITEMS];
    int testNumber = 0;
    input = fopen("Knapsack data (2).txt", "r");
    if (input == NULL) {
        printf("Error: Input file could not be opened.\n");
        return 1;
    }
    output = fopen("result.txt", "w");
    if (output == NULL) {
        printf("Error: result.txt could not be created.\n");
        fclose(input);
        return 1;
    }
    while (fgets(line, sizeof(line), input) != NULL) {
        if (strncmp(line, "#Test", 5) == 0) {
            testNumber++;
            if (fgets(line, sizeof(line), input) == NULL)
                break;
            sscanf(line, "%d %d", &n, &W);
            for (int i = 0; i < n; i++) {
                if (fgets(line, sizeof(line), input) == NULL)
                    break;
                sscanf(line, "%d %d",
                       &weight[i],
                       &value[i]);
            }
            printf("\n=================================\n");
            printf("TEST CASE %d\n", testNumber);
            printf("n = %d, W = %d\n", n, W);
            printf("=================================\n");
            int result =
                knapsack(n, W, weight, value);
            printf("Maximum Value = %d\n", result);
            fprintf(output,
                    "#Test%d (%d %d) %d\n",
                    testNumber,
                    n,
                    W,
                    result);
        }
    }
    fclose(input);
    fclose(output);
    printf("\nAll test cases completed.\n");
    printf("Results stored in result.txt\n");
    return 0;
}
