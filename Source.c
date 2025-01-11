#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define TEAMS 9
#define GAMES 16

// Функция для заполнения таблицы случайными результатами
void randomTable(char results[TEAMS][GAMES]);
// Функция для вывода таблицы результатов
void printTable(char results[TEAMS][GAMES]);
// Функция для подсчета очков каждой команды
int* countPoints(char results[TEAMS][GAMES], int points[TEAMS]);
// Функция для вывода очков каждой команды
void printPoints(int points[TEAMS]);
// Функция для поиска команд с более чем n очками
int* searchN(int points[TEAMS], int n, int* count);
// Функция для сортировки команд по очкам (пузырьковая сортировка)
void sortirovka(int points[TEAMS], int indices[TEAMS]);
// Функция для вывода очков в отсортированном порядке
void printSortirovky(int points[TEAMS], int indices[TEAMS]);
// Функция для редактирования данных в таблице
int editTable(char results[TEAMS][GAMES]);
// Функция для вычисления среднего количества очков по всем командам
float countSredneePoints(int points[TEAMS]);

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    char results[TEAMS][GAMES]; // Таблица результатов игр
    int points[TEAMS]; // Массив для хранения очков команд
    int choice; // Переменная для выбора действия
    int porog; // Пороговое значение для поиска команд

    printf("Таблица соревнований в которой приняли участие 9 команд, проведено игр - 16|\n");
    printf("Функции программы:                                                         |\n");
    printf("1.Выводит таблицу результатов                                              |\n");
    printf("2.Выводит очки команд                                                      |\n");
    printf("3.Находит команды с более чем n очками                                     |\n");
    printf("4.Сортирует команды по очкам                                               |\n");
    printf("5.Редактирует данные в таблице                                             |\n");
    printf("6.Вычисляет среднее количество очков                                       |\n");
    printf("---------------------------------------------------------------------------|\n");

    randomTable(results); // Заполняем таблицу случайными результатами
    int* pointsPointer = countPoints(results, points); // Подсчитываем очки команд
    int index[TEAMS];
    do {
        // Меню
        printf("\nМеню:\n");
        printf("1.Показать таблицу результатов\n");
        printf("2.Показать очки команд\n");
        printf("3.Найти команды с более чем n очками\n");
        printf("4.Отсортировать команды по очкам\n");
        printf("5.Редактировать данные в таблице\n");
        printf("6.Вычислить среднее количество очков\n");
        printf("7.Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printTable(results); // Показать таблицу результатов
            break;
        case 2:
            printPoints(points); // Показать очки команд
            break;
        case 3:
            printf("\nВведите пороговое значение очков: ");
            scanf("%d", &porog);

            int count; // Переменная для количества команд
            int* teams = searchN(points, porog, &count); // Вызов функции

            if (count > 0) {
                printf("\nКоманды с более чем %d очками:\n", porog);
                for (int i = 0; i < count; i++) {
                    printf("Команда %d\n", teams[i]);
                }
            }
            else {
                printf("\nНет команд с более чем %d очками.\n", porog);
            }
            break;
        case 4:
            sortirovka(points, index); // Отсортировать команды по очкам
            printSortirovky(points, index); // Показать отсортированные очки
            break;
        case 5:
            editTable(results); // Редактировать данные в таблице
            countPoints(results, points); // Пересчитываем очки после изменения данных
            break;
        case 6:
            printf("\nСреднее количество очков: %.2f\n", countSredneePoints(points));
            break;
        case 7:
            printf("Выход из программы.\n");
            break;
        default:
            printf("\nНеверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 7); // Цикл продолжается, пока не выбрано "Выход"

    return 0;
}


void randomTable(char results[TEAMS][GAMES])
{
    for (int i = 0; i < TEAMS; i++) { // Перебираем команды
        for (int j = 0; j < GAMES; j++) { // Перебираем игры
            results[i][j] = (rand() % 5 == 0) ? '+' : '-'; // Заполняем результат случайно: "+" или "-"
        }
    }
}

void printTable(char results[TEAMS][GAMES])
{
    printf("\nТаблица результатов:\n");
    for (int i = 0; i < TEAMS; i++) { // Перебираем команды
        printf("Команда %d: ", i + 1); // Выводим номер команды
        for (int j = 0; j < GAMES; j++) { // Перебираем игры
            printf("%c ", results[i][j]); // Выводим результат игры
        }
        printf("\n");
    }
}

int* countPoints(char results[TEAMS][GAMES], int points[TEAMS]) {
    for (int i = 0; i < TEAMS; i++) { // Перебираем команды
        points[i] = 0; // Сбрасываем очки команды
        for (int j = 0; j < GAMES; j++) { // Перебираем игры
            if (results[i][j] == '+') { // Если победа
                points[i] += 4; // Добавляем 4 очка
            }
            else if (results[i][j] == '-') { // Если ничья
                points[i] += 2; // Добавляем 2 очка
            }
        }
    }
    return points; // Возвращаем указатель на массив
}

void printPoints(int points[TEAMS])
{
    printf("\nОчки команд:\n");
    for (int i = 0; i < TEAMS; i++) { // Перебираем команды
        printf("Команда %d: %d очков\n", i + 1, points[i]); // Выводим очки команды
    }
}

int* searchN(int points[TEAMS], int n, int* count) {
    static int teamIndex[TEAMS]; // Статический массив для хранения номеров команд
    *count = 0; // Сбрасываем счетчик подходящих команд

    for (int i = 0; i < TEAMS; i++) {
        if (points[i] > n) {
            teamIndex[*count] = i + 1; // Сохраняем номер команды (индексация с 1)
            (*count)++; // Увеличиваем количество подходящих команд
        }
    }
    return teamIndex; // Возвращаем массив номеров команд
}

void sortirovka(int points[TEAMS], int index[TEAMS]) {
    // Инициализация массива индексов
    for (int i = 0; i < TEAMS; i++) {
        index[i] = i;
    }

    // Пузырьковая сортировка массива индексов на основе очков
    for (int i = 0; i < TEAMS - 1; i++) {
        for (int j = 0; j < TEAMS - 1 - i; j++) {
            if (points[index[j]] > points[index[j + 1]]) {
                // Меняем местами индексы
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

void printSortirovky(int points[TEAMS], int index[TEAMS]) {
    printf("\nОчки команд в отсортированном порядке:\n");
    for (int i = 0; i < TEAMS; i++) {
        printf("Команда %d: %d очков\n", index[i] + 1, points[index[i]]);
    }
}

int editTable(char results[TEAMS][GAMES]) {
    int team, game;
    char newResult;

    printf("\nВведите номер команды: ");
    scanf("%d", &team);
    printf("Введите номер игры: ");
    scanf("%d", &game);

    if (team < 1 || team > TEAMS || game < 1 || game > GAMES) {
        printf("Неверный ввод. Попробуйте снова.\n");
        return -1;
    }

    printf("Введите новый результат ('+' для победы, '-' для ничьи): ");
    scanf(" %c", &newResult);

    if (newResult != '+' && newResult != '-') {
        printf("Неверный результат. Попробуйте снова.\n");
        return -1;
    }

    results[team - 1][game - 1] = newResult; // Изменяем значение
    printf("Результат изменён успешно!\n");
    return 0;
}

float countSredneePoints(int points[TEAMS]) {
    int sum = 0;
    for (int i = 0; i < TEAMS; i++) {
        sum += points[i];
    }
    return (float)sum / TEAMS; // Возвращаем среднее
}