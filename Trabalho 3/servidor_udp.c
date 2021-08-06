#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define TAMBUFFER 1024
#define PORTA 1234

int main(void){
	struct sockaddr_in addr_local;
	struct sockaddr_in addr_remoto;
	int socket_desc;
	socklen_t slen = sizeof(addr_remoto);
	char buf[TAMBUFFER];
	int tam_recebido;
	char p_o_i, *resultado, *vencedor;
	int num_jogador, num_servidor, soma, cont=0;
	int num_vitorias_servidor = 0, num_vitorias_cliente = 0;

	srand(time(NULL));


	// Passo 1 : Criando um socket UDP
	if ((socket_desc=socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		perror("Nao foi possivel criar socket");
		return -1;
	}
	
	// Associando o socket a todos IPs locais e escolhendo um PORTA ESPECIFICA
	memset((char *) &addr_local, 0, sizeof(addr_local));
	addr_local.sin_family = AF_INET;
	addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_local.sin_port = htons(PORTA);

	if (bind(socket_desc, (struct sockaddr *)&addr_local, sizeof(addr_local)) < 0){
		perror("Erro ao fazer bind!");
		return -1;
	}
	
	// Passo 2: Realizar a comunicação com os clientes - fica em loop
	while(1){
		printf("Aguardando requisição ...\n");
		
		// processando pacote recebido
		if ( (tam_recebido = recvfrom(socket_desc, buf, TAMBUFFER, 0, (struct sockaddr *)&addr_remoto, &slen)) > 0){
			buf[tam_recebido]='\0';
			printf("Pacote recebido de: %s:[%d]\nDados: %s\n\n", 
				inet_ntoa(addr_remoto.sin_addr), ntohs(addr_remoto.sin_port), buf);
			
			while (cont++ < 5){	
				// respondendo ao addr_remoto
				printf("Rodada %d de 5\n", cont-1);
				sprintf(buf, "%s%d%s%s", "Rodada ", cont-1, " de 5\n","Par (P) ou Ímpar (I)?:");;
				if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
					perror("Erro ao enviar resposta!!!");
				}
				p_o_i = 'c';
				while(p_o_i == 'c'){ // Validação da opção escolhida pelo cliente
					if ( (tam_recebido = recvfrom(socket_desc, buf, TAMBUFFER, 0, (struct sockaddr *)&addr_remoto, &slen) > 0) ){
						buf[tam_recebido] = '\0';
						printf("O Cliente escolheu: %s\n",buf);
					}
					if (buf[0] == 'P' || buf[0] == 'p'){
						printf("Então serei ímpar\n");
						p_o_i = 'I';
						break;
					} else if (buf[0] == 'I' || buf[0] == 'i'){
						printf("Então serei par\n");
						p_o_i = 'P';
						break;
					} else {
						printf("Opção inválida! Escolha outra opção.\n");
						sprintf(buf, "%s", "C");
					}
					if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
						perror("Erro ao enviar resposta!!!");
					}
				}
				sprintf(buf, "%s", "V"); // Resposta válida
				if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
					perror("Erro ao enviar resposta!!!");
				}

				// Leitura do número escolhido pelo cliente
				sprintf(buf, "%s", "Digite um número menor (ou igual) a 10.");
				if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
					perror("Erro ao enviar resposta!!!");
				}
				do{
					if ( (tam_recebido = recvfrom(socket_desc, buf, TAMBUFFER, 0, (struct sockaddr *)&addr_remoto, &slen) > 0) ){
						num_jogador = atoi(buf);
						printf("O Cliente digitou: %d\n",num_jogador);
					}

					sprintf(buf, "%s", "");
					if ( (num_jogador < 0) || (num_jogador > 10) ){
						printf("Este é um valor inválido\n");
						sprintf(buf, "%s", "C");
						if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
							perror("Erro ao enviar resposta!!!");
						}
					}
				}while( (num_jogador < 0) || (num_jogador > 10) );
				sprintf(buf, "%s", "V"); // Resposta válida
				if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
					perror("Erro ao enviar resposta!!!");
				}
				num_servidor = rand() % 11;
				sprintf(buf, "Meu número é: %d", num_servidor); // Resposta válida
				if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
					perror("Erro ao enviar resposta!!!");
				}
				soma = num_servidor + num_jogador;
				if ( soma % 2 == 0){
					resultado = "PAR";
					if (p_o_i == 'P'){
						vencedor = "Servidor";
						num_vitorias_servidor++;
					} else {
						vencedor = "Cliente";
						num_vitorias_cliente++;
					}
				} else {
					resultado = "ÍMPAR";
					if (p_o_i == 'I'){
						vencedor = "Servidor";
						num_vitorias_servidor++;
					} else {
						vencedor = "Cliente";
						num_vitorias_cliente++;
					}
				}
				sprintf(buf, "Soma: %d\nO resultado do par ou ímpar é: %s\nO vencedor foi: %s\nPlacar atual: Serv %d x %d Cli\n", soma, resultado, vencedor, num_vitorias_servidor, num_vitorias_cliente);
				if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
					perror("Erro ao enviar resposta!!!");
				}
				
				// Anúncio das respostas
				if (num_vitorias_servidor == 3 || num_vitorias_cliente == 3){
					sprintf(buf, "%s", "Y");
					if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
						perror("Erro ao enviar resposta!!!");
					}
					if (num_vitorias_cliente == 3){
						sprintf(buf, "%s", "O VENCEDOR É O CLIENTE!!");
						if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
							perror("Erro ao enviar resposta!!!");
						}
					} else if (num_vitorias_servidor == 3){
						sprintf(buf, "%s", "O VENCEDOR É O SERVIDOR!!");
						if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
							perror("Erro ao enviar resposta!!!");
						}
					}
					break;
				} else { // Continua competição
					sprintf(buf, "%s", "N");
					if ((sendto(socket_desc, buf, strlen(buf), 0, (struct sockaddr *)&addr_remoto, slen)) <0){
						perror("Erro ao enviar resposta!!!");
					}
				}				
			}
		}
	}
	//Passo 3: Fechar socket
	close(socket_desc);
	return 0;
}
