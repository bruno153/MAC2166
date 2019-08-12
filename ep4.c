/***************************************************************/
/**                                                           **/
/**   Bruno Daiki Yamada                Número USP: 9348780   **/
/**   Exercício-Programa 04                                   **/
/**   Professor: Fernando Mario Oliveira                      **/
/**   Turma: 05                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXLINHA 400
#define MAXCOLUNA 400
#define JANELA_MAX 50
#define MAX_NAME 256 /* tamanho maximo para nome de arquivo */

int le_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int *linhas, int* colunas, int* maiorValor);
int grava_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int maiorValor);
void ordena(int ordenar[JANELA_MAX*JANELA_MAX], int k);
int mediana(int mediana[JANELA_MAX*JANELA_MAX], int k);
int minimo(int minimo[JANELA_MAX*JANELA_MAX], int k);
int maximo(int maximo[JANELA_MAX*JANELA_MAX], int k);
int novomaiorvalor(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void display(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
int compara(int m[MAXLINHA][MAXCOLUNA], int linhasm, int colunasm, char* name);
void help();
void concatenar(char nome[MAX_NAME], char *letra, int *hifen);
void negativo(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void rebatimentoVertical(int m[MAXLINHA][MAXCOLUNA], int linhas,int colunas);
void rebatimentoHorizontal(int m[MAXLINHA][MAXCOLUNA], int linhas,int colunas);
void rotacao(int m[MAXLINHA][MAXCOLUNA], int* linhas, int* colunas);
void corte(int m[MAXLINHA][MAXCOLUNA], int* linhas, int* colunas, int xsup, int ysup, int xinf, int yinf);
void filtroMediana(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void filtroMedia(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void filtroErosao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void filtroDilatacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void limiarizacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int k);
void filtroBorda1(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k);
void filtroBorda2(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k);
void filtroBorda3(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k);



int main()
{
    int m[MAXLINHA][MAXCOLUNA], linhas, colunas, maiorvalor, hifen=0;
    char arquivo[MAX_NAME], comando[2];
    comando[1]='\0';/*comando armazena o char do comando na posicao 0, e o null na posicao 1, para poder usar strcat()*/
    while(1)
    {
        printf("Digite o nome do arquivo de entrada: ");
        scanf(" %s", arquivo);
        if(le_pgm(arquivo, m, &linhas, &colunas, &maiorvalor))
        {
            printf("Arquivo %s.pgm carregado com sucesso.\n", arquivo);
            break;
        }
    }
    help();

    while(!(comando[0]=='s'))
    {
        printf("Digite um comando: ");
        scanf(" %c", &comando[0]);
        if(comando[0]=='c')
        {
            while(1)
            {
                printf("Digite o nome do arquivo de entrada: ");
                scanf(" %s", arquivo);
                if(le_pgm(arquivo, m, &linhas, &colunas, &maiorvalor))
                {
                    printf("Arquivo %s.pgm carregado com sucesso.\n", arquivo);
                    break;
                }
            }
        }
        if(comando[0]=='t')
        {
            display(m, linhas, colunas);
        }
        if(comando[0]=='n')
        {
            negativo(m, linhas, colunas);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='r')
        {
            rotacao(m, &linhas, &colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='v')
        {
            rebatimentoVertical(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='h')
        {
            rebatimentoHorizontal(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='x')
        {
            int xsup, ysup, xinf, yinf;
            printf("Informe x superior: ");
            scanf("%d", &xsup);
            printf("Informe y superior: ");
            scanf("%d", &ysup);
            printf("Informe x inferior: ");
            scanf("%d", &xinf);
            printf("Informe y inferior: ");
            scanf("%d", &yinf);
            corte(m, &linhas, &colunas, xsup, ysup, xinf, yinf);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='e')
        {
            int janela;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            filtroErosao(m, linhas, colunas, janela);
            printf("Operacao realizada com sucesso.\n");
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='d')
        {
            int janela;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            filtroDilatacao(m, linhas, colunas, janela);
            printf("Operacao realizada com sucesso.\n");
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='m')
        {
            int janela;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            filtroMediana(m, linhas, colunas, janela);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='z')
        {
            int janela;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            filtroMedia(m, linhas, colunas, janela);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='1')
        {
            int janela, k;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            printf("Informe o valor de k: ");
            scanf("%d", &k);
            filtroBorda1(m, linhas, colunas, janela, k);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='2')
        {
            int janela, k;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            printf("Informe o valor de k: ");
            scanf("%d", &k);
            filtroBorda2(m, linhas, colunas, janela, k);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='3')
        {
            int janela, k;
            printf("Digite o tamanho da janela: ");
            scanf("%d", &janela);
            printf("Informe o valor de k: ");
            scanf("%d", &k);
            filtroBorda3(m, linhas, colunas, janela, k);
            maiorvalor=novomaiorvalor(m, linhas, colunas);
            concatenar(arquivo, comando, &hifen);
        }
        if(comando[0]=='g')
        {
            if(grava_pgm(arquivo, m, linhas, colunas, maiorvalor))
            {
                printf("Arquivo %s.pgm gravado com sucesso\n",arquivo);
            }
        }
        if(comando[0]=='C')
        {
            char name[MAX_NAME];
            printf("Digite o nome do arquivo com a imagem a ser comparada: ");
            scanf("%s", name);
            compara(m, linhas, colunas, name);
        }
        if(comando[0]=='a')
        {
            help();
        }
    }
    return 0;
}



int le_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int *linhas, int* colunas, int* maiorValor){
    /* ----------------------------------------------
    Le um arquivo no formato PGM.
    prefixo_do_nome : prefixo do arquivo pgm
    m : matriz correspondente a imagem lida
    linhas : numero de linhas da matriz
    colunas : numero de colunas da matriz
    max_value : maior valor na matriz
    ---------------------------------------------- */
    FILE *arq;
    char key[128];
    int i, j, aux;
    char fname[MAX_NAME];
    /* monta o nome do arquivo */
    strcpy(fname, prefixo_do_nome);
    strcat(fname,".pgm");
    /* abre o o arquivo de entrada para leitura */
    arq = fopen(fname, "r");
    if (arq == NULL){
        printf("Erro na abertura do arquivo %s\n",fname);
        return 0;
    }
    /* le dados do cabecalho */
    aux = fscanf(arq, "%s", key);
    if (aux != 1){
        printf("Erro na leitura do arquivo %s \n",fname);
        return 0;
    }
    if(strcmp(key,"P2") != 0) {
        printf("Formato desconhecido\n") ;
        fclose(arq) ;
        return 0;
    }
    aux = fscanf(arq, "%d %d %d", colunas, linhas, maiorValor) ;
    if (aux != 3) {
        printf("Formato incorreto\n") ;
        fclose(arq) ;
        return 0;
    }
    /* le a matriz (imagem) que se segue */
    for(i = 0; i < *linhas; i++) {
        for(j = 0; j < *colunas; j++) {
            fscanf(arq, "%d", &m[i][j]);
        }
    }
    fclose(arq) ; /* fecha arquivo */
    return 1;
}

int grava_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int maiorValor){
    /* ----------------------------------------------
    Escreve um arquivo, no formato PGM.
    prefixo_do_nome : prefixo do arquivo pgm
    m : matriz correspondente a imagem lida
    linhas : numero de linhas da matriz
    colunas : numero de colunas da matriz
    max_value : maior valor na matriz
    ---------------------------------------------- */
    FILE *arq;
    int i, j;
    char fname[MAX_NAME];
    /* monta o nome do arquivo */
    strcpy(fname, prefixo_do_nome);
    strcat(fname,".pgm");
    /*abre o o arquivo para gravacao */
    arq = fopen(fname, "w");
    if (arq == NULL){
        printf("Erro na abertura do arquivo %s\n",fname);
        return 0;
    }
    /* grava dados do cabecalho */
    fprintf(arq, "P2\n");
    fprintf(arq, "%d %d\n%d\n", colunas, linhas, maiorValor);
    /* grava a matriz (imagem) que se segue */
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            fprintf(arq, "%d ", m[i][j]);
        }
    fprintf(arq, "\n");
    }
    fclose(arq); /* fecha arquivo */
    return 1;
}

void ordena(int ordenar[JANELA_MAX*JANELA_MAX], int k) /*recebe vetor tamanho k e o ordena*/
{
    int i, j, menor;

    for(i=0; i<k; i++)
    {
        menor=i;
        for(j=(i+1); j<k; j++)
        {
            if(ordenar[menor]>ordenar[j])
            {
                menor=j;
            }
        }
        if(i!=menor)
        {
            ordenar[i]=ordenar[i]+ordenar[menor];
            ordenar[menor]=ordenar[i]-ordenar[menor];
            ordenar[i]=ordenar[i]-ordenar[menor];
        }
    }
}

int mediana(int ordem[JANELA_MAX*JANELA_MAX], int k) /*retorna mediana do vetor de tamanho k*/
{
    ordena(ordem, k);
    return ordem[k/2];
}

int minimo(int minimo[JANELA_MAX*JANELA_MAX], int k) /*retorna valor minimo do vetor de tamanho k*/
{
    ordena(minimo, k);
    return minimo[0];
}

int maximo(int maximo[JANELA_MAX*JANELA_MAX], int k) /*retorna valor maximo do vetor de tamanho k*/
{
    ordena(maximo, k);
    return maximo[k-1];
}

int novomaiorvalor(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) /*update no novo maior valor da matriz de n linhas e m colunas*/
{
    int i, j, maiorlinha=0, maiorcoluna=0;
    for(j=0; j<colunas; j++)
    {
        for(i=0; i<linhas; i++)
        {
            if(m[i][j]>m[maiorlinha][maiorcoluna])
            {
                maiorlinha=i;
                maiorcoluna=j;
            }
        }
    }
    return m[maiorlinha][maiorcoluna];
}

void negativo(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) /*aplica efeito negativo*/
{
    int i, j;
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            m[i][j]=255-m[i][j];
        }
    }
    printf("Operacao realizada com sucesso.\n");
}

void display(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) /*imprime no prompt a matriz m*/
{
    int i, j;
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int compara(int m[MAXLINHA][MAXCOLUNA], int linhasm, int colunasm, char* name) /*compara duas matrizes e imprime onde esta o erro caso o tenha*/
{
    int i, j, n[MAXLINHA][MAXCOLUNA], linhasn, colunasn;

    le_pgm(name, n, &linhasn, &colunasn, &i);
    if((linhasn!=linhasm)||(colunasn!=colunasm))
    {
        printf("As matrizes tem dimensoes diferentes\n");
        return 0;
    }
    for(i=0; i<linhasm; i++)
    {
        for(j=0; j<colunasm; j++)
        {
            if(m[i][j]!=n[i][j])
            {
                printf("As matrizes tem valores diferentes na posicao %d, %d\n", i, j);
                return 0;
            }
        }
    }
    printf("As matrizes sao iguais\n");
    return 0;
}

void help() /*imprime na tela a lista de comandos*/
{
    printf("c - carga\nt - exibicao na tela\nn - negativo\nr - rotacao\nv - espelhamento vertical\nh - espelhamento horizontal\nx - corte\ne - filtro da erosao\nd - filtro da dilatacao\nm - filtro da mediana\nz - filtro da media\n1 - filtro de bordas 1\n2 - filtro de bordas 2\n3 - filtro de bordas 3\ng - gravacao\nC - comparacao\na - ajuda\ns - sair\n\n");
}

void concatenar(char nome[MAX_NAME], char *letra, int *hifen) /*adiciona o comando digitado pelo usuario e adiciona hifen pela primeira vez*/
{
    if(!(*hifen))
    {
        strcat(nome, "-");
        (*hifen)++;
    }
    strcat(nome, letra);
}

void rebatimentoHorizontal(int m[MAXLINHA][MAXCOLUNA], int linhas,int colunas)
{
    int i, j;
    for(j=0; j<colunas; j++)
    {
        for(i=0; i<(linhas/2); i++)
        {
            m[i][j]+=m[linhas-i-1][j];
            m[linhas-i-1][j]=m[i][j]-m[linhas-i-1][j];
            m[i][j]-=m[linhas-i-1][j];
        }
    }
    printf("Operacao realizada com sucesso.\n");
}

void rebatimentoVertical(int m[MAXLINHA][MAXCOLUNA], int linhas,int colunas)
{
    int i, j;
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<(colunas/2); j++)
        {
            m[i][j]+=m[i][colunas-j-1];
            m[i][colunas-j-1]=m[i][j]-m[i][colunas-j-1];
            m[i][j]-=m[i][colunas-j-1];
        }
    }
    printf("Operacao realizada com sucesso.\n");
}

