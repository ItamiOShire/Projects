// imn5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#define M_PI 3.14159265358979323846

double sq(double p)
{
    return p*p;
}

const double delta = 0.2;
const int nx = 128;
const int ny = 128;
const double xmax = delta * nx;
const double ymax = delta * ny;
const double TOL = pow(10, -8);
FILE* fps;
FILE* fpv;

double vb1(double y)
{
    return sin(M_PI * delta * y / ymax);
}
double vb2(double x)
{
    return -sin(2.0 * M_PI * delta * x / xmax);
}
double vb3(double y)
{
    return sin(M_PI * delta * y / ymax);
}
double vb4(double x)
{
    return sin(2.0 * M_PI * delta * x / xmax);
}

int main()
{
    std::vector<int> kk = { 16,8,4,2,1 };
    auto v = new double[nx + 1][ny + 1];

    for (int x = 0; x <= nx; x++)
    {
        v[x][ny] = vb2(x);
        v[x][0] = vb4(x);
    }

    for (int y = 0; y <= ny; y++)
    {
        v[0][y] = vb1(y);
        v[nx][y] = vb3(y);
    }

    int it = 0;

    for (int k : kk)
    {
        int kit = 0;
        double prevs=TOL;
        double nexts;
        std::string fname = "s_" + std::to_string(k) + ".txt";
        std::string fnamev = "v_" + std::to_string(k) + ".txt";
        fps = fopen(fname.c_str(), "w");
        fpv = fopen(fnamev.c_str(), "w");

        while (true)
        {
            it += 1;
            kit += 1;

            for (int i = k; i < nx; i = i + k)
            {
                for (int j = k; j < ny; j = j + k)
                {
                    v[i][j] = 0.25 * (v[i + k][j] + v[i - k][j] + v[i][j + k] + v[i][j - k]);
                }
            }

            nexts = 0.0;

            for (int i = 0; i < nx; i = i + k)
            {
                for (int j = 0; j < ny; j = j + k)
                {
                    nexts += sq(k * delta) * 0.5 *
                        (sq((v[i + k][j] - v[i][j] + v[i + k][j + k] - v[i][j + k]) / (2.0 * k * delta))
                            + sq((v[i][j + k] - v[i][j] + v[i + k][j + k] - v[i + k][j]) / (2.0 * k * delta)));
                }
            }
            fprintf(fps, "%d %g\n", it, nexts);

            if (fabs((nexts - prevs) / prevs) < TOL)
            {
                break;
            }
            prevs = nexts;
        }

        for (int i = 0; i <= nx; i=i+k)
        {
            for (int j = 0; j <= ny; j=j+k)
            {
                fprintf(fpv,"%g ",v[j][i]);
            }
            fprintf(fpv, "\n");
        }

        if (k != 1)
        {
            for (int i = 0; i < nx; i = i + k)
            {
                for (int j = 0; j < ny; j = j + k)
                {
                    v[i + k / 2][j + k / 2] = 0.25 * (v[i][j] + v[i + k][j] + v[i][j + k] + v[i + k][j + k]);
                    v[i + k][j + k / 2] = 0.5 * (v[i + k][j] + v[i + k][j + k]);
                    v[i + k / 2][j + k] = 0.5 * (v[i][j + k] + v[i + k][j + k]);
                    v[i + k / 2][j] = 0.5 * (v[i][j] + v[i + k][j]);
                    v[i][j + k / 2] = 0.5 * (v[i][j] + v[i][j + k]);
                }
            }
        }

        

        for (int x = 0; x <= nx; x++)
        {
            v[x][ny] = vb2(x);
            v[x][0] = vb4(x);
        }

        for (int y = 0; y <= ny; y++)
        {
            v[0][y] = vb1(y);
            v[nx][y] = vb3(y);
        }
        fclose(fps);
        fclose(fpv);
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
