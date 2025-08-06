//GKPS - Projeto Hotel - 18/06/2024
//Giulia Meninel Mattedi (RA: 00346241)
//Pedro Huck Henrique (RA: 00347436)
//Keisy Alves Do Nascimento (RA: 00325632)
//Sthefany Viveiros Cordeiro (RA: 00347631)

#include <iostream>
#include <stdlib.h>
#include <string.h>
#define ANDARES 20
#define APS 14

int checkin();
int checkout();
int reservar();
int cancelar();
void indice();
int infoHospede();
void taxaOcupacao();
void mapaQuartos();
int comparaCpf(char cpf[12], char cpf2[12]);
int validaCpf(char cpf[12]);
void fclear();

typedef struct hospede                       //struct do hospede
{
	char cpf[12];
	char nome[80];
	char endereco[100];
	char telefone[20];
	char email[50];
}tipoHospede;

typedef struct hotel                         //struct do hotel 
{
	char apartamento;
	tipoHospede hospede;                     // informações do hospede que ocupa o apartamento
}tipoHotel;

tipoHospede hospede;
tipoHotel habboHotel[ANDARES][APS];

main()
{
	for(int i=0;i<ANDARES;i++)                 //define o mapa
		for(int j=0;j<APS;j++)
			habboHotel[i][j].apartamento = '.';

	printf(
  "   / /_  ____  / /____  / /  \n"
        "  / __ \\/ __ \\/ __/ _ \\/ /   \n"
        " / / / / /_/ / /_/  __/ /    \n"
        "/_/ /_/\\____/\\__/\\___/_/     \n"
        "                             \n"
        "    __          __    __        \n"
        "   / /_  ____ _/ /_  / /_  ____ \n"
        "  / __ \\/ __ `/ __ \\/ __ \\/ __ \\\n"
        " / / / / /_/ / /_/ / /_/ / /_/ /\n"
        "/_/ /_/\\__,_/_.___/_.___/\\____/ \n\n");
        
	system("pause");
	system("cls");
	mapaQuartos();
	indice();
}

void mapaQuartos()                           //funcao do mapa
{
	printf("\n apto ->        ");
	for(int j=0;j<APS;j++)
		printf("%2d  ", j+1);
	printf("\n\n");
	for(int i=19;i>=0;i--)
	{
		printf("Andar %2d\t", i+1);
		for(int j=0;j<APS;j++)
			printf("%2c  ", habboHotel[i][j].apartamento);
		printf("\n\n");
	}		
}

void indice()                                // função para visualizar o menu
{
	int numero;
	do
	{
		printf("+------------------------------------------------------------------------+\n");
		printf("| (1) - Check-in de hospede:		                         	 |\n");
		printf("| (2) - Check-out de hospede:     		                         |\n");
		printf("| (3) - Reservar um apartamento:			                 |\n");
		printf("| (4) - Cancelar uma reserva:      			                 |\n");
		printf("| (5) - Mapa de ocupacao e reservas do hotel:			         |\n");
		printf("| (6) - Informacoes do hospede:                                          |\n");
		printf("| (7) - Taxas de ocupacao e reservas do hotel:		                 |\n");
		printf("| (8) - Sair do programa:		                                 |\n");
		printf("+------------------------------------------------------------------------+\n");
		scanf("%d", &numero);
		
		switch(numero) 
		{
			case 1:
				checkin();
				break;
			case 2:
				checkout();
				break;
			case 3:
				reservar();
				break;
			case 4:
				cancelar();
				break;
			case 5:
				mapaQuartos();
				break;
			case 6:
				infoHospede();
				break;
			case 7:
				taxaOcupacao();
				break;
			case 8:
				printf("Saindo...");
				exit(0);
				break;
			default:
				printf("Comando invalido\n");
		}
	}while (numero != 8);
}

