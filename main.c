#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Protótipo de todas as funções
void troca(int  *a, int *b, long long *movimentacoes);
void bubble_sort (int *vetor, int tamanho, long long *comparacoes, long long *movimentacoes);
void insertion_sort(int *vetor, int tamanho, long long *comparacoes, long long *movimentacoes);
int particionar_quick_sort(int *vetor, int inferior, int superior, long long *comparacoes, long long *movimentacoes);
void quick_sort(int *vetor, int inferior, int superior, long long *comparacoes, long long *movimentacoes);
void merge_sort(int *vetor, int inf, int sup, long long *comparacoes, long long *movimentacoes);
void merge_buffer(int *vetor, int inf, int mid, int sup, long long *comparacoes, long long *movimentacoes, int *buffer);
void merge_recursivo(int *vetor, int inf, int sup, long long *comparacoes, long long *movimentacoes, int *buffer);
void selection_sort(int *vetor, int tamanho, long long*comparacoes, long long *movimentacoes);
void contagem_de_menores(int *vetor, int tamanho, long long *comparacoes, long long *movimentacoes);
int knuth(int tamanho, int *incrementos);
void shell_sort(int *vetor, int tamanho, int *incrementos, int qtdIncrementos, long long *comparacoes, long long *movimentacoes);
int get_max(int *vetor, int n, long long *comparacoes);
void counting_sort(int *vetor, int n, int exp, long long *movimentacoes, int *saida);
void radix_sort(int *vetor, int n, long long *comparacoes, long long *movimentacoes);
void rearranjar_heap(int *vetor, int i, int tamanhoHeap, long long *comparacoes, long long *movimentacoes);
void construir_heap(int *vetor, int n, long long *comparacoes, long long *movimentacoes);
void heap_sort(int *vetor, int n, long long *comparacoes, long long *movimentacoes);

typedef struct resultado_ {
    long long comparacoes;
    long long movimentacoes;
    double tempoExecucao;
}RESULTADO;

