#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int finish[n];

    // Initialize finish array
    for(i = 0; i < n; i++) {

        int sum = 0;

        for(j = 0; j < m; j++)
            sum += alloc[i][j];

        if(sum == 0)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    int work[m];

    for(i = 0; i < m; i++)
        work[i] = avail[i];

    int found;

    do {
        found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {

                    if(request[i][j] > work[j])
                        break;
                }

                // Process can finish
                if(j == m) {

                    for(k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    finish[i] = 1;
                    found = 1;

                    printf("\nP%d can finish.", i);
                }
            }
        }

    } while(found);

    // Check deadlock
    int deadlock = 0;

    printf("\n\nProcesses in Deadlock:\n");

    for(i = 0; i < n; i++) {

        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
        printf("No deadlock detected. All processes can finish.");

    return 0;
}
