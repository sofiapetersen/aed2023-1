#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int valid;
    int tag;
    char *data;
} CacheLine;

typedef struct{
    int numSets;
    int blockSize;
    int associativity;
    CacheLine *lines;
} Cache;

Cache* initializeCache(int num_sets, int block_size, int associativity);
int getIndex(int address, int block_size, int num_sets);
int getTag(int address, int block_size, int num_sets);
void readCache(Cache *cache, int address);
void freeCache (Cache *cache);

int main( int argc, char *argv[ ] )
{
	if (argc != 7){
		printf("Numero de argumentos incorreto. Utilize:\n");
		printf("./cache_simulator <nsets> <bsize> <assoc> <substituicao> <flag_saida> arquivo_de_entrada\n");
		exit(EXIT_FAILURE);
	}
	int nsets = atoi(argv[1]);
	int bsize = atoi(argv[2]);
	int assoc = atoi(argv[3]);
	char *subst = argv[4];
	int flagOut = atoi(argv[5]);
	char *arquivoEntrada = argv[6];



	printf("nsets = %d\n", nsets);
	printf("bsize = %d\n", bsize);
	printf("assoc = %d\n", assoc);
	printf("subst = %s\n", subst);
	printf("flagOut = %d\n", flagOut);
	printf("arquivo = %s\n", arquivoEntrada);


    // Seu codigo vai aqui


	return 0;
}

// vamos inicializar a cache e alocar memoria
Cache* initializeCache(int num_sets, int block_size, int associativity){
    int i;

    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->numSets = num_sets;
    cache->blockSize = block_size;
    cache->associativity = associativity;

    cache->lines = (CacheLine *)malloc(sizeof(CacheLine) * num_sets * associativity);
    //acessar a linha da cache e alocar o tamanho necessário pra armazenar todas as linhas

    for(i = 0; i < num_sets * associativity; i++){      //num_sets * associativity representa o total de linhas da cache
        cache->lines[i].tag = 0;
        cache->lines[i].valid = 0;
        cache->lines[i].data = (char *)malloc(sizeof(block_size));      //array que armazena os dados em uma linha de cache, e o tamanho é o tamanho do bloco    
    }

    return cache;
}

// proxima funcao é pra achar o indice mapeado
int getIndex(int address, int block_size, int num_sets){

    int index;

    index = (address / block_size) % num_sets;  // o endereço / tamanho do bloco calcula a parte do endereçço q nao eh usada pra indexar, mas eh usada pra achar o bloco dentro do conjunto
                                                // o % numsets vai resultar no indice que queremos
    return index;   // indice do conjunto q o endereço dado deve ser mapeado na cache
}

// funcao pra pegar o tag do endereço na cache
int getTag(int address, int block_size, int num_sets) {
    
    int tag;

    tag = address / (block_size * num_sets);    // o resultado disso eh a parte do endereço que vai ser a tag, identifica um bloco na memoria
    
    return tag;     //permite q o simulador determine se o bloco esta presente ou ausente na cache numa operacao
}


// agora sim siular a leitura da cache
void readCache(Cache *cache, int address){     //um ponteiro vai ser pra estrutura da cache que determinamos e o int eh do endereco
    int index, tag, i;

    index = getIndex(address, cache->blockSize, cache->numSets);       //calcular o indice, pela funcao que fizemos ali em cima
    tag = getTag(address, cache->blockSize, cache->numSets);       //calcular a tag, pela funcao que fizemos ali em cima

    for(i = 0; i < cache->associativity; i++){  //pra percorrer todas as linhas no conjunto
        CacheLine *line;    //ponteiro pra linha especifica
        line = &cache->lines[index * cache->associativity + i];     //esse indice da linha faz percorrer todas as linhas dentro do conjunto, dentro do loop for

        if(line->valid && line->tag == tag){        //aqui olha se os dados sao validos e se a tag da linha eh a mesma que a tag calculada
            printf("\n----Cache hit----\n");
            return;
        }
    }

    printf("\n----Cache miss----\n");   //se aquele for ali n der certo, então foi um miss

}

// pra liberar a cache
void freeCache (Cache *cache){
    int i;

    for(i = 0; i < cache->numSets * cache->associativity; i++){ //pra poder percorrer todas as linhas
        free(cache->lines->data[i]);    //dai libera os dados
    }

    free(cache->lines); //libera o espaço alocado pras linhas
    free(cache);        //libera o espaço alocao pra cache
}

