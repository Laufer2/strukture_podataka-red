using namespace std;
struct paci{
	int a, b, c, d, e;
	char prez_ime[35];
	char spol;
	int dan, mjesec, godina;
};
typedef int element;
struct qu {
	paci elementi[100];
	element front, rear;
};

typedef struct qu queue;

int AddOne(int n) {
	return((n+1)%100); //poveca za jedan i vrati na 0 ako bude n=99
}

paci FrontQ(queue *Q) {//vrijednost elementa s èela reda
	if (AddOne(Q->rear)==Q->front) {
		cout<<"Red je prazan!"<<endl;
	}
	else
		return Q->elementi[Q->front]; //front pokazuje na element na èelu reda
}

void EnqueueQ(paci x, queue *Q) {//unos na kraj reda
	if (AddOne(AddOne(Q->rear))==Q->front) {
		cout<<"Red je popunjen"<<endl;
	}
	else {
		Q->rear = AddOne(Q->rear); //pokazivac rear se pomice za jedan i stvara mjesto za novi element na kraju reda
		Q->elementi[Q->rear]= x;   //novi element se zapisuje na novootvoreno mjesto na kraju reda
	}
}
bool IsEmptyQ(queue *Q) {
	if (AddOne(Q->rear)==Q->front)
		return true;
	else
		return false;
}

void DequeueQ(queue *Q) { //briše element s èela reda
	if (AddOne(Q->rear)==Q->front) {
		cout<<"Red je prazan."<<endl;
	}
	else
		Q->front = AddOne(Q->front); //front se poveca za jedan i jednostavno se izgubi element s èela reda
}

void InitQ(queue *Q) {//stvaranje novog reda
	Q->rear = 99;	  //postavljanje pokazivaca na pocetak i kraj reda
	Q->front = 0;    //ne stvaramo novi element jer smo ga vec stvorili u main-u
}
