#include <iostream>
#include <ctime>
#include <cstring>
#include "red_pokazivac.h"
//#include "red_polje.h"
using namespace std;

void ispis(paci slog){// funkcija za ispis jednog pacijenta
	cout<<"a- "<<slog.a<<" b- "<<slog.b<<" ";
	if(slog.c==1) cout<<slog.c<<"- hitni sl. ";
	else if(slog.c==2) cout<<slog.c<<"- invalid ";
	else if(slog.c==3) cout<<slog.c<<"- trudnica ";
	else if(slog.c==4) cout<<slog.c<<"- dijete<6 ";
	else if (slog.c==5) cout<<slog.c<<"- ostali ";
	
	if(slog.d==1) cout<<slog.d<<"- pregled ";
	else if(slog.d==2) cout<<slog.d<<"- previjanje ";
	else if(slog.d==3) cout<<slog.d<<"- recept ";
	else if(slog.d==4) cout<<slog.d<<"- uputnica ";
	
	if(slog.e==1) cout<<slog.e<<"- obiteljska medicina ";
	else if(slog.e==2) cout<<slog.e<<"- oftalmologija ";
	else if(slog.e==3) cout<<slog.e<<"- dermatovenerologija ";
	else if(slog.e==4) cout<<slog.e<<"- ginekologija ";
	else if(slog.e==5) cout<<slog.e<<"- urologija ";
	cout<<endl;
	
	cout<<slog.prez_ime<<endl;
	cout<<slog.spol<<endl;
	cout<<slog.dan<<"."<<slog.mjesec<<"."<<slog.godina<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}
bool stariji_od_25 (int dan, int mj, int god,int d=7, int m=12, int g=2013){//usporedba starosti s obzirom na datum: 7.12.2013
	if(g-25==god&&m>=mj){
		if(m==mj&&d>=dan) return true;			// stariji od 25god  7.12.1988
	}
	if(g-25>god) return true;
	return false;
}
bool stariji_od_50 (int dan, int mj, int god,int d=7, int m=12, int g=2013){//usporedba starosti s obzirom na datum: 7.12.2013
	if(g-50==god&&m>=mj){
		if(m==mj&&d>=dan) return true;			// stariji od 50god  7.12.1963
	}
	if(g-50>god) return true;
	return false;
}
bool pps=false;
void genera(queue *q, paci polje[], int n, int g=0){
	srand(time(0));
	rand();
	int a;
	switch(g){
		case 0:// generiranje ure�ene N-torke
			for(int i=0; i<n; i++){
				polje[i].a=50+rand()%250; // ai 50-300
				polje[i].b=50+rand()%250; // bi 50-300
				rand();
				polje[i].c=1+rand()%5; // ci 1-5 prioriteti
				if(polje[i].c==1) polje[i].d=1+rand()%2; // di - hitni - pregled, previjanje
				else if(polje[i].c==3){
					do{
						polje[i].d=1+rand()%4;
					}while(polje[i].d==2); // trudnice bez previjanja
				}
				else polje[i].d=1+rand()%4;
				
				if(polje[i].c==1) polje[i].e=2+rand()%4;//hitni bez obitelj med
				else if (polje[i].c==3){//trudnice
					if (polje[i].d==1){ //na pregledu bez urologa
						polje[i].e=1+rand()%4;
					}	
					else if (polje[i].d==3 || polje[i].d==4){ //ako je dosla po recept ili uputnicu ide kod obit med
						polje[i].e=1; 
					}	
				}
				else if (polje[i].d==3 || polje[i].d==4) polje[i].e=1;
				else polje[i].e=1+rand()%5;
			} 
			break;
		case 1: // generiranje imena, prezimena, datuma rodjenja i spola pacijenta
			pps=true;
			for(int i=0; i<n; i++){ // kad se izgenerira sve od jednog sloga dodat ga u red
				polje[i].prez_ime[0]=char(rand()%26+65);
			    	for (int j=1;j<=6;j++)
			      	polje[i].prez_ime[j]=char(rand()%26+97);
			    	polje[i].prez_ime[7]=' ';
			    	polje[i].prez_ime[8]=char(rand()%26+65);
			    	for (int j=9;j<=16;j++)
			     	polje[i].prez_ime[j]=char(rand()%26+97);
			    	polje[i].prez_ime[17]='\0';
			    	if(polje[i].c==3) polje[i].spol='z'; //trudnice
			    	else{
					a=rand()%2;
					if(a==0) polje[i].spol='m';
					else polje[i].spol='z';
				}
				if(polje[i].c==4){ // djeca mladja od 6
					polje[i].mjesec=rand()%12+1;
					polje[i].dan=rand()%31+1;
					polje[i].godina=rand()%7+2007;
				}
				else if (polje[i].c==3){ //trudnice izmedju 12-60
					polje[i].mjesec=rand()%12+1;
					polje[i].dan=rand()%31+1;
					polje[i].godina=rand()%49+1953;
				}
				else {// ostali stariji od 6 do 100
					polje[i].mjesec=rand()%12+1;
					polje[i].dan=rand()%31+1;
					polje[i].godina=rand()%95+1913;
				}
				EnqueueQ(polje[i],q); //dodavanje sloga(pacijenta) na kraj reda q
				if((int)polje[i].spol==122 && polje[i].d==1 && polje[i].e==2 && stariji_od_25(polje[i].dan, polje[i].mjesec, polje[i].godina)){ 
					ispis(polje[i]); // ispis pacijentica starijih od 25 na pregledu kod oftamologa
				}
			}//for
	}//switch
}//genera