int infoHospede()                            // função para visualizar informações do hospede
{
    char apto[5];
    int andar, ap;

    printf("Digite o apartamento no formato AndarQuarto (X para retornar ao menu): ");
    scanf("%5s", apto);
    fclear();
    
    andar = apto[0] - '0';
    ap = (apto[1] - '0') * 10 + apto[2] - '0';
    if (apto[3] != '\0' && apto[0] != '0') {
        andar = (apto[0] - '0') * 10 + apto[1] - '0';
        ap = (apto[2] - '0') * 10 + apto[3] - '0';
    }
    
    if(apto[0] == 'X' || apto[0] == 'x') {                    //para retornar ao menu
		system("cls");
		indice();
		return 0;
    }
    
    if (apto[2] == '\0')
    {
    	printf("Apartamento invalido\n\n");
    	return infoHospede();
	}
    
    if ((andar < 1 || andar > 20) || (ap < 1 || ap > 14)) {
        printf("Apartamento invalido!\n\n");
        return infoHospede();
    }
    
    if (habboHotel[andar - 1][ap - 1].apartamento == 'O') 	{
        printf("Nome: %s\n", habboHotel[andar-1][ap-1].hospede.nome);
        printf("CPF: %s\n", habboHotel[andar-1][ap-1].hospede.cpf);
        printf("Telefone: %s\n", habboHotel[andar-1][ap-1].hospede.telefone);
        printf("Email: %s\n", habboHotel[andar-1][ap-1].hospede.email);  
      	printf("Endereco: %s\n", habboHotel[andar-1][ap-1].hospede.endereco);
        system("pause");
		system("cls");
    }
    
	else {
        printf("Apartamento livre\n");
        system("pause");
		system("cls");
    }
    return 0;
}

int reservar()                               //funcao para reservar
{
	char apto[5];
	int andar, ap;
	
	printf("Digite o apartamento no formato AndarQuarto (ex. 302: andar 3, ap 2)\n(X para retornar ao menu): ");
	scanf("%5s", &apto);
	fclear();
	
	if(apto[0] == 'X' || apto[0] == 'x') {                    //para retornar ao menu
		system("cls");
		indice();
		return 0;
    }
	
	andar = apto[0] - '0';
	ap = (apto[1] - '0')*10 + apto[2] - '0';
	 if(apto[3] != '\0' && apto[0] != '0'){
		andar = (apto[0] - '0')*10 + apto[1] - '0';
		ap = (apto[2] - '0')*10 + apto[3] - '0';
	}
	if (apto[2] == '\0')
    {
    	printf("Apartamento invalido!\nDigite um numero AAQQ ou AQQ\n\n");
    	return reservar();
	}
	
	if((andar<1 || andar > 20) || (ap<1 || ap > 14)){
		printf("Andar invalido!\nDigite um numero AAQQ ou AQQ\n\n");
		return reservar();
	}
	
	if((habboHotel[andar - 1 ][ap - 1].apartamento) != '.'){
		printf("Apartamento indisponivel!\n\n");
		return reservar();
	}
	
	printf("Digite o CPF (Apenas numeros)(X para retornar ao menu): ");
		do{
			scanf("%11s", habboHotel[andar-1][ap-1].hospede.cpf);
			fclear();
				if(habboHotel[andar-1][ap-1].hospede.cpf[0] == 'X' || habboHotel[andar-1][ap-1].hospede.cpf[0] == 'x') { //para retornar ao menu
					system("cls");
					indice();
					return 0;
   				}
		}while(!validaCpf(habboHotel[andar-1][ap-1].hospede.cpf));
		habboHotel[andar-1][ap-1].apartamento = 'R';
		mapaQuartos();
		printf("Apartamento reservado com sucesso!\n\n");
		system("pause");
		system("cls");
}