void rotacao(int m[MAXLINHA][MAXCOLUNA], int* linhas, int* colunas)
{
    int temp[MAXLINHA][MAXCOLUNA], i, j;
    for(i=0; i<*linhas; i++)
    {
        for(j=0; j<*colunas; j++)
        {
            temp[i][j]=m[i][j];
        }
    }
    for(i=0; i<*linhas; i++)
    {
        for(j=0; j<*colunas; j++)
        {
            m[j][*linhas-i-1]=temp[i][j];
        }
    }
    *linhas+=*colunas; /*troca as linhas com colunas*/
    *colunas=*linhas-*colunas;
    *linhas-=*colunas;
    printf("Operacao realizada com sucesso.\n");
}

void corte(int m[MAXLINHA][MAXCOLUNA], int* linhas, int* colunas, int xsup, int ysup, int xinf, int yinf)
{
    int temp[MAXLINHA][MAXCOLUNA], i, j;
    if(xsup>=*linhas||ysup>=*colunas||xinf>=*linhas||yinf>=*colunas) /*para o programa se as coordenadas sao invalidas*/
    {
        printf("Limites invalidos\n");
    }
    else /*somente realiza a operacao se as coordenadas sao validas*/
    {
        for(i=0; i<*linhas; i++) /*copia a matriz no temporario*/
        {
            for(j=0; j<*colunas; j++)
            {
                temp[i][j]=m[i][j];
            }
        }
        *colunas=(yinf-ysup)+1; /*atualiza colunas e linhas*/
        *linhas=(xinf-xsup)+1;
        for(i=0; i<*linhas; i++) /*copia a regiao selecionada*/
        {
            for(j=0; j<*colunas; j++)
            {
                m[i][j]=temp[xsup+i][ysup+j];
            }
        }
        printf("Operacao realizada com sucesso.\n");
    }

}

