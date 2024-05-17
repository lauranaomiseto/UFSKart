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
	int cmp_ocorrencia = strcmp(((corridas_index *)a)->ocorrencia, ((corridas_index *)b)->ocorrencia);
	if (!cmp_ocorrencia) // se as ocorrências das corridas forem iguais, a ordem é dada pelo id_pista
		return strcmp(((corridas_index *)a)->id_pista, ((corridas_index *)b)->id_pista);
	// se as ocorrências forem diferentes, elas têm prioridade na ordenação
	return cmp_ocorrencia;
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
	return strcmp(strupr(((nome_pista_index *)a)->nome), strupr(((nome_pista_index *)b)->nome));
	// printf(ERRO_NAO_IMPLEMENTADO, "qsort_nome_pista_idx()");
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int qsort_preco_veiculo_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (((preco_veiculo_index *)a)->preco < ((preco_veiculo_index *)b)->preco)
		return -1;
	else if (((preco_veiculo_index *)a)->preco > ((preco_veiculo_index *)b)->preco)
		return 1;
	else // a = b
		return 0;
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
		pistas_idx[i].rrn = i;
		strcpy(pistas_idx[i].id_pista, p.id_pista);
	}

	qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
	printf(INDICE_CRIADO, "pistas_idx");

	// printf(ERRO_NAO_IMPLEMENTADO, "criar_pistas_idx()");
}

void criar_corridas_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!corridas_idx)
		corridas_idx = malloc(MAX_REGISTROS * sizeof(corridas_index));

	if (!corridas_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_corridas; ++i) {
		Corrida c = recuperar_registro_corrida(i);
		corridas_idx[i].rrn = i;
		strcpy(corridas_idx[i].id_pista, c.id_pista);
		strcpy(corridas_idx[i].ocorrencia, c.ocorrencia);
	}

	qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);
	printf(INDICE_CRIADO, "corridas_idx");

	// printf(ERRO_NAO_IMPLEMENTADO, "criar_corridas_idx()");
}

void criar_nome_pista_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!nome_pista_idx)
		nome_pista_idx = malloc(MAX_REGISTROS * sizeof(nome_pista_index));
	
	if(!nome_pista_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_pistas; ++i) {
		Pista p = recuperar_registro_pista(i);
		// considerando que não há operação de remoção de pistas, não é necessário testar a integridade do id_pista recuperado;
		// como a chave nome é um campo de tam. variável no arquivo de dados das pistas, ela deve ser truncada caso exceda o tam. max do campo no arquivo de índice. além disso, precisa ser transformada em um formato canônico
		strncpy(nome_pista_idx[i].nome, strupr(p.nome), TAM_CHAVE_NOME_PISTA_IDX);
		strcpy(nome_pista_idx[i].id_pista, p.id_pista);
	}

	qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
	printf(INDICE_CRIADO, "nome_pista_idx");

	// printf(ERRO_NAO_IMPLEMENTADO, "criar_nome_pista_idx()");
}

void criar_preco_veiculo_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!preco_veiculo_idx) 
		preco_veiculo_idx = malloc(MAX_REGISTROS * sizeof(preco_veiculo_index));

	if (!preco_veiculo_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_veiculos; ++i) {
		Veiculo v = recuperar_registro_veiculo(i);
		// considerando que não há operação de remoção de veículos, não é necessário testar a integridade do id_veiculo recuperado
		// como a chave preco tem tamanho fixo no arquivo de dados dos veiculos, não é necessário truncá-lo. além disso, por ser numérico, já é canônico também.
		preco_veiculo_idx[i].preco = v.preco;
		strcpy(preco_veiculo_idx[i].id_veiculo, v.id_veiculo);
	}

	qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
	printf(INDICE_CRIADO, "preco_veiculo_idx");

	// printf(ERRO_NAO_IMPLEMENTADO, "criar_preco_veiculo_idx()");
}

