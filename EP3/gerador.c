/***************************************************************/
/**                                                           **/
/**   Bruno Daiki Yamada                            9348780   **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Fernando Mário de Oliveira Filho             **/
/**   Turma: 5                                                **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int main()
{
    /*adquire apontadores*/
    FILE *in=0, *out=0;
    int grau;
    double scan1, scan2;

    in=fopen("polinomio.txt", "r");
    if(!in)
    {
        printf("Nao consegui abrir o arquivo para leitura!\n\n");
        return 0;
    }
    out=fopen("polinomio.c", "w");
    if(!out)
    {
        printf("Nao consegui abrir o arquivo para gravacao!\n");
        return 0;
    }

    /*comeca com o script*/
    fprintf(out, "void calcula(double x_real, double x_imag, double *p_real, double *p_imag, double *d_real, double *d_imag) {\n");
    fprintf(out, "	double a, b;\n");
    fprintf(out, "	*p_real=*p_imag=0;\n");
    fprintf(out, "	*d_real=*d_imag=0;\n");

    for(fscanf(in, "%d", &grau); grau>=0; grau--)
    {
        /*valor do polinomio*/
        fscanf(in, "%lf", &scan1);
        fscanf(in, "%lf", &scan2);
        if(!(scan1==0&&scan2==0)) /*quando os coeficientes sao nulos, nada e' impresso*/
        {
            fprintf(out, "	potencia(&a, &b, x_real, x_imag, %d);\n", grau);
            fprintf(out, "	multiplica(&a, &b, a, b, %.10g, %.10g);\n", scan1, scan2);
            fprintf(out, "	*p_real+=a;\n	*p_imag+=b;\n");
        }

        /*valor da derivada*/
        if(grau&&!(scan1==0&&scan2==0)) /*quando a variavel e' livre (grau-1==0), sua derivada e' 0*/
        {
            fprintf(out, "	potencia(&a, &b, x_real, x_imag, %d);\n", grau-1);
            fprintf(out, "	multiplica(&a, &b, a, b, %.10g, %.10g);\n", scan1*grau, scan2*grau);
            fprintf(out, "	*d_real+=a;\n	*d_imag+=b;\n");
        }
    }

    fprintf(out,"}");
    fclose(in);
    fclose(out);
    return 0;
}
