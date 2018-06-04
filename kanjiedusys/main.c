#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLEN 1024

#define ONEQUESTIONSCORE 300

#define MAXUSER 100
#define MAXUSERNAME 20

void KanjiEduSys();
void KanjiYomiQ();
void KanjiTaigiQ();
void KanjiRuigiQ();
void KanjiBushuQ();
int ReadQuestionList(char *);
int BinarySearch(int, int);

int ReadUserList();
int SearchUN(char *);
void MakeAccount(char *);
void SetUserName(int, char *);
void SetKanjiScore(int, int);
int GetKanjiScore(int);
void SetEnglishScore(int, int);
int GetEnglishScore(int);
int WriteUserList();
void Ranking();

char question[MAXLEN][MAXLEN];
int questionCount = 0;
int questionNumber = -1;
char select1[MAXLEN][MAXLEN];
char select2[MAXLEN][MAXLEN];
char select3[MAXLEN][MAXLEN];
char select4[MAXLEN][MAXLEN];
int answer[MAXLEN];
int Answers[MAXLEN];
int AnswerCount = 0;

char userName[MAXUSER][MAXUSERNAME];
int kanjiScore[MAXUSER];
int englishScore[MAXUSER];
int accountCount = 0;
int userNumber = -1;

int main(int argc, char *argv[]) {
    char buf[MAXLEN];
    int x = 0;

    printf("There is education system.\n");
    printf("Please chose system.\n");
    printf("1. English Education System\n");
    printf("2. Kanji Education System.\n");
    printf("3. Mathematical Expression Processing System\n");

    printf("> ");
    fgets(buf, MAXLEN, stdin);
    x = atoi(buf);

    if (x != 0) {
        switch (x) {
            case 1:
                printf("You chose English Education Eystem.\n");
                break;
            case 2:
                printf("You chose Kanji Education System.\n");
                KanjiEduSys();
                break;
            case 3:
                printf("You chose Mathematical Expression Processing System\n");
                break;
            default:
                printf("No System.\n");
                break;
        }
    } else {
        printf("No System.\n");
    }

    return 0;
}