void criar_corredor_veiculos_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	// criando índice corredor veículos secundário que armazena o modelo do veículo e a referência ao primeiro dos corredores proprietários no índice corredor veículos primário
	if (!corredor_veiculos_idx.corredor_veiculos_secundario_idx)
		corredor_veiculos_idx.corredor_veiculos_secundario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_secundario_index));
	if (!corredor_veiculos_idx.corredor_veiculos_secundario_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	// criando índice corredor veículos primário que armazena o id do corredor e o índice do próximo corredor proprietário
	if (!corredor_veiculos_idx.corredor_veiculos_primario_idx)
		corredor_veiculos_idx.corredor_veiculos_primario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_primario_index));
	if (!corredor_veiculos_idx.corredor_veiculos_primario_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_corredores; ++i) { // percorre corredores já existentes  
        Corredor c = recuperar_registro_corredor(i);
        for (unsigned j = 0; j < QTD_MAX_VEICULO; ++j) { // percorre os veículos do corredor
			if (strlen(c.veiculos[j])) { // verifica se o corredor possui véiculos
				// verifica se o veículo já está listado no índice corredor veículos secundário
				corredor_veiculos_secundario_index index_modelo;
				// o modelo do veículo deve ser truncado caso exceda o tam. max do campo no índice e precisa estar no formato canônico
				strncpy(index_modelo.chave_secundaria, strupr(c.veiculos[j]), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
				corredor_veiculos_secundario_index *found_modelo = busca_binaria((void *)&index_modelo, corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, false, 0);
				
				if (!found_modelo) { // se o modelo ainda não estiver no índice corredor_veiculos_secundario_idx, adiciona o modelo nele
					corredor_veiculos_secundario_index novo_modelo;
					// como a chave (veículo/modelo) é um campo de tam. variável no arquivo de dados dos corredores, ela deve ser truncada caso exceda o tam. max do campo no arquivo de índice. além disso, precisa ser transformada em um formato canônico
					strncpy(novo_modelo.chave_secundaria, strupr(c.veiculos[j]), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
					novo_modelo.primeiro_indice = corredor_veiculos_idx.qtd_registros_primario;
					corredor_veiculos_idx.corredor_veiculos_secundario_idx[corredor_veiculos_idx.qtd_registros_secundario] = novo_modelo;
					corredor_veiculos_idx.qtd_registros_secundario++;

					// ordenar índice corredor_veiculos_secundario_idx
					qsort(corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx);
				}
				else { // se o modelo já estiver no índice corredor_veiculos_secundario_idx, percorre índice corredor_veiculos_primario_idx para atualização do campo próx. registro
					corredor_veiculos_primario_index *aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[found_modelo->primeiro_indice];
					while (aux->proximo_indice != -1) {
						aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[aux->proximo_indice];
					}
					aux->proximo_indice = corredor_veiculos_idx.qtd_registros_primario;
				}

				// adiciona o corredor/proprietario no índice corredor_veiculos_primario_idx
				corredor_veiculos_primario_index novo_proprietario;
				strcpy(novo_proprietario.chave_primaria, c.id_corredor);
				novo_proprietario.proximo_indice = -1;
				corredor_veiculos_idx.corredor_veiculos_primario_idx[corredor_veiculos_idx.qtd_registros_primario] = novo_proprietario;
				corredor_veiculos_idx.qtd_registros_primario++;
			}
		}
    }

	printf(INDICE_CRIADO, "corredor_veiculos_idx");
	// printf(ERRO_NAO_IMPLEMENTADO, "criar_corredor_veiculos_idx()");
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
	if (rrn < 0)
		return false;
	
	Veiculo v = recuperar_registro_veiculo(rrn);

	printf("%s, %s, %s, %s, %d, %d, %d, %.2lf\n", v.id_veiculo, v.marca, v.modelo, v.poder, v.velocidade, v.aceleracao, v.peso, v.preco);

	// printf(ERRO_NAO_IMPLEMENTADO, "exibir_veiculo()");
	return true;
}

bool exibir_pista(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;
	
	Pista p = recuperar_registro_pista(rrn);

	printf("%s, %s, %d, %d, %d\n", p.id_pista, p.nome, p.dificuldade, p.distancia, p.recorde);

	return true;
	// printf(ERRO_NAO_IMPLEMENTADO, "exibir_pista()");
}

bool exibir_corrida(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0) 
		return false;
	
	Corrida c = recuperar_registro_corrida(rrn);

	printf("%s, %s, %s, %s\n", c.id_pista, c.ocorrencia, c.id_corredores, c.id_veiculos);
	
	// printf(ERRO_NAO_IMPLEMENTADO, "exibir_corrida()");
	return true;
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
	char temp[TAM_REGISTRO_CORRIDA + 1];
	strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);

	strncpy(c.id_pista, temp, 8);
	c.id_pista[8] = '\0';
	strncpy(c.ocorrencia, temp + 8, 12);
	c.ocorrencia[12] = '\0';
	strncpy(c.id_corredores, temp + 8 + 12, 66);
	c.id_corredores[66] = '\0';
	strncpy(c.id_veiculos, temp + 8 + 12 + 66, 42);
	c.id_veiculos[42] = '\0';

	// printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_corrida()");

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
	char temp[TAM_REGISTRO_VEICULO + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	strcpy(temp, v.id_veiculo);
	strcat(temp, ";");
	strcat(temp, v.marca);
	strcat(temp, ";");
	strcat(temp, v.modelo);
	strcat(temp, ";");
	strcat(temp, v.poder);
	strcat(temp, ";");
	sprintf(p, "%04d", v.velocidade);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%04d", v.aceleracao);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%04d", v.peso);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", v.preco); 
	strcat(temp, p);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_VEICULO);

	strncpy(ARQUIVO_VEICULOS + rrn * TAM_REGISTRO_VEICULO, temp, TAM_REGISTRO_VEICULO);
	// printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_veiculo()");
}

void escrever_registro_pista(Pista p, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_PISTA + 1], q[100];
	temp[0] = '\0'; q[0] = '\0';

	strcpy(temp, p.id_pista);
	strcat(temp, ";");
	strcat(temp, p.nome);
	strcat(temp, ";");
	sprintf(q, "%04d;", p.dificuldade);
	strcat(temp, q);
	sprintf(q, "%04d;", p.distancia);
	strcat(temp, q);
	sprintf(q, "%04d;", p.recorde);
	strcat(temp, q);

	strpadright(temp, '#', TAM_REGISTRO_PISTA);

	strncpy(ARQUIVO_PISTAS + rrn * TAM_REGISTRO_PISTA, temp, TAM_REGISTRO_PISTA);
	// printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_pista()");
}