int main(){
    //leitura do tamanho do vetor
    int tamanho;
    printf("Digite quantos elementos você quer que o vetor tenha:\n");
    printf("1.100\n");
    printf("2.1000\n");
    printf("3.10000\n");
    printf("4.100000\n");
    printf("Sua escolha: ");
    scanf("%d", &tamanho);
    printf("\n");
    while (tamanho < 1 || tamanho > 4){
        printf("Selecione uma opção válida (1 a 4)\n");
        scanf("%d", &tamanho);
    }
    printf("\n");

    int n;
    switch (tamanho){
        case 1: n = 100; break;
        case 2: n = 1000; break;
        case 3: n = 10000; break;
        case 4: n = 100000; break;
    }   

    // Seleção do algoritimo de ordenação
    int algoritimo;
    printf("Selecione o método de ordenação:\n");
    printf("1.Bubble-Sort\n");
    printf("2.Selection-Sort\n");
    printf("3.Insertion-Sort\n");
    printf("4.Shell-Sort\n");
    printf("5.Quick-Sort\n");
    printf("6.Heap-Sort\n");
    printf("7.Merge-Sort\n");
    printf("8.Contagem dos Menores\n");
    printf("9.Radix-Sort\n");
    printf("Sua escolha: ");
    scanf("%d", &algoritimo);
    printf("\n");

    // Seleção da estrutura dos elementos no vetor
    int ordem;
    printf("Selecione o modelo dos registros no vetor:\n");
    printf("1.Elementos ordenados\n");
    printf("2.Elementos inversamente ordenados\n");
    printf("3.Elementos em ordem aleatória\n");
    printf("Sua escolha: ");
    scanf("%d", &ordem);
    printf("\n");

    // Defnição da seed do srand()
    srand(time(NULL));

    // Definição da quantidade de vezes que o algorítimo será executado
    int execucoes = 0;
    if (ordem == 1 || ordem == 2){
        execucoes = 1;
    }
    if (ordem == 3){
        execucoes = 5;
    }

    // Alocando memória para o vetor
    int *vetor = (int*)malloc(sizeof(int)*n);
    if (vetor == NULL){
        printf("Erro ao alocar memória para o vetor\n");
        return 1;
    }

    // Inicialização das variáveis contadoras para o caso de arrays de elementos aleatórios
    long long totalComparacoes = 0;
    long long totalMovimentacoes = 0;
    double totalTempo = 0;

    for (int i = 0; i < execucoes; i++){

        // Preenchimento do vetor
        switch (ordem)
        {
            case 1: //gera um vetor de elementos ordenados
            {
                for (int j = 0; j <  n; j++)
                {
                    vetor[j] = j + 1;
                }
                break;
            }
            case 2: //gera um vetor de elementos ordenados inversamente
            {
                for (int j = 0; j < n; j++)
                {
                    vetor[j] = n - j;   
                }
                break;
            }
            case 3: //gera um vetor de elementos aleatórios
            {
                for (int j = 0; j < n; j++)
                {
                    vetor[j] = rand() % n; //aleatoriza os elemetos com base na seed
                }
                break;
            }
            default:
            {
                printf("Modelo invalido!");
                return 1;
            }
        }

        // Incializando o resultado
        RESULTADO res;
        res.comparacoes = 0;
        res.movimentacoes = 0;
        res.tempoExecucao = 0;

        clock_t inicio, fim;
        inicio = clock();

        switch(algoritimo)        
        {
            case 1: 
            {
                bubble_sort(vetor, n, &res.comparacoes, &res.movimentacoes);
                break;
            }
            case 2:
            {
                selection_sort(vetor, n, &res.comparacoes, &res.movimentacoes);
                break;
            }
            case 3:
            {
                insertion_sort(vetor, n, &res.comparacoes, &res.movimentacoes);
                break;
            }
            case 4:
            {
                int incrementos[50];//vetor que armazena os valores da sequencia de knuth (nunca vai passar de 50)
                int qtdIncrementos = knuth(n, incrementos);
                shell_sort(vetor, n, incrementos, qtdIncrementos, &res.comparacoes, &res.movimentacoes);
                break;
            }
            case 5:
            {
                if (n > 0){
                    quick_sort(vetor, 0, n-1, &res.comparacoes, &res.movimentacoes);
                }
                break;
            }
            case 6:
            {
                heap_sort(vetor, n, &res.comparacoes, &res.movimentacoes);
                break;
            }
            case 7:
            {
                merge_sort(vetor, 0, n-1, &res.comparacoes, &res.movimentacoes);
                break;
            }
            case 8:
            {
                if (ordem == 3){
                    printf("O Algoritmo 'Contagem dos Menores' não suporta vetores com elementos duplicados (caso aleatório).\n");
                    res.comparacoes = 0;
                    res.movimentacoes = 0;
                } else {
                    contagem_de_menores(vetor, n, &res.comparacoes, &res.movimentacoes);
                }
                break;
            }
            case 9:
            {
                radix_sort(vetor, n, &res.comparacoes, &res.movimentacoes);
                break;
            }
            default:
            {
                printf("Escolha do algoritimo inválida\n");
                return 0;
            }
        }

        fim = clock();
        res.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        // Somando nos acumuladores do caso aleatório
        totalComparacoes += res.comparacoes;
        totalMovimentacoes += res.movimentacoes;
        totalTempo += res.tempoExecucao;

        if (ordem == 1 || ordem == 2){
            printf("Resultado Final:\n");
        }else{
            printf("Resultado da Execução %d:\n", i+1);
        }
        printf("Comparações de Chaves: %lld\n", res.comparacoes);
        printf("Movimentações de Registro: %lld\n", res.movimentacoes);
        printf("Tempo de execução: %.6f segundos\n", res.tempoExecucao);
    }

    if (ordem == 3){
        printf ("\n\n");
        printf("Resultado Final (Média de %d execuções):\n", execucoes);
        printf("Comparações de Chaves: %lld\n", totalComparacoes / execucoes);
        printf("Movimentações de Registro: %lld\n", totalMovimentacoes / execucoes);
        printf("Tempo de execução: %.6f segundos\n", totalTempo / execucoes);
    }

    free(vetor);
    return 0;
}

// Função auxiliar para trocar dois elementos
void troca(int  *a, int *b, long long *movimentacoes){
    int temp = *a;
    *a = *b;
    *b = temp;

    *movimentacoes += 2;
}

// Função axuliar para encontrar o maior elemento no vetor
int get_max(int *vetor, int n, long long *comparacoes){
    if (n <= 0){
        return 0;
    }
    
    int max = vetor[0];
    for (int i = 1; i < n; i++){
        (*comparacoes) += 1;
        if (vetor[i] > max){
            max = vetor[i];
        }
    }
    return max;
}

