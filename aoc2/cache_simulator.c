#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct {
    int valid;
    int tag;
    int accessTime;     //pro LRU
    int insertionTime;  //pro FIFO
    int lastAccessedAddress;  // pra rastrear o endereço do último acesso
} CacheLine;

typedef struct{
    int numSets;
    int blockSize;
    int associativity;
    CacheLine *lines;
} Cache;

typedef struct {
    int compulsorio;
    int capacidade;
    int conflito;
    int hit;
    int miss;
} MissCounters;

typedef enum {  //enumera cada um de 0 a 2
    LRU,
    FIFO,
    RANDOM
} ReplacementPolicy;

Cache* initializeCache(int num_sets, int block_size, int associativity);
void freeCache (Cache *cache);
int getIndex(int address, int block_size, int num_sets);
int getTag(int address, int block_size, int num_sets);
void readCache(Cache *cache, int address, MissCounters *missCounters, ReplacementPolicy policy, int *totalAccesses);
void openFile(Cache *cache, const char *fileName, MissCounters *missCounters, ReplacementPolicy policy, int *totalAccesses);
int findReplacementIndex(Cache *cache, ReplacementPolicy policy, int index);
int findFIFOIndex(Cache *cache, int index);
int findLRUIndex(Cache *cache, int index);
int isCacheFull(Cache *cache);

int main( int argc, char *argv[ ] )
{
    if (argc != 7){
		printf("Numero de argumentos incorreto. Utilize:\n");
		printf("./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada\n");
		exit(EXIT_FAILURE);
	}
	int nsets = atoi(argv[1]);
	int bsize = atoi(argv[2]);
	int assoc = atoi(argv[3]);
	char *subst = argv[4];
	int flagOut = atoi(argv[5]);
	char *arquivoEntrada = argv[6];

	// printf("nsets = %d\n", nsets);
	// printf("bsize = %d\n", bsize);
	// printf("assoc = %d\n", assoc);
	// printf("subst = %s\n", subst);
	// printf("flagOut = %d\n", flagOut);
	// printf("arquivo = %s\n", arquivoEntrada);

/*Pra fazer por scanf*/
    // int nsets, bsize, assoc, flagOut;
    // char subst[10], arquivoEntrada[100];
    // srand(time(NULL));

    // char command[50];
    // scanf("%s %d %d %d %s %d %s", command, &nsets, &bsize, &assoc, subst, &flagOut, arquivoEntrada);

    // if (strcmp(command, "./cache_simulator") != 0) {
    //     printf("Comando invalido. Use o formato ./cache_simulator <nsets> <bsize> <assoc> <substituicao> <flag_saida> arquivo_de_entrada\n");
    //     return 1;
    // }

    ReplacementPolicy policy;
    if (strcmp(subst, "L") == 0) {
        policy = LRU;
    } else if (strcmp(subst, "F") == 0) {
        policy = FIFO;
    } else if (strcmp(subst, "R") == 0) {
        policy = RANDOM;
    } else {
        printf("Politica de substituicao invalida.\n");
        exit(EXIT_FAILURE);
    }

    
    int totalAccesses = 0; //inicializa o contador de acessos
    MissCounters missCounters = {0, 0, 0, 0, 0};  // Inicializa todos os contadores


    Cache *cache = initializeCache(nsets, bsize, assoc);  // Inicializar a cache
    

    openFile(cache, arquivoEntrada, &missCounters, policy, &totalAccesses);  // Abrir o arquivo binário


    // Calcula as taxas de miss e hit
    float hitRate = (float)missCounters.hit / totalAccesses;
    float missRate = (float)missCounters.miss / totalAccesses;

    float TotalMisses = missCounters.miss; 
    float compulsorioRate = (float)missCounters.compulsorio / TotalMisses;
    float conflitoRate = (float)missCounters.conflito / TotalMisses;
    float capacidadeRate = (float)missCounters.capacidade / TotalMisses;

if (flagOut == 0) {
    printf("Total de hit = %d\n", missCounters.hit);
    printf("Total de miss = %d\n", missCounters.miss);
    printf("Taxa de hits = %.2f%%\n", hitRate * 100);
    printf("Taxa de miss = %.2f%%\n", missRate * 100);
    printf("Taxa de miss compulsorio = %.2f%%\n", compulsorioRate * 100);
    printf("Taxa de miss de capacidade = %.2f%%\n", capacidadeRate * 100);
    printf("Taxa de miss de conflito = %.2f%%\n", conflitoRate * 100);

} else if (flagOut == 1) {
    printf("%d %.4f %.4f %.2f %.2f %.2f\n", totalAccesses, hitRate, missRate, compulsorioRate, capacidadeRate, conflitoRate);
}
    freeCache(cache);
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
        cache->lines[i].accessTime = 0;
    }

    return cache;
}

// pra liberar a cache
void freeCache(Cache *cache) {
    for (int i = 0; i < cache->numSets; i++) {  // percorre os conjuntos
        for (int j = 0; j < cache->associativity; j++) {    //percorre cada linha
            free(&cache->lines[i * cache->associativity + j]);  //libera cada linha
        }
    }

    // Libera a memória para a estrutura de cache
    free(cache);
}

// pra achar o indice mapeado
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


