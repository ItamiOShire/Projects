// imn2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable:4996)
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    double beta = 0.001;
    int N = 500;
    double gamma = 0.1;
    int tmax = 100;
    double dt = 0.1;
    double tol = pow(10, -6);
    double alfa = (beta * N) - gamma;
    int mi_max = 20;
    int n = 0;

       
    std::vector<double> u;
    std::vector<double> z;
    u.push_back(1.0);

    double u_p, u_n;

    FILE* fp1 = fopen("picard_u.txt", "w+");
    FILE* fp2 = fopen("picard_v.txt", "w+");

    // ---- METODA PICARD'A ----

    for (double t = 0.0; t < tmax; t = t + dt)
    {
        u_p = u.at(n);
        for (int mi = 0; mi <= mi_max; mi++)
        {
            u_n = u.at(n) + (dt * ((alfa * u.at(n) - beta * pow(u.at(n), 2)) + (alfa * u_p - beta * pow(u_p, 2)))) / 2;
            if (abs(u_n - u_p) < tol)
                break;
            u_p = u_n;
        }
        u.push_back(u_n);
        z.push_back(N - u.at(n));
        fprintf(fp1, "%g %g\n", t, u.at(n));
        fprintf(fp2, "%g %g\n", t, z.at(n));
        n++;   
    }

    u.clear();
    z.clear();
    u.push_back(1.0);
    n = 0;
    fclose(fp1);
    fclose(fp2);
    std::cout << "Wyniki obliczone metoda Picarda zosta³y zapisane do pliku" << std::endl;


    fp1 = fopen("newton_u.txt", "w+");
    fp2 = fopen("newton_v.txt", "w+");

    // ---- METODA NETWON'A ----

    for (double t = 0.0; t < tmax; t = t + dt)
    {
        u_p = u.at(n);
        for (int mi = 0; mi <= mi_max; mi++)
        {
            u_n = u_p - (u_p - u.at(n) - (dt * ((alfa * u.at(n) - beta * pow(u.at(n), 2)) + (alfa * u_p - beta * pow(u_p, 2)))) / 2)/(1-dt*(alfa - 2*beta*u_p)/2);
            if (abs(u_n - u_p) < tol)
                break;
            u_p = u_n;
        }
        u.push_back(u_n);
        z.push_back(N - u.at(n));
        fprintf(fp1, "%g %g\n", t, u.at(n));
        fprintf(fp2, "%g %g\n", t, z.at(n));
        n++;
    }

    u.clear();
    z.clear();
    u.push_back(1.0);
    n = 0;
    fclose(fp1);
    fclose(fp2);
    std::cout << "Wyniki obliczone metoda Netwon'a zostaly zapisane do piku" << std::endl;


    // ---- METODA RK2 ----


    double a[2][2] = { {0.25,0.25 - (sqrt(3) / 6)},{0.25 + (sqrt(3) / 6),0.25} };
    double b[2] = { 0.5,0.5 };
    double m11, m12, m21, m22;
    double U1, U2, U1_n, U2_n;

    fp1 = fopen("rk2_u.txt", "w+");
    fp2 = fopen("rk2_v.txt", "w+");

    auto wsp = [alfa, beta](double U) {return alfa - 2 * beta * U; };
    auto F1 = [alfa, beta, a, dt](double U1, double U2, double u)
    {
        return U1 - u - dt * (a[0][0] * (alfa * U1 - beta * pow(U1, 2)) + a[0][1] * (alfa * U2 - beta * pow(U2, 2)));
    };
    auto F2 = [alfa, beta, a, dt](double U1, double U2, double u)
    {
        return U2 - u - dt * (a[1][0] * (alfa * U1 - beta * pow(U1, 2)) + a[1][1] * (alfa * U2 - beta * pow(U2, 2)));
    };
    auto f = [alfa, beta](double u) {return alfa * u - beta * pow(u, 2); };

    for (double t = 0.0; t < tmax; t = t + dt)
    {
        U1 = u.at(n);
        U2 = u.at(n);
        for (int mi = 0; mi <= mi_max; mi++)
        {
            m11 = 1 - dt * a[0][0] * wsp(U1);
            m12 = -dt * a[0][1] * wsp(U2);
            m21 = -dt * a[1][0] * wsp(U1);
            m22 = 1 - dt * a[1][1] * wsp(U2);

            U1_n = U1 +(F2(U1, U2, u.at(n)) * m12 - F1(U1, U2, u.at(n)) * m22) / (m11 * m22 - m12 * m21);
            U2_n = U2 +(F1(U1, U2, u.at(n)) * m21 - F2(U1, U2, u.at(n)) * m11) / (m11 * m22 - m12 * m21);

            if (abs(U1_n - U1) < tol and abs(U2_n - U2) < tol)
                break;
            U1 = U1_n;
            U2 = U2_n;
        }
        u.push_back(u.at(n) + dt * (b[0] * f(U1) + b[1] * f(U2)));
        z.push_back(N - u.at(n));
        fprintf(fp1, "%g %g\n", t, u.at(n));
        fprintf(fp2, "%g %g\n", t, z.at(n));
        n++;
    }
    fclose(fp1);
    fclose(fp2);
    std::cout << "Wyniki obliczone metoda RK2 zostaly zapisane do pliku" << std::endl;
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