// Função do algoritimo bubble-sort
void bubble_sort (int *vetor, int tamanho, long long *comparacoes, long long *movimentacoes)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if(vetor[j] > vetor[j + 1])
            {
                troca(&vetor[j], &vetor[j + 1], movimentacoes);
            }
            *comparacoes += 1;  
        }
    }

    return;
}

// Função do algoritimo Insertion-sort
void insertion_sort(int *vetor, int tamanho, long long *comparacoes, long long *movimentacoes){
    // Percorrer o array não ordenado
    for (int i = 1; i < tamanho; i++){
        int elemento = vetor[i];
        int j;

        // Abrindo espaço para inserção no vetor ordenado (mover os elementos "maiores")
        for (j = i - 1; j >= 0; j--){
            *comparacoes += 1;
            if (vetor[j] > elemento){
                vetor[j + 1] = vetor[j];
                (*movimentacoes)++;
            } else {
                break; // Encontrou a posição
            }
        }
        vetor[j + 1] = elemento;
        (*movimentacoes)++;
    }
    return;
}

// Função de partição do algoritimo quick-sort
int particionar_quick_sort(int *vetor, int inferior, int superior, long long *comparacoes, long long *movimentacoes){

    //Escolha do pivô pela mediana de 3
    int meio = inferior + (superior - inferior) / 2;

    // Logica para ordenar o inferior, superior e meio para encontrar a mediana
    if (vetor[meio] < vetor[inferior]){
        troca(&vetor[inferior], &vetor[meio], movimentacoes);
        *comparacoes += 1;
    }
    if (vetor[superior] < vetor[inferior]){
        troca(&vetor[inferior], &vetor[superior], movimentacoes);
        *comparacoes += 1;
    }
    if (vetor[meio] > vetor[superior]){
        troca(&vetor[meio], &vetor[superior], movimentacoes);
        *comparacoes += 1;
    }

    troca(&vetor[meio], &vetor[superior], movimentacoes);

    // Atribuir a mediana no pivo
    int pivo = vetor[superior];

    int i = (inferior - 1);
    for (int j = inferior; j <= superior - 1; j++){
        // Se o elemento atual for menor ou igual ao pivô incrementa o índice do menor elemento
        (*comparacoes) += 1;
        if (vetor[j] <= pivo){
            i++;
            troca(&vetor[i], &vetor[j], movimentacoes);
        }
    }
    // Coloca o pivô na posição correta
    troca(&vetor[i + 1], &vetor[superior],movimentacoes);

    // Retorna o índice onde a partição foi feita
    return (i + 1);
}

// Função principal do algoritimo quick-sort
void quick_sort(int *vetor, int inferior, int superior, long long *comparacoes, long long *movimentacoes){
    if (inferior < superior){
        // Encontrando o indice correto do pivô
        int indice_pivo = particionar_quick_sort(vetor, inferior, superior, comparacoes, movimentacoes);

        // Ordenando recursivamente os elementos antes e depois da partição
        quick_sort(vetor, inferior, indice_pivo - 1, comparacoes, movimentacoes);
        quick_sort(vetor, indice_pivo + 1, superior, comparacoes, movimentacoes);
    }
}

//Função principal do mergesort
void merge_sort(int *vetor, int inf, int sup, long long *comparacoes, long long *movimentacoes){
    int tamanho = sup + 1; // n = (n-1) + 1
    if (tamanho <= 1){
        return;
    }    

    // Aloca o buffer
    int *buffer = (int*)malloc(tamanho * sizeof(int));
    if (buffer == NULL){
        printf("Erro de alocação no buffer do merge_sort\n");
        return;
    }

    // Chama a função recursiva
    merge_recursivo(vetor, inf, sup, comparacoes, movimentacoes, buffer);

    // Libera o buffer
    free(buffer);
}

void merge_recursivo(int *vetor, int inf, int sup, long long *comparacoes, long long *movimentacoes, int *buffer){
    if (inf < sup){
        int mid = inf + (sup - inf) / 2;
        merge_recursivo(vetor, inf, mid, comparacoes, movimentacoes, buffer);
        merge_recursivo(vetor, mid + 1, sup, comparacoes, movimentacoes, buffer);
        merge_buffer(vetor, inf, mid, sup, comparacoes, movimentacoes, buffer); 
    }
}

