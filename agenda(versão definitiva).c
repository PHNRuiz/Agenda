#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _pessoa{
	char Nome[100];
	char telefone[15];
	char email[120];

};

struct _agenda{

	struct _pessoa *cadastrados;
	int n;
	int nmax;

};

typedef struct _pessoa pessoa;
typedef struct _agenda agenda;

void tiraLinha(char *str){
	int i=0;
	while(str[i] != '\0' && str[i] != '\n' )
	    i++;
	str[i] = '\0';
}

agenda criagenda (int n){

	agenda g;
	g.n = 0;
	g.cadastrados = malloc(sizeof(pessoa) * n);
	g.nmax = n;
	return g;
}

agenda lerAgenda(){

    FILE* f = fopen("agenda.txt", "r");
    
    int n;
    fread(&n,sizeof(int), 1, f);
	agenda g = criagenda(2*n);
	fread(g.cadastrados,sizeof(pessoa), n, f);
	g.n = n;
	return g;
	
	fclose(f);

}

void gravaAgenda(agenda g){

	FILE* f = fopen("agenda.txt", "w");
	pessoa* atual = g.cadastrados;
	
	fwrite(&(g.n), sizeof(int),1,f);
	fwrite(atual, sizeof(pessoa), g.n,f);
	
	fclose(f);
	
}

void inserep(agenda g){
	
	fflush(stdin);
	puts("insira o Nome da pessoa:");
	fgets( g.cadastrados[g.n].Nome, 100, stdin );
	tiraLinha(g.cadastrados[g.n].Nome);
	puts("insira o telefone da pessoa:");
	fgets( g.cadastrados[g.n].telefone, 50, stdin );
	tiraLinha(g.cadastrados[g.n].telefone);
	puts("insira o email da pessoa:");
	fgets( g.cadastrados[g.n].email, 120, stdin );
	tiraLinha(g.cadastrados[g.n].email);
	g.n++;
	gravaAgenda(g);

}

void impritodos(agenda g){
	//agenda g = lerAgenda();
	int i;
	for(i=0;i<g.n;i++){
		puts("==========");
		printf("Nome do %d cadastrado:",i+1);
		printf(g.cadastrados[i].Nome);
		printf("\n");
		printf("telefone do %d cadastrado:",i+1);
		printf(g.cadastrados[i].telefone);
		printf("\n");
		printf("email do %d cadastrado:",i+1);
		printf(g.cadastrados[i].email);
		printf("\n");
	}
	puts("==========");

}

void imprium(int idx){
	agenda g = lerAgenda();
	puts("==========");
	printf("Nome do %d cadastrado:",idx+1);
	printf(g.cadastrados[idx].Nome);
	printf("\n");
	printf("telefone do %d cadastrado:",idx+1);
	printf(g.cadastrados[idx].telefone);
	printf("\n");
	printf("email do %d cadastrado:",idx+1);
	printf(g.cadastrados[idx].email);
	printf("\n");
	puts("==========");

}


int BuscaNome(agenda g){
	int i;
	char Nomebusca[100];
	fflush(stdin);
	fgets(Nomebusca, 100, stdin );
	tiraLinha(Nomebusca);
	for(i=0;i<g.n; i++){
		if( stricmp(g.cadastrados[i].Nome, Nomebusca) == 0){
			return i;
		}
	}
	return -1;
}
int Buscatel(agenda g){
	int i;
	char telbusca[100];
	fflush(stdin);
	fgets(telbusca, 100, stdin );
	tiraLinha(telbusca);
	for(i=0;i<g.n; i++){
		if( stricmp(g.cadastrados[i].telefone, telbusca) == 0){
			return i;
		}
	}
	return -1;
}
int Buscaemail(agenda g){
	int i;
	char emailbusca[100];
	fflush(stdin);
	fgets(emailbusca, 100, stdin );
	tiraLinha(emailbusca);
	for(i=0;i<g.n; i++){
		if( stricmp(g.cadastrados[i].email, emailbusca) == 0){
			return i;
		}
	}
	return -1;
}

void BBnome(agenda g){
	
	int i,j;
	for(i=0; i<g.n-1; i++ ){
        for(j=0; j<g.n-1; j++ ){
            if( strcmp(g.cadastrados[j].Nome, g.cadastrados[j+1].Nome) > 0 ){
				pessoa temp = g.cadastrados[j];
				g.cadastrados[j] = g.cadastrados[j+1];
				g.cadastrados[j+1] = temp;
			}
		}
	}
	
	impritodos(g);

}
void BBtel(agenda g){
	
	int i,j;
	for(i=0; i<g.n-1; i++ ){
        for(j=0; j<g.n-1; j++ ){
            if( strcmp(g.cadastrados[j].telefone, g.cadastrados[j+1].telefone) > 0 ){
				pessoa temp = g.cadastrados[j];
				g.cadastrados[j] = g.cadastrados[j+1];
				g.cadastrados[j+1] = temp;
			}
		}
	}
	
	impritodos(g);

}
void BBemail(agenda g){
	
	int i,j;
	for(i=0; i<g.n-1; i++ ){
        for(j=0; j<g.n-1; j++ ){
            if( strcmp(g.cadastrados[j].email, g.cadastrados[j+1].email) > 0 ){
				pessoa temp = g.cadastrados[j];
				g.cadastrados[j] = g.cadastrados[j+1];
				g.cadastrados[j+1] = temp;
			}
		}
	}
	impritodos(g);
}

