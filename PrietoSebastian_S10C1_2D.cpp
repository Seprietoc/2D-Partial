#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <array>

using namespace std;
ofstream outfile;

const double Tfija = 50;
const double Ty = 100;
const double tf = 2500;
const int L = 100;
const int dl = 1;
const double v = 1e-4;
double dt = 0.25*dl*dl/v;
const int Nx = L/dl;
const int Nt = tf/dt;

void temperature(array<array<double, Nx>, Nx>& xpresent, array<array<double, Nx>, Nx>& xfuture, int parameter);
void initialization(array<array<double, Nx>, Nx>& placa);
void writefile(array<array<double, Nx>, Nx>& placa);

int main(void)
{
    array<array<double, Nx>, Nx> x;
    array<array<double, Nx>, Nx> xnew;
    string list[3] = {"evotemp.dat", "evotempperiod.dat", "evotempabierta.dat"};

    for (int i = 0; i < 3; i++)
    {
        initialization(xnew);
        outfile.open(list[i]); 
        writefile(xnew);
        for (int t = 1; t <= tf; t++)
        {
            x = xnew;
            temperature(x, xnew, i);

            if (t == 100)
                writefile(x);
            else if (t == 1000)
                writefile(x);
            else if (t == 2500)
                writefile(x);
        }
        outfile.close();
    }
}

void initialization(array<array<double, Nx>, Nx>& placa)
{   
    for (int i = 0; i < Nx; i++)
    {
        for (int j = 0; j < Nx; j++)
        {
            if ((i > 39 && j > 19) && (i < 59 && j < 39))
            {
                placa[i][j] = Ty;
            }
            else
                placa[i][j] = Tfija;
        }
    }
}


void temperature(array<array<double, Nx>, Nx>& xpresent, array<array<double, Nx>, Nx>& xfuture, int parameter)
{
    
    for (int i = 1; i < Nx - 1; i++)
    {
        // calculate the next step 
        for (int j = 1; j < Nx - 1; j++)
        {

            xfuture[i][j] = xpresent[i][j] + dt*v*((xpresent[i+1][j] - 2*xpresent[i][j] + xpresent[i-1][j])/(dl*dl) + 
                                                   (xpresent[i][j+1] - 2*xpresent[i][j] + xpresent[i][j-1])/(dl*dl));
        }
    }

    // case 1: periodic extremes, case 2: open extremes, else: fixed extremes
    switch (parameter)
    {   
        case 1:
        for (int i = 0; i < Nx; i++)
        {
            xfuture[i][0] = xfuture[i][Nx - 2];
            xfuture[i][Nx - 1] = xfuture[i][1];
            xfuture[0][i] = xfuture[Nx - 2][i];
            xfuture[Nx - 1][i] = xfuture[1][i];
        }
        return;

        case 2:
        for (int i = 0; i < Nx; i++)
        {
            xfuture[i][0] = xfuture[i][1];
            xfuture[i][Nx - 1] = xfuture[i][Nx - 2];
            xfuture[0][i] = xfuture[1][i];
            xfuture[Nx - 1][i] = xfuture[Nx - 2][i];
        }
        return;

        default:
        return;
    }   
}

void writefile(array<array<double, Nx>, Nx>& placa)
{
    for (int i = 0; i < Nx; i++)
    {
        for (int j = 0; j < Nx - 1; j++)
        {
            outfile << placa[i][j] << ",";
        }
        outfile << placa[i][Nx - 1] << endl;
    }
    return;
}