void escrever_registro_corrida(Corrida i, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_CORRIDA + 1];
	temp[0] = '\0';

	strcpy(temp, i.id_pista);
	strcat(temp, i.ocorrencia);
	strcat(temp, i.id_corredores);
	strcat(temp, i.id_veiculos);

	strncpy(ARQUIVO_CORRIDAS + rrn*TAM_REGISTRO_CORRIDA, temp, TAM_REGISTRO_CORRIDA);
	// printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_corrida()");
}

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	
	if (!found) { // se não encontrar, realiza o cadastro
		if (qtd_registros_corredores < MAX_REGISTROS) { // se ainda não atingiu o número máximo de registros
			// adicionado no arquivo de dados	
			Corredor novo_corredor;
			strcpy(novo_corredor.id_corredor, id_corredor);
			strcpy(novo_corredor.nome, nome);
			strcpy(novo_corredor.apelido, apelido);
			current_datetime(novo_corredor.cadastro);
			novo_corredor.saldo = 0;
			novo_corredor.veiculos[0][0] = '\0'; // não sei se precisa deixar inicializado
			novo_corredor.veiculos[1][0] = '\0';
			novo_corredor.veiculos[2][0] = '\0';
			escrever_registro_corredor(novo_corredor, qtd_registros_corredores); 

			// adicionando no "arquivo"/estrutura de índice
			corredores_index novo_corredor_index;
			strcpy(novo_corredor_index.id_corredor, id_corredor);
			novo_corredor_index.rrn = qtd_registros_corredores;
			corredores_idx[qtd_registros_corredores] = novo_corredor_index;
			qtd_registros_corredores++; 
			qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

			printf(SUCESSO);
		}
		else 
			printf(ERRO_MEMORIA_INSUFICIENTE);
	}
	else 
		printf(ERRO_PK_REPETIDA, id_corredor);
	
	// printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_corredor_menu()");
}

void remover_corredor_menu(char *id_corredor) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

	if (found) {
		// marcando registro como exluído no arquivo de dados		
		Corredor c;
		c = recuperar_registro_corredor(found->rrn);
		c.id_corredor[0] = '*';
		c.id_corredor[1] = '|';

		escrever_registro_corredor(c, found->rrn);

		// marcando registro como escluído no "arquivo"/estrutura de índice primário
		found->rrn = -1;

		printf(SUCESSO);
	}	
	else 
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);

	// printf(ERRO_NAO_IMPLEMENTADO, "remover_corredor_menu()");
}

void adicionar_saldo_menu(char *id_corredor, double valor) {
	adicionar_saldo(id_corredor, valor, true);
}

