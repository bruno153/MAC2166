/***************************************************************/
/**                                                           **/
/**   Bruno Daiki Yamada                            9348780   **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Fernando Mário de Oliveira Filho             **/
/**   Turma: 5                                                **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

/*
Prototipos
*/
void multiplica(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag);

void potencia(double *ret_real, double *ret_imag, double x_real, double x_imag, int k);

double absolute(double number);

int newton(double *x_real, double *x_imag, int max_iter, double eps);

/*
Funcao que calcula o polinomio
*/
#include "polinomio.c"

/*
Funcao main
*/
int main()
{
    /*setup de variaveis*/
    double l, u, e, delta, u_real, u_imag;
    int N, max_iter, i, j;
    FILE *out;

    out=fopen("saida.txt", "w");

    /*aquisicao de dados*/
    printf("Digite o valor de l       : ");
    scanf("%lf", &l);
    printf("Digite o valor de u       : ");
    scanf("%lf", &u);
    printf("Digite o valor de N       : ");
    scanf("%d", &N);
    printf("Digite o valor de max_iter: ");
    scanf("%d", &max_iter);
    printf("Digite o valor de epsilon : ");
    scanf("%lf", &e);

    /*calcula a resolucao*/
    delta=(u-l)/N;
    u_real=l;
    u_imag=l;

    /*setup do txt*/
    fprintf(out, "%d\n", N);

    /*inicializa a sequencia*/
    for(i=0; i<=N; i++)
    {
        for(j=0; j<=N; j++)
        {
            u_real=l+(delta*i);
            u_imag=l+(delta*j);
            if(newton(&u_real, &u_imag, max_iter, e))
            {
                fprintf(out, "%.10g ", u_real);
                fprintf(out, "%.10g ", u_imag);
            }
            else
            {
                fprintf(out, "N ");
            }
        }

        fprintf(out, "\n");
    }
    fclose(out);
    return 0;
}

void multiplica(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag)
{
    *ret_real=(x_real*y_real)-(x_imag*y_imag); /*multiplicacao entre complexos*/
    *ret_imag=(x_real*y_imag)+(x_imag*y_real);
}

void potencia(double *ret_real, double *ret_imag, double x_real, double x_imag, int k)
{
    double f_real=x_real, f_imag=x_imag;

    *ret_real=x_real; /*caso k==1, devemos retornar os proprios valores*/
    *ret_imag=x_imag;

    if(k!=1)
    {
        for(; k>1; k--)/*executa a potencia*/
        {
            multiplica(&f_real, &f_imag, f_real, f_imag, x_real, x_imag);
        }

        *ret_real=f_real;
        *ret_imag=f_imag;
    }
    if(k==0) /*qualquer coisa nao nula elevado a 0 e' 1*/
    {
        *ret_imag=0;
        *ret_real=1;
    }
    if((x_real==0)&&(x_imag==0)) /*0 elevado a alguma coisa e'0*/
    {
        *ret_real=0;
        *ret_imag=0;
    }
    /*note que 0 elevado a 0 e' indeterminado, essa funcao retorna 0*/
}

double absolute(double number) /*recebe um double, retorna seu valor absoluto*/
{
    if(number<0)
    {
        number=-number;
    }
    return number;
}

int newton(double *x_real, double *x_imag, int max_iter, double eps)
{
    double d_real, d_imag, p_real, p_imag;
    int i=0;
    for(; i<=max_iter; i++) /*sai do loop se o max_iter of atingido*/
    {
        calcula(*x_real, *x_imag, &p_real, &p_imag, &d_real, &d_imag);

        if((absolute(p_real)<=eps)&&(absolute(p_imag)<=eps)) /*o processo foi terminado com sucesso*/
        {

            return 1;
        }

        if((absolute(d_real)<=eps)&&(absolute(d_imag)<=eps)) /*processo falhou por metodo resultar em div por 0*/
        {
            return 0;
        }

        if(!(abs(d_imag)<=eps)) /*verifica se e' necessario multiplicar pelo conjugado*/
        {
            multiplica(&p_real, &p_imag, p_real, p_imag, d_real, -d_imag); /*multiplica pelo conjugado*/
            multiplica(&d_real, &d_imag, d_real, d_imag, d_real, -d_imag);
        }

        *x_real=*x_real-(double)(p_real/(d_real)); /*calcula o proximo termo da aproximacao*/
        *x_imag=*x_imag-(double)(p_imag/(d_real));
    }
    return 0; /*processo falhou por superar max_iter*/
}
