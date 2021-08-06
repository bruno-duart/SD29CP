#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG 1024
#define PORTA 4321

int ler_resposta_servidor(int socket_desc, char *resposta_servidor, int prio);
int interpreta_resposta(int status);

int main(int argc , char *argv[]){
	// variaveis
	int socket_desc;
	struct sockaddr_in servidor;
	char *mensagem;
	char resposta_servidor[MAX_MSG];
	int tamanho, numcompeticao, ret=3;
	char *ipservidor = "127.0.0.1";


        //Passo 1: Criar o socket 
	// AF_INET = ARPA INTERNET PROTOCOLS
	// SOCK_STREAM = TCP
	// 0 = protocolo IP
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
     
	if (socket_desc == -1){
		printf("Nao foi possivel criar socket\n");
		return -1;	
	}

	/* Informacoes para conectar no servidor */
	// IP do servidor
	// familia ARPANET
	// Porta - hton = host to network short (2bytes)
	servidor.sin_addr.s_addr = inet_addr(ipservidor);
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(PORTA);

	//Conectar no servidor
	if (connect(socket_desc , (struct sockaddr *)&servidor , sizeof(servidor)) < 0){
		printf("Nao foi possivel conectar\n");
		return -1;
	}
	printf("Conectado no servidor!!!\n");
	/*****************************************/


	/*******COMUNICAO - TROCA DE MENSAGENS **************/

	//Passo 3: Realizar a comunição com o servidor segundo um protocolo.


	//Envia mensagem para o servidor
	//mensagem = "A";

	

	//Recebendo resposta do servidor (echo)
	/*if( (tamanho = recv(socket_desc, resposta_servidor, MAX_MSG , 0)) < 0){
		printf("Falha ao receber resposta\n");
		return -1;
	}
	printf("Resposta: ");
	resposta_servidor[tamanho] = '\0';*/

	if( (tamanho = recv(socket_desc, resposta_servidor, MAX_MSG , 0)) < 0){
		printf("Falha ao receber resposta\n");
		exit(1);
	}
	resposta_servidor[tamanho] = '\0';
	puts(resposta_servidor);
	while( (ret != 1) && (ret != 2 ) ){
		//gets(mensagem);
		printf("Digite sua opção: ");
		scanf("%s", mensagem);
		printf("\nEnviando: %s\n", mensagem);
		if( send(socket_desc , mensagem , strlen(mensagem) , 0) < 0){
			printf("Erro ao enviar mensagem\n");
			return -1;
		}
		ret = ler_resposta_servidor(socket_desc, resposta_servidor, 0);
	}

	if( (tamanho = recv(socket_desc, resposta_servidor, MAX_MSG , 0)) < 0){
		printf("Falha ao receber resposta\n");
		exit(1);
	}
	resposta_servidor[tamanho] = '\0';
	printf("%s", resposta_servidor);
	scanf("%s", mensagem);
	printf("\nEnviando: %s\n", mensagem);
	if( send(socket_desc , mensagem , strlen(mensagem) , 0) < 0){
		printf("Erro ao enviar mensagem\n");
		return -1;
	}

	if( (tamanho = recv(socket_desc, resposta_servidor, MAX_MSG , 0)) < 0){
		printf("Falha ao receber resposta\n");
		exit(1);
	}
	resposta_servidor[tamanho] = '\0';
	printf("%s", resposta_servidor);
	//gets(mensagem);
	/*****************************************/
		//Passo 4: Encerrar conexão
	getchar();
	close(socket_desc);
	printf("Cliente finalizado com sucesso!\n");
	return 0;
}

int ler_resposta_servidor(int socket_desc, char *resposta_servidor, int prio){
	int tamanho;
	if( (tamanho = recv(socket_desc, resposta_servidor, MAX_MSG , 0)) < 0){
		printf("Falha ao receber resposta\n");
		exit(1);
	}
	//printf("Resposta: %ld ", strlen(resposta_servidor));
	resposta_servidor[tamanho] = '\0';
	
	return interpreta_resposta(resposta_servidor[0]-'0');
}

int interpreta_resposta(int status){
	switch (status)
	{
	case 1:
		printf("Então sou ímpar\n");
		break;
	case 2:
		printf("Então sou par\n");
		break;
	default:
		printf("Opção inválida\n");
		break;
	}

	return status;
}