// imn7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

const double delta = 0.01;
const double rho = 1.0;
const double mi = 1.0;
const int nx = 200;
const int ny = 90;
const int I1 = 50;
const int J1 = 55;
const int it_max = 20000;
const int J2 = J1 + 2;

auto x = [](int i) {return 0.01 * i; };
auto y = [](int j) {return 0.01 * j; };

double qwy(int qwe)
{
    return (qwe * (y(ny)* y(ny)* y(ny) - y(J1)* y(J1)* y(J1) - 3.0 * y(J1) * y(ny)* y(ny)
        + 3.0 * y(J1)* y(J1) * y(ny)))/ (y(ny)* y(ny)* y(ny));
}

bool edge(int i, int j)
{
    if (i == 0 && (j >= J1 && j <= ny))
        return true;
    if (j == ny)
        return true;
    if (i == nx)
        return true;
    if ((i >= I1 && i <= nx) && j == 0)
        return true;
    if (i == I1 && (j >= 0 && j <= J1))
        return true;
    if ((i >= 0 && i <= I1) && j == J1)
        return true;
    return false;
}

int main()
{
    FILE* fp1;
    FILE* fp2;
    FILE* fp3;
    FILE* fp4;

    std::vector<int> Q = { -1000,-4000,4000 };

    for (int q : Q)
    {
        std::string fname1="psi_"+std::to_string(q)+".txt";
        std::string fname2 = "zeta_" + std::to_string(q) + ".txt";
        std::string fname3 = "u_" + std::to_string(q) + ".txt";
        std::string fname4 = "v_" + std::to_string(q) + ".txt";

        fp1 = fopen(fname1.c_str(), "w");
        fp2 = fopen(fname2.c_str(), "w");
        fp3 = fopen(fname3.c_str(), "w");
        fp4 = fopen(fname4.c_str(), "w");

        auto psi = new double[nx + 1][ny + 1];
        auto zeta = new double[nx + 1][ny + 1];
        auto u = new double[nx + 1][ny + 1];
        auto v = new double[nx + 1][ny + 1];

        for (int j = J1; j <= ny; j++)
        {
            psi[0][j] = (q / (2.0 * mi) *(( y(j)* y(j)* y(j)) / 3.0 - (y(j)* y(j) * (y(J1) + y(ny))) / 2.0 + (y(j) * y(J1) * y(ny))));

        }

        for (int j = 0; j <= ny; j++)
        {
            psi[nx][j] = (qwy(q) / (2.0 * mi)) * ((y(j) * y(j) * y(j)) / 3.0 
                - (y(j)* y(j))* y(ny)/2.0) +
                  (q* y(J1)* y(J1)*(-y(J1) + 3.0 * y(ny)))/(12.0*mi);
        }

        for (int i = 1; i < nx; i++)
        {
            psi[i][ny] = psi[0][ny];
        }

        for (int i = I1; i < nx; i++)
        {
            psi[i][0] = psi[0][J1];
        }

        for (int j = 1; j <= J1; j++)
        {
            psi[I1][j] = psi[0][J1];
        }

        for (int i = 1; i <= I1; i++)
        {
            psi[i][J1] = psi[0][J1];
        }

        
        double omega;

        for (int it = 1; it <= it_max; it++)
        {
            it < 2000 ? omega = 0 : omega = 1;

            for (int i = 1; i < nx; i++)
            {
                for (int j = 1; j < ny; j++)
                {
                    if (!edge(i, j))
                    {
                        psi[i][j] = 0.25 * (psi[i + 1][j] + psi[i - 1][j]
                            + psi[i][j + 1] + psi[i][j - 1] - (delta * delta * zeta[i][j]));
                     
                            zeta[i][j] = 0.25 * (zeta[i + 1][j] + zeta[i - 1][j] + zeta[i][j + 1] + zeta[i][j - 1])
                            - omega * (rho / (16.0 * mi)
                            * ((psi[i][j + 1] - psi[i][j - 1]) * (zeta[i + 1][j] - zeta[i - 1][j]) - (psi[i + 1][j] - psi[i - 1][j])
                                * (zeta[i][j + 1] - zeta[i][j - 1])));
                    

                        u[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2.0 * delta);
                        v[i][j] = -(psi[i + 1][j] - psi[i - 1][j]) / (2.0 * delta);
                    }
                }
            }

            for (int j = J1; j <= ny; j++)
            {
                zeta[0][j] = q / (2 * mi) * (2.0 * y(j) - y(J1) - y(ny));
            }
            for (int j = 0; j <= ny; j++)
            {
                zeta[nx][j] = qwy(q) / (2.0 * mi) * (2.0 * y(j) - y(ny));
            }
            for (int i = 1; i < nx; i++)
            {
                zeta[i][ny] = (2.0/ (delta * delta)) * (psi[i][ny - 1] - psi[i][ny]);
            }
            for (int i = I1 + 1; i < nx; i++)
            {
                zeta[i][0] = (2.0/ (delta * delta)) * (psi[i][1] - psi[i][0]);
            }
            for (int j = 1; j < J1; j++)
            {
                zeta[I1][j] = (2.0/ (delta * delta)) * (psi[I1 + 1][j] - psi[I1][j]);
            }
            for (int i = 1; i <= I1; i++)
            {
                zeta[i][J1] = (2.0/ (delta * delta)) * (psi[i][J1 + 1] - psi[i][J1]);
            }

            zeta[I1][J1] = 0.5 * (zeta[I1 - 1][J1] + zeta[I1][J1 - 1]);

            double gamma = 0.0;

            for (int i = 1; i < nx; i++)
            {
                gamma += psi[i + 1][J2] + psi[i - 1][J2] + psi[i][J2 + 1] + psi[i][J2 - 1] - (4.0 * psi[i][J2]) - (delta * delta * zeta[i][J2]);
            }
            std::cout << it << " Gamma = " << gamma << "\n";
        }
          
        for (int i = 0; i < I1; i++)
        {
            psi[i][0] = 0.0;
            zeta[i][0] = 0.0;
            u[i][0] = 0.0;
            v[i][0] = 0.0;
        }
        for (int j = 0; j < J1; j++)
        {
            psi[0][j] = 0.0;
            zeta[0][j] = 0.0;
            u[0][j] = 0.0;
            v[0][j] = 0.0;
        }

        for (int i = 0; i <= nx; i++)
        {
            for (int j = 0; j <= ny; j++)
            {
                if (isnan(psi[i][j]) || isnan(zeta[i][j]) || isnan(u[i][j]) || isnan(v[i][j]))
                { 
                    psi[i][j] = 0.0;
                    zeta[i][j] = 0.0;
                    u[i][j] = 0.0;
                    v[i][j] = 0.0;
                }
                fprintf(fp1, "%g %g %g\n", 0.01 * i, 0.01 * j, psi[i][j]);
                fprintf(fp2, "%g %g %g\n", i * 0.01, j * 0.01, zeta[i][j]);
                fprintf(fp3, "%g %g %g\n", i * 0.01, j * 0.01, u[i][j]);
                fprintf(fp4, "%g %g %g\n", i * 0.01, j * 0.01, v[i][j]);
            }
            fprintf(fp1, "\n");
            fprintf(fp2, "\n");
        }
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