int checkin()                                //funcao para fazer check-in	
{
	char apto[20];
	int andar, ap;
	char cpf2[12];
	
	printf("Digite o apartamento no formato AndarQuarto (ex. 302: andar 3, ap 2)\n(X para retornar ao menu): ");
	scanf("%5s", apto);
	fclear();
	
	if(apto[0] == 'X' || apto[0] == 'x')                     //para retornar ao menu
	{
		system("cls");
		indice();
		return 0;
    }
	
	andar = apto[0] - '0';
	ap = (apto[1] - '0')*10 + apto[2] - '0';
	if(apto[3] != '\0' && apto[0] != '0')
	{
		andar = (apto[0] - '0')*10 + apto[1] - '0';
		ap = (apto[2] - '0')*10 + apto[3] - '0';
	}
	if (apto[2] == '\0')
    {
    	printf("Apartamento invalido!\nDigite um numero AAQQ ou AQQ\n\n");
    	return checkin();
	}
	
	if((andar<1 || andar > 20) || (ap<1 || ap > 14))
	{
		printf("Andar invalido!\nDigite um numero AAQQ ou AQQ\n\n");
		return checkin();
	}
	
	if(habboHotel[andar-1][ap-1].apartamento == 'O') 
	{
        printf("Apartamento indisponivel!\n\n");
        return checkin();
	}
	
	else
	{
		if (habboHotel[andar-1][ap-1].apartamento == 'R')       //se o quarto tiver reserva
		{
			do
			{
	   			fflush(stdin);
	   			printf("CPF (Apenas numeros)(X para retornar ao menu)\n");
				printf("*Se houver reserva o CPF devera ser o mesmo!: ");
				fgets(cpf2, sizeof(cpf2), stdin);
				habboHotel[andar-1][ap-1].hospede.cpf[strcspn(habboHotel[andar-1][ap-1].hospede.cpf, "\n")] = '\0';
			
				if(!comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2))
				{
					printf("CPF Incorreto\n\n");                  //cpf nao compativel com o armazenado
				}
			}while (!comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2));
		}
		
		fflush(stdin);
		printf("Nome (X para retornar ao menu): ");
		fgets(habboHotel[andar-1][ap-1].hospede.nome, sizeof(habboHotel[andar-1][ap-1].hospede.nome), stdin);   //atribui o nome para o hospede no quarto
		habboHotel[andar-1][ap-1].hospede.nome[strcspn(habboHotel[andar-1][ap-1].hospede.nome, "\n")] = '\0';
		
		if(habboHotel[andar-1][ap-1].hospede.nome[0] == 'X' || habboHotel[andar-1][ap-1].hospede.nome[0] == 'x')  //para retornar ao menu
		{
			system("cls");
			indice();
			return 0;
    	}
    
    	fflush(stdin);
		printf("CPF (Apenas numeros)(X para retornar ao menu): "); 
		do
		{
			fgets(habboHotel[andar-1][ap-1].hospede.cpf, sizeof(habboHotel[andar-1][ap-1].hospede.cpf), stdin);  //atribui o cpf para o hospede no quarto
			habboHotel[andar-1][ap-1].hospede.cpf[strcspn(habboHotel[andar-1][ap-1].hospede.cpf, "\n")] = '\0';
			if(habboHotel[andar-1][ap-1].hospede.cpf[0] == 'X' || habboHotel[andar-1][ap-1].hospede.cpf[0] == 'x')   //para retornar ao menu
			{
				system("cls");
				indice();
				return 0;
    		}
			
		}while(!validaCpf(habboHotel[andar-1][ap-1].hospede.cpf));
		
		fflush(stdin);	
		printf("Telefone (X para retornar ao menu): ");
		fgets(habboHotel[andar-1][ap-1].hospede.telefone, sizeof(habboHotel[andar-1][ap-1].hospede.telefone), stdin);  //atribui o telefone para o hospede no quarto
		habboHotel[andar-1][ap-1].hospede.telefone[strcspn(habboHotel[andar-1][ap-1].hospede.telefone, "\n")] = '\0';
			if(habboHotel[andar-1][ap-1].hospede.telefone[0] == 'X' || habboHotel[andar-1][ap-1].hospede.telefone[0] == 'x')   //para retornar ao menu
			{
				system("cls");
				indice();
				return 0;
    		}
		fflush(stdin);
		printf("Email (X para retornar ao menu): ");
		fgets(habboHotel[andar-1][ap-1].hospede.email, sizeof(habboHotel[andar-1][ap-1].hospede.email), stdin);  //atribui o email para o hospede no quarto
		habboHotel[andar-1][ap-1].hospede.email[strcspn(habboHotel[andar-1][ap-1].hospede.email, "\n")] = '\0';
			if(habboHotel[andar-1][ap-1].hospede.email[0] == 'X' || habboHotel[andar-1][ap-1].hospede.email[0] == 'x')   //para retornar ao menu
			{
				system("cls");
				indice();
				return 0;
    		}
		fflush(stdin);
		printf("Endereco (X para retornar ao menu): ");
		fgets(habboHotel[andar-1][ap-1].hospede.endereco, sizeof(habboHotel[andar-1][ap-1].hospede.endereco), stdin);  //atribui o endereco para o hospede no quarto
		habboHotel[andar-1][ap-1].hospede.endereco[strcspn(habboHotel[andar-1][ap-1].hospede.endereco, "\n")] = '\0';
			if(habboHotel[andar-1][ap-1].hospede.endereco[0] == 'X' || habboHotel[andar-1][ap-1].hospede.endereco[0] == 'x')   //para retornar ao menu
			{
				system("cls");			
				indice();
				return 0;
    		}
    		
    	else 
		{
    		habboHotel[andar-1][ap-1].apartamento = 'O';
    		mapaQuartos();	
			printf("Checkin realizado com sucesso!\n\n");
			system("pause");
			system("cls");
		}
	}
}

