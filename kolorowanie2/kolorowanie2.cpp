// kolorowanie2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

void DFS(int *odwiedzone, int**tab, int v,int liczbaWierz)
{
	odwiedzone[v] = 1;
	for (int i = 1; i < tab[v][liczbaWierz]; i++)
	{
		if (odwiedzone[tab[v][i]] == 0)
		{
			DFS(odwiedzone, tab, tab[v][i], liczbaWierz);
		}
	}
}
bool CzySpojny(int**tab, int liczbaWierz)
{
	int *odwiedzone = new int[liczbaWierz];
	for (int i = 0; i < liczbaWierz; i++)
	{
		odwiedzone[i] = 0;
	}
	DFS(odwiedzone, tab, 0, liczbaWierz);
	for (int i = 0; i < liczbaWierz; i++)
	{
		if (odwiedzone[i] == 0)
		{
			delete[] odwiedzone;
			return false;
		}
	}
	delete[]odwiedzone;
	return true;
}
int Sprawdz(int*nowygraf, int**tab, int iloscWierz, int ilosc)
{
	int min = iloscWierz, maks = 0;
	for (int j = 0; j < ilosc; j++)
	{
		if (tab[nowygraf[j]][iloscWierz] < min)
			min = tab[nowygraf[j]][iloscWierz];
		if (tab[nowygraf[j]][iloscWierz]>maks)
			maks = tab[nowygraf[j]][iloscWierz];
	}
	if (maks == ilosc)
	{
		if (min == ilosc)
		{
			return maks;
		}
		else
		{
			return 0;
		}
	}
	else if (maks == 3)
	{
		if (min == 3 && ilosc % 2 == 1)
			return maks;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}
bool Podziel(int**tab, int liczbaWierz)
{
	int *odwiedzone = new int[liczbaWierz];
	int maks = 0;
	for (int i = 0; i < liczbaWierz; i++)
	{
		odwiedzone[i] = 0;
	}
	int *nowygraf = new int[liczbaWierz];
	for (int i = 0; i < liczbaWierz; i++)
	{
		if (odwiedzone[i] == 0)
		{
			DFS(odwiedzone, tab, i, liczbaWierz);
			int ilosc = 0;
			for (int j = 0; j < liczbaWierz; j++)
			{
				if (odwiedzone[j] == 1)
				{
					odwiedzone[j] = 2;
					nowygraf[ilosc] = j;
					ilosc++;
				}
			}
			int liczba = Sprawdz(nowygraf, tab, liczbaWierz, ilosc);
			if (liczba>maks)
			{
				maks = liczba;
			}
		}
	}
	int stopien=0;
	for (int i = 0; i < liczbaWierz; i++)
	{
		if (tab[i][liczbaWierz]>stopien)
			stopien = tab[i][liczbaWierz];
	}
	delete[]nowygraf;
	delete[]odwiedzone;
	if (maks > stopien - 1)
		return true;
	else
		return false;
}
int main()
{
	std::ios::sync_with_stdio(false);
	int ilosc, liczbaWierz;
	scanf_s("%d", &ilosc);
	for (int i = 0; i < ilosc; i++)
	{
		scanf_s("%d", &liczbaWierz);
		int **tab = new int*[liczbaWierz];
		for (int j = 0; j < liczbaWierz; j++)
		{
			tab[j] = new int[liczbaWierz + 1];
			tab[j][liczbaWierz] = 1;
		}
		string znak;
		cin >> znak;
		for (int j = 0; j < liczbaWierz; j++)
		{
			for (int k = 0; k < liczbaWierz; k++)
			{
				if (znak[j*liczbaWierz + k] == '1')
				{
					tab[j][tab[j][liczbaWierz]] = k;
					tab[j][liczbaWierz]++;
				}
			}
		}
		for (int j = 0; j < liczbaWierz; j++)
		{
			tab[j][0] = j;
		}
		//tab[nrwierzchola][zero] przechowuje numer wierzcholka, natomiast kolejne zawieraja wierzcholki sasiednie, tab[nrwierz][liczbaWierz] przechowuje rozmiar
		if (CzySpojny(tab,liczbaWierz))
		{
			int maks = 0;
			int min = liczbaWierz;
			for (int j = 0; j < liczbaWierz; j++)
			{
				if (tab[j][liczbaWierz] < min)
					min = tab[j][liczbaWierz];
				if (tab[j][liczbaWierz]>maks)
					maks = tab[j][liczbaWierz];
			}
			if (maks == liczbaWierz)
			{
				if (min == liczbaWierz)
				{
					printf("True\n");
				}
				else
				{
					printf("False\n");
				}
			}
			else if (maks == 3)
			{
				if (min == 3 && liczbaWierz % 2 == 1)
					printf("True\n");
				else
					printf("False\n");
			}
			else
			{
				printf("False\n");
			}
		}
		else
		{
			if (Podziel(tab, liczbaWierz))
			{
				printf("True\n");
			}
			else
			{
				printf("False\n");
			}
			
		}
		for (int j = 0; j < liczbaWierz; j++)
		{
			delete[] tab[j];
		}
		delete[] tab;
	}
	return 0;
}

