/*
    EWELINA KOLBA
    04.12.2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>

int main() {
        std::string filename;
        int X=0;
        int Y=0;
        int MCS=0;
        int i = 0;
        std::string temp="";
        std::vector < int > dem;
        std::vector < double > T;
        double m4;  //moment centralny 4 rzêdu == kurtoza
        double m2;  //moment centralny 2 rzêdu == wariancja
        
        std::cin >> temp;
        X = std::stoi(temp);
        temp = "";
        std::cin >> temp;
        Y = std::stoi(temp);
        temp = "";
        std::cin >> temp;
        MCS = std::stoi(temp);
        temp = "";
        std::cin >> temp;
        i = std::stoi(temp);
        temp = "";
        for (int k = 0; k < i; k++) {
            std::cin >> temp;
            dem.push_back(std::stoi(temp));
            temp = "";
        }

        //model
        int **sp = new int *[X];
        for (int i = 0; i < X; i++) {
            sp[i] = new int[Y];
        }

        double demon, en,mag,en_C, m_mag, m_demon, m_mag2,stab;
        int r1 = 0, r2 = 0;
        int *demonTab = new int[MCS];
        int* magTab = new int[MCS];


        srand(time(NULL));

        std::fstream zapis("C:\\Users\\Max\\Desktop\\dane.txt");

         for (int k = 0; k < dem.size(); k++) {

             stab = 0.0; m_mag = 0.0; m_demon = 0.0; demon = dem[k]; m_mag2 = 0.0, en_C = 0.0;
             int iMinus1=0, iPlus1=0, jMinus1=0, jPlus1=0;

             // INICJALIZACJA UKLADU WARTOŒCIAMI 1
             for (int i = 0; i < X; i++)
             {
                 for (int j = 0; j < Y; j++) {
                     sp[i][j] = 1;
                 }
             }
             //// INICJALIZACJA UKLADU WARTOŒCIAMI 1 I -1
             /*for (int i = 0; i < MCS / 2; i++) {
                 sp[rand() % X][rand() % Y] = -1;
             }*/
             
             //OBLICZAMY ENERGIÊ CA£KOWIT¥ UK£ADU
             for (int i = 0; i < X; i++) {
                 for (int j = 0; j < Y; j++) {
                     if (i - 1 < 0) iMinus1 = X - 1;
                     else iMinus1 = i - 1;
                     if (j + 1 > Y - 1) jPlus1 = 0;
                     else jPlus1 = j + 1;
                     en_C += -((sp[i][j] * sp[iMinus1][j]) + (sp[i][j] * sp[i][jPlus1]));
                 }
             }
             //WYŒWIETLENIE UK£ADU W STANIE POCZATKOWYM PRZED DOKONANIEM ZMIAN SPINÓW
             /*for (int i = 0; i < X; i++) {
                 for (int j = 0; j < Y; j++)
                 {
                     std::cout << sp[i][j] << " ";
                 }
                 std::cout << std::endl;
             }
             std::cout << std::endl;*/

             ////stabilizacja
             ////for (float p = 0.01; p <= 3.99; p += 0.01)
             ////{
             //   // if (p <= 0.5) stab = (int)(p * 10000.0);
             //    else stab = (int)(10000.0 * (1.0 - p));

             //    m_mag = 0.0; m_demon = 0.0; demon = dem[k]; m_mag2 = 0.0;
             //    double suma_mag = 0;
             //    double suma_dem = 0;
             //    double suma2_dem = 0;
                 //SYMULACJA
                 for (int krok = 1; krok <= stab+MCS; krok++)
                 {
                     // OBLICZANIE ENERGII DLA KONKRETNEGO LOSOWEGO SPINU
                     r1 = rand() % (X);
                     r2 = rand() % (Y);
                     if (r1 - 1 < 0) iMinus1 = X - 1;
                     else iMinus1 = r1 - 1;
                     if (r1 + 1 > X - 1) iPlus1 = 0;
                     else iPlus1 = r1 + 1;
                     if (r2 - 1 < 0) jMinus1 = Y - 1;
                     else jMinus1 = r2 - 1;
                     if (r2 + 1 > Y - 1) jPlus1 = 0;
                     else jPlus1 = r2 + 1;
                     en = -((-2 * (sp[r1][r2] * sp[iPlus1][r2])) + ((-2) * (sp[r1][r2] * sp[iMinus1][r2])) + ((-2) * (sp[r1][r2] * sp[r1][jMinus1])) + ((-2) * (sp[r1][r2] * sp[r1][jPlus1])));

                     if (demon - en > 0) {
                         demon -= en;
                         sp[r1][r2] = -sp[r1][r2];
                     }

                     //if (krok >= stab) {
                         m_demon += (double)demon / (double)(X * Y);
                         //suma_dem += m_demon;
                         //suma2_dem += m_demon * m_demon;
                     //}
                     //OBLICZANIE MAGNETYZACJI I MODULU MAGNETYZACJI DLA UKLADU
                     mag = 0.0;
                     m_mag = 0.0;

                     /*for (int i = 0; i < X; i++) {
                         for (int j = 0; j < Y; j++)
                         {
                             mag += sp[i][j];
                         }
                     }*/
                     //if (krok >= stab)
                     //{
                         mag = 0;
                         for (int w = 0; w < X; w++) {
                             for (int k = 0; k < Y; k++) {
                                 mag += sp[w][k];
                             }
                         }
                         m_mag += (double)mag / (double)(X * Y);
                     //}

                     //suma_mag += m_mag;
                    
                     // ENERGIA CA£KOWITA UK£ADU PO DOKONANIU ZMIANY
                     en_C = 0;
                     for (int i = 0; i < X; i++) {
                         for (int j = 0; j < Y; j++) {
                             if (i - 1 < 0) iMinus1 = X - 1;
                             else iMinus1 = i - 1;
                             if (j + 1 > Y - 1) jPlus1 = 0;
                             else jPlus1 = j + 1;
                             en_C += -((sp[i][j] * sp[iMinus1][j]) + (sp[i][j] * sp[i][jPlus1]));
                         }
                     }

                     // WYSWIETLENIE UKLADU
                     //std::cout << "en: " << en << std::endl;
                     //std::cout << "demon: " << demon << std::endl;
                     //std::cout << "mag: " << mag << std::endl;
                     //std::cout <<"demon: "<<demon<< "  m_mag: " << m_mag << " " << "T: " << T[krok-1] << std::endl;
                     //std::cout << "m_mag: " << m_mag << std::endl;
                     //std::cout << "en_c: " << en_C << std::endl;

                         /*for (int i = 0; i < X; i++) {
                             for (int j = 0; j < Y; j++)
                             {
                                 std::cout << sp[i][j] << " ";
                             }
                             std::cout << std::endl;
                         }
                         std::cout << std::endl; */

                         // ZAPIS DO PLIKU
                     //zapis << krok - 1 << " " << abs(m_mag) << std::endl;
                     std::cout << krok - 1 << " " << abs(m_mag) << std::endl;

                     
                     

                 }
                // PROÓBY OBLICZENIA TEMPERATURY
                 //if (m_demon > 0) zapis << (0.25 * log(1.0 + 4.0 / m_demon)) << " " << abs(m_mag) << std::endl;
                 //t = (0.25 * log(1.0 + 4.0 / m_demon));
                 //double t;
                 //if (m_demon > 0) t = (-1.0 / ((log((1/p)-1)/((-2)*m_mag))));
                 /*if (m_demon>0) t = (-1.0 / ((((suma_dem + MCS) *X*Y) - (suma_dem - MCS)) / ((X*Y* suma2_dem) - pow(suma_dem,2))));*/

                  //if (m_demon > 0) zapis << (0.25 * log(1.0 + 4.0 / m_demon)) << " " << abs(m_mag) << std::endl;
                //if (m_demon > 0) zapis << p << " " << abs(m_mag) << std::endl;

             //}
             
         }
        return 0;
    }