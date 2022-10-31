#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int count, qtd;
	long inicio, tamanho, meio, final;
	
	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	
	count = 0;
	inicio = 0;
	
	f = fopen("cep_ordenado.dat","rb");
	fseek(f,0,SEEK_END);
	tamanho = ftell(f);
	final = (tamanho/sizeof(Endereco))-1;

while(inicio <= final)
	{
		meio = (inicio + final)/2;
		fseek(f,meio * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);
		count++;
		
		if(strncmp(argv[1],e.cep,8)==0)
		{
			printf("CEP existe!\n\n");
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			printf("Total lido(s): %d\n", count);
			break;
			
		}
		
		else if(strncmp(argv[1],e.cep,8)>0)
		{
			inicio = meio + 1;
		}
		else{
			final = meio - 1;
		}
    }
    if(strncmp(argv[1],e.cep,8) != 0){
    	printf("CEP não existe!");
    	printf("Total lido(s): %d\n", count);
	}		
	fclose(f);
}
