// imn1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <cmath>
#include <string>


# define M_PI           3.14159265358979323846

double rozw(double t, int l)
{
    return exp(t * l);
}

int main()
{

    //PROBLEM AUTONOMICZNY

    int l = -1;
    double tmin = 0.0;
    double tmax = 5.0;
    std::vector<double> dt = { 0.01,0.1,1.0 };

    std::vector<double> y;
    y.push_back(1.0);
    int i = 0;

    //---- METODA JAWNA EULERA ----
    std::string file_name = "euler";
    int j = 0;
    bool flag = true;
    double sol;
    std::vector<const char*> files_name = { "euler1.txt","euler2.txt","euler3.txt"};
    std::vector<const char*> files_name_gb = { "euler1_gb.txt","euler2_gb.txt","euler3_gb.txt"};
    const char* nazwa = "euler_an.txt";
    FILE* fp3 = fopen(nazwa, "w+");
    for (double delT : dt)
    {
        file_name = file_name + std::to_string(j) + ".txt";
        FILE* fp1 = fopen(files_name.at(j), "w+");
        FILE* fp2 = fopen(files_name_gb.at(j), "w+");
        
        std::cout << "---Plik "<< files_name.at(j)<<" zostal utwozony dla dt = "<<delT<<"-- - " << std::endl;

        for (double t = tmin; t < tmax; t = t + delT)
        {
            y.push_back(y.at(i) + (delT * l * y.at(i)));
            
            double gt = y.at(i) - rozw(t, l);
            //std::cout << y.at(i) << " " << rozw(t, l) << " " << gt << std::endl;
            fprintf(fp1, "%g ", t);
            fprintf(fp1, "%g ", y.at(i));  
            fprintf(fp1, "\n");
            fprintf(fp2, "%g ", t);
            fprintf(fp2, "%g ", gt);
            fprintf(fp2, "\n");
            sol = rozw(t, l);
            if (flag)
            {
                fprintf(fp3, "%g ", t);
                fprintf(fp3, "%g ", sol);
                fprintf(fp3, "\n");
            }

            i++;
        }
        y.clear();
        y.push_back(1.0);
        i = 0;
        j++;
        flag = false;
    }

    //---- METODA JAWNA RK2 ----

    double k1;
    double k2;

    files_name = { "rk2_1.txt","rk2_2.txt","rk2_3.txt" };
    files_name_gb = { "rk2_1_gb.txt","rk2_2_gb.txt","rk2_3_gb.txt" };

    j = 0;
    flag = true;
    fp3 = fopen("rk2_an.txt", "w+");

    for (double delT : dt)
    {
        std::cout << "---Plik " << files_name.at(j) << " zostal utwozony dla dt = " << delT << "-- - " << std::endl;

        FILE* fp1 = fopen(files_name.at(j), "w+");
        FILE* fp2 = fopen(files_name_gb.at(j), "w+");

        for (double t = tmin; t < tmax; t = t + delT)
        {
            k1 = l * y.at(i);
            k2 = l * (y.at(i) + (delT * k1));
            y.push_back(y.at(i) + (0.5 * delT * (k1+k2)));
            
            double gt = y.at(i) - rozw(t, l);
            //std::cout << y.at(i) << " " << rozw(t, l) << " " << gt << std::endl;
            fprintf(fp1, "%g ", t);
            fprintf(fp1, "%g ", y.at(i));
            fprintf(fp1, "\n");
            fprintf(fp2, "%g ", t);
            fprintf(fp2, "%g ", gt);
            fprintf(fp2, "\n");
            if (flag)
            {
            fprintf(fp3, "%g ", t);
            fprintf(fp3, "%lf ", rozw(t, l));
            fprintf(fp3, "\n");
            }
            i++;

        }
        y.clear();
        y.push_back(1.0);
        i = 0;
        j++;
        flag = false;
    }

    //---- METODA JAWNA RK4 ----

    double k3;
    double k4;

    files_name = { "rk4_1.txt","rk4_2.txt","rk4_3.txt" };
    files_name_gb = { "rk4_1_gb.txt","rk4_2_gb.txt","rk4_3_gb.txt" };

    j = 0;
    flag = true;
    fp3 = fopen("rk4_an.txt", "w+");

    for (double delT : dt)
    {
        std::cout << "---Plik " << files_name.at(j) << " zostal utwozony dla dt = " << delT << "-- - " << std::endl;

        FILE* fp1 = fopen(files_name.at(j), "w+");
        FILE* fp2 = fopen(files_name_gb.at(j), "w+");
        

        for (double t = tmin; t < tmax; t = t + delT)
        {
            k1 = l * y.at(i);
            k2 = l * (y.at(i) + (0.5*delT * k1));
            k3 = l * (y.at(i) + (0.5 * delT * k2));
            k4 = l * (y.at(i) + (delT * k3));

            y.push_back(y.at(i) + (delT/6 *(k1 + 2*k2 + 2*k3 + k4)));
            
            double gt = y.at(i) - rozw(t, l);
            //std::cout << y.at(i) << " " << rozw(t, l) << " " << gt << std::endl;
            fprintf(fp1, "%g ", t);
            fprintf(fp1, "%g ", y.at(i));
            fprintf(fp1, "\n");
            fprintf(fp2, "%g ", t);
            fprintf(fp2, "%g ", gt);
            fprintf(fp2, "\n");
            if(flag)
            {
            fprintf(fp3, "%g ", t);
            fprintf(fp3, "%g ", rozw(t, l));
            fprintf(fp3, "\n");
            }
            i++;

        }
        y.clear();
        y.push_back(1.0);
        i = 0;
        j++;
        flag = false;
    }

    //---- RRZ 2 RZÊDU

    double dT = pow(10,-4);
    double R = 100.0;
    double L = 0.1;
    double C = 0.001;
    double omg0 = 1 / (sqrt(L * C));
    double T0 = (2 * M_PI)/omg0;

    double kQ1, kI1, kQ2, kI2, kQ3, kI3, kQ4, kI4;

    tmin = 0.0;
    tmax = 4 * T0;
    std::vector<double> omgV= { 0.5 * omg0,0.8 * omg0,1.0 * omg0,1.2 * omg0 };
    std::vector<double> Q;
    std::vector<double> I;
    
    Q.push_back(0.0);
    I.push_back(0.0);
    i = 0;
    j = 0;


    files_name = { "Q_1.txt","Q_2.txt","Q_3.txt","Q_4.txt"};
    files_name_gb = { "I_1.txt","I_2.txt","I_3.txt","I_4.txt" };

    for (double dtt : omgV)
    {
        std::cout << "---Plik " << files_name.at(j) << " zostal utwozony dla omega_v = " << dtt << "-- - " << std::endl;
        auto Vt = [dtt,dT](double t) {return (10 * sin(dtt * t * dT)); };

        FILE* fp1 = fopen(files_name.at(j), "w+");
        FILE* fp2 = fopen(files_name_gb.at(j), "w+");

        for (double t = tmin; t < tmax; t = t + dT)
        {  
            kQ1 = I.at(i);
            kI1 = (Vt(i) / L) - ((Q.at(i) / L * C)) - ((R * I.at(i) / L) );
            kQ2 = I.at(i) + (0.5 * dT * kI1);
            kI2 = (Vt(i + 0.5) / L) - ((Q.at(i) + 0.5 * dT * kQ1) / (L * C))  - ((R * (I.at(i) + 0.5 * dT * kI1) / L) );
            kQ3 = I.at(i) + (0.5 * dT * kI2);
            kI3 = (Vt(i + 0.5) / L) - ((Q.at(i) + 0.5 * dT * kQ2) / (L * C)) - ((R * (I.at(i) + 0.5 * dT * kI2) / L) );
            kQ4 = I.at(i) + (dT * kI3);
            kI4 = (Vt(i + 1) / L) - ((Q.at(i) + dT * kQ3) / (L * C)) - ((R * (I.at(i) + dT * kI3) / L) );
            Q.push_back(Q.at(i) + (dT / 6.0) * (kQ1 + (2.0 * kQ2) + (2.0 * kQ3) + kQ4));
            I.push_back(I.at(i) + (dT / 6.0) * (kI1 + (2.0 * kI2) + (2.0 * kI3) + kI4));
            fprintf(fp1, "%g ", t);
            fprintf(fp1, "%g ", Q.at(i));
            fprintf(fp1, "\n");
            fprintf(fp2, "%g ", t);
            fprintf(fp2, "%g ", I.at(i));
            fprintf(fp2, "\n");
            //std::cout << Q.at(i) <<" "<<I.at(i)<< std::endl;
            i++;
        }
        Q.clear();
        I.clear();  
        Q.push_back(0.0);
        I.push_back(0.0);
        i = 0;
        j++;
    }

    


    
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
