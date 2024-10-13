#include <stdio.h>
#include <stdlib.h>

#define CAR 1
#define SCOOTER 2

struct vehicle {
    int num;
    int row;
    int col;
    int type;
};

int parkinfo[4][10];
int vehcount = 0;
int carcount = 0;
int scootercount = 0;

void display();
void changecol(struct vehicle *);
struct vehicle *add(int, int, int, int);
void del(struct vehicle *);
void getfreerowcol(int, int *);
void getrcbyinfo(int, int, int *);

void changecol(struct vehicle *v) {
    v->col = v->col - 1;
}

struct vehicle *add(int t, int num, int row, int col) {
    struct vehicle *v;
    v = (struct vehicle *)malloc(sizeof(struct vehicle));

    v->type = t;
    v->row = row;
    v->col = col;

    if (t == CAR) carcount++;
    else scootercount++;

    vehcount++;
    parkinfo[row][col] = num;

    return v;
}

void del(struct vehicle *v) {
    int c;
    for (c = v->col; c < 9; c++) {
        parkinfo[v->row][c] = parkinfo[v->row][c + 1];
    }
    parkinfo[v->row][c] = 0;

    if (v->type == CAR) carcount--;
    else scootercount--;

    vehcount--;
}

void getfreerowcol(int type, int *arr) {
    int r, c, fromrow = 0, torow = 2;

    if (type == SCOOTER) {
        fromrow += 2;
        torow += 2;
    }

    for (r = fromrow; r < torow; r++) {
        for (c = 0; c < 10; c++) {
            if (parkinfo[r][c] == 0) {
                arr[0] = r;
                arr[1] = c;
                return;
            }
        }
    }

    arr[0] = -1;
    arr[1] = -1;
}

void getrcbyinfo(int type, int num, int *arr) {
    int r, c, fromrow = 0, torow = 2;

    if (type == SCOOTER) {
        fromrow += 2;
        torow += 2;
    }

    for (r = fromrow; r < torow; r++) {
        for (c = 0; c < 10; c++) {
            if (parkinfo[r][c] == num) {
                arr[0] = r;
                arr[1] = c;
                return;
            }
        }
    }

    arr[0] = -1;
    arr[1] = -1;
}

void display() {
    int r, c;

    printf("Cars ->\n");

    for (r = 0; r < 4; r++) {
        if (r == 2) printf("Scooters ->\n");

        for (c = 0; c < 10; c++) {
            printf("%d\t", parkinfo[r][c]);
        }
        printf("\n");
    }
}

int main() {
    int choice, type, number, row = 0, col = 0;
    int i, tarr[2];
    int finish = 1;

    struct vehicle *car[2][10];
    struct vehicle *scooter[2][10];

    system("clear");

    while (finish) {
        system("clear");

        printf("\n<<<-----****-----****<<<<Vehicle Parking System>>>>****-----****----->>>\n\n");
        printf("1. Arrival of a vehicle-->\n\n");
        printf("\t2. Total no. of vehicles parked-->\n\n");
        printf("\t\t3. Total no. of cars parked-->\n\n");
        printf("\t\t\t4. Total no. of scooters parked-->\n\n");
        printf("\t\t\t\t5. Display order in which vehicles are parked-->\n\n");
        printf("\t\t\t\t\t6. Departure of vehicle-->\n\n");
        printf("\t\t\t\t\t\t7. Exit-->\n\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("clear");
                printf("\nAdd: \n");

                type = 0;
                while (type != CAR && type != SCOOTER) {
                    printf("Enter vehicle type (1 for Car / 2 for Scooter ): \n");
                    scanf("%d", &type);
                    if (type != CAR && type != SCOOTER) printf("\nInvalid vehicle type.\n");
                }

                printf("Enter vehicle number: ");
                scanf("%d", &number);

                if (type == CAR || type == SCOOTER) {
                    getfreerowcol(type, tarr);
                    if (tarr[0] != -1 && tarr[1] != -1) {
                        row = tarr[0];
                        col = tarr[1];

                        if (type == CAR) car[row][col] = add(type, number, row, col);
                        else scooter[row - 2][col] = add(type, number, row, col);
                    } else {
                        if (type == CAR) printf("\nNo parking slot free to park a car\n");
                        else printf("\nNo parking slot free to park a scooter\n");
                    }
                } else {
                    printf("Invalid type\n");
                    break;
                }

                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;

            case 2:
                system("clear");
                printf("Total vehicles parked: %d\n", vehcount);
                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;

            case 3:
                system("clear");
                printf("Total cars parked: %d\n", carcount);
                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;

            case 4:
                system("clear");
                printf("Total scooters parked: %d\n", scootercount);
                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;

            case 5:
                system("clear");
                printf("Display\n");
                display();
                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;

            case 6:
                system("clear");
                printf("Departure\n");
                type = 0;
                while (type != CAR && type != SCOOTER) {
                    printf("Enter vehicle type (1 for Car / 2 for Scooter ): \n");
                    scanf("%d", &type);
                    if (type != CAR && type != SCOOTER) printf("\nInvalid vehicle type.\n");
                }
                printf("Enter number: ");
                scanf("%d", &number);

                if (type == CAR || type == SCOOTER) {
                    getrcbyinfo(type, number, tarr);
                    if (tarr[0] != -1 && tarr[1] != -1) {
                        col = tarr[1];
                        if (type == CAR) {
                            row = tarr[0];
                            del(car[row][col]);
                            for (i = col; i < 9; i++) {
                                car[row][i] = car[row][i + 1];
                                changecol(car[row][i]);
                            }
                            free(car[row][i]);
                            car[row][i] = NULL;
                        } else {
                            row = tarr[0] - 2;
                            if (!(row < 0)) {
                                del(scooter[row][col]);
                                for (i = col; i < 9; i++) {
                                    scooter[row][i] = scooter[row][i + 1];
                                    changecol(scooter[row][col]);
                                }
                                scooter[row][i] = NULL;
                            }
                        }
                    } else {
                        if (type == CAR) printf("\nInvalid car number, or a car with such number has not been parked here.\n");
                        else printf("\nInvalid scooter number, or a scooter with such number has not been parked here.\n");
                    }
                }
                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;

            case 7:
                finish = 0;
                break;
        }
    }

    return 0;
}
