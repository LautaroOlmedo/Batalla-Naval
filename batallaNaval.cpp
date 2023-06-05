#include <iostream>
#include <string>

using namespace std;


struct jugador {
    string nombre;
    int puntos;
    string tablero[11][11]={{"   ","A","B","C","D","E","F","G","H","I","J"},
                        {"1  ","0","0","0","0","0","0","0","0","0","0"},
                        {"2  ","0","0","0","0","0","0","0","0","0","0"},
                        {"3  ","0","0","0","0","0","0","0","0","0","0"},
                        {"4  ","0","0","0","0","0","0","0","0","0","0"},
                        {"5  ","0","0","0","0","0","0","0","0","0","0"},
                        {"6  ","0","0","0","0","0","0","0","0","0","0"},
                        {"7  ","0","0","0","0","0","0","0","0","0","0"},
                        {"8  ","0","0","0","0","0","0","0","0","0","0"},
                        {"9  ","0","0","0","0","0","0","0","0","0","0"},
                        {"10 ","0","0","0","0","0","0","0","0","0","0"},};;
    string marcador[11][11]={{"   ","A","B","C","D","E","F","G","H","I","J"},
                        {"1  ","0","0","0","0","0","0","0","0","0","0"},
                        {"2  ","0","0","0","0","0","0","0","0","0","0"},
                        {"3  ","0","0","0","0","0","0","0","0","0","0"},
                        {"4  ","0","0","0","0","0","0","0","0","0","0"},
                        {"5  ","0","0","0","0","0","0","0","0","0","0"},
                        {"6  ","0","0","0","0","0","0","0","0","0","0"},
                        {"7  ","0","0","0","0","0","0","0","0","0","0"},
                        {"8  ","0","0","0","0","0","0","0","0","0","0"},
                        {"9  ","0","0","0","0","0","0","0","0","0","0"},
                        {"10 ","0","0","0","0","0","0","0","0","0","0"},};;
};

void recorrerTableros();
void pintarTablero(string tableroJugadorPintar[11][11]);
void cargarBarco(string tableroACargar[11][11]);
int preguntarPosBarco(int& linea , int& columna);
float transformarColumnas(char columna);
bool validacionesDir(int linea, int columna,string tableroDireccion[11][11],int largoBarco,string& dirBarcoUsuario);
void colocarBarcoDir(int linea,int columna, int largoBarco,string dir, string tableroBarco[11][11]);
string direccionBarco(string& dirBarco);
string cambiarNumALetra(int largoBarco);
int atacar(string tablero[11][11], string marcador[11][11], jugador jugadorAtacante);
void dondeAtacar(string marcadorAtaque[11][11]);
float verificacionAtaque(string marcadorAtaque[11][11], int fila, int columna);
float verificarFila(int fila);
float verificarColumna(int columna);
float verificacionFilaYColumna(int fila, int columna);
float verificarQuienGana(int puntosjugador1, int puntosjugador2);
void jugar();


int main(){                      
    jugar();
}

void pintarTablero(string tableroJugadorPintar[11][11]){

	for(int i=0; i<11; i++){
		for(int j=0; j<11; j++){
		    cout<<tableroJugadorPintar[i][j] << " ";
		}
	cout<<"\n";
	}		
}

void cargarBarco(string tableroACargar[11][11]){
	int fila;
	int columna;
	string direccion;
	bool validacion;
	
	for(int barco=2 ; barco<6 ; barco++){ // POSIBLE ERROR: Pregunta donde poner el barco Y SI ESA POSICION INICIAL ES 0 lo pone sin importar que 1 posicion adelante esté otro barco
	    do{
	    	cout<<"INGRESE LA POSICION DEL BARCO DE "<<barco<<" DE LARGO.\n";
	    	preguntarPosBarco(fila, columna);
		    validacion = validacionesDir(fila,columna,tableroACargar,barco, direccion);
		    
		}while(!validacion);
	 
	 colocarBarcoDir(fila, columna, barco, direccion, tableroACargar);
	 cout<<"El barco de "<<barco <<" de largo fue colocado\n";	    
	 pintarTablero(tableroACargar);
	}
	
}

int preguntarPosBarco(int& linea, int& columna){
	
	char letraColumna;
	
	cout<<"Indique del 1 al 10 en que linea quiere colocar el barco:"<<"\n";
    cin>>linea;
    cout<<"Indique del A al J en que columna quiere colocar el barco:"<<"\n";
    cin>>letraColumna;
    
    columna = transformarColumnas(letraColumna);
    
    if(linea==0 || columna==0 || linea>10 || columna>10){
    	cout<<"Posicion incorrecta, intente de nuevo..." <<"\n";
	}
	return 0;
}

