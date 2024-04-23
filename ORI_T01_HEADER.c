/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T01_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */


/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */


/* Funções auxiliares para o qsort.
 * Com uma pequena alteração, é possível utilizá-las no bsearch, assim, evitando código duplicado.
 * */

/* Função de comparação entre chaves do índice corredores_idx */
int qsort_corredores_idx(const void *a, const void *b) {
    return strcmp( ( (corredores_index *)a )->id_corredor, ( (corredores_index *)b )->id_corredor);
}

/* Função de comparação entre chaves do índice veiculos_idx */
int qsort_veiculos_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	/* segundo a documentação da função qsort e bsearch, a função de comparação deve retornar:
		- <0 se a<b; 
		- >0 se a>b; 
		- 0 se a=b.
		por isso, utilizar o strcmp (para char[] ou int) foi a melhor solução.
	*/
	return strcmp( ( (veiculos_index *)a)->id_veiculo, ( (veiculos_index *)b)->id_veiculo);
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_veiculos_idx()");
}

/* Função de comparação entre chaves do índice pistas_idx */
int qsort_pistas_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp( ((pistas_index *)a)->id_pista, ((pistas_index *)b)->id_pista );
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_pistas_idx()");
}

/* Função de comparação entre chaves do índice corridas_idx */
int qsort_corridas_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((corridas_index *)a)->id_pista, ((corridas_index *)b)->id_pista);
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_corridas_idx()");
}

/* Funções de comparação apenas entre data de ocorrencia do índice corridas_idx */
int qsort_data_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((corridas_index *)a)->ocorrencia, ((corridas_index *)b)->ocorrencia);
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_data_idx()");
}

/* Função de comparação entre chaves do índice nome_pista_idx */
int qsort_nome_pista_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((nome_pista_index *)a)->id_pista, ((nome_pista_index *)b)->id_pista);
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_nome_pista_idx()");
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int qsort_preco_veiculo_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((preco_veiculo_index *)a)->id_veiculo, ((preco_veiculo_index *)b)->id_veiculo);
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_preco_veiculo_idx()");
}

/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
int qsort_corredor_veiculos_secundario_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((corredor_veiculos_secundario_index *)a)->chave_secundaria, ((corredor_veiculos_secundario_index *)b)->chave_secundaria);
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_corredor_veiculos_secundario_idx()");
}

/* Cria o índice respectivo */
void criar_corredores_idx() {
    if (!corredores_idx) // aloca espaço se o ponteiro pro vetor de corredores estiver nulo
        corredores_idx = malloc(MAX_REGISTROS * sizeof(corredores_index));
 
    if (!corredores_idx) { // se o ponteiro seguir nulo, indica erro e fecha prog
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_corredores; ++i) { // percorre corredores já existentes no arquivo de dados e preenche o arquivo de indices com base neles
        Corredor c = recuperar_registro_corredor(i);
 
        if (strncmp(c.id_corredor, "*|", 2) == 0)
            corredores_idx[i].rrn = -1; // registro excluído
        else
            corredores_idx[i].rrn = i;
 
        strcpy(corredores_idx[i].id_corredor, c.id_corredor);
    }
 
    qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx); // mantém uma ordenação dos índices
    printf(INDICE_CRIADO, "corredores_idx");
}

void criar_veiculos_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!veiculos_idx)
		veiculos_idx = malloc(MAX_REGISTROS * sizeof(veiculos_index));

	if (!veiculos_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_veiculos; ++i) {
		Veiculo v = recuperar_registro_veiculo(i);

		if (strncmp(v.id_veiculo, "*|", 2) == 0)
			veiculos_idx[i].rrn = -1;
		else 
			veiculos_idx[i].rrn = i;
		
		strcpy(veiculos_idx[i].id_veiculo, v.id_veiculo);
	}

	qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
	printf(INDICE_CRIADO, "veiculos_idx");

	// printf(ERRO_NAO_IMPLEMENTADO, "criar_veiculos_idx()");
}

