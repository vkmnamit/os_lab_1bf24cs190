#include <stdio.h>

int frames[10], pages[50];

/* FIFO Page Replacement */
void fifo(int n, int f)
{
    int i, j, k = 0, fault = 0, found;

    for(i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frames[k] = pages[i];
            k = (k + 1) % f;
            fault++;
        }

        printf("Page %d -> ", pages[i]);
        for(j = 0; j < f; j++)
        {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", fault);
}

/* LRU Page Replacement */
void lru(int n, int f)
{
    int i, j, least, pos, fault = 0;
    int time[10], counter = 0, found;

    for(i = 0; i < f; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            least = time[0];
            pos = 0;

            for(j = 1; j < f; j++)
            {
                if(time[j] < least)
                {
                    least = time[j];
                    pos = j;
                }
            }

            counter++;
            frames[pos] = pages[i];
            time[pos] = counter;
            fault++;
        }

        printf("Page %d -> ", pages[i]);
        for(j = 0; j < f; j++)
        {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", fault);
}

/* Optimal Page Replacement */
void optimal(int n, int f)
{
    int i, j, k, pos, farthest, fault = 0, found;

    for(i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            pos = -1;

            for(j = 0; j < f; j++)
            {
                int flag = 0;

                for(k = i + 1; k < n; k++)
                {
                    if(frames[j] == pages[k])
                    {
                        if(flag == 0 || k > farthest)
                        {
                            farthest = k;
                            pos = j;
                        }
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
                pos = 0;

            frames[pos] = pages[i];
            fault++;
        }

        printf("Page %d -> ", pages[i]);
        for(j = 0; j < f; j++)
        {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", fault);
}

int main()
{
    int n, f, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(n, f);
    lru(n, f);
    optimal(n, f);

    return 0;
}