void removep(agenda g,int idx){
	
	int ultpos, i;
	
	for(i=0;i<g.n;i++){
		ultpos = i;
	}
	
	pessoa temp = g.cadastrados[idx];
	g.cadastrados[idx] = g.cadastrados[ultpos];
	g.cadastrados[ultpos] = temp;
	g.n--;
	gravaAgenda(g);
	
}


int main(int argc, char *argv[]){
	int opc=1,opcsub=0,subsubopc=0;
	

	
	while(opc <=6){

		agenda g = lerAgenda();

		puts("");
		puts("QUAL OPERACAO DESEJA FAZER:");
		puts("");
		puts("1 - inserir pessoas");
		puts("2 - buscar pessoas");
		puts("3 - ordenar pessoas");
		puts("4 - remover pessoas");
        puts("5 - imprimir pessoas");
		puts("6 - sair");
		puts("");
		printf("DIGITE SUA OPCAO:");

		scanf("%d", &opc);

		printf("\n");
		
		if(opc == 1){
			inserep(g);
			
		}
		else if(opc == 2){
			puts("VOCE DESEJA BUSCAR POR:");
			puts("1 - nome");
			puts("2 - telefone");
			puts("3 - email");
			printf("DIGITE SUA OPCAO:");
			printf("\n");
			scanf("%d", &opcsub);
			
			if(opcsub == 1){
				int res = BuscaNome(g);
				if(res != -1){
					puts("Contato encontrado!");
					imprium(res);
				}	
				else{
					puts("Contato não encontrado!");
				}
			}
			if(opcsub == 2){
				int res = Buscatel(g);
				if(res != -1){
					puts("Contato encontrado!");
					imprium(res);
				}	
				else{
					puts("Contato não encontrado!");
				}
			}
			if(opcsub == 3){
				int res = Buscaemail(g);
				if(res != -1){
					puts("Contato encontrado!");
					imprium(res);
				}	
				else{
					puts("Contato não encontrado!");
				}
			}	
		}
		else if(opc == 3){
			puts("VOCE DESEJA ORDENAR POR:");
			puts("1 - Nome");
			puts("2 - telefone");
			puts("3 - email");
			printf("DIGITE SUA OPCAO:");
			printf("\n");
			scanf("%d", &opcsub);
			
			if(opcsub == 1){
				BBnome(g);
			}
			if(opcsub == 2){
				BBtel(g);
			}
			if(opcsub == 3){
				BBemail(g);
			}
		}
		else if(opc == 4){
			puts("VOCE DESEJA BUSCAR O CONTATO A SER REMOVIDO POR:");
			puts("1 - nome");
			puts("2 - telefone");
			puts("3 - email");
			printf("DIGITE SUA OPCAO:");
			printf("\n");
			scanf("%d", &opcsub);
			
			if(opcsub == 1){
				int res = BuscaNome(g);
				if(res != -1){
					puts("Contato encontrado!");
					imprium(res);
					puts("VOCE TEM CERTEZA QUE DESEJA REMOVER ESSE CONTATO?");
					puts("1 - sim");
					puts("2 - nao");
					printf("DIGITE SUA OPCAO:");
					printf("\n");
					scanf("%d", &subsubopc);
					if(subsubopc != 2){
						removep(g,res);
					}		
				}	
				else{
					puts("Contato não encontrado!");
				}
			}
			if(opcsub == 2){
				int res = Buscatel(g);
				if(res != -1){
					puts("Contato encontrado!");
					imprium(res);
					puts("VOCE TEM CERTEZA QUE DESEJA REMOVER ESSE CONTATO?");
					puts("1 - sim");
					puts("2 - nao");
					printf("DIGITE SUA OPCAO:");
					printf("\n");
					scanf("%d", &subsubopc);
					if(subsubopc != 2){
						removep(g,res);
					}		
				}	
				else{
					puts("Contato não encontrado!");
				}
			}
			if(opcsub == 3){
				int res = Buscaemail(g);
				if(res != -1){
					puts("Contato encontrado!");
					imprium(res);
					puts("VOCE TEM CERTEZA QUE DESEJA REMOVER ESSE CONTATO?");
					puts("1 - sim");
					puts("2 - nao");
					printf("DIGITE SUA OPCAO:");
					printf("\n");
					scanf("%d", &subsubopc);
					if(subsubopc != 2){
						removep(g,res);
					}		
				}	
				else{
					puts("Contato não encontrado!");
				}
			}
		}
		else if(opc == 5){
			impritodos(g);
		}
		else{
			break;
		}
	}


	system("pause");	
	return 0;
}
