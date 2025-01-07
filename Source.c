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
void countPoints(char results[TEAMS][GAMES], int points[TEAMS]);
// ������� ��� ������ ����� ������ �������
void printPoints(int points[TEAMS]);
// ������� ��� ������ ������ � ����� ��� n ������
void searchN(int points[TEAMS], int n);
// ������� ��� ���������� ������ �� ����� (����������� ����������)
void sortirovka(int points[TEAMS]);
// ������� ��� ������ ����� � ��������������� �������
void printSortirovky(int points[TEAMS]);
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
    int a; // ��������� �������� ��� ������ ������

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
    countPoints(results, points); // ������������ ���� ������

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
            scanf("%d", &a);
            searchN(points, a); // ����� ������� � ����� ��� n ������
            break;
        case 4:
            sortirovka(points); // ������������� ������� �� �����
            printSortirovky(points); // �������� ��������������� ����
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

void countPoints(char results[TEAMS][GAMES], int points[TEAMS])
{
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
}

void printPoints(int points[TEAMS])
{
    printf("\n���� ������:\n");
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        printf("������� %d: %d �����\n", i + 1, points[i]); // ������� ���� �������
    }
}

void searchN(int points[TEAMS], int n)
{
    printf("\n������� � ����� ��� %d ������:\n", n);
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        if (points[i] > n) { // ���������, ������ �� �����, ��� n
            printf("������� %d: %d �����\n", i + 1, points[i]); // ����� ������
        }
    }
}

void sortirovka(int points[TEAMS]) {
    for (int i = 0; i < TEAMS - 1; i++) { // ������� ���� ��� ��������
        for (int j = 0; j < TEAMS - 1 - i; j++) { // ���������� ���� ��� ��������� �������� ���������
            if (points[j] < points[j + 1]) { // ���� ���� ������� ������� ������ ���������
                // ������ ������� ����
                int temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
}

void printSortirovky(int points[TEAMS]) {
    printf("\n���� ������ � ��������������� �������:\n");
    for (int i = 0; i < TEAMS; i++) { // ���������� �������
        printf("������� %d: %d �����\n", i + 1, points[i]); // ������� ���� �������
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