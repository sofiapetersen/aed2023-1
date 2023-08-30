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
int getIndex(int address, int block_size, int num_sets);
int getTag(int address, int block_size, int num_sets);
void readCache(Cache *cache, int address, MissCounters *missCounters, ReplacementPolicy policy);
void freeCache (Cache *cache);
void openFile(Cache *cache, const char *fileName, MissCounters *missCounters, ReplacementPolicy policy, int *totalAccesses);
void missCounters(MissCounters *missCounters);
int findFIFOIndex(Cache *cache, int index);
int findLRUIndex(Cache *cache, int index);

int main()
{

    int nsets, bsize, assoc, flagOut;
    char subst[10], arquivoEntrada[100];
    srand(time(NULL));

    char command[50];
    scanf("%s %d %d %d %s %d %s", command, &nsets, &bsize, &assoc, subst, &flagOut, arquivoEntrada);

    if (strcmp(command, "/cache_simulator") != 0) {
        printf("Comando inválido. Use o formato /cache_simulator <nsets> <bsize> <assoc> <substituicao> <flag_saida> arquivo_de_entrada\n");
        return 1;
    }

	printf("nsets = %d\n", nsets);
	printf("bsize = %d\n", bsize);
	printf("assoc = %d\n", assoc);
	printf("subst = %s\n", subst);
	printf("flagOut = %d\n", flagOut);
	printf("arquivo = %s\n\n", arquivoEntrada);

    ReplacementPolicy policy;
    if (strcmp(subst, "L") == 0) {
        policy = LRU;
    } else if (strcmp(subst, "F") == 0) {
        policy = FIFO;
    } else if (strcmp(subst, "R") == 0) {
        policy = RANDOM;
    } else {
        printf("Política de substituição inválida.\n");
        exit(EXIT_FAILURE);
    }

    
    int totalAccesses = 0; //inicializa o contador de acessos
    MissCounters missCounters = {0, 0, 0, 0, 0};  // Inicializa todos os contadores


    Cache *cache = initializeCache(nsets, bsize, assoc);  // Inicializar a cache
    

    openFile(cache, arquivoEntrada, &missCounters, policy, &totalAccesses);  // Abrir o arquivo binário

    freeCache(cache);

// Calcula os hits e misses

    // Calcula as taxas de miss e hit
    float hitRate = (float)missCounters.hit / totalAccesses;
    float missRate = (float)missCounters.miss / totalAccesses;

    float compulsorioRate = (float)missCounters.compulsorio / totalAccesses;
    float conflitoRate = (float)missCounters.conflito / totalAccesses;
    float capacidadeRate = (float)missCounters.capacidade / totalAccesses;

if (flagOut == 0) {
    printf("Taxa de hits = %.2f%%\n", hitRate * 100);
    printf("Taxa de miss = %.2f%%\n", missRate * 100);
    printf("Taxa de miss compulsorio = %.2f%%\n", compulsorioRate * 100);
    printf("Taxa de miss de capacidade = %.2f%%\n", capacidadeRate * 100);
    printf("Taxa de miss de conflito = %.2f%%\n", conflitoRate * 100);
} else if (flagOut == 1) {
    printf("%d %.2f %.2f %.2f %.2f %.2f\n", totalAccesses, hitRate, missRate, compulsorioRate, capacidadeRate, conflitoRate);
}

    printf("\nMisses compulsorios: %d\n", missCounters.compulsorio);
    printf("Misses de capacidade: %d\n", missCounters.capacidade);
    printf("Misses de conflito: %d\n", missCounters.conflito);
    printf("Misses: %d\n", missCounters.miss);
    printf("Hits: %d\n", missCounters.hit);
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

void readCache(Cache *cache, int address, MissCounters *missCounters, ReplacementPolicy policy) {
    int index = getIndex(address, cache->blockSize, cache->numSets);
    int tag = getTag(address, cache->blockSize, cache->numSets);

    if (cache->lines[index].valid == 0) {
        missCounters->compulsorio++;
        cache->lines[index].valid = 1;
        cache->lines[index].tag = tag;
        missCounters->miss++;  // Incrementa o contador total de misses
    } else {
        if (cache->lines[index].tag == tag) {
            missCounters->hit++;  // Incrementa o contador de hits
        } else {
            int missType = cache->lines[index].valid ? 0 : 1;
            if (missType == 0) {
                missCounters->conflito++;
            } else if (missType == 1) {
                missCounters->capacidade++;
            }

            if (policy == LRU) {
                int lruIndex = findLRUIndex(cache, index);
                cache->lines[lruIndex].tag = tag;
            } else if (policy == FIFO) {
                int fifoIndex = findFIFOIndex(cache, index);
                cache->lines[fifoIndex].tag = tag;
            } else if (policy == RANDOM) {
                int randomIndex = rand() % cache->associativity;
                cache->lines[randomIndex].tag = tag;
            }
            missCounters->miss++;  // Incrementa o contador total de misses
        }
    }
}



// pra liberar a cache
void freeCache (Cache *cache){
    free(cache->lines); //libera o espaço alocado pras linhas
    free(cache);        //libera o espaço alocao pra cache
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
        // le um endereço do arquivo binário
        (*totalAccesses)++;  // Incrementa o contador de acessos
        readCache(cache, address, missCounters, policy);  // simula a leitura da cache para o endereço lido
    }

    fclose(inputFile);  // fecha o arquivo após a leitura
}

// so pra inicializar os misses
void missCounters(MissCounters *missCounters) {
    missCounters->compulsorio = 0;
    missCounters->capacidade = 0;
    missCounters->conflito = 0;
    missCounters->hit = 0;
    missCounters->miss = 0;
}

// pra achar qual linha substituir no LRU
int findLRUIndex(Cache *cache, int index) {
    int oldestIndex = index * cache->associativity; //inicializa a variavel com o indice da primeira linha no conjunto
    int oldestAccessTime = cache->lines[oldestIndex].accessTime; //inicializa a variavel com o tempo de acesso da primeira linha no conjunto

    for (int i = index * cache->associativity + 1; i < (index + 1) * cache->associativity; i++) {   //percorre a partir da segunda linha do conjunto
        if (cache->lines[i].accessTime < oldestAccessTime) {    // se o tempo de acesso da linha atual eh menor do que o do mais antigo 
            oldestIndex = i;    //se sim, atualiza o indice pra linha atual
            oldestAccessTime = cache->lines[i].accessTime;  // atualiza oldestAccessTime com o tempo de acesso da linha atual
        }
    }

    return oldestIndex - index * cache->associativity;  //retorna o indice da linha mais antiga no conjunto
}

int findFIFOIndex(Cache *cache, int index) {
    int oldestIndex = index * cache->associativity; //inicializa a variavel com o indice da primeira linha no conjunto
    int oldestInsertionTime = cache->lines[oldestIndex].insertionTime; //inicializa a variavel com o tempo de inserção da primeira linha no conjunto

    for (int i = index * cache->associativity + 1; i < (index + 1) * cache->associativity; i++) { //percorre a partir da segunda linha do conjunto
        if (cache->lines[i].insertionTime < oldestInsertionTime) {   // se o tempo de inserção da linha atual eh menor do que o do mais antigo 
            oldestIndex = i; //se sim, atualiza o indice pra linha atual
            oldestInsertionTime = cache->lines[i].insertionTime; //// atualiza a variavel com o tempo de inserção da linha atual
        }
    }

    return oldestIndex - index * cache->associativity; ///retorna o indice da linha mais antiga no conjunto
}
