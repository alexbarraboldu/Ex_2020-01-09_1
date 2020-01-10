#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct JugadorRanking
{
	std::string nombre;
	int puntos;
	JugadorRanking() {};
	JugadorRanking(std::string _nombre, int _puntos)
	{
		nombre = _nombre;
		puntos = _puntos;
	}
};

template <class T>
void askThings(T& _n)
{
	std::cin >> _n;
}

std::vector<JugadorRanking> vtr1;

bool newInsertedPlayer = false;

void openReadDownloadFile(std::string _file, JugadorRanking _playerNew)
{
	//	ABRIR FICHERO
	std::ifstream myFile(_file);
	//	COMPROBAR SI EL FICHERO ESTÁ ABIERTO
	if (myFile.is_open())
	{
		std::string line;
		//	RECORRER EL FICHERO
		while (std::getline(myFile, line))
		{
			//	CREAR DELIMITADOR
			size_t pos = line.find(' ');
			//	SEPARAR NOMBRE Y PUNTUACIÓN
			std::string name = line.substr(0, pos);
			int points = std::stoi(line.substr(pos++));
			//	INTRODUCIR CADA EL NOMBRE Y PUNTUACIÓN EN EL STRUCT
			JugadorRanking playerAux(name, points);

			if (!newInsertedPlayer && playerAux.puntos < _playerNew.puntos)
			{
				vtr1.push_back(_playerNew);
				newInsertedPlayer = true;
			}
			//	INTRODUCIR EL STRUCT EN EL ARRAY
			vtr1.push_back(playerAux);
		}
		if (!newInsertedPlayer) vtr1.push_back(_playerNew);

		myFile.close();
	}
}

void openWriteUploadFile(std::string _file) {
	//	ABRIR FICHERO
	std::ofstream myFile(_file);

	for (size_t i = 0; i < vtr1.size(); i++)
	{
		myFile << vtr1.at(i).nombre << ' ' << std::to_string(vtr1.at(i).puntos) << std::endl;
	}
	std::cout << "\nEscritura realizada correctamente!\n";
	myFile.close();
}

void printArray(std::vector<JugadorRanking> _vector)
{
	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (_vector[i].nombre == "") continue;
		std::cout << _vector[i].nombre << " - " << _vector[i].puntos << std::endl;
	}
}


int main()
{
	std::cout << "Introduce un archivo (con extension):\n";
	std::string fileName;
	askThings(fileName);

	std::cout << "Introduce un nombre de jugador:\n";
	std::string playerName;
	askThings(playerName);

	std::cout << "Introduce tu puntuacion:\n";
	int playerPoints;
	askThings(playerPoints);

	JugadorRanking playerNew(playerName, playerPoints);

	openReadDownloadFile(fileName, playerNew);
	printArray(vtr1);
	openWriteUploadFile(fileName);



	std::cin.get();
	system("pause");
	return 0;
}