int checkout()                               //funcao para fazer check-out
{
	char apto[5];
	int andar, ap;
	char cpf[15];
	
	printf("Digite o apartamento no formato AndarQuarto (ex. 302: andar 3, ap 2)\n(X para retornar ao menu): ");
	scanf("%5s", apto);
	fclear();
	
	if(apto[0] == 'X' || apto[0] == 'x')                      //para retornar ao menu
	{
		system("cls");
		indice();
		return 0;
    }
	
	andar = apto[0] - '0';
	ap = (apto[1] - '0')*10 + apto[2] - '0';
	
	if(apto[3] != '\0'&& apto[0] != '0')
	{
		andar = (apto[0] - '0')*10 + apto[1] - '0';
		ap = (apto[2] - '0')*10 + apto[3] - '0';
	}
	if (apto[2] == '\0')
    {
    	printf("Apartamento invalido\nDigite um numero AAQQ ou AQQ\n\n");
    	return checkout();
	}
	
	if((andar<1 || andar > 20) || (ap<1 || ap > 14))
	{
		printf("Andar invalido!\nDigite um numero AAQQ ou AQQ\n\n");
		return checkout();
	}
	
	if((habboHotel[andar-1][ap-1].apartamento) != ('O'))
	{
		printf("Este quarto nao esta ocupado!\n\n");
		return checkout();
	}
	
	else
	{	
		char cpf2[12];
			do
			{
				fflush(stdin);
				printf("\nCPF (Apenas numeros)(X para retornar ao menu)\n");
				printf("*O CPF devera ser o mesmo utilizado no checkin!: ");
				scanf("%11s", cpf2);
				fclear();
			
				if(cpf2[0] == 'X' || cpf2[0] == 'x')        //para retornar ao menu
				{
					system("cls");	
					indice();
					return 0;
		    	}
				
				if(!comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2))
				{
					printf("CPF Incorreto\n\n");                  //cpf nao compativel com o armazenado
				}
			
			}while(!comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2));
		
		if(comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2))
		{
			habboHotel[andar-1][ap-1].apartamento = '.';
			mapaQuartos();
			printf("Checkout realizado com sucesso!\n\n");     //cpf compativel com o armazenado
		}
		system("pause");
		system("cls");
	}
}

