#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Client{
    string name;
    string password;
};

bool registerClient(string name, string password){
    fstream File;

    File.open("clientes.txt", ios::app);

    if (File.is_open())
	{
        File << name + "\n" + password + "\n";
		File.close();
        return true;
	}
	else
	{
		return false;
	}
};

bool getRegisteredClients(){
    fstream File;

	File.open("clientes.txt", ios::in);

	if (File.is_open())
	{
        bool pass = false;
		string line;
		while (getline(File, line))
		{
            if (pass == false){
                pass = true;
                cout << line + "\n";
            }
            else{
                pass = false;
            }
		};

		File.close();
        return true;
	}
	else
	{
		return false;
	}
}

int main(void)
{
    bool endProgram = false;

    int option;

    while(!endProgram){
        system("cls");
        cout << "Seja bem vindo ao portal de registro da GamesBC! Selecione uma das opcoes para continuar.\n";
        cout << "Opcao 1: Cadastrar\nOpcao 2: Listar cadastros\nOpcao 3: Sair\n\n";

        cin >> option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(80, '\n');
            cout <<"Valor invalido." << endl;
            system("pause");
        }
        else{
            switch(option){
                case 1:{
                    bool endTask = false;
                    while (!endTask){
                        system("cls");
                        
                        Client cliente;
                        bool gotName = false, gotPass = false;

                        while (!gotName && !endTask){
                            system("cls");
                            cout << "Insira o nome do cliente: (Insira 3 para cancelar.)\n";
                            cin >> cliente.name;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(80, '\n');
                                cout <<"Valor invalido." << endl;
                                system("pause");
                            }

                            if (cliente.name == "3"){endTask = true; break;}

                            gotName = true;
                        }

                        while (!gotPass && !endTask && gotName){
                            system("cls");
                            cout << "Insira a senha do cliente: (Insira 3 para cancelar.)\n";
                            cin >> cliente.password;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(80, '\n');
                                cout <<"Valor invalido." << endl;
                                system("pause");
                            }

                            if (cliente.password == "3"){endTask = true; break;}

                            gotPass = true;
                        }

                        if (gotPass && gotName){
                            system("cls");
                            if (registerClient(cliente.name, cliente.password) == true)
                            {
                                cout << "Usuario cadastrado com sucesso.\n";
                                system("pause");
                                break;
                            }
                            else{
                                cout << "Ocorreu um erro ao cadastrar o cliente. Tente novamente.\n";
                            }
                        }
                    }
                    break;
                }
                break;
                case 2:{
                    system("cls");
                    cout << "Usuarios cadastrados:\n\n";

                    if (!getRegisteredClients()){
                        cout << "Ocorreu um erro ao buscar os usuarios cadastrados. Por favor tente novamente.\n";
                    }
                    
                    cout << endl;

                    system("pause");
                }
                break;
                case 3:{
                    endProgram = true;
                }
                break;
                default:{
                    cout << "\nInsira um valor valido!\n";
                    system("pause");
                }
                break;
            }
        }
    }

    return 1;
}