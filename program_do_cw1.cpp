//program demonstracyjny, kompilowany w Dev C++,
//na pocz¹tku programu za³¹czamy biblioteki i pliki naglowkowe ze zdefiniowanymi funkcjami
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
//Pliki z rozszerzeniem .h zawieraja tylko prototypy funkcji, kody znajduja
//sie w plikach o tych samych nazwach lecz z rozszerzeniem .cpp
#include "matrix.h"

//deklarujemy u¿ywanie przestrzeni nazw std, zawieraj¹cej wiele przydatnych komend,
//je¿eli nie zdeklarowalibyœmy przestrzeni nazw std, przed komendami tej przestrzeni nale¿a³oby u¿yæ zapisu std::
// np. std::cout<<"tekst";         
using namespace std;
double** dodaj2s(double **tab, int &tab_size, int a,  std::string c); //metoda do powiekszania tablicy 2 wymiarowej
//w funkcji main mamy nasz g³ówny program,
int main (void) {
cout<<"Program pomocniczy do cw1\n";

//definiujemy nazwe pliku, musi istnieæ w katalogu programu
string nazwap="australian.txt";

//korzystamy z funkcji umieszczonych w pliku matrix.h
// w celu znalezienia rozmiaru wczytywanego pliku,
//plik powinien byc w formacie
//6 2 5 6 1
//5 8 9 2 0
int wym2=num_rows_file(nazwap.c_str());
int wym1=num_cols_file(nazwap.c_str());

//teraz deklarujemy dynamicznie tablice do, której wczytamy nasz plik,
int rows = wym2+1;
std::string **G;
G = new std::string*[rows];
while(rows--) G[rows] = new std::string[wym1+1];

////wczytujemy tablice w postaci string, czyli jej elementy traktujemy jako stringi(ci¹gi znaków)
//wym2 to liczba wierszy
//wym1 to liczba kolumn
//G nasza tablica stringów
//nazwap.c_str() podajemy nazwe wczytywanego pliku w odpowiednim formacie do funkcji.
cout<<"\n\nNacisnij ENTER aby wczytac tablice o nazwie "<< nazwap;
getchar();
wczytywanie(wym2,wym1,G,nazwap.c_str());
//wypisujemy wczytan¹ tablicê na ekran
cout<<"\nWypisujemy na ekran wczytana tablice\n\n";
for(int i=1;i<wym2+1;i++){
  for(int j=1;j<wym1+1;j++){
    cout<<" "<<G[i][j];
  }
  cout<<"\n";
} 

//definiujemy nazwe pliku typu atrybutow, musi istnieæ w katalogu programu
string nazwa_atr_type="australian-type.txt";

//teraz deklarujemy dynamicznie tablice do, której wczytamy nasz plik,
rows = wym2+1;
std::string **atr_type;
atr_type = new std::string*[rows];
while(rows--) atr_type[rows] = new std::string[4];

cout<<"\n\nNacisnij ENTER aby wczytac tablice o nazwie "<< nazwa_atr_type;
getchar();
wczytywanie(wym1,2,atr_type,nazwa_atr_type.c_str());
//wypisujemy wczytan¹ tablicê na ekran
cout<<"\nWypisujemy na ekran wczytana tablice\n\n";

for(int i=1;i<wym1+1;i++){
  for(int j=1;j<2+1;j++){
    cout<<" "<<atr_type[i][j];
  }
  cout<<"\n";
} 

//******************************************************
//MIEJSCE NA ROZWIAZANIE 
 	int class_size = 0; //iloœæ klas decyzyjnych
	double max[wym1+1]; //maxymalna wartoœæ danego ardumentu
	double min[wym1+1]; //minimalna wartoœæ danego argumentu
	double suma[wym1+1]; // suma wartoœci danych argumentów
	double klasy[10];
	int liczklas[10];
	double odchylenie[wym1+1]; // odchylenie standardowe poszczególnych argumentów
	int size_a=1; //licznik ró¿nych argumentów systemu
	int b = 3; //zmienna pomocnicza
	double **AR; //tablica dwuwymiarowa która przechowuje nr argumentów oraz klas decyzyjnych AR[0][*] ich wartoœc AR[1][*] i iloœæ ich wystêpowania AR[2][*] 
	int liczA[wym1]; // tablica ró¿nych argumentów
	//************ustawienie wartoœci pocz¹tkowych
	AR= new double*[b];
	int q=50;
	while(b--) AR[b] = new double[20];
		AR[0][0]=1;
		AR[1][0]=string_to_double(G[1][1]);
		AR[2][0]=0;
	for(int j=1;j<=wym1;j++)
	{
	 	if(atr_type[j][2]=="n")
		{
		 	max[j]=string_to_double(G[1][j]);
			min[j]=string_to_double(G[1][j]);
			suma[j]=string_to_double(G[1][j]);
			odchylenie[j]=0;
		}
	}
	//*************
	//**************obliczanie
 	cout<<"Trwa obliczanie prosze czekac ";
	int x=1;
 	for(int j=1;j<wym1+1;j++)
	{	
 		for(int i=1;i<wym2+1;i++)
		{	//******mechanizm oczekiwania
 			if(i%50==0)
			{
 			cout<<". ";
			}
 			if(i%300==0)
			{
 			cout<<"\r                                                  \rTrwa obliczanie prosze czekac ";	
			}
			//******
			//********okreœlenie minimalnej i maxymalnej wartoœæi
	 		if((atr_type[j][2])=="n")
			{
	 			double temp=string_to_double(G[i][j]);
	 			suma[j]+=temp;
	 			if(temp>max[j])
	 			{
	 				max[j]=temp;
				}
				if(temp<min[j])
				{
					min[j]=temp;
				}
			}
			//********
			//****** wyszukanie roznych argómêtów oraz klas decyzyjnych i ich zliczanie 
 			bool  flag=false;
    		for(int k=x;k<=size_a;k++)
			{
	    		if((string_to_double(G[i][j])==AR[1][k])&&((double)(j)==AR[0][k]))
				{
					AR[2][k]++;// jeœli wykruta zostanie ta sama wartoœæ licznik wartoœci zwieksza sie o jeden
					flag=true;			
				}	
			}	
			if(!flag) // jeœli w za³ej tablicy AR nie ma danej wartoœci która nale¿y do danego argumentu zostanie ona zapisana to tablicy
			{	if(q<50){
					size_a++;
				 	AR[0][size_a-1] = j;
    				AR[1][size_a-1] = string_to_double(G[i][j]);
    				AR[2][size_a-1] =1;
    				q++;
    				
				}
				else{
					AR=dodaj2s(AR,size_a,j,G[i][j]);//zwiekszenie tablicy dwuwymiarowej i przypisanie nowych wartoœci 
					q=0;
				}
					
			}
			//******
 		}
 		liczA[j]=size_a-x; //obliczanie iloœci ró¿nych wartoœci w argumêcie
 		x=size_a;	//zmienna pozwalaj¹ca pominiêcie wartoœci innych argumêtów podczas sprawdzania
	}
	cout<<"\r                                                  ";
	//************* 
	//wyœwietlanie	 
	cout<<"\n\nNacisnij ENTER aby wyswietlic informacje o klasach decyzyjnych \n  ";
	getchar();
	cout<<endl<<endl<<"Klasy decyzyjne systemu:"<<endl;
	// wyœwietlenie klas decyzyjnych oraz ich liczebnoœæ
	for(int j=0;j<x;j++)
	{
		if(AR[0][j]==(double)(15))
		{
			
			klasy[class_size]=AR[1][j];
			liczklas[class_size]=AR[2][j];
			
			
			class_size++;
		}
	}
	for(int i=0;i<class_size;i++)
	{
		cout<<"\t"<<klasy[i]<< "\t "<<liczklas[i]<<endl;
	}
	

	double sumaK[class_size][wym1+1];
	double odchylenieK[class_size][wym1+1];
//obliczanie odchylenia standarowego dla poszczególnych klas	
	for(int i=0;i<class_size;i++)
	{
		
		for(int k=1;k<wym1;k++){
			
			sumaK[i][k]=0;
			
			for(int j=1;j<wym2+1;j++)
			{
				
				double temp=string_to_double(G[j][wym1]);
				
				if(temp==klasy[i]){
				
				sumaK[i][k]+=string_to_double(G[j][k]);
				
				}
				
	
			}
			sumaK[i][k]=sumaK[i][k]/liczklas[i];
			
		}

		for(int k=1;k<wym1;k++){
			odchylenieK[i][k]=0;
			for(int j=1;j<wym2+1;j++)
			{
				double temp=string_to_double(G[j][wym1]);
				if(temp==klasy[i]){
				
				odchylenieK[i][k]+=((string_to_double(G[j][k])-sumaK[i][k])*(string_to_double(G[j][k])-sumaK[i][k]));
				
				}
	
			}
			odchylenieK[i][k]=sqrt(odchylenieK[i][k]/liczklas[i]);
		}

		
	}
	//*******
	//wyœwietlenie minimalnej i maxymalnej wartoœci poszczególnych argumentów (w miejsce argumentów symbolicznych wypisana jest litera s)
	cout<<"\n\nNacisnij ENTER aby wyswietlic minimalnej i maxymalnej wartosci poszczegolnych argumentow  \n  ";
	getchar();
	cout<<endl<<endl<<"minimalne i maxymalne wartosci argumentow:"<<endl;
	for(int j=1;j<wym1;j++)
	{	
		cout<<atr_type[j][1];
		if((atr_type[j][2])=="n")
		{
			suma[j]=suma[j]/(wym2);
			cout<<"\t max: \t"<<max[j]<<"\t min: \t"<<min[j]<<endl;
		}
		else
		{
			cout<<"\t s"<<endl;
		}
	}	
	//********
	//wyœwietlenie liczebnoœci i wartoœci argumentów oraz liczebnoœci ich wystêpowania, i czêœæiowe obliczenie odchylenia standardowego	
	cout<<"\n\nNacisnij ENTER aby wyswietlic szczegoly o argumentach \n  ";
	getchar();
	cout<<endl<<endl<<"wartosci argumentow i ich liczebnosc:"<<endl<<endl;
	for(int i=1;i<wym1;i++)
	{	
		cout<<endl<<"a"<<i<<"\t wartosc \t liczebnosc \t ilosc roznych argumentow : "<<liczA[i]<<endl;
		for(int j=1;j<size_a;j++)
		{
			if(AR[0][j]==(double)(i))
			{
				cout<<"\t "<<AR[1][j]<< "\t\t "<<AR[2][j]<<endl;
				if((atr_type[i][2])=="n")
				{
					odchylenie[i]=odchylenie[i]+(pow((AR[1][j]-suma[i]),2)*AR[2][j]);// czêœæiowe obliczenie odchylenia standardowego 
				}	
			}
		}
	}
	//***************
	//************ obliczenie i wyœwietlenie odchylenia standardowego
	cout<<"\n\nNacisnij ENTER aby wyswietlic odchylenie standardowe argumentow \n  ";
	getchar();
	for(int i=1;i<wym1;i++)
	{
		if(atr_type[i][2]=="n")
		{
			cout<<endl<<"odchylenie standardowe a"<<i<<" = "<<sqrt(odchylenie[i]/(wym2))<<endl;
		}
	
	}
	
		for(int i=0;i<class_size;i++)
	{
		for(int k=1;k<wym1;k++){
			
		if(atr_type[k][2]=="n")
		{
			cout<<endl<<"odchylenie standardowe a"<<k<<" dla klasy "<<klasy[i]<<" = "<<odchylenieK[i][k]<<endl;
		}
		
		}
		
		}
	
	//************
	//****************
//KONIEC MIEJSCA NA ROZWIAZANIE  
//******************************************************

cout<<"\n\nPrzykladowa konwersja string do double i operacja na skonwertowanych wartosciach";
getchar();
double temp1,temp2;
double wynik;
//wrzucam do temp1 i temp2 wartosci G[1][1],G[1][2] z mojej tablicy G i dodaje te wartoœci;
//pamietamy, ze wartosci tablicy sa typu string, stad zanim zaczniemy wykonywac operacje
// trzeba je przekonwertowac do odpowiedniego typu,
// w naszym przypadku potrzebujemy wartosci ca³kowitych stad uzywamy string_to_int,
temp1=string_to_double(G[1][1]);
temp2=string_to_double(G[1][2]);
wynik=temp1+temp2;

//wyswietlamy wynik
cout<<"\n"<<temp1<<" + "<<temp2<<" = "<<wynik;

//funkcja zapisuje tablice stringów do pliku, podajemy
string nazwap2="plik_do zapisu.txt";
cout<<"\n\nNacisnij ENTER aby wykonac demonstracyjny zapis pliku o nazwie "<<nazwap2;
getchar();
zapis(wym2,wym1,G,nazwap2.c_str());


//na koniec czyœcimy pamiêæ po naszej tablicy
for(int i=0;i<wym2+1;i++)
{delete[] G[i];}//czyscimy wiersze
delete[] G;//zwalniamy tablice wskaznikow do wierszy

cout<<"\n\nNacisnij ENTER aby zakonczyc";
getchar();

//na koniec nasza funkcja zwraca wartoœæ 0 i program siê koñczy
return 0;
}
double** dodaj2s(double **tab, int &tab_size, int a,   std::string c)
{
    tab_size+=1;//wpowikszenie wielkoœci tablicy
 	int b=3;
 	//zainicjowanie tablicy tymczasowej
    double **temp_tab = new double *[3];
    while(b--) temp_tab[b] = new double[tab_size+50];
    //**********
    //przepisanie wartoœci
 	for (int j = 0; j < 3; j++)
    for (int i = 0; i < tab_size-1; i++)
    {
        temp_tab[j][i] = tab[j][i];
    }
 	//**********
 	//dopisanie nowej wartoœæi
    temp_tab[0][tab_size-1] = a;
    temp_tab[1][tab_size-1] = string_to_double(c);
    temp_tab[2][tab_size-1] =1;
    //wyczyszczenie pamiêci po starej tablicy
    for(int i=0;i<3;i++)
	{
		delete[] tab[i];
	}
	delete[] tab; 
	//**********
    return temp_tab;//zwrucenie nowej tablicy

}