void KanjiEduSys() {
    int i;
    char buf[MAXLEN];
    char name[MAXUSERNAME];
    int select = -1;
    int find = -1;

    if (ReadUserList() == 1) {
        return;
    }

    printf("What do you name?\n");
    printf("> ");
    fgets(buf, MAXUSERNAME, stdin);
    for (i = 0; i < MAXUSERNAME; i++) {
        if(buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    strcpy(name, buf);

    find = SearchUN(name);

    if (find >= 0) {
        printf("Welcome back, %s\n", name);
        userNumber = find;
    } else {
        printf("Nice to meet you, %s\n", name);
        MakeAccount(name);
    }

    printf("Please chose kind of question.\n");
    printf("1. Yomi question\n");
    printf("2. Taigigo question\n");
    printf("3. Ruigigo question\n");
    printf("4. Bushu question\n");

    printf("> ");
    fgets(buf, MAXLEN, stdin);
    select = atoi(buf);

    switch (select) {
        case 1:
            printf("You chose Yomi question.\n");
            KanjiYomiQ();
            break;
        case 2:
            printf("You chose Taigigo question.\n");
            KanjiTaigiQ();
            break;
        case 3:
            printf("You chose Ruigigo question.\n");
            KanjiRuigiQ();
            break;
        case 4:
            printf("You chose Bushu question.\n");
            KanjiBushuQ();
            break;
        default:
            printf("Can't find question.\n");
            break;
    }
}


void KanjiYomiQ() {
    int r;

    char buf[MAXLEN];
    int yourAnswer;
    int missCount = 0;

    int score = 0;

    srand((unsigned)time(NULL));

    if (ReadQuestionList("KanjiYomiQ.txt") == 1) {
        return;
    }

    /*setumei*/
    printf("Please chose correct reading of Kanji.\n");

    /*question print*/
    while (1) {
        questionNumber = rand()%questionCount;
        if (AnswerCount != 0) {
            r = BinarySearch(0, questionCount - 1);
            while (r == 1) {
                questionNumber = rand()%questionCount;
                r = BinarySearch(0, questionCount - 1);
            }
        }

        printf("%s\n", question[questionNumber]);
        printf("%s\n", select1[questionNumber]);
        printf("%s\n", select2[questionNumber]);
        printf("%s\n", select3[questionNumber]);
        printf("%s\n", select4[questionNumber]);

        r = 0;
        while (r == 0) {
            /*answer scanf*/
            printf("> ");
            fgets(buf, MAXLEN, stdin);
            yourAnswer = atoi(buf);

            /*correct or wrong*/
            if (answer[questionNumber] == yourAnswer) {
                printf("Correct\n");
                r = 1;
            } else {
                printf("Wrong answer\n");
                missCount++;
            }
        }

        /*score add*/
        if (missCount < 3) {
            score  = GetKanjiScore(userNumber) + ONEQUESTIONSCORE - 100 * missCount;
        }
        SetKanjiScore(userNumber, score);
        printf("Your kanji score: %d\n", score);

        r = 0;

        printf("Do you want to continue?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("> ");
        fgets(buf, MAXLEN, stdin);
        r = atoi(buf);
        if (r == 2) {
            printf("See you.\n");
            WriteUserList();
            Ranking();
            return;
        }
    }
}

void KanjiTaigiQ() {
    int r;

    char buf[MAXLEN];
    int yourAnswer;
    int missCount = 0;

    int score = GetKanjiScore(userNumber);

    srand((unsigned)time(NULL));

    if (ReadQuestionList("KanjiTaigiQ.txt") == 1) {
        return;
    }

    /*setumei*/
    printf("Please chose correct antonym.\n");

    /*question print*/
    while (1) {
        questionNumber = rand()%questionCount;
        if (AnswerCount != 0) {
            r = BinarySearch(0, questionCount - 1);
            while (r == 1) {
                questionNumber = rand()%questionCount;
                r = BinarySearch(0, questionCount - 1);
            }
        }

        printf("%s\n", question[questionNumber]);
        printf("%s\n", select1[questionNumber]);
        printf("%s\n", select2[questionNumber]);
        printf("%s\n", select3[questionNumber]);
        printf("%s\n", select4[questionNumber]);

        r = 0;
        while (r == 0) {
            /*answer scanf*/
            printf("> ");
            fgets(buf, MAXLEN, stdin);
            yourAnswer = atoi(buf);

            /*correct or wrong*/
            if (answer[questionNumber] == yourAnswer) {
                printf("Correct\n");
                r = 1;
            } else {
                printf("Wrong answer\n");
                missCount++;
            }
        }

        /*score add*/
        if (missCount < 3) {
            score  = score + ONEQUESTIONSCORE - 100 * missCount;
        }
        SetKanjiScore(userNumber, score);
        printf("Your kanji score: %d\n", score);

        r = 0;

        printf("Do you want to continue?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("> ");
        fgets(buf, MAXLEN, stdin);
        r = atoi(buf);
        if (r == 2) {
            printf("See you.\n");
            WriteUserList();
            Ranking();
            return;
        }
    }
}
void KanjiRuigiQ() {
    int r;

    char buf[MAXLEN];
    int yourAnswer;
    int missCount = 0;

    int score = 0;

    srand((unsigned)time(NULL));

    if (ReadQuestionList("KanjiRuigiQ.txt") == 1) {
        return;
    }

    /*setumei*/
    printf("Please chose correct synonym.\n");

    /*question print*/
    while (1) {
        questionNumber = rand()%questionCount;
        if (AnswerCount != 0) {
            r = BinarySearch(0, questionCount - 1);
            while (r == 1) {
                questionNumber = rand()%questionCount;
                r = BinarySearch(0, questionCount - 1);
            }
        }

        printf("%s\n", question[questionNumber]);
        printf("%s\n", select1[questionNumber]);
        printf("%s\n", select2[questionNumber]);
        printf("%s\n", select3[questionNumber]);
        printf("%s\n", select4[questionNumber]);

        r = 0;
        while (r == 0) {
            /*answer scanf*/
            printf("> ");
            fgets(buf, MAXLEN, stdin);
            yourAnswer = atoi(buf);

            /*correct or wrong*/
            if (answer[questionNumber] == yourAnswer) {
                printf("Correct\n");
                r = 1;
            } else {
                printf("Wrong answer\n");
                missCount++;
            }
        }

        /*score add*/
        if (missCount < 3) {
            score  = GetKanjiScore(userNumber) + ONEQUESTIONSCORE - 100 * missCount;
        }
        SetKanjiScore(userNumber, score);
        printf("Your kanji score: %d\n", score);

        r = 0;

        printf("Do you want to continue?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("> ");
        fgets(buf, MAXLEN, stdin);
        r = atoi(buf);
        if (r == 2) {
            printf("See you.\n");
            WriteUserList();
            Ranking();
            return;
        }
    }
}
void KanjiBushuQ() {
    int r;

    char buf[MAXLEN];
    int yourAnswer;
    int missCount = 0;

    int score = 0;

    srand((unsigned)time(NULL));

    if (ReadQuestionList("KanjiBushuQ.txt") == 1) {
        return;
    }

    /*setumei*/
    printf("Please chose correct radical.\n");

    /*question print*/
    while (1) {
        questionNumber = rand()%questionCount;
        if (AnswerCount != 0) {
            r = BinarySearch(0, questionCount - 1);
            while (r == 1) {
                questionNumber = rand()%questionCount;
                r = BinarySearch(0, questionCount - 1);
            }
        }

        printf("%s\n", question[questionNumber]);
        printf("%s\n", select1[questionNumber]);
        printf("%s\n", select2[questionNumber]);
        printf("%s\n", select3[questionNumber]);
        printf("%s\n", select4[questionNumber]);

        r = 0;
        while (r == 0) {
            /*answer scanf*/
            printf("> ");
            fgets(buf, MAXLEN, stdin);
            yourAnswer = atoi(buf);

            /*correct or wrong*/
            if (answer[questionNumber] == yourAnswer) {
                printf("Correct\n");
                r = 1;
            } else {
                printf("Wrong answer\n");
                missCount++;
            }
        }

        /*score add*/
        if (missCount < 3) {
            score  = GetKanjiScore(userNumber) + ONEQUESTIONSCORE - 100 * missCount;
        }
        SetKanjiScore(userNumber, score);
        printf("Your kanji score: %d\n", score);

        r = 0;

        printf("Do you want to continue?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("> ");
        fgets(buf, MAXLEN, stdin);
        r = atoi(buf);
        if (r == 2) {
            printf("See you.\n");
            WriteUserList();
            Ranking();
            return;
        }
    }
}

int ReadQuestionList(char *fileName) {
    FILE *fp;
    char line[MAXLEN], *que, *sel1, *sel2, *sel3, *sel4, *ans;

    fp = fopen(fileName, "r");
    if( fp == NULL ) {
        fprintf(stderr,"Can't open file %s\n.",fileName);
        return 1;
    }

    while(fgets(line, MAXLEN, fp) != NULL && questionCount < MAXLEN) {
        que = strtok(line, ",");
        sel1 = strtok(NULL, ",");
        sel2 = strtok(NULL, ",");
        sel3 = strtok(NULL, ",");
        sel4 = strtok(NULL, ",");
        ans = strtok(NULL, ",");
        strcpy(question[questionCount], que);
        strcpy(select1[questionCount], sel1);
        strcpy(select2[questionCount], sel2);
        strcpy(select3[questionCount], sel3);
        strcpy(select4[questionCount], sel4);
        answer[questionCount] = atoi(ans);
        questionCount++;
        fgets(line, MAXLEN, fp);
    }

    fclose(fp);

    return 0;
}

int BinarySearch(int low, int high) {
    int mid, r;

    mid = (low + high) / 2;
    if (low == high) {
        if (Answers[mid] == questionNumber) {
            return 1;
        } else {
            return 0;
        }
    }

    if (Answers[mid] > questionNumber) {
        r = BinarySearch(low, mid - 1);
    } else if (Answers[mid] < questionNumber) {
        r = BinarySearch(mid + 1, high);
    } else {
        r = 1;
    }

    return r;
}

int ReadUserList() {
    char *fileName = "UserList.txt";
    FILE *fp;
    char line[MAXLEN], *UN, *KS, *ES;

    fp = fopen(fileName, "r");
    if( fp == NULL ) {
        fprintf(stderr,"Can't open file %s\n.",fileName);
        return 1;
    }

    while(fgets(line, MAXLEN, fp) != NULL && accountCount < MAXUSER) {
        UN = strtok(line, ",");
        KS = strtok(NULL, ",");
        ES = strtok(NULL, ",");
        strcpy(userName[accountCount], UN);
        kanjiScore[accountCount] = atoi(KS);
        englishScore[accountCount] = atoi(ES);
        accountCount++;
    }

    fclose(fp);

    return 0;
}

int SearchUN(char *name) {
    int i;

    for (i = 0; i < accountCount; i++) {
        if (strcmp(userName[i], name) == 0) {
            return i;
        }
    }

    return -1;
}

void MakeAccount(char *name) {
    SetUserName(accountCount, name);
    SetKanjiScore(accountCount, 0);
    SetEnglishScore(accountCount, 0);
    userNumber = accountCount;
    accountCount++;
}

void SetUserName(int num, char *name) {
    strcpy(userName[num], name);
}

void SetKanjiScore(int num, int score) {
    kanjiScore[num] = score;
}

int GetKanjiScore(int num) {
    return kanjiScore[num];
}

void SetEnglishScore(int num, int score) {
    englishScore[num] = score;
}

int GetEnglishScore(int num) {
    return englishScore[num];
}

int WriteUserList() {
    char *fileName = "UserList.txt";
    FILE *fp;
    int i;

    fp = fopen(fileName, "w");
    if( fp == NULL ) {
        fprintf(stderr,"Can't open file %s\n.",fileName);
        return 1;
    }

    for (i = 0; i < accountCount; i++) {
        fprintf(fp, "%s,%d,%d\n", userName[i], kanjiScore[i], englishScore[i]);
    }

    fclose(fp);

    return 0;
}

void Ranking() {
}