void criar_pistas_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!pistas_idx)
		pistas_idx = malloc(MAX_REGISTROS * sizeof(pistas_index));
	
	if (!pistas_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_pistas; ++i) {
		Pista p = recuperar_registro_pista(i);

		if (strncmp(p.id_pista, "*|", 2) == 0 ) 
			pistas_idx[i].rrn = -1;
		else 	
			pistas_idx[i].rrn = i;
		
		strcpy(pistas_idx[i].id_pista, p.id_pista);
	}

	qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
	printf(INDICE_CRIADO, "pistas_idx");

	// printf(ERRO_NAO_IMPLEMENTADO, "criar_pistas_idx()");
}

void criar_corridas_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_corridas_idx()");
}

void criar_nome_pista_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_nome_pista_idx()");
}

void criar_preco_veiculo_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_preco_veiculo_idx()");
}

void criar_corredor_veiculos_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_corredor_veiculos_idx()");
}

/* Exibe um registro com base no RRN */
bool exibir_corredor(int rrn) {
    if (rrn < 0)
        return false;
 
    Corredor c = recuperar_registro_corredor(rrn);
 
    printf("%s, %s, %s, %s, %.2lf\n", c.id_corredor, c.nome, c.apelido, c.cadastro, c.saldo);
    return true;
}

bool exibir_veiculo(int rrn) {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_veiculo()");
	
	return false;
}

bool exibir_pista(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_pista()");
	
	return false;
}

bool exibir_corrida(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_corrida()");
	
	return false;
}

/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs */
Corredor recuperar_registro_corredor(int rrn) {
	Corredor c;
	char temp[TAM_REGISTRO_CORREDOR + 1], *p;
	strncpy(temp, ARQUIVO_CORREDORES + (rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
	temp[TAM_REGISTRO_CORREDOR] = '\0';

	p = strtok(temp, ";");
	strcpy(c.id_corredor, p);
	p = strtok(NULL, ";");
	strcpy(c.nome, p);
	p = strtok(NULL, ";");
	strcpy(c.apelido, p);
	p = strtok(NULL, ";");
	strcpy(c.cadastro, p);
	p = strtok(NULL, ";");
	c.saldo = atof(p);
	p = strtok(NULL, ";");

	for(int i = 0; i < QTD_MAX_VEICULO; ++i)
		c.veiculos[i][0] = '\0'; 

	if(p[0] != '#') { // se campo veiculo (multi-valorado) não estiver vazio
		p = strtok(p, "|");

		for(int pos = 0; p; p = strtok(NULL, "|"), ++pos) // itera até strtok retornar NULL
			strcpy(c.veiculos[pos], p);
	}

	return c;
}

Veiculo recuperar_registro_veiculo(int rrn) {
	Veiculo v;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_VEICULO + 1], *p;
	strncpy(temp, ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), TAM_REGISTRO_VEICULO);
	temp[TAM_REGISTRO_VEICULO] = '\0';

	p = strtok(temp, ";");
	strcpy(v.id_veiculo, p);
	p = strtok(NULL, ";");
	strcpy(v.marca, p);
	p = strtok(NULL, ";");
	strcpy(v.modelo, p);
	p = strtok(NULL, ";");
	strcpy(v.poder, p);
	p = strtok(NULL, ";");
	v.velocidade = atoi(p);
	p = strtok(NULL, ";");
	v.aceleracao = atoi(p);
	p = strtok(NULL, ";");
	v.peso = atoi(p);
	p = strtok(NULL, ";");
	v.preco = atof(p);

	// printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_veiculo()");
	
	return v;
}

