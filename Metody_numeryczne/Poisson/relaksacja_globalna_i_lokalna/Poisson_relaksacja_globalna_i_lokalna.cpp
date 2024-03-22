// imn4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable:4996)
#include <iostream>
#include <cmath>
#include <vector>

double pow(double p)
{
    return p * p;
}
double ro1(double xmax, double ymax, double sigmax, double sigmay, double x, double y)
{
    return exp(-pow(x - 0.35 * xmax) / (sigmax * sigmax) - pow(y - 0.5 * ymax) / (sigmay * sigmay));
}
double ro2(double xmax, double ymax, double sigmax, double sigmay, double x, double y)
{
    return -exp(-pow(x - 0.35 * xmax) / (sigmax * sigmax) - pow(y - 0.5 * ymax) / (sigmay * sigmay));
}

int main()
{
    double eps = 1.0;
    double delta = 0.1;
    const int nx = 150;
    const int ny = 100;
    double V1 = 10.0;
    double V2 = 0;
    double xmax = delta * nx;
    double ymax = delta * ny;
    double sigmax = 0.1 * xmax;
    double sigmay = 0.1 * ymax;
    double TOL = pow(10, -8);

    
    std::vector<double> omegag = { 0.6,1.0 };
    auto Vs = new double[nx+1][ny+1];
    auto Vn = new double[nx+1][ny+1];   
    auto Err = new double[nx + 1][ny + 1];
    auto ro = new double[nx + 1][ny + 1];

    auto V = new double[nx + 1][ny + 1];

    
    //auto ro1 = [xmax, ymax, sigmax, sigmay](double x, double y) {return exp(-pow(x - 0.35 * xmax, 2) / (sigmax * sigmax) - pow(y - 0.5 * ymax, 2) / (sigmay*sigmay)); };
    //auto ro2 = [xmax, ymax, sigmax, sigmay](double x, double y) {return -exp(-pow(x - 0.65 * xmax, 2) / (sigmax * sigmax) - pow(y - 0.5 * ymax, 2) / (sigmay * sigmay)); };

    FILE* fp1 = fopen("sit1.txt", "w+");
    FILE* fp2 = fopen("sit2.txt", "w+");
    FILE* fp3 = fopen("err1.txt", "w+");
    FILE* fp4 = fopen("err2.txt", "w+");
    FILE* fp5 = fopen("vn1.txt", "w+");
    FILE* fp6 = fopen("vn2.txt", "w+");

    FILE* fp7 = fopen("sitl1.txt", "w+");
    FILE* fp8 = fopen("sitl2.txt", "w+");
    FILE* fp9 = fopen("sitl3.txt", "w+");
    FILE* fp10 = fopen("sitl4.txt", "w+");

    for (int i = 0; i <= nx; i++)
    {
        for (int j = 0; j <= ny; j++)
        {
            ro[i][j] = ro1(xmax,ymax,sigmax,sigmay,i * delta, j * delta) + ro2(xmax, ymax, sigmax, sigmay, i * delta, j * delta);
        }
    }
    //relaksacja globalna
    for (double omg : omegag)
    {
        for (int i = 0; i <= nx; i++)
        {
            for (int j = 0; j <= ny; j++)
            {
                Vs[i][j] = 0.0;
                Vn[i][j] = 0.0;
                Err[i][j] = 0.0;
                ro[i][j] = 0.0;
            }
        }

        for (int i = 0; i <= nx; i++)
        {
            Vs[i][0] = V1;
            Vn[i][0] = V1;
            Vs[i][ny] = V2;
        }

        double prevs;
        double nexts=0.0;
        int it = 0;
        while(true)
        {

            it=it+1;
            for (int i = 1; i < nx; i++)
            {
                for (int j = 1; j < ny; j++)
                {
                    Vn[i][j] = 0.25 * (Vs[i + 1][j] + Vs[i - 1][j] + Vs[i][j + 1] + Vs[i][j - 1] + (delta * delta * ro[i][j]/eps) );
                    
                }
                
            }
            for (int j = 1; j < ny; j++)
            {
                Vn[0][j] = Vn[1][j];
                Vn[nx][j] = Vn[nx - 1][j];
            }

            for (int i = 0; i <= nx; i++)
            {
                for (int j = 0; j <= ny; j++)
                {
                    Vs[i][j] = (1.0 - omg) * Vs[i][j] + omg * Vn[i][j];
                  
                }
            }

            prevs = nexts;
            nexts = 0.0;

            for (int i = 0; i < nx; i++)
            {
                for (int j = 0; j < ny; j++)
                {
                    nexts += delta * delta * (0.5 * pow((Vs[i + 1][j] - Vs[i][j]) / delta) + 0.5 * pow((Vs[i][j + 1] - Vs[i][j]) / delta) - ro[i][j]* Vs[i][j]);
                    /*if (omg == 0.6)
                        fprintf(fp5, "%g %g %g\n", i * delta, j * delta, Vn[i][j]);
                    else
                        fprintf(fp6, "%g %g %g\n", i * delta, j * delta, Vn[i][j]);*/
                }
            } 
            if(omg==0.6)
                fprintf(fp1, "%d %g\n", it, nexts);
            else
                fprintf(fp2, "%d %g\n", it, nexts);
            if (fabs((nexts - prevs) / prevs) < TOL)
            {
                break;
            }
        }
        for (int i = 1; i < nx; i++)
        {
            for (int j = 1; j < ny; j++)
            {
                Err[i][j] = (Vn[i + 1][j] - 2.0 * Vn[i][j] + Vn[i-1][j]) / (delta * delta) + (Vn[i][j + 1] - 2.0 * Vn[i][j] + Vn[i][j - 1]) / (delta * delta) + ro[i][j] / eps;
                if (omg == 0.6)
                {
                    fprintf(fp3, "%g %g %g\n", i * delta, j * delta, Err[i][j]);
                    fprintf(fp5, "%g %g %g\n", i * delta, j * delta, Vn[i][j]);
                }
                else
                {
                    fprintf(fp4, "%g %g %g\n", i * delta, j * delta, Err[i][j]);
                    fprintf(fp6, "%g %g %g\n", i * delta, j * delta, Vn[i][j]);
                }
            }
        }
       
        
    }
    omegag = { 1.0,1.4,1.8,1.9 };
    //relaksacja lokalna
    for (double omg : omegag)
    {
        for (int i = 0; i < nx; i++)
        {
            for (int j = 0; j < ny; j++)
            {
                V[i][j] = 0.0;
                
            }
        }

        for (int i = 0; i <= nx; i++)
        {
            V[i][0] = V1;   
        }

        double prevs;
        double nexts = 0.0;
        int it = 0;
        while (true)
        {

            it = it + 1;
            for (int i = 1; i < nx; i++)
            {
                for (int j = 1; j < ny; j++)
                {
                    V[i][j] = (1.0 - omg) * V[i][j] + 0.25 * omg * (V[i + 1][j] + V[i - 1][j] + V[i][j + 1] + V[i][j - 1] + delta * delta * ro[i][j] / eps);
                }

            }
            for (int j = 1; j < ny; j++)
            {
                V[0][j] = V[1][j];
                V[nx][j] = V[nx - 1][j];
            }


            prevs = nexts;
            nexts = 0.0;

            for (int i = 0; i < nx; i++)
            {
                for (int j = 0; j < ny; j++)
                {
                    nexts += delta * delta * (0.5 * pow((V[i + 1][j] - V[i][j]) / delta, 2) + 0.5 * pow((V[i][j + 1] - V[i][j]) / delta, 2) - ro[i][j] * V[i][j]);
                    
                }
            }
            if (omg == 1.0)
                fprintf(fp7, "%d %g\n", it, nexts);
            else if(omg == 1.4)
                fprintf(fp8, "%d %g\n", it, nexts);
            else if(omg==1.8)
                fprintf(fp9, "%d %g\n", it, nexts);
            else
                fprintf(fp10, "%d %g\n", it, nexts);
            if (fabs((nexts - prevs) / prevs) < TOL)
            {
                break;
            }
        }

    }

    fclose(fp1);
    return 0;
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