bool validacionesDir(int fila, int columna,string tableroDireccion[11][11],int largoBarco,string& dirBarcoUsuario){
	
	
	dirBarcoUsuario = direccionBarco(dirBarcoUsuario);
	
	if(dirBarcoUsuario=="arriba"){
	    for (int i = fila; i > fila - largoBarco; i--) { // ---> 10 ; 8; 10 - 1 = 9 | 9 - 1 = 8 | ...
			if(tableroDireccion[i][columna] != "0") {
				if((fila - largoBarco) <= 0){
					cout << "Fuera de rango..." << "\n"; 
				    return false;
				}
   	            cout << "Se encuentra otro barco en esta casilla..." << "\n"; 
				return false;
            }     
        }
		return true;
	}else if(dirBarcoUsuario== "abajo"){
		for (int i = fila; i < largoBarco + fila; i++) {
			if(tableroDireccion[i][columna] != "0"){
				if((largoBarco + fila) > 11){
					cout << "Fuera de rango..." << "\n";
					return false;
				}
    	        cout << "Se encuentra otro barco en esta casilla..." << "\n";
				return false;
            }
        }
		return true;
	}else if(dirBarcoUsuario== "derecha"){
		for (int j = columna; j < largoBarco + columna; j++) { // ---> 5 ; 5 <= 8; 5++
			if(tableroDireccion[fila][j] != "0"){
				if((largoBarco + columna) > 11){
					cout << "Fuera de rango..." << "\n";
				    return false; 
				}
    	        cout << "Se encuentra otro barco en esta casilla..." << "\n";
				return false; 
	        }
        }
		return true;
	}else if(dirBarcoUsuario=="izquierda"){
		for (int j = columna; j > columna - largoBarco; j--) {
			if(tableroDireccion[fila][j] != "0"){
				if((columna - largoBarco) <= 0){
					cout << "Fuera de rango..." << "\n";
			        return false;
				}
   	            cout << "Se encuentra otro barco en esta casilla..." << "\n";
			    return false;
            }
        }
		return true;
	}else{
		cout<<"Error de tipeo vuelva a escribirlo...\n";
		return false;
	}
  return false;
}

void colocarBarcoDir(int linea,int columna,int largoBarco,string dir, string tableroBarco[11][11]){
	string tamano = cambiarNumALetra(largoBarco);
	
	if(dir=="arriba"){
		for (int i = linea; i > linea - largoBarco; i--) {
            tableroBarco[i][columna] = tamano;
        }
	}else if(dir=="abajo"){
		for (int i = linea; i < largoBarco + linea; i++) {
            tableroBarco[i][columna] = tamano;
        }
	}else if(dir=="derecha"){
		for (int j = columna; j < largoBarco + columna; j++) {
            tableroBarco[linea][j] = tamano;
        }
	}else if(dir=="izquierda"){
		for (int j = columna; j > columna - largoBarco; j--) {
            tableroBarco[linea][j] = tamano;
        }
	}else{
		cout<<"Error de tipeo vuelva a intentarlo...\n";
	}
}

string cambiarNumALetra(int largoBarco){
	string tamano;
	switch (largoBarco)
{
case 2:
	tamano = "2";
	break;
case 3:
	tamano = "3";
	break;
case 4:
	tamano = "4";
	break;
case 5:
	tamano = "5";
	break;
}
return tamano;
}

string direccionBarco(string& dirBarco){
    
	cout<<"Para que direccion quiere que vaya el barco(derecha, izquierda, arriba o abajo): "<<"\n";
    cin>> dirBarco;
 	
    return dirBarco;
 	
}

float transformarColumnas(char columna){
	int num;
	switch (toupper(columna)){
		case 'A': num = 1;
			break;
		case 'B': num = 2;
			break;
		case 'C': num = 3;
			break;
		case 'D': num = 4;
			break;
		case 'E': num = 5;
			break;
		case 'F': num = 6;
			break;
		case 'G': num = 7;
			break;
		case 'H': num = 8;
			break;
		case 'I': num = 9;
			break;
		case 'J': num = 10;
			break;	
	}
	if(num < 1 || num > 10){
		return false;
	}
	return num;
}

// ---------- ATACAR ----------

int atacar(string tableroAtacado[11][11], string marcadorAtaque[11][11], jugador jugadorAtacante){ // ---> RECIBE LOS ARREGLOS CON LOS BARCOS CARGADOS 
    bool fallo = true;
    int fila, columna;
    bool verificacion;    //, verificacionFila, verificacionColumna;
	char letraColumna;


	cout << "--------------------------------------------------" << "\n";
	cout << "Turno del jugador " << jugadorAtacante.nombre <<"\n";
	cout << "--------------------------------------------------" << "\n";
	
	do{
	cout << "Ingrese la fila donde queres atacar" <<"\n";    //Si en la fila pones una letra salta un bucle.
	cin >> fila;

	cout << "\n";

	cout << "Ingrese la columna donde queres atacar" <<"\n";
	cin>>letraColumna;
    
    columna = transformarColumnas(letraColumna);
	
	}while(!verificacionFilaYColumna(fila, columna) || !verificacionAtaque(marcadorAtaque, fila, columna));
	
	marcadorAtaque[fila][columna] = "*";

	if(tableroAtacado[fila][columna] != "0"){
		cout << "LE DISTE A UN BARCO \n";
		tableroAtacado[fila][columna] = "X";
		marcadorAtaque[fila][columna] = "R";
		pintarTablero(marcadorAtaque);
		return 1;

	}else{
		pintarTablero(marcadorAtaque);
		fallo = false;
				
	}
	if(!fallo){
		cout << "NO LE PEGASTE AL BARCO \n";
		return 0;
	}

	return 0;
}