void filtroMediana(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela)
{
    int temp[MAXLINHA][MAXCOLUNA], i, j, k, l, tamanho=0, seq[JANELA_MAX*JANELA_MAX];

    for(i=0; i<linhas; i++) /*copia a matriz para uma temporaria*/
    {
        for(j=0; j<colunas; j++)
        {
            temp[i][j]=m[i][j];
        }
    }
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            for(k=-larguraJanela/2; k<=larguraJanela/2; k++)
            {
                for(l=-larguraJanela/2; l<=larguraJanela/2; l++)
                {
                    if(i+k>=0&&i+k<linhas&&j+l>=0&&j+l<colunas) /*verifica se a coordenada relativa e' valida*/
                    {
                        seq[tamanho]=temp[i+k][j+l]; /*adiciona o numero da coordenada no vetor e ajusta o tamanho*/
                        tamanho++;
                    }
                }
            }
            m[i][j]=mediana(seq, tamanho); /*aplica a mediana*/
            tamanho=0;
        }
    }
    printf("Operacao realizada com sucesso.\n");
}

void filtroMedia(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela)
{
    int temp[MAXLINHA][MAXCOLUNA], i, j, k, l, total=0, tamanho=0;

    for(i=0; i<linhas; i++) /*copia a matriz para uma temporaria*/
    {
        for(j=0; j<colunas; j++)
        {
            temp[i][j]=m[i][j];
        }
    }
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            for(k=-larguraJanela/2; k<=larguraJanela/2; k++)
            {
                for(l=-larguraJanela/2; l<=larguraJanela/2; l++)
                {
                    if(i+k>=0&&i+k<linhas&&j+l>=0&&j+l<colunas) /*verifica se a coordenada relativa e' valida*/
                    {
                        total+=temp[i+k][j+l]; /*adiciona o numero da coordenada na soma*/
                        tamanho++;
                    }
                }
            }
            m[i][j]=total/tamanho; /*calcula a media e salva na matriz*/
            tamanho=0;
            total=0;
        }
    }
    printf("Operacao realizada com sucesso.\n");
}

