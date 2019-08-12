/***************************************************************/
/**                                                           **/
/**   Bruno Daiki Yamada                            9348780   **/
/**   Exercício-Programa 02                                   **/
/**   Professor: Fernando Mário de Oliveira Filho             **/
/**   Turma: 5                                                **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int flag; // 0==nenhum problema; 1==overflow positivo; 2==overflow negativo; -1==underflow

int mant(int num) //recebe o numero na notacao padrao, retorna somente a mantissa com o sinal
{
    if(num<0) //se o número for negativo
    {
        num=-num;
        return(-(num/1000));
    }
    return(num/1000);
}

int expp(int num) //recebe o numero na notacao padrao, retorna somente o expoente com o sinal
{
    if(num<0)
    {
        num=-num;
    }
    if(num%1000>=100) //se o expoente for negativo
    {
        return(-(num%100));
    }
    return(num%100);
}

int gen_num(int man, int num) //recebe mantissa e expoente com sinal, retorna numero na notacao, E ESPERADO CONFORMIDADE COM A MANTISSA
{
    if(man>0) //mostra somente os 6 digitos mais significativos, tanto remove zeros desnecessarios como diminui uma mantissa com mais de 7 digitos
    {
        while(man%10==0||man>1000000)
        {
            man=man/10;
            num++;
        }
    }
    if(man<0)
    {
        while((-man)%10==0||man<-1000000)
        {
            man=man/10;
            num++;
        }
    }

    if(man==0) //retorna 0 para mantissa igual a 0
    {
        return 0;
    }
    if(num>99) //detecta overflow
    {
        printf("\n*** AVISO: ocorreu um overflow no expoente. ***");
        if(man>0) //overflow positivo
        {
            flag=1;
        }
        else //overflow negativo
        {
            flag=2;
        }
    }
    if(num<-99) //detecta underflow
    {
        printf("\n*** AVISO: ocorreu um underflow no expoente. ***");
        flag=-1;
    }
    if(num<0) //expoente negativo
    {
        return(man*1000+(-num+100));
    }
    else //expoente positivo
    {
        return((man*1000)+num);
    }
}

int sum(int parcela1, int parcela2) //recebe as parcelas em notacao padrao, retorna soma na notacao padrao
{
    int n1,n2,e1,e2,modulo;
    if(expp(parcela1)>expp(parcela2)) //n1 e e1 sempre pertencem a parcela com maior exp
    {
        n1=mant(parcela1);
        n2=mant(parcela2);
        e1=expp(parcela1);
        e2=expp(parcela2);
    }
    else
    {
        n1=mant(parcela2);
        n2=mant(parcela1);
        e1=expp(parcela2);
        e2=expp(parcela1);
    }

    if(n1<0)
    {
        modulo=-n1;
    }
    else
    {
        modulo=n1;
    }

    while(modulo<100000&&e1!=e2) //diminui o expoente do e1 ate quando for possivel ou necessario
    {
        n1=n1*10;
        e1--;
    }
    while(e1!=e2)
    {
        n2=n2/10;
        e2++;
    }

    n1=n1+n2;

    if(n1>0) //mostra somente os 6 digitos mais significativos, tanto remove zeros desnecessarios como diminui uma mantissa com mais de 7 digitos
    {
        while(n1%10==0||n1>1000000)
        {
            n1=n1/10;
            e1++;
        }
    }
    if(n1<0)
    {
        while((-n1)%10==0||n1<-1000000)
        {
            n1=n1/10;
            e1++;
        }
    }

    if(e1>99) //overflow
    {
        e1=99;
        if(n1>0) // condicoes diferentes caso o numero seja negativo ou positivo
        {
            n1=999999;
            flag=1;
        }
        else
        {
            n1=-999999;
            flag=2;
        }
        printf("\n*** AVISO: ocorreu um overflow no expoente. ***");
    }
    if(e1<-99) //underflow
    {
        n1=0;
        e1=0;
        flag=-1;
        printf("\n*** AVISO: ocorreu um underflow no expoente. ***");
    }
    if(e1<0)//se expoente for negativo, aplica muda o numero das centenas para 1
    {
        e1=-e1;
        e1=e1+100;
    }

    if(n1>0)
    {
        return(((n1)*1000)+e1);
    }
    else
    {
        return(((n1)*1000)-e1);
    }
}

int mult(int coeficiente1, int coeficiente2) //recebe coeficientes na notacao padrao, retorna produto na notacao padrao
{
    int nn1,nn2,ee1,ee2,digito,ee;
    int prod=0;

    nn1=mant(coeficiente1);
    nn2=mant(coeficiente2);
    ee1=expp(coeficiente1);
    ee2=expp(coeficiente2);

    if(nn1<0) //mantem as mantissas posistivas, para que nao ocorra erro com operacoes de resto e divisao inteiro
    {
        nn1=-nn1;
    }
    if(nn2<0)
    {
        nn2=-nn2;
    }

    while(nn2!=0) //executa a soma entre os produtos de cada digito
    {
        ee=ee1+ee2;
        digito=gen_num((nn1*(nn2%10)),ee); //executa a multiplicacao para um digito
        prod=sum(prod,digito);

        if(flag==1) //retornam valores pre determinados para casos de overflow e underflow
        {
            return 999999099;
        }
        if(flag==2)
        {
            return -999999099;
        }
        if(flag==-1)
        {
            return 0;
        }

        nn2=nn2/10;
        ee2++;
    }
    if((coeficiente1<0&&coeficiente2>0)||(coeficiente1>0&&coeficiente2<0)) //inverte o sinal conforme a regra de sinais
    {
        prod=-prod;
    }
    return prod;
}

int div(int numerador, int denominador) //recebe numerador e denominador na notacao padrao, retorna divisao na notacao padrao
{
    int nn1,nn2,ee1,ee2,resultado,novo;
    resultado=0;
    nn1=mant(numerador); //obtem expoentes e mantissas para realizar a operacao
    nn2=mant(denominador);
    ee1=expp(numerador);
    ee2=expp(denominador);

    if(nn1<0) //mantem as mantissas posistivas, para que nao ocorra erro com operacoes de resto e divisao inteiro
    {
        nn1=-nn1;
    }
    if(nn2<0)
    {
        nn2=-nn2;
    }

    ee1=ee1-ee2; //executa a subtracao entre expoentes antes do loop

    while((resultado<100000000)&&(nn1!=0))
    {
        novo=nn1/nn2;
        resultado=sum(gen_num((novo),ee1),resultado);
        nn1=((nn1%nn2)*10);
        ee1--;
    }

    if(flag==1) //retorna valores diferentes para os flags
    {
        return 999999099;
    }
    if(flag==2)
    {
        return -999999099;
    }
    if(flag==-1)
    {
        return 0;
    }

    if((denominador<0&&numerador>0)||(denominador>0&&numerador<0))
    {
        return -resultado;
    }

    return resultado;


}

int main()
{
    int op1=0, op2=0, operacao;
    printf("MAC2166 - EP2 - Calculadora para Numeros de Ponto Flutuante\n");

    while(1)
    {
        printf("\nOperando 1...................: ");
        scanf("%d",&op1);
        while(1)
        {
            printf("\nOperacoes disponiveis: 1 (+), 2 (-), 3 (*), 4 (/), 5 (limpar), 6 (parar)\nNumero da operacao desejada..: ");
            scanf("%d",&operacao);
            if(operacao>4) //executa o break se o usuario escolher limpar o parar
            {
                break;
            }
            printf("\nOperando 2...................: ");
            scanf("%d",&op2);

            if(operacao==1)
            {
                op1=sum(op1,op2);
                printf("\nResultado (e novo operando 1): %d\n",op1);
            }
            if(operacao==2)
            {
                op1=sum(op1,-op2);
                printf("\nResultado (e novo operando 1): %d\n",op1);
            }
            if(operacao==3)
            {
                op1=mult(op1,op2);
                printf("\nResultado (e novo operando 1): %d\n",op1);
            }
            if(operacao==4)
            {
                if(op2!=0)
                {
                    op1=div(op1,op2);
                    printf("\nResultado (e novo operando 1): %d\n",op1);
                }
                else
                {
                    printf("\n*** ERRO: nao e' possivel dividir por zero. ***\n");
                }
            }
            flag=0; //reinicia o flag
        }
        if(operacao>5)
        {
            printf("\nTchau!");
            return 0;
        }
    }
}
