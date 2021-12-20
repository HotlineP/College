#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

void mainMenu()
{
	system("cls");
	cout << "_________________ Menu _________________" << endl;
	cout << endl;
	cout << "1 - Menu de produtos" << endl;
	cout << "2 - Menu de clientes" << endl;
	cout << "3 - Sair" << endl;
}

void createMenu(string labelName, string objectName)
{
	system("cls");
	cout << "_________________" + labelName + "_________________" << endl;
	cout << endl;
	cout << "1 - Cadastrar " + objectName << endl;
	cout << "2 - Excluir " + objectName << endl;
	cout << "3 - Voltar" << endl;
}

int checkF(string subjName, string fileName)
{
	fstream File;

	bool found = false;

	File.open(fileName + ".txt", ios::in);

	if (File.is_open())
	{
		string line;
		while (getline(File, line))
		{
			if (line == subjName)
			{
				found = true;
			}
		};
		File.close();
	}
	else
	{
		cout << "Ocorreu um erro ao abrir o arquivo. Tente novamente.";
		return 2;
	}

	if (found)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool onProductRegister(string productName, float productPrice, int productQuant)
{
	fstream File;

	File.open("products.txt", ios::app);
	if (File.is_open())
	{
		File << productName + "\n" + to_string(productPrice) + "\n" + to_string(productQuant) + "\n";
		File.close();
	}
	else
	{
		cout << "Ocorreu um erro ao abrir o arquivo. Tente novamente.";
		return false;
	}

	return true;
};

bool onClientRegister(string clientName)
{
	fstream File;

	File.open("clients.txt", ios::app);
	if (File.is_open())
	{
		File << clientName + "\n";
		File.close();
	}
	else
	{
		cout << "Ocorreu um erro ao abrir o arquivo. Tente novamente.";
		return false;
	}

	return true;
};

bool onProductDelete(string productName)
{
	ofstream Temp;
	fstream File;

	bool found;

	File.open("products.txt", ios::in);
	Temp.open("temp.txt", ios::out);

	int check = checkF(productName, "products");

	if (check != 1)
	{
		return check;
	}

	if (File.is_open() && Temp.is_open())
	{
		string line;
		int ignore = 0;

		while (getline(File, line))
		{
			if (ignore <= 0)
			{
				if (line == productName)
				{
					found = true;
					ignore = 3;
				}
				else
				{
					Temp << line + "\n";
				}
			}
			if (ignore >= 1)
			{
				ignore -= 1;
			}
		}

		File.close();
		Temp.close();

		remove("products.txt");
		rename("temp.txt", "products.txt");
	}
	else
	{
		cout << "Ocorreu um erro ao abrir o arquivo. Tente novamente.";
		return 0;
	}
	return 1;
}

bool onClientDelete(string clientName)
{
	ofstream Temp;
	fstream File;

	bool found;

	File.open("clients.txt", ios::in);
	Temp.open("temp.txt", ios::out);

	int check = checkF(clientName, "clients");

	if (check != 1)
	{
		return check;
	}

	if (File.is_open() && Temp.is_open())
	{
		string line;

		while (getline(File, line))
		{
			if (line == clientName)
			{
				found = true;
			}
			else
			{
				Temp << line + "\n";
			}
		}

		File.close();
		Temp.close();

		remove("clients.txt");
		rename("temp.txt", "clients.txt");
	}
	else
	{
		cout << "Ocorreu um erro ao abrir o arquivo. Tente novamente.";
		return 0;
	}
	return 1;
}

int relatorio(bool initial, string itype, string objName, string action){
	fstream File;

	File.open("relatorio.txt", ios::app);

	if (File.is_open() == 0){
		return 0;
	}

	if (initial){
			File << "\n_________\n";
		}

		File << itype + " " + objName + " " + action + "\n";
	
	return 1;
}

int main(void)
{
	bool stop = false;
	bool init = false;

	do
	{
		int answer;

		mainMenu();
		cout << endl;
		cout << "Digite a opcao escolhida:" << endl;

		cin >> answer;

		switch (answer)
		{
			case 1:
			{
				createMenu("Produtos", "produto");
				cout << endl;
				cout << "Digite a opcao escolhida:" << endl;

				int product_answer;
				cin >> product_answer;

				switch (product_answer)
				{
					case 1:
					{
						string productName;
						int productQuant;
						float productPrice;

						cout << endl;
						cout << "Digite o nome do produto:" << endl;
						cin >> productName;
						cout << endl;
						cout << "Digite o valor do produto:" << endl;

						cin >> productPrice;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(80, '\n');
							cout << "Valor invalido." << endl;
							system("pause");
							break;
						}

						cout << endl;
						cout << "Digite a quantidade de estoque deste produto:" << endl;

						cin >> productQuant;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(80, '\n');
							cout << "Valor invalido." << endl;
							system("pause");
							break;
						}

						if (productPrice && productQuant && productName.size() > 2)
						{
							if (onProductRegister(productName, productPrice, productQuant))
							{
								cout << "\nProduto registrado com sucesso.\n";
								if (init == false){init = true;}
								relatorio(init, "product", productName, "registered.");
								system("pause");
							}
						}

						break;
					}
					case 2:
					{
						string productname;

						system("cls");

						while (true)
						{
							cout << "Insira o nome do produto a ser excluido:\n";
							cin >> productname;

							if (productname.length() > 1)
							{
								if (onProductDelete(productname) == 1)
								{
									cout << "Deletado com sucesso.\n";
									if (init == false){init = true;}
									relatorio(init, "product", productname, "deleted.");
									system("pause");
									system("cls");
									break;
								}
								else
								{
									cout << "Nao foi possivel deletar o produto. Verifique o nome.\n";
									system("pause");
									system("cls");
								}
							}
							else
							{
								cout << "Insira um nome valido.\n";
								system("pause");
								system("cls");
							}
						}

						break;
					}
					case 3:
					{
						system("cls");
						break;
				}
				}
				break;
			}
			case 2:
			{
				createMenu("Clientes", "cliente");
				cout << endl;
				cout << "Digite a opcao escolhida:" << endl;

				int client_answer;
				cin >> client_answer;

				switch (client_answer)
				{
					case 1:
					{
						string clientName;

						while (true)
						{
							system("cls");
							cout << "Digite o seu usuario:\n";
							cin >> clientName;

							if (clientName.length() > 3)
							{
								if (onClientRegister(clientName))
								{
									cout << "Cliente registrado com sucesso.\n";
									if (init == false){init = true;}
									relatorio(init, "product", clientName, "registered.");
									system("pause");
								}
								else
								{
									cout << "Cliente nao foi encontrado. Tente novamente.\n";
								}
							}
							else
							{
								cout << "Insira um nome valido.\n";
							}
							break;
						}
					}
					case 2:
					{
						string clientName, clientPass;

						while (true) {
							cout << "Digite o seu usuario:\n";
							cin >> clientName;

							if (onClientDelete(clientName) == 1)
							{
								cout << "Cliente deletado com sucesso.\n";
								if (init == false){init = true;}
								relatorio(init, "product", clientName, "deleted.");
								system("pause");
							}
							else
							{
								cout << "Nao foi possivel deletar o cliente. Verifique o nome e tente novamente.\n";
								system("pause");
								system("cls");
							}

							break;
						}
					}
					case 3:
					{
						system("cls");
						break;
				}
				}
				break;
			}
			case 3:
			{
				stop = true;
				break;
			}
			default:
			{
				cout << "Digite uma opcao valida.";
				break;
		}
		}
	}
	while (stop != true);

	return 1;
}