// Funcao auxiliar para o mergesort, junta 2 arrays
void merge_buffer(int *vetor, int inf, int mid, int sup, long long *comparacoes, long long *movimentacoes, int *buffer)
{
    // Copia os elementos para o buffer
    for (int i = inf; i <= mid; i++) {
        buffer[i] = vetor[i];
    }
    for (int j = mid + 1; j <= sup; j++) {
        buffer[j] = vetor[j];
    }

    // Faz o merge de volta para o 'vetor' principal
    int i = inf;
    int j = mid + 1;
    int k = inf;

    while (i <= mid && j <= sup)
    {
        (*comparacoes)++;
        if(buffer[i] <= buffer[j])
        {
            vetor[k] = buffer[i];
            i++;
        }
        else
        {
            vetor[k] = buffer[j];
            j++;
        }
        (*movimentacoes)++;
        k++;
    }

    //Copia o restante (se houver)
    while (i <= mid){
        vetor[k] = buffer[i];
        i++;
        k++;
        (*movimentacoes)++; 
    }

    while (j <= sup){
        vetor[k] = buffer[j];
        j++;
        k++;
        (*movimentacoes)++;
    }
}

//função do algoritmo selectionsort
void selection_sort(int *vetor, int tamanho, long long*comparacoes, long long *movimentacoes)
{
    int minimo; //indice do menor valor da parte nao ordenada do vetor
    for (int i = 0; i < (tamanho-1); i++)
    {
        minimo = i;
        for (int j = (i+1); j < tamanho; j++)
        {
            (*comparacoes)++;
            if (vetor[j] < vetor[minimo]) //vai procurando o menor valor do vetor nao ordenado
            {
                minimo = j;
            }    
        }
        if (i != minimo)
        {
            troca(&vetor[i], &vetor[minimo], movimentacoes); //vai colocando o menor valor no inicio do vetor
        }
    }
}

