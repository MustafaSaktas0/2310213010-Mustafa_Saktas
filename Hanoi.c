#include <stdio.h>

void hanoi_move_disks(int diskCount, char source, char helper, char target);
unsigned long long hanoi_move_count(int diskCount);
void menu();

int main()
{
    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("Exiting program.\n");
            return 0;
        }

        if (choice == 1)
        {
            int diskCount;
            printf("Enter disk count: ");
            scanf("%d", &diskCount);

            if (diskCount < 0)
            {
                printf("Invalid disk count!\n");
                continue;
            }
            // overflow'u önlemek için 62'den büyük disk sayısına izin vermiyoruz
            if (diskCount > 62)
            {
                printf("Too large! Please enter disk count <= 62 (to avoid overflow).\n");
                continue;
            }

            unsigned long long moveCount = hanoi_move_count(diskCount);
            printf("Total move count = %llu\n", moveCount);

            // yazdırma limiti satır sayısı fahiş sayılara çıkmaması için
            if (diskCount > 20)
            {
                printf("Disk count is large, moves will not be printed (limit is 20).\n");
                continue;
            }

            printf("\n--- HANOI MOVES ---\n");
            hanoi_move_disks(diskCount, 'A', 'B', 'C');
            printf("-------------------\n");
        }
        else
        {
            printf("Invalid option!\n");
        }
    }
}

void menu()
{
    printf("\n==================== HANOI MENU ====================\n");
    printf("1- Solve Hanoi\n");
    printf("0- Exit\n");
    printf("=====================================================\n");
}

unsigned long long hanoi_move_count(int diskCount)
{
    // 2^n - 1
    if (diskCount == 0) return 0ULL;
    return (1ULL << diskCount) - 1ULL;
}

void hanoi_move_disks(int diskCount, char source, char helper, char target)
{
    if (diskCount == 0)
        return;

    hanoi_move_disks(diskCount - 1, source, target, helper);
    printf("Move disk %d: %c -> %c\n", diskCount, source, target);
    hanoi_move_disks(diskCount - 1, helper, source, target);
}