float verificacionAtaque(string marcadorAtaque[11][11], int fila, int columna){
	for(int i = 0; i < 11; i++){
		for(int t = 0; t < 11; t++){
			if(marcadorAtaque[fila][columna] != "0"){
				cout << "Ya has atacado en ese lugar. \n";
				return false;
			}
		}
	}
	return true;
}

float verificacionFilaYColumna(int fila, int columna){
	if(verificarFila(fila) && verificarColumna(columna)){
		return true;
	}
	return false;
}

float verificarFila(int fila){
	if(fila < 1 || fila > 10){
		return false;
	}else{
		return true;
	}
};

float verificarColumna(int columna){
	if(columna < 1 || columna > 11){
		return false;
	}else{
		return true;
	}
};

float verificarQuienGana(int puntosjugador1, int puntosjugador2){
	if(puntosjugador1 == 14){
		return false;
	}else if (puntosjugador2 == 14){
		return false;
	}else {
		return true;
	}
}

void jugar(){
	int contadorJugador1, contadorJugador2, opcionMenuJugar;
	jugador jugador1, jugador2;

	cout << "Bienvenida/os a la Batalla Naval!!" << "\n";

	//do{
	
	do{
		cout << "ELegir una opcion" << "\n";
		cout << "1. Jugar" << "\n";
		cout << "2. Salir" << "\n";
		cin >> opcionMenuJugar;
		if (opcionMenuJugar != 1 && opcionMenuJugar !=2){
			cout << "Opcion incorrecta. Por favor, elija una opcion valida. \n";
		}
	} while (opcionMenuJugar != 1 && opcionMenuJugar !=2);


	if(opcionMenuJugar == 2){
		cout << "Elegiste SALIR ";
		return;
	}else{

		cout << "Elegiste JUGAR" << "\n";

		cout << "Ingresa el nombre del primero jugador" << "\n";
		cin >> jugador1.nombre;
		cout << "Ingresa el nombre del segundo jugador" << "\n";
		cin >> jugador2.nombre;

		jugador1.puntos = 0;
        jugador2.puntos = 0;

		cout <<"\n";
		cout << "Tablero de " << jugador1.nombre<<"\n";
		cout <<"\n";
		pintarTablero(jugador1.tablero);

		cout <<"\n";

		cout << "Turno de " << jugador1.nombre <<"\n";
		cout <<"\n";
	    cargarBarco(jugador1.tablero);

		cout <<"\n";
		cout <<"\n";

		cout << "Tablero de " << jugador2.nombre<<"\n";
		cout <<"\n";
	    pintarTablero(jugador2.tablero);

		cout <<"\n";

		cout << "Turno de " << jugador1.nombre <<"\n";
		cout <<"\n";
	    cargarBarco(jugador2.tablero);
	do{
		        
	    jugador1.puntos = jugador1.puntos + atacar(jugador2.tablero, jugador1.marcador, jugador1);
		cout <<"\n";
		cout <<"\n";
		jugador2.puntos = jugador2.puntos + atacar(jugador1.tablero, jugador2.marcador, jugador2);
		cout << "El jugador " << jugador1.nombre << ". Lleva " << jugador1.puntos << " puntos de 14 \n";
		cout << "El jugador " << jugador2.nombre << ". Lleva " << jugador2.puntos << " puntos de 14 \n" ;
	    }while(verificarQuienGana(jugador1.puntos, jugador2.puntos));   
	}

	if(jugador1.puntos == 14){
			cout << "EL jugador " << jugador1.nombre << " ES EL GANADOR!!" << "\n";
		}else{
			cout << "EL jugador " << jugador2.nombre << " ES EL GANADOR!!" << "\n";
	}
	cout << "ADIOS";
}


/*void dondeAtacar(string marcadorAtaque[11][11]){
	int fila, columna;
	bool verificacion; //, verificacionFila, verificacionColumna;
	char letraColumna;
	
	do{
	cout << "Ingrese la fila donde queres atacar" <<"\n";
	cin >> fila;
	//verificacionFila = verificarFila(fila);
	
	cout << "Ingrese la columna donde queres atacar" <<"\n";
	cin>>letraColumna;
    
    columna = transformarColumnas(letraColumna);
	//verificacionColumna = verificarColumna(columna);
	
	  //verificacionAtaque(marcadorAtaque, fila, columna);
	}while(!verificacionFilaYColumna(fila, columna) && !verificacionAtaque(marcadorAtaque, fila, columna));
	// verificacion = verificacionAtaque(marcadorAtaque, fila, columna);
	
	// for(int i = 0; i < 11; i++){
	// 	for(int t = 0; t < 11; t++){
	// 		// if(marcadorAtaque[fila][columna] != "0"){
	// 		// 	marcadorAtaque[i][t] = "*";
	// 		// }
	// 		marcadorAtaque[fila][columna] = "*";
	// 	}
	// }
	
	marcadorAtaque[fila][columna] = "*";
}*/