//função do algoritmo ordenaçao por contagem de menores
//este algoritmo nao funciona se tiver elementos repetidos no vetor a ser ordenado
void contagem_de_menores(int *vetor, int tamanho, long long *comparacoes, long long *movimentacoes)
{
    int *contagem = (int *)malloc(tamanho *sizeof(int)); 
    int *vetorFinal = (int*)malloc(tamanho *sizeof(int));
    if (contagem == NULL || vetorFinal == NULL) {
        printf("Erro de alocação no contagem_de_menores\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        contagem[i] = 0;
    }
    
    // Conta quantos elementos menores
    for (int i = 1; i < tamanho; i++)
    {
        for (int j = i-1; j >= 0; j--)
        {
            (*comparacoes)++;
            if (vetor[i] < vetor[j]) {
                contagem[j]++;
            } else {
                contagem[i]++;
            }
        } 
    }
    
    // Organiza os elementos no vetor final (buffer)
    for (int i = 0; i < tamanho; i++)
    {
        vetorFinal[contagem[i]] = vetor[i];
    }
    
    // Copia o vetor final (buffer) para o original
    for (int i = 0; i < tamanho; i++) 
    {
        vetor[i] = vetorFinal[i];
        (*movimentacoes) += 1;
    }
    
    free (contagem);
    free (vetorFinal);
}

//função para calcular a sequencia de incrementos do shell sort baseado na sequencia de knuth, vai retornar o tamanho do vetor de incrementos
int knuth(int tamanho, int *incrementos) //tamanho é o tamanho do vetor a ser ordenado, sempre busco que o valor maximo de knuth seja menor que a metade do vetor a se ordenar
{    
    int h = 1;
    int qtdIncrementos = 0;//conta o tamanho do vetor de incrementos
    while (h < tamanho/2)
    {
        qtdIncrementos++;
        h = 3 * h + 1;
    }
    for (int i = 0; i < qtdIncrementos; i++) //calcula o valor dos incrementos e bota no vetor
    {
        h = (h - 1) / 3; //vamos colocando na ordem inversa, a partir do valor de h do ultimo loop
        incrementos[i] = h;
    }
    return qtdIncrementos;
}

//função principal para o shell sort
void shell_sort(int *vetor, int tamanho, int *incrementos, int qtdIncrementos, long long *comparacoes, long long *movimentacoes)
{
    int h, aux, j;
    for (int posIncremento = 0; posIncremento < qtdIncrementos; posIncremento++)
    {
        h = incrementos[posIncremento];
        for (int i = h; i < tamanho; i++)
        {
            aux = vetor[i];
            for (j = i - h; j >= 0; j -= h) 
            {
                (*comparacoes)++;
                if (vetor[j] > aux)
                {
                    vetor[j + h] = vetor[j];
                    (*movimentacoes)++;
                }
                else
                {
                    break;
                }
            }
            vetor[j + h] = aux;
            (*movimentacoes)++;
        }
    }
}

// Função auxiliar para fazer a ordenação estável de elementos com base em um dígito
void counting_sort(int *vetor, int n, int exp, long long *movimentacoes, int *saida){
    int count[10] = {0};

    // Contando ocorrências do dígito
    for (int i = 0; i < n; i++){
        count[(vetor[i] / exp) % 10] += 1;
    }

    // Calculando as posições
    for (int i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    // Construindo o vetor 'saida' (buffer)
    for (int i = n - 1; i >= 0; i--){
        saida[count[(vetor[i]/exp) % 10] - 1] = vetor[i];
        count[(vetor[i] / exp) % 10] -= 1;
    }

    // Copiando o vetor 'saida' para o original
    for (int i = 0; i < n; i++){
        vetor[i] = saida[i];
        (*movimentacoes) += 1;
    }
}

// Função principal para a ordenação por raizes (radix-sort)
void radix_sort(int *vetor, int n, long long *comparacoes, long long *movimentacoes){
    if (n <= 1){
        return;
    }

    // Aloca o buffer de saída
    int *saida = (int*)malloc(n * sizeof(int));
    if (saida == NULL) {
        printf("Erro de alocação no radix_sort\n");
        return;
    }

    // Encontrando o máximo
    int max = get_max(vetor, n, comparacoes);

    // Fazendo o counting sort para cada dígito
    for (int exp = 1; max / exp > 0; exp *= 10){
        // Passa o buffer pré-alocado para a função
        counting_sort(vetor, n, exp, movimentacoes, saida);
    }
    
    // Libera o buffer
    free(saida);
}

void rearranjar_heap(int *vetor, int i, int tamanhoHeap, long long *comparacoes, long long *movimentacoes){
    int esquerda, direita, maior, aux;
    maior = i;
    esquerda = 2*i + 1;
    direita = 2*i + 2;

    if (esquerda < tamanhoHeap) {
        (*comparacoes) += 1;
        if (vetor[esquerda] > vetor[maior]) {
            maior = esquerda;
        }
    }

    if (direita < tamanhoHeap) {
        (*comparacoes) += 1;
        if (vetor[direita] > vetor[maior]) {
            maior = direita;
        }
    }

    if (maior != i) {
        troca(&vetor[i], &vetor[maior], movimentacoes);

        // Chama recursivamente para a subárvore afetada
        rearranjar_heap(vetor, maior, tamanhoHeap, comparacoes, movimentacoes);
    }
}

void construir_heap(int *vetor, int n, long long *comparacoes, long long *movimentacoes){
    for (int i = n/2-1; i >= 0; i--){
        rearranjar_heap(vetor, i, n, comparacoes, movimentacoes);
    }
}

void heap_sort(int *vetor, int n, long long *comparacoes, long long *movimentacoes){
    int aux, tamanhoHeap;

    // Se o vetor tem 1 ou 0 elementos ele está ordenado
    if (n <= 1){
        return;
    }

    // Construção do heap máximo com todo o vetor
    construir_heap(vetor, n, comparacoes, movimentacoes);

    // Extração sucessiva do maior elemento e reconstrução do heap
    tamanhoHeap = n;
    for (int i = n-1; i > 0; i--){
        // Troca a raíz (maior elemento) com o último elemento do heap atual
        troca(&vetor[0], &vetor[i], movimentacoes);

        // Redução do tamanho do heap para manter os elementos já ordenados
        tamanhoHeap -= 1;

        // Restauração do heap máximo na raíz da árvore reduzida
        rearranjar_heap(vetor, 0, tamanhoHeap, comparacoes, movimentacoes);
    }
}