void trojka(queue *q, paci polje[], int n){
	queue *t=new queue; // t - pomocni red
	InitQ(t);
	for(int i=0; i<n; i++){ // prepisivanje svih elemenata iz glavnog u pomocni red
		polje[i]=FrontQ(q);
		EnqueueQ(polje[i],t);
		DequeueQ(q);  // svi elementi iz gavnog reda se izbrisu
	}
	for(int i=0; i<n; i++){ //prebacivanje elemenata iz pomocnog u glavni red
		polje[i]=FrontQ(t);
		//ako je pacijent invalid tariji od 50god i ceka na previjanje kod obit med. onda se brise
		if(polje[i].c==2 && polje[i].d==2 && polje[i].e==1 && stariji_od_50(polje[i].dan, polje[i].mjesec, polje[i].godina)) DequeueQ(t); 
		else{ // inace se upisuje u glavni red
			EnqueueQ(polje[i],q);
			DequeueQ(t);
			ispis(polje[i]);
		}//else
	}//for
}
void brzi2(queue* q, paci polje[], int n=-1){//druga rekurzija glavnog reda
	if(IsEmptyQ(q)) return;	//potrebna da pacijenti u glavnom redu ostanu u istom redoslijedu nakon odvajanja pacijenata u brzi red
	n++;
	polje[n]=FrontQ(q);
	DequeueQ(q);
	brzi2(q,polje,n);
	EnqueueQ(polje[n],q);
	ispis(polje[n]);
	return;
}

void brzi(queue *q, queue* r, paci polje[], int n=-1){//brzi red
	if(IsEmptyQ(q)) return; 	//spremanje elemenata na prog stog sve dok red q ne bude prazan
	n++;					//potrebno za dohvacanje elemenata po redu 
	polje[n]=FrontQ(q);  	//citanje elementa s cela reda
	DequeueQ(q); 			//brisanje elementa iz reda
	brzi(q, r, polje, n);	//rekurzija - element iz reda q i ostali parametri se spremaju na prog stog
	if(polje[n].d==3||polje[n].d==4){ 	//ako pacijent treba recept(d-3) ili uputnicu(d-4) onda se zapisuje u red r(brzi red)
		EnqueueQ(polje[n],r);
		ispis(polje[n]);
	}
	else { 	//ostali se zapisuju u glavni red
		EnqueueQ(polje[n],q);
	}
	return;
}
int main(){
	queue *q=new queue;// pok- stvoreni front i rear,  polje- stvoren pacijent
	InitQ(q);
	int izbor;
	int n=0;
	cout<<"Broj pacijenata za generiranje: ";
	cin>>n;
	paci* polje=new paci[n]; //dinamicko polje pacijenata
	genera(q,polje, n); 
	do{
		cout<<"----------------------------------------------------------------------------"<<endl;
		cout<<"1. Dodavanje imena N-torkama"<<endl;
		cout<<"2. Brisanje invalida starijih od 50 na previjanju kod obiteljske doktorke..."<<endl;
		cout<<"3. Brzi red"<<endl;
		cout<<"9. Izlaz iz programa"<<endl;
		cin>>izbor;
		cout<<"----------------------------------------------------------------------------"<<endl;
		switch(izbor){
			case 1:
				genera(q,polje,n,1);
				break;
			case 2:
				if(pps==false){
					cout<<"Prvo dodajte imena N-torkama preko mogucnosti 1."<<endl;
					break;
				}
				trojka(q,polje,n);
				break;
			case 3:{
				if(pps==false){
					cout<<"Prvo dodajte imena N-torkama preko mogucnosti 1."<<endl;
					break;
				}
				queue *r=new queue;
				InitQ(r);
				cout<<"<<--Brzi red-->>"<<endl;
				brzi(q,r,polje);
				cout<<"<<--Glavni red-->>"<<endl;
				brzi2(q,polje);
				break;
			}
			case 9: 
				cout<<"Izlaz iz programa!!!"<<endl;
				break;
			default: cout<<"Ponovi izbor"<<endl;
		}
	}while(izbor!=9);
    return 0;
}