void adicionar_saldo(char *id_corredor, double valor, bool flag){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (found) { // se encontrar, realiza a adição de saldo
		if (valor > 0) {
			Corredor c;
			c = recuperar_registro_corredor(found->rrn);
			if (valor + c.saldo > 9999999999.99) 
				c.saldo = 9999999999.99;
			else 
				c.saldo += valor;

			escrever_registro_corredor(c, found->rrn);
			if (flag)
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
	corredores_index index_corredor; 
	strcpy(index_corredor.id_corredor, id_corredor);
	corredores_index *found_corredor = busca_binaria((void *)&index_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

	veiculos_index index_veiculo;
	strcpy(index_veiculo.id_veiculo, id_veiculo);
	veiculos_index *found_veiculo = busca_binaria((void *)&index_veiculo, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

	if (found_corredor && found_veiculo) { // se ambas as chaves forem válidas
		// printf("ambas as chaves são válidas\n");
		// checando se o veículo já não está vinculado com o corredor
		Corredor c = recuperar_registro_corredor(found_corredor->rrn);
		Veiculo v = recuperar_registro_veiculo(found_veiculo->rrn);
		int repetido = 0;

		for (unsigned i = 0; i < QTD_MAX_VEICULO; ++i) {
			// printf("veiculo modelo: %s\n", c.veiculos[i]);
			if (strcmp(c.veiculos[i], v.modelo) == 0) {
				repetido = 1;
				break;
			}
		}
		
		if (!repetido) { // se ainda não estiver vinculado
			// printf("veículo ainda não está vinculado ao corredor\n");
			if (c.saldo >= v.preco) { // se saldo for suficiente
				// printf("o saldo é suficiente\n");
				// o sistema garante que não haverá nenhuma tentativa de inserir mais que a quantidade max de veículos por corredor, então não foi feita nenhuma verificação para esse caso
				// printf("o saldo é suficiente\n");
				for (unsigned i = 0; i < QTD_MAX_VEICULO; ++i) {
					if (!strlen(c.veiculos[i])) {
						strcpy(c.veiculos[i], v.modelo);	
						break;
					}
				}
				c.saldo -= v.preco;
				// atualizando arquivo de dados
				escrever_registro_corredor(c, found_corredor->rrn);
				// printf("arquivo de dados atualizado\n");
				
				// atualizando arquivo de índice corredor_veiculo_idx (secundário e primário) 
				corredor_veiculos_secundario_index index_modelo;
				strncpy(index_modelo.chave_secundaria, strupr(v.modelo), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
				corredor_veiculos_secundario_index *found_modelo = busca_binaria((void *)&index_modelo, corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, false, 0);

				if (!found_modelo) { // se o modelo ainda não estiver no índice secundário
					// printf("modelo ainda não está no índice secundário\n");
					corredor_veiculos_secundario_index novo_modelo;
					strncpy(novo_modelo.chave_secundaria, strupr(v.modelo), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
					novo_modelo.primeiro_indice = corredor_veiculos_idx.qtd_registros_primario;
					corredor_veiculos_idx.corredor_veiculos_secundario_idx[corredor_veiculos_idx.qtd_registros_secundario] = novo_modelo;
					corredor_veiculos_idx.qtd_registros_secundario++;
					// printf("novo modelo adicionado no índice secundário\n");

					qsort(corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx);
					// printf("índice secundário ordenado\n");
				}
				else { // se o modelo já estiver no índice secundário
					// printf("modelo já está no índice secundário\n");
					corredor_veiculos_primario_index *aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[found_modelo->primeiro_indice];
					while (aux->proximo_indice != -1) {
						aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[aux->proximo_indice];
					}
					aux->proximo_indice = corredor_veiculos_idx.qtd_registros_primario;
				}
				// printf("adicionando novo proprietario\n");
				corredor_veiculos_primario_index novo_proprietario;
				strcpy(novo_proprietario.chave_primaria, c.id_corredor);
				novo_proprietario.proximo_indice = -1;
				corredor_veiculos_idx.corredor_veiculos_primario_idx[corredor_veiculos_idx.qtd_registros_primario] = novo_proprietario;
				corredor_veiculos_idx.qtd_registros_primario++;
				printf(SUCESSO);
			}
			else 
				printf(ERRO_SALDO_NAO_SUFICIENTE);
		}
		else 
			printf(ERRO_VEICULO_REPETIDO, c.id_corredor, v.id_veiculo);
	}
	else 
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	// printf(ERRO_NAO_IMPLEMENTADO, "comprar_veiculo_menu()");
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char id_veiculo[TAM_ID_VEICULO]; // TAM_ID_VEICULO já considera o byte final pro \0
	sprintf(id_veiculo, "%07d", qtd_registros_veiculos); // formatando o id_veiculo

	veiculos_index index;
	strcpy(index.id_veiculo, id_veiculo);
	veiculos_index *found = busca_binaria((void *)&index, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

	if (!found) {
		if (qtd_registros_veiculos < MAX_REGISTROS) {
			// adicionando no arquivo de dados
			Veiculo novo_veiculo;
			strcpy(novo_veiculo.id_veiculo, id_veiculo);
			strcpy(novo_veiculo.marca, marca);
			strcpy(novo_veiculo.modelo, modelo);
			strcpy(novo_veiculo.poder, poder);
			novo_veiculo.velocidade = velocidade;
			novo_veiculo.aceleracao = aceleracao;
			novo_veiculo.peso = peso;
			novo_veiculo.preco = preco;
			escrever_registro_veiculo(novo_veiculo, qtd_registros_veiculos);

			// adicionando no "arquivo"/estrutura de índice principal
			veiculos_index novo_veiculo_index;
			strcpy(novo_veiculo_index.id_veiculo, id_veiculo);
			novo_veiculo_index.rrn = qtd_registros_veiculos;
			veiculos_idx[qtd_registros_veiculos] = novo_veiculo_index;


			// adicionando no "arquivo"/estrutura de índice secundário (preco_veiculo_idx)
			preco_veiculo_index novo_preco_veiculo_index;
			novo_preco_veiculo_index.preco = preco;
			strcpy(novo_preco_veiculo_index.id_veiculo, id_veiculo);
			preco_veiculo_idx[qtd_registros_veiculos] = novo_preco_veiculo_index;

			// ordenação dos índices principal e secundário
			qtd_registros_veiculos++;
			qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
			qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
			printf(SUCESSO);
		}
		else 
			printf(ERRO_MEMORIA_INSUFICIENTE);
	}
	else 
		printf(ERRO_PK_REPETIDA, id_veiculo);

	// printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_veiculo_menu()");
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char id_pista[TAM_ID_PISTA]; // TAM_ID_PISTA já considera o byte final pro \0
	sprintf(id_pista, "%08d", qtd_registros_pistas); // formatando o id_pista

	// checando tentativa de cadastro com chave (nome) repetido
	nome_pista_index index;
	strcpy(index.nome, nome);
	nome_pista_index *found = busca_binaria((void *)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, false, 0);
	
	if (!found) { // se não encontrar pista com o nome informado, realiza o cadastro
		if (qtd_registros_pistas < MAX_REGISTROS) {
			// adicionando no arquivo de dados
			Pista nova_pista;
			strcpy(nova_pista.id_pista, id_pista);
			strcpy(nova_pista.nome, nome);
			if(!distancia)
				nova_pista.dificuldade = 1;
			else 
				nova_pista.dificuldade = dificuldade;
			nova_pista.distancia = distancia;
			nova_pista.recorde = recorde;
			escrever_registro_pista(nova_pista, qtd_registros_pistas);

			// adicionando no "arquivo"/estrutura de índice principal
			pistas_index nova_pista_index;
			strcpy(nova_pista_index.id_pista, id_pista);
			nova_pista_index.rrn = qtd_registros_pistas;
			pistas_idx[qtd_registros_pistas] = nova_pista_index;

			// adicionando no "arquivo"/estrutura de índice secundário (nome_pista_idx)
			nome_pista_index novo_nome_pista_index;
			strncpy(novo_nome_pista_index.nome, strupr(nome), TAM_CHAVE_NOME_PISTA_IDX);
			strcpy(novo_nome_pista_index.id_pista, id_pista);
			nome_pista_idx[qtd_registros_pistas] = novo_nome_pista_index;

			// ordenação dos arquivos de índices principal e secundário
			qtd_registros_pistas++;
			qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
			qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
			printf(SUCESSO);
		}
		else
			printf(ERRO_MEMORIA_INSUFICIENTE);
	}
	else 
		printf(ERRO_PK_REPETIDA, nome);

	// printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_pista_menu()");
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// verificando se a corrida já está castrada
	corridas_index index_corrida;
	strcpy(index_corrida.id_pista, id_pista);
	strcpy(index_corrida.ocorrencia, ocorrencia);
	corridas_index *found_corrida = busca_binaria((void *)&index_corrida, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx, false, 0);
	if (!found_corrida) { // se a corrida não estiver cadastrada
		// verificando se a pista é válida
		pistas_index index_pista;
		strcpy(index_pista.id_pista, id_pista);
		pistas_index *found_pista = busca_binaria((void *)&index_pista, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, false, 0);

		if (found_pista) { // se a pista for válida
			// verificando se o corredor e veículos são válidos
			corredores_index index_corredor, *found_corredor;
			veiculos_index index_veiculo, *found_veiculo;

			int verificacao = 0;

			for (unsigned i = 0; i < 6; ++i) {
				strncpy(index_corredor.id_corredor, id_corredores + i*11, 11);
				index_corredor.id_corredor[11] = '\0';
				found_corredor = busca_binaria((void *)&index_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

				strncpy(index_veiculo.id_veiculo, id_veiculos + i*7, 7);
				index_veiculo.id_veiculo[7] = '\0';
				found_veiculo = busca_binaria((void *)&index_veiculo, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

				if (found_corredor && found_veiculo) { // se o corredor e o veículo forem válidos
					// verificando se corredor é proprietário do veículo em questão
					// abordagens: i) recupearar o modelo do veículo e percorrer a lista invertida (linearmente) para checar se o modelo pertence ao corredor; e ii) recuperar o registro do corredor e do veículo para verificar se o modelo do veículo está no registro do corredor
					Corredor c = recuperar_registro_corredor(found_corredor->rrn);
					Veiculo v = recuperar_registro_veiculo(found_veiculo->rrn);

					int proprietario = 0; // flag auxiliar

					for (unsigned j = 0; j < QTD_MAX_VEICULO; ++j) { // percorrendo os veículos do corredor 
						// printf("[%s] [%s]\n", c.veiculos[j], v.modelo);
						if (strcmp(c.veiculos[j], v.modelo) == 0) {
							proprietario = 1;
							break;
						}
					}

					if (proprietario) 
						verificacao++;
					else 
						printf(ERRO_CORREDOR_VEICULO, c.id_corredor, v.id_veiculo);
				}
				else {
					printf(ERRO_REGISTRO_NAO_ENCONTRADO);
					break;
				}
			}

			// printf("verificação: %d\n", verificacao);
			if (verificacao == 6) { // se todos os 6 corredores forem válidos e proprietários dos 6 veículos válidos correspondentes
				 if (qtd_registros_corridas < MAX_REGISTROS) {
					// adicionando no arquivo de dados
					Corrida nova_corrida;
					strcpy(nova_corrida.id_pista, id_pista);
					strcpy(nova_corrida.ocorrencia, ocorrencia);
					strcpy(nova_corrida.id_corredores, id_corredores);
					strcpy(nova_corrida.id_veiculos, id_veiculos);
					escrever_registro_corrida(nova_corrida, qtd_registros_corridas);

					// adicionanod no "arquivo"/estrutura de íncide 
					corridas_index nova_corrida_index;
					strcpy(nova_corrida_index.id_pista, id_pista);
					strcpy(nova_corrida_index.ocorrencia, ocorrencia);
					nova_corrida_index.rrn = qtd_registros_corridas;
					corridas_idx[qtd_registros_corridas] = nova_corrida_index;

					// ordenação do arquivo de índice
					qtd_registros_corridas++;
					qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);

					// adicionando saldo/prêmio aos vecendores
					Pista p = recuperar_registro_pista(found_pista->rrn);
					int valor = 6 * TX_FIXA * p.dificuldade;

					char podio[3][TAM_ID_CORREDOR];
					strncpy(podio[0], id_corredores, 11);
					podio[0][11] = '\0';
					strncpy(podio[1], id_corredores+11, 11);
					podio[1][11] = '\0';
					strncpy(podio[2], id_corredores + 22, 11);
					podio[2][11] = '\0';

					adicionar_saldo(podio[0], valor*0.4, false);
					adicionar_saldo(podio[1], valor*0.3, false);
					adicionar_saldo(podio[2], valor*0.2, false);

					printf(SUCESSO);
				 }
				 else 
				 	printf(ERRO_MEMORIA_INSUFICIENTE);
			}
		}
		else 
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	}
	else {
		char temp[TAM_ID_PISTA + TAM_DATETIME];
		temp[0] = '\0';
		printf(ERRO_PK_REPETIDA, strcat(strcpy(temp, ocorrencia), id_pista));
	}
	// printf(ERRO_NAO_IMPLEMENTADO, "executar_corrida_menu()");
}

/* Busca */
void buscar_corredor_id_menu(char *id_corredor) {
	corredores_index index;
	strcpy(index.id_corredor, id_corredor); // para a função de comparação, os objetos devem ser do mesmo tipo (struct _index)
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0); // o cast no index é pra adaptar ao tipo do parâmetro mesmo
	if (found == NULL || found->rrn < 0) // se não encontrar ou estiver deletado
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(found->rrn);
}

void buscar_pista_id_menu(char *id_pista) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	pistas_index index;
	strcpy(index.id_pista, id_pista); 
	pistas_index *found = busca_binaria((void *)&index, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else 
		exibir_pista(found->rrn);
	// printf(ERRO_NAO_IMPLEMENTADO, "buscar_pista_id_menu()");
}

void buscar_pista_nome_menu(char *nome_pista) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// busca pelo nome no índice secundário nome_pista_idx
	nome_pista_index index_nome_pista;
	strcpy(index_nome_pista.nome, nome_pista);
	nome_pista_index *found_nome_pista = busca_binaria((void *)&index_nome_pista, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, true, 0);
	if(found_nome_pista) {
		// busca pelo id encontrado no índice primário pistas_idx
		pistas_index index_pista;
		strcpy(index_pista.id_pista, found_nome_pista->id_pista);
		pistas_index *found_pista = busca_binaria((void *)&index_pista, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);

		exibir_pista(found_pista->rrn);
	}
	else 
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);

	// printf(ERRO_NAO_IMPLEMENTADO, "buscar_pista_nome_menu()");
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
	corredor_veiculos_secundario_index index_modelo;
	strncpy(index_modelo.chave_secundaria, strupr(modelo), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
	corredor_veiculos_secundario_index *found_modelo = busca_binaria((void *)&index_modelo, corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, false, 0);

	if (found_modelo) {
		corredor_veiculos_primario_index *aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[found_modelo->primeiro_indice]; 

		// como o índice corredor_veiculos_primario_idx não é ordenado, é necessário ralizar a ordenação dos proprietários agora
		corredores_index proprietarios[corredor_veiculos_idx.qtd_registros_primario]; // vetor que será ordenado
		unsigned i; 
		printf(REGS_PERCORRIDOS);
		printf(" %d", found_modelo->primeiro_indice);
		for (i = 0; i < corredor_veiculos_idx.qtd_registros_primario; ++i) { // percorrendo a sequência de corredores proprietários do modelo para preencher o vetor de proprietários e contar sua quantidade
			strcpy(proprietarios[i].id_corredor, aux->chave_primaria);
			if (aux->proximo_indice != -1) {// se não for o último proprietário, itera
				printf(" %d", aux->proximo_indice);
				aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[aux->proximo_indice];
			}
			else 
				break;
		}
		printf("\n");

		// ordenando proprietários por cpf
		qsort(proprietarios, i+1, sizeof(corredores_index), qsort_corredores_idx);

		// listando
		for (unsigned j = 0; j <= i; ++j) {
			corredores_index index_proprietario;
			strcpy(index_proprietario.id_corredor, proprietarios[j].id_corredor); 
			corredores_index *found_proprietario = busca_binaria((void*)&index_proprietario, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0); 
			if (found_proprietario == NULL || found_proprietario->rrn < 0) // se não encontrar ou estiver deletado
				printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			else
				exibir_corredor(found_proprietario->rrn);
		}	
	}
	else // se o modelo não for encontrado no índice corredor_veiculos_secundario ele não não está vinculado a nenhum corredor
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);

	// printf(ERRO_NAO_IMPLEMENTADO, "listar_corredores_modelo_menu()");
}

void listar_veiculos_compra_menu(char *id_corredor) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	corredores_index index;
	strcpy(index.id_corredor, id_corredor); 
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0); 
	if (found == NULL || found->rrn < 0) // se o id do corredor for inválido
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else {
		Corredor c = recuperar_registro_corredor(found->rrn);
		veiculos_index index;
		veiculos_index *found = NULL;
		
		for(unsigned i = 0; i < qtd_registros_veiculos; ++i) {
			if (preco_veiculo_idx[i].preco <= c.saldo) {
				strcpy(index.id_veiculo, preco_veiculo_idx[i].id_veiculo);
				found = busca_binaria((void *)&index, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
				exibir_veiculo(found->rrn);
			}
		}
		if (!found) 
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	}
	// printf(ERRO_NAO_IMPLEMENTADO, "listar_veiculos_compra_menu()");
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/

	// reordenando o índice corridas_idx pela ocorrência/data
	qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx);

	corridas_index index, *found;
	strcpy(index.ocorrencia, data_inicio);
	found = busca_binaria_com_reps((void *)&index, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx, true, -1, 1);

	if (found) {
		if (strcmp(found->ocorrencia, data_fim) <= 0) { // se a ocorrência estiver dentro do intervalo
			for (unsigned i = (found - corridas_idx)/sizeof(corridas_index); i < qtd_registros_corridas && strcmp(corridas_idx[i].ocorrencia, data_fim) <= 0; i++) {
				exibir_corrida(corridas_idx[i].rrn);
			} 
		}
		else {// se houver ocorrências maiores/depois da data_inicio, mas elas forem maiores que a data_fim (fora do intervalo)
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			printf("aqui\n");
		}
	}
	else // se a busca biária retornar NULL, significa que não há registro com a ocorrência da data_inicio, nem registro com ocorrência maior/depois dela
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);

	// reordenando o índice corridas_idx por sua chave (id_pista e ocorrencia);
	qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);

	// printf(ERRO_NAO_IMPLEMENTADO, "listar_corridas_periodo_menu()");
}

/* Liberar espaço */
void liberar_espaco_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	unsigned i = 0, qtd_espacos_livres = 0;
	int i_livre = -1; // variável que indica o início do intervalo de blocos livres 
	while (i < qtd_registros_corredores) { 
		Corredor c = recuperar_registro_corredor(i);
		if (strncmp(c.id_corredor, "*|", 2) == 0) { // se corredor foi removido
			if (!qtd_espacos_livres) { // e não há espaço livre
				i_livre = i; // "inicializa" a a variável livre_i
			}
			qtd_espacos_livres++;			
		}
		else if (qtd_espacos_livres) { // se o corredor não foi removido e há espaço livre para movê-lo
			escrever_registro_corredor(c, i_livre); 
			// printf("movendo %s de [%d] para [%d]\n", c.nome, i, i_livre);
			i_livre++;
		}
		i++;
	}
	qtd_registros_corredores -= qtd_espacos_livres;
	ARQUIVO_CORREDORES[qtd_registros_corredores*TAM_REGISTRO_CORREDOR] = '\0';

	// recriando o arquivos de índice (corredores_idx e corredor_veiculos_idx)
    for (unsigned i = 0; i < qtd_registros_corredores; ++i) { // percorre corredores já existentes no arquivo de dados e preenche o arquivo de indices com base neles
        Corredor c = recuperar_registro_corredor(i);

		// recriando arquivo de índice corredores_idx
        corredores_idx[i].rrn = i;
        strcpy(corredores_idx[i].id_corredor, c.id_corredor);

		// recriando arquivo de índice corredor_veiculos_idx (secundário e primário)
		corredor_veiculos_idx.qtd_registros_secundario = 0;
		corredor_veiculos_idx.qtd_registros_primario = 0;
		for (unsigned j = 0; j < QTD_MAX_VEICULO; ++j) { // percorre os veículos do corredor
			if (strlen(c.veiculos[j])) { // verifica se o corredor possui véiculos
				// verifica se o veículo já está listado no índice corredor veículos secundário
				corredor_veiculos_secundario_index index_modelo;
				strncpy(index_modelo.chave_secundaria, strupr(c.veiculos[j]), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
				corredor_veiculos_secundario_index *found_modelo = busca_binaria((void *)&index_modelo, corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, false, 0);
				
				if (!found_modelo) { // se o modelo ainda não estiver no índice corredor_veiculos_secundario_idx, adiciona o modelo nele
					corredor_veiculos_secundario_index novo_modelo;
					strncpy(novo_modelo.chave_secundaria, strupr(c.veiculos[j]), TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX);
					novo_modelo.primeiro_indice = corredor_veiculos_idx.qtd_registros_primario;
					corredor_veiculos_idx.corredor_veiculos_secundario_idx[corredor_veiculos_idx.qtd_registros_secundario] = novo_modelo;
					corredor_veiculos_idx.qtd_registros_secundario++;

					// ordenar índice corredor_veiculos_secundario_idx
					qsort(corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx);
				}
				else { // se o modelo já estiver no índice corredor_veiculos_secundario_idx, percorre índice corredor_veiculos_primario_idx para atualização do campo próx. registro
					corredor_veiculos_primario_index *aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[found_modelo->primeiro_indice];
					while (aux->proximo_indice != -1) {
						aux = &corredor_veiculos_idx.corredor_veiculos_primario_idx[aux->proximo_indice];
					}
					aux->proximo_indice = corredor_veiculos_idx.qtd_registros_primario;
				}

				// adiciona o corredor/proprietario no índice corredor_veiculos_primario_idx
				corredor_veiculos_primario_index novo_proprietario;
				strcpy(novo_proprietario.chave_primaria, c.id_corredor);
				novo_proprietario.proximo_indice = -1;
				corredor_veiculos_idx.corredor_veiculos_primario_idx[corredor_veiculos_idx.qtd_registros_primario] = novo_proprietario;
				corredor_veiculos_idx.qtd_registros_primario++;
			}
		}
    }

	// ordenar índice corredores_idx
    qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx); // mantém uma ordenação dos índices
	
	printf(SUCESSO);
	// printf(ERRO_NAO_IMPLEMENTADO, "liberar_espaco_menu()");
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
	if (veiculos_idx == NULL || qtd_registros_veiculos == 0) 
		printf(ERRO_ARQUIVO_VAZIO);
	else 
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i) 
			printf("%s, %d\n", veiculos_idx[i].id_veiculo, veiculos_idx[i].rrn);
	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_veiculos_idx_menu()");
}