int cancelar()                               //funcao para cancelar uma reserva
{  
	char apto[5];
	int andar, ap;
	char cpf2[15];
	
	printf("Digite o apartamento no formato AndarQuarto (ex. 302: andar 3, ap 2)\n(X para retornar ao menu): ");
	scanf("%s", apto);
	fclear();
	
	if(apto[0] == 'X' || apto[0] == 'x')         //para retornar ao menu
	{
		system("cls");
		indice();
		return 0;
    }
	
	andar = apto[0] - '0';
	ap = (apto[1] - '0')*10 + apto[2] - '0';
	
	if(apto[3] != '\0' && apto[0] != '0')
	{
		andar = (apto[0] - '0')*10 + apto[1] - '0';
		ap = (apto[2] - '0')*10 + apto[3] - '0';
	}
	if (apto[2] == '\0')
    {
    	printf("Apartamento invalido!\nDigite um numero AAQQ ou AQQ\n\n");
    	return cancelar();
	}
	
	if((andar<1 || andar > 20) || (ap<1 || ap > 14))
	{
		printf("Andar invalido!\nDigite um numero AAQQ ou AQQ\n\n");
		return cancelar();
	}
	
	if((habboHotel[andar - 1][ap -1].apartamento) != 'R')
	{
		printf("Apartamento indisponivel!\n\n");
		return cancelar();
	} 
	
		do
		{
			printf("CPF (Apenas numeros)(X para retornar ao menu)\n");
			printf("*O CPF devera ser o mesmo da reserva!: ");
			scanf("%11s", cpf2);
			fclear();
			
			if(cpf2[0] == 'X' || cpf2[0] == 'x')            //para retornar ao menu
			{
				system("cls");	
				indice();
				return 0;
		    }
			
			if(!comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2))
			{
				printf("CPF Incorreto\n\n");                  //cpf nao compativel com o armazenado
			}	
			
		}while(!comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2));
		
		if(comparaCpf(habboHotel[andar-1][ap-1].hospede.cpf, cpf2))
		{
			habboHotel[andar-1][ap-1].apartamento = '.';
			mapaQuartos();
			printf("Cancelamento de reserva realizado com sucesso!\n\n");                  //cpf compativel com o armazenado
		}
		system("pause");
		system("cls");
}

void taxaOcupacao()                          //funcao para calcular a % dos quartos ocupados e reservados
{
    float ocupados = 0, reservados = 0;
    for (int i = 0; i < ANDARES; i++) 
	{
        for (int j = 0; j < APS; j++) 
		{
            if (habboHotel[i][j].apartamento == 'O')
			{
            	ocupados++;	                 //aumenta contador para os ocupados
			}
            else if (habboHotel[i][j].apartamento == 'R')
			{
           		reservados++;	             //aumenta contador para os ocupados
			}
        }
    }

    float taxaOcupacao = ocupados / (ANDARES * APS) * 100;
    float taxaReservas = reservados / (ANDARES * APS) * 100;

    printf("Taxa de ocupacao: %.2f%%\n", taxaOcupacao);
    printf("Taxa de reservas: %.2f%%\n", taxaReservas);
    system("pause");
	system("cls");
}

int validaCpf(char cpf[12])                  //funcao para verificar se o cpf é valido (somente numeros)
{
	for(int i = 0; i < 11; i++)
	{
		
		if(cpf[i] < '0' || cpf[i] > '9')
		{
			printf("CPF invalido!\nDigite novamente: ", cpf);
			return 0;
		}
	}
		return 1;
}

int comparaCpf(char cpf[12], char cpf2[12])  //funcao para comparar cpfs (se compativei ou nao)
{ 
	return !strcmp(cpf, cpf2);
}

void fclear()                                //funcao para limpar o buffer
{
	char caract;
	while((caract = fgetc(stdin)) != EOF && caract != '\n');
}