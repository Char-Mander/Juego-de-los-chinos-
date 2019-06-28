#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <fstream>
using namespace std;

const int NADIE=0, MAQUINA=1, HUMANO=2;

int menu();
int pedirMarcador();
int pedirMonedas();
bool mostrarReglas();
void juego(int, int);
int monedasHumano(int);
int apuestaHumano(int, int, int);
int quienGana(int, int, int, int);

int main()
{ 
int opcion, MARCADOR=0, NUMMONEDAS=0;

srand(time(NULL));
ifstream outdatos1;
string configP1;
outdatos1.open("configP1.txt");
int dmarc, dmone;
if (outdatos1.is_open()) {
outdatos1 >> dmarc >> dmone;
MARCADOR=dmarc;
NUMMONEDAS=dmone;
}

else if (outdatos1.fail()){
	MARCADOR=2;
	NUMMONEDAS=3;
}

cout << "Bienvenido" << endl;
cout << "------------------------------------------------------" << endl;

while (opcion!=0) {
		
		 opcion = menu();
		 

		     if (opcion==1) {
			     MARCADOR = pedirMarcador();
				 dmarc=MARCADOR;
		        }
		          if (opcion==2) {
			      NUMMONEDAS = pedirMonedas();
				  dmone=NUMMONEDAS;
		          }
				  
				    if (opcion == 3){
				       bool opcion;
				       opcion = mostrarReglas();
				       ifstream archivo;
				       string reglas;
				
				       if (opcion == true){
					   archivo.open("Reglas.txt");
                       cout << endl;					   
					   getline(archivo, reglas);					
					        while (reglas != "XXX"){
						    cout << reglas << endl;
						    getline(archivo, reglas);
				             }
				     archivo.close();
				        }
				       else
					 cout << "El archivo 'reglas.txt' no ha sido encontrado..." << endl;
					 cout << " " << endl;
				 
			        }  
						 if (opcion==4) {
							juego(MARCADOR, NUMMONEDAS);
							ofstream indatos1;
                            indatos1.open("configP1.txt");
                            indatos1 << dmarc << " " << dmone ;
                            indatos1.close();	
							cout << "Gracias por jugar." << endl;
							cout << endl;
							return 0;
						 }
						 
						 while ((opcion <0) || (opcion>4)) {
							 	cout << "Introduce una opcion valida: ";
	                            cin >> opcion;
						 }
				
						             
	}
	
ofstream indatos1;
indatos1.open("configP1.txt");
indatos1 << dmarc << " " << dmone ;
indatos1.close();
	
return 0;
}

int menu() 
{
	int opcion;
	cout << endl;
	cout << "Menu del juego. " << endl;
	cout << endl;
	cout << "Elija la opcion que desee: " << endl;
	cout << "1.- Cambiar el marcador. " << endl;
	cout << "2.- Cambiar el numero de monedas. " << endl;
	cout << "3.- Acerca del juego de los chinos. " << endl;
	cout << "4.- Jugar una partida." << endl;
	cout << "0.- Salir" << endl;
	cout << endl;
	cin >> opcion;
	
	return opcion;

}

int pedirMarcador() 
{
	int MARCADOR;
	
	cout << endl;
	cout << "Usted ha seleccionado el cambio de marcador. " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Por favor, introduzca el nuevo valor del marcador: " ; 
	cin >> MARCADOR;
	while (MARCADOR <=0) {
		cout << "Ha introducido un valor no valido. Introduzcalo de nuevo: " ; 
		cin >> MARCADOR;
	}
	
	
	return MARCADOR; 
}

int pedirMonedas() 
{
	int NUMMONEDAS;
	
	cout << endl;
	cout << "Usted ha seleccionado el cambio del numero de monedas. " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Por favor, introduzca el nuevo numero de monedas: ";
	cin >> NUMMONEDAS;
	
	while (NUMMONEDAS<=0) {
				cout << "Ha introducido un valor no valido. Introduzcalo de nuevo: " ; 
		 cin >> NUMMONEDAS;
		
	 }
	
	
	return NUMMONEDAS;
	
}