Pista recuperar_registro_pista(int rrn) {
	Pista p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/

	char temp[TAM_REGISTRO_PISTA + 1], *q;
	strncpy(temp, ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), TAM_REGISTRO_PISTA);
	temp[TAM_REGISTRO_PISTA] = '\0';

	q = strtok(temp, ";");
	strcpy(p.id_pista, q);
	q = strtok(NULL, ";");
	strcpy(p.nome, q);
	q = strtok(NULL, ";");
	p.dificuldade = atoi(q);
	q = strtok(NULL, ";");
	p.distancia = atoi(q);
	q = strtok(NULL, ";");
	p.recorde = atoi(q);

	// printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_pista()");

	return p;
}

Corrida recuperar_registro_corrida(int rrn) {
	Corrida c;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_corrida()");

	return c;
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_corredor(Corredor c, int rrn) {
	char temp[TAM_REGISTRO_CORREDOR + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	strcpy(temp, c.id_corredor);
	strcat(temp, ";");
	strcat(temp, c.nome);
	strcat(temp, ";");
	strcat(temp, c.apelido);
	strcat(temp, ";");
	strcat(temp, c.cadastro);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", c.saldo); // coloca o saldo formatado antes de concaternar ele
	strcat(temp, p);
	strcat(temp, ";");

	for(int i = 0, k = 0; i < QTD_MAX_VEICULO; ++i) {
		if(strlen(c.veiculos[i]) > 0) { // se tiver veículos comprados
			if (k == 0) // pra verificar se é o primeiro kart
				k = 1;
			else
				strcat(temp, "|");
			strcat(temp, c.veiculos[i]);
		}
	}
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_CORREDOR); // completa com # 

	strncpy(ARQUIVO_CORREDORES + rrn*TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR);
}

void escrever_registro_veiculo(Veiculo v, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_veiculo()");
}

void escrever_registro_pista(Pista p, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_pista()");
}

void escrever_registro_corrida(Corrida i, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_corrida()");
}

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(!busca_binaria(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0)) { // se não encontrar, realiza o cadastro
		if (qtd_registros_corredores < MAX_REGISTROS) { // se ainda não atingiu o número máximo de registros
			// adicionado no arquivo de dados	
			Corredor novo_corredor;
			strcpy(novo_corredor.id_corredor, id_corredor);
			strcpy(novo_corredor.nome, nome);
			strcpy(novo_corredor.apelido, apelido);
			current_date(novo_corredor.cadastro);
			novo_corredor.saldo = 0;
			novo_corredor.veiculos[0][0] = '\0'; // não sei se precisa deixar inicializado
			novo_corredor.veiculos[1][0] = '\0';
			novo_corredor.veiculos[2][0] = '\0';
			escrever_registro_corredor(novo_corredor, qtd_registros_corredores); 

			// adicionando no "arquivo"/estrutura de índice
			corredores_index novo_corredor_indice;
			strcpy(novo_corredor_indice.id_corredor, id_corredor);
			novo_corredor_indice.rrn = qtd_registros_corredores;
			corredores_idx[qtd_registros_corredores] = novo_corredor_indice;
			qtd_registros_corredores++; 
			qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

			printf(SUCESSO);
		}
		else 
			printf(ERRO_MEMORIA_INSUFICIENTE);
	}
	else 
		printf(ERRO_PK_REPETIDA);
	
	// printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_corredor_menu()");
}

void remover_corredor_menu(char *id_corredor) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "remover_corredor_menu()");
}

void adicionar_saldo_menu(char *id_corredor, double valor) {
	adicionar_saldo(id_corredor, valor, true);
}

void adicionar_saldo(char *id_corredor, double valor, bool flag){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	corredores_index *corredor_index = (corredores_index *) busca_binaria(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (corredor_index) { // se encontrar, realiza a adição de saldo
		if (valor > 0) {
			Corredor c;
			c = recuperar_registro_corredor(corredor_index->rrn);
			if (valor + c.saldo > 9999999999.99) 
				c.saldo = 9999999999.99;
			else 
				c.saldo += valor;

			escrever_registro_corredor(c, corredor_index->rrn);
			printf(SUCESSO);
		}
		else 
			printf(ERRO_VALOR_INVALIDO);
	}
	else 
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	// printf(ERRO_NAO_IMPLEMENTADO, "adicionar_saldo()");
}

void comprar_veiculo_menu(char *id_corredor, char *id_veiculo) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "comprar_veiculo_menu()");
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_veiculo_menu()");
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_pista_menu()");
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "executar_corrida_menu()");
}

