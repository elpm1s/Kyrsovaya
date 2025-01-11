#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define TEAMS 9
#define GAMES 16

// ������� ��� ���������� ������� ���������� ������������
void randomTable(char results[TEAMS][GAMES]);
// ������� ��� ������ ������� �����������
void printTable(char results[TEAMS][GAMES]);
// ������� ��� �������� ����� ������ �������
int* countPoints(char results[TEAMS][GAMES], int points[TEAMS]);
// ������� ��� ������ ����� ������ �������
void printPoints(int points[TEAMS]);
// ������� ��� ������ ������ � ����� ��� n ������
int* searchN(int points[TEAMS], int n, int* count);
// ������� ��� ���������� ������ �� ����� (����������� ����������)
void sortirovka(int points[TEAMS], int indices[TEAMS]);
// ������� ��� ������ ����� � ��������������� �������
void printSortirovky(int points[TEAMS], int indices[TEAMS]);
// ������� ��� �������������� ������ � �������
int editTable(char results[TEAMS][GAMES]);
// ������� ��� ���������� �������� ���������� ����� �� ���� ��������
float countSredneePoints(int points[TEAMS]);

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    char results[TEAMS][GAMES]; // ������� ����������� ���
    int points[TEAMS]; // ������ ��� �������� ����� ������
    int choice; // ���������� ��� ������ ��������
    int porog; // ��������� �������� ��� ������ ������

    printf("������� ������������ � ������� ������� ������� 9 ������, ��������� ��� - 16|\n");
    printf("������� ���������:                                                         |\n");
    printf("1.������� ������� �����������                                              |\n");
    printf("2.������� ���� ������                                                      |\n");
    printf("3.������� ������� � ����� ��� n ������                                     |\n");
    printf("4.��������� ������� �� �����                                               |\n");
    printf("5.����������� ������ � �������                                             |\n");
    printf("6.��������� ������� ���������� �����                                       |\n");
    printf("---------------------------------------------------------------------------|\n");

    randomTable(results); // ��������� ������� ���������� ������������
    int* pointsPointer = countPoints(results, points); // ������������ ���� ������
    int index[TEAMS];
    do {
        // ����
        printf("\n����:\n");
        printf("1.�������� ������� �����������\n");
        printf("2.�������� ���� ������\n");
        printf("3.����� ������� � ����� ��� n ������\n");
        printf("4.������������� ������� �� �����\n");
        printf("5.������������� ������ � �������\n");
        printf("6.��������� ������� ���������� �����\n");
        printf("7.�����\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printTable(results); // �������� ������� �����������
            break;
        case 2:
            printPoints(points); // �������� ���� ������
            break;
        case 3:
            printf("\n������� ��������� �������� �����: ");
            scanf("%d", &porog);

            int count; // ���������� ��� ���������� ������
            int* teams = searchN(points, porog, &count); // ����� �������

            if (count > 0) {
                printf("\n������� � ����� ��� %d ������:\n", porog);
                for (int i = 0; i < count; i++) {
                    printf("������� %d\n", teams[i]);
                }
            }
            else {
                printf("\n��� ������ � ����� ��� %d ������.\n", porog);
            }
            break;
        case 4:
            sortirovka(points, index); // ������������� ������� �� �����
            printSortirovky(points, index); // �������� ��������������� ����
            break;
        case 5:
            editTable(results); // ������������� ������ � �������
            countPoints(results, points); // ������������� ���� ����� ��������� ������
            break;
        case 6:
            printf("\n������� ���������� �����: %.2f\n", countSredneePoints(points));
            break;
        case 7:
            printf("����� �� ���������.\n");
            break;
        default:
            printf("\n�������� �����. ���������� �����.\n");
        }
    } while (choice != 7); // ���� ������������, ���� �� ������� "�����"

    return 0;
}


void randomTable(char results[TEAMS][GAMES])
{
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        for (int j = 0; j < GAMES; j++) { // ���������� ����
            results[i][j] = (rand() % 5 == 0) ? '+' : '-'; // ��������� ��������� ��������: "+" ��� "-"
        }
    }
}

void printTable(char results[TEAMS][GAMES])
{
    printf("\n������� �����������:\n");
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        printf("������� %d: ", i + 1); // ������� ����� �������
        for (int j = 0; j < GAMES; j++) { // ���������� ����
            printf("%c ", results[i][j]); // ������� ��������� ����
        }
        printf("\n");
    }
}

int* countPoints(char results[TEAMS][GAMES], int points[TEAMS]) {
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        points[i] = 0; // ���������� ���� �������
        for (int j = 0; j < GAMES; j++) { // ���������� ����
            if (results[i][j] == '+') { // ���� ������
                points[i] += 4; // ��������� 4 ����
            }
            else if (results[i][j] == '-') { // ���� �����
                points[i] += 2; // ��������� 2 ����
            }
        }
    }
    return points; // ���������� ��������� �� ������
}

void printPoints(int points[TEAMS])
{
    printf("\n���� ������:\n");
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        printf("������� %d: %d �����\n", i + 1, points[i]); // ������� ���� �������
    }
}

int* searchN(int points[TEAMS], int n, int* count) {
    static int teamIndex[TEAMS]; // ����������� ������ ��� �������� ������� ������
    *count = 0; // ���������� ������� ���������� ������

    for (int i = 0; i < TEAMS; i++) {
        if (points[i] > n) {
            teamIndex[*count] = i + 1; // ��������� ����� ������� (���������� � 1)
            (*count)++; // ����������� ���������� ���������� ������
        }
    }
    return teamIndex; // ���������� ������ ������� ������
}

void sortirovka(int points[TEAMS], int index[TEAMS]) {
    // ������������� ������� ��������
    for (int i = 0; i < TEAMS; i++) {
        index[i] = i;
    }

    // ����������� ���������� ������� �������� �� ������ �����
    for (int i = 0; i < TEAMS - 1; i++) {
        for (int j = 0; j < TEAMS - 1 - i; j++) {
            if (points[index[j]] > points[index[j + 1]]) {
                // ������ ������� �������
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

void printSortirovky(int points[TEAMS], int index[TEAMS]) {
    printf("\n���� ������ � ��������������� �������:\n");
    for (int i = 0; i < TEAMS; i++) {
        printf("������� %d: %d �����\n", index[i] + 1, points[index[i]]);
    }
}

int editTable(char results[TEAMS][GAMES]) {
    int team, game;
    char newResult;

    printf("\n������� ����� �������: ");
    scanf("%d", &team);
    printf("������� ����� ����: ");
    scanf("%d", &game);

    if (team < 1 || team > TEAMS || game < 1 || game > GAMES) {
        printf("�������� ����. ���������� �����.\n");
        return -1;
    }

    printf("������� ����� ��������� ('+' ��� ������, '-' ��� �����): ");
    scanf(" %c", &newResult);

    if (newResult != '+' && newResult != '-') {
        printf("�������� ���������. ���������� �����.\n");
        return -1;
    }

    results[team - 1][game - 1] = newResult; // �������� ��������
    printf("��������� ������ �������!\n");
    return 0;
}

float countSredneePoints(int points[TEAMS]) {
    int sum = 0;
    for (int i = 0; i < TEAMS; i++) {
        sum += points[i];
    }
    return (float)sum / TEAMS; // ���������� �������
}