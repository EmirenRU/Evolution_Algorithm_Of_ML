#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "func.h"
using namespace std;

double comp (const func i1, const func i2)
{
    double dist = 0;
    for (double x = -100; x < 100; x++)
    {
        dist += abs((i1.k1 * pow(x,3) + i1.k2 * pow(x,2) + i1.k3 * x + i1.k4) - (i2.k1 * pow(x,3) + i2.k2 * pow(x,2) + i2.k3 * x + i2.k4));
    }
    return dist;
}

double comp_ind (const func i1, const func i2)
{
    double dist = 0;
    for (double x = -100; x < 100; x++)
    {
        dist += abs((i1.k1 * pow(x,3) + i1.k2 * pow(x,2) + i1.k3 * x + i1.k4) - (i2.k1/4 * pow(x,4) + i2.k2/3 * pow(x,3) + i2.k3/2 * pow(x,2) + i2.k4 * x));
    }
    return dist;
}

double calc_dir(func f)
{
    double dist = 0;
    for (int x = -100; x < 100; x++)
    {
        dist += f.k1 * pow(x,3) + f.k2 * pow(x,2) + f.k3 * x + f.k4;
    }
    return dist;
}

int main() {
    srand(time(0));

    int epoch = 1000;
    double d = 2.5;


    func finish;
    finish.k1 = (double)(rand() % 100) / 100.0;
    finish.k2 = (double)(rand() % 100) / 100.0;
    finish.k3 = (double)(rand() % 100) / 100.0;
    finish.k4 = (double)(rand() % 100) / 100.0;


    func start;
    start.k1 = (double)(rand() % 100) / 100.0;
    start.k2 = (double)(rand() % 100) / 100.0;
    start.k3 = (double)(rand() % 100) / 100.0;
    start.k4 = (double)(rand() % 100) / 100.0;



    func suc = start;
    char choice;
    cout << "DIRECT OR INDIRECT SIGN:\n1.Direct\n2.Indirect\nEnter the number: ";
    cin >> choice;
    cout << endl;
    switch(choice) {
        case '1': {
            int m = 0;
            do {
                for (int i = 0; i < epoch; i++) {
                    func suc_temp;

                    suc_temp.k1 = start.k1 + (-d + 2 * (rand() % 1000) / 1000.0 * d);
                    suc_temp.k2 = start.k2 + (-d + 2 * (rand() % 1000) / 1000.0 * d);
                    suc_temp.k3 = start.k3 + (-d + 2 * (rand() % 1000) / 1000.0 * d);
                    suc_temp.k4 = start.k4 + (-d + 2 * (rand() % 1000) / 1000.0 * d);

                    //  printf("Inp1:%.2f Inp2:%.2f Inp3:%.2f Inp4:%.2f\n", suc_temp.k1, suc_temp.k2, suc_temp.k3, suc_temp.k4);

                    if (comp(suc_temp, finish) < comp(suc, finish)) {
                        suc = suc_temp;
                    }
                }

                m++;
                // cout << calc_dir(suc) << " " <<  calc_dir(start) << " " << abs(calc_dir(suc) - calc_dir(start)) << " " << comp(start,suc)  << endl;
            } while (comp(suc, finish) > 0.5 && m < 1000);
        }
            break;
        case '2':
        {
            int m = 0;
            do {
                for (int i = 0; i < epoch; i++) {
                    func suc_temp;

                    suc_temp.k1 = start.k1 + (-d + 2 * (rand() % 1000) / 1000.0 * d);
                    suc_temp.k2 = start.k2 + (-d + 2 * (rand() % 1000) / 1000.0 * d);
                    suc_temp.k3 = start.k3 + (-d + 2 * (rand() % 1000) / 1000.0 * d);
                    suc_temp.k4 = start.k4 + (-d + 2 * (rand() % 1000) / 1000.0 * d);

                    //  printf("Inp1:%.2f Inp2:%.2f Inp3:%.2f Inp4:%.2f\n", suc_temp.k1, suc_temp.k2, suc_temp.k3, suc_temp.k4);

                    if (comp_ind(suc_temp, finish) < comp_ind(suc, finish)) {
                        suc = suc_temp;
                    }
                }

                m++;
                // cout << calc_dir(suc) << " " <<  calc_dir(start) << " " << abs(calc_dir(suc) - calc_dir(start)) << " " << comp(start,suc)  << endl;
            } while (comp_ind(suc, finish) > 0.5 && m < 1000);
        }
        break;
    }
    printf("Start : Inp1:%.4f Inp2:%.4f Inp3:%.4f Inp4:%.4f\n", start.k1, start.k2, start.k3, start.k4);
    printf("Suc : Inp1:%.4f Inp2:%.4f Inp3:%.4f Inp4:%.4f\n", suc.k1, suc.k2, suc.k3, suc.k4);
    printf("Finish : Inp1:%.4f Inp2:%.4f Inp3:%.4f Inp4:%.4f\n", finish.k1, finish.k2, finish.k3, finish.k4);
    if (choice == '2') {
        printf("k1:%.4f k2:%.4f k3:%.4f k4:%.4f\n", finish.k1 / 4, finish.k2 / 3, finish.k3 / 2, finish.k4);
        printf("Success-Finish: %.4f Start-Finish: %.4f\n", comp_ind(suc, finish), comp_ind(start, finish));
    }else
        printf("Success-Finish: %.4f Start-Finish: %.4f\n", comp(suc,finish), comp(start, finish));


    return 0;
}