void filtroErosao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela)
{
    int temp[MAXLINHA][MAXCOLUNA], i, j, k, l, tamanho=0, seq[JANELA_MAX*JANELA_MAX];

    for(i=0; i<linhas; i++) /*copia a matriz para uma temporaria*/
    {
        for(j=0; j<colunas; j++)
        {
            temp[i][j]=m[i][j];
        }
    }
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            for(k=-larguraJanela/2; k<=larguraJanela/2; k++)
            {
                for(l=-larguraJanela/2; l<=larguraJanela/2; l++)
                {
                    if(i+k>=0&&i+k<linhas&&j+l>=0&&j+l<colunas) /*verifica se a coordenanda relativa e' valida*/
                    {
                        seq[tamanho]=temp[i+k][j+l]; /*salva o numero da coordenada no vetor*/
                        tamanho++;
                    }
                }
            }
            m[i][j]=minimo(seq, tamanho); /*salva o valor minimo do vetor na matriz*/
            tamanho=0;
        }
    }
}

void filtroDilatacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela)
{
    int temp[MAXLINHA][MAXCOLUNA], i, j, k, l, tamanho=0, seq[JANELA_MAX*JANELA_MAX];

    for(i=0; i<linhas; i++) /*copia a matriz para uma temporaria*/
    {
        for(j=0; j<colunas; j++)
        {
            temp[i][j]=m[i][j];
        }
    }
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            for(k=-larguraJanela/2; k<=larguraJanela/2; k++)
            {
                for(l=-larguraJanela/2; l<=larguraJanela/2; l++)
                {
                    if(i+k>=0&&i+k<linhas&&j+l>=0&&j+l<colunas) /*verifica se a coordenada relativa e' valida*/
                    {
                        seq[tamanho]=temp[i+k][j+l]; /*salva o numero da coordenada no vetor*/
                        tamanho++;
                    }
                }
            }
            m[i][j]=maximo(seq, tamanho); /*salva o valor maximo na matriz*/
            tamanho=0;
        }
    }
}

void limiarizacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int k)
{
    int i, j;
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            if(m[i][j]>=k)
            {
                m[i][j]=255;
            }
            else
            {
                m[i][j]=0;
            }
        }
    }
}

void filtroBorda1(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k)
{
    /* nesse caso, a matriz m sera erosao, e a matriz d dilatacao*/
    int d[MAXLINHA][MAXCOLUNA], i, j;
    for(i=0; i<linhas; i++) /*copia a matriz m em d*/
    {
        for(j=0; j<colunas; j++)
        {
            d[i][j]=m[i][j];
        }
    }
    filtroErosao(m, linhas, colunas, larguraJanela);
    filtroDilatacao(d, linhas, colunas, larguraJanela);
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            m[i][j]=d[i][j]-m[i][j];
        }
    }
    limiarizacao(m, linhas, colunas, k);
    printf("Operacao realizada com sucesso.\n");
}

void filtroBorda2(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k)
{
    int e[MAXLINHA][MAXCOLUNA], i, j;
    for(i=0; i<linhas; i++) /*copia a matriz*/
    {
        for(j=0; j<colunas; j++)
        {
            e[i][j]=m[i][j];
        }
    }
    filtroErosao(e, linhas, colunas, larguraJanela);
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            m[i][j]-=e[i][j];
        }
    }
    limiarizacao(m, linhas, colunas, k);
    printf("Operacao realizada com sucesso.\n");
}

void filtroBorda3(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k)
{
    int d[MAXLINHA][MAXCOLUNA], i, j;
    for(i=0; i<linhas; i++) /*copia a matriz*/
    {
        for(j=0; j<colunas; j++)
        {
            d[i][j]=m[i][j];
        }
    }
    filtroDilatacao(d, linhas, colunas, larguraJanela);
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            m[i][j]=d[i][j]-m[i][j];
        }
    }
    limiarizacao(m, linhas, colunas, k);
    printf("Operacao realizada com sucesso.\n");
}