bool mostrarReglas(){
ifstream archivo;
archivo.open("reglas.txt");
	
	if (archivo.is_open()){
		return true;}
		
	else {
		return false;}

archivo.close();
} 


void juego (int MARCADOR, int NUMMONEDAS)
{
	int monedasM, monedasH, eleccionM, eleccionH, resultado;
	int ganadasM=0, ganadasH=0, ronda=0;
	
	while (ganadasM<MARCADOR && ganadasH<MARCADOR)
	{
		ronda = (ronda+1);
		cout << endl;
		cout << "Ronda " << ronda << endl;
		cout << endl;
		monedasH = monedasHumano(NUMMONEDAS);
		monedasM = 0 + rand() % ((NUMMONEDAS + 1) - 0);
		eleccionM = monedasM + rand() % (((2*NUMMONEDAS) +1) - monedasM);
		eleccionH = apuestaHumano(eleccionM, monedasH, NUMMONEDAS);
		resultado = quienGana(monedasM, monedasH, eleccionM, eleccionH);
		
		cout << "La maquina saco " << monedasM << " monedas. " << endl;
		cout << "Usted saco " << monedasH << " monedas. " << endl;
	
	
		if (resultado == 1) {
			ganadasM = (ganadasM+1);
			cout << "Esta ronda la ha ganado la maquina." << endl;
			cout << "------------------------------------------------------" << endl;
		}
		else if (resultado == 2) {
			ganadasH = (ganadasH+1);
			cout << "Ha ganado usted esta ronda." << endl;
			cout << "------------------------------------------------------" << endl;
		}
		else 
			cout << "No ha ganado nadie esta ronda." << endl;
		    cout << "------------------------------------------------------" << endl;
		
	}
			
	
		
		if (ganadasM==MARCADOR) {
			cout << "Ha ganado la maquina!" << endl;
			cout << "El humano gano " << ganadasH << " ronda(s)." << endl;
			cout << "------------------------------------------------------" << endl;	
		}
		
		else if (ganadasH==MARCADOR) {
			cout << "Ha ganado el humano!" << endl;
		cout << "La maquina gano " << ganadasM << " ronda(s)." << endl;
		cout << "------------------------------------------------------" << endl;
		}
}

 int monedasHumano(int NUMMONEDAS)
 {
	 int monedasH;
	 cout << "Introduce el numero de monedas que quiere sacar: ";
	 cin >> monedasH;
	 
	 while (monedasH > NUMMONEDAS || monedasH <0) {
		 cout << "Error. Introduce nueva cantidad de monedas: ";
		 cin >> monedasH;
		
	 }
	 return monedasH;
 }

 
 int apuestaHumano(int eleccionM, int monedasH, int NUMMONEDAS)
 {
 int eleccionH;
 
 cout << "Usted ha sacado " << monedasH << " monedas. " << endl;
 cout << "La maquina ha apostado " << eleccionM << " monedas. " << endl;
 cout << "Recuerde que su apuesta debe ser distinta. " << endl;
 cout << endl;
 
 cout << "Introduzca el numero de su apuesta: " ;
 cin >> eleccionH;
 
 while (eleccionH == eleccionM || eleccionH < monedasH || eleccionH < 0 || eleccionH>(monedasH + NUMMONEDAS)) {
	 cout << "Por favor, introduzca una apuesta valida. " ;
	 cin >> eleccionH;
 }

    return eleccionH; 
 }


 int quienGana(int monedasM, int monedasH, int eleccionM, int eleccionH)
 {
	 if (eleccionM == (monedasM + monedasH)) {
		 return MAQUINA;
	 }
	 else if (eleccionH == (monedasM + monedasH)) {
		 return HUMANO;
	 }
	 else 
		 return NADIE;
 }
