void imprimir_pistas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (pistas_idx == NULL || qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %d\n", pistas_idx[i].id_pista, pistas_idx[i].rrn);
	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_pistas_idx_menu()");
}

void imprimir_corridas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/

	if (corridas_idx == NULL || qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corridas; ++i) 
			printf("%s, %s, %d\n", corridas_idx[i].ocorrencia, corridas_idx[i].id_pista, corridas_idx[i].rrn);

	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_corridas_idx_menu()");
}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (nome_pista_idx == NULL || qtd_registros_pistas == 0) 
		printf(ERRO_ARQUIVO_VAZIO);
	else 
		for (unsigned i = 0; i < qtd_registros_pistas; ++i) 
			printf("%s, %s\n", nome_pista_idx[i].nome, nome_pista_idx[i].id_pista);
	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_nome_pista_idx_menu()");
}

void imprimir_preco_veiculo_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (preco_veiculo_idx == NULL || qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else 
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%.2f, %s\n", preco_veiculo_idx[i].preco, preco_veiculo_idx[i].id_veiculo);
	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_preco_veiculo_idx_menu()");
}

void imprimir_corredor_veiculos_secundario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.corredor_veiculos_secundario_idx == NULL || corredor_veiculos_idx.qtd_registros_secundario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; ++i) 
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria, corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice);
	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_corredor_veiculos_secundario_idx_menu()");
}

