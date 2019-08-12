/***************************************************************/
/**                                                           **/
/**   Bruno Daiki Yamada                            9348780   **/
/**   Exercício-Programa 01                                   **/
/**   Professor: Fernando Mário de Oliveira Filho             **/
/**   Turma: 5                                                **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int main()
{
    //Variables
    int m; //algarismos
    int e; //posicao da virgula
    int counter=1; //fator em base 10
    int zero=0; //numero de zeros depois da virgula
    int right=0; //algarismos depois da virgula

    //Data aquisition
    printf("MAC2166 - EP1 - Usando Inteiros para Representar Reais\n\nDigite os algarismos do numero..................: ");
    scanf("%d",&m);
    printf("Digite a posicao do separador das casas decimais: ");
    scanf("%d",&e);

    //Answer
    if(e==0) //quebra o processo se e for igual a 0
    {
        printf("O numero correspondente na notacao decimal e....: %d", m);
        return(0);
    }

    for (e;e>0;e--)
    {
        right=right+(counter*(m%10)); //adquire o algarismo na casa correta
        if(m==0) //conta a quantidade de zeros depois da virgula
        {
            zero++;
        }
        m=m/10;
        counter= counter*10; //permite que o proximo algarismo possa ser armazenado na casa correta
    }
    printf("O numero correspondente na notacao decimal e....: %d", m); //imprime a primeira parte
    printf(",");
    for(zero;zero>0;zero--) //imprime os zeros depois da virgula
    {
        printf("0");
    }
    printf("%d", right); //imprime os algarismos depois da virgula
}
