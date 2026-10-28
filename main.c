/*
 * 自動販売機シミュレーター
 * Japanese Vending Machine Simulator
 *
 * 初心者向けのC言語プロジェクトです。
 * 飲み物を選び、お金を入れて、お釣りを受け取る流れを
 * ターミナル上でシミュレーションします。
 *
 * ビルド:
 *   gcc -Wall -Wextra -Wpedantic main.c -o vending_machine.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* 一度に入力できる金額の上限（安全に計算するための制限） */
#define MAX_MONEY 100000L

/* メニューを表示する */
static void print_menu(void)
{
    printf("====================================\n");
    printf("     自動販売機シミュレーター\n");
    printf("     Japanese Vending Machine\n");
    printf("====================================\n");
    printf("\n");
    printf("1. Water       - 100 yen\n");
    printf("2. Green Tea   - 120 yen\n");
    printf("3. Coffee      - 150 yen\n");
    printf("0. Exit\n");
    printf("\n");
}

/*
 * 1行を読み取り、整数に変換する。
 * 戻り値: 1 = 成功, 0 = 不正な入力, -1 = 入力終了(EOF)
 *
 * fgets で1行ずつ読むため、入力が文字列でも安全に処理できる。
 * strtol で変換し、数字以外の文字が残っていれば不正な入力とする。
 */
static int read_number(const char *prompt, long *value)
{
    char line[64];
    char *end;
    long number;

    printf("%s", prompt);

    /* 入力できない、または入力が終了した場合 */
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }

    /* 1行が長すぎる場合は、残りを読み捨てて不正な入力とする */
    if (strchr(line, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* 読み捨て */
        }
        return 0;
    }

    errno = 0;
    number = strtol(line, &end, 10);

    /* 数字がない、または long の範囲を超えた場合 */
    if (end == line || errno == ERANGE) {
        return 0;
    }

    /* 数字の後ろに空白以外の文字があれば不正な入力とする */
    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        end++;
    }
    if (*end != '\0') {
        return 0;
    }

    *value = number;
    return 1;
}

int main(void)
{
    long choice;
    long money;
    long price;
    long change;
    const char *drink_name;
    int result;

    for (;;) {
        print_menu();

        result = read_number("Select a drink: ", &choice);

        /* 入力が終了した場合は無限ループにならないよう終了する */
        if (result == -1) {
            printf("\n入力が終了したため、プログラムを終了します。\n");
            break;
        }
        if (result == 0) {
            printf("Invalid input. 1〜3 または 0 を入力してください。\n\n");
            continue;
        }

        if (choice == 0) {
            printf("Thank you! またお越しください。\n");
            break;
        }

        /* 選んだ飲み物の名前と値段を決める */
        if (choice == 1) {
            drink_name = "Water";
            price = 100;
        } else if (choice == 2) {
            drink_name = "Green Tea";
            price = 120;
        } else if (choice == 3) {
            drink_name = "Coffee";
            price = 150;
        } else {
            printf("Invalid selection. 1〜3 または 0 を選んでください。\n\n");
            continue;
        }

        printf("\nYou selected: %s\n", drink_name);
        printf("Price: %ld yen\n\n", price);

        result = read_number("Insert money: ", &money);

        if (result == -1) {
            printf("\n入力が終了したため、プログラムを終了します。\n");
            break;
        }
        if (result == 0) {
            printf("Invalid input. 数字で金額を入力してください。\n\n");
            continue;
        }

        /* 金額のチェック */
        if (money < 0) {
            printf("Invalid amount. マイナスの金額は入力できません。\n\n");
            continue;
        }
        if (money == 0) {
            printf("Invalid amount. 0円では購入できません。\n\n");
            continue;
        }
        if (money > MAX_MONEY) {
            printf("Invalid amount. 一度に入力できるのは %ld 円までです。\n\n",
                   MAX_MONEY);
            continue;
        }

        /* お金が足りない場合 */
        if (money < price) {
            printf("Insufficient payment. あと %ld 円必要です。\n\n",
                   price - money);
            continue;
        }

        /* 購入成功とお釣りの計算 */
        change = money - price;
        printf("Purchase successful!\n");
        printf("Drink: %s\n", drink_name);
        printf("Change: %ld yen\n\n", change);
        printf("Thank you!\n\n");
    }

    return 0;
}