/* Busca */
void buscar_corredor_id_menu(char *id_corredor) {
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(found->rrn);
}

void buscar_pista_id_menu(char *id_pista) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "buscar_pista_id_menu()");
}

void buscar_pista_nome_menu(char *nome_pista) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "buscar_pista_nome_menu()");
}

/* Listagem */
void listar_corredores_id_menu() {
	if (qtd_registros_corredores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_corredores; i++)
			exibir_corredor(corredores_idx[i].rrn);
}

void listar_corredores_modelo_menu(char *modelo){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_corredores_modelo_menu()");
}

void listar_veiculos_compra_menu(char *id_corredor) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_veiculos_compra_menu()");
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_corridas_periodo_menu()");
}

/* Liberar espaço */
void liberar_espaco_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "liberar_espaco_menu()");
}

/* Imprimir arquivos de dados */
void imprimir_arquivo_corredores_menu() {
	if (qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDORES);
}

void imprimir_arquivo_veiculos_menu() {
	if (qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_VEICULOS);
}

void imprimir_arquivo_pistas_menu() {
	if (qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PISTAS);
}

void imprimir_arquivo_corridas_menu() {
	if (qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORRIDAS);
}

/* Imprimir índices primários */
void imprimir_corredores_idx_menu() {
	if (corredores_idx == NULL || qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corredores; ++i)
			printf("%s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn);
}

void imprimir_veiculos_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_veiculos_idx_menu()");
}

void imprimir_pistas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_pistas_idx_menu()");
}

void imprimir_corridas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_corridas_idx_menu()");
}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_nome_pista_idx_menu()");
}

void imprimir_preco_veiculo_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_preco_veiculo_idx_menu()");
}

void imprimir_corredor_veiculos_secundario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_corredor_veiculos_secundario_idx_menu()");
}

void imprimir_corredor_veiculos_primario_idx_menu(){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_corredor_veiculos_primario_idx_menu()");
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "liberar_memoria_menu()");
}

void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_insert()");
}

bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_secondary_search()");
	return false;
}

int inverted_list_primary_search(char result[][TAM_ID_CORREDOR], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_primary_search()");
	return -1;
}


void* busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/	
	int imin = 0, imax = nmemb-1, imid, cmp; 
	void *elemento;
	// void *base = base0;

	if(exibir_caminho){
		printf(REGS_PERCORRIDOS);
	}
	while(imin <= imax){
		if ((imax+1)%2 == 0) // número de elementos no intervalo é par
			imid = ((imin + imax)/2) + 1; // sempre escolher o mais a direita
		else // número de elementos no intervalo é ímpar
			imid = (imin + imax)/2; 
		
		if(exibir_caminho)
			printf(" %d", imid);

		elemento = base0 + (imid * size); // calculando o end do elemento com pase na posição relativa (imid) 
		cmp = (*compar)(key, elemento);  // comparando 
		if(cmp < 0) { // key < elemento
			imax = imid - 1;
		}
		else if(cmp > 0) { // key > elemento
			imin = imid + 1;
		}
		else { // key == elemento
			// percorrendo até o elemento mais a esquerda (primeiro da seq. de repetidos)
			while((*compar)(key, elemento - size) == 0) {
				elemento = elemento - size;
			}
			if(exibir_caminho)
				printf("\n");
			return elemento + posicao_caso_repetido * size; // retornando o elemento na posição informada relativa ao bloco de repetição 
		}
	}
	if(exibir_caminho)
		printf("\n");
	
	return NULL;
	
	// printf(ERRO_NAO_IMPLEMENTADO, "busca_binaria_com_reps()");
	// return (void*) -1;
}

void* busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}
char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}
char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}