void imprimir_corredor_veiculos_primario_idx_menu(){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.corredor_veiculos_primario_idx == NULL || corredor_veiculos_idx.qtd_registros_primario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_primario; ++i) 
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria, corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice);
	// printf(ERRO_NAO_IMPLEMENTADO, "imprimir_corredor_veiculos_primario_idx_menu()");
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	free(corredores_idx);
	free(veiculos_idx);
	free(pistas_idx);
	free(nome_pista_idx);
	free(preco_veiculo_idx);
	free(corridas_idx);	
	free(corredor_veiculos_idx.corredor_veiculos_secundario_idx);
	free(corredor_veiculos_idx.corredor_veiculos_primario_idx);
	// printf(ERRO_NAO_IMPLEMENTADO, "liberar_memoria_menu()");
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
	const void *elemento;
	// void *base = base0;

	if(exibir_caminho){
		printf(REGS_PERCORRIDOS);
	}
	while(imin <= imax){
		if ((imax-imin+1)%2 == 0) // número de elementos no intervalo é par
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
			if(exibir_caminho)
				printf("\n");

			if (posicao_caso_repetido < 0) { // primeiro elemento do bloco de repetição
				// percorrendo até o elemento mais a esquerda (primeiro da seq. de repetidos) 
				while(base0 <= elemento - size && (*compar)(key, elemento - size) == 0) {
					elemento = elemento - size;
				}
			}
			else if (posicao_caso_repetido > 0) { // último elemento do bloco de repetição
				while(base0 + (size * nmemb) >= elemento + size && (*compar)(key, elemento + size) == 0) {
					elemento = elemento + size;
				}
			}
			else { // elemento do meio
				const void *elemento_ini = elemento;
				const void *elemento_fin = elemento;

				while((*compar)(key, elemento_ini - size) == 0) {
					elemento_ini = elemento_ini - size;
				}

				while((*compar)(key, elemento_fin + size) == 0) {
					elemento_fin = elemento_fin + size;
				}

				elemento = elemento_ini + (int)(((elemento_fin - elemento_ini)/size)/2) * size;
			}
			
			return (void *)elemento; 
		}
	}
	if(exibir_caminho)
		printf("\n");
	
	if (retorno_se_nao_encontrado < 0) { // retonrar elemento imediatamente menor que a chave (piso)
		if (cmp > 0) // se a chave já era maior que o elemento
			return (void *) elemento;
		else if (base0 <= elemento - size)
			return (void *) elemento - size;
	}
	else if (retorno_se_nao_encontrado > 0) { // retonrar elemento imediatamente maior que a chave (teto)
		if (cmp < 0) // se a chave já era menor que o elemento
			return (void *) elemento;
		else if (base0 + (size * nmemb) >= elemento + size)
			return (void *) elemento + size;
	}
	
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