// pra ler a cache 
void readCache(Cache *cache, int address, MissCounters *missCounters, ReplacementPolicy policy, int *totalAccesses) {
    int index = getIndex(address, cache->blockSize, cache->numSets);
    int tag = getTag(address, cache->blockSize, cache->numSets);
    int lineIndex = index * cache->associativity;
    int hitIndex = -1; // indice da linha que vai ter hit (-1 aqui para indicar um miss)

    for (int i = 0; i < cache->associativity; i++) {
        if (cache->lines[lineIndex + i].valid && cache->lines[lineIndex + i].tag == tag) {
            hitIndex = i;
            break; // se for hit sai do loop
        }
    }

    if (hitIndex != -1) {
        // Hit
        missCounters->hit++;
        
        // Atualiza o tempo de acesso da linha atingida para o valor mais recente
        if (policy == LRU)
            cache->lines[lineIndex + hitIndex].accessTime = (*totalAccesses);

        
     } else {
        // Miss
        missCounters->miss++;

        // Compulsório: O bloco nunca foi carregado na cache
        // Capacidade: A cache está cheia
        // Conflito: O bloco não está na cache devido a uma colisão de conjunto

        int emptyLineIndex = -1; // indice de uma linha vazia na cache
        int replaceIndex = -1;   // indice da linha para substituição

        for (int i = lineIndex; i < lineIndex + cache->associativity; i++) {
            if (!cache->lines[i].valid) {
                emptyLineIndex = i;
                break;
            }
        }

        if (emptyLineIndex != -1) {
            missCounters->compulsorio++; 
            replaceIndex = emptyLineIndex;

        } else {
            replaceIndex = findReplacementIndex(cache, policy, index); // Encontra uma linha para substituir
            int cacheCheia = isCacheFull(cache);

            if (cacheCheia) {
                missCounters->capacidade++;
            } else {
                missCounters->conflito++;
            }
        }

        // Substituir a linha
        cache->lines[replaceIndex].valid = 1;
        cache->lines[replaceIndex].tag = tag;
        cache->lines[replaceIndex].lastAccessedAddress = address;

        if (policy == LRU) {
            // Atualiza o tempo de acesso da linha atual para o valor mais recente
            cache->lines[replaceIndex].accessTime = (*totalAccesses);

        } else if (policy == FIFO) {
            // Atualiza o tempo de inserção da linha atual para o valor mais recente
            cache->lines[replaceIndex].insertionTime = (*totalAccesses);
        }
    }
    (*totalAccesses)++;
}


// vai escolher qual politica usar dependendo da entrada
int findReplacementIndex(Cache *cache, ReplacementPolicy policy, int index) {
    int lineIndex = index * cache->associativity;
    int replaceIndex;

    if (policy == LRU) {
        replaceIndex = findLRUIndex(cache, index);
    } else if (policy == FIFO) {
        replaceIndex = findFIFOIndex(cache, index);
    } else if (policy == RANDOM) {
        replaceIndex = lineIndex + rand() % cache->associativity;
    }

    return replaceIndex;
}


// pra abrir o binario
void openFile(Cache *cache, const char *fileName, MissCounters *missCounters, ReplacementPolicy policy, int *totalAccesses) {
    FILE *inputFile = fopen(fileName, "rb");

    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(EXIT_FAILURE);
    }

    int address;
    while (fread(&address, sizeof(int), 1, inputFile) == 1) {
        address = __builtin_bswap32(address);// Inverte os bits pois o arquivo está em big endian
        // le um endereço do arquivo binário
        readCache(cache, address, missCounters, policy, totalAccesses);  // simula a leitura da cache para o endereço lido
    }

    fclose(inputFile);  // fecha o arquivo após a leitura
}

// pra achar qual linha substituir no LRU
int findLRUIndex(Cache *cache, int index) {
    int oldestIndex = index * cache->associativity; //inicializa a variavel com o indice da primeira linha no conjunto
    int oldestAccessTime = cache->lines[oldestIndex].accessTime; //inicializa a variavel com o tempo de acesso da primeira linha no conjunto

    for (int i = index * cache->associativity + 1; i < (index + 1) * cache->associativity; i++) {   //percorre a partir da segunda linha do conjunto
        if (cache->lines[i].accessTime < oldestAccessTime) {    // verifica se o tempo de acesso da linha atual eh menor do que o do mais antigo 
            oldestIndex = i;    //se sim, atualiza o indice pra linha atual
            oldestAccessTime = cache->lines[i].accessTime;  // atualiza oldestAccessTime com o tempo de acesso da linha atual
        }
    }

    return oldestIndex;
}

// pra achar qual linha substituir no FIFO
int findFIFOIndex(Cache *cache, int index) {
    int oldestIndex = index * cache->associativity; //inicializa a variavel com o indice da primeira linha no conjunto
    int oldestInsertionTime = cache->lines[oldestIndex].insertionTime; //inicializa a variavel com o tempo de inserção da primeira linha no conjunto

    for (int i = index * cache->associativity + 1; i < (index + 1) * cache->associativity; i++) { //percorre a partir da segunda linha do conjunto
        if (cache->lines[i].insertionTime < oldestInsertionTime) {   // verifica se o tempo de inserção da linha atual eh menor do que o do mais antigo 
            oldestIndex = i; //se sim, atualiza o indice pra linha atual
            oldestInsertionTime = cache->lines[i].insertionTime; // atualiza a variavel com o tempo de inserção da linha atual
        }
    }

    return oldestIndex;
}

// verifica se a cache ta cheia pra determianr qual miss eh capacidade ou conflito
int isCacheFull(Cache *cache) {
    for (int i = 0; i < cache->numSets; i++) {  //percorre os conjuntos
        int occupiedLines = 0;
        for (int j = 0; j < cache->associativity; j++) {    //percorre as linhas
            if (cache->lines[i * cache->associativity + j].valid) { //ve se ta como valida (tem coisa)
                occupiedLines++;    //se sim, dai incrementa
            }
        }
        if (occupiedLines < cache->associativity) { //aqui ele verifica se a quantidade de linhas ocupadas é menor que a quntd total de linhas
            return 0; // se sim, cache não ta cheia
        }
    }
    return 1; // se não, cache ta cheia
}