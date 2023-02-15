using namespace std;

struct paci{
	int a, b, c, d, e;
	char prez_ime[35];
	char spol;
	int dan, mjesec, godina;
};
struct qu {
	paci pacijent;
	qu *next;
};
struct que {
	struct qu *front, *rear;
};

typedef struct que queue;
typedef struct qu *element;

paci FrontQ(queue *Q) {// dohvacanje vrijednosti elementa s cela reda (proslijedjen varijabla koja u sebi sadrzi front i rear pokazivace)
	if (Q->front==Q->rear) {
        cout<<"Red je prazan!"<<endl;
     }
     else
         return Q->front->next->pacijent;
}

void EnqueueQ( paci x, queue *Q) {//dodavanje na kraj reda
	element novi=new qu;	//- stvari se novi element
    	novi->pacijent=x;		//- dodijeli mu se vrijednost koja je proslijedjena funkciji (x)
    	novi->next=NULL;		//- posto je novi, zadnji element, next mora biti NULL
    	Q->rear->next=novi;		//- ostatak reda se poveze sa novim elementom
     Q->rear=novi;			//- pokazivac repa reda(rear) pokazuje na novo stvoreni element koji je zadnji u redu
}

void DequeueQ(queue *Q) {// brisanje s cela reda
	element e;
	if (Q->front==Q->rear) {
        cout<<"Red je prazan."<<endl;
     }
	else {
	     e=Q->front;			//- pomocni pokazivac e stavi se na celu reda
          Q->front=Q->front->next; //- pokazivac front se prebaci na element ispod cela
          delete e;				//- izbrise se pomocni pokazivac koji je pokazivao na element s cela reda
     }						//- elementu s cela reda se vise ne moze pristupiti i on je "izgubljen" u memoriji (izbrisan iz reda)
}

void InitQ(queue *Q) {		//- proslijedi se varijabla tipa queue (que) koja sadrzi samo front i rear
	element glava=new qu;	//- stvari se glava
    	Q->front=glava;		//- front se postavlja na glavu
    	Q->rear=glava;			//- rear se postavlja na glavu
    	glava->next=NULL;		//- next pokazivac na NULL jer je red prazan
}		

bool IsEmptyQ(queue *Q){
     if (Q->front==Q->rear)
         return true;
     else
	   return false;
}
